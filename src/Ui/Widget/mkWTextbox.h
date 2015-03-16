//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTEXTBOX_H
#define MK_WTEXTBOX_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>
#include <Object/mkRef.h>

namespace mk
{
	class MK_UI_EXPORT WTextbox : public Widget, public Styled<WTextbox>
	{
	public:
		WTextbox(Form* form, Lref& value);
		WTextbox(Form* form, string text);

		bool leftClick(float xPos, float yPos);

	protected:
		Lref mLref;
		Lref& mValue;
		string mText;
	};
}

#endif
