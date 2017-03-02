//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WTEXTBOX_H
#define TOY_WTEXTBOX_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Edit/TypeIn.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Textbox : public TypeIn
	{
	public:
		Textbox(WValue& input);
		Textbox(Piece& parent, string& text);

		static Type& cls() { static Type ty("Textbox", TypeIn::cls()); return ty; }

	protected:
		string m_string;
	};
}

#endif
