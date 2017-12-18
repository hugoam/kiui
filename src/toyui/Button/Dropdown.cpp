//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Types.h>
#include <toyui/Button/Dropdown.h>

namespace toy
{
	Dropdown::Dropdown(const Params& params)
		: WrapButton({ params, &cls<Dropdown>() }, [this](Widget&) { this->dropdown(true); })
		, m_header({ this, &styles().head }, {}, nullptr)
		, m_toggle({ this, &styles().toggle }, "", [this](Widget&) { this->dropdown(true); })
		, m_list({ this, &styles().list }, nullptr, false)
	{}

	MultiButton& Dropdown::addChoice(const StringVector& elements, const Callback& trigger)
	{
		Callback callback = [this, trigger](Widget& widget) { this->selected(as<MultiButton>(widget)); if(trigger) trigger(widget); };
		return m_list.emplace_style<MultiButton>(styles().choice , elements, callback);
	}

	void Dropdown::dropup()
	{
		m_list.close();
	}

	void Dropdown::dropdown(bool modal)
	{
		m_list.open(modal);
	}

	void Dropdown::selected(MultiButton& selected)
	{
		UNUSED(selected);
		this->dropup();
	}

	DropdownInput::DropdownInput(const Params& params, StringVector choices, const Callback& onSelected)
		: Dropdown({ params, &cls<DropdownInput>() })
		, m_onSelected(onSelected)
		, m_selected(nullptr)
	{
		for(string& choice : choices)
			this->addChoice({ choice });
	}

	MultiButton& DropdownInput::addChoice(const StringVector& elements, const Callback& trigger)
	{
		MultiButton& choice = Dropdown::addChoice(elements, trigger);
		if(m_selected == nullptr)
			this->select(choice);
		return choice;
	}

	void DropdownInput::select(MultiButton& choice)
	{
		if(m_selected)
			m_selected->disableState(SELECTED);

		m_selected = &choice;
		m_selected->enableState(SELECTED);

		m_header.reset(m_selected->m_elements);
	}

	void DropdownInput::selected(MultiButton& choice)
	{
		this->dropup();

		this->select(choice);

		if(m_onSelected)
			m_onSelected(*m_selected);
	}
}
