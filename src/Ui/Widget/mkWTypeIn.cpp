//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWTypeIn.h>

#include <Object/mkRef.h>

#include <Object/String/mkStringConvert.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Form/mkFValue.h>

#include <Ui/mkUiWindow.h>

#include <iostream>

namespace mk
{
	WInputBase::WInputBase(Lref& value, Style* style)
		: Sheet(style ? style : styleCls())
		, mValue(value)
	{}

	WTypeIn::WTypeIn(WInputBase* input, Style* style)
		: Widget(style ? style : styleCls())
		, mInput(input)
		, mHasPeriod(false)
	{
		mString = mInput->value()->getString();
	}

	void WTypeIn::setAllowedChars(const string& chars)
	{
		mAllowedChars = chars;
	}

	void WTypeIn::updateString()
	{
		mString = mInput->value()->getString();
		this->markDirty();
	}

	bool WTypeIn::leftClick(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		this->activate();
		return true;
	}

	bool WTypeIn::keyDown(KeyCode code, char c)
	{
		if(code == KC_RETURN)
		{
			this->deactivate();
			mInput->value()->setString(mString);
			mInput->notifyUpdate();
		}
		else if(code == KC_BACK)
		{
			mString.pop_back();
		}
		else if(mAllowedChars.size() == 0 || mAllowedChars.find(c) != string::npos)
		{
			if(c == '.' && mString.find('.') != string::npos)
				return true;

			mString.push_back(c);
		}

		mInput->value()->setString(mString);
		mInput->notifyUpdate();
		this->markDirty();
		
		return true;
	}

	WNumControls::WNumControls(const Trigger& plus, Trigger minus)
		: Sheet(styleCls())
		, mPlusTrigger(plus)
		, mMinusTrigger(minus)
	{}

	void WNumControls::build()
	{
		mPlus = this->makeappend<WButton>("+", nullptr, mPlusTrigger);
		mMinus = this->makeappend<WButton>("-", nullptr, mMinusTrigger);
	}
}
