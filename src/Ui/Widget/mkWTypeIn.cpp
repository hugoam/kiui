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

namespace mk
{
	WTypeIn::WTypeIn(Form* form)
		: Widget("typein", form)
		, mValue(form->as<FValue>()->valref())
		, mHasPeriod(false)
	{
		mString = form->as<FValue>()->toString();
		mForm->setLabel(mString);
	}

	Lref& WTypeIn::value()
	{
		return mForm->as<FValue>()->valref();
	}

	void WTypeIn::setAllowedChars(string chars)
	{
		mAllowedChars = chars;
	}

	bool WTypeIn::leftClick(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		this->activate();
		this->stack(this);
		mString = "";
		mForm->setLabel(mString);
		return true;
	}

	bool WTypeIn::keyDown(KeyCode code, char c)
	{
		if(code == KC_RETURN)
		{
			this->deactivate();
			this->yield();
			mForm->as<FValue>()->setString(mString);
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

		mForm->as<FValue>()->setString(mString);
		mForm->setLabel(mString);

		return true;
	}

	WString::WString(Form* form)
		: WTypeIn(form)
	{}

	WInt::WInt(Form* form)
		: Sheet("", form)
	{}

	void WInt::build()
	{
		mDisplay = this->makeappend<WTypeIn>(mForm);
		mDisplay->setAllowedChars("1234567890");
		mControls = this->makeappend<Sheet>("controls");
		mPlus = mControls->makeappend<WButton>("+", "button", std::bind(&WInt::plus, this));
		mMinus = mControls->makeappend<WButton>("-", "button", std::bind(&WInt::minus, this));
	}

	void WInt::plus()
	{
		mDisplay->value()->ref<int>() = mDisplay->value()->get<int>() + 1;
	}

	void WInt::minus()
	{
		mDisplay->value()->ref<int>() = mDisplay->value()->get<int>() - 1;
	}

	WFloat::WFloat(Form* form)
		: Sheet("", form)
	{}

	void WFloat::build()
	{
		mDisplay = this->makeappend<WTypeIn>(mForm);
		mDisplay->setAllowedChars("1234567890.");
		mControls = this->makeappend<Sheet>("controls");
		mPlus = mControls->makeappend<WButton>("+", "button", std::bind(&WFloat::plus, this));
		mMinus = mControls->makeappend<WButton>("-", "button", std::bind(&WFloat::minus, this));
	}

	void WFloat::plus()
	{
		mDisplay->value()->ref<float>() = mDisplay->value()->get<float>() + 0.1f;
	}

	void WFloat::minus()
	{
		mDisplay->value()->ref<float>() = mDisplay->value()->get<float>() - 0.1f;
	}

	WBool::WBool(Form* form)
		: WCheckbox(form, form->as<FValue>()->valref())
	{}
}
