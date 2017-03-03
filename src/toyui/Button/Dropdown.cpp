//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Dropdown.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Frame/Frame.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Container/List.h>

using namespace std::placeholders;

namespace toy
{
	DropdownHead::DropdownHead(Wedge& parent, const Trigger& trigger)
		: MultiButton(parent, trigger, {}, cls())
	{}

	DropdownToggle::DropdownToggle(Wedge& parent, const Trigger& trigger)
		: Button(parent, "", trigger, cls())
	{}

	DropdownChoice::DropdownChoice(Wedge& parent, const Trigger& trigger, const StringVector& elements)
		: MultiButton(parent, trigger, elements, cls())
	{}

	DropdownList::DropdownList(Dropdown& dropdown)
		: Container(dropdown, cls(), LAYER)
		, m_dropdown(dropdown)
	{}

	void DropdownList::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_dropdown.dropup();
	}

	void DropdownList::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		//m_dropdown.dropup();
	}

	Dropdown::Dropdown(Wedge& parent, Type& type)
		: WrapButton(parent, std::bind(&Dropdown::dropdown, this, true), type)
		, m_header(*this, std::bind(&Dropdown::dropdown, this, true))
		, m_toggle(*this, std::bind(&Dropdown::dropdown, this, true))
		, m_list(*this)
		, m_down(false)
	{
		m_list.hide();
	}

	DropdownChoice& Dropdown::addChoice()
	{
		return m_list.emplace<DropdownChoice>([this](Widget& widget) { this->dropup(); }, StringVector{});
		// widget.setStyle(DropdownChoice::cls());
	}

	Container& Dropdown::emplaceContainer()
	{
		return this->addChoice();
	}

	void Dropdown::dropup()
	{
		m_list.hide();
		m_list.yieldControl();
		m_down = false;
	}

	void Dropdown::dropdown(bool modal)
	{
		m_list.show();
		m_list.frame().as<Layer>().moveToTop();
		m_list.takeControl(CM_MODAL);
		m_down = true;
	}

	DropdownInput::DropdownInput(Wedge& parent, const Trigger& onSelected, StringVector choices, Type& type)
		: Dropdown(parent, type)
		, m_onSelected()
		, m_selected(nullptr)
	{
		for(string& choice : choices)
			this->addChoice({ choice });

		m_onSelected = onSelected;
	}

	DropdownChoice& DropdownInput::addChoice(const StringVector& elements)
	{
		DropdownChoice& choice = m_list.emplace<DropdownChoice>([this](Widget& button) { this->selected(button.as<DropdownChoice>()); }, elements);
		if(m_selected == nullptr)
			this->select(choice);
		return choice;
	}

	Container& DropdownInput::emplaceContainer()
	{
		return this->addChoice({ "" });
	}

	void DropdownInput::select(DropdownChoice& choice)
	{
		if(m_selected)
			m_selected->disableState(ACTIVATED);

		m_selected = &choice;
		m_selected->enableState(ACTIVATED);

		this->updateHead(*m_selected);
	}

	void DropdownInput::selected(DropdownChoice& choice)
	{
		if(m_down)
			this->dropup();

		this->select(choice);

		if(m_onSelected)
			m_onSelected(*m_selected);
	}

	void DropdownInput::updateHead(MultiButton& choice)
	{
		m_header.reset(choice.elements());
	}
}
