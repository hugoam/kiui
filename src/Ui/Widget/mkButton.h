//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WBUTTON_H
#define MK_WBUTTON_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

namespace mk
{
	class MK_UI_EXPORT Label : public Widget
	{
	public:
		Label(const string& label, StyleType& type = cls(), FrameType frameType = FRAME);

		const string& label() { return m_label; }
		unique_ptr<Widget> clone() { return make_unique<Label>(m_label); }

		void setLabel(const string& label);

		static StyleType& cls() { static StyleType ty("Label", Widget::cls()); return ty; }

	protected:
		string m_label;
	};

	class MK_UI_EXPORT Title : public Label
	{
	public:
		Title(const string& label);

		static StyleType& cls() { static StyleType ty("Title", Label::cls()); return ty; }
	};

	class MK_UI_EXPORT Icon : public Widget
	{
	public:
		Icon(Image& image);
		Icon(const string& image);

		Image* image() { return &m_image; }

		//void setImage(Image& image);

		static StyleType& cls() { static StyleType ty("Icon", Widget::cls()); return ty; }

	protected:
		Image& m_image;
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

	class MK_UI_EXPORT Button : public Control, public WidgetTrigger<Button>
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		Button(const string& label, const Trigger& trigger = Trigger(), StyleType& type = cls());

		const string& label() { return m_label; }
		const string& tooltip() { return m_tooltip; }

		void leftClick(MouseEvent& mouseEvent);
		void rightClick(MouseEvent& mouseEvent);

		unique_ptr<Widget> clone() { return make_unique<Button>(m_label, m_trigger, cls()); }

		static StyleType& cls() { static StyleType ty("Button", Control::cls()); return ty; }

	protected:
		string m_label;
		string m_tooltip;
	};

	class MK_UI_EXPORT ImgButton : public Button
	{
	public:
		typedef WidgetTrigger<Button>::Trigger Trigger;

	public:
		ImgButton(Image& image, const Trigger& trigger = Trigger(), StyleType& type = cls());
		ImgButton(const string& image, const Trigger& trigger = Trigger(), StyleType& type = cls());

		Image* image() { return &m_image; }
		const string& tooltip() { return m_tooltip; }

		static StyleType& cls() { static StyleType ty("ImgButton", Button::cls()); return ty; }

	protected:
		Image& m_image;
		string m_tooltip;
	};

	class MK_UI_EXPORT WrapButton : public Sheet, public WidgetTrigger<WrapButton>
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

	class MK_UI_EXPORT Toggle : public Control
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
