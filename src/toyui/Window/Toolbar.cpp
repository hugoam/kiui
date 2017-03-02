//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Toolbar.h>

namespace toy
{
	ToolButton::ToolButton(Piece& parent, const string& icon)
		: Dropdown(parent)
	{
		this->emplace<Icon>(icon);
		m_header.reset(make_unique<Icon>(m_header, icon));
		m_toggle.hide();
		//m_header.emplace<Icon>(icon);
	}

	Tooldock::Tooldock(Piece& parent)
		: Div(parent, cls())//, GRID)
	{}

	Toolbar::Toolbar(Piece& parent)
		: WrapControl(parent, cls())
	{}
}
