//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_SHEET_H
#define TOY_SHEET_H

/* toy */
#include <toyobj/Id.h>
#include <toyobj/String/String.h>
#include <toyobj/Util/Updatable.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Frame/Stripe.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Sheet : public Widget
	{
	public:
		Sheet(StyleType& type = cls(), FrameType frameType = STRIPE);
		~Sheet();

		inline Stripe& stripe() { return m_frame->as<Stripe>(); }
		inline const std::vector<unique_ptr<Widget>>& contents() { return m_contents; }
		inline size_t count() { return m_contents.size(); }

		inline Widget& at(size_t index) { return *m_contents.at(index); }

		virtual void cleanup();

		virtual void bind(Sheet& parent, size_t index);
		virtual void rebind(Sheet& parent, size_t index);

		virtual Widget& vappend(unique_ptr<Widget> widget) { return append(std::move(widget)); }
		virtual unique_ptr<Widget> vrelease(Widget& widget) { return widget.unbind(); }

		Widget& insert(unique_ptr<Widget> widget, size_t index);
		Widget& append(unique_ptr<Widget> widget);
		unique_ptr<Widget> release(Widget& widget);
		unique_ptr<Widget> release(size_t index);

		void swap(size_t from, size_t to);

		void clear();

		template <class T, class... Args>
		inline T& emplace(Args&&... args)
		{
			return this->vappend(make_unique<T>(std::forward<Args>(args)...)).template as<T>();
		}

		static StyleType& cls() { static StyleType ty("Sheet", Widget::cls()); return ty; }

	protected:
		template <class T, class... Args>
		inline T& makeappend(Args&&... args)
		{
			return this->append(make_unique<T>(std::forward<Args>(args)...)).template as<T>();
		}

		template <class T, class... Args>
		inline T& makeinsert(size_t index, Args&&... args)
		{
			return this->insert(make_unique<T>(std::forward<Args>(args)...), index).template as<T>();
		}

	protected:
		std::vector<unique_ptr<Widget>> m_contents;
	};

	class _I_ TOY_UI_EXPORT LayerSheet : public Sheet
	{
	public:
		LayerSheet(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("LayerSheet", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Board : public Sheet
	{
	public:
		Board(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("Board", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WrapSheet : public Sheet
	{
	public:
		WrapSheet(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("WrapSheet", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT ScrollSheet : public Sheet
	{
	public:
		ScrollSheet(StyleType& type = cls(), FrameType frameType = STRIPE);
		~ScrollSheet();

		void clear();

		void nextFrame(size_t tick, size_t delta);

		void mouseWheel(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("ScrollSheet", Sheet::cls()); return ty; }

	protected:
		ScrollArea& m_scrollArea;
	};

	class _I_ TOY_UI_EXPORT GridSheet : public Sheet
	{
	public:
		GridSheet(Dimension dim, StyleType& type = cls());

		Style* hoverCursor() { return &m_hoverCursor; }

		void leftDragStart(MouseEvent& mouseEvent);
		void leftDrag(MouseEvent& mouseEvent);
		void leftDragEnd(MouseEvent& mouseEvent);

		virtual void gridResized(Widget& first, Widget& second) { UNUSED(first); UNUSED(second); }

		static StyleType& cls() { static StyleType ty("GridSheet", Sheet::cls()); return ty; }

	protected:
		Dimension m_dim;
		Widget* m_resizing;
		Style& m_hoverCursor;
	};

	class _I_ TOY_UI_EXPORT Band : public Sheet
	{
	public:
		Band(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("Band", Sheet::cls()); return ty; }
	};
}

#endif // TOY_SHEET_H
