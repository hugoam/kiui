//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkScrollbar.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkSlider.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	Scroller::Scroller(Dimension dim, StyleType& type)
		: Slider(dim, nullptr, type)
	{}

	ScrollerX::ScrollerX()
		: Scroller(DIM_X, cls())
	{}

	ScrollerY::ScrollerY()
		: Scroller(DIM_Y, cls())
	{}

	ScrollerKnob::ScrollerKnob(Dimension dim, StyleType& type)
		: SliderKnob(dim, type)
	{}

	ScrollerKnobX::ScrollerKnobX()
		: ScrollerKnob(DIM_X, cls())
	{}

	ScrollerKnobY::ScrollerKnobY()
		: ScrollerKnob(DIM_Y, cls())
	{}

	ScrollUp::ScrollUp(const Trigger& trigger)
		: Button("", trigger, cls())
	{}

	ScrollDown::ScrollDown(const Trigger& trigger)
		: Button("", trigger, cls())
	{}

	void Scroller::sliderStep(float value, bool ended)
	{
		UNUSED(ended);
		m_parent->as<Scrollbar>().scroll(value);
	}

	Scrollbar::Scrollbar(Sheet& sheet)
		: Sheet(cls())
		, m_sheet(sheet)
		, m_up(this->makeappend<ScrollUp>(std::bind(&Scrollbar::scrollup, this)))
		, m_scroller(this->makeappend<ScrollerY>())
		, m_down(this->makeappend<ScrollDown>(std::bind(&Scrollbar::scrolldown, this)))
	{}

	Scrollbar::~Scrollbar()
	{}

	void Scrollbar::scrollup()
	{
		m_sheet.stripe().cursorUp();
	}

	void Scrollbar::scrolldown()
	{
		m_sheet.stripe().cursorDown();
	}

	void Scrollbar::scroll(float offset)
	{
		m_sheet.stripe().setCursor(offset);
	}

	void Scrollbar::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);
		Stripe& stripe = m_sheet.stripe();
		m_scroller.updateMetrics(0.f, stripe.sequenceLength() - stripe.dclipsize(DIM_Y), stripe.cursor(), 1.f, stripe.dclipsize(DIM_Y));
	}

	ScrollArea::ScrollArea(Sheet& sheet)
		: Sheet(cls())
		, m_scrollbar(this->emplace<Scrollbar>(sheet))
	{}
}
