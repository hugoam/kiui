//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Typedown.h>

#include <toyui/Input/InputEvent.h>

#include <toyui/Button/Filter.h>

namespace toy
{
	TypedownInput::TypedownInput(const Params& params, StringVector choices, const Callback& callback)
		: DropdownInput({ params, &cls<TypedownInput>() }, choices, callback)
		, m_input({ this }, m_list, nullptr)
	{
		this->move(m_input.m_index, 0);
		m_trigger = [this](Widget&) { this->dropdown(); };
		m_input.hide();
	}

	void TypedownInput::dropdown(bool modal)
	{
		DropdownInput::dropdown(modal);

		m_header.hide();
		m_input.show();

		m_input.setText(""); // m_header.label()
		m_input.selectCaret(0);
		m_input.activate();
	}

	void TypedownInput::dropup()
	{
		m_header.show();
		m_input.hide();

		//m_input.yieldControl();

		DropdownInput::dropup();
	}
}
