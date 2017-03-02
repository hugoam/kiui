//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Container/List.h>

#include <toyui/Widget/Layout.h>

#include <locale>

using namespace std::placeholders;

namespace toy
{
	List::List(Piece& parent, Type& type, FrameType frameType)
		: ScrollContainer(parent, type)
	{}

	SelectList::SelectList(Piece& parent, Type& type)
		: List(parent, type)
	{}

	WrapButton& SelectList::addChoice()
	{
		return this->emplaceLocal<WrapButton>(m_scrollzone.container(), [this](Widget& button) { return this->selected(button); });
	}

	Container& SelectList::emplaceContainer()
	{
		return this->addChoice();
	}

	void SelectList::selected(Widget& selected)
	{
		selected.toggleState(ACTIVATED);
	}

	LabelSequence::LabelSequence(Piece& parent, StringVector labels)
		: Line(parent)
	{
		for(string& label : labels)
			this->emplace<Label>(label);
	}
	
	ButtonSequence::ButtonSequence(Piece& parent, StringVector labels)
		: Line(parent)
	{
		for(string& label : labels)
			this->emplace<Button>(label);
	}

	SortList::SortList(Piece& parent)
		: List(parent, cls())
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
