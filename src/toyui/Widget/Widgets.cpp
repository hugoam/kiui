//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Widget/Widgets.h>

namespace toy
{
	Control::Control(StyleType& type)
		: Widget(type)
	{}

	Page::Page(const string& name, const string& dockid)
		: ScrollSheet(cls())
		, m_name(name)
		, m_dockId(dockid)
	{}

	Dialog::Dialog()
		: Sheet(cls())
	{}

	Header::Header()
		: Sheet(cls())
	{}
}
