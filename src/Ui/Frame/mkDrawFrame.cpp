//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkDrawFrame.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkLayer.h>
#include <Ui/Widget/mkWidget.h>

#include <Ui/mkUiWindow.h>
#include <Ui/Widget/mkRootSheet.h>

#include <iostream>

namespace mk
{
	Renderer* DrawFrame::sRenderer = nullptr;

	bool DrawFrame::sDebugDrawFrameRect = false;
	bool DrawFrame::sDebugDrawPaddedRect = false;
	bool DrawFrame::sDebugDrawContentRect = false;
	bool DrawFrame::sDebugDrawClipRect = false;

	DrawFrame::DrawFrame(Frame& frame)
		: d_frame(frame)
		, d_stencil(frame)
		, d_caption(frame)
		, m_text()
		, m_textLines(0)
		, m_image(nullptr)
		, d_inkstyle(nullptr)
	{}

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
		float paddedWidth = floor(d_frame.width() - d_inkstyle->padding().x0() - d_inkstyle->padding().x1());
		float paddedHeight = floor(d_frame.height() - d_inkstyle->padding().y0() - d_inkstyle->padding().y1());

		DimFloat paddedSize(paddedWidth, paddedHeight);

		d_caption.updateTextRows(*sRenderer, paddedSize);

		this->updateFrameSize(DIM_X);
		this->updateFrameSize(DIM_Y);
	}

	void DrawFrame::updateFrameSize()
	{
		if(!d_inkstyle)
			return;

		this->updateContentSize();

		this->updateFrameSize(DIM_X);
		this->updateFrameSize(DIM_Y);
	}

	void DrawFrame::updateFrameSize(Dimension dim)
	{
		bool wrapContent = (d_frame.frameType() == FRAME || d_frame.as<Stripe>().sequence().size() == 0);
		if(!(d_frame.dshrink(dim) && wrapContent))
			return;

		DimFloat contentSize;
		this->contentSize(dim, contentSize);

		d_frame.setSizeDim(dim, contentSize[dim] + d_inkstyle->padding()[dim] + d_inkstyle->padding()[dim + 2]);
	}

	void DrawFrame::contentSize(Dimension dim, DimFloat& size)
	{
		if(!m_text.empty())
			size[dim] = d_caption.textSize(dim);
		else if(m_image)
			size[dim] = dim == DIM_X ? float(m_image->d_width) : float(m_image->d_height);
		else if(m_textLines && dim == DIM_Y)
			size[dim] = sRenderer->textLineHeight(*d_inkstyle) * m_textLines;
		else if(d_inkstyle->image())
			size[dim] = dim == DIM_X ? float(d_inkstyle->image()->d_width) : float(d_inkstyle->image()->d_height);
		else if(!d_inkstyle->imageSkin().null())
		{
			Dimension stretchDim = d_inkstyle->imageSkin().d_stretch;

			if(dim == DIM_Y && stretchDim == DIM_X)
				size[dim] = float(d_inkstyle->imageSkin().d_solidHeight);
			else if(dim == DIM_X && stretchDim == DIM_Y)
				size[dim] = float(d_inkstyle->imageSkin().d_solidWidth);
		}
	}

	void DrawFrame::contentPos(const BoxFloat& paddedRect, const DimFloat& size, Dimension dim, DimFloat& pos)
	{
		pos[dim] = paddedRect[dim];
		if(d_inkstyle->align()[dim] == CENTER)
			pos[dim] = paddedRect[dim] + paddedRect[dim + 2] / 2.f - size[dim] / 2.f;
		else if(d_inkstyle->align()[dim] == RIGHT)
			pos[dim] = paddedRect[dim] + paddedRect[dim + 2] - size[dim];
	}

	void DrawFrame::beginDraw(Renderer& renderer)
	{
		float x = floor(d_frame.dposition(DIM_X));
		float y = floor(d_frame.dposition(DIM_Y));

#ifdef KIUI_DRAW_CACHE
		void* layerCache = nullptr;
		renderer.layerCache(d_frame.layer(), layerCache);

		if(d_frame.frameType() > LAYER)
			renderer.beginTarget();

		if(d_frame.frameType() >= LAYER)
			renderer.beginLayer(layerCache, x, y, d_frame.scale());
		else
			renderer.beginUpdate(layerCache, x, y, d_frame.scale());

#else
		renderer.beginUpdate(x, y);
#endif

		if(!d_frame.layer().redraw())
			return;

		d_frame.widget().customDraw(renderer);

		float left = floor(d_inkstyle->margin().x0());
		float top = floor(d_inkstyle->margin().y0());
		float width = floor(d_frame.width() - d_inkstyle->margin().x0() - d_inkstyle->margin().x1());
		float height = floor(d_frame.height() - d_inkstyle->margin().y0() - d_inkstyle->margin().y1());

		BoxFloat rect(left, top, width, height);

		float paddedLeft = floor(d_inkstyle->padding().x0());
		float paddedTop = floor(d_inkstyle->padding().y0());
		float paddedWidth = floor(d_frame.width() - d_inkstyle->padding().x0() - d_inkstyle->padding().x1());
		float paddedHeight = floor(d_frame.height() - d_inkstyle->padding().y0() - d_inkstyle->padding().y1());

		BoxFloat paddedRect(paddedLeft, paddedTop, paddedWidth, paddedHeight);

		DimFloat contentSize;
		this->contentSize(DIM_X, contentSize);
		this->contentSize(DIM_Y, contentSize);

		DimFloat contentPos;
		this->contentPos(paddedRect, contentSize, DIM_X, contentPos);
		this->contentPos(paddedRect, contentSize, DIM_Y, contentPos);

		BoxFloat contentRect(contentPos.x(), contentPos.y(), contentSize.x(), contentSize.y());

		if(d_frame.clip())
			renderer.clipRect(rect);

		if(d_frame.inkstyle().m_empty)
			return;

		// add clipping test > m_frame.clipped()

		d_stencil.redraw(renderer, rect, paddedRect, contentRect);
		d_caption.redraw(renderer, rect, paddedRect, contentRect);

#if 1 // DEBUG
		if(sDebugDrawFrameRect)
			renderer.debugRect(rect, Colour::Red);
		if(sDebugDrawPaddedRect)
			renderer.debugRect(paddedRect, Colour::Green);
		if(sDebugDrawContentRect)
			renderer.debugRect(contentRect, Colour::Blue);
		if(sDebugDrawClipRect && d_frame.clip())
			renderer.debugRect(rect, Colour::Red);
#endif
	}

	void DrawFrame::endDraw(Renderer& renderer)
	{
		renderer.endUpdate();

		if(d_frame.frameType() > LAYER)
			renderer.endTarget();
	}

	void DrawFrame::resetInkstyle(InkStyle& inkstyle)
	{
		d_inkstyle = &inkstyle;
		this->updateFrameSize();

		d_frame.setDirty(Frame::DIRTY_SKIN); // only used to redraw ourselves
		//std::cerr << ">>>>>> SKIN " << d_inkstyle->name() << std::endl;
	}

	void DrawFrame::updateInkstyle(InkStyle& inkstyle)
	{
		if(d_inkstyle != &inkstyle)
			this->resetInkstyle(inkstyle);
	}
}
