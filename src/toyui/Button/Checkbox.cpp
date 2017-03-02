//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Checkbox.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Ref.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Edit/TypeIn.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	Checkbox::Checkbox(Piece& parent, WValue* input, bool on)
		: Toggle(parent, std::bind(&Checkbox::toggleOn, this), std::bind(&Checkbox::toggleOff, this), on, cls())
		, m_input(input)
	{}

	void Checkbox::toggleOn()
	{
		if(m_input)
		{
			m_input->value()->set<bool>(m_on);
			m_input->triggerModify();
		}
	}

	void Checkbox::toggleOff()
	{
		if(m_input)
		{
			m_input->value()->set<bool>(m_on);
			m_input->triggerModify();
		}
	}
}
