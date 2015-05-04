//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_INPUT_H_INCLUDED
#define MK_INPUT_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkRef.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkValue.h>
#include <Ui/Widget/mkSlider.h>
#include <Ui/Widget/mkTypeIn.h>

#include <Object/Util/mkStat.h>
#include <Object/Util/mkDispatch.h>

/* Standard */
#include <functional>

namespace mk
{
	template <class T_Val, class T_Arg = T_Val>
	class Field : public Sequence
	{
	public:
		Field(const string& label, const T_Val& value, std::function<void(T_Arg)> callback = nullptr, bool reverse = false)
			: Sequence()
			, mInput(this->template makeappend<Input<T_Val>>(value, callback))
			, mLabel(this->template makeappend<Label>(label))
		{
			UNUSED(reverse);
		}

		Input<T_Val>& input() { return mInput; }

		static StyleType& cls() { static StyleType ty("Field<" + typecls<T_Val>().name() + ">", Sequence::cls()); return ty; }

	protected:
		Input<T_Val>& mInput;
		Label& mLabel;
	};

	typedef Field<bool> InputBool;
	typedef Field<int> InputInt;
	typedef Field<float> InputFloat;
	typedef Field<string> InputText;

	class MK_UI_EXPORT InputRadio : public Sequence
	{
	public:
		InputRadio(const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr);

		static StyleType& cls() { static StyleType ty("InputDropdown", Sequence::cls()); return ty; }
	};

	class MK_UI_EXPORT InputDropdown : public Sequence
	{
	public:
		InputDropdown(const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool textinput = false, bool reverse = false);

		static StyleType& cls() { static StyleType ty("InputDropdown", Sequence::cls()); return ty; }
	};
	
	class MK_UI_EXPORT SliderInt : public Sequence
	{
	public:
		SliderInt(const string& label, AutoStat<int> value, std::function<void(int)> callback = nullptr);

		static StyleType& cls() { static StyleType ty("SliderInt", Sequence::cls()); return ty; }
	};

	class MK_UI_EXPORT SliderFloat : public Sequence
	{
	public:
		SliderFloat(const string& label, AutoStat<float> value, std::function<void(float)> callback = nullptr);

		static StyleType& cls() { static StyleType ty("SliderFloat", Sequence::cls()); return ty; }
	};
}

#endif // MK_INPUT_H_INCLUDED
