//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWDropdown.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkRootForm.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Frame/mkFrame.h>

#include <Ui/Widget/mkRootSheet.h>

using namespace std::placeholders;

namespace mk
{
	WDropdown::WDropdown(const Trigger& onSelected)
		: Sheet(styleCls())
		, mOnSelected(onSelected)
		, mSelected(nullptr)
		, mDown(false)
	{}

	WDropdown::~WDropdown()
	{}

	void WDropdown::build()
	{
		Sheet::build();
		mHeader = this->makeappend<WDropdownHeader>();
		mDropbox = this->makeappend<WDropdownBox>(this);
		mDropButton = this->makeappend<WDropdownToggle>(std::bind(&WDropdown::dropdown, this));

		mDropbox->hide();
	}

	Sheet* WDropdown::vaddwrapper(Widget* widget)
	{
		WWrapButton* button = mDropbox->makeappend<WDropdownChoice>(widget, std::bind(&WDropdown::selected, this, _1));
		if(mSelected == nullptr)
		{
			mSelected = button;
			mHeader->makeappend<Widget>(nullptr, widget->form());
		}

		return button;
	}

	unique_ptr<Widget> WDropdown::vrelease(Widget* widget)
	{
		return widget->extract();
	}

	void WDropdown::dropup()
	{
		mDropbox->hide();
		this->rootSheet()->modalOff();

		mDown = false;
	}

	void WDropdown::dropdown()
	{
		if(mDropbox->contents().size() == 0)
			return;

		mDropbox->show();
		mDropbox->frame()->as<Layer>()->moveToTop();

		this->rootSheet()->modalOn(mDropbox);

		mDropbox->frame()->setPositionDim(DIM_Y, mFrame->dsize(DIM_Y));

		mDown = true;
	}

	void WDropdown::selected(WWrapButton* button)
	{
		if(mDown)
			this->dropup();

		mSelected = button;
		
		mHeader->clear();
		mHeader->makeappend<Widget>(nullptr, button->content()->form());

		mOnSelected(button->content());
	}

	WDropdownHeader::WDropdownHeader()
		: Sheet(styleCls())
	{}

	WDropdownToggle::WDropdownToggle(const Trigger& trigger)
		: WButton("", styleCls(), trigger)
	{}

	WDropdownChoice::WDropdownChoice(Widget* content, const Trigger& trigger)
		: WWrapButton(content, styleCls(), trigger)
	{}

	WDropdownBox::WDropdownBox(WDropdown* dropdown)
		: Sheet(styleCls())
		, mDropdown(dropdown)
	{}

	bool WDropdownBox::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mDropdown->dropup();
		return true;
	}

	Dropdown::Dropdown(const Trigger& onSelected, std::function<void(const string&)> onSelectedString)
		: Form(nullptr, "", [this](){ return make_unique<WDropdown>(std::bind(&Dropdown::onSelected, this, _1)); })
		, mOnSelected(onSelected)
		, mOnSelectedString(onSelectedString)
	{}

	Dropdown::Dropdown(std::function<void(const string&)> onSelected, StringVector choices)
		: Dropdown(nullptr, onSelected)
	{
		for(string& choice : choices)
			this->makeappend<Label>(choice);
	}

	void Dropdown::onSelected(Widget* widget)
	{
		if(mOnSelected)
			mOnSelected(widget->form());
		else if(mOnSelectedString)
			mOnSelectedString(string(widget->form()->label()));
	}
}
