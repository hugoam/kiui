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

namespace mk
{
	InkWindow::InkWindow(UiWindow& uiWindow, unique_ptr<Renderer> renderer)
		: m_uiWindow(uiWindow)
		, m_renderer(std::move(renderer))
	{
		DrawFrame::sRenderer = &*m_renderer;
	}

	void InkWindow::addImage(const string& image, int width, int height)
	{
		m_images.emplace_back(image, width, height);
	}

	Renderer* DrawFrame::sRenderer = nullptr;

	DrawFrame::DrawFrame(Frame& frame)
		: d_frame(frame)
		, d_stencil(frame)
		, d_caption(frame)
		, m_text()
		, m_image(nullptr)
		, d_inkstyle(nullptr)
	{}

	void DrawFrame::setText(const string& text)
	{
		m_text = text;
		this->updateSize();
	}

	void DrawFrame::setImage(Image* image)
	{
		m_image = image;
		this->updateSize();
	}

	void DrawFrame::updateSize()
	{
		if(!d_inkstyle)
			return;

		DimFloat contentSize;
		this->contentSize(DIM_X, contentSize);
		this->contentSize(DIM_Y, contentSize);

		contentSize[DIM_X] = contentSize[DIM_X] + d_inkstyle->padding().x0() + d_inkstyle->padding().x1();
		contentSize[DIM_Y] = contentSize[DIM_Y] + d_inkstyle->padding().y0() + d_inkstyle->padding().y1();

		bool wrapContent = (d_frame.frameType() == FRAME || d_frame.as<Stripe>().sequence().size() == 0);

		if(d_frame.dshrink(DIM_X) && wrapContent)
			d_frame.setSizeDim(DIM_X, contentSize[DIM_X]);
		if(d_frame.dshrink(DIM_Y) && wrapContent)
			d_frame.setSizeDim(DIM_Y, contentSize[DIM_Y]);
	}

	void DrawFrame::contentSize(Dimension dim, DimFloat& size)
	{
		if(!m_text.empty())
			size[dim] = sRenderer->textSize(m_text, dim, *d_inkstyle);
		else if(m_image)
			size[dim] = dim == DIM_X ? float(m_image->d_width) : float(m_image->d_height);
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

	void DrawFrame::beginDraw()
	{
		if(!d_frame.layer().redraw())
			return;

		if(!d_frame.visible())
			return;

		//Renderer& renderer = d_frame.layer().rootLayer().target()->renderer();
		Renderer& renderer = *sRenderer;

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

		float x = floor(d_frame.dposition(DIM_X));
		float y = floor(d_frame.dposition(DIM_Y));

#ifdef KIUI_DRAW_CACHE
		void* layerCache = nullptr;
		renderer.layerCache(d_frame.layer(), layerCache);

		if(d_frame.frameType() >= LAYER)
			renderer.beginLayer(layerCache);

		renderer.beginUpdate(layerCache, x, y);
#else
		renderer.beginUpdate(x, y);
#endif

		if(d_frame.frameType() >= LAYER)
			renderer.unclipRect();

		this->draw(d_stencil, renderer, rect, paddedRect, contentRect);
		this->draw(d_caption, renderer, rect, paddedRect, contentRect);

		d_frame.widget().customDraw(renderer);

		if(d_frame.clip())
			renderer.clipRect(rect);
	}

	void DrawFrame::draw(RenderFrame& frame, Renderer& target, BoxFloat& rect, BoxFloat& paddedRect, BoxFloat& contentRect)
	{
		// add clipping test > m_frame.clipped()
		if(d_frame.inkstyle().m_empty)
			return;

		frame.redraw(target, rect, paddedRect, contentRect);
	}

	void DrawFrame::endDraw()
	{
		if(!d_frame.layer().redraw())
			return;

		if(!d_frame.visible())
			return;

		//Renderer& renderer = d_frame.layer().rootLayer().target()->renderer();
		Renderer& renderer = *sRenderer;

		renderer.endUpdate();
	}

	void DrawFrame::updateInkstyle(InkStyle& inkstyle)
	{
		if(d_inkstyle == &inkstyle)
			return;

		d_inkstyle = &inkstyle;
		this->updateSize();

		d_frame.setDirty(Frame::DIRTY_SKIN); // only used to redraw ourselves

		//std::cerr << ">>>>>> SKIN " << d_inkstyle->name() << std::endl;
	}
}
