//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTYPEIN_H
#define MK_WTYPEIN_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Controller/mkController.h>
#include <Ui/Widget/mkWCheckbox.h>

namespace mk
{
	class MK_UI_EXPORT WTypeIn : public Widget, public Controller
	{
	public:
		WTypeIn(Form* form);

		Lref& value();

		bool leftClick(float xPos, float yPos);

		bool keyDown(KeyCode code, char c);

		void setAllowedChars(string chars);

	protected:
		Lref& mValue;
		string mString;
		bool mHasPeriod;
		string mAllowedChars;
	};

	class MK_UI_EXPORT WString : public WTypeIn
	{
	public:
		WString(Form* form);
	};

	class MK_UI_EXPORT WInt : public Sheet
	{
	public:
		WInt(Form* form);

		void build();

		void plus();
		void minus();

	protected:
		WTypeIn* mDisplay;
		Sheet* mControls;
		WButton* mPlus;
		WButton* mMinus;
	};

	class MK_UI_EXPORT WFloat : public Sheet
	{
	public:
		WFloat(Form* form);

		void build();
		
		void plus();
		void minus();

	protected:
		WTypeIn* mDisplay;
		Sheet* mControls;
		WButton* mPlus;
		WButton* mMinus;

	};

	class MK_UI_EXPORT WBool : public WCheckbox
	{
	public:
		WBool(Form* form);
	};
}

#endif
