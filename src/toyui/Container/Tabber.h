//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TABBER_H
#define TOY_TABBER_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Container/ScrollSheet.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Tab : public Wedge
	{
	public:
		Tab(const Params& params, Tabber& tabber, Button& header, bool active);

		virtual void extract() override;

	public:
		Tabber& m_tabber;
		Button& m_header;
		bool m_active;
	};

	class _refl_ TOY_UI_EXPORT Tabber : public Wedge
	{
	public:
		Tabber(const Params& params, bool downtabs = false);

		Tab& addTab(const string& name);
		void removeTab(Tab& tab);

		void headerClicked(Widget& button);

		void showTab(Tab& tab);
		void showTab(size_t index);

		struct Styles
		{
			Style tab = { cls<Tab>(), Widget::styles().wedge, Args{ { &Layout::m_clipping, CLIP } } };
			Style tab_button = { "TabHeader", Widget::styles().button };
			Style tabber = { cls<Tabber>(), Widget::styles().wedge };
			Style head = { "TabberHead", Widget::styles().row };
			Style body = { "TabberBody", Widget::styles().sheet };
		};
		static Styles& styles() { static Styles styles; return styles; }

	public:
		Wedge m_headers;
		Wedge m_tabs;
		Tab* m_currentTab;
		bool m_downTabs;
		bool m_hideSingleHeader;
	};
}

#endif
