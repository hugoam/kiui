//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Menu.h>

#include <toyui/Frame/Layer.h>

namespace toy
{
	Menu::Menu(Wedge& parent, const string& label, bool submenu)
		: Dropdown(parent, cls())
		, m_submenu(submenu)
	{
		m_list.setStyle(MenuList::cls());
		if(submenu)
			m_list.setStyle(SubMenuList::cls());

		m_header.reset({ label });
	}

	Menubar::Menubar(Wedge& parent)
		: Header(parent, cls())
	{}
}
