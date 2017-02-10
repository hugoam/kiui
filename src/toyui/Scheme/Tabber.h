//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_WTABBER_H
#define TOY_WTABBER_H

/* toy */
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Button.h>

namespace toy
{
	class TOY_UI_EXPORT TabHeader : public Button
	{
	public:
		TabHeader(const string& label, const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("TabHeader", Button::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Tab : public Sheet
	{
	public:
		Tab(Button& header, bool active);

		unique_ptr<Widget> vrelease(Widget& widget);

		Button& header() { return m_header; }

		static StyleType& cls() { static StyleType ty("Tab", Sheet::cls()); return ty; }

	protected:
		Button& m_header;
		bool m_active;
	};

	class _I_ TOY_UI_EXPORT TabberHead : public Band
	{
	public:
		TabberHead();

		static StyleType& cls() { static StyleType ty("TabberHead", Band::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT TabberBody : public Sheet
	{
	public:
		TabberBody();

		static StyleType& cls() { static StyleType ty("TabberBody", Sheet::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Tabber : public Sheet
	{
	public:
		Tabber(StyleType& type = cls(), bool downtabs = false);
		~Tabber();

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void headerClicked(Button& button);

		void showTab(Tab& tab);
		void showTab(size_t index);

		static StyleType& cls() { static StyleType ty("Tabber", Sheet::cls()); return ty; }

	protected:
		TabberHead& m_headers;
		TabberBody& m_tabs;
		Tab* m_currentTab;
		bool m_downTabs;
	};
}

#endif
