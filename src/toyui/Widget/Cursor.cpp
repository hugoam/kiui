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
		: Wedge({ &rootSheet, &cls<Cursor>(), LAYER })
		, m_hovered(&rootSheet)
		, m_locked(false)
		, m_tooltip(rootSheet, "")
	{
		this->tooltipOff();
	}

	void Cursor::update()
	{
		if(m_tooltipClock.read() > 0.5f && m_tooltip.frame().d_hidden && !m_hovered->tooltip().empty())
			this->tooltipOn();
	}

	void Cursor::setPosition(const DimFloat& pos)
	{
		if(!m_tooltip.frame().d_hidden)
			this->tooltipOff();
		m_tooltipClock.step();
		m_frame->setPosition(pos);
	}

	void Cursor::tooltipOn()
	{
		m_tooltip.setContent(m_hovered->tooltip());
		m_tooltip.frame().setPosition({ m_frame->d_position.x, m_frame->d_position.y + m_frame->m_size.y });
		m_tooltip.show();
	}

	void Cursor::tooltipOff()
	{
		m_tooltip.setContent("");
		m_tooltip.hide();
	}

	void Cursor::hover(Widget& widget)
	{
		if(m_locked) return;
		m_hovered = &widget;
		this->setStyle(widget.m_style->m_skin.m_hover_cursor ? *widget.m_style->m_skin.m_hover_cursor : styles().cursor, false);
	}

	void Cursor::unhover(Widget& widget)
	{
		if(m_hovered == &widget)
			this->unhover();
	}

	void Cursor::unhover()
	{
		if(m_locked) return;
		this->setStyle(styles().cursor, false);
		m_hovered = &this->rootSheet();
	}

	Tooltip::Tooltip(RootSheet& rootSheet, const string& label)
		: Wedge({ &rootSheet, &cls<Tooltip>(), LAYER })
	{
		m_frame->setCaption(label);
	}

	Rectangle::Rectangle(const Params& params)
		: Wedge({ params, &cls<Rectangle>() })
	{}
}
