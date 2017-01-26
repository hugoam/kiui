//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_LIST_H
#define TOY_LIST_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/TypeIn.h>

namespace toy
{
	class TOY_UI_EXPORT List : public ScrollSheet
	{
	public:
		List(StyleType& type = cls(), FrameType frameType = STRIPE);

		static StyleType& cls() { static StyleType ty("List", ScrollSheet::cls()); return ty; }
	};

	class TOY_UI_EXPORT SelectList : public List
	{
	public:
		SelectList(StyleType& type = cls());

		Widget& vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void selected(WrapButton& selected);

		static StyleType& cls() { static StyleType ty("SelectList", List::cls()); return ty; }
	};

	class TOY_UI_EXPORT FilterInput : public Input<string>
	{
	public:
		FilterInput(Sheet& list, std::function<void(string)> callback = nullptr);

		void filterOn();
		void filterOff();

		void notifyModify();

		void updateFilter(const string& filter);
		bool fitsFilter(const string& filter, const string& value);

		static StyleType& cls() { static StyleType ty("FilterInput", Input<string>::cls()); return ty; }

	protected:
		Sheet& m_list;
	};

	class TOY_UI_EXPORT LabelSequence : public Band
	{
	public:
		LabelSequence(StringVector labels = StringVector());
	};

	class TOY_UI_EXPORT ButtonSequence : public Band
	{
	public:
		ButtonSequence(StringVector labels = StringVector());
	};

	class TOY_UI_EXPORT SortList : public List//, public Dropper
	{
	public:
		SortList();

		static StyleType& cls() { static StyleType ty("SortList", List::cls()); return ty; }
	};
}

#endif // TOY_WIDGET_H
