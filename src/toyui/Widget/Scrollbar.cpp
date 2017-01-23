//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Scrollbar.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Widget/Slider.h>

#include <toyobj/Iterable/Reverse.h>

#include <iostream>

namespace toy
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

	Scrollbar::Scrollbar(Sheet& sheet, Dimension dim)
		: Sheet(cls())
		, m_dim(dim)
		, m_sheet(sheet)
		, m_up(this->makeappend<ScrollUp>(std::bind(&Scrollbar::scrollup, this)))
		, m_scroller(dim == DIM_X ? (Scroller&) this->makeappend<ScrollerX>() : (Scroller&) this->makeappend<ScrollerY>())
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
		m_sheet.stripe().setCursor(m_dim, offset);
	}

	void Scrollbar::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
		float visibleSize = m_sheet.stripe().dsize(DIM_Y); // stripe.dclipsize(DIM_Y)
		m_scroller.updateMetrics(0.f, m_sheet.stripe().sequenceLength() - visibleSize, m_sheet.stripe().cursor(), 1.f, visibleSize);
	}

	ScrollArea::ScrollArea(Sheet& sheet)
		: Sheet(cls())
		, m_scrollbar(this->emplace<Scrollbar>(sheet))
	{}
}
