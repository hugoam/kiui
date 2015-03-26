//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WCHECKBOX_H
#define MK_WCHECKBOX_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWButton.h>

namespace mk
{
	class MK_UI_EXPORT _I_ WCheckbox : public WToggle, public Typed<WCheckbox>, public Styled<WCheckbox>
	{
	public:
		WCheckbox(WInputBase* input, bool on);

		void on();
		void off();

		using Typed<WCheckbox>::cls;

	protected:
		WInputBase* mInput;
	};
}

#endif
