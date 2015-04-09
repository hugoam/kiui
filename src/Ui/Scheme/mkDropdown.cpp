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

using namespace std::placeholders;

namespace mk
{
	Dropdown::Dropdown(const Trigger& onSelected, StringVector choices)
		: Sheet(styleCls())
		, mOnSelected(onSelected)
		, mSelected(nullptr)
		, mDown(false)
	{
		mHeader = this->makeappend<DropdownHeader>(std::bind(&Dropdown::dropdown, this));
		mDropbox = this->makeappend<DropdownBox>(this);
		mDropButton = this->makeappend<DropdownToggle>(std::bind(&Dropdown::dropdown, this));

		mDropbox->hide();

		for(string& choice : choices)
			this->emplace<Label>(choice);
	}

	Dropdown::~Dropdown()
	{}

	Sheet* Dropdown::vappend(std::unique_ptr<Widget> widget)
	{
		WrapButton* button = mDropbox->emplace<DropdownChoice>(widget.get(), std::bind(&Dropdown::selected, this, _1));
		button->append(std::move(widget));
		if(mSelected == nullptr)
		{
			mSelected = button;
			mHeader->append(button->content()->clone());
		}

		return button;
	}

	unique_ptr<Widget> Dropdown::vrelease(Widget* widget)
	{
		return widget->extract();
	}

	void Dropdown::dropup()
	{
		mDropbox->hide();
		if(mDropbox->state() & MODAL)
			mDropbox->unmodal();
		mDown = false;
	}

	void Dropdown::dropdown()
	{
		if(mDropbox->count() == 0)
			return;

		mDropbox->show();
		mDropbox->modal();
		mDropbox->frame()->as<Layer>()->moveToTop();

		mDropbox->frame()->setPositionDim(DIM_Y, mFrame->dsize(DIM_Y));

		mDown = true;
	}

	void Dropdown::selected(WrapButton* button)
	{
		if(mDown)
			this->dropup();

		mSelected = button;
		
		mHeader->clear();
		mHeader->append(button->content()->clone());

		mOnSelected(button->content());
	}

	DropdownHeader::DropdownHeader(const Trigger& trigger)
		: WrapButton(nullptr, styleCls(), trigger)
	{}

	DropdownToggle::DropdownToggle(const Trigger& trigger)
		: Button("", styleCls(), trigger)
	{}

	DropdownChoice::DropdownChoice(Widget* content, const Trigger& trigger)
		: WrapButton(content, styleCls(), trigger)
	{}

	DropdownBox::DropdownBox(Dropdown* dropdown)
		: Sheet(styleCls(), LAYER)
		, mDropdown(dropdown)
	{
		mFrame = make_unique<Layer>(this, 0);
	}

	bool DropdownBox::leftClick(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		mDropdown->dropup();
		return true;
	}
}
