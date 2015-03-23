//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkList.h>

#include <Ui/Form/mkButton.h>
#include <Ui/Form/mkWidgets.h>

namespace mk
{
	List::List(Style* style)
		: Form(style ? style : styleCls())
	{
		mType = cls();
	}

	LabelList::LabelList(StringVector labels)
		: List()
	{
		for(string& label : labels)
			this->makeappend<Label>(label);
	}
	
	ButtonList::ButtonList(StringVector labels)
		: List()
	{
		for(string& label : labels)
			this->makeappend<Button>(label);
	}

	SortList::SortList(Style* style)
		: List(style ? style : styleCls())
		, Dropper(this)
	{
		mType = cls();
	}

	/*void SortList::move(Form* form, size_t index)
	{
		if(form->index() == index) // @required because after droping in a specific spot, a move is issued, and if the item was dropped at the end the move will crash
			return;

		size_t from = form->index();
		mContents.move(form->index(), index);
		moved(from, index);

		//this->altered();
	}

	void SortList::transfer(Form* form, SortList* list, size_t index)
	{}*/
}
