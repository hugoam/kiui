//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkInk.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/mkUiWindow.h>
#include <Ui/Widget/mkRootSheet.h>

using namespace std::placeholders;

namespace mk
{
	bool Inkbox::sDebugDraw = false;
	int Inkbox::sDebugBatch = 0;

	InkWindow::InkWindow(UiWindow& uiWindow, unique_ptr<Renderer> renderer)
		: m_uiWindow(uiWindow)
		, m_renderer(std::move(renderer))
		, m_screenTarget(make_unique<InkTarget>(*m_renderer, 50))
	{}

	void InkWindow::addImage(const string& image, int width, int height)
	{
		m_images.emplace_back(image, width, height);
	}

	void InkWindow::draw()
	{
		m_uiWindow.rootSheet().layer().inkLayer().draw();
	}

	InkLayer::InkLayer(Layer& layer, InkTarget& target, size_t z)
		: m_layer(layer)
		, m_frame(layer)
		, m_target(target)
		, m_z(z)
	{}

	void InkLayer::show()
	{
		m_frame.inkbox().show();
		//this->moveToTop();
	}

	void InkLayer::hide()
	{
		m_frame.inkbox().hide();
	}

	void InkLayer::move(size_t pos, size_t z)
	{
		UNUSED(pos); UNUSED(z);

		/*if(!m_layer.bound() || !m_layer.parent()) return;
		*/
	}

	void InkLayer::draw()
	{
		this->drawImage(m_frame);
		this->drawText(m_frame);

		for(Layer* sublayer : m_layer.layers())
			if(sublayer->visible())
				sublayer->inkLayer().draw();
	}

	void InkLayer::drawImage(Frame& frame)
	{
		frame.inkbox().drawImage();

		if(frame.frameType() >= STRIPE)
			for(Frame* subframe : frame.as<Stripe>().contents())
				if(subframe->visible() && subframe->frameType() < LAYER)
					this->drawImage(*subframe);
	}

	void InkLayer::drawText(Frame& frame)
	{
		frame.inkbox().drawText();

		if(frame.frameType() >= STRIPE)
			for(Frame* subframe : frame.as<Stripe>().contents())
				if(subframe->visible() && subframe->frameType() < LAYER)
					this->drawText(*subframe);
	}

	InkTarget::InkTarget(Renderer& renderer, size_t layers)
		: d_renderer(renderer)
		, d_layers(layers)
		, d_rootLayer(nullptr)
	{}

	Inkbox::Inkbox(Frame& frame)
		: m_frame(frame)
		, m_visible(true)
		, m_selectFirst(0)
		, m_selectSecond(0)
		, m_image(0)
		, m_overlay(0)
		, m_tile(0)
		, m_imageUpdate(true)
		, m_textUpdate(true)
		, m_render(frame.widget().rootSheet().inkTarget().renderer())
#ifdef KIUI_DRAW_CACHE
		, m_imageCache(nullptr)
		, m_textCache(nullptr)
#endif
	{}

	Inkbox::~Inkbox()
	{
#ifdef KIUI_DRAW_CACHE
		if(m_imageCache)
			m_render.destroyCache(m_imageCache);
		if(m_textCache)
			m_render.destroyCache(m_textCache);
#endif
	}

	void Inkbox::show()
	{
		m_visible = true;
	}

	void Inkbox::hide()
	{
		m_visible = false;
	}

	void Inkbox::updateContent()
	{
		m_textUpdate = true;
		m_imageUpdate = true;
	}

	void Inkbox::updateStyle()
	{
		m_textUpdate = true;
		m_imageUpdate = true;

		if(skin().m_empty)
			return;

		m_image = m_frame.widget().image();
		m_overlay = skin().overlay();
		m_tile = skin().tile();

		if(!skin().imageSkin().null())
		{
			m_skin = skin().imageSkin().d_image;

			if(!skin().imageSkin().d_prepared)
				skin().imageSkin().prepare(m_skin->d_width, m_skin->d_height);
		}
	}

	void Inkbox::updateFrame()
	{
		if(m_frame.dirty() >= Frame::DIRTY_ABSOLUTE)
			m_moved = true;

		if(m_frame.dirty() < Frame::DIRTY_CLIP)
			return;

		m_textUpdate = true;
		m_imageUpdate = true;

		if(skin().m_empty || !m_visible || m_frame.dsize(DIM_X) == 0.f || m_frame.dsize(DIM_Y) == 0.f)
			return;

		if(!m_frame.widget().label().empty() && skin().textWrap())
		{
			BoxFloat paddedRect(this->pleft(), this->ptop(), this->pwidth(), this->pheight());
			m_render.breakText(m_frame.widget().label(), paddedRect, m_frame.inkstyle(), m_textRows);
		}
		else if(!m_frame.widget().label().empty())
		{
			m_textRows.resize(1);

			BoxFloat paddedRect(this->pleft(), this->ptop(), this->pwidth(), this->pheight());
			m_render.fillText(m_frame.widget().label(), paddedRect, m_frame.inkstyle(), m_textRows[0]);
		}
		else
		{
			m_textRows.clear();
		}
	}

	float Inkbox::contentSize(Dimension dim)
	{
		if(m_image)
		{
			return dim == DIM_X ? float(m_image->d_width) : float(m_image->d_height);
		}
		else if(skin().textColour().a() != 0.f)
		{
			return m_render.textSize(m_frame.widget().label(), dim, m_frame.inkstyle());
			//return m_textRows[0].rect[1 + dim];
		}
		else if(!skin().imageSkin().null())
		{
			if(dim == DIM_Y && skin().imageSkin().d_stretch == DIM_X)
				return float(skin().imageSkin().d_solidHeight);
			else if(dim == DIM_X && skin().imageSkin().d_stretch == DIM_Y)
				return float(skin().imageSkin().d_solidWidth);
		}

		return 0.f;
	}

	void Inkbox::drawImage()
	{
		m_frame.widget().customDraw();

		if(this->skin().m_empty || !m_visible)
			return;

		++sDebugBatch;

#ifdef KIUI_DRAW_CACHE
		if(!m_imageCache)
			m_render.createCache(m_imageCache, 11);

		if(m_imageUpdate)
			this->redrawImage();

		float x = floor(m_frame.dabsolute(DIM_X));
		float y = floor(m_frame.dabsolute(DIM_Y));

		m_render.drawCache(m_imageCache, x, y);

		m_imageUpdate = false;
#else
		this->redrawImage();
#endif
	}

	void Inkbox::drawText()
	{
		if(this->skin().m_empty || !m_visible)
			return;


#ifdef KIUI_DRAW_CACHE
		if(!m_textCache)
			m_render.createCache(m_textCache, 3);

		if(m_textUpdate)
			this->redrawText();

		float x = floor(m_frame.dabsolute(DIM_X));
		float y = floor(m_frame.dabsolute(DIM_Y));

		m_render.drawCache(m_textCache, x, y);

		m_textUpdate = false;
#else
		this->redrawText();
#endif
	}

	void Inkbox::redrawImage()
	{
#ifdef KIUI_DRAW_CACHE
		m_render.beginUpdate(m_imageCache);
#else
		float x = floor(m_frame.dabsolute(DIM_X));
		float y = floor(m_frame.dabsolute(DIM_Y));

		m_render.beginUpdate(x, y);
#endif

		InkStyle& skin = m_frame.inkstyle();
		ImageSkin& imageSkin = skin.imageSkin();

		BoxFloat rect(this->left(), this->top(), this->width(), this->height());
		BoxFloat clipRect(this->cleft(), this->ctop(), this->cwidth(), this->cheight());
		BoxFloat paddedRect(this->pleft(), this->ptop(), this->pwidth(), this->pheight());
		BoxFloat contentRect(this->contentLeft(), this->contentTop(), this->contentWidth(), this->contentHeight());
		BoxFloat& corners = skin.cornerRadius();
		float border = skin.borderWidth().x0();

		if(rect.w() - border <= 0.f || rect.h() - border <= 0.f)
		{
#ifdef KIUI_DRAW_CACHE
			m_render.endUpdate(m_imageCache);
#else
			m_render.endUpdate();
#endif
		}

		//if(m_frame.dclip(DIM_X) || m_frame.dclip(DIM_Y))
			m_render.clipRect(clipRect);

		// Shadow
		if(!skin.shadow().d_null)
		{
			m_render.drawShadow(rect, corners, skin.shadow());
		}

		// Rect
		if((skin.borderWidth().x0() || skin.backgroundColour().a() > 0.f) && skin.m_weakCorners)
		{
			BoxFloat clipRect(m_frame.parent()->dabsolute(DIM_X) - x, m_frame.parent()->dabsolute(DIM_Y) - y, m_frame.parent()->width(), m_frame.parent()->height());
			m_render.drawRectClipped(rect, corners, skin, clipRect, m_frame.parent()->inkstyle().cornerRadius());
		}
		else if((skin.borderWidth().x0() || skin.backgroundColour().a() > 0.f))
		{
			m_render.drawRect(rect, corners, skin);
		}

		// ImageSkin
		if(!skin.imageSkin().null())
		{
			BoxFloat skinRect;
			float margin = imageSkin.d_margin * 2.f;

			if(imageSkin.d_stretch == DIM_X)
				skinRect.assign(rect.x(), contentRect.y() + margin, rect.w() + margin, imageSkin.d_height);
			else if(imageSkin.d_stretch == DIM_Y)
				skinRect.assign(contentRect.x() + imageSkin.d_margin, rect.y(), imageSkin.d_width, rect.h() + margin);
			else
				skinRect.assign(rect.x(), rect.y(), rect.w() + margin, rect.h() + margin);

			imageSkin.stretchCoords(skinRect.x(), skinRect.y(), skinRect.w(), skinRect.h(), std::bind(&Inkbox::drawSkinImage, this, _1, _2, _3, _4, _5));
		}

		// Image
		if(m_image)
			m_render.drawImage(*m_image, contentRect);
		if(m_overlay)
			m_render.drawImage(*m_overlay, contentRect);
		if(m_tile)
			m_render.drawImage(*m_tile, rect);

		if(skin.m_weakCorners)
			m_render.unclipShape();

		//if(m_frame.dclip(DIM_X) || m_frame.dclip(DIM_Y))
			m_render.unclipRect();

#if 1 // DEBUG
			if(sDebugDraw && m_visible)
			{
				static InkStyle frameStyle("debugFrameStyle");
				static InkStyle paddingStyle("debugPaddingStyle");
				static InkStyle contentStyle("debugPaddingStyle");

				frameStyle.m_borderWidth = 1.f;
				paddingStyle.m_borderWidth = 1.f;
				contentStyle.m_borderWidth = 1.f;

				frameStyle.m_borderColour = Colour::Red;
				paddingStyle.m_borderColour = Colour::Green;
				contentStyle.m_borderColour = Colour::Blue;

				m_render.drawRect(rect, BoxFloat(), frameStyle);
				m_render.drawRect(paddedRect, BoxFloat(), paddingStyle);
				m_render.drawRect(contentRect, BoxFloat(), contentStyle);
			}
#endif

#ifdef KIUI_DRAW_CACHE
		m_render.endUpdate(m_imageCache);
#else
		m_render.endUpdate();
#endif
	}

	void Inkbox::drawSkinImage(ImageSkin::Section section, int left, int top, int width, int height)
	{
		left -= skin().imageSkin().d_margin;
		top -= skin().imageSkin().d_margin;

		float xratio = 1.f;
		float yratio = 1.f;

		if(section == ImageSkin::TOP || section == ImageSkin::BOTTOM || section == ImageSkin::FILL)
			xratio = float(width) / skin().imageSkin().d_fillWidth; //float(imgwidth);
		if(section == ImageSkin::LEFT || section == ImageSkin::RIGHT || section == ImageSkin::FILL)
			yratio = float(height) / skin().imageSkin().d_fillHeight; //float(imgheight);

		BoxFloat rect(left, top, width, height);
		m_render.drawImageStretch(skin().imageSkin().d_images[section], rect, xratio, yratio);
	}

	void Inkbox::redrawText()
	{
		static InkStyle textSelectionStyle("TextSelection");
		textSelectionStyle.m_backgroundColour = Colour(0/255.f, 55/255.f, 255/255.f, 124/255.f);

#ifdef KIUI_DRAW_CACHE
		m_render.beginUpdate(m_textCache);
#else
		float x = floor(m_frame.dabsolute(DIM_X));
		float y = floor(m_frame.dabsolute(DIM_Y));
		 
		m_render.beginUpdate(x, y);
#endif

		BoxFloat rect(this->cleft(), this->ctop(), this->cwidth(), this->cheight());
		BoxFloat paddedRect(this->pleft(), this->ptop(), this->pwidth(), this->pheight());

		// Caption
		if(!m_frame.widget().label().empty() && !(paddedRect.w() <= 0.f || paddedRect.h() <= 0.f))
		{
			m_render.clipRect(rect);

			for(TextRow& row : m_textRows)
			{
				if(!row.selected.null())
					m_render.drawRect(row.selected, BoxFloat(), textSelectionStyle);

				m_render.drawText(row.rect.x(), row.rect.y(), row.start, row.end, m_frame.inkstyle());
			}

			m_render.unclipRect();
		}

#ifdef KIUI_DRAW_CACHE
		m_render.endUpdate(m_textCache);
#else
		m_render.endUpdate();
#endif
	}

	void Inkbox::updateSelection()
	{
		const char* start = m_textRows[0].start;

		for(TextRow& row : m_textRows)
		{
			row.selected.clear();

			if(selectStart() != selectEnd())
			{
				size_t indexStart = row.start - start;
				size_t indexEnd = row.end - start - 1;

				if(indexEnd > selectStart() && indexStart < selectEnd())
				{
					size_t lineSelectStart = std::max(indexStart, selectStart());
					size_t lineSelectEnd = std::min(indexEnd, selectEnd());

					TextGlyph& startGlyph = row.glyphs[lineSelectStart - indexStart];
					TextGlyph& endGlyph = row.glyphs[lineSelectEnd - indexStart];

					row.selected.assign(startGlyph.rect.x(), row.rect.y(), endGlyph.rect.x() + endGlyph.rect.w() - startGlyph.rect.x(), row.rect.h());
				}
			}
		}
	}

	size_t Inkbox::caretIndex(float posX, float posY)
	{
		const string& text = m_frame.widget().label();

		const char* start = text.c_str();
		const char* end = start + text.size();

		for(TextRow& row : m_textRows)
			if(posY > row.rect.y() && posY < row.rect.y() + row.rect.h())
				for(TextGlyph& glyph : row.glyphs)
					if(posX > glyph.rect.x() && posX <= glyph.rect.x() + glyph.rect.w())
						return glyph.position - start;

		return end - start - 1;
	}

	void Inkbox::caretCoords(size_t index, float& caretX, float& caretY, float& caretHeight)
	{
		const string& text = m_frame.widget().label();

		const char* start = text.c_str();

		for(TextRow& row : m_textRows)
			if(index <= row.end - start)
				for(TextGlyph& glyph : row.glyphs)
					if(index == glyph.position - start)
					{
						caretX = glyph.rect.x();
						caretY = glyph.rect.y();
						return;
					}

		caretX = pleft();
		caretY = ptop();
		return;
	}
}
