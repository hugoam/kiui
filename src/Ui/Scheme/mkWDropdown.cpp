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

#include <Ui/Frame/mkFrame.h>

#include <Ui/mkUiWindow.h>

using namespace std::placeholders;

namespace mk
{
	WDropdown::WDropdown(Trigger onSelected)
		: Sheet("dropdown")
		, mOnSelected(onSelected)
		, mSelected(nullptr)
		, mDown(false)
	{}

	WDropdown::~WDropdown()
	{}

	void WDropdown::build()
	{
		Sheet::build();
		mHeader = this->makeappend<Sheet>("dropdownheader");
		mDropbox = this->makeappend<WDropdownBox>();
		mDropButton = this->makeappend<WButton>("", "dropdownbutton", std::bind(&WDropdown::dropdown, this));

		mDropbox->frame()->hide();
	}

	Sheet* WDropdown::vaddwrapper(Widget* widget)
	{
		WWrapButton* button = mDropbox->makeappend<WWrapButton>(widget, "dropbutton", std::bind(&WDropdown::selected, this, _1));
		if(mSelected == nullptr)
		{
			mSelected = button;
			mHeader->makeappend<Widget>("", widget->form());
		}

		return button;
	}

	std::unique_ptr<Widget> WDropdown::vrelease(Widget* widget)
	{
		return widget->extract();
	}

	void WDropdown::dropup()
	{
		mDropbox->rebind(this);
		mDropbox->frame()->hide();
		uiWindow()->modalOff();

		mDown = false;
	}

	void WDropdown::dropdown()
	{
		if(mDropbox->contents()->size() == 0)
			return;

		mDropbox->rebind(this->rootWidget());
		mDropbox->frame()->show();
		mDropbox->frame()->moveToTop();

		uiWindow()->modalOn(mDropbox);

		Frame* frame = mFrame.get(); //mHeader->frame();
		mDropbox->frame()->setPosition(frame->dabsolute(DIM_X), frame->dabsolute(DIM_Y) + frame->dsize(DIM_Y));

		mDown = true;
	}

	void WDropdown::selected(WWrapButton* button)
	{
		if(mDown)
			this->dropup();

		mSelected = button;
		
		mHeader->clear();
		mHeader->makeappend<Widget>("", button->content()->form());

		mOnSelected(button->content());
	}

	WDropdownBox::WDropdownBox()
		: Sheet("dropdownbox")
	{}

	bool WDropdownBox::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mParent->as<WDropdown>()->dropup();
		return true;
	}

	Dropdown::Dropdown(Trigger onSelected, std::function<void(string)> onSelectedString)
		: Form("dropdown", "", [this](){ return std::make_unique<WDropdown>(std::bind(&Dropdown::onSelected, this, _1)); })
		, mOnSelected(onSelected)
		, mOnSelectedString(onSelectedString)
	{}

	Dropdown::Dropdown(std::function<void(string)> onSelected, StringVector choices)
		: Dropdown(nullptr, onSelected)
	{
		for(string& choice : choices)
			this->makeappend<Label>("", choice);
	}

	void Dropdown::onSelected(Widget* widget)
	{
		if(mOnSelected)
			mOnSelected(widget->form());
		else if(mOnSelectedString)
			mOnSelectedString(string(widget->form()->label()));
	}
}
