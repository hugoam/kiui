//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TYPEIN_H
#define TOY_TYPEIN_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Button/Checkbox.h>
#include <toyui/Edit/Value.h>

#include <toyobj/String/StringConvert.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT TypeIn : public Control
	{
	public:
		TypeIn(Wedge& parent, string& string, Type& type = cls());
		TypeIn(WValue& input, Type& type = cls());

		void nextFrame(size_t tick, size_t delta);

		void setAllowedChars(const string& chars);

		void focused();
		void unfocused();

		void erase();
		void insert(char c);
		void updateString();
		void updateText();

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

		static Type& cls() { static Type ty("TypeIn", Control::cls()); return ty; }

	protected:
		WValue* m_input;
		string& m_string;
		bool m_hasPeriod;
		string m_allowedChars;
		size_t m_precision;

		string m_valueString;

		size_t m_selectFirst;
		size_t m_selectSecond;

		//std::vector<TextSelection*> m_selection;
	};

	template <class T>
	class NumberInput : public WValue
	{
	public:
		NumberInput(Wedge& parent, Lref& lref, std::function<void(T)> callback = nullptr)
			: WValue(parent, lref, this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value->template ref<AutoStat<T>>())
			, m_typeIn(*this)
			, m_plus(*this, "+", std::bind(&NumberInput<T>::increment, this))
			, m_minus(*this, "-", std::bind(&NumberInput<T>::decrement, this))
		{
			this->build();
		}

		NumberInput(Wedge& parent, AutoStat<T> value, std::function<void(T)> callback = nullptr)
			: WValue(parent, lref(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<AutoStat<T>>()); } : OnUpdate())
			, m_stat(this->m_value->template ref<AutoStat<T>>())
			, m_typeIn(*this)
			, m_plus(*this, "+", std::bind(&NumberInput<T>::increment, this))
			, m_minus(*this, "-", std::bind(&NumberInput<T>::decrement, this))
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

	template class _I_ TOY_UI_EXPORT Input<unsigned int>;
	template class _I_ TOY_UI_EXPORT Input<int>;
	template class _I_ TOY_UI_EXPORT Input<float>;
	template class _I_ TOY_UI_EXPORT Input<double>;

	template <>
	class _I_ TOY_UI_EXPORT Input<bool> : public WValue
	{
	public:
		Input(Wedge& parent, Lref& value, std::function<void(bool)> callback = nullptr)
			: WValue(parent, value, this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<bool>()); } : OnUpdate())
			, m_checkbox(*this, this, m_value->get<bool>())
		{}

		Input(Wedge& parent, bool value, std::function<void(bool)> callback = nullptr)
			: WValue(parent, lref(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<bool>()); } : OnUpdate())
			, m_checkbox(*this, this, m_value->get<bool>())
		{}

		void notifyUpdate() { m_checkbox.update(m_value->get<bool>()); }

		static Type& cls() { static Type ty("Input<bool>", WValue::cls()); return ty; }

	protected:
		Checkbox m_checkbox;
	};

	template <>
	class _I_ TOY_UI_EXPORT Input<string> : public WValue
	{
	public:
		Input(Wedge& parent, Lref& value, std::function<void(string)> callback = nullptr)
			: WValue(parent, value, this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<string>()); } : OnUpdate())
			, m_typeIn(*this)
		{}

		Input(Wedge& parent, const string& value, std::function<void(string)> callback = nullptr)
			: WValue(parent, lref(value), this->cls(), callback ? [callback](Lref& lref) { callback(lref->get<string>()); } : OnUpdate())
			, m_typeIn(*this)
		{}

		TypeIn& typeIn() { return m_typeIn; }

		void notifyUpdate() { m_typeIn.updateString(); }
		//void notifyModify() { if(this->m_onUpdate) this->m_onUpdate(this->m_value->get<string>()); }

	protected:
		TypeIn m_typeIn;
	};
}

#endif
