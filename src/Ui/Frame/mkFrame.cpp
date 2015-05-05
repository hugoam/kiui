//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkFrame.h>

#include <Object/String/mkString.h>
#include <Object/Iterable/mkReverse.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkInk.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

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
		, d_widget(widget)
		, d_parent(nullptr)
		, d_dirty(DIRTY_VISIBILITY)
		, d_hidden(false)
		, d_visible(true)
		, d_clipPos(0.f, 0.f)
		, d_clipSize(0.f, 0.f)
		, d_index(0)
		, d_style(nullptr)
		, d_inkstyle(nullptr)
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
			this->updateStyle();
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
		if(d_widget.image() || !d_widget.label().empty())
			d_space = BLOCK;
		else
			d_space = BOARD;
	}

	void Frame::updateStyle()
	{
		d_style = &d_widget.fetchOverride(d_widget.style());
		d_layout = &d_style->layout();
		d_inkstyle = &d_style->subskin(d_widget.state());
		d_styleStamp = d_style->updated();

		d_flow = d_layout->d_flow == FLOW;
		d_opacity = d_layout->d_opacity;
		if(d_span.null())
			d_span = d_layout->d_span;

		this->updateSizing();

		this->setDirty(DIRTY_SKIN);
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

		if(d_parent && d_parent->parent() && d_parent->parent()->layout()->d_weight == TABLE) // @kludge if this is not done the table layout is fucked up because elements are set back to SHRINK and their size is wrongly substracted from sequencelength
			d_sizing[DIM_X] = EXPAND;
	}

	void Frame::updateFixed(Dimension dim)
	{
		if(d_layout->size()[dim])
		{
			d_sizing[dim] = FIXED;
			if(d_layout->d_space != BOARD || d_size[dim] == 0.f)
			{
				d_size[dim] = d_layout->size()[dim];
				d_clipSize[dim] = d_layout->size()[dim];
				this->setDirty(DIRTY_FRAME);
				this->resized(dim);
			}
			//this->setSizeDim(dim, d_layout->size()[dim]);
		}
	}

	void Frame::bind(Stripe* parent)
	{
		d_parent = parent;
		this->updateStyle();
		d_inkbox = this->layer().inkLayer().createInkbox(*this);

		this->setVisible(d_parent->visible());
	}
	
	void Frame::unbind()
	{
		d_parent = nullptr;
		d_visible = false;
		d_inkbox.reset();
	}

	void Frame::remove()
	{
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

	void Frame::updateClip()
	{
		if(!d_parent || !d_visible || !clip())
			return;

		bool clipped = !d_inkbox->visible(); // We are visible, so the inkbox not visible means we were clipped

		this->updateClip(DIM_X);
		this->updateClip(DIM_Y);

		if((dclip(DIM_X) == HIDDEN || dclip(DIM_Y) == HIDDEN) && !clipped)
			d_inkbox->hide();
		else if(dclip(DIM_X) != HIDDEN && dclip(DIM_Y) != HIDDEN && clipped)
			d_inkbox->show();

		d_inkbox->updateClip();
	}

	void Frame::updateClip(Dimension dim)
	{
		d_clipPos[dim] = std::max(d_parent->d_clipPos[dim] - d_position[dim], 0.f);
		d_clipSize[dim] = std::min(d_size[dim], d_parent->d_clipPos[dim] + d_parent->d_clipSize[dim] - d_position[dim]) - d_clipPos[dim];
		d_clipSize[dim] = std::max(d_clipSize[dim], 0.f);
	}

	void Frame::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);

		if(d_style->updated() > d_styleStamp)
			this->resetStyle();

		this->updateOnce();
	}

	void Frame::updateOnce()
	{
		if(d_parent)
			this->setDirty(d_parent->forceDirty());

		switch(d_dirty)
		{
		case DIRTY_FLOW:
		case DIRTY_OFFSET:
		case DIRTY_VISIBILITY:
			d_visible ? d_inkbox->show() : d_inkbox->hide();
		case DIRTY_SKIN:
			d_inkbox->updateStyle();
		case DIRTY_WIDGET:
			d_inkbox->updateContent();
		case DIRTY_CONTENT:
			this->updateSize();
		case DIRTY_FRAME:
			d_inkbox->updateFrame();
		case DIRTY_POSITION:
			this->updatePosition();
		case DIRTY_CLIP:
			this->updateClip();
		case DIRTY_ABSOLUTE:
			this->derivePosition();
			d_inkbox->updatePosition();
		case CLEAN:
			break;
		};

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

		d_inkbox = this->layer().inkLayer().createInkbox(*this);
		this->setDirty(DIRTY_VISIBILITY);
	}

	void Frame::updatePosition()
	{
		if(!d_parent || d_hidden || unflow())
			return;

		d_parent->positionDepth(*this);
		d_parent->positionLength(*this);
	}

	void Frame::derivePosition()
	{
		d_absolute[DIM_X] = this->calcAbsolute(DIM_X);
		d_absolute[DIM_Y] = this->calcAbsolute(DIM_Y);
	}

	void Frame::updateSize()
	{
		//if(!d_inkbox->visible()) // @note this is needed for gorilla, but not for nanovg, discuss
		//	return;

		if(dshrink(DIM_X) && (this->frameType() == FRAME || this->as<Stripe>().sequence().size() == 0))
			this->setSizeDim(DIM_X, d_inkbox->contentSize(DIM_X));
		if(dshrink(DIM_Y) && (this->frameType() == FRAME || this->as<Stripe>().sequence().size() == 0)) // !this->container())
			this->setSizeDim(DIM_Y, d_inkbox->contentSize(DIM_Y));
	}

	void Frame::updateState(WidgetState state)
	{
		InkStyle* inkstyle = d_inkstyle;
		d_inkstyle = &d_style->subskin(state);

		if(d_inkstyle != inkstyle)
			this->setDirty(DIRTY_SKIN);
	}

	void Frame::setSizeDim(Dimension dim, float size)
	{
		if(d_size[dim] == size)
			return;

		float delta = size - d_size[dim];
		d_size[dim] = size;
		this->setDirty(DIRTY_FRAME);

		if(dexpand(dim) || !flow())
			d_clipSize[dim] = size;

		if(d_parent)
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
		d_clipPos[dim] = 0.f;
		this->setDirty(DIRTY_ABSOLUTE);
	}

	void Frame::show()
	{
		d_hidden = false;
		if(!d_visible)
			this->setVisible(true);
		if(d_parent)
			d_parent->childShown(*this);
	}

	void Frame::hide()
	{
		d_hidden = true;
		if(d_visible)
			this->setVisible(false);
		if(d_parent)
			d_parent->childHidden(*this);
	}

	void Frame::setVisible(bool visible)
	{
		visible ? this->setVisible() : this->setInvisible();
	}

	void Frame::setVisible()
	{
		if(d_visible || d_hidden || (d_parent && !d_parent->visible()))
			return;

		d_visible = true;
		this->setDirty(DIRTY_VISIBILITY);
	}

	void Frame::setInvisible()
	{
		if(d_visible == false)
			return;

		d_visible = false;
		this->setDirty(DIRTY_VISIBILITY);
	}

	float Frame::calcAbsolute(Dimension dim)
	{
		if(d_parent)
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
