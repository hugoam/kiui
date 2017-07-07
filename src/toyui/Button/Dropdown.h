//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DROPDOWN_H
#define TOY_DROPDOWN_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Container/List.h>
#include <toyui/Window/Popup.h>

#include <functional>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Dropdown : public WrapButton
	{
	public:
		Dropdown(Wedge& parent, Type& type = cls());

		virtual void dropdown(bool modal = true);
		virtual void dropup();

		virtual void selected(MultiButton& selected);

		MultiButton& addChoice(const StringVector& elements, const Callback& trigger = nullptr);

		static Type& cls() { static Type ty("Dropdown", WrapButton::cls()); return ty; }

		static Type& Toggle() { static Type ty("DropdownToggle", Button::cls()); return ty; }
		static Type& Head() { static Type ty("DropdownHead", MultiButton::cls()); return ty; }
		static Type& List() { static Type ty("DropdownList", Wedge::cls()); return ty; }
		static Type& Choice() { static Type ty("DropdownChoice", MultiButton::cls()); return ty; }

	protected:
		MultiButton m_header;
		Button m_toggle;
		Popup m_list;
	};

	class _refl_ TOY_UI_EXPORT DropdownInput : public Dropdown
	{
	public:
		DropdownInput(Wedge& parent, StringVector choices = {}, const Callback& callback = nullptr, Type& type = cls());

		virtual void selected(MultiButton& selected);
		void select(MultiButton& selected);

		MultiButton& addChoice(const StringVector& elements, const Callback& trigger = nullptr);

		static Type& cls() { static Type ty("DropdownInput", Dropdown::cls()); return ty; }

	protected:
		Callback m_onSelected;
		MultiButton* m_selected;
	};
}

#endif
