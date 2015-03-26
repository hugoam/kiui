//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWScrollbar.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/mkUiWindow.h>

#include <Ui/Widget/mkWSlider.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	WScroller::WScroller(Dimension dim)
		: WSlider(dim, styleCls())
	{}

	WScrollerX::WScrollerX()
		: WScroller(DIM_X)
	{}

	void WScrollerX::build()
	{
		mSpaceBefore = this->makeappend<WSpacerX>();
		mButton = this->makeappend<WScrollerKnobY>();
		mSpaceAfter = this->makeappend<WSpacerX>();

		WSlider::build();
	}

	WScrollerY::WScrollerY()
		: WScroller(DIM_Y)
	{}

	void WScrollerY::build()
	{
		mSpaceBefore = this->makeappend<WSpacerY>();
		mButton = this->makeappend<WScrollerKnobY>();
		mSpaceAfter = this->makeappend<WSpacerY>();

		WSlider::build();
	}

	WScrollerKnobX::WScrollerKnobX()
		: WSliderKnob(DIM_X, styleCls())
	{}

	WScrollerKnobY::WScrollerKnobY()
		: WSliderKnob(DIM_Y, styleCls())
	{}

	WScrollUp::WScrollUp(const Trigger& trigger)
		: WButton("", styleCls(), trigger)
	{}

	WScrollDown::WScrollDown(const Trigger& trigger)
		: WButton("", styleCls(), trigger)
	{}

	void WScroller::sliderStep(float value, bool ended)
	{
		UNUSED(ended);
		mParent->as<WScrollbar>()->scroll(value);
	}

	WScrollbar::WScrollbar(Stripe* sheet)
		: Sheet(styleCls())
		, mSheet(sheet)
	{}

	WScrollbar::~WScrollbar()
	{}

	void WScrollbar::build()
	{
		Sheet::build();
		mUp = this->makeappend<WScrollUp>(std::bind(&WScrollbar::scrollup, this));
		mScroller = this->makeappend<WScrollerY>();
		mDown = this->makeappend<WScrollDown>(std::bind(&WScrollbar::scrolldown, this));

		mScroller->resetMetrics(0.f, mSheet->sequenceLength() - mSheet->dclipsize(DIM_Y), mSheet->cursor(), 1.f, mSheet->dclipsize(DIM_Y));
	}

	void WScrollbar::show()
	{
		Widget::show();
	}

	void WScrollbar::hide()
	{
		Widget::hide();
		mSheet->setCursor(0.f);
	}

	void WScrollbar::scrollup()
	{

	}

	void WScrollbar::scrolldown()
	{

	}

	void WScrollbar::scroll(float offset)
	{
		mSheet->setCursor(offset);
	}

	void WScrollbar::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);

		mScroller->updateMetrics(0.f, mSheet->sequenceLength() - mSheet->dclipsize(DIM_Y), mSheet->cursor(), 1.f, mSheet->dclipsize(DIM_Y));
	}

	WScrollSheet::WScrollSheet()
		: Sheet(styleCls())
	{}
}
