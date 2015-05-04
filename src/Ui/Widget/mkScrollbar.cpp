//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkScrollbar.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/mkUiWindow.h>

#include <Ui/Widget/mkSlider.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	Scroller::Scroller(Dimension dim)
		: Slider(dim)
	{
		mStyle = &cls();
	}

	ScrollerX::ScrollerX()
		: Scroller(DIM_X)
	{
		mStyle = &cls();
	}

	ScrollerY::ScrollerY()
		: Scroller(DIM_Y)
	{
		mStyle = &cls();
	}

	ScrollerKnob::ScrollerKnob(Dimension dim)
		: SliderKnob(dim)
	{
		mStyle = &cls();
	}

	ScrollerKnobX::ScrollerKnobX()
		: ScrollerKnob(DIM_X)
	{
		mStyle = &cls();
	}

	ScrollerKnobY::ScrollerKnobY()
		: ScrollerKnob(DIM_Y)
	{
		mStyle = &cls();
	}

	ScrollUp::ScrollUp(const Trigger& trigger)
		: Button("", trigger)
	{
		mStyle = &cls();
	}

	ScrollDown::ScrollDown(const Trigger& trigger)
		: Button("", trigger)
	{
		mStyle = &cls();
	}

	void Scroller::sliderStep(float value, bool ended)
	{
		UNUSED(ended);
		mParent->as<Scrollbar>().scroll(value);
	}

	Scrollbar::Scrollbar(Sheet& sheet)
		: Sheet()
		, mSheet(sheet)
		, mUp(this->makeappend<ScrollUp>(std::bind(&Scrollbar::scrollup, this)))
		, mScroller(this->makeappend<ScrollerY>())
		, mDown(this->makeappend<ScrollDown>(std::bind(&Scrollbar::scrolldown, this)))
	{
		mStyle = &cls();
	}

	Scrollbar::~Scrollbar()
	{}

	void Scrollbar::show()
	{
		Widget::show();
	}

	void Scrollbar::hide()
	{
		Widget::hide();
		mSheet.stripe().setCursor(0.f);
	}

	void Scrollbar::scrollup()
	{
		mSheet.stripe().cursorUp();
	}

	void Scrollbar::scrolldown()
	{
		mSheet.stripe().cursorDown();
	}

	void Scrollbar::scroll(float offset)
	{
		mSheet.stripe().setCursor(offset);
	}

	void Scrollbar::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);
		Stripe& stripe = mSheet.stripe();
		mScroller.updateMetrics(0.f, stripe.sequenceLength() - stripe.dclipsize(DIM_Y), stripe.cursor(), 1.f, stripe.dclipsize(DIM_Y));
	}

	ScrollArea::ScrollArea(Sheet& sheet)
		: Sheet()
		, mScrollbar(this->emplace<Scrollbar>(sheet))
	{
		mStyle = &cls();
	}
}
