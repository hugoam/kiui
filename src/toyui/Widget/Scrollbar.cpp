//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Scrollbar.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Widget/Slider.h>

#include <toyobj/Iterable/Reverse.h>

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

	ScrollLeft::ScrollLeft(const Trigger& trigger)
		: Button("", trigger, cls())
	{}

	ScrollRight::ScrollRight(const Trigger& trigger)
		: Button("", trigger, cls())
	{}

	void Scroller::sliderStep(float value, bool ended)
	{
		UNUSED(ended);
		m_parent->as<Scrollbar>().scrollTo(value);
	}

	Scrollbar::Scrollbar(Sheet& frameSheet, Dimension dim, StyleType& type)
		: Sheet(type)
		, m_dim(dim)
		, d_cursor(0.f)
		, m_frameSheet(frameSheet)
		, m_up(dim == DIM_X ? (Button&) this->makeappend<ScrollLeft>(std::bind(&Scrollbar::scrollup, this))
									  : this->makeappend<ScrollUp>(std::bind(&Scrollbar::scrollup, this)))
		, m_scroller(dim == DIM_X ? (Scroller&) this->makeappend<ScrollerX>() : (Scroller&) this->makeappend<ScrollerY>())
		, m_down(dim == DIM_X ? (Button&) this->makeappend<ScrollRight>(std::bind(&Scrollbar::scrolldown, this))
										: this->makeappend<ScrollDown>(std::bind(&Scrollbar::scrolldown, this)))
	{}

	Scrollbar::~Scrollbar()
	{}

	float Scrollbar::contentSize()
	{
		Sheet& contentSheet = m_frameSheet.contents()[0]->as<Sheet>();
		return contentSheet.frame().dsize(m_dim);
	}

	float Scrollbar::visibleSize()
	{
		return m_frameSheet.frame().dsize(m_dim);
	}

	float Scrollbar::overflow()
	{
		return m_frameSheet.contents().size() != 0 ? contentSize() - visibleSize() : 0.f;
	}

	void Scrollbar::scrollup()
	{
		float pos = m_frameSheet.stripe().prevOffset(m_dim, -10.f);
		this->scrollTo(std::max(0.f, d_cursor + pos));
	}

	void Scrollbar::scrolldown()
	{
		float pos = m_frameSheet.stripe().nextOffset(m_dim, 10.f);
		this->scrollTo(std::min(this->overflow(), d_cursor + pos));
	}

	void Scrollbar::scrollTo(float offset)
	{
		d_cursor = offset;
		Sheet& contentSheet = m_frameSheet.contents()[0]->as<Sheet>();
		contentSheet.frame().setPositionDim(m_dim, -offset);
	}

	void Scrollbar::scroll(float amount)
	{
		if(!this->overflow())
			return;

		if(amount > 0)
			while(amount-- > 0)
				this->scrollup();
		else if(amount < 0)
			while(amount++ < 0)
				this->scrolldown();
	}

	void Scrollbar::nextFrame(size_t tick, size_t delta)
	{
		float visibleSize = this->visibleSize();
		float contentSize = this->contentSize();
		float overflow = this->overflow();

		m_scroller.updateMetrics(0.f, overflow, d_cursor, 1.f, visibleSize);

		if(d_cursor > 0.f && contentSize - d_cursor < visibleSize)
			this->scrollTo(std::max(contentSize - visibleSize, 0.f));

		if(overflow > 0.f && m_frame->hidden())
			this->show();
		else if(overflow <= 0.f && !m_frame->hidden())
			this->hide();

		Sheet::nextFrame(tick, delta);
	}

	ScrollbarX::ScrollbarX(Sheet& frameSheet)
		: Scrollbar(frameSheet, DIM_X, cls())
	{}

	ScrollbarY::ScrollbarY(Sheet& frameSheet)
		: Scrollbar(frameSheet, DIM_Y, cls())
	{}
}
