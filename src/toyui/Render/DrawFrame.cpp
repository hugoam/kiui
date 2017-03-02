//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Render/DrawFrame.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Layer.h>
#include <toyui/Widget/Widget.h>

#include <toyui/UiWindow.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Renderer* DrawFrame::sRenderer = nullptr;

	string DrawFrame::sDebugDrawFilter = "";
	bool DrawFrame::sDebugDrawFrameRect = false;
	bool DrawFrame::sDebugDrawPaddedRect = false;
	bool DrawFrame::sDebugDrawContentRect = false;
	bool DrawFrame::sDebugDrawClipRect = false;

	DrawFrame::DrawFrame(Frame& frame)
		: d_frame(&frame)
		, d_stencil(*this)
		, d_caption(*this)
		, m_text()
		, m_textLines(0)
		, m_image(nullptr)
		, d_inkstyle(nullptr)
	{}

	bool DrawFrame::empty()
	{
		return m_text.empty() && m_image == nullptr && d_inkstyle->image() == nullptr;
	}

	void DrawFrame::setText(const string& text)
	{
		m_text = text;
		this->updateFrameSize();
	}

	void DrawFrame::setImage(Image* image)
	{
		m_image = image;
		this->updateFrameSize();
	}

	void DrawFrame::setTextLines(size_t lines)
	{
		m_textLines = lines;
		this->updateFrameSize();
	}

	void DrawFrame::updateContentSize()
	{
		if(!d_inkstyle->textWrap())
			return;

		this->updateTextLineBreaks();
	}

	void DrawFrame::updateFrameSize()
	{
		if(!d_inkstyle)
			return;

		this->updateTextLineBreaks();
		d_frame->setDirty(Frame::DIRTY_CONTENT);
	}

	void DrawFrame::updateTextLineBreaks()
	{
		float paddedWidth = floor(d_frame->width() - d_inkstyle->padding().x0() - d_inkstyle->padding().x1());
		float paddedHeight = floor(d_frame->height() - d_inkstyle->padding().y0() - d_inkstyle->padding().y1());

		DimFloat paddedSize(paddedWidth, paddedHeight);

		d_caption.updateTextRows(*sRenderer, paddedSize);
	}

	float DrawFrame::extentSize(Dimension dim)
	{
		float content = this->contentSize(dim);
		if(content > 0.f)
			return content + d_inkstyle->padding()[dim] + d_inkstyle->padding()[dim + 2];
		else return 0.f;
	}

	float DrawFrame::contentSize(Dimension dim)
	{
		if(!m_text.empty())
			return d_caption.textSize(dim);
		else if(m_image)
			return dim == DIM_X ? float(m_image->d_width) : float(m_image->d_height);
		else if(m_textLines && dim == DIM_Y)
			return sRenderer->textLineHeight(*d_inkstyle) * m_textLines;
		else if(d_inkstyle->image())
			return dim == DIM_X ? float(d_inkstyle->image()->d_width) : float(d_inkstyle->image()->d_height);
		else if(!d_inkstyle->imageSkin().null())
		{
			Dimension stretchDim = d_inkstyle->imageSkin().d_stretch;

			if(dim == DIM_Y && stretchDim == DIM_X)
				return float(d_inkstyle->imageSkin().d_solidHeight);
			else if(dim == DIM_X && stretchDim == DIM_Y)
				return float(d_inkstyle->imageSkin().d_solidWidth);
		}

		return 0.f;
	}

	void DrawFrame::contentPos(const BoxFloat& paddedRect, const DimFloat& size, Dimension dim, DimFloat& pos)
	{
		pos[dim] = paddedRect[dim];
		if(d_inkstyle->align()[dim] == CENTER)
			pos[dim] = paddedRect[dim] + paddedRect[dim + 2] / 2.f - size[dim] / 2.f;
		else if(d_inkstyle->align()[dim] == RIGHT)
			pos[dim] = paddedRect[dim] + paddedRect[dim + 2] - size[dim];
	}

	void DrawFrame::beginDraw(Renderer& renderer, bool force)
	{
		float x = floor(d_frame->dposition(DIM_X));
		float y = floor(d_frame->dposition(DIM_Y));

		if(d_frame->frameType() > LAYER)
			renderer.beginTarget();

#ifdef TOYUI_DRAW_CACHE
		void* layerCache = nullptr;
		renderer.layerCache(d_frame->layer(), layerCache);

		if(d_frame->frameType() >= LAYER && (d_frame->layer().redraw() || force))
		{
			//d_frame->debugPrintDepth();
			//printf("Clearing Layer %s\n", d_frame->style().name().c_str());
			renderer.clearLayer(layerCache);
		}

		renderer.beginUpdate(layerCache, x, y, d_frame->scale());
#else
		renderer.beginUpdate(x, y);
#endif
	}

	void DrawFrame::draw(Renderer& renderer, bool force)
	{
#ifdef TOYUI_DRAW_CACHE
		if(!(d_frame->layer().redraw() || force))
			return;
#endif
		bool custom = d_frame->widget()->customDraw(renderer);
		if(custom)
			return;

		if(d_inkstyle->customRenderer() != nullptr)
		{
			CustomRenderer func = d_inkstyle->customRenderer();
			custom = func(*d_frame, renderer);
			if(custom)
				return;
		}

		float left = floor(d_inkstyle->margin().x0());
		float top = floor(d_inkstyle->margin().y0());
		float width = floor(d_frame->width() - d_inkstyle->margin().x0() - d_inkstyle->margin().x1());
		float height = floor(d_frame->height() - d_inkstyle->margin().y0() - d_inkstyle->margin().y1());

		BoxFloat rect(left, top, width, height);

#if 1 // DEBUG
		if(d_frame->style().name() == sDebugDrawFilter)
			renderer.debugRect(rect, Colour::Red);
#endif

		if(d_frame->clip())
			renderer.clipRect(rect);

		if(renderer.clipTest(rect))
			return;

		if(d_inkstyle->m_empty)
			return;

		float paddedLeft = floor(d_inkstyle->padding().x0());
		float paddedTop = floor(d_inkstyle->padding().y0());
		float paddedWidth = floor(d_frame->width() - d_inkstyle->padding().x0() - d_inkstyle->padding().x1());
		float paddedHeight = floor(d_frame->height() - d_inkstyle->padding().y0() - d_inkstyle->padding().y1());

		BoxFloat paddedRect(paddedLeft, paddedTop, paddedWidth, paddedHeight);

		DimFloat contentSize;
		contentSize[DIM_X] = this->contentSize(DIM_X);
		contentSize[DIM_Y] = this->contentSize(DIM_Y);

		DimFloat contentPos;
		this->contentPos(paddedRect, contentSize, DIM_X, contentPos);
		this->contentPos(paddedRect, contentSize, DIM_Y, contentPos);

		BoxFloat contentRect(contentPos.x(), contentPos.y(), contentSize.x(), contentSize.y());

		d_stencil.redraw(renderer, rect, paddedRect, contentRect);
		d_caption.redraw(renderer, rect, paddedRect, contentRect);

#if 1 // DEBUG
		if(d_frame->style().name() == sDebugDrawFilter)
			renderer.debugRect(rect, Colour::Red);
		if(sDebugDrawFrameRect)
			renderer.debugRect(rect, Colour::Red);
		if(sDebugDrawPaddedRect)
			renderer.debugRect(paddedRect, Colour::Green);
		if(sDebugDrawContentRect)
			renderer.debugRect(contentRect, Colour::Blue);
		if(sDebugDrawClipRect && d_frame->clip())
			renderer.debugRect(rect, Colour::Red);
#endif
	}

	void DrawFrame::endDraw(Renderer& renderer)
	{
		renderer.endUpdate();

		if(d_frame->frameType() >= LAYER)
			d_frame->layer().endRedraw();

		if(d_frame->frameType() > LAYER)
			renderer.endTarget();
	}

	void DrawFrame::resetInkstyle(InkStyle& inkstyle)
	{
		d_inkstyle = &inkstyle;
		this->updateFrameSize();
	}

	void DrawFrame::updateInkstyle(InkStyle& inkstyle)
	{
		if(d_inkstyle != &inkstyle)
			this->resetInkstyle(inkstyle);
	}
}
