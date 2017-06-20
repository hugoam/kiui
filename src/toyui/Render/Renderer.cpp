//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/Renderer.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>

#include <toyui/UiWindow.h>

namespace toy
{
	RenderTarget::RenderTarget(Renderer& renderer, MasterLayer& masterLayer, bool gammaCorrected)
		: m_renderer(renderer)
		, m_masterLayer(masterLayer)
		, m_gammaCorrected(gammaCorrected)
	{}

	void RenderTarget::render()
	{
		m_renderer.render(*this);
	}



	Renderer::Renderer(const string& resourcePath)
		: m_resourcePath(resourcePath)
		, m_debugBatch(0)
		, m_debugDepth(0)
		, m_debugPrintFilter("")
		, m_debugPrint(true)
		, m_debugDrawFilter("")
		, m_debugDrawFrameRect(false)
		, m_debugDrawPaddedRect(false)
		, m_debugDrawContentRect(false)
		, m_debugDrawClipRect(false)
	{
		DrawFrame::s_renderer = this;
	}

	void Renderer::render(RenderTarget& target)
	{
		this->logFPS();

		m_debugBatch = 0;
		m_debugDepth = 0;
		static int prevBatch = 0;

		this->beginFrame(target);

		this->render(target.layer().widget()->as<Wedge>(), false);

#ifdef TOYUI_DRAW_CACHE
		void* layerCache = nullptr;
		this->layerCache(target.layer(), layerCache);
		this->drawLayer(layerCache, 0.f, 0.f, 1.f);

		for(Layer* layer : target.layer().layers())
			if(layer->visible())
			{
				this->layerCache(*layer, layerCache);
				this->drawLayer(layerCache, 0.f, 0.f, 1.f);
			}
#endif

		if(m_debugBatch > 1 && m_debugBatch != prevBatch)
		{
			prevBatch = m_debugBatch;
			//printf("DEBUG: Render Frame : %i frames redrawn\n", m_debugBatch);
		}

		this->endFrame();
	}

	void Renderer::render(Widget& widget, bool force)
	{
		this->beginDraw(widget.frame(), force);
		this->draw(widget.frame(), force);
		this->endDraw(widget.frame());
	}

	void Renderer::render(Wedge& wedge, bool force)
	{
		if(wedge.frame().layer().forceRedraw())
			force = true;

		this->beginDraw(wedge.frame(), force);
		this->draw(wedge.frame(), force);

		for(size_t i = 0; i < wedge.contents().size(); ++i)
			if(!wedge.contents()[i]->frame().hidden())
				if(wedge.contents()[i]->isa<Wedge>())
					this->render(wedge.contents()[i]->as<Wedge>(), force);
				else
					this->render(*wedge.contents()[i], force);


		this->endDraw(wedge.frame());
	}

	void Renderer::beginDraw(Frame& frame, bool force)
	{
		float x = floor(frame.dposition(DIM_X));
		float y = floor(frame.dposition(DIM_Y));

		if(frame.frameType() > LAYER)
			this->beginTarget();

#ifdef TOYUI_DRAW_CACHE
		void* layerCache = nullptr;
		this->layerCache(frame.layer(), layerCache);

		if(frame.frameType() >= LAYER && (frame.layer().redraw() || force))
			this->clearLayer(layerCache);

		this->beginUpdate(layerCache, x, y, frame.scale());
#else
		this->beginUpdate(x, y);
#endif
	}

	void Renderer::draw(Frame& frame, bool force)
	{
		InkStyle& inkstyle = frame.content().inkstyle();

		float left = floor(inkstyle.margin().x0());
		float top = floor(inkstyle.margin().y0());
		float width = floor(frame.width() - inkstyle.margin().x0() - inkstyle.margin().x1());
		float height = floor(frame.height() - inkstyle.margin().y0() - inkstyle.margin().y1());

		BoxFloat rect(left, top, width, height);

		if(frame.clip())
			this->clipRect(rect);

#ifdef TOYUI_DRAW_CACHE
		if(!(frame.layer().redraw() || force))
			return;
#endif

		if(inkstyle.m_empty || this->clipTest(rect))
			return;

		bool custom = frame.widget()->customDraw(*this);
		if(custom)
			return;

		if(inkstyle.customRenderer() != nullptr)
		{
			CustomRenderer func = inkstyle.customRenderer();
			custom = func(frame, *this);
			if(custom)
				return;
		}

#if 1 // DEBUG
		if(frame.style().name() == m_debugDrawFilter)
			this->debugRect(rect, Colour::Red);
#endif

		float paddedLeft = floor(inkstyle.padding().x0());
		float paddedTop = floor(inkstyle.padding().y0());
		float paddedWidth = floor(frame.width() - inkstyle.padding().x0() - inkstyle.padding().x1());
		float paddedHeight = floor(frame.height() - inkstyle.padding().y0() - inkstyle.padding().y1());

		BoxFloat paddedRect(paddedLeft, paddedTop, paddedWidth, paddedHeight);

		DimFloat contentSize;
		contentSize[DIM_X] = frame.content().contentSize(DIM_X);
		contentSize[DIM_Y] = frame.content().contentSize(DIM_Y);

		DimFloat contentPos;
		frame.content().contentPos(paddedRect, contentSize, DIM_X, contentPos);
		frame.content().contentPos(paddedRect, contentSize, DIM_Y, contentPos);

		BoxFloat contentRect(contentPos.x(), contentPos.y(), contentSize.x(), contentSize.y());

		this->drawStencil(frame, frame.content().stencil(), rect, paddedRect, contentRect);
		this->drawCaption(frame, frame.content().caption(), rect, paddedRect, contentRect);

#if 1 // DEBUG
		if(frame.style().name() == m_debugDrawFilter)
			this->debugRect(rect, Colour::Red);
		if(m_debugDrawFrameRect)
			this->debugRect(rect, Colour::Red);
		if(m_debugDrawPaddedRect)
			this->debugRect(paddedRect, Colour::Green);
		if(m_debugDrawContentRect)
			this->debugRect(contentRect, Colour::Blue);
		if(m_debugDrawClipRect && frame.clip())
			this->debugRect(rect, Colour::Red);
#endif
	}

	void Renderer::endDraw(Frame& frame)
	{
		this->endUpdate();

		if(frame.frameType() >= LAYER)
			frame.layer().endRedraw();

		if(frame.frameType() > LAYER)
			this->endTarget();
	}

	void Renderer::drawStencil(Frame& frame, Stencil& stencil, const BoxFloat& rect, const BoxFloat& paddedRect, const BoxFloat& contentRect)
	{
		UNUSED(paddedRect);

		if(!frame.hardClip().null())
			return;

		m_debugBatch++;

		InkStyle& skin = frame.content().inkstyle();

		// Shadow
		if(!skin.shadow().d_null)
		{
			this->drawShadow(rect, skin.cornerRadius(), skin.shadow());
		}

		// Rect
		if((skin.borderWidth().x0() || skin.backgroundColour().a() > 0.f))
		{
			BoxFloat cornerRadius = skin.m_weakCorners ? stencil.selectCorners() : skin.cornerRadius();
			this->drawRect(rect, cornerRadius, skin);
		}

		// ImageSkin
		ImageSkin& imageSkin = skin.imageSkin();
		if(!imageSkin.null())
		{
			BoxFloat skinRect;
			float margin = imageSkin.d_margin * 2.f;

			if(imageSkin.d_stretch == DIM_X)
				skinRect.assign(rect.x(), contentRect.y() + margin, rect.w() + margin, imageSkin.d_height);
			else if(imageSkin.d_stretch == DIM_Y)
				skinRect.assign(contentRect.x() + imageSkin.d_margin, rect.y(), imageSkin.d_width, rect.h() + margin);
			else
				skinRect.assign(rect.x(), rect.y(), rect.w() + margin, rect.h() + margin);

			auto func = [this, &frame](ImageSkin::Section section, const BoxFloat& rect) { this->drawSkinImage(frame, section, rect); };
			imageSkin.stretchCoords(skinRect.x(), skinRect.y(), skinRect.w(), skinRect.h(), func);
		}

		// Image
		if(skin.image())
			this->drawImage(*skin.image(), contentRect);
		if(skin.overlay())
			this->drawImage(*skin.overlay(), contentRect);
		if(skin.tile())
			this->drawImage(*skin.tile(), rect);
	}

	void Renderer::drawSkinImage(Frame& frame, ImageSkin::Section section, BoxFloat rect)
	{
		ImageSkin& imageSkin = frame.content().inkstyle().imageSkin();
		rect.setX(rect.x() - imageSkin.d_margin);
		rect.setY(rect.y() - imageSkin.d_margin);

		float xratio = 1.f;
		float yratio = 1.f;

		if(section == ImageSkin::TOP || section == ImageSkin::BOTTOM || section == ImageSkin::FILL)
			xratio = rect.w() / imageSkin.d_fillWidth;
		if(section == ImageSkin::LEFT || section == ImageSkin::RIGHT || section == ImageSkin::FILL)
			yratio = rect.h() / imageSkin.d_fillHeight;

		this->drawImageStretch(imageSkin.d_images[section], rect, xratio, yratio);
	}

	void Renderer::drawCaption(Frame& frame, Caption& caption, const BoxFloat& rect, const BoxFloat& paddedRect, const BoxFloat& contentRect)
	{
		static InkStyle textSelectionStyle;
		textSelectionStyle.m_backgroundColour = Colour(0 / 255.f, 55 / 255.f, 255 / 255.f, 124 / 255.f);

		static InkStyle caretStyle;
		caretStyle.m_backgroundColour = Colour::White;

		if(paddedRect.w() <= 0.f || paddedRect.h() <= 0.f)
			return;

		if(!frame.content().image() && frame.content().text().empty())
			return;

		this->clipRect(rect);

		if(frame.content().image())
			this->drawImage(*frame.content().image(), contentRect);

		if(!frame.content().text().empty())
			for(TextRow& row : caption.textRows())
			{
				if(!row.selected.null())
					this->drawRect(BoxFloat(paddedRect.x() + row.selected.x(), paddedRect.y() + row.selected.y(), row.selected.w(), row.selected.h()), BoxFloat(), textSelectionStyle);

				this->drawText(paddedRect.x() + row.rect.x(), paddedRect.y() + row.rect.y(), row.start, row.end, frame.content().inkstyle());

				if(!row.caret.null())
					this->drawRect(BoxFloat(paddedRect.x() + row.caret.x(), paddedRect.y() + row.caret.y(), row.caret.w(), row.caret.h()), BoxFloat(), caretStyle);
			}
	}

	void Renderer::logFPS()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = m_clock.read();
		double delta = time - prevtime;
		if(time - prevtime >= 4.f)
		{
			printf("INFO: fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		++frames;
	}
}
