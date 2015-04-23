//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkTextbox.h>

#include <Object/String/mkStringConvert.h>

#include <Object/mkRef.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/mkUiWindow.h>

#include <Ui/Widget/mkSheet.h>

namespace mk
{
	Textbox::Textbox(WValue* input)
		: TypeIn(input)
	{
		mStyle = &cls();
	}

	Textbox::Textbox(const string& text)
		: TypeIn(nullptr, text)
	{
		mStyle = &cls();
	}
}
