//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Cursor.h>

#include <toyui/Frame/Caption.h>

#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Cursor::Cursor(RootSheet& rootSheet)
		: Wedge(rootSheet, cls(), LAYER)
		, m_tooltip(rootSheet, "")
	{
		m_hovered = &rootSheet;

		this->tooltipOff();
	}

	void Cursor::nextFrame(size_t tick, size_t delta)
	{
		if(m_tooltipClock.read() > 0.5f && m_tooltip.frame().hidden() && !m_hovered->tooltip().empty())
			this->tooltipOn();
	}

	void Cursor::setPosition(const DimFloat& pos)
	{
		//if(!m_hovered->frame().inside(x, y))
		//	this->unhover();

		if(!m_tooltip.frame().hidden())
			this->tooltipOff();
		m_tooltipClock.step();
		m_frame->setPosition(pos);
	}

	void Cursor::tooltipOn()
	{
		m_tooltip.setContent(m_hovered->tooltip());
		m_tooltip.frame().setPosition({ m_frame->d_position.x(), m_frame->d_position.y() + m_frame->d_size.y() });
		m_tooltip.show();
	}

	void Cursor::tooltipOff()
	{
		m_tooltip.setContent("");
		m_tooltip.hide();
	}

	void Cursor::hover(Widget& widget)
	{
		m_hovered = &widget;
		if(widget.style().skin().m_hoverCursor)
			this->setStyle(*widget.style().skin().m_hoverCursor, false);
	}

	void Cursor::unhover(Widget& widget)
	{
		if(m_hovered == &widget)
			this->unhover();
	}

	void Cursor::unhover()
	{
		this->setStyle(Cursor::cls(), false);
		m_hovered = &this->rootSheet();
	}

	Tooltip::Tooltip(RootSheet& rootSheet, const string& label)
		: Wedge(rootSheet, cls(), LAYER)
	{
		m_frame->setCaption(label);
	}

	Rectangle::Rectangle(Wedge& parent, Type& type)
		: Wedge(parent, type)
	{}
}
