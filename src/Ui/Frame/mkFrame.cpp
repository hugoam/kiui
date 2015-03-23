//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Frame/mkFrame.h>

#include <Object/String/mkString.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkInk.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Style/mkStyle.h>

#include <iostream>

namespace mk
{
	Frame::Frame(Stripe* parent, Widget* widget, size_t index)
		: Uibox(widget->style()->layout())
		, d_widget(widget)
		, d_parent(parent)
		, d_dirty(DIRTY_VISIBILITY)
		, d_hidden(false)
		, d_visible(!parent || parent->visible())
		, d_clipPos(0.f, 0.f)
		, d_clipSize(0.f, 0.f)
		, d_index(index)
		, d_wstyle(widget->style())
		, d_inkstyle(d_wstyle->skin())
		, d_inkbox(widget->frameType() < LAYER ? this->layer()->inkLayer()->inkbox(this) : nullptr)
	{
		if(d_parent)
			d_parent->insert(this, index);

		if(dfixed(DIM_X))
			setSizeDim(DIM_X, d_style->d_size[DIM_X]);
		if(dfixed(DIM_Y))
			setSizeDim(DIM_Y, d_style->d_size[DIM_Y]);
 	}

	Frame::~Frame()
	{}

	FrameType Frame::frameType()
	{
		return d_widget->frameType();
	}

	Layer* Frame::layer()
	{
		if(this->frameType() < LAYER)
			return d_parent->layer();
		else
			return this->as<Layer>();	
	}

	void Frame::reset(Style* style)
	{
		d_parent->remove(this);

		this->setStyle(style->layout());
		d_wstyle = style;
		d_inkstyle = style->skin();

		d_parent->insert(this, d_index);

		this->setDirty(DIRTY_WIDGET);
	}

	void Frame::remove()
	{
		d_parent->remove(this);
		// d_parent = nullptr;
		// @kludge possible dangling pointer, commented out for now because of ~Layer() which accesses d_parent
	}

	void Frame::clip()
	{
		if(!d_parent || !d_visible || !flow())
			return;

		d_clipPos[DIM_X] = std::max(d_parent->d_clipPos[DIM_X] - d_position[DIM_X], 0.f);
		d_clipPos[DIM_Y] = std::max(d_parent->d_clipPos[DIM_Y] - d_position[DIM_Y], 0.f);

		d_clipSize[DIM_X] = std::min(dsize(DIM_X), d_parent->d_clipPos[DIM_X] + d_parent->d_clipSize[DIM_X] - d_position[DIM_X]) - d_clipPos[DIM_X];
		d_clipSize[DIM_Y] = std::min(dsize(DIM_Y), d_parent->d_clipPos[DIM_Y] + d_parent->d_clipSize[DIM_Y] - d_position[DIM_Y]) - d_clipPos[DIM_Y];

		d_clipSize[DIM_X] = std::max(d_clipSize[DIM_X], 0.f);
		d_clipSize[DIM_Y] = std::max(d_clipSize[DIM_Y], 0.f);

		bool clipped = !d_inkbox->visible(); // We are visible, so the inkbox not visible means we were clipped

		if((dclip(DIM_X) == HIDDEN || dclip(DIM_Y) == HIDDEN) && !clipped)
			d_inkbox->hide();
		else if(dclip(DIM_X) != HIDDEN && dclip(DIM_Y) != HIDDEN && clipped)
			d_inkbox->show();
	}

	void Frame::nextFrame(size_t tick, size_t delta)
	{
		//if(d_style->d_updated == tick)
		//	this->setStyle(d_style);

		switch(d_dirty)
		{
		case DIRTY_VISIBILITY:
			d_visible ? d_inkbox->show() : d_inkbox->hide();
		//case DIRTY_FLOW:
		case DIRTY_SKIN:
			d_inkbox->updateStyle();
		case DIRTY_WIDGET:
			d_inkbox->updateContent();
		case DIRTY_CONTENT:
			this->updateSize();
		case DIRTY_FRAME:
			this->updatePosition();
			this->clip();
			d_inkbox->updateFrame();
		case CLEAN:
			break;
		};

		d_dirty = CLEAN;
	}

	void Frame::transfer(Stripe* stripe, size_t index)
	{
		stripe->insert(this, index);
		this->migrate(stripe);
	}

	void Frame::migrate(Stripe* stripe)
	{
		if(this->frameType() == LAYER)
			return;

		d_inkbox = this->layer()->inkLayer()->inkbox(this);
		this->setDirty(DIRTY_WIDGET);
	}

	void Frame::updatePosition()
	{
		d_absolute[DIM_X] = this->calcAbsolute(DIM_X);
		d_absolute[DIM_Y] = this->calcAbsolute(DIM_Y);
	}

	void Frame::updateSize()
	{
		//if(!d_widget->label().empty() && this->container())
		//	std::cerr << "WARNING : label of style " << d_widget->style() << " not fitted to text as it's a container" << std::endl;

		if(dshrink(DIM_X) && (this->frameType() == FRAME || this->as<Stripe>()->contents().size() == 0))
			this->setSizeDim(DIM_X, d_inkbox->contentSize(DIM_X));
		if(dshrink(DIM_Y) && (this->frameType() == FRAME || this->as<Stripe>()->contents().size() == 0)) // !this->container())
			this->setSizeDim(DIM_Y, d_inkbox->contentSize(DIM_Y));
	}

	void Frame::updateState(WidgetState state)
	{
		InkStyle* inkstyle = d_inkstyle;

		if(d_wstyle->subskin(state))
			d_inkstyle = d_wstyle->subskin(state);
		else
			d_inkstyle = d_wstyle->skin();

		if(d_inkstyle != inkstyle)
			this->setDirty(DIRTY_SKIN);
	}

	void Frame::setSizeDim(Dimension dim, float size)
	{
		if(d_size[dim] == size)
			return;

		float delta = size - d_size[dim];
		d_size[dim] = size;
		d_clipSize[dim] = size;
		this->setDirty(DIRTY_FRAME);

		if(d_parent && flow() && (dshrink(dim) || dfixed(dim))) // Upward notification -> when shrinking
			d_parent->flowSized(this, dim, delta);

		//if(dexpand(dim)) // Downward notification -> when expanding
		this->resized(dim);
	}

	void Frame::setSpanDim(Dimension dim, float span)
	{
		if(d_span[dim] == span)
			return;

		d_sizing[dim] = EXPAND;
		d_span[dim] = span;
		this->setDirty(DIRTY_FRAME);

		d_parent->markRelayout();
	}

	void Frame::setPositionDim(Dimension dim, float position)
	{
		d_position[dim] = position;
		d_clipPos[dim] = 0.f;
		this->markDirty(DIRTY_FRAME);
	}

	void Frame::markDirty(Dirty dirty)
	{
		this->setDirty(dirty);
	}

	void Frame::show()
	{
		d_hidden = false;
		if(!d_visible)
			this->setVisible(true);
		if(this->flow())
			d_parent->flowShown(this);
	}

	void Frame::hide()
	{
		d_hidden = true;
		if(d_visible)
			this->setVisible(false);
		if(this->flow())
			d_parent->flowHidden(this);
	}

	void Frame::setVisible(bool visible)
	{
		visible ? this->setVisible() : this->setInvisible();
	}

	void Frame::setVisible()
	{
		if(d_visible || !d_parent->visible() || d_hidden)
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
			return d_parent->dabsolute(dim) + d_parent->dpivotposition(dim, this);
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

	FrameSkin::FrameSkin(Frame* frame, ImageSkin* skin)
		: d_frame(frame)
		, d_skin(skin)
	{
		d_left = floor(frame->dabsolute(DIM_X) + frame->inkstyle()->mMargin[DIM_X]);
		d_top = floor(frame->dabsolute(DIM_Y) + frame->inkstyle()->mMargin[DIM_Y]);

		float width = floor(frame->dsize(DIM_X) - frame->inkstyle()->mMargin[DIM_X] - frame->inkstyle()->mMargin[DIM_X + 2]);
		float height = floor(frame->dsize(DIM_Y) - frame->inkstyle()->mMargin[DIM_Y] - frame->inkstyle()->mMargin[DIM_Y + 2]);

		d_inleft = d_left + d_skin->d_leftIn;
		d_inright = d_left + width - d_skin->d_rightIn;
		d_intop = d_top + d_skin->d_topIn;
		d_inbottom = d_top + height - d_skin->d_bottomIn;

		d_outtop = d_top - d_skin->d_topOut;
		d_outleft = d_left - d_skin->d_leftOut;

		d_inwidth = d_inright - d_inleft;
		d_inheight = d_inbottom - d_intop;
	}
}
