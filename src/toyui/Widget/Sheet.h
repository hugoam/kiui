//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SHEET_H
#define TOY_SHEET_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Types.h>
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
		Wedge(const Params& params);

		_attr_ _graph_  std::vector<Widget*> m_contents;

		inline size_t count() { return m_contents.size(); }
		inline Widget& at(size_t index) { return *m_contents.at(index); }

		WidgetStore& store() { if(!m_store) m_store = make_unique<WidgetStore>(*this);  return *m_store; }

		virtual void visit(const Visitor& visitor);

		void append(Widget& widget);
		void insert(Widget& widget, size_t index);
		void remove(Widget& widget);
		void clear() { this->store().clear(); m_contents.clear(); }

		void reindex(size_t from);
		void move(size_t from, size_t to);
		void swap(size_t from, size_t to);

		template <class T, class... Args>
		inline T& emplace_style(Style& style, Args&&... args)
		{
			return as<T>(this->store().append(make_object<T>(Params{ this, &style }, std::forward<Args>(args)...)));
		}

		template <class T, class... Args>
		inline T& emplace(Args&&... args)
		{
			return as<T>(this->store().append(make_object<T>(Params{ this }, std::forward<Args>(args)...)));
		}

	protected:
		unique_ptr<WidgetStore> m_store;
	};

	class _refl_ TOY_UI_EXPORT GridSheet : public Wedge
	{
	public:
		using Callback = std::function<void(Frame&, Frame&)>;

	public:
		GridSheet(const Params& params, Dimension dim, Callback callback = nullptr);

		Dimension dim() { return m_dim; }

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);

	protected:
		Dimension m_dim;
		Frame* m_dragPrev;
		Frame* m_dragNext;
		Callback m_onResize;
	};
}

#endif // TOY_SHEET_H
