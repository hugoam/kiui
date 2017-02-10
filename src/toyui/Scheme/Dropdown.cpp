//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Scheme/Dropdown.h>

#include <toyui/Widget/Widgets.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>
#include <toyui/Frame/Layer.h>

#include <toyui/Frame/Frame.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Scheme/List.h>

using namespace std::placeholders;

namespace toy
{
	Dropdown::Dropdown(const Trigger& onSelected, StringVector choices, bool input, StyleType& type)
		: Sheet(type)
		, m_onSelected()
		, m_list(this->makeappend<DropdownList>(*this))
		, m_header(this->makeappend<DropdownHeader>(*this, input))
		, m_toggle(this->makeappend<DropdownToggle>(*this))
		, m_selected(nullptr)
		, m_down(false)
	{
		m_list.hide();

		for(string& choice : choices)
			this->emplace<Label>(choice);

		m_onSelected = onSelected;
	}

	Dropdown::~Dropdown()
	{}

	Widget& Dropdown::vappend(std::unique_ptr<Widget> widget)
	{
		WrapButton& button = m_list.emplace<DropdownChoice>(std::move(widget), std::bind(&Dropdown::selected, this, _1));
		if(m_selected == nullptr)
			this->select(button);

		return button;
	}

	unique_ptr<Widget> Dropdown::vrelease(Widget& widget)
	{
		return widget.extract();
	}

	void Dropdown::dropup()
	{
		m_list.hide();
		if(m_list.state() & CONTROL)
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

	void Dropdown::select(WrapButton& button)
	{
		if(m_selected)
			m_selected->toggleState(ACTIVATED);

		m_selected = &button;
		m_selected->toggleState(ACTIVATED);
		m_header.updateContent(*button.content());
	}

	void Dropdown::selected(WrapButton& button)
	{
		if(m_down)
			this->dropup();

		this->select(button);

		if(m_onSelected)
			m_onSelected(*button.content());
	}

	DropdownHeader::DropdownHeader(Dropdown& dropdown, bool input)
		: WrapButton(nullptr, std::bind(&DropdownHeader::click, this), cls())
		, m_dropdown(dropdown)
		, m_input(nullptr)
	{
		if(input)
		{
			m_input = &this->makeappend<FilterInput>(m_dropdown.dropbox(), std::bind(&DropdownHeader::onInput, this, _1));
			m_input->hide();
		}
	}

	void DropdownHeader::click()
	{
		if(m_input)
		{
			m_content->hide();
			m_input->show();
			m_input->setString(m_content->contentlabel());
			MouseClickEvent mouseEvent(InputEvent::DEVICE_MOUSE_LEFT_BUTTON, this->rootSheet().mouse().lastX(), this->rootSheet().mouse().lastY());
			m_input->typeIn().leftClick(mouseEvent);
		}
		else
		{
			m_dropdown.dropdown();
		}
	}

	void DropdownHeader::onInput(string value)
	{
		m_input->filterOn();

		if(!m_dropdown.down())
			m_dropdown.dropdown(false);
	}

	void DropdownHeader::updateContent(Widget& choice)
	{
		if(m_input && (m_input->typeIn().state() & CONTROL))
		{
			m_input->typeIn().yieldControl();
			m_input->hide();
		}

		if(m_content)
			this->release(*m_content);
		m_content = &this->append(choice.clone());
	}

	DropdownToggle::DropdownToggle(Dropdown& dropdown)
		: Button("", std::bind(&DropdownToggle::click, this), cls())
		, m_dropdown(dropdown)
	{}

	void DropdownToggle::click()
	{
		if(m_dropdown.header().input())
			m_dropdown.header().input()->filterOff();
		m_dropdown.dropdown();
	}

	DropdownLabel::DropdownLabel(const string& label)
		: Label(label)
	{}

	DropdownChoice::DropdownChoice(unique_ptr<Widget> content, const Trigger& trigger)
		: WrapButton(std::move(content), trigger, cls())
	{}

	DropdownList::DropdownList(Dropdown& dropdown)
		: List(cls(), LAYER)
		, m_dropdown(dropdown)
	{
		m_frame = make_unique<Layer>(*this, 0);
	}

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

	Typedown::Typedown(const Trigger& onSelected, StringVector choices)
		: Dropdown(onSelected, choices, true)
	{}

	MenuList::MenuList(Menu& menu)
		: List(cls(), LAYER)
		, m_menu(menu)
	{
		m_frame = make_unique<Layer>(*this, 0);
	}

	void MenuList::leftClick(MouseEvent& mouseEvent)
	{
		UNUSED(mouseEvent);
		m_menu.dropup();
	}

	Menu::Menu(const string& label, bool submenu)
		: Sheet(cls())
		, m_submenu(submenu)
		, m_button(this->makeappend<Button>(label, std::bind(&Menu::dropdown, this)))
		, m_list(this->makeappend<MenuList>(*this))
		, m_down(false)
	{
		m_list.hide();
	}

	Widget& Menu::vappend(std::unique_ptr<Widget> widget)
	{
		WrapButton& button = m_list.emplace<DropdownChoice>(std::move(widget), std::bind(&Menu::selected, this, _1));
		return button;

		//return m_list.append(std::move(widget));
	}

	unique_ptr<Widget> Menu::vrelease(Widget& widget)
	{
		return widget.extract();
		//return m_list.release(widget);
	}

	void Menu::selected(WrapButton& selected)
	{
		//selected;
		this->dropup();
	}

	void Menu::dropdown()
	{
		m_list.show();
		m_list.takeControl(CM_MODAL);
		m_list.frame().as<Layer>().moveToTop();

		m_down = true;
	}

	void Menu::dropup()
	{
		m_list.hide();
		if(m_list.state() & MODAL)
			m_list.yieldControl();
		m_down = false;
	}
}
