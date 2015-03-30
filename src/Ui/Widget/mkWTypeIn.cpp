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
		: Sheet(style ? style : styleCls())
		, mInput(input)
		, mHasPeriod(false)
	{
		mString = mInput->value()->getString();
	}

	void WTypeIn::build()
	{
		mCaret = this->makeappend<Caret>(mFrame.get());
		mCaret->hide();
	}

	void WTypeIn::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);

		if(mState & ACTIVATED)
		{
			bool odd = (tick / 25) % 2;
			if(odd && mCaret->frame()->hidden())
				mCaret->show();
			else if(!odd && !mCaret->frame()->hidden())
				mCaret->hide();
		}
	}

	void WTypeIn::activated()
	{
		if(mCaret->frame()->hidden())
			mCaret->show();
	}

	void WTypeIn::deactivated()
	{
		if(!mCaret->frame()->hidden())
			mCaret->hide();
	}

	void WTypeIn::setAllowedChars(const string& chars)
	{
		mAllowedChars = chars;
	}

	void WTypeIn::erase()
	{
		if(mCaret->index() == 0)
			return;

		mString.erase(mString.begin() + mCaret->index() - 1);
		mCaret->setIndex(mCaret->index() - 1);
	}

	void WTypeIn::insert(char c)
	{
		mString.insert(mString.begin() + mCaret->index(), c);
		mCaret->setIndex(mCaret->index() + 1);
	}

	void WTypeIn::updateString()
	{
		mString = mInput->value()->getString();
		this->markDirty();
	}

	bool WTypeIn::leftClick(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		mCaret->setIndex(mFrame->inkbox()->caretIndex(xPos - mFrame->dabsolute(DIM_X), yPos - mFrame->dabsolute(DIM_Y)));
		if(!(mState & ACTIVATED))
			this->activate();
		return true;
	}

	bool WTypeIn::keyDown(KeyCode code, char c)
	{
		if(code == KC_LEFT && mCaret->index() > 0)
		{
			mCaret->setIndex(mCaret->index() - 1);
		}
		else if(code == KC_RIGHT && mCaret->index() < mString.size())
		{
			mCaret->setIndex(mCaret->index() + 1);
		}
		else if(code == KC_RETURN)
		{
			this->deactivate();
			mInput->value()->setString(mString);
			mInput->notifyUpdate();
		}
		else if(code == KC_BACK)
		{
			this->erase();
		}
		else if(c != 0 && mAllowedChars.size() == 0 || mAllowedChars.find(c) != string::npos)
		{
			if(c == '.' && mString.find('.') != string::npos)
				return true;

			this->insert(c);
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
