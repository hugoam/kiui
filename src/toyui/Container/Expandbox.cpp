//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Expandbox.h>

#include <toyui/Widget/Sheet.h>

#include <toyui/Container/Layout.h>

#include <toyui/Frame/Frame.h>

namespace toy
{
	ExpandboxHeader::ExpandboxHeader(Wedge& parent, const Callback& trigger)
		: WrapButton(parent, trigger, cls())
	{}

	ExpandboxBody::ExpandboxBody(Wedge& parent)
		: Container(parent, cls())
	{}

	ExpandboxToggle::ExpandboxToggle(Wedge& parent, const Callback& triggerOn, const Callback& triggerOff, bool on)
		: Toggle(parent, triggerOn, triggerOff, on, cls())
	{}

	Expandbox::Expandbox(Wedge& parent, const string& title, bool collapsed, Type& type)
		: Stack(parent, type)
		, m_header(*this)
		, m_toggle(m_header, [this](Widget&) { this->expand(); }, [this](Widget&) { this->collapse(); }, !collapsed)
		, m_title(m_header, title)
		, m_container(*this)
		, m_collapsed(collapsed)
	{
		m_container.hide();
		m_containerTarget = &m_container;
	}

	Widget& Expandbox::insert(object_ptr<Widget> widget)
	{
		if(!m_collapsed && m_container.frame().hidden())
			m_container.show();

		return this->append(std::move(widget));
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
