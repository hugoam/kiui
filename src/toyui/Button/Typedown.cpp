//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Typedown.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Input/InputDevice.h>

#include <toyui/Button/Filter.h>

namespace toy
{
	TypedownInput::TypedownInput(Wedge& parent, const Trigger& onSelected, StringVector choices)
		: DropdownInput(parent, onSelected, choices)
		, m_input(*this, m_list, [this](const string& value) { this->onInput(value); })
	{
		m_input.hide();
	}

	void TypedownInput::click()
	{
		this->showFilter();
		MouseClickEvent mouseEvent(DEVICE_MOUSE_LEFT_BUTTON, this->rootSheet().mouse().lastX(), this->rootSheet().mouse().lastY());
		m_input.typeIn().leftClick(mouseEvent);
	}

	void TypedownInput::showFilter()
	{
		m_header.hide();
		m_input.show();
		m_input.setString(m_header.content().contentlabel());
	}

	void TypedownInput::hideFilter()
	{
		if(!(m_input.typeIn().state() & CONTROL))
			return;

		m_input.filterOff();
		m_input.typeIn().yieldControl();
		m_input.hide();
	}

	void TypedownInput::onInput(string value)
	{
		m_input.filterOn();

		if(!m_down)
			this->dropdown(false);
	}
}
