//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WCHECKBOX_H
#define MK_WCHECKBOX_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>

namespace mk
{
	class MK_UI_EXPORT _I_ WCheckbox : public Widget, public Typed<WCheckbox>, public Styled<WCheckbox>
	{
	public:
		WCheckbox(Form* form, Lref& value);

		void build();

		void updateChecked();

		bool leftClick(float xPos, float yPos);

		using Typed<WCheckbox>::cls;

	protected:
		Lref& mValue;
	};
}

#endif
