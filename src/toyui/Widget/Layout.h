//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WIDGETS_H
#define TOY_WIDGETS_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Page : public Container
	{
	public:
		Page(Piece& parent, const string& name);

		const string& name() { return m_name; }

		static Type& cls() { static Type ty("Page", Container::cls()); return ty; }

	protected:
		string m_name;
	};

	class _I_ TOY_UI_EXPORT Dialog : public Container
	{
	public:
		Dialog(Piece& parent);

		static Type& cls() { static Type ty("Dialog", Container::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Header : public Line
	{
	public:
		Header(Piece& parent);

		static Type& cls() { static Type ty("Header", Line::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
