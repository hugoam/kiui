//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Toolbar.h>

namespace toy
{
	ToolButton::ToolButton(Wedge& parent, const string& icon, Trigger trigger)
		: Dropdown(parent)
	{
		DropdownChoice& choice = this->addChoice();
		choice.reset({ icon }, trigger);
		m_header.reset({ icon });
		m_toggle.hide();
		//m_header.emplace<Icon>(icon);
	}

	Tooldock::Tooldock(Wedge& parent)
		: Div(parent, cls())//, GRID)
	{}

	ToolbarMover::ToolbarMover(Wedge& parent)
		: Control(parent, cls())
	{}

	Toolbar::Toolbar(Wedge& parent)
		: WrapControl(parent, cls())
		, m_mover(*this)
	{}
}
