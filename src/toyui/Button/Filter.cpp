//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Button/Filter.h>

#include <locale>

namespace toy
{
	FilterInput::FilterInput(const Params& params, Wedge& list, Criteria criteria)
		: TypeIn({ params, &cls<FilterInput>() }, "", [this](const string& value) { this->updateFilter(value); return value; })
		, m_list(list)
		, m_criteria(criteria ? criteria : [](Widget& widget) { return widget.label(); })
	{}

	void FilterInput::updateFilter(const string& filter)
	{
		for(auto& widget : m_list.m_contents)
		{
			string text = m_criteria(*widget);
			bool fit = fitsFilter(filter, text);
			fit ? widget->show() : widget->hide();
		}
	}

	bool FilterInput::fitsFilter(const string& filter, const string& value)
	{
		for(size_t i = 0; i < filter.size(); ++i)
			if(std::tolower(filter[i], std::locale()) != std::tolower(value[i], std::locale()))
				return false;

		return true;
	}
}
