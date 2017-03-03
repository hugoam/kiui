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
		, d_dirty(DIRTY_MAPPING)
		, d_hidden(false)
		, d_index(0, 0)
	{}

	Frame::Frame(Style& style, Stripe& parent)
		: Uibox()
		, d_widget(nullptr)
		, d_frame(*this)
		, d_parent(nullptr)
		, d_dirty(DIRTY_MAPPING)
		, d_hidden(false)
		, d_index(0, 0)
	{
		this->setStyle(style);
		parent.append(*this);
		this->bind(parent);
	}

	Layer& Frame::layer()
	{
		if(this->frameType() < LAYER)
			return d_parent->layer();
		else
			return this->as<Layer>();
	}

	MasterLayer& Frame::masterlayer()
	{
		if(this->frameType() < MASTER_LAYER)
			return d_parent->masterlayer();
		else
			return this->as<MasterLayer>();
	}

	void Frame::visit(Stripe& root, const Visitor& visitor)
	{
		visitor(*this);
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

	void Frame::setStyle(Style& style, bool reset)
	{
		d_style = &style;
		reset ? this->resetStyle() : this->updateStyle();
	}

	void Frame::updateStyle()
	{
		d_styleStamp = d_style->updated();

		if(d_widget)
			d_frame.resetInkstyle(d_style->subskin(d_widget->state()));
		else
			d_frame.resetInkstyle(d_style->skin());

		if(d_parent)
			this->updateLayout();
	}

	void Frame::resetStyle()
	{
		this->updateStyle();
		this->markDirty(DIRTY_MAPPING);
	}

	void Frame::updateLayout()
	{
		Space space = d_style->layout().space();

		if(space == MANUAL_SPACE)
			this->applySpace(PARAGRAPH, MANUAL, MANUAL);
		else if(space == SHEET)
			this->applySpace(PARAGRAPH, WRAP, WRAP);
		else if(space == ITEM)
			this->applySpace(READING, SHRINK, SHRINK);
		else if(space == BLOCK)
			this->applySpace(PARAGRAPH, SHRINK, SHRINK);
		else if(space == FIXED_BLOCK)
			this->applySpace(PARAGRAPH, FIXED, FIXED);
		else if(space == LINE)
			this->applySpace(READING, WRAP, SHRINK);
		else if(space == STACK)
			this->applySpace(PARAGRAPH, SHRINK, WRAP);
		else if(space == DIV)
			this->applySpace(ORTHOGONAL, WRAP, SHRINK);
		else if(space == SPACE)
			this->applySpace(PARALLEL, WRAP, SHRINK);
		else if(space == BOARD)
			this->applySpace(PARAGRAPH, EXPAND, EXPAND);
		else if(space == PARALLEL_FLEX)
			this->applySpace(PARALLEL, WRAP, WRAP);

		this->updateFixed(DIM_X);
		this->updateFixed(DIM_Y);
	}

	void Frame::applySpace(Direction direction, Sizing length, Sizing depth)
	{
		if(d_style->layout().direction() < DIRECTION_AUTO)
			direction = d_style->layout().direction();

		if(direction == ORTHOGONAL)
			d_length = this->orthogonal(d_parent->length());
		else if(direction == PARALLEL)
			d_length = this->parallel(d_parent->length());
		else if(direction == READING)
			d_length = DIM_X;
		else if(direction == PARAGRAPH)
			d_length = DIM_Y;

		d_depth = this->orthogonal(d_length);

		d_sizing[d_length] = length;
		d_sizing[d_depth] = depth;
	}

	void Frame::updateFixed(Dimension dim)
	{
		if(d_style->layout().size()[dim])
			this->setFixedSize(dim, d_style->layout().size()[dim]);
	}

	void Frame::setFixedSize(Dimension dim, float size)
	{
		d_sizing[dim] = FIXED;
		d_content[dim] = size;
		if(d_style->layout().d_space != BOARD || d_size[dim] == 0.f)
			this->setSizeDim(dim, size);
	}

	void Frame::bind(Stripe& parent)
	{
		d_parent = &parent;
		this->updateLayout();
	}
	
	void Frame::unbind()
	{
		d_parent = nullptr;
	}

	void Frame::remap()
	{}

	void Frame::measureLayout()
	{
		d_content[DIM_X] = d_frame.extentSize(DIM_X);
		d_content[DIM_Y] = d_frame.extentSize(DIM_Y);
	}
	
	void Frame::resizeLayout()
	{}

	void Frame::positionLayout()
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
		//this->markDirty(DIRTY_LAYOUT);
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

	void Frame::integratePosition(Frame& root, DimFloat& global)
	{
		if(this == &root)
			return;
		
		d_parent->integratePosition(root, global);
		global[DIM_X] = (global[DIM_X] - d_position[DIM_X]) / d_scale;
		global[DIM_Y] = (global[DIM_Y] - d_position[DIM_Y]) / d_scale;
	}

	void Frame::derivePosition(Frame& root, DimFloat& local)
	{
		if(this == &root)
			return;

		local[DIM_X] = d_position[DIM_X] + local[DIM_X] * d_scale;
		local[DIM_Y] = d_position[DIM_Y] + local[DIM_Y] * d_scale;
		d_parent->derivePosition(root, local);
	}

	float Frame::deriveScale(Frame& root)
	{
		if(this == &root)
			return d_scale;
		else 
			return d_parent->deriveScale(root) * d_scale;
	}

	DimFloat Frame::relativePosition(Frame& root)
	{
		DimFloat pos;
		this->derivePosition(root, pos);
		return pos;
	}

	DimFloat Frame::absolutePosition()
	{
		return this->relativePosition(this->masterlayer());
	}

	float Frame::absoluteScale()
	{
		return this->deriveScale(this->masterlayer());
	}

	DimFloat Frame::localPosition(float x, float y)
	{
		DimFloat local(x, y);
		this->integratePosition(this->masterlayer(), local);
		return local;
	}

	float Frame::doffset(Dimension dim)
	{
		if(d_parent && !d_widget)
			return dposition(dim) + d_parent->doffset(dim);
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
