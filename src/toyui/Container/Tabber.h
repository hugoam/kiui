//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_TABBER_H
#define TOY_TABBER_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/ScrollSheet.h>
#include <toyui/Button/Button.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT TabHeader : public Button
	{
	public:
		TabHeader(Wedge& parent, const string& label, const Trigger& trigger);

		static Type& cls() { static Type ty("TabHeader", Button::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Tab : public ScrollSheet
	{
	public:
		Tab(Wedge& parent, Tabber& tabber, Button& header, bool active);

		void handleRemove(Widget& widget);

		Button& header() { return m_header; }

		static Type& cls() { static Type ty("Tab", ScrollSheet::cls()); return ty; }

	protected:
		Tabber& m_tabber;
		Button& m_header;
		bool m_active;
	};

	class _I_ TOY_UI_EXPORT TabberHead : public Line
	{
	public:
		TabberHead(Wedge& parent);

		static Type& cls() { static Type ty("TabberHead", Line::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT TabberBody : public Sheet
	{
	public:
		TabberBody(Wedge& parent);

		static Type& cls() { static Type ty("TabberBody", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Tabber : public Container
	{
	public:
		Tabber(Wedge& parent, Type& type = cls(), bool downtabs = false);
		~Tabber();

		Tab& addTab(const string& name);
		void removeTab(Tab& tab);

		virtual Container& emplaceContainer();

		void headerClicked(Widget& button);

		void showTab(Tab& tab);
		void showTab(size_t index);

		static Type& cls() { static Type ty("Tabber", Container::cls()); return ty; }

	protected:
		TabberHead m_headers;
		TabberBody m_tabs;
		Tab* m_currentTab;
		bool m_downTabs;
	};
}

#endif
