//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkList.h>

#include <Ui/Widget/mkWidgets.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	List::List(StyleType& type, FrameType frameType)
		: ScrollSheet(type, frameType)
	{}

	SelectList::SelectList(StyleType& type)
		: List(type)
	{}

	Widget& SelectList::vappend(std::unique_ptr<Widget> widget)
	{
		return this->makeappend<WrapButton>(std::move(widget), std::bind(&SelectList::selected, this, _1));
	}

	unique_ptr<Widget> SelectList::vrelease(Widget& widget)
	{
		return widget.extract();
	}

	void SelectList::selected(WrapButton& selected)
	{
		selected.toggleState(ACTIVATED);
	}

	FilterInput::FilterInput(Sheet& list, std::function<void(string)> callback)
		: Input<string>("", callback)
		, m_list(list)
	{}

	void FilterInput::filterOn()
	{
		this->updateFilter(m_value->ref<string>());
	}

	void FilterInput::filterOff()
	{
		this->updateFilter("");
	}

	void FilterInput::updateFilter(const string& filter)
	{
		for(auto& pt : m_list.contents())
		{
			bool fit = fitsFilter(filter, pt->contentlabel());
			if(fit && pt->frame().hidden())
				pt->show();
			else if(!fit && !pt->frame().hidden())
				pt->hide();
		}
	}

	bool FilterInput::fitsFilter(const string& filter, const string& value)
	{
		for(size_t i = 0; i < filter.size(); ++i)
			if(filter[i] != value[i])
				return false;

		return true;
	}

	void FilterInput::notifyModify()
	{
		Input<string>::notifyModify();
		this->updateFilter(m_value->ref<string>());
	}

	Band::Band(StyleType& type)
		: Sheet(type)
	{}

	LabelSequence::LabelSequence(StringVector labels)
		: Band()
	{
		for(string& label : labels)
			this->emplace<Label>(label);
	}
	
	ButtonSequence::ButtonSequence(StringVector labels)
		: Band()
	{
		for(string& label : labels)
			this->emplace<Button>(label);
	}

	SortList::SortList()
		: List(cls())
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
