//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WCHECKBOX_H
#define MK_WCHECKBOX_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkButton.h>

namespace mk
{
	class MK_UI_EXPORT _I_ Checkbox : public Toggle
	{
	public:
		Checkbox(WValue* input, bool on);

		void toggleOn();
		void toggleOff();

		static StyleType& cls() { static StyleType ty("Checkbox", Toggle::cls()); return ty; }

	protected:
		WValue* mInput;
	};
}

#endif
