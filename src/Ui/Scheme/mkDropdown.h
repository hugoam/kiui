//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WDROPDOWN_H
#define MK_WDROPDOWN_H

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

		static StyleType& cls() { static StyleType ty(WrapButton::cls()); return ty; }

	protected:
		Dropdown& mDropdown;
		FilterInput* mInput;
	};

	class MK_UI_EXPORT DropdownToggle : public Button
	{
	public:
		DropdownToggle(Dropdown& dropdown);

		void click();

		static StyleType& cls() { static StyleType ty(Button::cls()); return ty; }

	protected:
		Dropdown& mDropdown;
	};

	class MK_UI_EXPORT DropdownLabel : public Label
	{
	public:
		DropdownLabel(const string& label);

		static StyleType& cls() { static StyleType ty(Label::cls()); return ty; }
	};

	class MK_UI_EXPORT DropdownChoice : public WrapButton
	{
	public:
		DropdownChoice(Widget* content, const Trigger& trigger);

		static StyleType& cls() { static StyleType ty(WrapButton::cls()); return ty; }
	};

	class MK_UI_EXPORT DropdownBox : public FilterList
	{
	public:
		DropdownBox(Dropdown& dropdown);

		bool leftClick(float x, float y);
		
		static StyleType& cls() { static StyleType ty(FilterList::cls()); return ty; }

	protected:
		Dropdown& mDropdown;
	};

	class MK_UI_EXPORT Dropdown : public Sheet
	{
	public:
		Dropdown(const Trigger& onSelected, StringVector choices = StringVector(), bool input = false);
		~Dropdown();

		DropdownBox& dropbox() { return mDropbox; }
		DropdownHeader& header() { return mHeader; }
		bool down() { return mDown; }

		void dropdown(bool modal = true);
		void dropup();

		Widget& vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void selected(WrapButton& selected);

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		Trigger mOnSelected;
		DropdownBox& mDropbox;
		DropdownHeader& mHeader;
		DropdownToggle& mToggle;
		WrapButton* mSelected;
		bool mDown;
	};

	class MK_UI_EXPORT Typedown : public Dropdown
	{
	public:
		Typedown(const Trigger& onSelected, StringVector choices = StringVector());

		static StyleType& cls() { static StyleType ty(Dropdown::cls()); return ty; }
	};
}

#endif
