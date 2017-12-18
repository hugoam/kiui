//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TEXTBOX_H
#define TOY_TEXTBOX_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Edit/TypeIn.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Textbox : public TypeIn
	{
	public:
		Textbox(const Params& params, const string& text);

		string m_string;
	};
}

#endif
