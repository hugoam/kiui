//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/Expandbox.h>

#include <toyui/Widget/Sheet.h>

namespace toy
{
	Expandbox::Expandbox(const Params& params, const StringVector& elements, bool collapsed)
		: Wedge({ params, &cls<Expandbox>() })
		, m_header({ this, &styles().header }, {}, nullptr)
		, m_toggle({ &m_header, &styles().toggle }, [this](Widget&, bool on) { on ? this->expand() : this->collapse(); }, !collapsed)
		, m_body({ this, &styles().body })
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
