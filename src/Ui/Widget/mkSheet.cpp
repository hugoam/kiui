//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkSheet.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkWScrollbar.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Object/Store/mkReverse.h>

#include <iostream>

namespace mk
{
	Sheet::Sheet(string clas, Form* form)
		: Widget(clas, form)
		, mOverrides(false)
	{}

	Sheet::~Sheet()
	{}

	void Sheet::build()
	{
		mOverrides = this->uiWindow()->skinner()->hasOverrides(mClas);
	}

	InkStyle* Sheet::elementSkin(string clas)
	{
		if(mOverrides)
			return this->uiWindow()->skinner()->elementSkin(clas, mClas);
		else
			return mParent->elementSkin(clas);
	}

	LayoutStyle* Sheet::elementStyle(string clas)
	{
		if(mOverrides)
			return this->uiWindow()->layout()->elementStyle(clas, mClas);
		else
			return mParent->elementStyle(clas);
	}

	Widget* Sheet::append(unique_ptr<Widget> unique)
	{
		return this->insert(std::move(unique), mContents.size());
	}

	Widget* Sheet::insert(unique_ptr<Widget> unique, size_t index)
	{
		Widget* widget = unique.get();
		mContents.insert(std::move(unique), index);
		widget->parent() ? widget->rebind(this) : widget->bind(this);
		return widget;
	}

	unique_ptr<Widget> Sheet::release(Widget* widget)
	{
		widget->detach();
		return mContents.release(widget);
	}

	unique_ptr<Widget> Sheet::release(size_t index)
	{
		mContents.at(index)->detach();
		return mContents.release(index);
	}

	void Sheet::clear()
	{
		for(auto& widget : mContents.store())
			widget->detach();

		mContents.clear();
	}

	GridSheet::GridSheet(Dimension dim, string clas, Form* form)
		: Sheet(clas, form)
		, mDim(dim)
		, mResizing(nullptr)
		, mHoverCursor(mDim == DIM_X ? "resize_h cursor" : "resize_v cursor")
	{}

	void GridSheet::build()
	{
		Sheet::build();
	}

	bool GridSheet::leftDragStart(float xPos, float yPos)
	{
		float pos = mDim == DIM_X ? xPos : yPos;
		mResizing = nullptr;

		for(Frame* frame : mFrame->as<Stripe>()->sequence())
			if(frame->dabsolute(mDim) >= pos)
			{
				mResizing = frame->widget();
				break;
			}

		return true;
	}

	bool GridSheet::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xPos); UNUSED(yPos);

		if(!mResizing)
			return true;

		Widget* prev = mResizing->prev();
		Widget* next = mResizing;

		float pixspan = 1.f / mFrame->as<Stripe>()->dsize(mDim);
		float offset = mDim == DIM_X ? xDif * pixspan : yDif * pixspan;

		//std::cerr << "Dragging resize offset " << offset << std::endl;
		prev->frame()->setSpanDim(mDim, prev->frame()->dspan(mDim) + offset);
		next->frame()->setSpanDim(mDim, next->frame()->dspan(mDim) - offset);
		//std::cerr << prev->frame()->dspan(mDim) << " + " << next->frame()->dspan(mDim) << " = " << 1.f << std::endl;

		this->gridResized(prev, next);

		return true;
	}

	bool GridSheet::leftDragEnd(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		return true;
	}

	ScrollSheet::ScrollSheet(string clas, Form* form)
		: Sheet("scrollsheet", form)
		, mClas(clas)
		, mForm(form)
		//, mSheet(this->makeappend<Sheet>(clas, form))
		, mScrollbar(nullptr)
	{}

	void ScrollSheet::build()
	{
		Sheet::build();
		mScrollbox = this->makeappend<Sheet>("scrollbox");
		mSheet = mScrollbox->makeappend<Sheet>(mClas, mForm);
	}

	Widget* ScrollSheet::vappend(unique_ptr<Widget> widget)
	{
		return mSheet->vappend(std::move(widget));
	}

	unique_ptr<Widget> ScrollSheet::vrelease(Widget* widget)
	{
		return mSheet->vrelease(widget);
	}

	void ScrollSheet::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
		if(mSheet->stripe()->overflow() && !mScrollbar)
		{
			mScrollbar = this->makeappend<WScrollbar>(mSheet->stripe());
		}
		else if(!mSheet->stripe()->overflow() && mScrollbar)
		{
			this->release(mScrollbar);
			mScrollbar = nullptr;
		}
	}

	Cursor::Cursor()
		: Widget("cursor")
	{}

	void Cursor::nextFrame()
	{
		if(mDirty)
		{
			mFrame->inkbox()->updateFrame();
			mDirty = false;
		}
	}

	void Cursor::setPosition(float x, float y)
	{
		mFrame->setPosition(x, y);
		mDirty = true;
	}

	void Cursor::hover(Widget* widget)
	{
		if(widget->hoverCursor() != "")
			this->reset(widget->hoverCursor());
	}

	void Cursor::unhover(Widget* widget)
	{
		if(widget->hoverCursor() != "")
			this->reset("cursor");
	}

	Tooltip::Tooltip(const string& label)
		: Widget("tooltip")
		, mLabel(label)
	{}

	Tooltip::~Tooltip()
	{}

	void Tooltip::setLabel(string label)
	{
		mLabel = label;
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	RootSheet::RootSheet(UiWindow* window, Form* form)
		: Sheet("", form)
		, mWindow(window)
	{
		mFrame = make_unique<Stripe>(nullptr, this, form->clas());
		mFrame->setOpacity(_OPAQUE);
	}

	InkStyle* RootSheet::elementSkin(string clas)
	{
		return mWindow->skinner()->elementSkin(clas, "");
	}

	LayoutStyle* RootSheet::elementStyle(string clas)
	{
		return mWindow->layout()->elementStyle(clas, "");
	}

}
