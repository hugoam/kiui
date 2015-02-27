//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_LIST_H_INCLUDED
#define MK_LIST_H_INCLUDED

/* mk headers */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkDropper.h>

namespace mk
{
	class MK_UI_EXPORT List : public Form
	{
	public:
		List(const string& cls);
	};

	class MK_UI_EXPORT SortList : public List//, public Dropper
	{
	public:
		SortList(const string& cls);

		//void move(Form* form, size_t index);
		//void transfer(Form* form, SortList* list, size_t index);

		virtual void moved(size_t from, size_t to) { UNUSED(from); UNUSED(to); }
	};
}

#endif // MK_WIDGET_H_INCLUDED
