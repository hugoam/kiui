//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_SHEET_H_INCLUDED
#define MK_SHEET_H_INCLUDED

/* mk */
#include <Object/mkId.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkStripe.h>

#include <memory>
#include <deque>

namespace mk
{
	class MK_UI_EXPORT _I_ Sheet : public Widget
	{
	public:
		Sheet(StyleType& type = cls(), FrameType frameType = STRIPE);
		~Sheet();

		void nextFrame(size_t tick, size_t delta);

		inline Stripe& stripe() { return m_frame->as<Stripe>(); }
		inline const std::vector<unique_ptr<Widget>>& contents() { return m_contents; }
		inline size_t count() { return m_contents.size(); }

		inline Widget* at(size_t index) { return m_contents.at(index).get(); }

		void bind(Sheet& parent, size_t index);
		void rebind(Sheet& parent, size_t index);

		virtual Widget& vappend(unique_ptr<Widget> widget) { return append(std::move(widget)); }
		virtual unique_ptr<Widget> vrelease(Widget& widget) { return widget.unbind(); }

		Widget& insert(unique_ptr<Widget> widget, size_t index);
		Widget& append(unique_ptr<Widget> widget);
		unique_ptr<Widget> release(Widget& widget);
		unique_ptr<Widget> release(size_t index);

		void swap(size_t from, size_t to);

		void clear();

		void cleanup();

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

	class MK_UI_EXPORT _I_ LayerSheet : public Sheet
	{
	public:
		LayerSheet(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("LayerSheet", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Board : public Sheet
	{
	public:
		Board(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("Board", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ WrapSheet : public Sheet
	{
	public:
		WrapSheet(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("WrapSheet", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ ScrollSheet : public Sheet
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

	class MK_UI_EXPORT GridSheet : public Sheet
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

	class MK_UI_EXPORT _I_ Cursor : public Sheet
	{
	public:
		Cursor(RootSheet& rootSheet);

		void nextFrame();
		void setPosition(float x, float y);

		void hover(Widget& hovered);
		void unhover();

		void tooltipOn();
		void tooltipOff();

		static StyleType& cls() { static StyleType ty("Cursor", Widget::cls()); return ty; }

	protected:
		bool m_dirty;
		Widget* m_hovered;
		Tooltip& m_tooltip;
		Clock m_tooltipClock;
	};

	class MK_UI_EXPORT ResizeCursorX : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorX", Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT ResizeCursorY
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorY", Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT MoveCursor : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("MoveCursor", Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT ResizeCursorDiagLeft : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorDiagLeft", Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT ResizeCursorDiagRight : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorDiagRight", Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT CaretCursor : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("CaretCursor", Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Caret : public Widget
	{
	public:
		Caret(Frame* textFrame);

		size_t index() { return m_index; }

		void setIndex(size_t index) { m_index = index; m_dirty = true; }
		
		void moveTo(size_t index);
		void moveRight();
		void moveLeft();

		void nextFrame(size_t tick, size_t delta);

		static StyleType& cls() { static StyleType ty("Caret", Widget::cls()); return ty; }

	protected:
		Frame* m_textFrame;
		size_t m_index;
		bool m_dirty;
	};

	class MK_UI_EXPORT _I_ Tooltip : public Widget
	{
	public:
		Tooltip(RootSheet& rootSheet, const string& label);
		~Tooltip();

		const string& label() { return m_label; }

		void setLabel(const string& label);

		static StyleType& cls() { static StyleType ty("Tooltip", Widget::cls()); return ty; }

	protected:
		string m_label;
	};

	class MK_UI_EXPORT Band : public Sheet
	{
	public:
		Band(StyleType& type = cls());

		static StyleType& cls() { static StyleType ty("Band", Sheet::cls()); return ty; }
	};
}

#endif // MK_SHEET_H_INCLUDED
