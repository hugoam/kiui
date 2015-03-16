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

#include <Ui/mkUiWindow.h>

#include <Ui/Widget/mkSheet.h>

namespace mk
{
	WCheckbox::WCheckbox(Form* form, Lref& value)
		: Widget(styleCls(), form)
		, mValue(value)
	{
		mForm->setLabel("");
	}

	void WCheckbox::build()
	{
		this->updateChecked();
	}

	void WCheckbox::updateChecked()
	{
		if(mValue->any<bool>()->ref())
			this->updateState(ACTIVATED);
		else
			this->updateState(ENABLED);
	}

	bool WCheckbox::leftClick(float xPos, float yPos)
	{
		UNUSED(xPos); UNUSED(yPos);
		mValue->any<bool>()->ref() = !mValue->get<bool>();
		this->updateChecked();
		return true;
	}
}
