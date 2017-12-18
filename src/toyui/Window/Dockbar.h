//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DOCKBAR_H
#define TOY_DOCKBAR_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Window/Window.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Dockbox : public Window
	{
	public:
		Dockbox(const Params& params, Dockbar& dockbar, const string& title, const string& icon);

		void toggle(bool open);

	public:
		Dockbar& m_dockbar;
		Toggle m_toggle;
	};

	class _refl_ TOY_UI_EXPORT Docker : public Wedge
	{
	public:
		Docker(const Params& params);

		struct Styles
		{
			Style docker = { cls<Docker>(), Widget::styles().row, Args{ { &Layout::m_flow, ALIGN },{ &Layout::m_space, SPACER },{ &Layout::m_align, Dim<Align>{ LEFT, OUT_LEFT } } } };
			Style dockbar = { cls<Dockbar>(), Widget::styles().div, Args{ { &Layout::m_align, Dim<Align>{ RIGHT, RIGHT } } } };
			Style dockbar_toggle = { "DockbarToggle", Widget::styles().button };
			Style dockbox = { cls<Dockbox>(), Window::styles().window, Args{ { &Layout::m_flow, FLOW },{ &Layout::m_space, Space{ PARAGRAPH, WRAP, FIXED } },{ &Layout::m_size, DimFloat{ 300.f, 0.f } } } };
		};
		static Styles& styles() { static Styles styles; return styles; }
	};

	class _refl_ TOY_UI_EXPORT Dockbar : public Wedge
	{
	public:
		Dockbar(const Params& params);

		Dockbox& addDock(const string& name, const string& icon);
		Dockbox& addDock(const string& name);

	protected:
		Docker m_docker;
	};
}

#endif
