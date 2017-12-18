//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Scrollbar.h>

#include <toyui/Frame/Layer.h>

namespace toy
{
	Scrollbar::Scrollbar(const Params& params, Wedge& frameSheet, Wedge& contentSheet, Dimension dim)
		: Wedge({ params, &cls<Scrollbar>() })
		, m_dim(dim)
		, m_frameSheet(frameSheet)
		, m_contentSheet(contentSheet)
		, m_rewind({ this, dim == DIM_Y ? &styles().scroll_up : &styles().scroll_left }, "", [&](Widget&) { this->scrollforward(); })
		, m_scroller({ this, &styles().scroller }, dim, [&](Widget& widget) { this->scrollTo(as<Slider>(widget).val()); }, true)
		, m_seek({ this, dim == DIM_Y ? &styles().scroll_down : &styles().scroll_right }, "", [&](Widget&) { this->scrollback(); })
	{
		m_frame->d_length = dim;

		m_scroller.m_filler.setStyle(Widget::styles().spacer);
		m_scroller.m_button.setStyle(styles().scroller_knob);
	}

	float Scrollbar::nextOffset(Widget& widget, Dimension dim, float pos)
	{
		pos -= widget.frame().d_position[dim];

		if(is<Wedge>(widget))
			for(Widget* child : as<Wedge>(widget).m_contents)
				if(child->frame().flow() && child->frame().d_position[dim] + child->frame().m_size[dim] > pos)
					return widget.frame().d_position[dim] + this->nextOffset(*child, dim, pos);

		return widget.frame().d_position[dim] + widget.frame().m_size[dim];
	}

	float Scrollbar::prevOffset(Widget& widget, Dimension dim, float pos)
	{
		pos -= widget.frame().d_position[dim];

		if(is<Wedge>(widget))
			for(Widget* child : reverse_adapt(as<Wedge>(widget).m_contents))
				if(child->frame().flow() && child->frame().d_position[dim] < pos)
					return widget.frame().d_position[dim] + this->prevOffset(*child, dim, pos);

		return widget.frame().d_position[dim];
	}

	void Scrollbar::scrollforward()
	{
		float pos = this->nextOffset(m_frameSheet, m_dim, 10.f);
		this->scrollTo(std::min(this->overflow(), this->cursor() + pos));
	}

	void Scrollbar::scrollback()
	{
		float pos = this->prevOffset(m_frameSheet, m_dim, -10.f);
		this->scrollTo(std::max(0.f, this->cursor() + pos));
	}

	void Scrollbar::scrollTo(float offset)
	{
		m_contentSheet.frame().setPositionDim(m_dim, -offset);
		m_contentSheet.frame().layer().setForceRedraw();
	}

	void Scrollbar::scroll(float amount)
	{
		if(!this->overflow())
			return;

		if(amount > 0)
			while(amount-- > 0)
				this->scrollforward();
		else if(amount < 0)
			while(amount++ < 0)
				this->scrollback();
	}

	void Scrollbar::update()
	{
		float visibleSize = this->visibleSize();
		float contentSize = this->contentSize();
		float overflow = this->overflow();
		float cursor = this->cursor();

		m_scroller.updateMetrics(0.f, overflow, cursor, 1.f, visibleSize);

		if(cursor > 0.f && contentSize - cursor < visibleSize)
			this->scrollTo(std::max(contentSize - visibleSize, 0.f));

		if(overflow > 0.f && m_frame->d_hidden)
			this->show();
		else if(overflow <= 0.f && !m_frame->d_hidden)
			this->hide();
	}
}
