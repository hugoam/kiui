//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Scheme/RadioButton.h>

#include <toyui/Widget/Widgets.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

using namespace std::placeholders;

namespace toy
{
	RadioChoice::RadioChoice(Widget* content, const Trigger& trigger)
		: WrapButton(content, trigger, cls())
	{}

	RadioSwitch::RadioSwitch(const Trigger& onSelected, size_t active, StringVector labels)
		: Sheet(cls())
		, m_onSelected(onSelected)
		, m_active(nullptr)
		, m_activeIndex(active)
	{
		for(string& label : labels)
			this->emplace<Label>(label);
	}

	Widget& RadioSwitch::vappend(unique_ptr<Widget> widget)
	{
		WrapButton& button = this->makeappend<RadioChoice>(widget.get(), std::bind(&RadioSwitch::activated, this, _1));
		button.append(std::move(widget));
		if(m_contents.size() - 1 == m_activeIndex)
		{
			m_active = &button;
			m_active->activate();
		}
		return button;
	}

	unique_ptr<Widget> RadioSwitch::vrelease(Widget& widget)
	{
		return widget.extract();
	}

	void RadioSwitch::activated(WrapButton& button)
	{
		if(m_active)
			m_active->deactivate();
		m_active = &button;
		m_active->activate();
		if(m_onSelected)
			m_onSelected(*button.content());
	}
}
