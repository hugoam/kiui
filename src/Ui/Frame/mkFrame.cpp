//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkFrame.h>

#include <Object/String/mkString.h>
#include <Object/Iterable/mkReverse.h>

#include <Ui/Widget/mkWidget.h>

#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Style/mkStyle.h>

#include <cmath>
#include <iostream>

namespace mk
{
	float AlignSpace[5] = { 0.f, 0.5f, 1.f, 0.f, 1.f };
	float AlignExtent[5] = { 0.f, 0.5f, 1.f, 1.f, 0.f };

	Frame::Frame(Widget& widget)
		: Uibox()
		, DrawFrame(*this)
		, d_widget(widget)
		, d_parent(nullptr)
		, d_dirty(DIRTY_VISIBILITY)
		, d_hidden(false)
		, d_index(0)
		, d_style(nullptr)
		, d_styleStamp(0)
	{}

	Frame::~Frame()
	{}

	Layer& Frame::layer()
	{
		if(this->frameType() < LAYER)
			return d_parent->layer();
		else
			return this->as<Layer>();	
	}

	void Frame::resetStyle()
	{
		if(!d_parent)
		{
			//this->updateStyle();
			return;
		}

		Stripe* parent = d_parent;
		bool flow = d_flow;

		d_parent->remove(*this);
		parent->insert(*this, d_index);

		if(flow && !this->flow())
		{
			d_position[0] = 0.f;
			d_position[1] = 0.f;
		}
	}

	void Frame::updateSizing(Dimension dim)
	{
		if(d_layout->sizing()[dim])
			d_sizing[dim] = d_layout->sizing()[dim];
		else if(d_space == BLOCK)
			d_sizing[dim] = SHRINK;
		else if(d_space == FIT)
			d_sizing[dim] = d_parent->d_sizing[dim] == FIXED ? EXPAND : d_parent->d_sizing[dim];
		else if(d_space == BOARD)
			d_sizing[dim] = EXPAND;
		else if(d_parent && ((d_space == SPACE && d_parent->layoutDim() == dim) || (d_space == DIV && d_parent->layoutDim() != dim)))
			d_sizing[dim] = WRAP;
		else if(d_parent && ((d_space == SPACE && d_parent->layoutDim() != dim) || (d_space == DIV && d_parent->layoutDim() == dim)))
			d_sizing[dim] = SHRINK;

		if(d_sizing[dim] == WRAP && d_parent->d_sizing[dim] != SHRINK)
			d_sizing[dim] = EXPAND;
		if(d_sizing[dim] == WRAP && d_parent->d_sizing[dim] == SHRINK)
			d_sizing[dim] = SHRINK;
	}

	void Frame::updateSpace()
	{
		if(!m_text.empty() || m_image != nullptr || d_inkstyle->image() != nullptr)
			d_space = BLOCK;
		else
			d_space = BOARD;
	}

	void Frame::updateStyle()
	{
		d_style = &d_widget.fetchOverride(d_widget.style());
		d_layout = &d_style->layout();
		d_styleStamp = d_style->updated();
		
		d_flow = d_layout->d_flow == FLOW;
		d_opacity = d_layout->d_opacity;
		if(d_span.null())
			d_span = d_layout->d_span;

		this->resetInkstyle(d_style->subskin(d_widget.state()));

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

		if(d_parent && d_parent->parent() && d_parent->parent()->layout().d_weight == TABLE) // @kludge if this is not done the table layout is fucked up because elements are set back to SHRINK and their size is wrongly substracted from sequencelength
			d_sizing[DIM_X] = EXPAND;
	}

	void Frame::updateFixed(Dimension dim)
	{
		if(!d_layout->size()[dim])
			return;

		d_sizing[dim] = FIXED;
		if(d_layout->d_space != BOARD || d_size[dim] == 0.f)
			this->setSizeDim(dim, d_layout->size()[dim]);
	}

	void Frame::bind(Stripe* parent)
	{
		d_parent = parent;
		this->updateStyle();
	}
	
	void Frame::unbind()
	{
		d_parent = nullptr;
	}

	void Frame::remove()
	{
		if(d_parent)
			d_parent->remove(*this);
	}

	Frame* Frame::before()
	{
		int index = d_index;
		while(index-- > 0)
			if(!d_parent->contents().at(index)->hidden())
				return d_parent->contents().at(index);
		return nullptr;
	}

	Frame& Frame::prev()
	{
		return *d_parent->contents().at(d_index - 1);
	}

	Frame& Frame::next()
	{
		return *d_parent->contents().at(d_index + 1);
	}

	bool Frame::first()
	{
		return d_index == 0;
	}

	bool Frame::last()
	{
		return d_index == d_parent->sequence().size()-1;
	}

	void Frame::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);

		d_widget.nextFrame(tick, delta);

		if(d_style->updated() > d_styleStamp)
			this->resetStyle();

		this->updateOnce();
	}

	void Frame::render(Renderer& renderer)
	{
		this->beginDraw(renderer);
		this->endDraw(renderer);
	}

	void Frame::updateOnce()
	{
		if(d_parent)
			this->setDirty(d_parent->forceDirty());

		if(d_dirty >= DIRTY_POSITION)
			this->updatePosition();
		if(d_frame.dirty() >= DIRTY_OFFSET)
			this->layer().setRedraw();

		d_dirty = CLEAN;
	}

	void Frame::transfer(Stripe& stripe, size_t index)
	{
		stripe.insert(*this, index);
		this->migrate(stripe);
	}

	void Frame::migrate(Stripe& stripe)
	{
		UNUSED(stripe);
		if(this->frameType() == LAYER)
			return;

		this->setDirty(DIRTY_VISIBILITY);
	}

	void Frame::updatePosition()
	{
		if(!d_parent || d_hidden || unflow())
			return;

		d_parent->positionDepth(*this);
		d_parent->positionLength(*this);
	}

	void Frame::updateState(WidgetState state)
	{
		this->updateInkstyle(d_style->subskin(state));
	}

	void Frame::resized(Dimension dim)
	{
		UNUSED(dim);
		this->updateContentSize();
	}

	void Frame::setSizeDim(Dimension dim, float size)
	{
		if(d_size[dim] == size)
			return;

		float delta = size - d_size[dim];
		d_size[dim] = size;
		this->setDirty(DIRTY_FRAME);

		// @kludge checking state because of double loop bind -> updateStyle -> setSizeDim -> childSized and insert -> childShown adding size twice
		// one option is reversing the parent part of updateStyle() so that the stripe takes care of it on insert (setting override style, space, sizing, and size)
		if(d_widget.state() & BOUND && d_parent)
			d_parent->childSized(*this, dim, delta);
		this->resized(dim);
	}

	void Frame::setSpanDim(Dimension dim, float span)
	{
		if(d_span[dim] == span)
			return;

		d_sizing[dim] = EXPAND;
		d_span[dim] = span;
		this->setDirty(DIRTY_FRAME);

		d_parent->setDirty(DIRTY_FLOW);
	}

	void Frame::setPositionDim(Dimension dim, float position)
	{
		d_position[dim] = position;
		this->setDirty(DIRTY_ABSOLUTE);
	}

	void Frame::show()
	{
		d_hidden = false;
		this->setDirty(DIRTY_VISIBILITY);
		if(d_parent)
			d_parent->childShown(*this);
	}

	void Frame::hide()
	{
		d_hidden = true;
		this->setDirty(DIRTY_VISIBILITY);
		if(d_parent)
			d_parent->childHidden(*this);
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

	bool Frame::inside(float x, float y)
	{
		float left = dabsolute(DIM_X);
		float top = dabsolute(DIM_Y);
		return (x >= left && x <= left + dsize(DIM_X)
			&& y >= top && y <= top + dsize(DIM_Y));
	}

	Frame* Frame::pinpoint(float x, float y, bool opaque)
	{
		if((opaque && !this->opaque()) || !this->inside(x, y))
			return nullptr;
		else
			return this;
	}

	bool Frame::nextOffset(Dimension dim, float& pos, float seuil, bool top)
	{
		UNUSED(top);
		pos += d_parent->extent(*this, dim);
		return pos > seuil;
	}

	bool Frame::prevOffset(Dimension dim, float& pos, float seuil, bool top)
	{
		UNUSED(top);
		if(pos + d_parent->extent(*this, dim) >= seuil)
			return true;
		
		pos += d_parent->extent(*this, dim);
		return false;
	}
}
