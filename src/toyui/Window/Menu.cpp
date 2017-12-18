//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Menu.h>

#include <toyui/Frame/Layer.h>

namespace toy
{
	Menu::Menu(const Params& params, const string& label, bool submenu)
		: Dropdown({ params, &cls<Menu>() })
		, m_submenu(submenu)
	{
		m_list.setStyle(submenu ? styles().sublist : styles().list);
		m_header.reset({ label });
	}

	Menubar::Menubar(const Params& params)
		: Wedge({ params, &cls<Menubar>() })
	{}
}
