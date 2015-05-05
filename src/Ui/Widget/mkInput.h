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
	template <>
	class MK_UI_EXPORT _I_ Input<Colour> : public WTypedInput<Colour>
	{
	public:
		Input(Colour value, std::function<void(Colour)> callback = nullptr)
			: WTypedInput<Colour>(value, callback)
			, mR(this->makeappend<StatSlider<float>>(AutoStat<float>(value.r(), 0.f, 1.f, 0.01f), [this](float val) { this->mValue->ref<Colour>().setR(val); this->triggerModify(); }))
			, mG(this->makeappend<StatSlider<float>>(AutoStat<float>(value.g(), 0.f, 1.f, 0.01f), [this](float val) { this->mValue->ref<Colour>().setG(val); this->triggerModify(); }))
			, mB(this->makeappend<StatSlider<float>>(AutoStat<float>(value.b(), 0.f, 1.f, 0.01f), [this](float val) { this->mValue->ref<Colour>().setB(val); this->triggerModify(); }))
			, mA(this->makeappend<StatSlider<float>>(AutoStat<float>(value.a(), 0.f, 1.f, 0.01f), [this](float val) { this->mValue->ref<Colour>().setA(val); this->triggerModify(); }))
		{}

		void notifyUpdate()
		{
			Colour colour = this->mValue->get<Colour>();
			mR.updateValue(colour.r());
			mG.updateValue(colour.g());
			mB.updateValue(colour.b());
			mA.updateValue(colour.a());
		}

		static StyleType& cls() { static StyleType ty("InputColour", Sequence::cls()); return ty; }

	protected:
		StatSlider<float>& mR;
		StatSlider<float>& mG;
		StatSlider<float>& mB;
		StatSlider<float>& mA;
	};

	template <class T_Val, class T_Arg, class T_Input>
	class Field : public Sequence
	{
	public:
		Field(const string& label, const T_Val& value, std::function<void(T_Arg)> callback = nullptr, bool reverse = false)
			: Sequence()
		{
			if(!reverse) this->template makeappend<Label>(label);
			mInput = &this->template makeappend<T_Input>(value, callback);
			if(reverse) this->template makeappend<Label>(label);
		}

		T_Input& input() { return *mInput; }

		static StyleType& cls() { static StyleType ty("Field<" + typecls<T_Val>().name() + ">", Sequence::cls()); return ty; }

	protected:
		T_Input* mInput;
	};

	typedef Field<bool, bool, Input<bool>> InputBool;
	typedef Field<int, int, Input<int>> InputInt;
	typedef Field<float, float, Input<float>> InputFloat;
	typedef Field<string, string, Input<string>> InputText;

	typedef Field<Colour, Colour, Input<Colour>> InputColour;

	typedef Field<AutoStat<int>, int, StatSlider<int>> SliderInt;
	typedef Field<AutoStat<float>, float, StatSlider<float>> SliderFloat;

	class MK_UI_EXPORT InputRadio : public Sequence
	{
	public:
		InputRadio(const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool reverse = false);

		static StyleType& cls() { static StyleType ty("InputDropdown", Sequence::cls()); return ty; }
	};

	class MK_UI_EXPORT InputDropdown : public Sequence
	{
	public:
		InputDropdown(const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool textinput = false, bool reverse = false);

		static StyleType& cls() { static StyleType ty("InputDropdown", Sequence::cls()); return ty; }
	};
}

#endif // MK_INPUT_H_INCLUDED
