//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Tabber.h>

#include <toyui/Frame/Frame.h>

namespace toy
{
	Tab::Tab(const Params& params, Tabber& tabber, Button& header, bool active)
		: Wedge({ params, &cls<Tab>() })
		, m_tabber(tabber)
		, m_header(header)
		, m_active(active)
	{
		if(!m_active)
			this->hide();
		else
			m_header.enableState(ACTIVATED);
	}

	void Tab::extract()
	{
		m_tabber.removeTab(*this);
	}

	Tabber::Tabber(const Params& params, bool downtabs)
		: Wedge({ params, &cls<Tabber>() })
		, m_headers({ this, &styles().head })
		, m_tabs({ this, &styles().body })
		, m_currentTab(nullptr)
		, m_downTabs(downtabs)
		, m_hideSingleHeader(false)
	{
		if(m_downTabs)
			this->swap(0, 1);
		if(m_hideSingleHeader)
			m_headers.hide();
	}

	Tab& Tabber::addTab(const string& name)
	{
		Button& header = m_headers.emplace_style<Button>(styles().tab_button, name, [this](Widget& button) {return this->headerClicked(button); });
		Tab& tab = m_tabs.emplace<Tab>(*this, header, m_currentTab == nullptr);

		if(!m_currentTab)
			m_currentTab = &tab;
		else if(m_hideSingleHeader && m_tabs.count() == 2)
			m_headers.show();

		return tab;
	}

	void Tabber::removeTab(Tab& tab)
	{
		if(&tab == m_currentTab)
			m_currentTab = nullptr;

		tab.m_header.destroy();
		tab.destroy();

		if(m_tabs.count() > 0)
			this->showTab(size_t(0));
		if(m_hideSingleHeader && m_tabs.count() == 1)
			m_headers.hide();
	}

	void Tabber::headerClicked(Widget& header)
	{
		this->showTab(header.m_index);
	}

	void Tabber::showTab(Tab& tab)
	{
		if(m_currentTab)
		{
			m_currentTab->hide();
			m_currentTab->m_header.disableState(ACTIVATED);
		}
		tab.show();
		tab.m_header.enableState(ACTIVATED);
		m_currentTab = &tab;
	}

	void Tabber::showTab(size_t index)
	{
		this->showTab(as<Tab>(m_tabs.at(index)));
	}
}
