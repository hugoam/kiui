//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUT_H
#define TOY_INPUT_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/Any.h>
#include <toyobj/Util/Dispatch.h>
#include <toyobj/String/StringConvert.h>
#include <toyobj/Util/Stat.h>
#include <toyobj/Util/StatString.h>
#include <toyui/Forward.h>
#include <toyui/Types.h>

#include <toyui/Button/Slider.h>
#include <toyui/Button/RadioButton.h>
#include <toyui/Button/Dropdown.h>
#include <toyui/Button/Typedown.h>
#include <toyui/Button/Checkbox.h>

#include <toyui/Edit/TypeIn.h>

namespace toy
{
	class TOY_UI_EXPORT DispatchInput : public Dispatcher<object_ptr<Widget>, Lref&>, public LazyGlobal<DispatchInput>
	{};
	
	class TOY_UI_EXPORT DispatchDisplay : public Dispatcher<object_ptr<Widget>, Lref&>, public LazyGlobal<DispatchDisplay>
	{};

	template <class T>
	class InputValue
	{
	public:
		InputValue(T value, const std::function<void(T)>& callback = nullptr) : m_value(value), m_ref(m_value), m_callback(callback) {}

		T m_value;
		T& m_ref;
		std::function<void(T)> m_callback;
	};

	template <class T>
	class StatSlider : public Wedge, public InputValue<AutoStat<T>>
	{
	public:
		using Callback = std::function<void(AutoStat<T>)>;

		StatSlider(Wedge& parent, AutoStat<T> value, const Callback& callback = nullptr, Dimension dim = DIM_X)
			: Wedge(parent, this->cls())
			, InputValue<AutoStat<T>>(value, callback)
			, m_slider(*this, dim, [this](Widget&) { this->changed(); })
			, m_display(*this, "", Slider::Display())
		{
			this->update();
		}

		void update()
		{
			m_slider.resetMetrics(float(this->m_ref.min()), float(this->m_ref.max()), float(this->m_ref.value()), float(this->m_ref.step()));
			m_slider.updateKnob();
			m_display.setContent(toString(this->m_ref));
		}

		void changed()
		{
			this->m_ref.modify(T(m_slider.val()));
			m_display.setContent(toString(this->m_ref));
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		void update(T val) { this->m_ref.modify(val); }
		void change(T val) { this->m_ref.modify(val); if(this->m_callback) this->m_callback(this->m_ref); }

		static Type& cls() { static Type ty("StatSlider<" + typecls<T>().name() + ">", Wedge::Row()); return ty; }

	protected:
		Slider m_slider;
		Label m_display;
	};

	template class _refl_ TOY_UI_EXPORT StatSlider<float>;
	template class _refl_ TOY_UI_EXPORT StatSlider<int>;

	template <class T>
	class NumberInput : public Wedge, public InputValue<AutoStat<T>>
	{
	public:
		using Callback = std::function<void(AutoStat<T>)>;

		NumberInput(Wedge& parent, AutoStat<T> value, const Callback& callback = nullptr)
			: Wedge(parent, this->cls())
			, InputValue<AutoStat<T>>(value, callback)
			, m_typeIn(*this, "", [this](const string& val) { this->typein(val); return val; })
			, m_plus(*this, "+", [this](Widget&) { this->increment(); })
			, m_minus(*this, "-", [this](Widget&) { this->decrement(); })
		{
			if(typecls<T>().template is<float>() || typecls<T>().template is<double>())
				m_typeIn.setAllowedChars("1234567890.");
			else
				m_typeIn.setAllowedChars("1234567890");

			m_typeIn.setString(toString(this->m_ref));
		}

		void typein(const string& str)
		{
			this->m_ref.modify(fromString<T>(str));
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		void increment()
		{
			this->m_ref.increment();
			m_typeIn.setString(toString(this->m_ref));
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		void decrement()
		{
			this->m_ref.decrement();
			m_typeIn.setString(toString(this->m_ref));
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		static Type& cls() { static Type ty("NumberInput<" + typecls<T>().name() + ">", Wedge::Row()); return ty; }

	protected:
		TypeIn m_typeIn;
		Button m_plus;
		Button m_minus;
	};

	template <class T>
	class Input : public NumberInput<T>
	{
	public:
		using typename NumberInput<T>::Callback;

		Input(Wedge& parent, AutoStat<T> value, const Callback& callback = nullptr)
			: NumberInput<T>(parent, value, callback)
		{}
	};

	template class _refl_ TOY_UI_EXPORT Input<unsigned int>;
	template class _refl_ TOY_UI_EXPORT Input<int>;
	template class _refl_ TOY_UI_EXPORT Input<float>;
	template class _refl_ TOY_UI_EXPORT Input<double>;

	template <>
	class _refl_ TOY_UI_EXPORT Input<bool> : public Wedge, public InputValue<bool>
	{
	public:
		using Callback = std::function<void(bool)>;

		Input(Wedge& parent, bool value, const Callback& callback = nullptr)
			: Wedge(parent, this->cls())
			, InputValue<bool>(value, callback)
			, m_checkbox(*this, [this](Widget&, bool on) { this->changed(on); }, value)
		{}

		void changed(bool on) { this->m_ref = on; if(this->m_callback) this->m_callback(on); }

		static Type& cls() { static Type ty("Input<bool>", Wedge::cls()); return ty; }

	protected:
		Checkbox m_checkbox;
	};

	template <>
	class _refl_ TOY_UI_EXPORT Input<string> : public TypeIn
	{
	public:
		using Callback = std::function<void(string)>;

		Input(Wedge& parent, const string& value, Callback callback = nullptr)
			: TypeIn(parent, value, [this](const string& val) { if(m_callback) m_callback(val); return val; }, false, this->cls())
			, m_callback(callback)
		{}

		static Type& cls() { static Type ty("Input<string>", TypeIn::cls()); return ty; }

	protected:
		Callback m_callback;
	};

	template <>
	class _refl_ TOY_UI_EXPORT Input<Colour> : public Wedge, public InputValue<Colour>
	{
	public:
		using Callback = std::function<void(Colour)>;

		Input(Wedge& parent, Colour value, const Callback& callback = nullptr)
			: Wedge(parent, this->cls())
			, InputValue<Colour>(value, callback)
			, m_r(*this, AutoStat<float>(value.r(), 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.setR(val); this->changed(); })
			, m_g(*this, AutoStat<float>(value.g(), 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.setG(val); this->changed(); })
			, m_b(*this, AutoStat<float>(value.b(), 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.setB(val); this->changed(); })
			, m_a(*this, AutoStat<float>(value.a(), 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.setA(val); this->changed(); })
		{}

		void changed()
		{
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		void notifyUpdate()
		{
			m_r.update(this->m_ref.r());
			m_g.update(this->m_ref.g());
			m_b.update(this->m_ref.b());
			m_a.update(this->m_ref.a());
		}

		static Type& cls() { static Type ty("InputColour", Wedge::Row()); return ty; }

	protected:
		StatSlider<float> m_r, m_g, m_b, m_a;
	};

	template <class T_Val, class T_Input>
	class Field : public Wedge
	{
	public:
		Field(Wedge& parent, const string& label, const T_Val& value, typename T_Input::Callback callback = nullptr, bool reverse = false)
			: Wedge(parent, cls())
			, m_label(*this, label)
			, m_input(*this, value, callback)
		{
			if(reverse)
				this->swap(0, 1);
		}

		T_Input& input() { return m_input; }

		static Type& cls() { static Type ty("Field<" + typecls<T_Val>().name() + ">", Wedge::WrapControl()); return ty; }

	protected:
		Label m_label;
		T_Input m_input;
	};

	using InputBool = Field<bool, Input<bool>>;
	using InputInt = Field<AutoStat<int>, Input<int>> ;
	using InputFloat = Field<AutoStat<float>, Input<float>>;
	using InputText = Field<string, Input<string>>;

	using InputColour = Field<Colour, Input<Colour>>;

	using SliderInt = Field<AutoStat<int>, StatSlider<int>>;
	using SliderFloat = Field<AutoStat<float>, StatSlider<float>>;

	using InputRadio = Field<StringVector, RadioSwitch>;
	using InputDropdown = Field<StringVector, DropdownInput>;
	using InputTypedown = Field<StringVector, TypedownInput>;
}

#endif // TOY_INPUT_H
