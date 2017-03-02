//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WBUTTON_H
#define TOY_WBUTTON_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Edit/Value.h>

namespace toy
{
	class TOY_UI_EXPORT Label : public Item
	{
	public:
		Label(Piece& parent, const string& label, Type& type = cls());

		virtual unique_ptr<Widget> clone(Piece& parent) { return make_unique<Label>(parent, this->label()); }

		static Type& cls() { static Type ty("Label", Item::cls()); return ty; }
	};

	class TOY_UI_EXPORT Text : public Label
	{
	public:
		Text(Piece& parent, const string& label, Type& type = cls());

		static Type& cls() { static Type ty("Text", Label::cls()); return ty; }
	};

	class TOY_UI_EXPORT Title : public Label
	{
	public:
		Title(Piece& parent, const string& label);

		static Type& cls() { static Type ty("Title", Label::cls()); return ty; }
	};

	class TOY_UI_EXPORT Icon : public Item
	{
	public:
		Icon(Piece& parent, Image& image);
		Icon(Piece& parent, const string& image);

		static Type& cls() { static Type ty("Icon", Item::cls()); return ty; }
	};

	class TOY_UI_EXPORT ClickTrigger
	{
	public:
		typedef std::function<void(Widget&)> TriggerFunc;

	public:
		ClickTrigger(Widget& widget, const TriggerFunc& trigger) : m_widget(widget), m_trigger(trigger) {}

		virtual void click() { if(m_trigger) m_trigger(m_widget); }

		virtual void clickAlt() { if(m_triggerAlt) m_triggerAlt(m_widget); }
		virtual void clickShift() { if(m_triggerShift) m_triggerShift(m_widget); }
		virtual void clickCtrl() { if(m_triggerCtrl) m_triggerCtrl(m_widget); }

	protected:
		Widget& m_widget;
		TriggerFunc m_trigger;
		TriggerFunc m_triggerAlt;
		TriggerFunc m_triggerShift;
		TriggerFunc m_triggerCtrl;
	};

	class TOY_UI_EXPORT Button : public Control, public ClickTrigger
	{
	public:
		Button(Piece& parent, const string& label, const Trigger& trigger = Trigger(), Type& type = cls());

		const string& tooltip() { return m_tooltip; }

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		virtual unique_ptr<Widget> clone(Piece& parent) { return make_unique<Button>(parent, this->label(), m_trigger, cls()); }

		static Type& cls() { static Type ty("Button", Control::cls()); return ty; }

	protected:
		string m_tooltip;
	};

	class TOY_UI_EXPORT ImgButton : public Button
	{
	public:
		ImgButton(Piece& parent, Image& image, const Trigger& trigger = Trigger(), Type& type = cls());
		ImgButton(Piece& parent, const string& image, const Trigger& trigger = Trigger(), Type& type = cls());

		const string& tooltip() { return m_tooltip; }

		static Type& cls() { static Type ty("ImgButton", Button::cls()); return ty; }

	protected:
		string m_tooltip;
	};

	class TOY_UI_EXPORT WrapButton : public WrapControl, public ClickTrigger
	{
	public:
		WrapButton(Piece& parent, const Trigger& trigger = Trigger(), Type& type = cls());
		WrapButton(Piece& parent, Widget* content = nullptr, const Trigger& trigger = Trigger(), Type& type = cls());
		WrapButton(Piece& parent, unique_ptr<Widget> content, const Trigger& trigger = Trigger(), Type& type = cls());

		Widget& content() { return *m_contents[0]; }

		void reset(unique_ptr<Widget> content);

		virtual void leftClick(MouseEvent& mouseEvent);
		virtual void rightClick(MouseEvent& mouseEvent);

		virtual void handleAdd(Widget& widget);

		const string& contentlabel() { return this->content().contentlabel(); }

		static Type& cls() { static Type ty("WrapButton", WrapControl::cls()); return ty; }

	protected:
		Widget* m_content;
	};

	class TOY_UI_EXPORT Toggle : public Control
	{
	public:
		typedef std::function<void(Toggle&)> Trigger;

	public:
		Toggle(Piece& parent, const Trigger& triggerOn, const Trigger& triggerOff, bool isOn = true, Type& type = cls());

		bool on() { return m_on; }

		void update(bool on);
		void toggle();

		void leftClick(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Toggle", Control::cls()); return ty; }

	protected:
		Trigger m_triggerOn;
		Trigger m_triggerOff;

		bool m_on;
	};
}

#endif
