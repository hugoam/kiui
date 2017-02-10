//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Frame/Frame.h>

#include <toyobj/String/String.h>
#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/Widget.h>

#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Style/Style.h>

#include <cmath>

namespace toy
{
	float AlignSpace[5] = { 0.f, 0.5f, 1.f, 0.f, 1.f };
	float AlignExtent[5] = { 0.f, 0.5f, 1.f, 1.f, 0.f };

	Frame::Frame(Widget& widget)
		: Uibox()
		, d_widget(&widget)
		, d_frame(*this)
		, d_parent(nullptr)
		, d_dirty(DIRTY_LAYOUT)
		, d_hidden(false)
		, d_index(0, 0)
		, d_style(nullptr)
	{
		this->setStyle(widget.style());
	}

	Frame::Frame(StyleType& style, Stripe& parent)
		: Uibox()
		, d_widget(nullptr)
		, d_frame(*this)
		, d_parent(nullptr)
		, d_dirty(DIRTY_LAYOUT)
		, d_hidden(false)
		, d_index(0, 0)
		, d_style(&style)
	{
		d_layout = &style.layout();
		parent.append(*this);
		this->bind(parent);
		this->setStyle(style);
	}

	Layer& Frame::layer()
	{
		if(this->frameType() < LAYER)
			return d_parent->layer();
		else
			return this->as<Layer>();	
	}

	void Frame::markDirty(Dirty dirty)
	{
		this->setDirty(dirty);
		Stripe* parent = this->parent();
		while(parent)
		{
			parent->setDirty(dirty);
			parent = parent->parent();
		}
	}

	void Frame::updateSpace()
	{
		if(!d_frame.empty())
			d_space = BLOCK;
		else if(frameType() == FRAME || !d_parent)
			d_space = BOARD;
		else if(!flow())
			d_space = BLOCK;
		else if(length() == d_parent->length() && length() == DIM_X) // @idea : make this distinction depend on a space Scarcity property (which by default would be Scarce for Y containers and Ample for X containers)
			d_space = SPACE;
		else if(length() != d_parent->length() && d_parent->length() == DIM_X)
			d_space = DIV;
		else
			d_space = DIV;
	}

	void Frame::updateSizing(Dimension dim)
	{
		if(d_layout->sizing()[dim])
			d_sizing[dim] = d_layout->sizing()[dim];
		else if(d_space == BLOCK)
			d_sizing[dim] = SHRINK;
		else if(d_space == BOARD)
			d_sizing[dim] = EXPAND;
		else if(d_space == FLEX)
			d_sizing[dim] = WRAP;
		else if(d_parent && ((d_space == SPACE && d_parent->length() == dim) || (d_space == DIV && d_parent->length() != dim)))
			d_sizing[dim] = WRAP;
		else if(d_parent && ((d_space == SPACE && d_parent->length() != dim) || (d_space == DIV && d_parent->length() == dim)))
			d_sizing[dim] = SHRINK;
	}

	void Frame::setStyle(Style& style)
	{
		d_style = &style;
		d_layout = &d_style->layout();

		d_opacity = d_layout->d_opacity;
		if(d_span.null())
			d_span = d_layout->d_span;

		d_length = d_layout->layoutDim();
		d_depth = d_layout->layoutDim() == DIM_X ? DIM_Y : DIM_X;

		if(d_widget)
			d_frame.resetInkstyle(d_style->subskin(d_widget->state()));
		else
			d_frame.resetInkstyle(d_style->skin());

		this->updateSizing();
	}

	void Frame::updateSizing()
	{
		if(d_layout->d_space != AUTO)
			d_space = d_layout->d_space;
		else
			this->updateSpace();

		this->updateSizing(DIM_X);
		this->updateSizing(DIM_Y);

		this->updateFixed(DIM_X);
		this->updateFixed(DIM_Y);
	}

	void Frame::updateFixed(Dimension dim)
	{
		if(!d_layout->size()[dim])
			return;

		d_sizing[dim] = FIXED;
		d_content[dim] = d_layout->size()[dim];
		if(d_layout->d_space != BOARD || d_size[dim] == 0.f)
			this->setSizeDim(dim, d_layout->size()[dim]);
	}

	void Frame::bind(Stripe& parent)
	{
		d_parent = &parent;
	}
	
	void Frame::unbind()
	{
		d_parent = nullptr;
	}

	void Frame::updateOnce()
	{
		if(d_dirty)
			this->layer().setRedraw();

		d_dirty = CLEAN;
	}

	void Frame::measure()
	{
		d_content[DIM_X] = d_frame.extentSize(DIM_X);
		d_content[DIM_Y] = d_frame.extentSize(DIM_Y);
	}
	
	void Frame::layout()
	{}

	void Frame::setSizeDim(Dimension dim, float size)
	{
		if(d_size[dim] == size)
			return;

		d_size[dim] = size;
		this->markDirty(DIRTY_LAYOUT);
	}

	void Frame::setSpanDim(Dimension dim, float span)
	{
		if(d_span[dim] == span)
			return;

		d_span[dim] = span;
		this->markDirty(DIRTY_LAYOUT);
	}

	void Frame::setPositionDim(Dimension dim, float position)
	{
		d_position[dim] = position;
		this->setDirty(DIRTY_ABSOLUTE);
	}

	void Frame::show()
	{
		d_hidden = false;
		this->markDirty(DIRTY_LAYOUT);
	}

	void Frame::hide()
	{
		d_hidden = true;
		this->markDirty(DIRTY_LAYOUT);
	}

	bool Frame::visible()
	{
		if(d_hidden)
			return false;
		else
			return d_parent ? d_parent->visible() : !d_hidden;
	}

	float Frame::dabsolute(Dimension dim)
	{
		if(d_parent && this->frameType() < MASTER_LAYER)
			return d_parent->dabsolute(dim) + d_parent->dpivotposition(*this, dim);
		else
			return dposition(dim);
	}

	float Frame::drelative(Dimension dim)
	{
		if(d_parent && !d_widget)
			return dposition(dim) + d_parent->drelative(dim);
		else
			return 0.f;
	}

	bool Frame::inside(float x, float y)
	{
		return (x >= 0.f && x <= width()
			 && y >= 0.f && y <= height());
	}

	Frame* Frame::pinpoint(float x, float y, bool opaque)
	{
		if((opaque && !this->opaque()) || !this->inside(x, y))
			return nullptr;
		else
			return this;
	}

	void Frame::debugPrintDepth()
	{
		Stripe* parent = this->parent();
		while(parent)
		{
			printf("  ");
			parent = parent->parent();
		}
	}
}
