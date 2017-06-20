//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Sheet.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Grid.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Container/Layout.h>

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

	void Wedge::unmap()
	{
		for(size_t i = 0; i < m_contents.size(); ++i)
			this->stripe().unmap(m_contents[i]->frame());
	}

	void Wedge::map()
	{
		for(size_t i = 0; i < m_contents.size(); ++i)
			this->stripe().map(m_contents[i]->frame());
	}

	void Wedge::nextFrame(size_t tick, size_t delta)
	{
		Widget::nextFrame(tick, delta);

		for(size_t i = 0; i < m_contents.size(); ++i)
			m_contents[i]->nextFrame(tick, delta);
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

	void Wedge::push(Widget& widget)
	{
		m_contents.push_back(&widget);
		widget.bind(*this, m_contents.size() - 1);
	}

	void Wedge::insert(Widget& widget, size_t index)
	{
		m_contents.insert(m_contents.begin() + index, &widget);
		widget.bind(*this, index);
		this->reindex(index);
	}

	void Wedge::remove(Widget& widget, bool destroy)
	{
		size_t index = widget.index();
		m_contents.erase(m_contents.begin() + index);
		widget.unbind(destroy);
		this->reindex(index);
	}

	void Wedge::move(size_t from, size_t to)
	{
		this->unmap();
		m_contents.insert(m_contents.begin() + to, m_contents[from]);
		m_contents.erase(m_contents.begin() + from + 1);
		this->reindex(from < to ? from : to);
		this->map();
	}

	void Wedge::swap(size_t from, size_t to)
	{
		this->unmap();
		std::iter_swap(m_contents.begin() + from, m_contents.begin() + to);
		this->reindex(from < to ? from : to);
		this->map();
	}

	Container::Container(Wedge& parent, Type& type, FrameType frameType)
		: Wedge(parent, type, frameType)
		, m_containerTarget(this)
	{}

	Container::Container(Type& type, FrameType frameType)
		: Wedge(type, frameType)
		, m_containerTarget(this)
	{}

	Widget& Container::append(object_ptr<Widget> unique)
	{
		return this->insert(std::move(unique), m_containerContents.size());
	}

	Widget& Container::insert(object_ptr<Widget> unique, size_t index)
	{
		Widget& widget = *unique;
		if(widget.parent() == nullptr)
			m_containerTarget->as<Wedge>().insert(widget, index);
		widget.setContainer(*this);
		m_containerContents.insert(m_containerContents.begin() + index, std::move(unique));
		this->handleAdd(widget);
		return widget;
	}

	object_ptr<Widget> Container::release(Widget& widget, bool destroy)
	{
		widget.parent()->remove(widget, destroy);
		auto pos = std::find_if(m_containerContents.begin(), m_containerContents.end(), [&widget](auto& pt) { return pt.get() == &widget; });
		object_ptr<Widget> pointer = std::move(*pos);
		m_containerContents.erase(pos);
		this->handleRemove(widget);
		return pointer;
	}

	void Container::clear()
	{
		for(auto& widget : m_containerContents)
			widget->parent()->remove(*widget, true);

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
		, m_dragPrev(nullptr)
		, m_dragNext(nullptr)
	{}

	bool GridSheet::leftDragStart(MouseEvent& mouseEvent)
	{
		// we take the position BEFORE the mouse moved as a reference
		float pos = m_dim == DIM_X ? mouseEvent.lastPressedX : mouseEvent.lastPressedY;
		m_dragPrev = nullptr;
		m_dragNext = nullptr;

		for(Frame* frame : this->stripe().sequence())
			if(frame->absolutePosition()[m_dim] >= pos)
			{
				m_dragNext = frame;
				m_dragPrev = this->stripe().before(*m_dragNext);
				break;
			}

		return true;
	}

	bool GridSheet::leftDrag(MouseEvent& mouseEvent)
	{
		if(!m_dragNext || !m_dragPrev)
			return true;

		float amount = m_dim == DIM_X ? mouseEvent.deltaX : mouseEvent.deltaY;
		this->stripe().transferPixelSpan(*m_dragPrev, *m_dragNext, amount);

		this->gridResized(*m_dragPrev, *m_dragNext);

		return true;
	}
}
