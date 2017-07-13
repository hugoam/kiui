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
		Tab(Wedge& parent, Tabber& tabber, Button& header, bool active);

		virtual void destroyz() override;

		static Type& cls() { static Type ty("Tab", Wedge::cls()); return ty; }

	public:
		Tabber& m_tabber;
		Button& m_header;
		bool m_active;
	};

	class _refl_ TOY_UI_EXPORT Tabber : public Wedge
	{
	public:
		Tabber(Wedge& parent, Type& type = cls(), bool downtabs = false);

		Tab& addTab(const string& name);
		void removeTab(Tab& tab);

		void headerClicked(Widget& button);

		void showTab(Tab& tab);
		void showTab(size_t index);

		static Type& cls() { static Type ty("Tabber", Wedge::cls()); return ty; }

		static Type& Head() { static Type ty("TabberHead", Wedge::Row()); return ty; }
		static Type& Body() { static Type ty("TabberBody", Wedge::Sheet()); return ty; }
		static Type& Header() { static Type ty("TabButton", Button::cls()); return ty; }

	public:
		Wedge m_headers;
		Wedge m_tabs;
		Tab* m_currentTab;
		bool m_downTabs;
	};
}

#endif
