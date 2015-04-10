//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WDROPDOWN_H
#define MK_WDROPDOWN_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

#include <functional>

namespace mk
{
	class MK_UI_EXPORT DropdownHeader : public WrapButton, public Typed<DropdownHeader, Sheet>, public Styled<DropdownHeader>
	{
	public:
		DropdownHeader(const Trigger& trigger);

		using Typed<DropdownHeader, Sheet>::cls;
	};

	class MK_UI_EXPORT DropdownToggle : public Button, public Typed<DropdownToggle, Button>, public Styled<DropdownToggle>
	{
	public:
		DropdownToggle(const Trigger& trigger);

		using Typed<DropdownToggle, Button>::cls;
		using Styled<DropdownToggle>::styleCls;
	};

	class MK_UI_EXPORT DropdownLabel : public Label, public Typed<DropdownLabel, Label>, public Styled<DropdownLabel>
	{
	public:
		DropdownLabel(const string& label);

		using Typed<DropdownLabel, Label>::cls;
		using Styled<DropdownLabel>::styleCls;
	};

	class MK_UI_EXPORT DropdownChoice : public WrapButton, public Typed<DropdownChoice, Sheet>, public Styled<DropdownChoice>
	{
	public:
		DropdownChoice(Widget* content, const Trigger& trigger);

		using Typed<DropdownChoice, Sheet>::cls;
	};

	class MK_UI_EXPORT DropdownBox : public Sheet, public Typed<DropdownBox, Sheet>, public Styled<DropdownBox>
	{
	public:
		DropdownBox(Dropdown* dropdown);

		bool leftClick(float x, float y);
		
		using Typed<DropdownBox, Sheet>::cls;

	protected:
		Dropdown* mDropdown;
	};

	class MK_UI_EXPORT Dropdown : public Sheet, public Typed<Dropdown, Sheet>, public Styled<Dropdown>
	{
	public:
		Dropdown(const Trigger& onSelected, StringVector choices = StringVector());
		~Dropdown();

		void dropdown();
		void dropup();

		Sheet* vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void selected(WrapButton* selected);

		using Typed<Dropdown, Sheet>::cls;

	protected:
		Trigger mOnSelected;
		Sheet* mHeader;
		Button* mDropButton;
		DropdownBox* mDropbox;
		WrapButton* mSelected;
		bool mDown;
	};
}

#endif
