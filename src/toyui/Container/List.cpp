//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/List.h>

namespace toy
{
	SelectList::SelectList(Wedge& parent, Type& type)
		: ScrollSheet(parent, type)
	{}

	WrapButton& SelectList::addChoice()
	{
		return this->emplace<WrapButton>([this](Widget& button) { return this->selected(button); });
	}

	void SelectList::selected(Widget& selected)
	{
		selected.toggleState(SELECTED);
	}

	LabelSequence::LabelSequence(Wedge& parent, StringVector labels)
		: Wedge(parent, cls())
	{
		for(string& label : labels)
			this->emplace<Label>(label);
	}
	
	ButtonSequence::ButtonSequence(Wedge& parent, StringVector labels)
		: Wedge(parent, cls())
	{
		for(string& label : labels)
			this->emplace<Button>(label);
	}

	SortList::SortList(Wedge& parent)
		: ScrollSheet(parent, cls())
	{}

	/*void SortList::move(Device* form, size_t index)
	{
		if(form->index() == index) // @required because after droping in a specific spot, a move is issued, and if the item was dropped at the end the move will crash
			return;

		size_t from = form->index();
		m_contents.move(form->index(), index);
		moved(from, index);

		//this->altered();
	}

	void SortList::transfer(Device* form, SortList* list, size_t index)
	{}*/
}
