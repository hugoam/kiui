//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Tabber.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>

using namespace std::placeholders;

namespace toy
{
	TabHeader::TabHeader(Wedge& parent, const string& label, const Trigger& trigger)
		: Button(parent, label, trigger, cls())
	{}

	Tab::Tab(Wedge& parent, Tabber& tabber, Button& header, bool active)
		: ScrollSheet(parent, cls())
		, m_tabber(tabber)
		, m_header(header)
		, m_active(active)
	{
		if(!m_active)
			this->hide();
		else
			m_header.activate();
	}

	void Tab::handleRemove(Widget& widget)
	{
		m_tabber.removeTab(*this);
	}

	TabberHead::TabberHead(Wedge& parent)
		: Container(parent, cls())
	{}

	TabberBody::TabberBody(Wedge& parent)
		: Container(parent, cls())
	{}

	Tabber::Tabber(Wedge& parent, Type& type, bool downtabs)
		: Container(parent, type)
		, m_currentTab(nullptr)
		, m_headers(*this)
		, m_tabs(*this)
		, m_downTabs(downtabs)
	{
		if(m_downTabs)
			this->swap(0, 1);
		m_headers.hide();
	}

	Tabber::~Tabber()
	{}

	Tab& Tabber::addTab(const string& name)
	{
		TabHeader& header = m_headers.emplace<TabHeader>(name, [this](Widget& button) {return this->headerClicked(button); });
		Tab& tab = m_tabs.emplace<Tab>(*this, header, m_currentTab == nullptr);

		if(!m_currentTab)
			m_currentTab = &tab;
		else if(m_tabs.containerContents().size() == 2)
			m_headers.show();

		return tab;
	}

	void Tabber::removeTab(Tab& tab)
	{
		if(&tab == m_currentTab)
			m_currentTab = nullptr;

		tab.header().destroy();
		tab.destroy();

		if(m_tabs.containerContents().size() > 0)
			this->showTab(size_t(0));
		if(m_tabs.containerContents().size() == 1)
			m_headers.hide();
	}

	Container& Tabber::emplaceContainer()
	{
		return this->addTab("").emplaceContainer();
	}

	void Tabber::headerClicked(Widget& header)
	{
		this->showTab(header.index());
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
