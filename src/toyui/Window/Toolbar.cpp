//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Toolbar.h>

namespace toy
{
	ToolButton::ToolButton(Wedge& parent, const string& icon, const Callback& trigger)
		: DropdownInput(parent, nullptr, {}, cls())
	{
		// header is a button
		m_activeHeader = true;

		// don't drop on left click, but on right click
		m_trigger = nullptr;
		m_triggerAlt = [this](Widget&) { this->dropdown(true); };

		MultiButton& choice = this->addChoice({ icon }, trigger);
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
