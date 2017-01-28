//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WBUTTON_H
#define TOY_WBUTTON_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Value.h>

namespace toy
{
	class TOY_UI_EXPORT Label : public Widget
	{
	public:
		Label(const string& label, StyleType& type = cls(), FrameType frameType = FRAME);

		unique_ptr<Widget> clone() { return make_unique<Label>(this->label()); }

		static StyleType& cls() { static StyleType ty("Label", Widget::cls()); return ty; }
	};

	class TOY_UI_EXPORT Text : public Label
	{
	public:
		Text(const string& label, StyleType& type = cls(), FrameType frameType = FRAME);

		static StyleType& cls() { static StyleType ty("Text", Label::cls()); return ty; }
	};

	class TOY_UI_EXPORT Title : public Label
	{
	public:
		Title(const string& label);

		static StyleType& cls() { static StyleType ty("Title", Label::cls()); return ty; }
	};

	class TOY_UI_EXPORT Icon : public Widget
	{
	public:
		Icon(Image& image);
		Icon(const string& image);

		static StyleType& cls() { static StyleType ty("Icon", Widget::cls()); return ty; }
	};

	template <class T_Widget>
	class WidgetTrigger
	{
	public:
		typedef std::function<void(T_Widget&)> Trigger;

	public:
		WidgetTrigger(const Trigger& trigger) : m_trigger(trigger) {}

		virtual void trigger() { if(m_trigger) m_trigger(static_cast<T_Widget&>(*this)); }
		virtual void triggerAlt() { if(m_triggerAlt) m_triggerAlt(static_cast<T_Widget&>(*this)); }
		virtual void triggerShift() { if(m_triggerShift) m_triggerShift(static_cast<T_Widget&>(*this)); }
		virtual void triggerCtrl() { if(m_triggerCtrl) m_triggerCtrl(static_cast<T_Widget&>(*this)); }

	protected:
		Trigger m_trigger;
		Trigger m_triggerAlt;
		Trigger m_triggerShift;
		Trigger m_triggerCtrl;
	};

	class TOY_UI_EXPORT Button : public Control, public WidgetTrigger<Button>
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		Button(const string& label, const Trigger& trigger = Trigger(), StyleType& type = cls());

		const string& tooltip() { return m_tooltip; }

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		unique_ptr<Widget> clone() { return make_unique<Button>(this->label(), m_trigger, cls()); }

		static StyleType& cls() { static StyleType ty("Button", Control::cls()); return ty; }

	protected:
		string m_tooltip;
	};

	class TOY_UI_EXPORT ImgButton : public Button
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		ImgButton(Image& image, const Trigger& trigger = Trigger(), StyleType& type = cls());
		ImgButton(const string& image, const Trigger& trigger = Trigger(), StyleType& type = cls());

		const string& tooltip() { return m_tooltip; }

		static StyleType& cls() { static StyleType ty("ImgButton", Button::cls()); return ty; }

	protected:
		string m_tooltip;
	};

	class TOY_UI_EXPORT WrapButton : public Sheet, public WidgetTrigger<WrapButton>
	{
	public:
		typedef WidgetTrigger<WrapButton>::Trigger Trigger;

	public:
		WrapButton(Widget* content, const Trigger& trigger = Trigger(), StyleType& type = cls());
		WrapButton(unique_ptr<Widget> content, const Trigger& trigger = Trigger(), StyleType& type = cls());

		Widget* content();

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		const string& contentlabel() { return m_content->contentlabel(); }

		static StyleType& cls() { static StyleType ty("WrapButton", Sheet::cls()); return ty; }

	protected:
		Widget* m_content;
	};

	class TOY_UI_EXPORT Toggle : public Control
	{
	public:
		typedef std::function<void(Toggle*)> Trigger;

	public:
		Toggle(const Trigger& triggerOn, const Trigger& triggerOff, bool isOn = true, StyleType& type = cls());

		bool on() { return m_on; }

		void update(bool on);
		void toggle();

		void leftClick(MouseEvent& mouseEvent);

		static StyleType& cls() { static StyleType ty("Toggle", Control::cls()); return ty; }

	protected:
		Trigger m_triggerOn;
		Trigger m_triggerOff;

		bool m_on;
	};
}

#endif
