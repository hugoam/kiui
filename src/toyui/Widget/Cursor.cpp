//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Cursor.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/RootSheet.h>

#include <toyobj/Iterable/Reverse.h>

namespace toy
{
	Cursor::Cursor(RootSheet& rootSheet)
		: Decal(rootSheet, cls())
		, m_tooltip(rootSheet, "")
	{
		m_hovered = &rootSheet;

		this->tooltipOff();
	}

	void Cursor::nextFrame(size_t tick, size_t delta)
	{
		Wedge::nextFrame(tick, delta);

		if(m_tooltipClock.read() > 0.5f && m_tooltip.frame().hidden() && !m_hovered->tooltip().empty())
			this->tooltipOn();
	}

	void Cursor::setPosition(float x, float y)
	{
		if(!m_hovered->frame().inside(x, y))
			this->unhover();

		if(!m_tooltip.frame().hidden())
			this->tooltipOff();
		m_tooltipClock.step();
		m_frame->setPosition(x, y);
	}

	void Cursor::tooltipOn()
	{
		m_tooltip.setLabel(m_hovered->tooltip());
		m_tooltip.frame().setPosition(m_frame->dposition(DIM_X), m_frame->dposition(DIM_Y) + m_frame->dsize(DIM_Y));
		m_tooltip.show();
	}

	void Cursor::tooltipOff()
	{
		m_tooltip.setLabel("");
		m_tooltip.hide();
	}

	void Cursor::hover(Widget& widget)
	{
		m_hovered = &widget;
		if(widget.style().skin().hoverCursor())
			this->setStyle(*widget.style().skin().hoverCursor(), false);
	}

	void Cursor::unhover(Widget& widget)
	{
		if(m_hovered = &widget)
			this->unhover();
	}

	void Cursor::unhover()
	{
		this->setStyle(Cursor::cls(), false);
		m_hovered = &this->rootSheet();
	}

	Tooltip::Tooltip(RootSheet& rootSheet, const string& label)
		: Overlay(rootSheet, cls())
	{
		this->content().setText(label);
	}

	void Tooltip::setLabel(const string& label)
	{
		this->content().setText(label);
	}
}
