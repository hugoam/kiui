//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_FILTER_H
#define TOY_FILTER_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Edit/TypeIn.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT FilterInput : public TypeIn
	{
	public:
		using Criteria = std::function<string(Widget&)>;

	public:
		FilterInput(const Params& params, Wedge& list, Criteria criteria = nullptr);

		void updateFilter(const string& filter);
		bool fitsFilter(const string& filter, const string& value);

	protected:
		string m_filter;
		Wedge& m_list;
		Criteria m_criteria;
	};
}

#endif // TOY_WIDGET_H
