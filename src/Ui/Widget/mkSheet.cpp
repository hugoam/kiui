//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkSheet.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkWScrollbar.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Object/Store/mkReverse.h>

#include <iostream>

namespace mk
{
	Sheet::Sheet(Style* style, Form* form)
		: Widget(style, form)
		, mScrollbar(nullptr)
	{}

	Sheet::~Sheet()
	{}

	void Sheet::build()
	{}

	void Sheet::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);
		
		// @todo @bug for a sheet with 0 size the following seems to cause a crash in Stripe::nextFrame()
		if(mFrame->style()->d_overflow == SCROLL)
			if(this->stripe()->overflow() && !mScrollbar)
			{
				mScrollsheet = mParent->makeappend<WScrollSheet>();
				mScrollsheet->append(mParent->release(this));
				mScrollbar = mScrollsheet->makeappend<WScrollbar>(this->stripe());
			}
			else if(!this->stripe()->overflow() && mScrollbar)
			{
				mScrollsheet->parent()->append(mScrollsheet->release(this));
				mScrollsheet->destroy();
				mScrollbar = nullptr;
			}
	}

	Widget* Sheet::append(unique_ptr<Widget> unique)
	{
		return this->insert(std::move(unique), mContents.size());
	}

	Widget* Sheet::insert(unique_ptr<Widget> unique, size_t index)
	{
		Widget* widget = unique.get();
		mContents.insert(mContents.begin() + index, std::move(unique));
		widget->parent() ? widget->rebind(this, index) : widget->bind(this, index);
		return widget;
	}

	unique_ptr<Widget> Sheet::release(Widget* widget)
	{
		widget->detach();

		size_t pos = 0;
		while(mContents[pos].get() != widget)
			++pos;

		unique_ptr<Widget> pointer = std::move(mContents[pos]);
		mContents.erase(mContents.begin() + pos);
		return pointer;
	}

	unique_ptr<Widget> Sheet::release(size_t index)
	{
		mContents.at(index)->detach();

		unique_ptr<Widget> pointer = std::move(mContents[index]);
		mContents.erase(mContents.begin() + index);
		return pointer;
	}

	void Sheet::clear()
	{
		for(auto& widget : mContents)
			widget->detach();

		mContents.clear();
	}

	GridSheet::GridSheet(Dimension dim, Style* style, Form* form)
		: Sheet(style, form)
		, mDim(dim)
		, mResizing(nullptr)
		, mHoverCursor(mDim == DIM_X ? ResizeCursorX::styleCls() : ResizeCursorY::styleCls())
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
		this->stripe()->weights()[prev->frame()->index()] = prev->frame()->dspan(mDim) + offset;
		this->stripe()->weights()[next->frame()->index()] = next->frame()->dspan(mDim) - offset;
		this->stripe()->markRelayout();

		this->gridResized(prev, next);

		return true;
	}

	bool GridSheet::leftDragEnd(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		return true;
	}

	Cursor::Cursor()
		: Widget(styleCls())
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
		if(widget->hoverCursor())
			this->reset(widget->hoverCursor());
	}

	void Cursor::unhover(Widget* widget)
	{
		if(widget->hoverCursor())
			this->reset(styleCls());
	}

	Tooltip::Tooltip(const string& label)
		: Widget(styleCls())
		, mLabel(label)
	{}

	Tooltip::~Tooltip()
	{}

	void Tooltip::setLabel(const string& label)
	{
		mLabel = label;
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}

	RootSheet::RootSheet(UiWindow* window, Form* form)
		: Sheet(styleCls(), form)
		, mWindow(window)
	{
		mFrame = make_unique<Layer>(nullptr, this, 0);
		mFrame->setOpacity(_OPAQUE);
	}
}
