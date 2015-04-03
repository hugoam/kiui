//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkTypeIn.h>

#include <Object/mkRef.h>

#include <Object/String/mkStringConvert.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/mkUiWindow.h>

#include <iostream>

namespace mk
{
	TypeIn::TypeIn(WValue* input, Style* style)
		: Sheet(style ? style : styleCls())
		, mInput(input)
		, mHasPeriod(false)
	{
		if(mInput)
			mString = mInput->value()->getString();

		mCaret = this->makeappend<Caret>(mFrame.get());
		mCaret->hide();
	}

	void TypeIn::nextFrame(size_t tick, size_t delta)
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

	void TypeIn::activated()
	{
		if(mCaret->frame()->hidden())
			mCaret->show();
	}

	void TypeIn::deactivated()
	{
		if(!mCaret->frame()->hidden())
			mCaret->hide();
	}

	void TypeIn::setAllowedChars(const string& chars)
	{
		mAllowedChars = chars;
	}

	void TypeIn::erase()
	{
		if(mCaret->index() == 0)
			return;

		mString.erase(mString.begin() + mCaret->index() - 1);
		mCaret->setIndex(mCaret->index() - 1);
	}

	void TypeIn::insert(char c)
	{
		mString.insert(mString.begin() + mCaret->index(), c);
		mCaret->setIndex(mCaret->index() + 1);
	}

	void TypeIn::updateString()
	{
		mString = mInput->value()->getString();
		this->markDirty();
	}

	bool TypeIn::leftClick(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		mCaret->setIndex(mFrame->inkbox()->caretIndex(xPos - mFrame->dabsolute(DIM_X), yPos - mFrame->dabsolute(DIM_Y)));
		if(!(mState & ACTIVATED))
			this->activate();
		return true;
	}

	bool TypeIn::keyDown(KeyCode code, char c)
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
		else if(c != 0 && (mAllowedChars.size() == 0 || mAllowedChars.find(c) != string::npos))
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

	Textbox::Textbox(WValue* input)
		: TypeIn(input, styleCls())
	{}

	Textbox::Textbox(const string& text)
		: TypeIn(nullptr)
	{}

	NumberControls::NumberControls(const Trigger& plus, Trigger minus)
		: Sheet(styleCls())
		, mPlusTrigger(plus)
		, mMinusTrigger(minus)
	{
		mPlus = this->makeappend<Button>("+", nullptr, mPlusTrigger);
		mMinus = this->makeappend<Button>("-", nullptr, mMinusTrigger);
	}
}
