//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Expandbox.h>

#include <toyui/Widget/Sheet.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>

namespace toy
{
	ExpandboxHeader::ExpandboxHeader(Piece& parent, const Trigger& trigger)
		: WrapButton(parent, nullptr, trigger, cls())
	{}

	ExpandboxBody::ExpandboxBody(Piece& parent)
		: Container(parent, cls())
	{}

	ExpandboxToggle::ExpandboxToggle(Piece& parent, const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: Toggle(parent, triggerOn, triggerOff, on, cls())
	{}

	Expandbox::Expandbox(Piece& parent, const string& title, bool collapsed, bool build, Type& type)
		: Stack(parent, type)
		, m_header(*this)
		, m_toggle(m_header, std::bind(&Expandbox::expand, this), std::bind(&Expandbox::collapse, this), !collapsed)
		, m_title(m_header, title)
		, m_container(*this)
		, m_collapsed(collapsed)
	{
		m_container.hide();
	}

	Expandbox::~Expandbox()
	{}

	Container& Expandbox::emplaceContainer()
	{
		if(!m_collapsed && m_container.frame().hidden())
			m_container.show();

		return m_container;
	}

	void Expandbox::expand()
	{
		m_container.show();
		m_collapsed = false;
	}

	void Expandbox::collapse()
	{
		m_container.hide();
		m_collapsed = true;
	}
}
