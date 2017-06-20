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
	Renderer* DrawFrame::s_renderer = nullptr;

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

		d_caption.updateTextRows(*s_renderer, paddedSize);
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
			return s_renderer->textLineHeight(*d_inkstyle) * m_textLines;
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
