//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Widget/mkTextbox.h>
#include <Ui/Widget/mkProgressBar.h>

#include <Object/String/mkStringConvert.h>

#include <Object/Image/mkImage.h>

namespace mk
{
	Control::Control(Style* style)
		: Widget(style)
	{}

	WrapX::WrapX()
		: Sheet(styleCls())
	{}

	WrapY::WrapY()
		: Sheet(styleCls())
	{}

	DivX::DivX()
		: Sheet(styleCls())
	{}

	DivY::DivY()
		: Sheet(styleCls())
	{}

	PartitionX::PartitionX()
		: Sheet(styleCls())
	{}

	PartitionY::PartitionY()
		: Sheet(styleCls())
	{}

	Page::Page(const string& name, const string& dockid, Style* style)
		: ScrollSheet(style ? style : styleCls())
		, mName(name)
		, mDockId(dockid)
	{}

	Dialog::Dialog()
		: Sheet(styleCls())
	{}

	Header::Header()
		: Sheet(styleCls())
	{}
}
