//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CURSOR_H
#define TOY_CURSOR_H

/* toy */
#include <toyobj/Util/Timer.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Tooltip : public Wedge
	{
	public:
		Tooltip(RootSheet& rootSheet, const string& label);

		static Type& cls() { static Type ty("Tooltip", Wedge::Decal()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Rectangle : public Wedge
	{
	public:
		Rectangle(Wedge& parent, Type& type = cls());

		static Type& cls() { static Type ty("Rectangle", Wedge::Decal()); return ty; }
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

		static Type& cls() { static Type ty("Cursor", Wedge::Decal()); return ty; }

		static Type& ResizeX() { static Type ty("ResizeCursorX", Cursor::cls()); return ty; }
		static Type& ResizeY() { static Type ty("ResizeCursorY", Cursor::cls()); return ty; }
		static Type& Move() { static Type ty("MoveCursor", Cursor::cls()); return ty; }
		static Type& ResizeDiagLeft() { static Type ty("ResizeCursorDiagLeft", Cursor::cls()); return ty; }
		static Type& ResizeDiagRight() { static Type ty("ResizeCursorDiagRight", Cursor::cls()); return ty; }
		static Type& Caret() { static Type ty("CaretCursor", Cursor::cls()); return ty; }

	protected:
		Widget* m_hovered;
		bool m_locked;

		Tooltip m_tooltip;
		Clock m_tooltipClock;
	};
}

#endif // TOY_CURSOR_H
