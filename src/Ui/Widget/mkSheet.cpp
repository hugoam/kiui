//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkSheet.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Widget/mkScrollbar.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/mkUiLayout.h>

#include <Object/Iterable/mkReverse.h>

#include <iostream>

namespace mk
{
	Sheet::Sheet(StyleType& type, FrameType frameType)
		: Widget(type, frameType)
	{}

	Sheet::~Sheet()
	{}

	/*unique_ptr<Sheet> Sheet::copy()
	{
		unique_ptr<Sheet> copy = this->clone();

		for(size_t i = 0; i < m_contents.size(); ++i)
			copy->append(m_contents[i]->clone());

		return copy;
	}*/

	void Sheet::bind(Sheet& parent, size_t index)
	{
		Widget::bind(parent, index);

		for(size_t i = 0; i < m_contents.size(); ++i)
			m_contents[i]->bind(*this, i);
	}

	void Sheet::rebind(Sheet& parent, size_t index)
	{
		Widget::rebind(parent, index);

		//for(size_t i = 0; i < m_contents.size(); ++i)
		//	m_contents[i]->rebind(this, i);
	}

	Widget& Sheet::append(unique_ptr<Widget> unique)
	{
		return this->insert(std::move(unique), m_contents.size());
	}

	Widget& Sheet::insert(unique_ptr<Widget> unique, size_t index)
	{
		Widget& widget = *unique;
		m_contents.insert(m_contents.begin() + index, std::move(unique));
		if(m_state & BOUND)
			widget.parent() ? widget.rebind(*this, index) : widget.bind(*this, index);
		return widget;
	}

	unique_ptr<Widget> Sheet::release(Widget& widget)
	{
		widget.detach();

		size_t pos = 0;
		while(m_contents[pos].get() != &widget)
			++pos;

		unique_ptr<Widget> pointer = std::move(m_contents[pos]);
		m_contents.erase(m_contents.begin() + pos);
		return pointer;
	}

	unique_ptr<Widget> Sheet::release(size_t index)
	{
		m_contents.at(index)->detach();

		unique_ptr<Widget> pointer = std::move(m_contents[index]);
		m_contents.erase(m_contents.begin() + index);
		return pointer;
	}

	void Sheet::clear()
	{
		for(auto& widget : m_contents)
			widget->detach();

		m_contents.clear();
	}

	void Sheet::cleanup()
	{
		Widget::cleanup();

		//for(auto& widget : m_contents)
		//	widget->cleanup();
	}

	void Sheet::swap(size_t from, size_t to)
	{
		std::iter_swap(m_contents.begin() + from, m_contents.begin() + to);
	}

	LayerSheet::LayerSheet(StyleType& type)
		: Sheet(type, LAYER)
	{
		m_frame = make_unique<Layer>(*this, 0);
	}

	Board::Board(StyleType& type)
		: Sheet(type)
	{}

	WrapSheet::WrapSheet(StyleType& type)
		: Sheet(type)
	{}

	ScrollSheet::ScrollSheet(StyleType& type, FrameType frameType)
		: Sheet(type, frameType)
		, m_scrollArea(this->makeappend<ScrollArea>(*this))
	{}

	ScrollSheet::~ScrollSheet()
	{}

	void ScrollSheet::nextFrame(size_t tick, size_t delta)
	{
		if(this->stripe().cursor() > 0.f && this->stripe().sequenceLength() - this->stripe().cursor() < m_frame->dsize(DIM_Y))
			this->stripe().setCursor(this->stripe().sequenceLength() - m_frame->dsize(DIM_Y));

		//Sheet::nextFrame(tick, delta);

		if(this->stripe().overflow() && m_scrollArea.scrollbar().frame().hidden())
			m_scrollArea.scrollbar().show();
		else if(!this->stripe().overflow() && !m_scrollArea.scrollbar().frame().hidden())
			m_scrollArea.scrollbar().hide();
	}

	void ScrollSheet::clear()
	{
		while(m_contents.size() > 1)
		{
			m_contents.back()->detach();
			m_contents.pop_back();
		}
	}

	void ScrollSheet::mouseWheel(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(!this->stripe().overflow())
			return;

		float amount = mouseEvent.deltaY;

		if(amount > 0)
			while(amount-- > 0)
				m_scrollArea.scrollbar().scrollup();
		else if(amount < 0)
			while(amount++ < 0)
				m_scrollArea.scrollbar().scrolldown();

		mouseEvent.consumed = true;
	};

	GridSheet::GridSheet(Dimension dim, StyleType& type)
		: Sheet(type)
		, m_dim(dim)
		, m_resizing(nullptr)
		, m_hoverCursor(m_dim == DIM_X ? ResizeCursorX::cls() : ResizeCursorY::cls())
	{}

	void GridSheet::leftDragStart(MouseEvent& mouseEvent)
	{
		float pos = m_dim == DIM_X ? mouseEvent.posX : mouseEvent.posY;
		m_resizing = nullptr;

		for(Frame* frame : m_frame->as<Stripe>().sequence())
			if(frame->dabsolute(m_dim) >= pos)
			{
				m_resizing = &frame->widget();
				break;
			}
	}

	void GridSheet::leftDrag(MouseEvent& mouseEvent)
	{
		if(!m_resizing || m_resizing->frame().first())
			return;

		Widget& prev = m_resizing->prev();
		Widget& next = *m_resizing;

		float pixspan = 1.f / m_frame->as<Stripe>().dsize(m_dim);
		float offset = m_dim == DIM_X ? mouseEvent.deltaX * pixspan : mouseEvent.deltaY * pixspan;

		prev.frame().setSpanDim(m_dim, std::max(0.01f, prev.frame().dspan(m_dim) + offset));
		next.frame().setSpanDim(m_dim, std::max(0.01f, next.frame().dspan(m_dim) - offset));

		this->gridResized(prev, next);
	}

	void GridSheet::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
	}

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
		if(m_tooltipClock.read() > 0.5f && !m_tooltip.frame().visible() && !m_hovered->tooltip().empty())
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

		if(m_tooltip.frame().visible())
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

	Caret::Caret(Frame* textFrame)
		: Widget(cls())
		, m_textFrame(textFrame)
		, m_index(0)
		, m_dirty(false)
	{}

	void Caret::nextFrame(size_t tick, size_t delta)
	{
		//Widget::nextFrame(tick, delta);

		if(m_dirty && m_textFrame->visible())
		{
			float caretX, caretY, caretHeight;
			m_textFrame->caption().caretCoords(m_index, caretX, caretY, caretHeight);
			m_frame->setPosition(caretX, caretY);
			m_frame->setSize(1.f, caretHeight);
			m_dirty = false;
		}
	}

	void Caret::moveRight()
	{
		m_index = m_index + 1;
		m_textFrame->caption().selectCaret(m_index);
		m_dirty = true;
	}

	void Caret::moveLeft()
	{
		m_index = m_index - 1;
		m_textFrame->caption().selectCaret(m_index);
		m_dirty = true;
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
