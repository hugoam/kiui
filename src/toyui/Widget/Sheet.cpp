//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Sheet.h>

#include <toyui/Frame/Frame.h>

#include <toyui/Input/InputDevice.h>

namespace toy
{
	WidgetStore::WidgetStore(Wedge& wedge)
		: m_wedge(wedge)
	{}

	Widget& WidgetStore::append(object_ptr<Widget> pointer)
	{
		Widget& widget = *pointer;
		m_contents.push_back(std::move(pointer));
		widget.setContainer(m_wedge);
		return widget;
	}

	void WidgetStore::remove(Widget& widget)
	{
		m_wedge.destroy(widget);
		vector_remove_pt(m_contents, widget);
	}

	void WidgetStore::transfer(Widget& widget, Wedge& target)
	{
		m_wedge.transfer(widget, target);
		widget.setContainer(target);
		vector_transfer_pt(m_contents, target.store().m_contents, widget);
	}

	void WidgetStore::clear()
	{
		for(auto& widget : reverse_adapt(m_contents))
			m_wedge.destroy(*widget);

		m_contents.clear();
	}

	Wedge::Wedge(Wedge& parent, Type& type, FrameType frameType)
		: Widget(parent, type, frameType)
	{}

	Wedge::Wedge(Type& type, FrameType frameType, Wedge* parent)
		: Widget(type, frameType, parent)
	{}

	void Wedge::visit(const Visitor& visitor, bool post)
	{
		if(!post) if(!visitor(*this)) return;

		for(Widget* pwidget : m_contents)
			pwidget->visit(visitor, post);

		if(post) visitor(*this);
	}

	void Wedge::reindex(size_t from)
	{
		for(size_t i = from; i < m_contents.size(); ++i)
			m_contents[i]->setIndex(i);
		m_frame->markDirty(Frame::DIRTY_STRUCTURE);
	}

	void Wedge::append(Widget& widget)
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

	void Wedge::remove(Widget& widget)
	{
		m_contents.erase(m_contents.begin() + widget.index());
		this->reindex(widget.index());
		widget.unbind();
	}

	void Wedge::destroy(Widget& widget)
	{
		widget.destroyTree();
		this->remove(widget);
	}

	void Wedge::transfer(Widget& widget, Wedge& target)
	{
		this->remove(widget);
		target.append(widget);
	}

	void Wedge::move(size_t from, size_t to)
	{
		m_contents.insert(m_contents.begin() + to, m_contents[from]);
		m_contents.erase(m_contents.begin() + from + 1);
		this->reindex(from < to ? from : to);
	}

	void Wedge::swap(size_t from, size_t to)
	{
		std::iter_swap(m_contents.begin() + from, m_contents.begin() + to);
		this->reindex(from < to ? from : to);
	}

	GridSheet::GridSheet(Wedge& parent, Dimension dim, Callback callback, Type& type)
		: Wedge(parent, type)
		, m_dim(dim)
		, m_dragPrev(nullptr)
		, m_dragNext(nullptr)
		, m_onResize(callback)
	{}

	bool GridSheet::leftDragStart(MouseEvent& mouseEvent)
	{
		// we take the position BEFORE the mouse moved as a reference
		
		DimFloat local = m_frame->derivePosition(mouseEvent.lastPressed);
		float pos = local[m_dim];
		m_dragPrev = nullptr;
		m_dragNext = nullptr;

		for(auto& widget : this->contents())
		{
			if(widget->frame().d_position[m_dim] >= pos)
			{
				m_dragNext = &widget->frame();
				break;
			}
			m_dragPrev = &widget->frame();
		}

		return true;
	}

	bool GridSheet::leftDrag(MouseEvent& mouseEvent)
	{
		if(!m_dragNext || !m_dragPrev)
			return true;

		m_frame->transferPixelSpan(*m_dragPrev, *m_dragNext, mouseEvent.delta[m_dim]);
		if(m_onResize)
			m_onResize(*m_dragPrev, *m_dragNext);
		return true;
	}
}
