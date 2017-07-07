//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DOCKBAR_H
#define TOY_DOCKBAR_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Window/Window.h>

namespace toy
{
	class TOY_UI_EXPORT Dockbox : public Window
	{
	public:
		Dockbox(Wedge& parent, Dockbar& dockbar, const string& title, const string& icon);

		Dockbar& dockbar() { return m_dockbar; }

		void toggle(bool open);

		static Type& cls() { static Type ty("Dockbox", Window::cls()); return ty; }

	protected:
		Dockbar& m_dockbar;
		Toggle m_toggle;
	};

	class TOY_UI_EXPORT Docker : public Wedge
	{
	public:
		Docker(Wedge& parent);

		static Type& cls() { static Type ty("Docker", Wedge::Row()); return ty; }
	};

	class TOY_UI_EXPORT Dockbar : public Wedge
	{
	public:
		Dockbar(Wedge& parent);

		Dockbox& addDock(const string& name, const string& icon);
		Dockbox& addDock(const string& name);

		static Type& cls() { static Type ty("Dockbar", Wedge::Div()); return ty; }

		static Type& Toggle() { static Type ty("DockToggle", Button::cls()); return ty; }

	protected:
		Docker m_docker;
	};
}

#endif
