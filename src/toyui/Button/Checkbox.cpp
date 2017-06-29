//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Checkbox.h>

#include <toyui/Types.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Any.h>

#include <toyui/Frame/Frame.h>

#include <toyui/Edit/TypeIn.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	Checkbox::Checkbox(Wedge& parent, WValue* input, bool on)
		: Toggle(parent, [this](Widget&, bool on) { this->toggle(on); }, on, cls())
		, m_input(input)
	{}

	void Checkbox::toggle(bool on)
	{
		if(!m_input) return;
		m_input->value().value<bool>() = on;
		m_input->triggerModify();
	}
}
