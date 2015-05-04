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
	TypeIn::TypeIn(WValue* input, const string& text)
		: Sheet()
		, mInput(input)
		, mHasPeriod(false)
		, mCaret(this->makeappend<Caret>(mFrame.get()))
	{
		mStyle = &cls();
		if(mInput)
			mString = mInput->value()->getString();
		else
			mString = text;
		
		mCaret.hide();
	}

	void TypeIn::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);

		if(mState & FOCUSED)
		{
			bool odd = (tick / 25) % 2;
			if(odd && mCaret.frame().hidden())
				mCaret.show();
			else if(!odd && !mCaret.frame().hidden())
				mCaret.hide();
		}
	}

	void TypeIn::focused()
	{
		if(mCaret.frame().hidden())
			mCaret.show();
	}

	void TypeIn::unfocused()
	{
		if(!mCaret.frame().hidden())
			mCaret.hide();
	}

	void TypeIn::setAllowedChars(const string& chars)
	{
		mAllowedChars = chars;
	}

	void TypeIn::erase()
	{
		if(mCaret.index() == 0 && mFrame->inkbox().selectStart() == mFrame->inkbox().selectEnd())
			return;

		if(mFrame->inkbox().selectStart() == mFrame->inkbox().selectEnd())
		{
			mString.erase(mString.begin() + mFrame->inkbox().selectStart() - 1);
			mCaret.setIndex(mCaret.index() - 1);
			mFrame->inkbox().selectCaret(mCaret.index());
		}
		else
		{
			mString.erase(mString.begin() + mFrame->inkbox().selectStart(), mString.begin() + mFrame->inkbox().selectEnd());
			mCaret.setIndex(mFrame->inkbox().selectStart());
			mFrame->inkbox().selectCaret(mCaret.index());
		}
	}

	void TypeIn::insert(char c)
	{
		mString.insert(mString.begin() + mCaret.index(), c);
		mCaret.setIndex(mCaret.index() + 1);
		mFrame->inkbox().selectCaret(mCaret.index());
	}

	void TypeIn::updateString()
	{
		mString = mInput->value()->getString();
		this->markDirty();
	}

	bool TypeIn::leftClick(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		size_t index = mFrame->inkbox().caretIndex(xPos - mFrame->dabsolute(DIM_X), yPos - mFrame->dabsolute(DIM_Y));
		mCaret.setIndex(index);
		mFrame->inkbox().selectCaret(mCaret.index());
		if(!(mState & FOCUSED))
			this->focus();
		return true;
	}

	bool TypeIn::leftDragStart(float xPos, float yPos)
	{
		size_t index = mFrame->inkbox().caretIndex(xPos - mFrame->dabsolute(DIM_X), yPos - mFrame->dabsolute(DIM_Y));
		mCaret.setIndex(index);
		mFrame->inkbox().selectFirst(index);
		if(!(mState & FOCUSED))
			this->focus();
		return true;
	}

	bool TypeIn::leftDrag(float xPos, float yPos, float xDif, float yDif)
	{
		UNUSED(xDif); UNUSED(yDif);
		size_t index = mFrame->inkbox().caretIndex(xPos - mFrame->dabsolute(DIM_X), yPos - mFrame->dabsolute(DIM_Y));
		mFrame->inkbox().selectSecond(index);
		mCaret.setIndex(index);
		return true;
	}

	bool TypeIn::leftDragEnd(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		return true;
	}

	bool TypeIn::keyDown(KeyCode code, char c)
	{
		if(code == KC_LEFT && mCaret.index() > 0)
		{
			mCaret.moveLeft();
		}
		else if(code == KC_RIGHT && mCaret.index() < mString.size())
		{
			mCaret.moveRight();
		}
		else if(code == KC_RETURN)
		{
			this->insert('\n');
			//this->unfocus();
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

		if(mInput)
			mInput->setString(mString);
		this->markDirty();
		
		return true;
	}
}
