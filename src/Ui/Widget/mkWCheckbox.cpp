//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWCheckbox.h>

#include <Object/String/mkStringConvert.h>
#include <Object/mkRef.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkWTypeIn.h>

#include <Ui/mkUiWindow.h>

#include <Ui/Widget/mkSheet.h>

namespace mk
{
	WCheckbox::WCheckbox(WInputBase* input, bool on)
		: WToggle(styleCls(), std::bind(&WCheckbox::on, this), std::bind(&WCheckbox::off, this), on)
		, mInput(input)
	{}

	void WCheckbox::on()
	{
		mInput->value()->set<bool>(mOn);
		mInput->notifyUpdate();
	}

	void WCheckbox::off()
	{
		mInput->value()->set<bool>(mOn);
		mInput->notifyUpdate();
	}
}
