//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWRadioButton.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Form/mkFValue.h>

#include <Ui/mkUiWindow.h>

using namespace std::placeholders;

namespace mk
{
	WRadioChoice::WRadioChoice(Widget* content, const Trigger& trigger)
		: WWrapButton(content, styleCls(), trigger)
	{}

	WRadioSwitch::WRadioSwitch(const Trigger& onSelected, size_t active)
		: Sheet(styleCls())
		, mOnSelected(onSelected)
		, mActive(nullptr)
		, mActiveIndex(active)
	{}

	Sheet* WRadioSwitch::vaddwrapper(Widget* widget)
	{
		WWrapButton* button = this->makeappend<WRadioChoice>(widget, std::bind(&WRadioSwitch::activated, this, _1));
		if(button->frame()->index() == mActiveIndex)
		{
			mActive = button;
			mActive->activate();
		}
		return button;
	}

	unique_ptr<Widget> WRadioSwitch::vrelease(Widget* widget)
	{
		return widget->extract();
	}

	void WRadioSwitch::activated(WWrapButton* button)
	{
		if(mActive)
			mActive->deactivate();
		mActive = button;
		mActive->activate();
		mOnSelected(button->content());
	}

	RadioSwitch::RadioSwitch(const Trigger& onSelected, size_t active, StringVector labels)
		: Form(nullptr, "", [this, active]() { return make_unique<WRadioSwitch>(std::bind(&RadioSwitch::onSelected, this, _1), active); })
		, mOnSelected(onSelected)
	{
		for(string& label : labels)
			this->makeappend<Label>(label);
	}

	void RadioSwitch::onSelected(Widget* widget)
	{
		if(mOnSelected)
			mOnSelected(widget->form());
	}
}
