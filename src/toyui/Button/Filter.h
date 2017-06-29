//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_FILTER_H
#define TOY_FILTER_H

/* toy */
#include <toyobj/Type.h>
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Edit/Input.h>

namespace toy
{
	class TOY_UI_EXPORT FilterInput : public Input<string>
	{
	public:
		using Criteria = std::function<string(Widget&)>;

	public:
		FilterInput(Wedge& parent, Wedge& list, Criteria criteria = nullptr, Callback callback = nullptr);

		void filterOn();
		void filterOff();

		void notifyModify();

		void updateFilter(const string& filter);
		bool fitsFilter(const string& filter, const string& value);

		static Type& cls() { static Type ty("FilterInput", Input<string>::cls()); return ty; }


	protected:
		Wedge& m_list;
		Criteria m_criteria;
	};
}

#endif // TOY_WIDGET_H
