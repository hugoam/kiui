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
	class MK_UI_EXPORT Textbox : public Widget, public Typed<Textbox, Widget>, public Styled<Textbox>
	{
	public:
		Textbox(Lref& value);
		Textbox(const string& text);

		bool leftClick(float xPos, float yPos);

		using Typed<Textbox, Widget>::cls;

	protected:
		Lref mLref;
		Lref& mValue;
		string mText;
	};
}

#endif
