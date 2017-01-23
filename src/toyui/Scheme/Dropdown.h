//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DROPDOWN_H
#define TOY_DROPDOWN_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Button.h>
#include <toyui/Scheme/List.h>

#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DropdownHeader : public WrapButton
	{
	public:
		DropdownHeader(Dropdown& dropdown, bool input);

		Style* hoverCursor() { return m_input ? &CaretCursor::cls() : nullptr; }
		FilterInput* input() { return m_input; }

		void click();

		void onInput(string value);
		void updateContent(Widget& choice);

		static StyleType& cls() { static StyleType ty("DropdownHeader", WrapButton::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
		FilterInput* m_input;
	};

	class TOY_UI_EXPORT DropdownToggle : public Button
	{
	public:
		DropdownToggle(Dropdown& dropdown);

		void click();

		static StyleType& cls() { static StyleType ty("DropdownToggle", Button::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
	};

	class TOY_UI_EXPORT DropdownLabel : public Label
	{
	public:
		DropdownLabel(const string& label);

		static StyleType& cls() { static StyleType ty("DropdownLabel", Label::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownChoice : public WrapButton
	{
	public:
		DropdownChoice(unique_ptr<Widget> content, const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("DropdownChoice", WrapButton::cls()); return ty; }
	};

	class TOY_UI_EXPORT DropdownList : public List
	{
	public:
		DropdownList(Dropdown& dropdown);

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);
		
		static StyleType& cls() { static StyleType ty("DropdownList", List::cls()); return ty; }

	protected:
		Dropdown& m_dropdown;
	};

	class TOY_UI_EXPORT Dropdown : public Sheet
	{
	public:
		Dropdown(const Trigger& onSelected, StringVector choices = StringVector(), bool input = false, StyleType& type = cls());
		~Dropdown();

		DropdownList& dropbox() { return m_list; }
		DropdownHeader& header() { return m_header; }
		bool down() { return m_down; }

		void dropdown(bool modal = true);
		void dropup();

		Widget& vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void select(WrapButton& selected);
		void selected(WrapButton& selected);

		static StyleType& cls() { static StyleType ty("Dropdown", Sheet::cls()); return ty; }

	protected:
		Trigger m_onSelected;
		DropdownList& m_list;
		DropdownHeader& m_header;
		DropdownToggle& m_toggle;
		WrapButton* m_selected;
		bool m_down;
	};

	class TOY_UI_EXPORT Typedown : public Dropdown
	{
	public:
		Typedown(const Trigger& onSelected, StringVector choices = StringVector());

		static StyleType& cls() { static StyleType ty("Typedown", Dropdown::cls()); return ty; }
	};

	class TOY_UI_EXPORT MenuList : public List
	{
	public:
		MenuList(Menu& menu);

		void leftClick(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("MenuList", List::cls()); return ty; }

	protected:
		Menu& m_menu;
	};

	class TOY_UI_EXPORT SubMenuList : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("SubMenuList", MenuList::cls()); return ty; }
	};

	class TOY_UI_EXPORT Menu : public Sheet
	{
	public:
		Menu(const string& label, bool submenu = false);

		void dropdown();
		void dropup();

		Widget& vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void selected(WrapButton& selected);

		static StyleType& cls() { static StyleType ty("Menu", Dropdown::cls()); return ty; }

	protected:
		bool m_submenu;
		Button& m_button;
		MenuList& m_list;
		bool m_down;
	};
}

#endif
