//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUT_H
#define TOY_INPUT_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/Any.h>
#include <toyui/Forward.h>
#include <toyui/Types.h>
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
	class TOY_UI_EXPORT DispatchInput : public Dispatcher<object_ptr<WValue>, Lref&>, public LazyGlobal<DispatchInput>
	{};
	
	class TOY_UI_EXPORT DispatchDisplay : public Dispatcher<object_ptr<Widget>, Lref&>, public LazyGlobal<DispatchDisplay>
	{};


	template <class T>
	class StatSlider : public WValue
	{
	public:
		StatSlider(Wedge& parent, Lref& lref, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WValue(parent, lref, this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value.template any<AutoStat<T>>())
			, m_dim(dim)
			, m_slider(*this, m_dim, std::bind(&StatSlider::updateStat, this))
			, m_display(*this, this->getString())
		{
			this->updateSlider();
		}

		StatSlider(Wedge& parent, AutoStat<T> value, std::function<void(T)> callback = nullptr, Dimension dim = DIM_X)
			: WValue(parent, var(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value.template any<AutoStat<T>>())
			, m_dim(dim)
			, m_slider(*this, m_dim, std::bind(&StatSlider::updateStat, this))
			, m_display(*this, this->getString())
		{
			this->updateSlider();
		}

		void updateSlider()
		{
			m_slider.resetMetrics(float(m_stat.min()), float(m_stat.max()), float(m_stat.value()), float(m_stat.step()));
			m_slider.updateKnob();
			m_display.setLabel(this->getString());
		}

		void updateStat()
		{
			m_stat.modify(T(m_slider.val()));
			m_display.setLabel(this->getString());
			this->triggerModify();
		}

		void updateValue(T val) { m_stat.modify(val); this->triggerUpdate(); }
		void modifyValue(T val) { m_stat.modify(val); this->triggerModify(); }

		void notifyUpdate() { this->updateSlider(); }
		void notifyModify() { this->updateSlider(); }

		static Type& cls() { static Type ty("StatSlider<" + typecls<T>().name() + ">", WValue::cls()); return ty; }

	protected:
		AutoStat<T>& m_stat;

		Dimension m_dim;

		Slider m_slider;
		SliderDisplay m_display;
	};

	template class _refl_ TOY_UI_EXPORT StatSlider<float>;
	template class _refl_ TOY_UI_EXPORT StatSlider<int>;

	template <class T>
	class NumberInput : public WValue
	{
	public:
		NumberInput(Wedge& parent, Lref& lref, std::function<void(T)> callback = nullptr)
			: WValue(parent, lref, this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value.template any<AutoStat<T>>())
			, m_typeIn(*this)
			, m_plus(*this, "+", std::bind(&NumberInput<T>::increment, this))
			, m_minus(*this, "-", std::bind(&NumberInput<T>::decrement, this))
		{
			this->build();
		}

		NumberInput(Wedge& parent, AutoStat<T> value, std::function<void(T)> callback = nullptr)
			: WValue(parent, var(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value.template any<AutoStat<T>>())
			, m_typeIn(*this)
			, m_plus(*this, "+", std::bind(&NumberInput<T>::increment, this))
			, m_minus(*this, "-", std::bind(&NumberInput<T>::decrement, this))
		{
			this->build();
		}

		void build()
		{
			if(typecls<T>().is<float>() || typecls<T>().is<double>())
				m_typeIn.setAllowedChars("1234567890.");
			else
				m_typeIn.setAllowedChars("1234567890");
		}

		void increment()
		{
			m_stat.increment();
			m_typeIn.updateString();
			this->triggerModify();
		}

		void decrement()
		{
			m_stat.decrement();
			m_typeIn.updateString();
			this->triggerModify();
		}

		void notifyUpdate() { m_typeIn.updateString(); }

		static Type& cls() { static Type ty("NumberInput<" + typecls<T>().name() + ">", WValue::cls()); return ty; }

	protected:
		AutoStat<T>& m_stat;
		TypeIn m_typeIn;
		Button m_plus;
		Button m_minus;
	};

	template <class T>
	class Input : public NumberInput<T>
	{
	public:
		Input(Wedge& parent, Lref& lref, std::function<void(T)> callback = nullptr)
			: NumberInput<T>(parent, lref, callback)
		{}

		Input(Wedge& parent, AutoStat<T> value, std::function<void(T)> callback = nullptr)
			: NumberInput<T>(parent, value, callback)
		{}
	};

	template class _refl_ TOY_UI_EXPORT Input<unsigned int>;
	template class _refl_ TOY_UI_EXPORT Input<int>;
	template class _refl_ TOY_UI_EXPORT Input<float>;
	template class _refl_ TOY_UI_EXPORT Input<double>;

	template <>
	class _refl_ TOY_UI_EXPORT Input<bool> : public WValue
	{
	public:
		Input(Wedge& parent, Lref& value, std::function<void(bool)> callback = nullptr)
			: WValue(parent, value, this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<bool>()); } : OnUpdate())
			, m_checkbox(*this, this, m_value.value<bool>())
		{}

		Input(Wedge& parent, bool value, std::function<void(bool)> callback = nullptr)
			: WValue(parent, var(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<bool>()); } : OnUpdate())
			, m_checkbox(*this, this, m_value.value<bool>())
		{}

		void notifyUpdate() { m_checkbox.update(m_value.value<bool>()); }

		static Type& cls() { static Type ty("Input<bool>", WValue::cls()); return ty; }

	protected:
		Checkbox m_checkbox;
	};

	template <>
	class _refl_ TOY_UI_EXPORT Input<string> : public WValue
	{
	public:
		Input(Wedge& parent, Lref& value, std::function<void(string)> callback = nullptr)
			: WValue(parent, value, this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<string>()); } : OnUpdate())
			, m_typeIn(*this)
		{}

		Input(Wedge& parent, const string& value, std::function<void(string)> callback = nullptr)
			: WValue(parent, var(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref.value<string>()); } : OnUpdate())
			, m_typeIn(*this)
		{}

		TypeIn& typeIn() { return m_typeIn; }

		void notifyUpdate() { m_typeIn.updateString(); }
		//void notifyModify() { if(this->m_onUpdate) this->m_onUpdate(this->m_value.value<string>()); }

	protected:
		TypeIn m_typeIn;
	};

	template <>
	class _refl_ TOY_UI_EXPORT Input<Colour> : public WValue
	{
	public:
		Input(Wedge& parent, Colour value, std::function<void(Colour)> callback = nullptr)
			: WValue(parent, var(value), this->cls(), [callback](Lref& lref) { callback(lref.value<Colour>()); })
			, m_r(*this, AutoStat<float>(value.r(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value.value<Colour>().setR(val); this->triggerModify(); })
			, m_g(*this, AutoStat<float>(value.g(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value.value<Colour>().setG(val); this->triggerModify(); })
			, m_b(*this, AutoStat<float>(value.b(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value.value<Colour>().setB(val); this->triggerModify(); })
			, m_a(*this, AutoStat<float>(value.a(), 0.f, 1.f, 0.01f), [this](float val) { this->m_value.value<Colour>().setA(val); this->triggerModify(); })
		{}

		void notifyUpdate()
		{
			Colour colour = this->m_value.value<Colour>();
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
		Field(Wedge& parent, const string& label, const T_Val& value, std::function<void(T_Arg)> callback = nullptr, bool reverse = false)
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
		InputRadio(Wedge& parent, const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool reverse = false);

		static Type& cls() { static Type ty("InputRadio", WrapControl::cls()); return ty; }

	protected:
		Label m_label;
		RadioSwitch m_input;
	};

	class TOY_UI_EXPORT InputDropdown : public WrapControl
	{
	public:
		InputDropdown(Wedge& parent, const string& label, StringVector choices, std::function<void(const string&)> callback = nullptr, bool reverse = false);

		static Type& cls() { static Type ty("InputDropdown", WrapControl::cls()); return ty; }

	protected:
		Label m_label;
		DropdownInput m_input;
	};
}

#endif // TOY_INPUT_H
