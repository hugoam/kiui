//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Scrollbar.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Button/Slider.h>

#include <toyobj/Iterable/Reverse.h>

namespace toy
{
	Scroller::Scroller(Wedge& parent, Dimension dim)
		: Slider(parent, dim, nullptr, cls())
	{
		m_filler.setStyle(Spacer::cls());
		m_button.setStyle(ScrollerKnob::cls());
	}

	void Scroller::sliderStep(float value, bool ended)
	{
		UNUSED(ended);
		m_parent->as<Scrollbar>().scrollTo(value);
	}

	ScrollerKnob::ScrollerKnob(Wedge& parent, Dimension dim)
		: SliderKnob(parent, dim, cls())
	{}

	ScrollForward::ScrollForward(Wedge& parent, const Callback& trigger)
		: Button(parent, "", trigger, cls())
	{}

	ScrollBackward::ScrollBackward(Wedge& parent, const Callback& trigger)
		: Button(parent, "", trigger, cls())
	{}

	Scrollbar::Scrollbar(Wedge& parent, Wedge& frameSheet, Wedge& contentSheet, Dimension dim)
		: Row(parent, cls())
		, m_dim(dim)
		, d_cursor(0.f)
		, m_frameSheet(frameSheet)
		, m_contentSheet(contentSheet)
		, m_up(*this, std::bind(&Scrollbar::scrollup, this))
		, m_scroller(*this, dim)
		, m_down(*this, std::bind(&Scrollbar::scrolldown, this))
	{
		m_frame->setLength(dim);
	}

	Scrollbar::~Scrollbar()
	{}

	float Scrollbar::contentSize()
	{
		return m_contentSheet.frame().dsize(m_dim) * m_contentSheet.frame().scale();
	}

	float Scrollbar::visibleSize()
	{
		return m_frameSheet.frame().dsize(m_dim);
	}

	float Scrollbar::overflow()
	{
		return m_frameSheet.contents().size() > 0 ? contentSize() - visibleSize() : 0.f;
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
		m_contentSheet.frame().setPositionDim(m_dim, -offset);
		m_contentSheet.frame().layer().setForceRedraw();
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
		Wedge::nextFrame(tick, delta);

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
	}
}
