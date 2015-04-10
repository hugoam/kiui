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
		: Slider(dim, styleCls())
	{}

	ScrollerX::ScrollerX()
		: Scroller(DIM_X)
	{
		mSpaceBefore = this->makeappend<SpacerX>();
		mButton = this->makeappend<ScrollerKnobY>();
		mSpaceAfter = this->makeappend<SpacerX>();
	}

	ScrollerY::ScrollerY()
		: Scroller(DIM_Y)
	{
		mSpaceBefore = this->makeappend<SpacerY>();
		mButton = this->makeappend<ScrollerKnobY>();
		mSpaceAfter = this->makeappend<SpacerY>();
	}

	ScrollerKnobX::ScrollerKnobX()
		: SliderKnob(DIM_X, styleCls())
	{}

	ScrollerKnobY::ScrollerKnobY()
		: SliderKnob(DIM_Y, styleCls())
	{}

	ScrollUp::ScrollUp(const Trigger& trigger)
		: Button("", styleCls(), trigger)
	{}

	ScrollDown::ScrollDown(const Trigger& trigger)
		: Button("", styleCls(), trigger)
	{}

	void Scroller::sliderStep(float value, bool ended)
	{
		UNUSED(ended);
		mParent->as<Scrollbar>()->scroll(value);
	}

	Scrollbar::Scrollbar(Stripe* sheet)
		: Sheet(styleCls())
		, mSheet(sheet)
	{
		mUp = this->makeappend<ScrollUp>(std::bind(&Scrollbar::scrollup, this));
		mScroller = this->makeappend<ScrollerY>();
		mDown = this->makeappend<ScrollDown>(std::bind(&Scrollbar::scrolldown, this));

		//mScroller->resetMetrics(0.f, mSheet->sequenceLength() - mSheet->dclipsize(DIM_Y), mSheet->cursor(), 1.f, mSheet->dclipsize(DIM_Y));
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
		mSheet->setCursor(0.f);
	}

	void Scrollbar::scrollup()
	{
		mSheet->cursorUp();
	}

	void Scrollbar::scrolldown()
	{
		mSheet->cursorDown();
	}

	void Scrollbar::scroll(float offset)
	{
		mSheet->setCursor(offset);
	}

	void Scrollbar::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);

		mScroller->updateMetrics(0.f, mSheet->sequenceLength() - mSheet->dclipsize(DIM_Y), mSheet->cursor(), 1.f, mSheet->dclipsize(DIM_Y));
	}
}
