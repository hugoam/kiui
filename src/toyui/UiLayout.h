//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UILAYOUT_H
#define TOY_UILAYOUT_H

/* toy */
#include <toyui/Types.h>
#include <toyobj/Object.h>
#include <toyobj/Util/Colour.h>
#include <toyobj/String/String.h>
#include <toyui/Style/Style.h>

/* standard */
#include <map>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Styler : public Object
	{
	public:
		Styler(UiWindow& uiWindow);

		UiWindow& m_uiWindow;
		std::map<string, Options> m_layout_definitions;
		std::map<string, Options> m_skin_definitions;

		void clear();
		void setup();
	};
}

#endif
