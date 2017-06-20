//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_BUTTON_H
#define TOY_BUTTON_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/Edit/Value.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Label : public Item
	{
	public:
		Label(Wedge& parent, const string& label, Type& type = cls());

		static Type& cls() { static Type ty("Label", Item::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Text : public Label
	{
	public:
		Text(Wedge& parent, const string& label);

		static Type& cls() { static Type ty("Text", Label::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Title : public Label
	{
	public:
		Title(Wedge& parent, const string& label);

		static Type& cls() { static Type ty("Title", Label::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT Icon : public Item
	{
	public:
		Icon(Wedge& parent, Image& image);
		Icon(Wedge& parent, const string& image);

		static Type& cls() { static Type ty("Icon", Item::cls()); return ty; }
	};

	class TOY_UI_EXPORT ClickTrigger
	{
	public:
		ClickTrigger(Widget& widget, const Widget::Callback& trigger) : m_widget(widget), m_trigger(trigger) {}

		const Widget::Callback& trigger() { return m_trigger; }
		void setTrigger(const Widget::Callback& trigger) { m_trigger = trigger; }

		virtual bool click(MouseEvent& mouseEvent)
		{
			if(!m_trigger)
				return false;

			m_trigger(m_widget);
			mouseEvent.abort = true; // @kludge for buttons that cause destroying a widget
			return true; 
		}

		virtual bool clickAlt(MouseEvent& mouseEvent) { if(!m_triggerAlt) return false; m_triggerAlt(m_widget); return true; }
		virtual bool clickShift(MouseEvent& mouseEvent) { if(!m_triggerShift) return false; m_triggerShift(m_widget); return true; }
		virtual bool clickCtrl(MouseEvent& mouseEvent) { if(!m_triggerCtrl) return false; m_triggerCtrl(m_widget); return true; }

	protected:
		Widget& m_widget;
		Widget::Callback m_trigger;
		Widget::Callback m_triggerAlt;
		Widget::Callback m_triggerShift;
		Widget::Callback m_triggerCtrl;
	};

	class _refl_ TOY_UI_EXPORT Button : public Control, public ClickTrigger
	{
	public:
		Button(Wedge& parent, const string& label, const Callback& trigger = nullptr, Type& type = cls());
		Button(Wedge& parent, Image& image, const Callback& trigger = nullptr, Type& type = cls());

		const string& tooltip() { return m_tooltip; }

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Button", Control::cls()); return ty; }

	protected:
		string m_tooltip;
	};

	class _refl_ TOY_UI_EXPORT WrapButton : public WrapControl, public ClickTrigger
	{
	public:
		WrapButton(Wedge& parent, const Callback& trigger = nullptr, Type& type = cls());

		Widget& content() { return *m_contents[0]; }

		virtual bool leftClick(MouseEvent& mouseEvent);
		virtual bool rightClick(MouseEvent& mouseEvent);

		const string& contentlabel() { return this->content().contentlabel(); }

		static Type& cls() { static Type ty("WrapButton", WrapControl::cls()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT MultiButton : public WrapButton
	{
	public:
		MultiButton(Wedge& parent, const Callback& trigger = nullptr, const StringVector& elements = {}, Type& type = cls());

		const std::vector<string>& elements() { return m_elements; }

		void reset(Button& button);
		void reset(MultiButton& button);
		void reset(const StringVector& contents, const Callback& trigger = nullptr);

		static Type& cls() { static Type ty("MultiButton", WrapButton::cls()); return ty; }

	protected:
		std::vector<string> m_elements;
	};

	class _refl_ TOY_UI_EXPORT Toggle : public Control
	{
	public:
		typedef std::function<void(Toggle&)> Callback;

	public:
		Toggle(Wedge& parent, const Callback& triggerOn, const Callback& triggerOff, bool isOn = true, Type& type = cls());

		bool on() { return m_on; }

		void update(bool on);
		void toggle();

		virtual bool leftClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Toggle", Control::cls()); return ty; }

	protected:
		Callback m_triggerOn;
		Callback m_triggerOff;

		bool m_on;
	};
}

#endif
