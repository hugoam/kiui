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
		, mOnSelected(onSelected)
		, mSelected(nullptr)
		, mDown(false)
		, mDropbox(this->makeappend<DropdownBox>(*this))
		, mHeader(this->makeappend<DropdownHeader>(*this, input))
		, mToggle(this->makeappend<DropdownToggle>(*this))
	{
		mStyle = &cls();
		mDropbox.hide();

		for(string& choice : choices)
			this->emplace<Label>(choice);
	}

	Dropdown::~Dropdown()
	{}

	Widget& Dropdown::vappend(std::unique_ptr<Widget> widget)
	{
		WrapButton& button = mDropbox.emplace<DropdownChoice>(widget.get(), std::bind(&Dropdown::selected, this, _1));
		button.append(std::move(widget));

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
		mDropbox.hide();
		if(mDropbox.state() & MODAL)
			mDropbox.unmodal();
		mDown = false;
	}

	void Dropdown::dropdown(bool modal)
	{
		if(mDropbox.count() == 0)
			return;

		mDropbox.show();
		if(modal)
			mDropbox.modal();

		mDropbox.frame().as<Layer>().moveToTop();
		mDropbox.frame().setPositionDim(DIM_Y, mFrame->dsize(DIM_Y));

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
			mInput->setString(mContent->contentlabel());
			mInput->show();
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
		if(mInput)
			mInput->hide();
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

	DropdownChoice::DropdownChoice(Widget* content, const Trigger& trigger)
		: WrapButton(content, trigger)
	{
		mStyle = &cls();
		//content->setStyle(DropdownLabel::cls());
	}

	DropdownBox::DropdownBox(Dropdown& dropdown)
		: FilterList(LAYER)
		, mDropdown(dropdown)
	{
		mStyle = &cls();
		mFrame = make_unique<Layer>(*this, 0);
	}

	bool DropdownBox::leftClick(float x, float y)
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
}
