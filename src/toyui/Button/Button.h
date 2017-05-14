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
	class _I_ TOY_UI_EXPORT Label : public Item
	{
	public:
		Label(Wedge& parent, const string& label, Type& type = cls());

		static Type& cls() { static Type ty("Label", Item::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Text : public Label
	{
	public:
		Text(Wedge& parent, const string& label);

		static Type& cls() { static Type ty("Text", Label::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Title : public Label
	{
	public:
		Title(Wedge& parent, const string& label);

		static Type& cls() { static Type ty("Title", Label::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Icon : public Item
	{
	public:
		Icon(Wedge& parent, Image& image);
		Icon(Wedge& parent, const string& image);

		static Type& cls() { static Type ty("Icon", Item::cls()); return ty; }
	};

	class TOY_UI_EXPORT ClickTrigger
	{
	public:
		typedef std::function<void(Widget&)> TriggerFunc;

	public:
		ClickTrigger(Widget& widget, const TriggerFunc& trigger) : m_widget(widget), m_trigger(trigger) {}

		virtual void click(MouseEvent& mouseEvent) { if(m_trigger) { m_trigger(m_widget); mouseEvent.consumed = true; } }

		virtual void clickAlt(MouseEvent& mouseEvent) { if(m_triggerAlt) { m_triggerAlt(m_widget); mouseEvent.consumed = true; } }
		virtual void clickShift(MouseEvent& mouseEvent) { if(m_triggerShift) { m_triggerShift(m_widget); mouseEvent.consumed = true; } }
		virtual void clickCtrl(MouseEvent& mouseEvent) { if(m_triggerCtrl) { m_triggerCtrl(m_widget); mouseEvent.consumed = true; } }

	protected:
		Widget& m_widget;
		TriggerFunc m_trigger;
		TriggerFunc m_triggerAlt;
		TriggerFunc m_triggerShift;
		TriggerFunc m_triggerCtrl;
	};

	class _I_ TOY_UI_EXPORT Button : public Control, public ClickTrigger
	{
	public:
		Button(Wedge& parent, const string& label, const Callback& trigger = nullptr, Type& type = cls());
		Button(Wedge& parent, Image& image, const Callback& trigger = nullptr, Type& type = cls());

		const string& tooltip() { return m_tooltip; }

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Button", Control::cls()); return ty; }

	protected:
		string m_tooltip;
	};

	class _I_ TOY_UI_EXPORT WrapButton : public WrapControl, public ClickTrigger
	{
	public:
		WrapButton(Wedge& parent, const Callback& trigger = nullptr, Type& type = cls());

		Widget& content() { return *m_contents[0]; }

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);

		const string& contentlabel() { return this->content().contentlabel(); }

		static Type& cls() { static Type ty("WrapButton", WrapControl::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT MultiButton : public WrapButton
	{
	public:
		MultiButton(Wedge& parent, const Callback& trigger = nullptr, const StringVector& elements = {}, Type& type = cls());

		const std::vector<string>& elements() { return m_elements; }

		void reset(MultiButton& button);
		void reset(const StringVector& contents, const Callback& trigger = nullptr);

		static Type& cls() { static Type ty("MultiButton", WrapButton::cls()); return ty; }

	protected:
		std::vector<string> m_elements;
	};

	class _I_ TOY_UI_EXPORT Toggle : public Control
	{
	public:
		typedef std::function<void(Toggle&)> Callback;

	public:
		Toggle(Wedge& parent, const Callback& triggerOn, const Callback& triggerOff, bool isOn = true, Type& type = cls());

		bool on() { return m_on; }

		void update(bool on);
		void toggle();

		virtual void leftClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Toggle", Control::cls()); return ty; }

	protected:
		Callback m_triggerOn;
		Callback m_triggerOff;

		bool m_on;
	};
}

#endif
