//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WINDOW_H
#define TOY_WINDOW_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT CloseButton : public Button
	{
	public:
		CloseButton(Wedge& parent, const Callback& trigger);

		static Type& cls() { static Type ty("CloseButton", Button::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT WindowHeader : public Wedge
	{
	public:
		WindowHeader(Window& window);

		const string& tooltip() { return m_tooltip; }

		Label& title() { return m_title; }
		Button& close() { return m_close; }

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("WindowHeader", Wedge::WrapControl()); return ty; }

	protected:
		Window& m_window;
		Label m_title;
		CloseButton m_close;
		string m_tooltip;
	};

	class _refl_ TOY_UI_EXPORT WindowSizer : public Item
	{
	public:
		WindowSizer(Wedge& parent, Window& window, Type& type, bool left);

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("WindowSizer", Item::Control()); return ty; }

	protected:
		Window& m_window;
		bool m_resizeLeft;
	};

	class _refl_ TOY_UI_EXPORT WindowFooter : public Wedge
	{
	public:
		WindowFooter(Window& window);

		static Type& cls() { static Type ty("WindowFooter", Wedge::WrapControl()); return ty; }

		static Type& SizerLeft() { static Type ty("WindowSizerLeft", WindowSizer::cls()); return ty; }
		static Type& SizerRight() { static Type ty("WindowSizerRight", WindowSizer::cls()); return ty; }

	protected:
		WindowSizer m_firstSizer;
		WindowSizer m_secondSizer;
	};

	enum WindowState
	{
		WINDOW_NOSTATE = 0,
		WINDOW_DOCKABLE = 1 << 0,
		WINDOW_CLOSABLE = 1 << 1,
		WINDOW_MOVABLE = 1 << 2,
		WINDOW_SIZABLE = 1 << 3,
		WINDOW_DEFAULT = WINDOW_MOVABLE | WINDOW_SIZABLE | WINDOW_CLOSABLE | WINDOW_DOCKABLE
	};

	class _refl_ TOY_UI_EXPORT Window : public Wedge
	{
	public:
		Window(Wedge& parent, const string& title, WindowState state = WINDOW_DEFAULT, const Callback& onClose = nullptr, Docksection* dock = nullptr, Type& type = cls());
		
		const string& name() { return m_name; }

		WindowState windowState() { return m_windowState; }
		Wedge& body() { return m_body; }
		Docksection* dock() { return m_dock; }

		bool closable() { return (m_windowState & WINDOW_CLOSABLE) != 0; }
		bool dockable() { return (m_windowState & WINDOW_DOCKABLE) != 0; }
		bool movable()  { return (m_windowState & WINDOW_MOVABLE) != 0; }
		bool sizable() { return (m_windowState & WINDOW_SIZABLE) != 0; }

		void toggleWindowState(WindowState state);

		void toggleClosable();
		void toggleMovable();
		void toggleResizable();

		void showTitlebar();
		void hideTitlebar();

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		void dockAt(const DimFloat& pos);

		void dock(Docksection& docksection);
		void undock();

		void toggleDocked();

		void close();

		static Type& cls() { static Type ty("Window", Wedge::Overlay()); return ty; }

		static Type& Body() { static Type ty("WindowBody", Wedge::cls()); return ty; }

		static Type& DockWindow() { static Type ty("DockWindow", Window::cls()); return ty; }
		static Type& WrapWindow() { static Type ty("WrapWindow", Window::cls()); return ty; }

	protected:
		string m_name;
		WindowState m_windowState;
		Callback m_onClose;
		WindowHeader m_header;
		Wedge m_body;
		WindowFooter m_footer;

		Docksection* m_dock;
	};
}

#endif
