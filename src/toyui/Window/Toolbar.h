//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TOOLBAR_H
#define TOY_TOOLBAR_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Dropdown.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT ToolButton : public DropdownInput
	{
	public:
		using Callback = std::function<void(ToolButton&)>;

	public:
		ToolButton(const Params& params, const string& icon, const Callback& trigger = nullptr);

		void activate();
		void deactivate();
	};

	class _refl_ TOY_UI_EXPORT Tooldock : public Wedge
	{
	public:
		Tooldock(const Params& params);
	};
	
	class _refl_ TOY_UI_EXPORT Toolbar : public Wedge
	{
	public:
		Toolbar(const Params& params);

		Widget m_mover;

		struct Styles
		{
			Style toolbutton = { cls<ToolButton>(), Dropdown::styles().dropdown_input };
			Style tooldock = { cls<Tooldock>(), Widget::styles().div };
			Style toolbar = { cls<Toolbar>(), Widget::styles().wrap_control, Args{ { &Layout::m_space, ITEM } } };
			Style mover = { "ToolbarMover", Widget::styles().control };
		};
		static Styles& styles() { static Styles styles; return styles; }
	};
}

#endif
