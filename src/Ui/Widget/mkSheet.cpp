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

#include <Ui/Widget/mkScrollbar.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	Sheet::Sheet(FrameType frameType)
		: Widget(frameType)
	{
		mStyle = &cls();
	}

	Sheet::~Sheet()
	{}

	/*unique_ptr<Sheet> Sheet::copy()
	{
		unique_ptr<Sheet> copy = this->clone();

		for(size_t i = 0; i < mContents.size(); ++i)
			copy->append(mContents[i]->clone());

		return copy;
	}*/

	void Sheet::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);
		
		Stripe& stripe = this->stripe();
		for(size_t i = 0; i < stripe.contents().size(); ++i)
			stripe.contents()[i]->widget().nextFrame(tick, delta);
	}

	void Sheet::bind(Sheet* parent, size_t index)
	{
		Widget::bind(parent, index);

		for(size_t i = 0; i < mContents.size(); ++i)
			mContents[i]->bind(this, i);
	}

	void Sheet::rebind(Sheet* parent, size_t index)
	{
		Widget::rebind(parent, index);

		//for(size_t i = 0; i < mContents.size(); ++i)
		//	mContents[i]->rebind(this, i);
	}

	Widget& Sheet::append(unique_ptr<Widget> unique)
	{
		return this->insert(std::move(unique), mContents.size());
	}

	Widget& Sheet::insert(unique_ptr<Widget> unique, size_t index)
	{
		Widget& widget = *unique.get();
		mContents.insert(mContents.begin() + index, std::move(unique));
		if(mState & BOUND)
			widget.parent() ? widget.rebind(this, index) : widget.bind(this, index);
		return widget;
	}

	unique_ptr<Widget> Sheet::release(Widget& widget)
	{
		widget.detach();

		size_t pos = 0;
		while(mContents[pos].get() != &widget)
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

	LayerSheet::LayerSheet()
		: Sheet(LAYER)
	{
		mStyle = &cls();
		mFrame = make_unique<Layer>(*this, 0);
	}

	Board::Board()
		: Sheet()
	{
		mStyle = &cls();
	}

	WrapSheet::WrapSheet()
		: Sheet()
	{
		mStyle = &cls();
	}

	ScrollSheet::ScrollSheet(FrameType frameType)
		: Sheet(frameType)
		, mScrollArea(this->makeappend<ScrollArea>(*this))
	{
		mStyle = &cls();
		//mScrollbar->hide();
	}

	ScrollSheet::~ScrollSheet()
	{}

	void ScrollSheet::nextFrame(size_t tick, size_t delta)
	{
		if(this->stripe().cursor() > 0.f && this->stripe().sequenceLength() - this->stripe().cursor() < mFrame->dsize(DIM_Y))
			this->stripe().setCursor(this->stripe().sequenceLength() - mFrame->dsize(DIM_Y));

		Sheet::nextFrame(tick, delta);

		if(this->stripe().overflow() && mScrollArea.scrollbar().frame().hidden())
			mScrollArea.scrollbar().show();
		else if(!this->stripe().overflow() && !mScrollArea.scrollbar().frame().hidden())
			mScrollArea.scrollbar().hide();
	}

	void ScrollSheet::clear()
	{
		while(mContents.size() > 1)
		{
			mContents.back()->detach();
			mContents.pop_back();
		}
	}

	bool ScrollSheet::mouseWheel(float xPos, float yPos, float amount)
	{
		UNUSED(xPos); UNUSED(yPos);
		if(!this->stripe().overflow())
			return false;
		if(amount > 0)
			while(amount-- > 0)
				mScrollArea.scrollbar().scrollup();
		else if(amount < 0)
			while(amount++ < 0)
				mScrollArea.scrollbar().scrolldown();
		return true;
	};

	GridSheet::GridSheet(Dimension dim)
		: Sheet()
		, mDim(dim)
		, mResizing(nullptr)
		, mHoverCursor(mDim == DIM_X ? ResizeCursorX::cls() : ResizeCursorY::cls())
	{
		mStyle = &cls();
	}

	bool GridSheet::leftDragStart(float xPos, float yPos)
	{
		float pos = mDim == DIM_X ? xPos : yPos;
		mResizing = nullptr;

		for(Frame* frame : mFrame->as<Stripe>().sequence())
			if(frame->dabsolute(mDim) >= pos)
			{
				mResizing = &frame->widget();
				break;
			}

		return true;
	}

	bool GridSheet::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xPos); UNUSED(yPos);

		if(!mResizing)
			return true;

		Widget& prev = mResizing->prev();
		Widget& next = *mResizing;

		float pixspan = 1.f / mFrame->as<Stripe>().dsize(mDim);
		float offset = mDim == DIM_X ? xDif * pixspan : yDif * pixspan;

		prev.frame().setSpanDim(mDim, std::max(0.01f, prev.frame().dspan(mDim) + offset));
		next.frame().setSpanDim(mDim, std::max(0.01f, next.frame().dspan(mDim) - offset));

		this->gridResized(prev, next);

		return true;
	}

	bool GridSheet::leftDragEnd(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		return true;
	}

	Cursor::Cursor(RootSheet& rootSheet)
		: Widget(LAYER)
		, mTooltip(rootSheet.emplace<Tooltip>(rootSheet, ""))
	{
		mStyle = &cls();
		mFrame = make_unique<Layer>(*this, rootSheet.layer().target()->ztop());

		mHovered = &rootSheet;
	}

	void Cursor::nextFrame()
	{
		if(mTooltipClock.read() > 0.5f && !mTooltip.frame().visible() && !mHovered->tooltip().empty())
			this->tooltipOn();

		if(mDirty)
		{
			mFrame->inkbox().updateFrame();
			mDirty = false;
		}
	}

	void Cursor::setPosition(float x, float y)
	{
		if(!mHovered->frame().inside(x, y))
			this->unhover();

		if(mTooltip.frame().visible())
			this->tooltipOff();
		mTooltipClock.step();
		mFrame->setPosition(x, y);
		mDirty = true;
	}

	void Cursor::tooltipOn()
	{
		mTooltip.setLabel(mHovered->tooltip());
		mTooltip.frame().setPosition(mFrame->dposition(DIM_X), mFrame->dposition(DIM_Y) + mFrame->dsize(DIM_Y));
		mTooltip.show();
	}

	void Cursor::tooltipOff()
	{
		mTooltip.setLabel("");
		mTooltip.hide();
	}

	void Cursor::hover(Widget& widget)
	{
		if(widget.contains(mHovered))
		{
			mUnderHover.push_back(&widget);
			return;
		}

		this->unhover();
		mHovered = &widget;
		if(widget.hoverCursor())
			this->resetSkin(widget.hoverCursor());
	}

	void Cursor::unhover()
	{
		if(mHovered->hoverCursor())
			this->resetSkin(&cls());
		mHovered->unhover();
		mHovered = &this->rootSheet();

		for(Widget* widget : mUnderHover)
			widget->unhover();
		mUnderHover.clear();
	}

	Caret::Caret(Frame* textFrame)
		: Widget()
		, mTextFrame(textFrame)
		, mIndex(0)
		, mDirty(false)
	{
		mStyle = &cls();
	}

	void Caret::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);

		if(mDirty && mTextFrame->inkbox().visible())
		{
			float caretX, caretY, caretHeight;
			mTextFrame->inkbox().caretCoords(mIndex, caretX, caretY, caretHeight);
			mFrame->setPosition(caretX, caretY);
			mFrame->setSize(1.f, caretHeight);
			mDirty = false;
		}
	}

	void Caret::moveRight()
	{
		mIndex = mIndex + 1;
		mTextFrame->inkbox().selectCaret(mIndex);
		mDirty = true;
	}

	void Caret::moveLeft()
	{
		mIndex = mIndex - 1;
		mTextFrame->inkbox().selectCaret(mIndex);
		mDirty = true;
	}

	Tooltip::Tooltip(RootSheet& rootSheet, const string& label)
		: Widget(LAYER)
		, mLabel(label)
	{
		mStyle = &cls();
		mFrame = make_unique<Layer>(*this, rootSheet.layer().target()->ztop()-1);
	}

	Tooltip::~Tooltip()
	{}

	void Tooltip::setLabel(const string& label)
	{
		mLabel = label;
		mFrame->setDirty(Frame::DIRTY_WIDGET);
	}
}
