//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Sheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Grid.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Button/Scrollbar.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/UiLayout.h>

#include <toyobj/Iterable/Reverse.h>

namespace toy
{
	Wedge::Wedge(Wedge& parent, Type& type, FrameType frameType)
		: Widget(parent, type, frameType)
	{}

	Wedge::Wedge(Type& type, FrameType frameType)
		: Widget(type, frameType)
	{}

	Wedge::~Wedge()
	{}

	void Wedge::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);

		for(size_t i = 0; i < m_contents.size(); ++i)
			m_contents[i]->nextFrame(tick, delta);
	}

	void Wedge::render(Renderer& renderer, bool force)
	{
		if(m_frame->layer().forceRedraw())
			force = true;

		m_frame->content().beginDraw(renderer, force);
		m_frame->content().draw(renderer, force);

		for(size_t i = 0; i < m_contents.size(); ++i)
			if(!m_contents[i]->frame().hidden())
				m_contents[i]->render(renderer, force);

		m_frame->content().endDraw(renderer);
	}

	void Wedge::visit(const Visitor& visitor)
	{
		bool pursue = visitor(*this);
		if(!pursue)
			return;

		for(Widget* pwidget : m_contents)
			pwidget->visit(visitor);
	}

	void Wedge::reindex(size_t from)
	{
		for(size_t i = from; i < m_contents.size(); ++i)
			m_contents[i]->setIndex(i);
	}

	void Wedge::push(Widget& widget, bool deferred)
	{
		m_contents.push_back(&widget);
		widget.bind(*this, m_contents.size() - 1, deferred);
	}

	void Wedge::remove(Widget& widget)
	{
		size_t index = widget.index();
		m_contents.erase(m_contents.begin() + index);
		widget.unbind();
		this->reindex(index);
	}

	void Wedge::swap(size_t from, size_t to)
	{
		std::iter_swap(m_contents.begin() + from, m_contents.begin() + to);
		this->reindex(from < to ? from : to);
		m_frame->markDirty(Frame::DIRTY_MAPPING);
	}

	Container::Container(Wedge& parent, Type& type, FrameType frameType)
		: Wedge(parent, type, frameType)
	{}

	Container::Container(Type& type, FrameType frameType)
		: Wedge(type, frameType)
	{}

	Container::~Container()
	{}

	Widget& Container::append(unique_ptr<Widget> unique)
	{
		return this->insert(std::move(unique), m_containerContents.size());
	}

	Widget& Container::insert(unique_ptr<Widget> unique, size_t index)
	{
		Widget& widget = *unique;
		if(widget.parent() == nullptr)
			this->push(widget, false);
		widget.setContainer(*this);
		m_containerContents.insert(m_containerContents.begin() + index, std::move(unique));
		this->handleAdd(widget);
		return widget;
	}

	unique_ptr<Widget> Container::release(Widget& widget)
	{
		widget.parent()->remove(widget);
		auto pos = std::find_if(m_containerContents.begin(), m_containerContents.end(), [&widget](auto& pt) { return pt.get() == &widget; });
		unique_ptr<Widget> pointer = std::move(*pos);
		m_containerContents.erase(pos);
		this->handleRemove(widget);
		return pointer;
	}

	void Container::clear()
	{
		for(auto& widget : m_containerContents)
			widget->parent()->remove(*widget);

		m_containerContents.clear();
	}

	WrapControl::WrapControl(Wedge& parent, Type& type)
		: Container(parent, type)
	{}

	Spacer::Spacer(Wedge& parent, Type& type)
		: Widget(parent, type)
	{}

	Filler::Filler(Wedge& parent)
		: Spacer(parent, cls())
	{}

	Decal::Decal(Wedge& parent, Type& type)
		: Wedge(parent, type, LAYER)
	{}

	Overlay::Overlay(Wedge& parent, Type& type)
		: Container(parent, type, LAYER)
	{}

	GridSheet::GridSheet(Wedge& parent, Dimension dim, Type& type)
		: Container(parent, type)
		, m_dim(dim)
		, m_resizing(nullptr)
	{}

	void GridSheet::leftDragStart(MouseEvent& mouseEvent)
	{
		// we take the position BEFORE the mouse moved as a reference
		float pos = m_dim == DIM_X ? mouseEvent.lastPressedX : mouseEvent.lastPressedY;
		m_resizing = nullptr;

		for(Frame* frame : m_frame->as<Stripe>().sequence())
			if(frame->absolutePosition()[m_dim] >= pos)
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
