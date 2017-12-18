//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WINDOW_H
#define TOY_WINDOW_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT WindowHeader : public Wedge
	{
	public:
		WindowHeader(Window& window);

		const string& tooltip() { return m_tooltip; }

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);
		virtual bool leftDragEnd(MouseEvent& mouseEvent);

	protected:
		Window& m_window;
		string m_tooltip;

	public:
		Label m_title;
		Button m_close;
	};

	class _refl_ TOY_UI_EXPORT WindowSizer : public Widget
	{
	public:
		WindowSizer(const Params& params, Window& window, bool left);

		virtual bool leftDragStart(MouseEvent& mouseEvent);
		virtual bool leftDrag(MouseEvent& mouseEvent);

	protected:
		Window& m_window;
		bool m_resizeLeft;
	};

	class _refl_ TOY_UI_EXPORT WindowFooter : public Wedge
	{
	public:
		WindowFooter(Window& window);

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
		WINDOW_DEFAULT = WINDOW_MOVABLE | WINDOW_SIZABLE | WINDOW_CLOSABLE
	};

	class _refl_ TOY_UI_EXPORT Window : public Wedge
	{
	public:
		Window(const Params& params, const string& title, WindowState state = WINDOW_DEFAULT, const Callback& onClose = nullptr, Docksection* dock = nullptr);

		bool closable() { return (m_windowState & WINDOW_CLOSABLE) != 0; }
		bool dockable() { return (m_windowState & WINDOW_DOCKABLE) != 0; }
		bool movable() { return (m_windowState & WINDOW_MOVABLE) != 0; }
		bool sizable() { return (m_windowState & WINDOW_SIZABLE) != 0; }

		void toggleWindowState(WindowState state);

		void toggleClosable();
		void toggleMovable();
		void toggleHeader();
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

		struct Styles
		{
			Style window = { cls<Window>(), Widget::styles().overlay, Args{ { &Layout::m_space, BLOCK } } };
			Style body = { "WindowBody", Widget::styles().wedge, Args{ { &Layout::m_clipping, CLIP } } };
			Style close_button = { "CloseButton", Widget::styles().button, Args{ { &Layout::m_align, Dim<Align>{ RIGHT, CENTER } } } };
			Style header = { cls<WindowHeader>(), Widget::styles().wrap_control };
			Style header_movable = { "WindowHeaderMovable", header, Args{ { &InkStyle::m_hover_cursor, &Cursor::styles().move } } };
			Style footer = { cls<WindowFooter>(), Widget::styles().wrap_control, Args{ /*{ &Layout::m_space, Space{ READING, WRAP, FIXED } }*/ } };
			Style sizer = { cls<WindowSizer>(), Widget::styles().control, Args{ { &Layout::m_space, Space{ READING, WRAP, FIXED } } } };
			Style sizer_left = { "WindowSizerLeft", sizer, Args{ { &InkStyle::m_hover_cursor, &Cursor::styles().resize_diag_left } } };
			Style sizer_right = { "WindowSizerRight", sizer, Args{ { &InkStyle::m_hover_cursor, &Cursor::styles().resize_diag_right } } };

			Style dock_window = { "DockWindow", window, Args{ { &Layout::m_flow, FLOW },{ &Layout::m_space, SHEET } } };
			Style wrap_window = { "WrapWindow", window, Args{ { &Layout::m_space, UNIT } } };
		}; 
		static Styles& styles() { static Styles styles; return styles; }

	public:
		string m_name;
		WindowState m_windowState;
		const Callback m_onClose;

		WindowHeader m_header;
		Wedge m_body;
		WindowFooter m_footer;

		Docksection* m_dock;
	};
}

#endif
