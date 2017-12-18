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
		Dropdown(const Params& params);

		virtual void dropdown(bool modal = true);
		virtual void dropup();

		virtual void selected(MultiButton& selected);

		MultiButton& addChoice(const StringVector& elements, const Callback& trigger = nullptr);

		struct Styles
		{
			Style dropdown = { cls<Dropdown>(), Widget::styles().wrap_button };
			Style toggle = { "DropdownToggle", Widget::styles().button };
			Style head = { "DropdownHead", Widget::styles().multi_button };
			Style list = { "DropdownList", Widget::styles().wedge, Args{ { &Layout::m_flow, ALIGN },{ &Layout::m_align, Dim<Align>{ LEFT, OUT_RIGHT } } } };
			Style choice = { "DropdownChoice", Widget::styles().multi_button };
			Style dropdown_input = { cls<DropdownInput>(), dropdown };
		};
		static Styles& styles() { static Styles styles; return styles; }

	public:
		MultiButton m_header;
		Button m_toggle;
		Popup m_list;
	};

	class _refl_ TOY_UI_EXPORT DropdownInput : public Dropdown
	{
	public:
		DropdownInput(const Params& params, StringVector choices = {}, const Callback& callback = nullptr);

		virtual void selected(MultiButton& selected);
		void select(MultiButton& selected);

		MultiButton& addChoice(const StringVector& elements, const Callback& trigger = nullptr);

	protected:
		Callback m_onSelected;
		MultiButton* m_selected;
	};
}

#endif
