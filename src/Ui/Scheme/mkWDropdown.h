//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WDROPDOWN_H
#define MK_WDROPDOWN_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Form/mkForm.h>

#include <functional>

namespace mk
{
	class MK_UI_EXPORT WDropdownHeader : public Sheet, public Styled<WDropdownHeader>
	{
	public:
		WDropdownHeader();
	};

	class MK_UI_EXPORT WDropdownToggle : public WButton, public Styled<WDropdownToggle>
	{
	public:
		WDropdownToggle(const Trigger& trigger);

		using Styled<WDropdownToggle>::styleCls;
	};

	class MK_UI_EXPORT WDropdownChoice : public WWrapButton, public Styled < WDropdownChoice >
	{
	public:
		WDropdownChoice(Widget* content, const Trigger& trigger);
	};

	class MK_UI_EXPORT WDropdownBox : public Sheet, public Styled<WDropdownBox>
	{
	public:
		WDropdownBox(WDropdown* dropdown);

		FrameType frameType() { return LAYER; }

		bool leftClick(float x, float y);

	protected:
		WDropdown* mDropdown;
	};

	class MK_UI_EXPORT WDropdown : public Sheet, public Styled<WDropdown>
	{
	public:
		WDropdown(const Trigger& onSelected);
		~WDropdown();

		void build();

		void dropdown();
		void dropup();

		Sheet* vaddwrapper(Widget* widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void selected(WWrapButton* selected);

	protected:
		Trigger mOnSelected;
		Sheet* mHeader;
		WButton* mDropButton;
		WDropdownBox* mDropbox;
		WWrapButton* mSelected;
		bool mDown;
	};

	class MK_UI_EXPORT Dropdown : public Form
	{
	public:
		Dropdown(const Trigger& onSelected, std::function<void(string)> onSelectedString = nullptr);
		Dropdown(std::function<void(string)> onSelected, StringVector choices);

		void onSelected(Widget* widget);

	protected:
		Trigger mOnSelected;
		std::function<void(string)> mOnSelectedString;
	};
}

#endif
