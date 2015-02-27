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

#include <Object/Store/mkReverse.h>

#include <iostream>

namespace mk
{
	WScroller::WScroller()
		: WSlider(DIM_Y, "scroller")
	{}

	void WScroller::sliderStep(float value, bool ended)
	{
		UNUSED(ended);
		mParent->as<WScrollbar>()->scroll(value);
	}

	WScrollbar::WScrollbar(Stripe* sheet)
		: Sheet("scrollbar")
		, mSheet(sheet)
	{}

	WScrollbar::~WScrollbar()
	{
		mSheet->setCursor(0.f);
	}

	void WScrollbar::build()
	{
		Sheet::build();
		mUp = this->makeappend<WButton>("", "scrollbutton_up scrollbutton", std::bind(&WScrollbar::scrollup, this));
		mScroller = this->makeappend<WScroller>();
		mDown = this->makeappend<WButton>("", "scrollbutton_down scrollbutton", std::bind(&WScrollbar::scrolldown, this));
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
		Widget::nextFrame(tick, delta);

		mScroller->resetMetrics(0.f, mSheet->sequenceLength() - mSheet->dclipsize(DIM_Y), mSheet->cursor(), 1.f, mSheet->dclipsize(DIM_Y));
	}
}
