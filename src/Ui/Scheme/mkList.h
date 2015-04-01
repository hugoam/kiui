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

namespace mk
{
	class MK_UI_EXPORT List : public ScrollSheet, public Typed<List, Sheet>, public Styled<List>
	{
	public:
		List(Style* style = nullptr);

		using Typed<List, Sheet>::cls;
		using Styled<List>::styleCls;
	};

	class MK_UI_EXPORT Sequence : public Sheet, public Typed<Sequence, Sheet>, public Styled<Sequence>
	{
	public:
		Sequence(Style* style = nullptr);

		using Typed<Sequence, Sheet>::cls;
		using Styled<Sequence>::styleCls;
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

	class MK_UI_EXPORT SortList : public List, public Typed<SortList, List>, public Dropper
	{
	public:
		SortList(Style* style);

		Form* swapdrop(Form* form, Dropper* source) { UNUSED(form); UNUSED(source); return nullptr; }
		bool candrop(Form* form, Dropper* source) { UNUSED(form); UNUSED(source); return false; }
		void dropin(Form* form, Dropper* source, size_t index) { UNUSED(form); UNUSED(source); UNUSED(index); }
		void dropout(Form* form, Dropper* source) { UNUSED(form); UNUSED(source); }

		virtual void moved(size_t from, size_t to) { UNUSED(from); UNUSED(to); }

		using Typed<SortList, List>::cls;
	};
}

#endif // MK_WIDGET_H_INCLUDED
