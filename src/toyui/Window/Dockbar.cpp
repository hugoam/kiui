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
		, m_toggle(dockbar, [this](Widget&, bool on) { this->toggle(on); }, false, Dockbar::Toggle())
	{
		m_toggle.setContent(icon);
	}

	void Dockbox::toggle(bool open)
	{
		open ? this->show() : this->hide();
	}

	Docker::Docker(Wedge& parent)
		: Wedge(parent, cls())
	{}

	Dockbar::Dockbar(Wedge& parent)
		: Wedge(parent, cls())
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
		string icon = "(" + replaceAll(name, " ", "") + ")";
		std::transform(icon.begin(), icon.end(), icon.begin(), ::tolower);
		return this->addDock(name, icon);
	}

	void Dockbar::removeDock(Dockbox& dockbox)
	{
		//dockbox.toggle().extract();
		//dockbox.extract();
	}
}
