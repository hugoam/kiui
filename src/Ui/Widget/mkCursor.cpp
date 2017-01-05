//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkCursor.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkRootSheet.h>

#include <Object/Iterable/mkReverse.h>

namespace mk
{
	Cursor::Cursor(RootSheet& rootSheet)
		: Sheet(cls(), LAYER)
		, m_tooltip(rootSheet.emplace<Tooltip>(rootSheet, ""))
	{
		m_frame = make_unique<Layer>(*this, -1);

		m_hovered = &rootSheet;

		this->tooltipOff();
	}

	void Cursor::nextFrame()
	{
		if(m_tooltipClock.read() > 0.5f && m_tooltip.frame().hidden() && !m_hovered->tooltip().empty())
			this->tooltipOn();

		if(m_dirty)
		{
			//m_frame->stencil().updateFrame();
			m_dirty = false;
		}
	}

	void Cursor::setPosition(float x, float y)
	{
		if(!m_hovered->frame().inside(x, y))
			this->unhover();

		if(!m_tooltip.frame().hidden())
			this->tooltipOff();
		m_tooltipClock.step();
		m_frame->setPosition(x, y);
		m_dirty = true;
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
		this->unhover();
		m_hovered = &widget;
		if(m_hovered->hoverCursor())
			this->resetSkin(*widget.hoverCursor());
	}

	void Cursor::unhover()
	{
		if(m_hovered->hoverCursor())
			this->resetSkin(cls());
		m_hovered = &this->rootSheet();
	}

	Tooltip::Tooltip(RootSheet& rootSheet, const string& label)
		: Widget(cls(), LAYER)
	{
		m_frame = make_unique<Layer>(*this, -2);
		m_frame->setText(label);
	}

	void Tooltip::setLabel(const string& label)
	{
		m_frame->setText(label);
	}
}
