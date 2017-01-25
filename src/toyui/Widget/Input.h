//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUT_H
#define TOY_INPUT_H

/* toy headers */
#include <toyobj/Typed.h>
#include <toyobj/Ref.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Value.h>
#include <toyui/Widget/Slider.h>
#include <toyui/Widget/TypeIn.h>

#include <toyobj/Util/Stat.h>
#include <toyobj/Util/Dispatch.h>

/* std */
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DispatchInput : public HashDispatch<DispatchInput, Lref&, unique_ptr<WValue>>
	{};
	
	class TOY_UI_EXPORT DispatchDisplay : public HashDispatch<DispatchDisplay, Lref&, unique_ptr<Widget>>
	{};

	template <>
	class _I_ TOY_UI_EXPORT Input<Colour> : public WValue
	{
	public:
		Input(Colour value, std::function<void(Colour)> callback = nullptr)
			: WValue(lref(value), this->cls(), [callback](Lref& lref) { callback(lref->get<Colour>()); })
			, m_r(this->makeappend<StatSlider<float>>(AutoStat<float>(value.r(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setR(val); this->triggerModify(); }))
			, m_g(this->makeappend<StatSlider<float>>(AutoStat<float>(value.g(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setG(val); this->triggerModify(); }))
			, m_b(this->makeappend<StatSlider<float>>(AutoStat<float>(value.b(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setB(val); this->triggerModify(); }))
			, m_a(this->makeappend<StatSlider<float>>(AutoStat<float>(value.a(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setA(val); this->triggerModify(); }))
		{}

		void notifyUpdate()
		{
			Colour colour = this->m_value->get<Colour>();
			m_r.updateValue(colour.r());
			m_g.updateValue(colour.g());
			m_b.updateValue(colour.b());
			m_a.updateValue(colour.a());
		}

		static StyleType& cls() { static StyleType ty("InputColour", Band::cls()); return ty; }

	protected:
		StatSlider<float>& m_r;
		StatSlider<float>& m_g;
		StatSlider<float>& m_b;
		StatSlider<float>& m_a;
	};

	template <class T_Val, class T_Arg, class T_Input>
	class Field : public Band
	{
	public:
		Field(const string& label, const T_Val& value, std::function<void(T_Arg)> callback = nullptr, bool reverse = false)
			: Band()
		{
			if(!reverse) this->template makeappend<Label>(label);
			m_input = &this->template makeappend<T_Input>(value, callback);
			if(reverse) this->template makeappend<Label>(label);
		}

		T_Input& input() { return *m_input; }

		static StyleType& cls() { static StyleType ty("Field<" + typecls<T_Val>().name() + ">", Band::cls()); return ty; }

	protected:
		T_Input* m_input;
	};

	typedef Field<bool, bool, Input<bool>> InputBool;
	typedef Field<AutoStat<int>, int, Input<int>> InputInt;
	typedef Field<AutoStat<float>, float, Input<float>> InputFloat;
	typedef Field<string, string, Input<string>> InputText;

	typedef Field<Colour, Colour, Input<Colour>> InputColour;

	typedef Field<AutoStat<int>, int, StatSlider<int>> SliderInt;
	typedef Field<AutoStat<float>, float, StatSlider<float>> SliderFloat;

	class TOY_UI_EXPORT InputRadio : public Band
	{
	public:
		InputRadio(const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool reverse = false);

		static StyleType& cls() { static StyleType ty("InputDropdown", Band::cls()); return ty; }
	};

	class TOY_UI_EXPORT InputDropdown : public Band
	{
	public:
		InputDropdown(const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool textinput = false, bool reverse = false);

		static StyleType& cls() { static StyleType ty("InputDropdown", Band::cls()); return ty; }
	};
}

#endif // TOY_INPUT_H
