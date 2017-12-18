//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/Renderer.h>

#include <toyui/Frame/Layer.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	RenderTarget::RenderTarget(Renderer& renderer, Layer& layer, bool gammaCorrected)
		: m_renderer(renderer)
		, m_layer(layer)
		, m_gammaCorrected(gammaCorrected)
	{}

	void RenderTarget::render()
	{
		m_renderer.render(*this);
	}

	Renderer::Renderer(const string& resourcePath)
		: m_resourcePath(resourcePath)
		, m_null(false)
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
		Caption::s_renderer = this;
	}

	void Renderer::render(RenderTarget& target)
	{
		this->logFPS();

		m_debugBatch = 0;
		m_debugDepth = 0;
		static int prevBatch = 0;

		this->beginFrame(target);

		this->render(*target.m_layer.d_wedge, target.m_layer, false);

#ifdef TOYUI_DRAW_CACHE
		target.m_layer.visit([this](Layer& layer) {
			if(layer.visible())
			{
				void* layerCache = nullptr;
				this->layerCache(layer, layerCache);
				this->drawLayer(layerCache, 0.f, 0.f, 1.f);
			}
		});
#endif

		if(m_debugBatch > 1 /*&& m_debugBatch != prevBatch*/)
		{
			prevBatch = m_debugBatch;
			//printf("DEBUG: Render Frame : %i frames redrawn\n", m_debugBatch);
		}

		this->endFrame();
	}

	void Renderer::render(Widget& widget, Layer& layer, bool force)
	{
		this->beginDraw(layer, widget.frame(), force);
		this->draw(layer, widget.frame(), force);
		this->endDraw(layer, widget.frame());
	}

	void Renderer::render(Wedge& wedge, Layer& toplayer, bool force)
	{
		Layer& layer = wedge.frame().frameType() == LAYER ? as<Layer>(wedge.frame()) : toplayer;

		if(layer.forceRedraw())
			force = true;

		this->beginDraw(layer, wedge.frame(), force);
		this->draw(layer, wedge.frame(), force);

		for(size_t i = 0; i < wedge.m_contents.size(); ++i)
			if(!wedge.m_contents[i]->frame().d_hidden)
			{
				if(is<Wedge>(*wedge.m_contents[i]))
					this->render(as<Wedge>(*wedge.m_contents[i]), layer, force);
				else
					this->render(*wedge.m_contents[i], layer, force);
			}

		this->endDraw(layer, wedge.frame());
	}

	void Renderer::beginDraw(Layer& layer, Frame& frame, bool force)
	{
		float x = floor(frame.d_position.x);
		float y = floor(frame.d_position.y);

		if(frame.frameType() > LAYER)
			this->beginTarget();

#ifdef TOYUI_DRAW_CACHE
		void* layerCache = nullptr;
		this->layerCache(layer, layerCache);

		if(&frame == &layer && (layer.redraw() || force))
			this->clearLayer(layerCache);

		this->beginUpdate(layerCache, x, y, frame.d_scale);
#else
		this->beginUpdate(x, y);
#endif
	}

	void Renderer::draw(Layer& layer, Frame& frame, bool force)
	{
		InkStyle& inkstyle = *frame.d_inkstyle;

		float left = floor(inkstyle.m_margin.x0);
		float top = floor(inkstyle.m_margin.y0);
		float width = floor(frame.m_size.x - inkstyle.m_margin.x0 - inkstyle.m_margin.x1);
		float height = floor(frame.m_size.y - inkstyle.m_margin.y0 - inkstyle.m_margin.y1);

		BoxFloat rect(left, top, width, height);

		if(frame.clip())
			this->clipRect(rect);

#ifdef TOYUI_DRAW_CACHE
		if(!(layer.redraw() || force))
			return;
#endif

		if(inkstyle.m_empty || this->clipTest(rect))
			return;

		bool custom = frame.d_widget.customDraw(*this);

		if(inkstyle.m_customRenderer != nullptr)
			custom = inkstyle.m_customRenderer(frame, *this);

		if(custom)
			return;

		//printf("DEBUG: Render Frame : %s\n", frame.style().m_name.c_str());

		float paddedLeft = floor(inkstyle.m_padding.x0);
		float paddedTop = floor(inkstyle.m_padding.y0);
		float paddedWidth = floor(frame.m_size.x - inkstyle.m_padding.x0 - inkstyle.m_padding.x1);
		float paddedHeight = floor(frame.m_size.y - inkstyle.m_padding.y0 - inkstyle.m_padding.y1);

		BoxFloat paddedRect(paddedLeft, paddedTop, paddedWidth, paddedHeight);

		DimFloat contentSize = frame.contentSize();

		DimFloat contentPos;
		this->contentPos(frame, paddedRect, contentSize, DIM_X, contentPos);
		this->contentPos(frame, paddedRect, contentSize, DIM_Y, contentPos);

		BoxFloat contentRect(contentPos.x, contentPos.y, contentSize.x, contentSize.y);
		
#if 1 // DEBUG
		if(frame.d_style->m_name == m_debugDrawFilter)
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

		this->drawBackground(frame, rect, paddedRect, contentRect);
		this->drawContent(frame, rect, paddedRect, contentRect);
	}

	void Renderer::endDraw(Layer& layer, Frame& frame)
	{
		this->endUpdate();

		if(frame.frameType() >= LAYER)
			layer.endRedraw();

		if(frame.frameType() > LAYER)
			this->endTarget();
	}

	void Renderer::contentPos(Frame& frame, const BoxFloat& paddedRect, const DimFloat& size, Dimension dim, DimFloat& pos)
	{
		pos[dim] = paddedRect[dim];
		if(frame.d_inkstyle->m_align[dim] == CENTER)
			pos[dim] = paddedRect[dim] + paddedRect[dim + 2] / 2.f - size[dim] / 2.f;
		else if(frame.d_inkstyle->m_align[dim] == RIGHT)
			pos[dim] = paddedRect[dim] + paddedRect[dim + 2] - size[dim];
	}

	BoxFloat Renderer::selectCorners(Frame& frame)
	{
		Frame& parent = *frame.d_parent;

		const BoxFloat& corners = parent.d_inkstyle->m_corner_radius;
		if(parent.first(frame))
			return parent.d_length == DIM_X ? BoxFloat(corners[0], 0.f, 0.f, corners[3]) : BoxFloat(corners[0], corners[1], 0.f, 0.f);
		else if(parent.last(frame))
			return parent.d_length == DIM_X ? BoxFloat(0.f, corners[1], corners[2], 0.f) : BoxFloat(0.f, 0.f, corners[2], corners[3]);
		else
			return BoxFloat();
	}

	void Renderer::drawBackground(Frame& frame, const BoxFloat& rect, const BoxFloat& paddedRect, const BoxFloat& contentRect)
	{
		if(!frame.d_hardClip.null())
			return;

		m_debugBatch++;

		InkStyle& inkstyle = *frame.d_inkstyle;

		// Shadow
		if(!inkstyle.m_shadow.d_null)
		{
			this->drawShadow(rect, inkstyle.m_corner_radius, inkstyle.m_shadow);
		}

		// Rect
		if(inkstyle.m_border_width.x0 || !inkstyle.m_background_colour.null())
		{
			BoxFloat cornerRadius = inkstyle.m_weak_corners ? this->selectCorners(frame) : inkstyle.m_corner_radius;
			this->drawRect(rect, cornerRadius, inkstyle);
		}

		// ImageSkin
		ImageSkin& imageSkin = inkstyle.m_image_skin;
		if(!imageSkin.null())
		{
			BoxFloat skinRect;
			float margin = imageSkin.m_margin * 2.f;

			if(imageSkin.d_stretch == DIM_X)
				skinRect.assign(rect.x, contentRect.y + margin, rect.w + margin, imageSkin.d_height);
			else if(imageSkin.d_stretch == DIM_Y)
				skinRect.assign(contentRect.x + imageSkin.m_margin, rect.y, imageSkin.d_width, rect.h + margin);
			else
				skinRect.assign(rect.x, rect.y, rect.w + margin, rect.h + margin);

			auto func = [this, &frame](ImageSkin::Section section, const BoxFloat& rect) { this->drawSkinImage(frame, section, rect); };
			imageSkin.stretchCoords(skinRect.x, skinRect.y, skinRect.w, skinRect.h, func);
		}

		// Image
		if(inkstyle.m_overlay)
			this->drawImage(*inkstyle.m_overlay, paddedRect);
		if(inkstyle.m_tile)
			this->drawImage(*inkstyle.m_tile, rect);
	}

	void Renderer::drawSkinImage(Frame& frame, ImageSkin::Section section, BoxFloat rect)
	{
		ImageSkin& imageSkin = frame.d_inkstyle->m_image_skin;
		rect.x = rect.x - imageSkin.m_margin;
		rect.y = rect.y - imageSkin.m_margin;

		float xratio = 1.f;
		float yratio = 1.f;

		if(section == ImageSkin::TOP || section == ImageSkin::BOTTOM || section == ImageSkin::FILL)
			xratio = rect.w / imageSkin.d_fillWidth;
		if(section == ImageSkin::LEFT || section == ImageSkin::RIGHT || section == ImageSkin::FILL)
			yratio = rect.h / imageSkin.d_fillHeight;

		this->drawImageStretch(imageSkin.d_images[section], rect, xratio, yratio);
	}

	void Renderer::drawContent(Frame& frame, const BoxFloat& rect, const BoxFloat& paddedRect, const BoxFloat& contentRect)
	{
		static InkStyle textSelectionStyle;
		textSelectionStyle.m_background_colour = Colour(0 / 255.f, 55 / 255.f, 255 / 255.f, 124 / 255.f);

		static InkStyle caretStyle;
		caretStyle.m_background_colour = Colour::White;

		if(frame.empty() || paddedRect.w <= 0.f || paddedRect.h <= 0.f)
			return;

		//this->clipRect(rect);

		if(frame.d_icon)
			this->drawImage(*frame.d_icon->m_image, contentRect);

		if(frame.d_caption)
			for(TextRow& row : frame.d_caption->m_textRows)
			{
				if(!row.selected.null())
					this->drawRect(BoxFloat(paddedRect.x + row.selected.x, paddedRect.y + row.selected.y, row.selected.w, row.selected.h), BoxFloat(), textSelectionStyle);

				this->drawText(paddedRect.x + row.rect.x, paddedRect.y + row.rect.y, row.start, row.end, *frame.d_inkstyle);

				if(!row.caret.null())
					this->drawRect(BoxFloat(paddedRect.x + row.caret.x, paddedRect.y + row.caret.y, row.caret.w, row.caret.h), BoxFloat(), caretStyle);
			}
	}

	void Renderer::logFPS()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = m_clock.read();
		if(time - prevtime >= 4.f)
		{
			printf("INFO: fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		++frames;
	}
}
