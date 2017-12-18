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
	Label::Label(const Params& params, const string& label)
		: Widget({ params, &cls<Label>() }, label)
	{}

	Button::Button(const Params& params, const string& content, const Callback& trigger)
		: Widget({ params, &cls<Button>() })
		, ClickTrigger(*this, trigger)
	{
		if(!content.empty())
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

	WrapButton::WrapButton(const Params& params, const Callback& trigger)
		: Wedge({ params, &cls<WrapButton>() })
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

	MultiButton::MultiButton(const Params& params, const StringVector& elements, const Callback& trigger)
		: WrapButton({ params, &cls<MultiButton>() }, trigger)
	{
		this->reset(elements);
	}

	void MultiButton::reset(Button& button)
	{
		this->reset({ button.label() }, button.m_trigger);
	}

	void MultiButton::reset(MultiButton& button)
	{
		this->reset(button.m_elements, button.m_trigger);
	}

	void MultiButton::reset(const StringVector& elements , const Callback& trigger)
	{
		if(trigger)
			m_trigger = trigger;

		this->clear();
		for(const string& value : elements)
			this->emplace_style<Widget>(styles().item, value);
		m_elements = elements;
	}

	Toggle::Toggle(const Params& params, const Callback& callback, bool on)
		: Widget({ params, &cls<Toggle>() })
		, m_on(on)
		, m_callback(callback)
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
