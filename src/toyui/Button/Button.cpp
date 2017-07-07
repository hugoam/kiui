//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Button.h>

#include <toyui/Frame/Caption.h>

#include <toyui/Widget/RootSheet.h>

#include <toyui/Input/InputDevice.h>

namespace toy
{
	Label::Label(Wedge& parent, const string& label, Type& type)
		: Item(parent, label, type)
	{}

	Text::Text(Wedge& parent, const string& label)
		: Label(parent, label, cls())
	{}

	Button::Button(Wedge& parent, const string& content, const Callback& trigger, Type& type)
		: Item(parent, type)
		, ClickTrigger(*this, trigger)
	{
		this->setContent(content);
	}

	bool Button::leftClick(MouseEvent& mouseEvent)
	{
		return this->clickMods(mouseEvent);
	}

	bool Button::rightClick(MouseEvent& mouseEvent)
	{
		return this->clickAlt(mouseEvent);
	}

	WrapButton::WrapButton(Wedge& parent, const Callback& trigger, Type& type)
		: Wedge(parent, type)
		, ClickTrigger(*this, trigger)
	{}

	bool WrapButton::leftClick(MouseEvent& mouseEvent)
	{
		return this->clickMods(mouseEvent);
	}

	bool WrapButton::rightClick(MouseEvent& mouseEvent)
	{
		return this->clickAlt(mouseEvent);
	}

	MultiButton::MultiButton(Wedge& parent, const StringVector& elements, const Callback& trigger, Type& type)
		: WrapButton(parent, trigger, type)
	{
		this->reset(elements);
	}

	void MultiButton::reset(Button& button)
	{
		this->reset({ button.label() }, button.trigger());
	}

	void MultiButton::reset(MultiButton& button)
	{
		this->reset(button.m_elements, button.m_trigger);
	}

	void MultiButton::reset(const StringVector& elements , const Callback& trigger)
	{
		if(trigger)
			m_trigger = trigger;

		this->store().clear();
		for(const string& value : elements)
			this->emplace<Item>(value);
		m_elements = elements;
	}

	Toggle::Toggle(Wedge& parent, const Callback& callback, bool on, Type& type)
		: Item(parent, type)
		, m_callback(callback)
		, m_on(on)
	{
		if(m_on)
			this->enableState(ACTIVATED);
	}

	void Toggle::update(bool on)
	{
		m_on = on;
		m_on ? this->enableState(ACTIVATED) : this->disableState(ACTIVATED);
	}

	void Toggle::toggle()
	{
		m_on = !m_on;
		m_on ? this->enableState(ACTIVATED) : this->disableState(ACTIVATED);
		if(m_callback) m_callback(*this, m_on);
	}

	bool Toggle::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		this->toggle();
		return true;
	}
}
