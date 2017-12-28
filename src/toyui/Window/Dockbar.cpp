//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Dockbar.h>

namespace toy
{
	Dockbox::Dockbox(const Params& params, Dockbar& dockbar, const string& title, const string& icon)
		: Window({ params, &cls<Dockbox>() }, title, static_cast<WindowState>(0), nullptr, nullptr)
		, m_dockbar(dockbar)
		, m_toggle({ &dockbar, &Dockbar::styles().toggle }, [this](Widget&, bool on) { this->toggle(on); }, false)
	{
		m_toggle.setContent(icon);
	}

	void Dockbox::toggle(bool open)
	{
		open ? this->show() : this->hide();
	}

	Dockbar::Dockbar(const Params& params)
		: Wedge({ params, &cls<Dockbar>() })
		, m_dockzone({ this, &styles().dockzone })
	{}

	Dockbox& Dockbar::addDock(const string& name, const string& icon)
	{
		Dockbox& dockbox = m_dockzone.emplace<Dockbox>(*this, name, icon);
		//dockbox.m_body.enableWrap();
		dockbox.hide();
		return dockbox;
	}

	Dockbox& Dockbar::addDock(const string& name)
	{
		string icon = "(" + replaceAll(name, " ", "") + ")";
		std::transform(icon.begin(), icon.end(), icon.begin(), ::tolower);
		return this->addDock(name, icon);
	}
}
