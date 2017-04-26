//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_LAYOUT_H
#define TOY_LAYOUT_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Page : public Container
	{
	public:
		Page(Wedge& parent);

		static Type& cls() { static Type ty("Page", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Dialog
	{
	public:
		static Type& cls() { static Type ty("Dialog", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Board
	{
	public:
		static Type& cls() { static Type ty("Board", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Layout
	{
	public:
		static Type& cls() { static Type ty("Layout", Board::cls()); return ty; }
	};

	class TOY_UI_EXPORT Line
	{
	public:
		static Type& cls() { static Type ty("Line", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Div
	{
	public:
		static Type& cls() { static Type ty("Div", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Stack
	{
	public:
		static Type& cls() { static Type ty("Stack", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Sheet
	{
	public:
		static Type& cls() { static Type ty("Sheet", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT Header
	{
	public:
		static Type& cls() { static Type ty("Header", Line::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
