//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_MENU_H
#define TOY_MENU_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/List.h>
#include <toyui/Button/Dropdown.h>

namespace toy
{
	class TOY_UI_EXPORT MenuList : public Object
	{
	public:
		static Type& cls() { static Type ty("MenuList", DropdownList::cls()); return ty; }
	};

	class TOY_UI_EXPORT SubMenuList : public Object
	{
	public:
		static Type& cls() { static Type ty("SubMenuList", MenuList::cls()); return ty; }
	};

	class TOY_UI_EXPORT Menu : public Dropdown
	{
	public:
		Menu(Piece& parent, const string& label, bool submenu = false);

		static Type& cls() { static Type ty("Menu", Dropdown::cls()); return ty; }

	protected:
		bool m_submenu;
	};
}

#endif
