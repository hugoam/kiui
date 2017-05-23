//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Dockbar.h>

namespace toy
{
	Dockbox::Dockbox(Wedge& parent, Dockbar& dockbar, const string& title, const string& icon)
		: Window(parent, title, static_cast<WindowState>(0), nullptr, nullptr, cls())
		, m_dockbar(dockbar)
		, m_toggle(dockbar, *this, icon)
	{}

	DockToggle::DockToggle(Dockbar& dockbar, Dockbox& dockbox, const string& icon)
		: Button(dockbar, dockbar.findImage(icon), [this](Widget&) { this->click(); }, cls())
		, m_dockbox(dockbox)
	{}

	void DockToggle::click()
	{
		bool open = !m_dockbox.frame().hidden();
		open ? m_dockbox.hide() : m_dockbox.show();
		open ? this->disableState(ACTIVATED) : this->enableState(ACTIVATED);
	}

	Docker::Docker(Wedge& parent)
		: Row(parent, cls())
	{}

	Dockbar::Dockbar(Wedge& parent)
		: Div(parent, cls())
		, m_docker(*this)
	{}

	Dockbox& Dockbar::addDock(const string& name, const string& icon)
	{
		Dockbox& dockbox = m_docker.emplace<Dockbox>(*this, name, icon);
		//dockbox.body().enableWrap();
		dockbox.hide();
		return dockbox;
	}

	Dockbox& Dockbar::addDock(const string& name)
	{
		string icon = replaceAll(name, " ", "");
		std::transform(icon.begin(), icon.end(), icon.begin(), ::tolower);
		return this->addDock(name, icon);
	}

	void Dockbar::removeDock(Dockbox& dockbox)
	{
		dockbox.toggle().destroy();
		dockbox.destroy();
	}
}
