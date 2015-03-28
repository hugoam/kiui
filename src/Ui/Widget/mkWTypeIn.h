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
#include <Ui/Form/mkFValue.h>

#include <Object/String/mkStringConvert.h>

namespace mk
{
	class MK_UI_EXPORT _I_ WInputBase : public Sheet, public Typed<WInputBase>, public Styled<WInputBase>
	{
	public:
		WInputBase(Lref& value, Style* style = nullptr);

		Lref& value() { return mValue; }

		virtual void notifyUpdate() = 0;

		using Typed<WInputBase>::cls;

	protected:
		Lref& mValue;
	};

	template <class T>
	class WTypedInput : public WInputBase
	{
	public:
		WTypedInput(Lref& value, Style* style = nullptr, std::function<void(T)> callback = nullptr)
			: WInputBase(value, style)
			, mOnUpdate(callback)
			, mUpdate(0)
		{}

		void notifyUpdate() { ++mUpdate; if(mOnUpdate) mOnUpdate(mValue->get<T>()); if(mForm) mForm->as<FValue>()->updateValue(); }

	protected:
		std::function<void(T)> mOnUpdate;
		size_t mUpdate;
	};

	class MK_UI_EXPORT _I_ WTypeIn : public Widget, public Typed<WTypeIn>, public Styled<WTypeIn>
	{
	public:
		WTypeIn(WInputBase* input, Style* style = nullptr);

		Style* hoverCursor() { return CaretCursor::styleCls(); }
		const string& label() { return mString; }

		bool leftClick(float xPos, float yPos);
		bool keyDown(KeyCode code, char c);

		void setAllowedChars(const string& chars);
		void updateString();

		using Typed<WTypeIn>::cls;

	protected:
		WInputBase* mInput;
		string mString;
		bool mHasPeriod;
		string mAllowedChars;
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

	template <class T>
	class WNumberInput : public WTypedInput<T>
	{
	public:
		WNumberInput(Lref& value, std::function<void(T)> callback = nullptr)
			: WTypedInput<T>(value, nullptr, callback)
			, mStep(1)
		{}

		void build()
		{
			mTypeIn = this->template makeappend<WTypeIn>(this);
			mControls = this->template makeappend<WNumControls>(std::bind(&WNumberInput<T>::increment, this), std::bind(&WNumberInput<T>::decrement, this));

			if(typecls<T>() == typecls<float>() || typecls<T>() == typecls<double>())
				mTypeIn->setAllowedChars("1234567890.");
			else
				mTypeIn->setAllowedChars("1234567890");
		}

		void increment()
		{
			this->mValue->template set<T>(this->mValue->template get<T>() + mStep);
			mTypeIn->updateString();
			this->notifyUpdate();
		}

		void decrement()
		{
			this->mValue->template set<T>(this->mValue->template get<T>() - mStep);
			mTypeIn->updateString();
			this->notifyUpdate();
		}

	protected:
		WTypeIn* mTypeIn;
		WNumControls* mControls;
		T mStep;
	};

	template <class T>
	class WInput
	{};

	template <>
	class MK_UI_EXPORT _I_ WInput<int> : public WNumberInput<int>
	{
	public:
		WInput(Lref& value, std::function<void(int)> callback = nullptr)
			: WNumberInput<int>(value, callback)
		{}
	};

	template <>
	class MK_UI_EXPORT _I_ WInput<float> : public WNumberInput<float>
	{
	public:
		WInput(Lref& value, std::function<void(float)> callback = nullptr)
			: WNumberInput<float>(value, callback)
		{}
	};

	template <>
	class MK_UI_EXPORT _I_ WInput<double> : public WNumberInput<double>
	{
	public:
		WInput(Lref& value, std::function<void(double)> callback = nullptr)
			: WNumberInput<double>(value, callback)
		{}
	};

	template <>
	class MK_UI_EXPORT _I_ WInput<bool> : public WTypedInput<bool>, public Typed<WInput<bool>>, public Styled<WInput<bool>>
	{
	public:
		WInput(Lref& value, std::function<void(bool)> callback = nullptr)
			: WTypedInput<bool>(value, styleCls(), callback)
		{}

		void build()
		{
			this->makeappend<WCheckbox>(this, mValue->get<bool>());
		}

		using Styled<WInput<bool>>::styleCls;
		using Typed<WInput<bool>>::cls;
	};

	template <>
	class MK_UI_EXPORT _I_ WInput<string> : public WTypedInput<string>
	{
	public:
		WInput(Lref& value, std::function<void(string)> callback = nullptr)
			: WTypedInput<string>(value, nullptr, callback)
		{}

		void build()
		{
			this->makeappend<WTypeIn>(this);
		}
	};
}

#endif
