//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABBER_H
#define MK_WTABBER_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>

namespace mk
{
	class MK_UI_EXPORT TabHeader : public Button
	{
	public:
		TabHeader(const string& label, const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("TabHeader", Button::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Tab : public Sheet
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

	class MK_UI_EXPORT _I_ TabberHead : public Band
	{
	public:
		TabberHead();

		static StyleType& cls() { static StyleType ty("TabberHead", Band::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ TabberBody : public Sheet
	{
	public:
		TabberBody();

		static StyleType& cls() { static StyleType ty("TabberBody", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT Tabber : public Sheet
	{
	public:
		Tabber(StyleType& type = cls(), bool downtabs = false);
		~Tabber();

		void select(size_t index);

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
