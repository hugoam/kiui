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
	Control::Control()
		: Widget()
	{
		mStyle = &cls();
	}

	Page::Page(const string& name, const string& dockid)
		: ScrollSheet()
		, mName(name)
		, mDockId(dockid)
	{
		mStyle = &cls();
	}

	Dialog::Dialog()
		: Sheet()
	{
		mStyle = &cls();
	}

	Header::Header()
		: Sheet()
	{
		mStyle = &cls();
	}
}
