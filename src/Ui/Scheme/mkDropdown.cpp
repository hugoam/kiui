//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkDropdown.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkRootForm.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Frame/mkFrame.h>

#include <Ui/Widget/mkRootSheet.h>
#include <Ui/Scheme/mkList.h>

using namespace std::placeholders;

namespace mk
{
	Dropdown::Dropdown(const Trigger& onSelected, StringVector choices, bool input)
		: Sheet()
		, mOnSelected()
		, mSelected(nullptr)
		, mDown(false)
		, mList(this->makeappend<DropdownList>(*this))
		, mHeader(this->makeappend<DropdownHeader>(*this, input))
		, mToggle(this->makeappend<DropdownToggle>(*this))
	{
		mStyle = &cls();
		mList.hide();

		for(string& choice : choices)
			this->emplace<Label>(choice);

		mOnSelected = onSelected;
	}

	Dropdown::~Dropdown()
	{}

	Widget& Dropdown::vappend(std::unique_ptr<Widget> widget)
	{
		WrapButton& button = mList.emplace<DropdownChoice>(std::move(widget), std::bind(&Dropdown::selected, this, _1));
		if(mSelected == nullptr)
			this->selected(button);

		return button;
	}

	unique_ptr<Widget> Dropdown::vrelease(Widget& widget)
	{
		return widget.extract();
	}

	void Dropdown::dropup()
	{
		mList.hide();
		if(mList.state() & MODAL)
			mList.unmodal();
		mDown = false;
	}

	void Dropdown::dropdown(bool modal)
	{
		if(mList.count() == 0)
			return;

		mList.show();
		mList.frame().as<Layer>().moveToTop();
		if(modal)
			mList.modal();

		mDown = true;
	}

	void Dropdown::selected(WrapButton& button)
	{
		if(mDown)
			this->dropup();

		if(mSelected)
			mSelected->toggleState(ACTIVATED);

		mSelected = &button;
		mSelected->toggleState(ACTIVATED);
		mHeader.update(button.content());

		if(mOnSelected)
			mOnSelected(*button.content());
	}

	DropdownHeader::DropdownHeader(Dropdown& dropdown, bool input)
		: WrapButton(nullptr, std::bind(&DropdownHeader::click, this))
		, mDropdown(dropdown)
		, mInput(nullptr)
	{
		mStyle = &cls();
		if(input)
		{
			mInput = &this->makeappend<FilterInput>(mDropdown.dropbox(), std::bind(&DropdownHeader::onInput, this, _1));
			mInput->hide();
		}
	}

	void DropdownHeader::click()
	{
		if(mInput)
		{
			mContent->hide();
			mInput->show();
			mInput->setString(mContent->contentlabel());
			mInput->typeIn().leftClick(this->rootSheet().lastPressedX(), this->rootSheet().lastPressedY());
		}
		else
		{
			mDropdown.dropdown();
		}
	}

	void DropdownHeader::onInput(string value)
	{
		mInput->filterOn();

		if(!mDropdown.down())
			mDropdown.dropdown(false);
	}

	void DropdownHeader::update(Widget* choice)
	{
		if(mInput && (mInput->typeIn().state() & FOCUSED))
		{
			mInput->typeIn().unfocus();
			mInput->hide();
		}

		if(mContent)
			this->release(*mContent);
		mContent = &this->append(choice->clone());
	}

	DropdownToggle::DropdownToggle(Dropdown& dropdown)
		: Button("", std::bind(&DropdownToggle::click, this))
		, mDropdown(dropdown)
	{
		mStyle = &cls();
	}

	void DropdownToggle::click()
	{
		if(mDropdown.header().input())
			mDropdown.header().input()->filterOff();
		mDropdown.dropdown();
	}

	DropdownLabel::DropdownLabel(const string& label)
		: Label(label)
	{}

	DropdownChoice::DropdownChoice(unique_ptr<Widget> content, const Trigger& trigger)
		: WrapButton(std::move(content), trigger)
	{
		mStyle = &cls();
		//content->setStyle(DropdownLabel::cls());
	}

	DropdownList::DropdownList(Dropdown& dropdown)
		: List(LAYER)
		, mDropdown(dropdown)
	{
		mStyle = &cls();
		mFrame = make_unique<Layer>(*this, 0);
	}

	bool DropdownList::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mDropdown.dropup();
		return true;
	}

	Typedown::Typedown(const Trigger& onSelected, StringVector choices)
		: Dropdown(onSelected, choices, true)
	{
		mStyle = &cls();
	}

	MenuList::MenuList(Menu& menu)
		: List(LAYER)
		, mMenu(menu)
	{
		mStyle = &cls();
		mFrame = make_unique<Layer>(*this, 0);
	}

	bool MenuList::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mMenu.dropup();
		return true;
	}

	Menu::Menu(const string& label, bool submenu)
		: Sheet()
		, mSubmenu(submenu)
		, mButton(this->makeappend<Button>(label, std::bind(&Menu::dropdown, this)))
		, mList(this->makeappend<MenuList>(*this))
		, mDown(false)
	{
		mStyle = &cls();
		mList.hide();
	}

	Widget& Menu::vappend(std::unique_ptr<Widget> widget)
	{
		return mList.append(std::move(widget));
	}

	unique_ptr<Widget> Menu::vrelease(Widget& widget)
	{
		return mList.release(widget);
	}

	void Menu::dropdown()
	{
		mList.show();
		mList.modal();
		mList.frame().as<Layer>().moveToTop();

		mDown = true;
	}

	void Menu::dropup()
	{
		mList.hide();
		if(mList.state() & MODAL)
			mList.unmodal();
		mDown = false;
	}
}
