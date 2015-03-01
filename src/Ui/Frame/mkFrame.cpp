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

#include <iostream>

namespace mk
{
	Frame::Frame(Stripe* parent, Widget* widget, string clas, size_t zorder)
		: Uibox(widget->elementStyle(clas))
		, d_widget(widget)
		, d_parent(parent)
		, d_dirty(DIRTY_SKIN)
		, d_hidden(false)
		, d_visible(!parent || parent->visible())
		, d_clipPos(0.f, 0.f)
		, d_clipSize(0.f, 0.f)
		, d_skin(widget->elementSkin(clas))
		, d_inkstyle(d_skin)
		, d_inkLayer(d_style->d_layer == LAYER ? widget->inkTarget()->layer(this, zorder) : nullptr)
		, d_inkbox(this->layer()->inkbox(this))
	{
		if(d_parent)
			//if(d_widget->form() && d_widget->form()->scheme()) // @ crash : if added to a tabber, we have a non-0 index whereas we are added as only child to a tab
			//	d_parent->insert(this, d_widget->form()->index());
			//else
				d_parent->append(this);

		if(dfixed(DIM_X))
			setSizeDim(DIM_X, d_style->d_size[DIM_X]);
		if(dfixed(DIM_Y))
			setSizeDim(DIM_Y, d_style->d_size[DIM_Y]);
 	}

	Frame::~Frame()
	{
		d_inkbox->hide(); // Destroys the inkboxes before the layer so that we don't try to destroy unexisting inkboxes (crash)
	}

	InkLayer* Frame::layer()
	{
		if(d_inkLayer)
			return d_inkLayer.get();
		else
			return d_parent->layer();
	}

	void Frame::reset(LayoutStyle* style, InkStyle* skin)
	{
		bool flowChange = style->d_flow != d_style->d_flow;

		if(d_visible)
			this->setVisible(false);

		d_parent->remove(this);

		this->setStyle(style);
		d_skin = skin;
		d_inkstyle = skin;

		this->setVisible(true);

		if(flowChange)
			d_parent->append(this);
		else
			d_parent->insert(this, d_index);

		this->setDirty(DIRTY_WIDGET);
	}

	void Frame::remove()
	{
		d_parent->remove(this);
		d_parent = nullptr;
	}

	void Frame::shrink()
	{
		if(d_dirty >= DIRTY_CONTENT)
			this->updateSize();
	}

	void Frame::clip()
	{
		if(!d_parent || !d_visible || !flow())
			return;

		bool clipped = dclip(DIM_X) == HIDDEN || dclip(DIM_Y) == HIDDEN;

		d_clipPos[DIM_X] = std::max(d_parent->d_clipPos[DIM_X] - d_position[DIM_X], 0.f);
		d_clipPos[DIM_Y] = std::max(d_parent->d_clipPos[DIM_Y] - d_position[DIM_Y], 0.f);

		d_clipSize[DIM_X] = std::min(dsize(DIM_X), d_parent->d_clipPos[DIM_X] + d_parent->d_clipSize[DIM_X] - d_position[DIM_X]) - d_clipPos[DIM_X];
		d_clipSize[DIM_Y] = std::min(dsize(DIM_Y), d_parent->d_clipPos[DIM_Y] + d_parent->d_clipSize[DIM_Y] - d_position[DIM_Y]) - d_clipPos[DIM_Y];

		/*Stripe* parent = d_parent;
		while(parent)
		{
			std::cerr << "  ";
			parent = parent->parent();
		}

		std::cerr << "Frame :: clip " << d_widget->clas() << " name " << d_widget->name() << " clipsize " << d_clipSize[DIM_X] << " , " << d_clipSize[DIM_Y] << std::endl;
		*/
		if((dclip(DIM_X) == HIDDEN || dclip(DIM_Y) == HIDDEN) && !clipped)
		{
			d_inkbox->hide();
		}
		else if(dclip(DIM_X) != HIDDEN && dclip(DIM_Y) != HIDDEN && clipped)
		{
			d_inkbox->show();
			d_inkbox->updateStyle();
			d_inkbox->updateContent();
		}
	}

	void Frame::nextFrame(size_t tick, size_t delta)
	{
		//if(d_style->d_updated == tick)
		//	this->setStyle(d_style);

		if(d_widget)
			d_widget->nextFrame(tick, delta);

		switch(d_dirty)
		{
		case DIRTY_FLOW:
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

	void Frame::migrate(Stripe* stripe)
	{
		// we hide and show, to preserve drawing order
		if(d_visible)
			this->setVisible(false);
		this->setVisible(true);

		if(this->layer())
			return;

		d_inkbox = stripe->layer()->inkbox(this);
		this->setDirty(DIRTY_WIDGET);
	}

	void Frame::moveToTop()
	{
		if(d_inkLayer)
			d_inkLayer->moveToTop();
	}

	void Frame::updatePosition()
	{
		d_absolute[DIM_X] = this->calcAbsolute(DIM_X);
		d_absolute[DIM_Y] = this->calcAbsolute(DIM_Y);
	}

	void Frame::updateSize()
	{
		//if(d_widget->label() != "" && this->container())
		//	std::cerr << "WARNING : label of clas " << d_widget->clas() << " not fitted to text as it's a container" << std::endl;

		if(dshrink(DIM_X) && (this->frameType() == FRAME || this->as<Stripe>()->contents().size() == 0))
			this->setSizeDim(DIM_X, d_inkbox->contentSize(DIM_X));
		if(dshrink(DIM_Y) && (this->frameType() == FRAME || this->as<Stripe>()->contents().size() == 0)) // !this->container())
			this->setSizeDim(DIM_Y, d_inkbox->contentSize(DIM_Y));
	}

	void Frame::updateState(WidgetState state)
	{
		if(d_skin->mSubInks.find(state) != d_skin->mSubInks.end())
			d_inkstyle = d_skin->mSubInks[state];
		else
			d_inkstyle = d_skin;

		this->setDirty(DIRTY_SKIN);
	}

	void Frame::setSizeDim(Dimension dim, float size)
	{
		if(d_size[dim] == size)
			return;

		d_size[dim] = size;
		d_clipSize[dim] = size;
		this->markDirty(DIRTY_FRAME);

		if(flow() && (dshrink(dim) || dfixed(dim))) // Upward notification -> when shrinking
			d_parent->flowChanged(this, dim);

		if(dexpand(dim)) // Downward notification -> when expanding
			this->resized(dim);
	}

	void Frame::setSpanDim(Dimension dim, float span)
	{
		if(d_span[dim] == span)
			return;

		d_sizing[dim] = EXPAND;
		d_span[dim] = span;
		this->markDirty(DIRTY_FRAME);

		d_parent->flowChanged(this, dim);
	}

	void Frame::setPositionDim(Dimension dim, float position)
	{
		d_position[dim] = position;
		d_clipPos[dim] = 0.f;
		this->markDirty(DIRTY_FRAME);
	}

	void Frame::markDirty(Dirty dirty)
	{
		if(dirty > d_dirty)
			d_dirty = dirty;
	}

	void Frame::show()
	{
		d_hidden = false;
		this->setVisible(true);
		if(this->flow())
			d_parent->flowChanged(this);
	}

	void Frame::hide()
	{
		d_hidden = true;
		this->setVisible(false);
		if(this->flow())
			d_parent->flowChanged(this);
	}

	void Frame::setVisible(bool visible)
	{
		if(dclip(DIM_X) != HIDDEN && dclip(DIM_Y) != HIDDEN)
			visible ? this->setVisible() : this->setInvisible();
	}

	void Frame::setVisible()
	{
		if(!d_parent->visible() || d_hidden)
			return;

		d_visible = true;
		d_inkLayer ? d_inkLayer->show() : d_inkbox->show();
		this->setDirty(DIRTY_SKIN);
	}

	void Frame::setInvisible()
	{
		d_visible = false;
		d_inkLayer ? d_inkLayer->hide() : d_inkbox->hide();
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
		return (x > left && x < left + dsize(DIM_X)
			&& y > top && y < top + dsize(DIM_Y));
	}

	Frame* Frame::pinpoint(float x, float y, bool opaque)
	{
		UNUSED(x); UNUSED(y);
		if(!opaque)
			return this;
		else if(this->opaque())
			return this;
		else
			return nullptr;
	}
}
