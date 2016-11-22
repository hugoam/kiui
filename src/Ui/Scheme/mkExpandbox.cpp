//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkExpandbox.h>

#include <Ui/Widget/mkSheet.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

namespace mk
{
	ExpandboxHeader::ExpandboxHeader()
		: Band(cls())
	{}

	ExpandboxBody::ExpandboxBody()
		: Sheet(cls())
	{}

	ExpandboxToggle::ExpandboxToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: Toggle(triggerOn, triggerOff, on, cls())
	{}

	Expandbox::Expandbox(const string& title, bool collapsed, bool build, StyleType& type)
		: Sheet(type)
		, m_title(title)
		, m_collapsed(collapsed)
	{
		if(build)
		{
			m_header = &this->makeappend<ExpandboxHeader>();
			m_container = &this->makeappend<ExpandboxBody>();

			m_expandButton = &m_header->emplace<ExpandboxToggle>(std::bind(&Expandbox::expand, this), std::bind(&Expandbox::collapse, this), !m_collapsed);
			m_titleLabel = &m_header->emplace<Title>(m_title);

			m_container->hide();
		}
	}

	Expandbox::~Expandbox()
	{}

	Widget& Expandbox::vappend(unique_ptr<Widget> widget)
	{
		if(!m_collapsed && m_container->frame().hidden())
			m_container->show();
		return m_container->append(std::move(widget));
	}

	unique_ptr<Widget> Expandbox::vrelease(Widget& widget)
	{
		return m_container->release(widget);
	}

	void Expandbox::expand()
	{
		m_container->show();
		m_collapsed = false;
	}

	void Expandbox::collapse()
	{
		m_container->hide();
		m_collapsed = true;
	}
}
