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

#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkWScrollbar.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	Sheet::Sheet(Style* style, Form* form)
		: Widget(style, form)
	{}

	Sheet::~Sheet()
	{}

	void Sheet::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);
		
		for(size_t i = 0; i < mContents.size(); ++i)
			mContents[i]->nextFrame(tick, delta);
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

	void Sheet::cleanup()
	{
		Widget::cleanup();

		for(auto& widget : mContents)
			widget->cleanup();
	}

	ScrollSheet::ScrollSheet(Style* style, Form* form)
		: Sheet(style, form)
		, mSheet(nullptr)
		, mScrollbar(nullptr)
	{}

	ScrollSheet::~ScrollSheet()
	{}

	void ScrollSheet::build()
	{
		mSheet = this->makeappend<Sheet>(DivY::styleCls());
		mScrollbar = this->makeappend<WScrollbar>(mSheet->stripe());
	}

	void ScrollSheet::nextFrame(size_t tick, size_t delta)
	{
		if(mSheet->stripe()->cursor() > 0.f && mSheet->stripe()->sequenceLength() - mSheet->stripe()->cursor() < mFrame->dsize(DIM_Y))
			mSheet->stripe()->setCursor(mSheet->stripe()->sequenceLength() - mFrame->dsize(DIM_Y));

		Sheet::nextFrame(tick, delta);

		if(mSheet->stripe()->overflow() && mScrollbar->frame()->hidden())
			mScrollbar->show();
		else if(!mSheet->stripe()->overflow() && !mScrollbar->frame()->hidden())
			mScrollbar->hide();
	}

	Widget* ScrollSheet::vappend(unique_ptr<Widget> widget)
	{
		return mSheet->vappend(std::move(widget));
	}

	unique_ptr<Widget> ScrollSheet::vrelease(Widget* widget)
	{
		return mSheet->vrelease(widget);
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

		prev->frame()->setSpanDim(mDim, std::max(0.01f, prev->frame()->dspan(mDim) + offset));
		next->frame()->setSpanDim(mDim, std::max(0.01f, next->frame()->dspan(mDim) - offset));

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

	void Cursor::build()
	{
		mTooltip = this->rootSheet()->makeappend<Tooltip>("");
		mHovered = mParent;
	}

	void Cursor::nextFrame()
	{
		if(mTooltipClock.read() > 0.5f && !mTooltip->frame()->visible() && !mHovered->tooltip().empty())
			this->tooltipOn();

		if(mDirty)
		{
			mFrame->inkbox()->updateFrame();
			mDirty = false;
		}
	}

	void Cursor::setPosition(float x, float y)
	{
		if(mTooltip->frame()->visible())
			this->tooltipOff();
		mTooltipClock.step();
		mFrame->setPosition(x, y);
		mDirty = true;
	}

	void Cursor::tooltipOn()
	{
		mTooltip->setLabel(mHovered->tooltip());
		mTooltip->frame()->setPosition(mFrame->dposition(DIM_X), mFrame->dposition(DIM_Y) + mFrame->dsize(DIM_Y));
		mTooltip->show();
	}

	void Cursor::tooltipOff()
	{
		mTooltip->setLabel("");
		mTooltip->hide();
	}

	void Cursor::hover(Widget* widget)
	{
		mHovered = widget;
		if(widget->hoverCursor())
			this->reset(widget->hoverCursor());
	}

	void Cursor::unhover(Widget* widget)
	{
		mHovered = mParent;
		if(widget->hoverCursor())
			this->reset(styleCls());
	}

	Caret::Caret(Frame* textFrame)
		: Widget(styleCls())
		, mTextFrame(textFrame)
		, mIndex(0)
		, mDirty(false)
	{}

	void Caret::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);

		if(mDirty && mTextFrame->inkbox()->visible())
		{
			float caretX, caretY, caretHeight;
			mTextFrame->inkbox()->caretCoords(mIndex, caretX, caretY, caretHeight);
			mFrame->setPosition(caretX, caretY);
			mFrame->setSize(1.f, caretHeight);
		}
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
}
