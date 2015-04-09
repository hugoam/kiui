//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkRadioButton.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/mkUiWindow.h>

using namespace std::placeholders;

namespace mk
{
	RadioChoice::RadioChoice(Widget* content, const Trigger& trigger)
		: WrapButton(content, styleCls(), trigger)
	{}

	RadioSwitch::RadioSwitch(const Trigger& onSelected, size_t active, StringVector labels)
		: Sheet(styleCls())
		, mOnSelected(onSelected)
		, mActive(nullptr)
		, mActiveIndex(active)
	{
		for(string& label : labels)
			this->emplace<Label>(label);
	}

	Sheet* RadioSwitch::vappend(unique_ptr<Widget> widget)
	{
		WrapButton* button = this->makeappend<RadioChoice>(widget.get(), std::bind(&RadioSwitch::activated, this, _1));
		button->append(std::move(widget));
		if(mContents.size() - 1 == mActiveIndex)
		{
			mActive = button;
			mActive->activate();
		}
		return button;
	}

	unique_ptr<Widget> RadioSwitch::vrelease(Widget* widget)
	{
		return widget->extract();
	}

	void RadioSwitch::activated(WrapButton* button)
	{
		if(mActive)
			mActive->deactivate();
		mActive = button;
		mActive->activate();
		if(mOnSelected)
			mOnSelected(button->content());
	}
}
