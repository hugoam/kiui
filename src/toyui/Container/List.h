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

	class _refl_ TOY_UI_EXPORT LabelSequence : public Wedge
	{
	public:
		LabelSequence(Wedge& parent, StringVector labels = StringVector());

		static Type& cls() { static Type ty("LabelSequence", Wedge::Row()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT ButtonSequence : public Wedge
	{
	public:
		ButtonSequence(Wedge& parent, StringVector labels = StringVector());

		static Type& cls() { static Type ty("ButtonSequence", Wedge::Row()); return ty; }
	};

	class _refl_ TOY_UI_EXPORT SortList : public ScrollSheet//, public Dropper
	{
	public:
		SortList(Wedge& parent);

		static Type& cls() { static Type ty("SortList", ScrollSheet::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
