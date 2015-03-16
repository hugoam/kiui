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
	class MK_UI_EXPORT _I_ WTypeIn : public Widget, public Controller, public Typed<WTypeIn>, public Styled<WTypeIn>
	{
	public:
		WTypeIn(Form* form, Style* style = nullptr);

		Lref& value();

		bool leftClick(float xPos, float yPos);

		bool keyDown(KeyCode code, char c);

		void setAllowedChars(const string& chars);

		using Typed<WTypeIn>::cls;

	protected:
		Lref& mValue;
		string mString;
		bool mHasPeriod;
		string mAllowedChars;
	};

	class MK_UI_EXPORT _I_ WString : public WTypeIn, public Typed<WString>, public Styled<WString>
	{
	public:
		WString(Form* form);

		using Typed<WString>::cls;
		using Styled<WString>::styleCls;
	};

	class MK_UI_EXPORT WNumControls : public Sheet, public Styled<WNumControls>
	{
	public:
		WNumControls(const Trigger& plus, Trigger minus);

		void build();

	protected:
		Trigger mPlusTrigger;
		Trigger mMinusTrigger;
		WButton* mPlus;
		WButton* mMinus;
	};

	class MK_UI_EXPORT _I_ WInt : public Sheet, public Typed<WInt>, public Styled<WInt>
	{
	public:
		WInt(Form* form);

		void build();

		void plus();
		void minus();

		using Typed<WInt>::cls;

	protected:
		WTypeIn* mDisplay;
		WNumControls* mControls;
	};

	class MK_UI_EXPORT _I_ WFloat : public Sheet, public Typed<WFloat>, public Styled<WFloat>
	{
	public:
		WFloat(Form* form);

		void build();
		
		void plus();
		void minus();

		using Typed<WFloat>::cls;

	protected:
		WTypeIn* mDisplay;
		WNumControls* mControls;
	};

	class MK_UI_EXPORT WBool : public WCheckbox, public Styled<WBool>
	{
	public:
		WBool(Form* form);
	};
}

#endif
