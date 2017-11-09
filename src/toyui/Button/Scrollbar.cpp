//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Scrollbar.h>

#include <toyui/Frame/Layer.h>

namespace toy
{
	Scrollbar::Scrollbar(Wedge& parent, Wedge& frameSheet, Wedge& contentSheet, Dimension dim)
		: Wedge(parent, cls())
		, m_dim(dim)
		, m_frameSheet(frameSheet)
		, m_contentSheet(contentSheet)
		, m_rewind(*this, "", [this](Widget&) { this->scrollup(); }, dim == DIM_Y ? ScrollUp() : ScrollLeft())
		, m_scroller(*this, dim, [this](Widget& widget) { this->scrollTo(widget.as<Slider>().val()); }, true, Scroller())
		, m_seek(*this, "", [this](Widget&) { this->scrolldown(); }, dim == DIM_Y ? ScrollDown() : ScrollRight())
	{
		m_frame->d_length = dim;

		m_scroller.m_filler.setStyle(Item::Spacer());
		m_scroller.m_button.setStyle(Scrollbar::Knob());
	}

	float Scrollbar::nextOffset(Widget& widget, Dimension dim, float pos)
	{
		pos -= widget.frame().d_position[dim];

		if(widget.isa<Wedge>())
			for(Widget* child : widget.as<Wedge>().m_contents)
				if(child->frame().flow() && child->frame().d_position[dim] + child->frame().d_size[dim] > pos)
					return widget.frame().d_position[dim] + this->nextOffset(*child, dim, pos);

		return widget.frame().d_position[dim] + widget.frame().d_size[dim];
	}

	float Scrollbar::prevOffset(Widget& widget, Dimension dim, float pos)
	{
		pos -= widget.frame().d_position[dim];

		if(widget.isa<Wedge>())
			for(Widget* child : reverse_adapt(widget.as<Wedge>().m_contents))
				if(child->frame().flow() && child->frame().d_position[dim] < pos)
					return widget.frame().d_position[dim] + this->prevOffset(*child, dim, pos);

		return widget.frame().d_position[dim];
	}

	void Scrollbar::scrollup()
	{
		float pos = this->prevOffset(m_frameSheet, m_dim, -10.f);
		this->scrollTo(std::max(0.f, this->cursor() + pos));
	}

	void Scrollbar::scrolldown()
	{
		float pos = this->nextOffset(m_frameSheet, m_dim, 10.f);
		this->scrollTo(std::min(this->overflow(), this->cursor() + pos));
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
				this->scrollup();
		else if(amount < 0)
			while(amount++ < 0)
				this->scrolldown();
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
