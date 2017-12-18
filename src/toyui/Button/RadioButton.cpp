//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/RadioButton.h>

namespace toy
{
	RadioSwitch::RadioSwitch(const Params& params, StringVector labels, const Callback& onSelected, size_t active)
		: Wedge({ params, &cls<RadioSwitch>() })
		, m_onSelected(onSelected)
		, m_active(nullptr)
		, m_activeIndex(active)
	{
		for(string& label : labels)
			this->addChoice({ label });
	}

	MultiButton& RadioSwitch::addChoice(const StringVector& elements)
	{
		MultiButton& choice = this->emplace_style<MultiButton>(styles().radio_choice , elements, [&](Widget& button) { this->activated(as<MultiButton>(button)); });
		
		if(m_contents.size() - 1 == m_activeIndex)
		{
			m_active = &choice;
			m_active->enableState(ACTIVATED);
		}

		return choice;
	}

	void RadioSwitch::activated(MultiButton& button)
	{
		if(m_active)
			m_active->disableState(ACTIVATED);
		m_active = &button;
		m_active->enableState(ACTIVATED);
		if(m_onSelected)
			m_onSelected(*m_active);
	}
}
