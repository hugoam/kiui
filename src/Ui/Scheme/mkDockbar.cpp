//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkDockbar.h>

namespace mk
{
	Dockbox::Dockbox(Dockbar& dockbar, const string& title, const string& icon)
		: Window(title, static_cast<WindowState>(0))
		, mDockbar(dockbar)
		, mToggle(dockbar.append(make_unique<DockToggle>(*this, icon)).as<DockToggle>())
	{
		mStyle = &cls();
	}

	DockToggle::DockToggle(Dockbox& dockbox, const string& icon)
		: ImgButton(icon, std::bind(&DockToggle::click, this))
		, mDockbox(dockbox)
	{
		mStyle = &cls();
	}

	void DockToggle::click()
	{
		if(mDockbox.frame().hidden())
			mDockbox.show();
		else
			mDockbox.hide();
	}

	Docker::Docker()
		: Sheet()
	{
		mStyle = &cls();
	}

	Dockbar::Dockbar()
		: Sheet()
		, mDocker(this->makeappend<Docker>())
	{
		mStyle = &cls();
	}

	Widget& Dockbar::addDock(const string& name, const string& icon, unique_ptr<Widget> widget)
	{
		Dockbox& dockbox = mDocker.emplace<Dockbox>(*this, name, icon);
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

		unique_ptr<Widget> unique = widget.unbind();
		dockbox.toggle().destroy();
		dockbox.destroy();

		return unique;
	}
}
