//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_LIST_H_INCLUDED
#define MK_LIST_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkDropper.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkTypeIn.h>

namespace mk
{
	class MK_UI_EXPORT List : public ScrollSheet
	{
	public:
		List(FrameType frameType = STRIPE);

		static StyleType& cls() { static StyleType ty("List", ScrollSheet::cls()); return ty; }
	};

	class MK_UI_EXPORT SelectList : public List
	{
	public:
		SelectList();

		Widget& vappend(std::unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void selected(WrapButton& selected);

		static StyleType& cls() { static StyleType ty("SelectList", List::cls()); return ty; }
	};

	class MK_UI_EXPORT FilterInput : public Input<string>
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
		Sheet& mList;
	};

	class MK_UI_EXPORT LabelSequence : public Sequence
	{
	public:
		LabelSequence(StringVector labels = StringVector());
	};

	class MK_UI_EXPORT ButtonSequence : public Sequence
	{
	public:
		ButtonSequence(StringVector labels = StringVector());
	};

	class MK_UI_EXPORT SortList : public List, public Dropper
	{
	public:
		SortList();

		Form* swapdrop(Form* form, Dropper* source) { UNUSED(form); UNUSED(source); return nullptr; }
		bool candrop(Form* form, Dropper* source) { UNUSED(form); UNUSED(source); return false; }
		void dropin(Form* form, Dropper* source, size_t index) { UNUSED(form); UNUSED(source); UNUSED(index); }
		void dropout(Form* form, Dropper* source) { UNUSED(form); UNUSED(source); }

		virtual void moved(size_t from, size_t to) { UNUSED(from); UNUSED(to); }

		static StyleType& cls() { static StyleType ty("SortList", List::cls()); return ty; }
	};
}

#endif // MK_WIDGET_H_INCLUDED
