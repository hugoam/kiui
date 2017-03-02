//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Button.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Render/Caption.h>

#include <toyui/Widget/RootSheet.h>

#include <toyui/Input/InputDevice.h>

namespace toy
{
	Label::Label(Piece& parent, const string& label, Type& type)
		: Item(parent, type)
	{
		this->setLabel(label);
	}

	Text::Text(Piece& parent, const string& label, Type& type)
		: Label(parent, label, type)
	{}

	Title::Title(Piece& parent, const string& label)
		: Label(parent, label, cls())
	{}

	Icon::Icon(Piece& parent, Image& image)
		: Item(parent, cls())
	{
		this->setImage(&image);
	}

	Icon::Icon(Piece& parent, const string& image)
		: Item(parent, cls())
	{
		if(image != "")
			this->setImage(&findImage(image));
	}

	Button::Button(Piece& parent, const string& label, const Trigger& trigger, Type& type)
		: Control(parent, type)
		, ClickTrigger(*this, trigger)
	{
		this->content().setText(label);
	}

	void Button::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(this->rootSheet().keyboard().ctrlPressed())
			this->clickCtrl();
		else if(this->rootSheet().keyboard().shiftPressed())
			this->clickShift();
		else
			this->click();
	}

	void Button::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->clickAlt();
	}

	ImgButton::ImgButton(Piece& parent, Image& image, const Trigger& trigger, Type& type)
		: Button(parent, "", trigger, type)
	{
		this->setImage(&image);
	}

	ImgButton::ImgButton(Piece& parent, const string& image, const Trigger& trigger, Type& type)
		: ImgButton(parent, findImage(image), trigger, type)
	{}

	WrapButton::WrapButton(Piece& parent, Widget* content, const Trigger& trigger, Type& type)
		: WrapControl(parent, type)
		, ClickTrigger(*this, trigger)
		, m_content(content)
	{}

	WrapButton::WrapButton(Piece& parent, const Trigger& trigger, Type& type)
		: WrapButton(parent, nullptr, trigger, type)
	{}

	WrapButton::WrapButton(Piece& parent, unique_ptr<Widget> content, const Trigger& trigger, Type& type)
		: WrapButton(parent, content.get(), trigger, type)
	{
		this->append(std::move(content));
	}

	void WrapButton::reset(unique_ptr<Widget> content)
	{
		if(m_content)
			this->release(*m_content);
		m_content = &this->append(std::move(content));
	}

	void WrapButton::handleAdd(Widget& widget)
	{
		m_content = &widget;
	}

	void WrapButton::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		if(this->rootSheet().keyboard().ctrlPressed())
			this->clickCtrl();
		else if(this->rootSheet().keyboard().shiftPressed())
			this->clickShift();
		else
			this->click();
	}

	void WrapButton::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->clickAlt();
	}

	Toggle::Toggle(Piece& parent, const Trigger& triggerOn, const Trigger& triggerOff, bool on, Type& type)
		: Control(parent, type)
		, m_triggerOn(triggerOn)
		, m_triggerOff(triggerOff)
		, m_on(on)
	{
		if(m_on)
			this->enableState(ACTIVATED);
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
			m_triggerOn(*this);
		else
			m_triggerOff(*this);
	}

	void Toggle::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->toggle();
	}
}
