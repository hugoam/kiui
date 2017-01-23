//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
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
	class _I_ TOY_UI_EXPORT Cursor : public Sheet
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

	class TOY_UI_EXPORT ResizeCursorX : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorX", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT ResizeCursorY
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorY", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT MoveCursor : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("MoveCursor", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT ResizeCursorDiagLeft : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorDiagLeft", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT ResizeCursorDiagRight : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ResizeCursorDiagRight", Cursor::cls()); return ty; }
	};

	class TOY_UI_EXPORT CaretCursor : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("CaretCursor", Cursor::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Tooltip : public Widget
	{
	public:
		Tooltip(RootSheet& rootSheet, const string& label);

		void setLabel(const string& label);

		static StyleType& cls() { static StyleType ty("Tooltip", Widget::cls()); return ty; }
	};
}

#endif // TOY_CURSOR_H
