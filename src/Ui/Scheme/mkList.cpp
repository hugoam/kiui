//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkList.h>

#include <Ui/Form/mkWidgets.h>

#include <iostream>

using namespace std::placeholders;

namespace mk
{
	List::List(FrameType frameType)
		: ScrollSheet(frameType)
	{
		mStyle = &cls();
	}

	SelectList::SelectList()
		: List()
	{
		mStyle = &cls();
	}

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
		, mList(list)
	{}

	void FilterInput::filterOn()
	{
		this->updateFilter(mValue->ref<string>());
	}

	void FilterInput::filterOff()
	{
		this->updateFilter("");
	}

	void FilterInput::updateFilter(const string& filter)
	{
		for(auto& pt : mList.contents())
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
		this->updateFilter(mValue->ref<string>());
	}

	Sequence::Sequence()
		: Sheet()
	{
		mStyle = &cls();
	}

	LabelSequence::LabelSequence(StringVector labels)
		: Sequence()
	{
		for(string& label : labels)
			this->emplace<Label>(label);
	}
	
	ButtonSequence::ButtonSequence(StringVector labels)
		: Sequence()
	{
		for(string& label : labels)
			this->emplace<Button>(label);
	}

	SortList::SortList()
		: List()
	{
		mStyle = &cls();
		mType = &cls();
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
