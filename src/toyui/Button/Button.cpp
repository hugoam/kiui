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
	Label::Label(Wedge& parent, const string& label, Type& type)
		: Item(parent, type)
	{
		this->setLabel(label);
	}

	Text::Text(Wedge& parent, const string& label)
		: Label(parent, label, cls())
	{}

	Title::Title(Wedge& parent, const string& label)
		: Label(parent, label, cls())
	{}

	Icon::Icon(Wedge& parent, Image& image)
		: Item(parent, cls())
	{
		this->setImage(&image);
	}

	Icon::Icon(Wedge& parent, const string& image)
		: Item(parent, cls())
	{
		if(image != "")
			this->setImage(&findImage(toLower(image)));
	}

	Button::Button(Wedge& parent, const string& label, const Trigger& trigger, Type& type)
		: Control(parent, type)
		, ClickTrigger(*this, trigger)
	{
		this->setLabel(label);
	}

	Button::Button(Wedge& parent, Image& image, const Trigger& trigger, Type& type)
		: Button(parent, "", trigger, type)
	{
		this->setImage(&image);
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

	WrapButton::WrapButton(Wedge& parent, const Trigger& trigger, Type& type)
		: WrapControl(parent, type)
		, ClickTrigger(*this, trigger)
	{}

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

	MultiButton::MultiButton(Wedge& parent, const Trigger& trigger, const StringVector& elements, Type& type)
		: WrapButton(parent, trigger, type)
	{
		this->reset(elements);
	}

	void MultiButton::reset(const StringVector& elements , const Trigger& trigger)
	{
		if(trigger)
			m_trigger = trigger;

		this->clear();
		for(const string& value : elements)
		{
			if(!findImage(toLower(value)).null())
				this->emplace<Icon>(value);
			else
				this->emplace<Label>(value);
		}
		m_elements = elements;
	}

	Toggle::Toggle(Wedge& parent, const Trigger& triggerOn, const Trigger& triggerOff, bool on, Type& type)
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
