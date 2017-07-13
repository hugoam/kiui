//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_LIST_H
#define TOY_LIST_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT SelectList : public ScrollSheet
	{
	public:
		SelectList(Wedge& parent, Type& type = cls());

		WrapButton& addChoice();

		void selected(Widget& selected);

		static Type& cls() { static Type ty("SelectList", ScrollSheet::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
