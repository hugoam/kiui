//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_LIST_H
#define TOY_LIST_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/ScrollSheet.h>
#include <toyui/Edit/TypeIn.h>

namespace toy
{
	class TOY_UI_EXPORT List : public ScrollContainer
	{
	public:
		List(Wedge& parent, Type& type = cls(), FrameType frameType = STRIPE);

		static Type& cls() { static Type ty("List", Container::cls()); return ty; }
	};

	class TOY_UI_EXPORT SelectList : public List
	{
	public:
		SelectList(Wedge& parent, Type& type = cls());

		WrapButton& addChoice();
		virtual Container& emplaceContainer();

		void selected(Widget& selected);

		static Type& cls() { static Type ty("SelectList", List::cls()); return ty; }
	};

	class TOY_UI_EXPORT LabelSequence : public Container
	{
	public:
		LabelSequence(Wedge& parent, StringVector labels = StringVector());

		static Type& cls() { static Type ty("LabelSequence", Line::cls()); return ty; }
	};

	class TOY_UI_EXPORT ButtonSequence : public Container
	{
	public:
		ButtonSequence(Wedge& parent, StringVector labels = StringVector());

		static Type& cls() { static Type ty("ButtonSequence", Line::cls()); return ty; }
	};

	class TOY_UI_EXPORT SortList : public List//, public Dropper
	{
	public:
		SortList(Wedge& parent);

		static Type& cls() { static Type ty("SortList", List::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
