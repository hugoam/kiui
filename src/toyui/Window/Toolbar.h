//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TOOLBAR_H
#define TOY_TOOLBAR_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Button/Dropdown.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT ToolButton : public DropdownInput
	{
	public:
		ToolButton(Wedge& parent, const string& icon, const Callback& trigger = nullptr);

		static Type& cls() { static Type ty("ToolButton", DropdownInput::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Tooldock : public Div
	{
	public:
		Tooldock(Wedge& parent);

		static Type& cls() { static Type ty("Tooldock", Div::cls()); return ty; }
	};
	
	class _refl_ TOY_UI_EXPORT ToolbarMover : public Control
	{
	public:
		ToolbarMover(Wedge& parent);

		static Type& cls() { static Type ty("ToolbarMover", Control::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Toolbar : public WrapControl
	{
	public:
		Toolbar(Wedge& parent);

		static Type& cls() { static Type ty("Toolbar", WrapControl::cls()); return ty; }

	protected:
		ToolbarMover m_mover;
	};
}

#endif
