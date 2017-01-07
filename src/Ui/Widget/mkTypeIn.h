//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_TYPEIN_H
#define MK_TYPEIN_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkCursor.h>
#include <Ui/Widget/mkCheckbox.h>
#include <Ui/Widget/mkValue.h>

#include <Object/String/mkStringConvert.h>

namespace mk
{
	class _I_ MK_UI_EXPORT TypeIn : public Sheet
	{
	public:
		TypeIn(string& string, StyleType& type = cls());
		TypeIn(WValue& input, StyleType& type = cls());

		Style* hoverCursor() { return &CaretCursor::cls(); }

		void nextFrame(size_t tick, size_t delta);

		void setAllowedChars(const string& chars);

		void focused();
		void unfocused();

		void erase();
		void insert(char c);
		void updateString();

		void leftClick(MouseEvent& mouseEvent);
		void keyDown(KeyEvent& keyEvent);

		void leftDragStart(MouseEvent& mouseEvent);
		void leftDrag(MouseEvent& mouseEvent);
		void leftDragEnd(MouseEvent& mouseEvent);

		void selectCaret(int index);
		void selectFirst(size_t start);
		void selectSecond(size_t end);

		void moveCaretTo(size_t index);
		void moveCaretRight();
		void moveCaretLeft();

		static StyleType& cls() { static StyleType ty("TypeIn", Sheet::cls()); return ty; }

	protected:
		WValue* m_input;
		string& m_string;
		bool m_hasPeriod;
		string m_allowedChars;

		string m_valueString;

		size_t m_selectFirst;
		size_t m_selectSecond;

		//std::vector<TextSelection*> m_selection;
	};

	template <class T>
	class NumberInput : public WValue
	{
	public:
		NumberInput(Lref& lref, std::function<void(T)> callback = nullptr)
			: WValue(lref, this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value->template ref<AutoStat<T>>())
			, m_typeIn(this->template makeappend<TypeIn>(*this))
			, m_plus(this->template makeappend<Button>("+", std::bind(&NumberInput<T>::increment, this)))
			, m_minus(this->template makeappend<Button>("-", std::bind(&NumberInput<T>::decrement, this)))
		{
			this->build();
		}

		NumberInput(AutoStat<T> value, std::function<void(T)> callback = nullptr)
			: WValue(lref(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value->template ref<AutoStat<T>>())
			, m_typeIn(this->template makeappend<TypeIn>(*this))
			, m_plus(this->template makeappend<Button>("+", std::bind(&NumberInput<T>::increment, this)))
			, m_minus(this->template makeappend<Button>("-", std::bind(&NumberInput<T>::decrement, this)))
		{
			this->build();
		}

		void build()
		{
			if(&typecls<T>() == &typecls<float>() || &typecls<T>() == &typecls<double>())
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

		static StyleType& cls() { static StyleType ty("NumberInput<" + typecls<T>().name() + ">", WValue::cls()); return ty; }

	protected:
		AutoStat<T>& m_stat;
		TypeIn& m_typeIn;
		Button& m_plus;
		Button& m_minus;
	};

	template <class T>
	class Input
	{};

	template <>
	class _I_ MK_UI_EXPORT Input<unsigned int> : public NumberInput<unsigned int>
	{
	public:
		using NumberInput<unsigned int>::NumberInput;
	};

	template <>
	class _I_ MK_UI_EXPORT Input<int> : public NumberInput<int>
	{
	public:
		using NumberInput<int>::NumberInput;
	};

	template <>
	class _I_ MK_UI_EXPORT Input<float> : public NumberInput<float>
	{
	public:
		using NumberInput<float>::NumberInput;
	};

	template <>
	class _I_ MK_UI_EXPORT Input<double> : public NumberInput<double>
	{
	public:
		using NumberInput<double>::NumberInput;
	};

	template <>
	class _I_ MK_UI_EXPORT Input<bool> : public WValue
	{
	public:
		Input(Lref& value, std::function<void(bool)> callback = nullptr)
			: WValue(value, this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<bool>()); } : OnUpdate())
			, m_checkbox(this->makeappend<Checkbox>(this, m_value->get<bool>()))
		{}

		Input(bool value, std::function<void(bool)> callback = nullptr)
			: WValue(lref(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<bool>()); } : OnUpdate())
			, m_checkbox(this->makeappend<Checkbox>(this, m_value->get<bool>()))
		{}

		void notifyUpdate() { m_checkbox.update(m_value->get<bool>()); }

		static StyleType& cls() { static StyleType ty("Input<bool>", WValue::cls()); return ty; }

	protected:
		Checkbox& m_checkbox;
	};

	template <>
	class _I_ MK_UI_EXPORT Input<string> : public WValue
	{
	public:
		Input(Lref& value, std::function<void(string)> callback = nullptr)
			: WValue(value, this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<string>()); } : OnUpdate())
			, m_typeIn(this->makeappend<TypeIn>(*this))
		{}

		Input(const string& value, std::function<void(string)> callback = nullptr)
			: WValue(lref(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<string>()); } : OnUpdate())
			, m_typeIn(this->makeappend<TypeIn>(*this))
		{}

		TypeIn& typeIn() { return m_typeIn; }

		void notifyUpdate() { m_typeIn.updateString(); }
		//void notifyModify() { if(this->m_onUpdate) this->m_onUpdate(this->m_value->get<string>()); }

	protected:
		TypeIn& m_typeIn;
	};
}

#endif
