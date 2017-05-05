//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WINDOW_H
#define TOY_WINDOW_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/ScrollSheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class TOY_UI_EXPORT Popup : public Overlay
	{
	public:
		Popup(Wedge& parent);

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Popup", Overlay::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT CloseButton : public Button
	{
	public:
		CloseButton(Wedge& parent, const Trigger& trigger);

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("CloseButton", Button::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WindowHeader : public WrapControl
	{
	public:
		WindowHeader(Window& window);

		const string& tooltip() { return m_tooltip; }

		Label& title() { return m_title; }
		Button& close() { return m_close; }

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void leftDragStart(MouseEvent& mouseEvent);
		virtual void leftDrag(MouseEvent& mouseEvent);
		virtual void leftDragEnd(MouseEvent& mouseEvent);

		Docksection* docktarget(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("WindowHeader", WrapControl::cls()); return ty; }

	protected:
		Window& m_window;
		Label m_title;
		CloseButton m_close;
		string m_tooltip;
	};

	class _I_ TOY_UI_EXPORT WindowSizer : public Control
	{
	public:
		WindowSizer(Wedge& parent, Window& window, Type& type, bool left);

		virtual void leftDragStart(MouseEvent& mouseEvent);
		virtual void leftDrag(MouseEvent& mouseEvent);
		virtual void leftDragEnd(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("WindowSizer", Control::cls()); return ty; }

	protected:
		Window& m_window;
		bool m_resizeLeft;
	};

	class _I_ TOY_UI_EXPORT WindowSizerLeft : public WindowSizer
	{
	public:
		WindowSizerLeft(Wedge& parent, Window& window);

		static Type& cls() { static Type ty("WindowSizerLeft", WindowSizer::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WindowSizerRight : public WindowSizer
	{
	public:
		WindowSizerRight(Wedge& parent, Window& window);

		static Type& cls() { static Type ty("WindowSizerRight", WindowSizer::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT WindowFooter : public WrapControl
	{
	public:
		WindowFooter(Window& window);

		static Type& cls() { static Type ty("WindowFooter", WrapControl::cls()); return ty; }

	protected:
		WindowSizerLeft m_firstSizer;
		WindowSizerRight m_secondSizer;
	};

	class _I_ TOY_UI_EXPORT WindowBody : public ScrollSheet
	{
	public:
		WindowBody(Wedge& parent);

		static Type& cls() { static Type ty("WindowBody", ScrollSheet::cls()); return ty; }
	};

	enum WindowState
	{
		WINDOW_NOSTATE = 0,
		WINDOW_DOCKABLE = 1 << 0,
		WINDOW_CLOSABLE = 1 << 1,
		WINDOW_MOVABLE = 1 << 2,
		WINDOW_SIZABLE = 1 << 3,
		WINDOW_SHRINK = 1 << 4,
		WINDOW_DEFAULT = WINDOW_MOVABLE | WINDOW_SIZABLE | WINDOW_CLOSABLE
	};

	class _I_ TOY_UI_EXPORT Window : public Overlay
	{
	public:
		Window(Wedge& parent, const string& title, WindowState state = WINDOW_DEFAULT, const Trigger& onClose = nullptr, Docksection* dock = nullptr, Type& type = cls());
		
		const string& name() { return m_name; }

		WindowState windowState() { return m_windowState; }
		WindowBody& body() { return m_body; }
		Docksection* dock() { return m_dock; }

		bool closable() { return (m_windowState & WINDOW_CLOSABLE) != 0; }
		bool dockable() { return (m_windowState & WINDOW_DOCKABLE) != 0; }
		bool movable()  { return (m_windowState & WINDOW_MOVABLE) != 0; }
		bool sizable() { return (m_windowState & WINDOW_SIZABLE) != 0; }
		bool shrink() { return (m_windowState & WINDOW_SHRINK) != 0; }

		void toggleWindowState(WindowState state);

		void toggleClosable();
		void toggleMovable();
		void toggleResizable();
		void toggleWrap();

		void showTitlebar();
		void hideTitlebar();

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);

		virtual Container& emplaceContainer();

		void dock(Docksection& docksection);
		void undock();

		void docked();
		void undocked();

		void close();

		static Type& cls() { static Type ty("Window", Overlay::cls()); return ty; }

	protected:
		string m_name;
		WindowState m_windowState;
		Trigger m_onClose;
		WindowHeader m_header;
		WindowBody m_body;
		WindowFooter m_footer;

		Docksection* m_dock;
	};

	class TOY_UI_EXPORT DockWindow : public Object
	{
	public:
		static Type& cls() { static Type ty("DockWindow", Window::cls()); return ty; }
	};

	class TOY_UI_EXPORT WrapWindow : public Object
	{
	public:
		static Type& cls() { static Type ty("WrapWindow", Window::cls()); return ty; }
	};
}

#endif
