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
	class TOY_UI_EXPORT DockToggle : public ImgButton
	{
	public:
		DockToggle(Dockbar& dockbar, Dockbox& dockbox, const string& icon);

		void click();

		static Type& cls() { static Type ty("DockToggle", ImgButton::cls()); return ty; }

	protected:
		Dockbox& m_dockbox;
	};

	class TOY_UI_EXPORT Dockbox : public Window
	{
	public:
		Dockbox(Piece& parent, Dockbar& dockbar, const string& title, const string& icon);

		Dockbar& dockbar() { return m_dockbar; }
		DockToggle& toggle() { return m_toggle; }

		static Type& cls() { static Type ty("Dockbox", Window::cls()); return ty; }

	protected:
		Dockbar& m_dockbar;
		DockToggle m_toggle;
	};

	class TOY_UI_EXPORT Docker : public Line
	{
	public:
		Docker(Piece& parent);

		static Type& cls() { static Type ty("Docker", Line::cls()); return ty; }
	};

	class TOY_UI_EXPORT Dockbar : public Div
	{
	public:
		Dockbar(Piece& parent);

		Dockbox& addDock(const string& name, const string& icon);
		Dockbox& addDock(const string& name);
		void removeDock(Dockbox& dockbox);

		static Type& cls() { static Type ty("Dockbar", Div::cls()); return ty; }

	protected:
		Docker m_docker;
	};
}

#endif
