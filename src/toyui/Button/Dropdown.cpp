//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Types.h>
#include <toyui/Button/Dropdown.h>

namespace toy
{
	Dropdown::Dropdown(Wedge& parent, Type& type)
		: WrapButton(parent, [this](Widget&) { this->dropdown(true); }, type)
		, m_header(*this, {}, [this](Widget&) { this->dropdown(true); }, Head())
		, m_toggle(*this, "", [this](Widget&) { this->dropdown(true); }, Toggle())
		, m_list(*this, nullptr, List())
		, m_down(false)
	{}

	MultiButton& Dropdown::addChoice(const StringVector& elements, const Callback& trigger)
	{
		Callback callback = [this, trigger](Widget& widget) { this->selected(widget.as<MultiButton>()); if(trigger) trigger(widget); };
		return m_list.emplace<MultiButton>(elements, callback, Dropdown::Choice());
	}

	void Dropdown::dropup()
	{
		m_list.close();
		m_down = false;
	}

	void Dropdown::dropdown(bool modal)
	{
		m_list.open(modal);
		m_down = true;
	}

	void Dropdown::selected(MultiButton& selected)
	{
		this->dropup();
	}

	DropdownInput::DropdownInput(Wedge& parent, const Callback& onSelected, StringVector choices, Type& type)
		: Dropdown(parent, type)
		, m_onSelected()
		, m_selected(nullptr)
		, m_activeHeader(false)
	{
		for(string& choice : choices)
			this->addChoice({ choice });

		m_onSelected = onSelected;
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

		m_activeHeader ? m_header.reset(*m_selected) : m_header.reset(m_selected->elements());
	}

	void DropdownInput::selected(MultiButton& choice)
	{
		this->dropup();

		this->select(choice);

		if(m_onSelected)
			m_onSelected(*m_selected);
	}
}
