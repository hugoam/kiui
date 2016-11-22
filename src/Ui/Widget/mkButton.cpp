//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkButton.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/mkUiWindow.h>

namespace mk
{
	Label::Label(const string& label, StyleType& type, FrameType frameType)
		: Widget(type, frameType)
		, m_label(label)
	{}

	void Label::setLabel(const string& label)
	{
		m_label = label;
		m_frame->setDirty(Frame::DIRTY_WIDGET);
	}

	Title::Title(const string& label)
		: Label(label, cls())
	{}

	Icon::Icon(Image& image)
		: Widget(cls())
		, m_image(image)
	{}

	Icon::Icon(const string& image)
		: Icon(findImage(image))
	{}

	/*void Icon::setImage(const string& image)
	{
		m_image = image;
		m_frame->setDirty(Frame::DIRTY_WIDGET);
	}*/

	Button::Button(const string& label, const Trigger& trigger, StyleType& type)
		: Control(type)
		, WidgetTrigger(trigger)
		, m_label(label)
	{}

	void Button::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(uiWindow().keyboard().ctrlPressed())
			this->triggerCtrl();
		else if(uiWindow().keyboard().shiftPressed())
			this->triggerShift();
		else
			this->trigger();
	}

	void Button::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		triggerAlt();
	}

	ImgButton::ImgButton(Image& image, const Trigger& trigger, StyleType& type)
		: Button("", trigger, type)
		, m_image(image)
	{}

	ImgButton::ImgButton(const string& image, const Trigger& trigger, StyleType& type)
		: ImgButton(findImage(image), trigger, type)
	{}

	WrapButton::WrapButton(Widget* content, const Trigger& trigger, StyleType& type)
		: Sheet(type)
		, WidgetTrigger(trigger)
		, m_content(content)
	{}

	WrapButton::WrapButton(unique_ptr<Widget> content, const Trigger& trigger, StyleType& type)
		: WrapButton(content.get(), trigger, type)
	{
		this->append(std::move(content));
	}

	Widget* WrapButton::content()
	{
		return m_contents[0].get();
	}

	void WrapButton::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(uiWindow().keyboard().ctrlPressed())
			this->triggerCtrl();
		else if(uiWindow().keyboard().shiftPressed())
			this->triggerShift();
		else
			this->trigger();

		//toggleState(HOVERED);
	}

	void WrapButton::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		triggerAlt();
	}

	Toggle::Toggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on, StyleType& type)
		: Control(type)
		, m_triggerOn(triggerOn)
		, m_triggerOff(triggerOff)
		, m_on(on)
	{
		if(m_on)
			this->toggleState(ACTIVATED);
	}
	
	void Toggle::update(bool on)
	{
		if(on != m_on)
			this->toggleState(ACTIVATED);
		m_on = on;
	}

	void Toggle::toggle()
	{
		m_on = !m_on;
		this->toggleState(ACTIVATED);

		if(m_on)
			m_triggerOn(this);
		else
			m_triggerOff(this);
	}

	void Toggle::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->toggle();
	}
}
