//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Scheme/Dockbar.h>

namespace toy
{
	Dockbox::Dockbox(Dockbar& dockbar, const string& title, const string& icon)
		: Window(title, static_cast<WindowState>(0), nullptr, nullptr, cls())
		, m_dockbar(dockbar)
		, m_toggle(dockbar.append(make_unique<DockToggle>(*this, icon)).as<DockToggle>())
	{}

	DockToggle::DockToggle(Dockbox& dockbox, const string& icon)
		: ImgButton(icon, std::bind(&DockToggle::click, this), cls())
		, m_dockbox(dockbox)
	{}

	void DockToggle::click()
	{
		this->toggleState(ACTIVATED);

		if(m_dockbox.frame().hidden())
			m_dockbox.show();
		else
			m_dockbox.hide();
	}

	Docker::Docker()
		: Sheet(cls())
	{}

	Dockbar::Dockbar()
		: Sheet(cls())
		, m_docker(this->makeappend<Docker>())
	{}

	Widget& Dockbar::addDock(const string& name, const string& icon, unique_ptr<Widget> widget)
	{
		Dockbox& dockbox = m_docker.emplace<Dockbox>(*this, name, icon);
		dockbox.hide();
		return dockbox.vappend(std::move(widget));
	}

	Widget& Dockbar::vappend(unique_ptr<Widget> widget)
	{
		string icon = replaceAll(widget->name(), " ", "");
		std::transform(icon.begin(), icon.end(), icon.begin(), ::tolower);
		const string name = widget->name();
		return this->addDock(name, icon, std::move(widget));
	}

	unique_ptr<Widget> Dockbar::vrelease(Widget& widget)
	{
		Dockbox& dockbox = widget.parent()->as<Dockbox>();

		unique_ptr<Widget> unique = widget.detach();
		dockbox.toggle().destroy();
		dockbox.destroy();

		return unique;
	}
}
