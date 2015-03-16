//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkWTextbox.h>

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
	WTextbox::WTextbox(Form* form, Lref& value)
		: Widget(styleCls(), form)
		, mValue(value)
	{}

	WTextbox::WTextbox(Form* form, string text)
		: Widget(styleCls(), form)
		, mLref(lref(text))
		, mValue(mLref)
	{}

	bool WTextbox::leftClick(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		return true;
	}
}
