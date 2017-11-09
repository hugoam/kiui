//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_BUTTON_H
#define TOY_BUTTON_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Input/InputDevice.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Label : public Item
	{
	public:
		Label(Wedge& parent, const string& label, Type& type = cls());

		static Type& cls() { static Type ty("Label", Item::cls()); return ty; }
		static Type& Title() { static Type ty("Title", Item::cls()); return ty; }
		static Type& Text() { static Type ty("Text", Item::cls()); return ty; }
	};

	class TOY_UI_EXPORT ClickTrigger
	{
	public:
		ClickTrigger(Widget& widget, const Widget::Callback& trigger) : m_widget(widget), m_trigger(trigger) {}

		bool click(MouseEvent& mouseEvent)
		{
			if(!m_trigger) return false; m_trigger(m_widget);
			mouseEvent.abort = true; // @kludge for buttons that cause destroying a widget
			return true; 
		}

		bool clickMods(MouseEvent& mouseEvent)
		{
			if(mouseEvent.modifiers & INPUT_CTRL)
				return this->clickCtrl(mouseEvent);
			else if(mouseEvent.modifiers & INPUT_SHIFT)
				return this->clickShift(mouseEvent);
			else
				return this->click(mouseEvent);
		}

		bool clickAlt(MouseEvent& mouseEvent) { UNUSED(mouseEvent); if(!m_triggerAlt) return false; m_triggerAlt(m_widget); return true; }
		bool clickShift(MouseEvent& mouseEvent) { UNUSED(mouseEvent); if(!m_triggerShift) return false; m_triggerShift(m_widget); return true; }
		bool clickCtrl(MouseEvent& mouseEvent) { UNUSED(mouseEvent); if(!m_triggerCtrl) return false; m_triggerCtrl(m_widget); return true; }

	public:
		Widget& m_widget;
		Widget::Callback m_trigger;
		Widget::Callback m_triggerAlt;
		Widget::Callback m_triggerShift;
		Widget::Callback m_triggerCtrl;
	};

	class _refl_ TOY_UI_EXPORT Button : public Item, public ClickTrigger
	{
	public:
		Button(Wedge& parent, const string& content, const Callback& trigger = nullptr, Type& type = cls());

		const string& tooltip() { return m_tooltip; }

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Button", Item::Control()); return ty; }

	protected:
		string m_tooltip;
	};

	class _refl_ TOY_UI_EXPORT WrapButton : public Wedge, public ClickTrigger
	{
	public:
		WrapButton(Wedge& parent, const Callback& trigger = nullptr, Type& type = cls());

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("WrapButton", Wedge::WrapControl()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT MultiButton : public WrapButton
	{
	public:
		MultiButton(Wedge& parent, const StringVector& elements = {}, const Callback& trigger = nullptr, Type& type = cls());

		std::vector<string> m_elements;

		void reset(Button& button);
		void reset(MultiButton& button);
		void reset(const StringVector& contents, const Callback& trigger = nullptr);

		virtual const string& label() { return m_elements[0]; }

		static Type& cls() { static Type ty("MultiButton", WrapButton::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Toggle : public Item
	{
	public:
		typedef std::function<void(Widget&, bool)> Callback;

	public:
		Toggle(Wedge& parent, const Callback& callback, bool isOn = true, Type& type = cls());

		void update(bool on);
		void toggle();

		virtual bool leftClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Toggle", Item::Control()); return ty; }

	public:
		bool m_on;
		const Callback m_callback;
	};
}

#endif
