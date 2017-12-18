//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CURSOR_H
#define TOY_CURSOR_H

/* toy */
#include <toyobj/Util/Timer.h>
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Tooltip : public Wedge
	{
	public:
		Tooltip(RootSheet& rootSheet, const string& label);
	};

	class _refl_ TOY_UI_EXPORT Rectangle : public Wedge
	{
	public:
		Rectangle(const Params& params);
	};

	class _refl_ TOY_UI_EXPORT Cursor : public Wedge
	{
	public:
		Cursor(RootSheet& rootSheet);

		void update();

		void lock() { m_locked = true; }
		void unlock() { m_locked = false; }

		void setPosition(const DimFloat& pos);

		void hover(Widget& hovered);
		void unhover(Widget& widget);
		void unhover();

		void tooltipOn();
		void tooltipOff();

		struct Styles
		{
			Style cursor = { cls<Cursor>(), Widget::styles().decal, Args{ { &Layout::m_zorder, -1 } } };
			Style resize_x = { "CursorResizeX", cursor, Args{ { &InkStyle::m_padding, BoxFloat{ -10.f, -10.f, +10.f, +10.f } } } };
			Style resize_y = { "CursorResizeY", cursor, Args{ { &InkStyle::m_padding, BoxFloat{ -10.f, -10.f, +10.f, +10.f } } } };
			Style move = { "CursorMove", cursor, Args{ { &InkStyle::m_padding, BoxFloat{ -10.f, -10.f, +10.f, +10.f } } } };
			Style resize_diag_left = { "CursorResizeDiagLeft", cursor, Args{ { &InkStyle::m_padding, BoxFloat{ -10.f, -10.f, +10.f, +10.f } } } };
			Style resize_diag_right = { "CursorResizeDiagRight", cursor, Args{ { &InkStyle::m_padding, BoxFloat{ -10.f, -10.f, +10.f, +10.f } } } };
			Style caret = { "CursorCaret", cursor, Args{ { &InkStyle::m_padding, BoxFloat{ -4.f, -9.f, +4.f, +9.f } } } };
		};
		static Styles& styles() { static Styles styles; return styles; }

	protected:
		Widget* m_hovered;
		bool m_locked;

		Tooltip m_tooltip;
		Clock m_tooltipClock;
	};
}

#endif // TOY_CURSOR_H
