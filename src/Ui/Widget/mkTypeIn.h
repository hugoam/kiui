//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTYPEIN_H
#define MK_WTYPEIN_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Controller/mkController.h>
#include <Ui/Widget/mkCheckbox.h>
#include <Ui/Widget/mkValue.h>

#include <Object/String/mkStringConvert.h>

namespace mk
{
	template <class T, class T_Val = T>
	class WTypedInput : public WValue
	{
	public:
		WTypedInput(Lref& value, Style* style = nullptr, std::function<void(T_Val)> callback = nullptr)
			: WValue(value, style)
			, mOnUpdate(callback)
			, mUpdate(0)
		{}

		WTypedInput(T value, Style* style = nullptr, std::function<void(T_Val)> callback = nullptr)
			: WValue(lref(value), style)
			, mOnUpdate(callback)
			, mUpdate(0)
		{}

		void notifyUpdate() { ++mUpdate; if(mOnUpdate) mOnUpdate(mValue->get<T>()); this->updateValue(); }

	protected:
		std::function<void(T_Val)> mOnUpdate;
		size_t mUpdate;
	};

	class MK_UI_EXPORT _I_ TypeIn : public Sheet, public Typed<TypeIn>, public Styled<TypeIn>
	{
	public:
		TypeIn(WValue* input, Style* style = nullptr);

		Style* hoverCursor() { return CaretCursor::styleCls(); }
		const string& label() { return mString; }
		
		void nextFrame(size_t tick, size_t delta);

		void setAllowedChars(const string& chars);

		void activated();
		void deactivated();

		void erase();
		void insert(char c);
		void updateString();

		bool leftClick(float xPos, float yPos);
		bool keyDown(KeyCode code, char c);

		using Typed<TypeIn>::cls;

	protected:
		WValue* mInput;
		string mString;
		bool mHasPeriod;
		string mAllowedChars;
		Caret* mCaret;
	};

	class MK_UI_EXPORT _I_ Textbox : public TypeIn, public Typed<Textbox>, public Styled<Textbox>
	{
	public:
		Textbox(WValue* input);
		Textbox(const string& text);

		using Typed<Textbox>::cls;
		using Styled<Textbox>::styleCls;

	protected:
		string mString;
	};
	
	class MK_UI_EXPORT NumberControls : public Sheet, public Styled<NumberControls>
	{
	public:
		NumberControls(const Trigger& plus, Trigger minus);

	protected:
		Trigger mPlusTrigger;
		Trigger mMinusTrigger;
		Button* mPlus;
		Button* mMinus;
	};

	template <class T>
	class NumberInput : public WTypedInput<T>
	{
	public:
		NumberInput(Lref& value, std::function<void(T)> callback = nullptr)
			: WTypedInput<T>(value, nullptr, callback)
			, mStep(1)
		{
			this->build();
		}

		NumberInput(T value, std::function<void(T)> callback = nullptr)
			: WTypedInput<T>(value, nullptr, callback)
			, mStep(1)
		{
			this->build();
		}

		void build()
		{
			mTypeIn = this->template makeappend<TypeIn>(this);
			mControls = this->template makeappend<NumberControls>(std::bind(&NumberInput<T>::increment, this), std::bind(&NumberInput<T>::decrement, this));

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
		TypeIn* mTypeIn;
		NumberControls* mControls;
		T mStep;
	};

	template <class T>
	class Input
	{};

	template <>
	class MK_UI_EXPORT _I_ Input<int> : public NumberInput<int>
	{
	public:
		Input(Lref& value, std::function<void(int)> callback = nullptr)
			: NumberInput<int>(value, callback)
		{}

		Input(int value, std::function<void(int)> callback = nullptr)
			: NumberInput<int>(value, callback)
		{}
	};

	template <>
	class MK_UI_EXPORT _I_ Input<float> : public NumberInput<float>
	{
	public:
		Input(Lref& value, std::function<void(float)> callback = nullptr)
			: NumberInput<float>(value, callback)
		{}

		Input(float value, std::function<void(float)> callback = nullptr)
			: NumberInput<float>(value, callback)
		{}
	};

	template <>
	class MK_UI_EXPORT _I_ Input<double> : public NumberInput<double>
	{
	public:
		Input(Lref& value, std::function<void(double)> callback = nullptr)
			: NumberInput<double>(value, callback)
		{}

		Input(double value, std::function<void(double)> callback = nullptr)
			: NumberInput<double>(value, callback)
		{}
	};

	template <>
	class MK_UI_EXPORT _I_ Input<bool> : public WTypedInput<bool>, public Typed<Input<bool>>, public Styled<Input<bool>>
	{
	public:
		Input(Lref& value, std::function<void(bool)> callback = nullptr)
			: WTypedInput<bool>(value, styleCls(), callback)
		{
			this->makeappend<Checkbox>(this, mValue->get<bool>());
		}

		Input(bool value, std::function<void(bool)> callback = nullptr)
			: WTypedInput<bool>(value, styleCls(), callback)
		{
			this->makeappend<Checkbox>(this, mValue->get<bool>());
		}

		using Styled<Input<bool>>::styleCls;
		using Typed<Input<bool>>::cls;
	};

	template <>
	class MK_UI_EXPORT _I_ Input<string> : public WTypedInput<string>
	{
	public:
		Input(Lref& value, std::function<void(string)> callback = nullptr)
			: WTypedInput<string>(value, nullptr, callback)
		{
			this->makeappend<TypeIn>(this);
		}

		Input(const string& value, std::function<void(string)> callback = nullptr)
			: WTypedInput<string>(value, nullptr, callback)
		{
			this->makeappend<TypeIn>(this);
		}
	};
}

#endif
