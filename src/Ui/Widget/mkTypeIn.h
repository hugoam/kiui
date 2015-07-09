//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TYPEIN_H
#define MK_TYPEIN_H

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
		WTypedInput(Lref& value, std::function<void(T_Val)> callback = nullptr)
			: WValue(value)
			, mOnUpdate(callback)
		{}

		WTypedInput(T value, std::function<void(T_Val)> callback = nullptr)
			: WValue(lref(value))
			, mOnUpdate(callback)
		{}

		void notifyModify() { if(mOnUpdate) mOnUpdate(mValue->get<T>()); }

	protected:
		std::function<void(T_Val)> mOnUpdate;
	};

	class MK_UI_EXPORT _I_ TextSelection : public Widget
	{
	public:
		TextSelection();
	};

	class MK_UI_EXPORT _I_ TypeIn : public Sheet
	{
	public:
		TypeIn(WValue* input, const string& text = "");

		Style* hoverCursor() { return &CaretCursor::cls(); }
		const string& label() { return mString; }
		
		void nextFrame(size_t tick, size_t delta);

		void setAllowedChars(const string& chars);

		void focused();
		void unfocused();

		void erase();
		void insert(char c);
		void updateString();

		bool leftClick(float xPos, float yPos);
		bool keyDown(KeyCode code, char c);

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		static StyleType& cls() { static StyleType ty("TypeIn", Sheet::cls()); return ty; }

	protected:
		WValue* mInput;
		string mString;
		bool mHasPeriod;
		string mAllowedChars;
		Caret& mCaret;
		std::vector<TextSelection*> mSelection;
	};

	template <class T>
	class NumberInput : public WTypedInput<T>
	{
	public:
		NumberInput(Lref& value, std::function<void(T)> callback = nullptr)
			: WTypedInput<T>(value, callback)
			, mTypeIn(this->template makeappend<TypeIn>(this))
			, mPlus(this->template makeappend<Button>("+", std::bind(&NumberInput<T>::increment, this)))
			, mMinus(this->template makeappend<Button>("-", std::bind(&NumberInput<T>::decrement, this)))
			, mStep(1)
			, mMinimum(std::numeric_limits<T>::lowest())
			, mMaximum(std::numeric_limits<T>::max())
		{
			this->mStyle = &cls();
			this->build();
		}

		NumberInput(T value, std::function<void(T)> callback = nullptr)
			: WTypedInput<T>(value, callback)
			, mTypeIn(this->template makeappend<TypeIn>(this))
			, mPlus(this->template makeappend<Button>("+", std::bind(&NumberInput<T>::increment, this)))
			, mMinus(this->template makeappend<Button>("-", std::bind(&NumberInput<T>::decrement, this)))
			, mStep(1)
			, mMinimum(std::numeric_limits<T>::lowest())
			, mMaximum(std::numeric_limits<T>::max())
		{
			this->mStyle = &cls();
			this->build();
		}

		void build()
		{
			if(&typecls<T>() == &typecls<float>() || &typecls<T>() == &typecls<double>())
				mTypeIn.setAllowedChars("1234567890.");
			else
				mTypeIn.setAllowedChars("1234567890");
		}

		void increment()
		{
			const auto currentValue = this->mValue->template get<T>();
			if (mMaximum == currentValue)
				return;

			if (mMaximum - mStep <= currentValue)
				this->mValue->template set<T>(mMaximum);
			else
				this->mValue->template set<T>(currentValue + mStep);

			mTypeIn.updateString();
			this->triggerModify();
		}

		void decrement()
		{
			const auto currentValue = this->mValue->template get<T>();
			if (mMinimum == currentValue)
				return;

			if (mMinimum + mStep >= currentValue)
				this->mValue->template set<T>(mMinimum);
			else
				this->mValue->template set<T>(currentValue - mStep);

			mTypeIn.updateString();
			this->triggerModify();
		}

		void notifyUpdate() { mTypeIn.updateString(); }

		static StyleType& cls() { static StyleType ty("NumberInput<" + typecls<T>().name() + ">", WValue::cls()); return ty; }

	protected:
		TypeIn& mTypeIn;
		Button& mPlus;
		Button& mMinus;
		T mStep;
		T mMinimum;
		T mMaximum;
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
	class MK_UI_EXPORT _I_ Input<bool> : public WTypedInput<bool>
	{
	public:
		Input(Lref& value, std::function<void(bool)> callback = nullptr)
			: WTypedInput<bool>(value, callback)
			, mCheckbox(this->makeappend<Checkbox>(this, mValue->get<bool>()))
		{
			this->mStyle = &cls();
		}

		Input(bool value, std::function<void(bool)> callback = nullptr)
			: WTypedInput<bool>(value, callback)
			, mCheckbox(this->makeappend<Checkbox>(this, mValue->get<bool>()))
		{
			this->mStyle = &cls();
		}

		void notifyUpdate() { mCheckbox.update(mValue->get<bool>()); }

		static StyleType& cls() { static StyleType ty("Input<bool>", WValue::cls()); return ty; }

	protected:
		Checkbox& mCheckbox;
	};

	template <>
	class MK_UI_EXPORT _I_ Input<string> : public WTypedInput<string>
	{
	public:
		Input(Lref& value, std::function<void(string)> callback = nullptr)
			: WTypedInput<string>(value, callback)
			, mTypeIn(this->makeappend<TypeIn>(this))
		{}

		Input(const string& value, std::function<void(string)> callback = nullptr)
			: WTypedInput<string>(value, callback)
			, mTypeIn(this->makeappend<TypeIn>(this))
		{}

		TypeIn& typeIn() { return mTypeIn; }

		void notifyUpdate() { mTypeIn.updateString(); }
		void notifyModify() { if(this->mOnUpdate) this->mOnUpdate(this->mValue->get<string>()); }

	protected:
		TypeIn& mTypeIn;
	};
}

#endif
