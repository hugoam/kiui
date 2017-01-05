//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkTabber.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

using namespace std::placeholders;

namespace mk
{
	TabHeader::TabHeader(const string& label, const Trigger& trigger)
		: Button(label, trigger, cls())
	{}

	Tab::Tab(Button& header, bool active)
		: Sheet(cls())
		, m_header(header)
		, m_active(active)
	{
		if(!m_active)
			this->hide();
		else
			m_header.activate();
	}

	unique_ptr<Widget> Tab::vrelease(Widget& widget)
	{
		return m_parent->parent()->vrelease(widget);
	}

	TabberHead::TabberHead()
		: Band(cls())
	{}

	TabberBody::TabberBody()
		: Sheet(cls())
	{}

	Tabber::Tabber(StyleType& type, bool downtabs)
		: Sheet(type)
		, m_currentTab(nullptr)
		, m_downTabs(downtabs)
		, m_headers(this->makeappend<TabberHead>())
		, m_tabs(this->makeappend<TabberBody>())
	{
		//if(m_downTabs)
		//	m_frame->as<Stripe>().move(0, 1);
		m_headers.hide();
	}

	Tabber::~Tabber()
	{}

	Widget& Tabber::vappend(unique_ptr<Widget> widget)
	{
		Button& header = m_headers.emplace<TabHeader>(widget->name(), std::bind(&Tabber::headerClicked, this, _1));
		Tab& tab = m_tabs.emplace<Tab>(header, m_currentTab == nullptr);

		if(!m_currentTab)
			m_currentTab = &tab;
		else if(m_tabs.count() == 2)
			m_headers.show();

		return tab.append(std::move(widget));
	}

	unique_ptr<Widget> Tabber::vrelease(Widget& widget)
	{
		Tab& tab = widget.parent()->as<Tab>();

		if(&tab == m_currentTab)
			m_currentTab = nullptr;

		unique_ptr<Widget> unique = widget.unbind();
		tab.header().destroy();
		tab.destroy();

		if(m_tabs.count() > 0)
			this->showTab(size_t(0));
		if(m_tabs.count() == 1)
			m_headers.hide();

		return unique;
	}

	void Tabber::headerClicked(Button& header)
	{
		this->showTab(header.frame().index());
	}

	void Tabber::showTab(Tab& tab)
	{
		if(m_currentTab)
		{
			m_currentTab->hide();
			m_currentTab->header().deactivate();
		}
		tab.show();
		tab.header().activate();
		m_currentTab = &tab;
	}

	void Tabber::showTab(size_t index)
	{
		this->showTab(m_tabs.at(index).as<Tab>());
	}
}
