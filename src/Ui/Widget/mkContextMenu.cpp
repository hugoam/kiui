//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkContextMenu.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkRootSheet.h>

namespace mk
{
	ContextMenu::ContextMenu()
		: Sheet()
	{
		mStyle = &cls();
		this->rootSheet().contextOn(this);
	}

	ContextMenu::~ContextMenu()
	{
		this->rootSheet().contextOff();
	}
}
