//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DOCKBAR_H
#define MK_DOCKBAR_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Scheme/mkWindow.h>

namespace mk
{
	class MK_UI_EXPORT DockToggle : public ImgButton
	{
	public:
		DockToggle(Dockbox& dockbox, const string& icon);

		void click();

		static StyleType& cls() { static StyleType ty("DockToggle", ImgButton::cls()); return ty; }

	protected:
		Dockbox& mDockbox;
	};

	class MK_UI_EXPORT Dockbox : public Window
	{
	public:
		Dockbox(Dockbar& dockbar, const string& title, const string& icon);

		Dockbar& dockbar() { return mDockbar; }
		DockToggle& toggle() { return mToggle; }

		static StyleType& cls() { static StyleType ty("Dockbox", Window::cls()); return ty; }

	protected:
		Dockbar& mDockbar;
		DockToggle& mToggle;
	};

	class MK_UI_EXPORT Docker : public Sheet
	{
	public:
		Docker();

		static StyleType& cls() { static StyleType ty("Docker", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT Dockbar : public Sheet
	{
	public:
		Dockbar();

		Widget& addDock(const string& name, const string& icon, unique_ptr<Widget> widget);

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		static StyleType& cls() { static StyleType ty("Dockbar", Sheet::cls()); return ty; }

	protected:
		Docker& mDocker;
	};
}

#endif
