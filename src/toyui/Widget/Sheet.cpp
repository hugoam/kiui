//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Sheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Grid.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/Widgets.h>

#include <toyui/Widget/Scrollbar.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/UiLayout.h>

#include <toyobj/Iterable/Reverse.h>

namespace toy
{
	Sheet::Sheet(StyleType& type, FrameType frameType)
		: Widget(type, frameType)
	{}

	Sheet::~Sheet()
	{}

	void Sheet::reindex(size_t from)
	{
		for(size_t i = from; i < m_contents.size(); ++i)
			m_contents[i]->setIndex(i);
	}

	void Sheet::bindChild(Widget& child, size_t index)
	{
		child.bind(*this, index);

		this->stripe().remap();
	}

	void Sheet::unbindChild(Widget& child)
	{
		child.unbind();

		this->stripe().remap();
	}

	void Sheet::bind(Sheet& parent, size_t index)
	{
		Widget::bind(parent, index);

		for(size_t i = 0; i < m_contents.size(); ++i)
			this->bindChild(*m_contents[i], i);
	}

	void Sheet::unbind()
	{
		for(int i = m_contents.size() - 1; i >= 0; --i)
			this->unbindChild(*m_contents[i]);

		Widget::unbind();
	}

	void Sheet::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);

		for(size_t i = 0; i < m_contents.size(); ++i)
			m_contents[i]->nextFrame(tick, delta);
	}

	void Sheet::render(Renderer& renderer)
	{
		m_frame->content().beginDraw(renderer);
		m_frame->content().draw(renderer);

		for(size_t i = 0; i < m_contents.size(); ++i)
			if(!m_contents[i]->frame().hidden())
				m_contents[i]->render(renderer);

		m_frame->content().endDraw(renderer);
	}

	Widget& Sheet::append(unique_ptr<Widget> unique)
	{
		return this->insert(std::move(unique), m_contents.size());
	}

	Widget& Sheet::insert(unique_ptr<Widget> unique, size_t index)
	{
		Widget& widget = *unique;
		m_contents.insert(m_contents.begin() + index, std::move(unique));
		this->reindex(index);
		if(m_state & BOUND)
			this->bindChild(widget, index);
		return widget;
	}

	unique_ptr<Widget> Sheet::release(Widget& widget)
	{
		return this->release(widget.index());
	}

	unique_ptr<Widget> Sheet::release(size_t index)
	{
		m_contents[index]->unbind();
		unique_ptr<Widget> pointer = std::move(m_contents[index]);
		m_contents.erase(m_contents.begin() + index);
		this->reindex(index);
		return pointer;
	}

	void Sheet::clear()
	{
		for(auto& widget : m_contents)
			widget->unbind();

		m_contents.clear();
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

	ScrollZone::ScrollZone()
		: Sheet(cls())
	{}

	ScrollSheet::ScrollSheet(StyleType& type)
		: Sheet(type, GRID)
		, m_scrollzone(this->makeappend<ScrollZone>())
		, m_scrollbarX(this->makeappend<ScrollbarX>(m_scrollzone))
		, m_scrollbarY(this->makeappend<ScrollbarY>(m_scrollzone))
	{
		m_scrollzone.frame().setIndex(0, 0);
		m_scrollbarY.frame().setIndex(1, 0);
		m_scrollbarX.frame().setIndex(0, 1);
	}

	ScrollSheet::~ScrollSheet()
	{}

	void ScrollSheet::bound()
	{
		m_frame->as<Grid>().resize(2);
		m_frame->as<Grid>().line(0).setSizing(EXPAND, EXPAND);
		m_frame->as<Grid>().line(1).setSizing(EXPAND, SHRINK);
	}

	Widget& ScrollSheet::vappend(unique_ptr<Widget> widget)
	{
		return m_scrollzone.vappend(std::move(widget));
	}

	unique_ptr<Widget> ScrollSheet::vrelease(Widget& widget)
	{
		return m_scrollzone.vrelease(widget);
	}

	void ScrollSheet::clear()
	{
		m_scrollzone.clear();
	}

	void ScrollSheet::mouseWheel(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_scrollbarX.scroll(mouseEvent.deltaX);
		m_scrollbarY.scroll(mouseEvent.deltaY);

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
		// we take the position BEFORE the mouse moved as a reference
		float pos = m_dim == DIM_X ? mouseEvent.lastPressedX : mouseEvent.lastPressedY;
		m_resizing = nullptr;

		for(Frame* frame : m_frame->as<Stripe>().sequence())
			if(frame->dabsolute(m_dim) >= pos)
			{
				m_resizing = frame->widget();
				break;
			}
	}

	void GridSheet::leftDrag(MouseEvent& mouseEvent)
	{
		if(!m_resizing || !this->stripe().before(m_resizing->frame()))
			return;

		Frame& prev = this->stripe().prev(m_resizing->frame());
		Frame& next = m_resizing->frame();

		float pixspan = 1.f / m_frame->as<Stripe>().dsize(m_dim);
		float offset = m_dim == DIM_X ? mouseEvent.deltaX * pixspan : mouseEvent.deltaY * pixspan;

		prev.setSpanDim(m_dim, std::max(0.01f, prev.dspan(m_dim) + offset));
		next.setSpanDim(m_dim, std::max(0.01f, next.dspan(m_dim) - offset));

		this->gridResized(prev, next);
	}

	void GridSheet::leftDragEnd(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
	}
}
