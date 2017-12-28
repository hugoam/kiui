//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Toolbar.h>

namespace toy
{
	ToolButton::ToolButton(const Params& params, const string& icon, const Callback& trigger)
		: DropdownInput({ params, &cls<ToolButton>() }, {}, nullptr)
	{
		m_trigger = nullptr; // don't drop on left click
		m_triggerAlt = [this](Widget&) { this->dropdown(true); }; // drop on right

		// MultiButton& choice = this->addChoice({ icon }); // @todo multiple tools, dropdown is complicated to retrofit
		m_header.reset({ icon }, [this, trigger](Widget&) { if(trigger) trigger(*this); });
		m_toggle.hide();
	}

	void ToolButton::activate()
	{
		this->enableState(ACTIVATED);
	}

	void ToolButton::deactivate()
	{
		this->disableState(ACTIVATED);
	}

	Tooldock::Tooldock(const Params& params)
		: Wedge({ params, &cls<Tooldock>() })//, GRID)
	{}

	Toolbar::Toolbar(const Params& params)
		: Wedge({ params, &cls<Toolbar>(), is<Tooldock>(*params.parent) ? &styles().toolbar_wrap : &styles().toolbar })
		, m_mover({ this, &styles().mover })
	{}
}
