//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Filter.h>

#include <toyui/Widget/Layout.h>

#include <locale>

using namespace std::placeholders;

namespace toy
{
	FilterInput::FilterInput(Piece& parent, Piece& list, std::function<void(string)> callback)
		: Input<string>(parent, "", callback)
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
			if(std::tolower(filter[i], std::locale()) != std::tolower(value[i], std::locale()))
				return false;

		return true;
	}

	void FilterInput::notifyModify()
	{
		Input<string>::notifyModify();
		this->updateFilter(m_value->ref<string>());
	}
}
