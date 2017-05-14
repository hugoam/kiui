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

namespace toy
{
	DropdownHead::DropdownHead(Dropdown& parent, const Callback& trigger)
		: MultiButton(parent, trigger, {}, cls())
		, m_dropdown(parent)
	{}

	DropdownToggle::DropdownToggle(Wedge& parent, const Callback& trigger)
		: Button(parent, "", trigger, cls())
	{}

	DropdownChoice::DropdownChoice(Wedge& parent, Dropdown& dropdown, const Callback& trigger, const StringVector& elements)
		: MultiButton(parent, trigger, elements, cls())
		, m_dropdown(dropdown)
	{}

	void DropdownChoice::leftClick(MouseEvent& mouseEvent)
	{
		MultiButton::leftClick(mouseEvent);
		m_dropdown.selected(*this);
	}

	DropdownList::DropdownList(Dropdown& dropdown)
		: Container(dropdown, cls(), LAYER)
		, m_dropdown(dropdown)
	{}

	void DropdownList::leftClick(MouseEvent& mouseEvent)
	{
		mouseEvent.consumed = true;
		m_dropdown.dropup();
	}

	void DropdownList::rightClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_dropdown.dropup();
	}

	Dropdown::Dropdown(Wedge& parent, Type& type)
		: WrapButton(parent, [this](Widget&) { this->dropdown(true); }, type)
		, m_header(*this, [this](Widget&) { this->dropdown(true); })
		, m_toggle(*this, [this](Widget&) { this->dropdown(true); })
		, m_list(*this)
		, m_down(false)
	{
		m_list.hide();
	}

	DropdownChoice& Dropdown::addChoice(const StringVector& elements, const Callback& trigger)
	{
		return m_list.emplace<DropdownChoice>(*this, trigger, elements);
	}

	Widget& Dropdown::insert(unique_ptr<Widget> widget)
	{
		widget->parent()->remove(*widget);

		DropdownChoice& choice = this->addChoice({});
		if(widget->type().upcast(MultiButton::cls()))
			choice.reset(widget->as<MultiButton>());
		else if(widget->type().upcast(Button::cls()))
			choice.reset({ widget->as<Button>().label() });
		return choice;
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

	void Dropdown::selected(DropdownChoice& selected)
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

	DropdownChoice& DropdownInput::addChoice(const StringVector& elements, const Callback& trigger)
	{
		DropdownChoice& choice = m_list.emplace<DropdownChoice>(*this, trigger, elements);
		if(m_selected == nullptr)
			this->select(choice);
		return choice;
	}

	void DropdownInput::select(DropdownChoice& choice)
	{
		if(m_selected)
			m_selected->disableState(ACTIVATED);

		m_selected = &choice;
		m_selected->enableState(ACTIVATED);

		m_activeHeader ? m_header.reset(*m_selected) : m_header.reset(m_selected->elements());
	}

	void DropdownInput::selected(DropdownChoice& choice)
	{
		this->dropup();

		this->select(choice);

		if(m_onSelected)
			m_onSelected(*m_selected);
	}
}
