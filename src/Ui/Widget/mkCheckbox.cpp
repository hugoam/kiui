//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkCheckbox.h>

#include <Object/String/mkStringConvert.h>
#include <Object/mkRef.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Widget/mkTypeIn.h>

#include <Ui/mkUiWindow.h>

#include <Ui/Widget/mkSheet.h>

namespace mk
{
	Checkbox::Checkbox(WValue* input, bool on)
		: Toggle(std::bind(&Checkbox::toggleOn, this), std::bind(&Checkbox::toggleOff, this), on)
		, mInput(input)
	{
		mStyle = &cls();
	}

	void Checkbox::toggleOn()
	{
		if(mInput)
		{
			mInput->value()->set<bool>(mOn);
			mInput->triggerModify();
		}
	}

	void Checkbox::toggleOff()
	{
		if(mInput)
		{
			mInput->value()->set<bool>(mOn);
			mInput->triggerModify();
		}
	}
}
