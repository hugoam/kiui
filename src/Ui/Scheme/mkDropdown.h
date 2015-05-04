//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DROPDOWN_H
#define MK_DROPDOWN_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Scheme/mkList.h>

#include <functional>

namespace mk
{
	class MK_UI_EXPORT DropdownHeader : public WrapButton
	{
	public:
		DropdownHeader(Dropdown& dropdown, bool input);

		Style* hoverCursor() { return mInput ? &CaretCursor::cls() : nullptr; }
		FilterInput* input() { return mInput; }

		void click();

		void onInput(string value);
		void update(Widget* choice);

		static StyleType& cls() { static StyleType ty("DropdownHeader", WrapButton::cls()); return ty; }

	protected:
		Dropdown& mDropdown;
		FilterInput* mInput;
	};

	class MK_UI_EXPORT DropdownToggle : public Button
	{
	public:
		DropdownToggle(Dropdown& dropdown);

		void click();

		static StyleType& cls() { static StyleType ty("DropdownToggle", Button::cls()); return ty; }

	protected:
		Dropdown& mDropdown;
	};

	class MK_UI_EXPORT DropdownLabel : public Label
	{
	public:
		DropdownLabel(const string& label);

		static StyleType& cls() { static StyleType ty("DropdownLabel", Label::cls()); return ty; }
	};

	class MK_UI_EXPORT DropdownChoice : public WrapButton
	{
	public:
		DropdownChoice(unique_ptr<Widget> content, const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("DropdownChoice", WrapButton::cls()); return ty; }
	};

	class MK_UI_EXPORT DropdownList : public List
	{
	public:
		DropdownList(Dropdown& dropdown);

		bool leftClick(float x, float y);
		
		static StyleType& cls() { static StyleType ty("DropdownList", List::cls()); return ty; }

	protected:
		Dropdown& mDropdown;
	};

	class MK_UI_EXPORT Dropdown : public Sheet
	{
	public:
		Dropdown(const Trigger& onSelected, StringVector choices = StringVector(), bool input = false);
		~Dropdown();

		DropdownList& dropbox() { return mList; }
		DropdownHeader& header() { return mHeader; }
		bool down() { return mDown; }

		void dropdown(bool modal = true);
		void dropup();

		Widget& vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void selected(WrapButton& selected);

		static StyleType& cls() { static StyleType ty("Dropdown", Sheet::cls()); return ty; }

	protected:
		Trigger mOnSelected;
		DropdownList& mList;
		DropdownHeader& mHeader;
		DropdownToggle& mToggle;
		WrapButton* mSelected;
		bool mDown;
	};

	class MK_UI_EXPORT Typedown : public Dropdown
	{
	public:
		Typedown(const Trigger& onSelected, StringVector choices = StringVector());

		static StyleType& cls() { static StyleType ty("Typedown", Dropdown::cls()); return ty; }
	};

	class MK_UI_EXPORT MenuList : public List
	{
	public:
		MenuList(Menu& menu);

		bool leftClick(float x, float y);

		static StyleType& cls() { static StyleType ty("MenuList", List::cls()); return ty; }

	protected:
		Menu& mMenu;
	};

	class MK_UI_EXPORT SubMenuList : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("SubMenuList", MenuList::cls()); return ty; }
	};

	class MK_UI_EXPORT Menu : public Sheet
	{
	public:
		Menu(const string& label, bool submenu = false);

		void dropdown();
		void dropup();

		Widget& vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		static StyleType& cls() { static StyleType ty("Menu", Dropdown::cls()); return ty; }

	protected:
		bool mSubmenu;
		Button& mButton;
		MenuList& mList;
		bool mDown;
	};
}

#endif
