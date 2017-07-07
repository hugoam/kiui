//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SHEET_H
#define TOY_SHEET_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>

namespace toy
{
	class TOY_UI_EXPORT WidgetStore : public Object
	{
	public:
		WidgetStore(Wedge& wedge);

		Widget& append(object_ptr<Widget> widget);
		void remove(Widget& widget);
		void transfer(Widget& widget, Wedge& target);
		void clear();

	protected:
		Wedge& m_wedge;
		std::vector<object_ptr<Widget>> m_contents;
	};

	class _refl_ TOY_UI_EXPORT Wedge : public Widget
	{
	public:
		Wedge(Wedge& parent, Type& type = cls(), FrameType frameType = FRAME);
		Wedge(Type& type = cls(), FrameType frameType = FRAME, Wedge* parent = nullptr);

		_attr_ _graph_ inline std::vector<Widget*>& contents() { return m_contents; }

		inline size_t count() { return m_contents.size(); }
		inline Widget& at(size_t index) { return *m_contents.at(index); }

		WidgetStore& store() { if(!m_store) m_store = make_unique<WidgetStore>(*this);  return *m_store; }

		virtual void visit(const Visitor& visitor);

		void append(Widget& widget);
		void insert(Widget& widget, size_t index);
		void remove(Widget& widget);
		void destroy(Widget& widget);
		void transfer(Widget& widget, Wedge& target);

		void reindex(size_t from);
		void move(size_t from, size_t to);
		void swap(size_t from, size_t to);

		template <class T, class... Args>
		inline T& emplace(Args&&... args)
		{
			return this->store().append(make_object<T>(*this, std::forward<Args>(args)...)).template as<T>();
		}

		static Type& cls() { static Type ty("Wedge", Widget::cls()); return ty; }

		static Type& Board() { static Type ty("Board", Wedge::cls()); return ty; }
		static Type& Layout() { static Type ty("Layout", Wedge::Board()); return ty; }
		static Type& Row() { static Type ty("Row", Wedge::cls()); return ty; }
		static Type& Div() { static Type ty("Div", Wedge::cls()); return ty; }
		static Type& Stack() { static Type ty("Stack", Wedge::cls()); return ty; }
		static Type& Sheet() { static Type ty("Sheet", Wedge::cls()); return ty; }
		static Type& Header() { static Type ty("Header", Wedge::Row()); return ty; }
		static Type& Decal() { static Type ty("Decal", Wedge::cls()); return ty; }
		static Type& Overlay() { static Type ty("Overlay", Wedge::cls()); return ty; }

		static Type& WrapControl() { static Type ty("WrapControl", Wedge::cls()); return ty; }

	protected:
		std::vector<Widget*> m_contents;
		unique_ptr<WidgetStore> m_store;
	};

	class _refl_ TOY_UI_EXPORT GridSheet : public Wedge
	{
	public:
		using Callback = std::function<void(Frame&, Frame&)>;

	public:
		GridSheet(Wedge& parent, Dimension dim, Callback callback = nullptr, Type& type = cls());

		Dimension dim() { return m_dim; }

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("GridSheet", Wedge::cls()); return ty; }

	protected:
		Dimension m_dim;
		Frame* m_dragPrev;
		Frame* m_dragNext;
		Callback m_onResize;
	};
}

#endif // TOY_SHEET_H
