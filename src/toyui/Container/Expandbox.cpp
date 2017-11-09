//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Expandbox.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	Expandbox::Expandbox(Wedge& parent, const StringVector& elements, bool collapsed, Type& type)
		: Wedge(parent, type)
		, m_header(*this, {}, nullptr, Header())
		, m_toggle(m_header, [this](Widget&, bool on) { on ? this->expand() : this->collapse(); }, !collapsed, Switch())
		, m_body(*this, Body())
		, m_collapsed(collapsed)
	{
		m_header.reset(elements);

		if(collapsed)
			m_body.hide();
	}

	void Expandbox::expand()
	{
		m_body.show();
		m_collapsed = false;
	}

	void Expandbox::collapse()
	{
		m_body.hide();
		m_collapsed = true;
	}
}
