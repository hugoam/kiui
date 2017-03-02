//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUT_H
#define TOY_INPUT_H

/* toy */
#include <toyobj/Typed.h>
#include <toyobj/Ref.h>
#include <toyui/Forward.h>
#include <toyui/Edit/Value.h>
#include <toyui/Button/Slider.h>
#include <toyui/Button/RadioButton.h>
#include <toyui/Button/Dropdown.h>
#include <toyui/Edit/TypeIn.h>

#include <toyobj/Util/Stat.h>
#include <toyobj/Util/Dispatch.h>

/* std */
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DispatchInput : public HashDispatch<DispatchInput, Lref&, unique_ptr<WValue>>
	{
	public:
		static string name() { return "DispatchInput"; };
	};
	
	class TOY_UI_EXPORT DispatchDisplay : public HashDispatch<DispatchDisplay, Lref&, unique_ptr<Widget>>
	{
	public:
		static string name() { return "DispatchDisplay"; };
	};

	template <>
	class _I_ TOY_UI_EXPORT Input<Colour> : public WValue
	{
	public:
		Input(Piece& parent, Colour value, std::function<void(Colour)> callback = nullptr)
			: WValue(parent, lref(value), this->cls(), [callback](Lref& lref) { callback(lref->get<Colour>()); })
			, m_r(*this, AutoStat<float>(value.r(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setR(val); this->triggerModify(); })
			, m_g(*this, AutoStat<float>(value.g(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setG(val); this->triggerModify(); })
			, m_b(*this, AutoStat<float>(value.b(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setB(val); this->triggerModify(); })
			, m_a(*this, AutoStat<float>(value.a(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value->ref<Colour>().setA(val); this->triggerModify(); })
		{}

		void notifyUpdate()
		{
			Colour colour = this->m_value->get<Colour>();
			m_r.updateValue(colour.r());
			m_g.updateValue(colour.g());
			m_b.updateValue(colour.b());
			m_a.updateValue(colour.a());
		}

		static Type& cls() { static Type ty("InputColour", WValue::cls()); return ty; }

	protected:
		StatSlider<float> m_r;
		StatSlider<float> m_g;
		StatSlider<float> m_b;
		StatSlider<float> m_a;
	};

	template <class T_Val, class T_Arg, class T_Input>
	class Field : public WrapControl
	{
	public:
		Field(Piece& parent, const string& label, const T_Val& value, std::function<void(T_Arg)> callback = nullptr, bool reverse = false)
			: WrapControl(parent)
			, m_label(*this, label)
			, m_input(*this, value, callback)
		{
			if(reverse)
				this->swap(0, 1);
		}

		T_Input& input() { return m_input; }

		static Type& cls() { static Type ty("Field<" + typecls<T_Val>().name() + ">", WrapControl::cls()); return ty; }

	protected:
		Label m_label;
		T_Input m_input;
	};

	typedef Field<bool, bool, Input<bool>> InputBool;
	typedef Field<AutoStat<int>, int, Input<int>> InputInt;
	typedef Field<AutoStat<float>, float, Input<float>> InputFloat;
	typedef Field<string, string, Input<string>> InputText;

	typedef Field<Colour, Colour, Input<Colour>> InputColour;

	typedef Field<AutoStat<int>, int, StatSlider<int>> SliderInt;
	typedef Field<AutoStat<float>, float, StatSlider<float>> SliderFloat;

	class TOY_UI_EXPORT InputRadio : public WrapControl
	{
	public:
		InputRadio(Piece& parent, const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool reverse = false);

		static Type& cls() { static Type ty("InputRadio", WrapControl::cls()); return ty; }

	protected:
		Label m_label;
		RadioSwitch m_input;
	};

	class TOY_UI_EXPORT InputDropdown : public WrapControl
	{
	public:
		InputDropdown(Piece& parent, const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool reverse = false);

		static Type& cls() { static Type ty("InputDropdown", WrapControl::cls()); return ty; }

	protected:
		Label m_label;
		DropdownInput m_input;
	};
}

#endif // TOY_INPUT_H
