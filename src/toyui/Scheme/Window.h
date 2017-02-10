//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WWINDOW_H
#define TOY_WWINDOW_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Widget/Button.h>

namespace toy
{
	class TOY_UI_EXPORT Popup : public LayerSheet
	{
	public:
		Popup();

		virtual void bound();

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("Popup", LayerSheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WindowHeader : public Band
	{
	public:
		WindowHeader(Window& window);

		Style* hoverCursor() { return &MoveCursor::cls(); }
		const string& tooltip() { return m_tooltip; }

		Label& title() { return m_title; }
		Button* closeButton() { return m_closeButton; }

		void leftClick(MouseEvent& mouseEvent);
		void leftDragStart(MouseEvent& mouseEvent);
		void leftDrag(MouseEvent& mouseEvent);
		void leftDragEnd(MouseEvent& mouseEvent);

		Docksection* docktarget(float x, float y);

		static StyleType& cls() { static StyleType ty("WindowHeader", Band::cls()); return ty; }

	protected:
		Window& m_window;
		Label& m_title;
		Button* m_closeButton;
		string m_tooltip;
	};

	class _I_ TOY_UI_EXPORT WindowSizer : public Widget
	{
	public:
		WindowSizer(Window& window, StyleType& type, bool left);

		Style* hoverCursor() { return &ResizeCursorDiagRight::cls(); }

		void leftDragStart(MouseEvent& mouseEvent);
		void leftDrag(MouseEvent& mouseEvent);
		void leftDragEnd(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("WindowSizer", Widget::cls()); return ty; }

	protected:
		Window& m_window;
		bool m_resizeLeft;
	};

	class _I_ TOY_UI_EXPORT WindowSizerLeft : public WindowSizer
	{
	public:
		WindowSizerLeft(Window& window);

		static StyleType& cls() { static StyleType ty("WindowSizerLeft", WindowSizer::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WindowSizerRight : public WindowSizer
	{
	public:
		WindowSizerRight(Window& window);

		static StyleType& cls() { static StyleType ty("WindowSizerRight", WindowSizer::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WindowFooter : public Sheet
	{
	public:
		WindowFooter(Window& window);

		static StyleType& cls() { static StyleType ty("WindowFooter", Sheet::cls()); return ty; }

	protected:
		WindowSizer& m_firstSizer;
		WindowSizer& m_secondSizer;
	};

	class _I_ TOY_UI_EXPORT WindowBody : public ScrollSheet
	{
	public:
		WindowBody();

		static StyleType& cls() { static StyleType ty("WindowBody", ScrollSheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT CloseButton : public Button
	{
	public:
		CloseButton(const Trigger& trigger);

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("CloseButton", Button::cls()); return ty; }
	};

	enum WindowState
	{
		WINDOW_NOSTATE = 0,
		WINDOW_CREATED = 1 << 0,
		WINDOW_DOCKABLE = 1 << 1,
		WINDOW_CLOSABLE = 1 << 2,
		WINDOW_MOVABLE = 1 << 3,
		WINDOW_SIZABLE = 1 << 4,
		WINDOW_SHRINK = 1 << 5,
		WINDOW_DEFAULT = WINDOW_CREATED | WINDOW_MOVABLE | WINDOW_SIZABLE | WINDOW_CLOSABLE
	};

	class _I_ TOY_UI_EXPORT Window : public LayerSheet
	{
	public:
		Window(const string& title, WindowState state = WINDOW_DEFAULT, const Trigger& onClose = nullptr, Docksection* dock = nullptr, StyleType& type = cls());
		~Window();

		const string& name();

		WindowState windowState() { return m_windowState; }
		WindowBody& body() { return m_body; }
		Docksection* dock() { return m_dock; }

		bool closable() { return (m_windowState & WINDOW_CLOSABLE) != 0; }
		bool dockable() { return (m_windowState & WINDOW_DOCKABLE) != 0; }
		bool movable()  { return (m_windowState & WINDOW_MOVABLE) != 0; }
		bool sizable() { return (m_windowState & WINDOW_SIZABLE) != 0; }
		bool shrink() { return (m_windowState & WINDOW_SHRINK) != 0; }

		virtual void bound();

		void toggleWindowState(WindowState state);

		void toggleClosable();
		void toggleMovable();
		void toggleResizable();
		void showTitlebar();
		void hideTitlebar();

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		Widget& vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget& widget);

		void dock(Docksection& docksection);
		void undock();

		void docked();
		void undocked();

		void close();

		static StyleType& cls() { static StyleType ty("Window", LayerSheet::cls()); return ty; }

	protected:
		string m_name;
		WindowState m_windowState;
		Widget* m_content;
		Trigger m_onClose;
		WindowHeader& m_header;
		WindowBody& m_body;
		WindowFooter& m_footer;

		Docksection* m_dock;
	};

	class _I_ TOY_UI_EXPORT DockWindow : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("DockWindow", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT ShrinkWindow : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ShrinkWindow", Window::cls()); return ty; }
	};
}

#endif
