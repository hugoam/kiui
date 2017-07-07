//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Toolbar.h>

namespace toy
{
	ToolButton::ToolButton(Wedge& parent, const string& icon, const Callback& trigger)
		: DropdownInput(parent, {}, nullptr, cls())
	{
		m_trigger = nullptr; // don't drop on left click
		m_triggerAlt = [this](Widget&) { this->dropdown(true); }; // drop on right

		// MultiButton& choice = this->addChoice({ icon }); // @todo multiple tools, dropdown is complicated to retrofit
		m_header.reset({ icon }, trigger);
		m_toggle.hide();
	}

	Tooldock::Tooldock(Wedge& parent)
		: Wedge(parent, cls())//, GRID)
	{}

	Toolbar::Toolbar(Wedge& parent)
		: Wedge(parent, cls())
		, m_mover(*this, Toolbar::Mover())
	{}
}
