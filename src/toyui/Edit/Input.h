//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUT_H
#define TOY_INPUT_H

/* toy */
#include <toyobj/Type.h>
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

static const size_t g_num_precision = 3;

namespace toy
{
	template <class T>
	class InputValue
	{
	public:
		InputValue(T value, const std::function<void(T)>& callback = nullptr) : m_value(value), m_ref(m_value), m_callback(callback) {}

		T m_value;
		T& m_ref;
		std::function<void(T)> m_callback;
	};

	inline string truncateNumber(const string& str)
	{
		size_t dot = str.find(".");
		if(dot == string::npos) return str;
		string result = str;
		while(result.size() > 1 + dot + g_num_precision || (result.size() > 1 + dot + 1 && result.back() == '0'))
			result.pop_back();
		return result;
	}

	template <class T>
	class StatSlider : public Wedge, public InputValue<AutoStat<T>>
	{
	public:
		using Callback = std::function<void(AutoStat<T>)>;

		StatSlider(Wedge& parent, AutoStat<T> value, const Callback& callback = nullptr, Dimension dim = DIM_X)
			: Wedge(parent, this->cls())
			, InputValue<AutoStat<T>>(value, callback)
			, m_slider(*this, dim, [this](Widget&) { this->m_ref.modify(T(m_slider.val())); this->changed(); })
			, m_display(*this, "", Slider::Display())
		{
			this->update();
		}

		void update()
		{
			m_slider.resetMetrics(float(this->m_ref.min()), float(this->m_ref.max()), float(this->m_ref.value()), float(this->m_ref.step()));
			m_slider.updateKnob();
			m_display.setContent(truncateNumber(toString(this->m_ref)));
		}

		void changed()
		{
			this->update();
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		void sync(T val)
		{
			this->m_ref.modify(val);
			this->update();
		}

		static Type& cls() { static Type ty("StatSlider<" + toy::cls<T>().m_name + ">", Wedge::Row()); return ty; }

	protected:
		Slider m_slider;
		Label m_display;
	};

	template class /*_refl_*/ TOY_UI_EXPORT StatSlider<float>;
	template class /*_refl_*/ TOY_UI_EXPORT StatSlider<int>;

	template <class T>
	class NumberInput : public Wedge, public InputValue<AutoStat<T>>
	{
	public:
		using Callback = std::function<void(AutoStat<T>)>;

		NumberInput(Wedge& parent, AutoStat<T> value, const Callback& callback = nullptr)
			: Wedge(parent, this->cls())
			, InputValue<AutoStat<T>>(value, callback)
			, m_typeIn(*this, "", [this](const string& val) { return this->typein(val); })
			, m_plus(*this, "+", [this](Widget&) { this->m_ref.increment(); this->changed(); })
			, m_minus(*this, "-", [this](Widget&) { this->m_ref.decrement(); this->changed(); })
		{
			if(toy::cls<T>().template is<float>() || toy::cls<T>().template is<double>())
				m_typeIn.setAllowedChars("1234567890.");
			else
				m_typeIn.setAllowedChars("1234567890");

			this->update();
		}

		void update()
		{
			m_typeIn.setString(truncateNumber(toString(this->m_ref)));
		}

		void changed()
		{
			this->update();
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		void sync(T val)
		{
			this->m_ref.modify(val);
			this->update();
		}

		string typein(const string& str)
		{
			this->m_ref.modify(fromString<T>(str));
			this->changed();
			return truncateNumber(str);
		}

		static Type& cls() { static Type ty("NumberInput<" + toy::cls<T>().m_name + ">", Wedge::Row()); return ty; }

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

	template class /*_refl_*/ TOY_UI_EXPORT Input<unsigned int>;
	template class /*_refl_*/ TOY_UI_EXPORT Input<int>;
	template class /*_refl_*/ TOY_UI_EXPORT Input<float>;
	template class /*_refl_*/ TOY_UI_EXPORT Input<double>;

	template <>
	class _refl_ TOY_UI_EXPORT Input<bool> : public Wedge, public InputValue<bool>
	{
	public:
		using Callback = std::function<void(bool)>;

		Input(Wedge& parent, bool value, const Callback& callback = nullptr)
			: Wedge(parent, this->cls())
			, InputValue<bool>(value, callback)
			, m_checkbox(*this, [this](Widget&, bool on) { this->m_ref = on; this->changed(); }, value)
		{}

		void update() { m_checkbox.update(this->m_ref); }
		void changed() { this->update(); if(this->m_callback) this->m_callback(this->m_ref); }
		void sync(bool on) { this->m_ref = on; this->update(); }

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

		void changed() { this->update(); if(this->m_callback) this->m_callback(this->value()); }
		void sync(string text) { this->setString(text); }

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
			, m_r(*this, AutoStat<float>(value.m_r, 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.m_r = val; this->changed(); })
			, m_g(*this, AutoStat<float>(value.m_g, 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.m_g = val; this->changed(); })
			, m_b(*this, AutoStat<float>(value.m_b, 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.m_b = val; this->changed(); })
			, m_a(*this, AutoStat<float>(value.m_a, 0.f, 1.f, 0.01f), [this](float val) { this->m_ref.m_a = val; this->changed(); })
		{}

		void update()
		{
			m_r.sync(this->m_ref.m_r);
			m_g.sync(this->m_ref.m_g);
			m_b.sync(this->m_ref.m_b);
			m_a.sync(this->m_ref.m_a);
		}

		void changed()
		{
			this->update();
			if(this->m_callback) this->m_callback(this->m_ref);
		}

		void sync(Colour& colour)
		{
			this->m_ref = colour;
			this->update();
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

		Label m_label;
		T_Input m_input;

		static Type& cls() { static Type ty("Field<" + toy::cls<T_Val>().m_name + ">", Wedge::WrapControl()); return ty; }
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
