//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_MENU_H
#define TOY_MENU_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/List.h>
#include <toyui/Button/Dropdown.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Menu : public Dropdown
	{
	public:
		Menu(const Params& params, const string& label, bool submenu = false);

		struct Styles
		{
			Style menubar = { cls<Menubar>(), Widget::styles().header };
			Style menu = { cls<Menu>(), Dropdown::styles().dropdown, Args{ { &Layout::m_space, ITEM } } };
			Style list = { "MenuList", Dropdown::styles().list, Args{ { &Layout::m_align, Dim<Align>{ LEFT, OUT_RIGHT } } } };
			Style sublist = { "SubMenuList", list, Args{ { &Layout::m_align, Dim<Align>{ OUT_RIGHT, LEFT } } } };
		};
		static Styles& styles() { static Styles styles; return styles; }

		bool m_submenu;
	};

	class _refl_ TOY_UI_EXPORT Menubar : public Wedge
	{
	public:
		Menubar(const Params& params);
	};
}

#endif
