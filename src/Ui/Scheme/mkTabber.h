//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABBER_H
#define MK_WTABBER_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT TabHeader : public Button, public Styled<TabHeader>
	{
	public:
		TabHeader(const string& label, const Trigger& trigger);

		using Styled<TabHeader>::styleCls;
	};

	class MK_UI_EXPORT _I_ Tab : public Sheet, public Typed<Tab>, public Styled<Tab>
	{
	public:
		Tab(Button* header, bool active);

		unique_ptr<Widget> vrelease(Widget* widget);

		Button* header() { return mHeader; }

		using Typed<Tab>::cls;

	protected:
		Button* mHeader;
		bool mActive;
	};

	class MK_UI_EXPORT _I_ TabberHead : public Sheet, public Typed<TabberHead>, public Styled<TabberHead>
	{
	public:
		TabberHead();

		using Typed<TabberHead>::cls;
	};

	class MK_UI_EXPORT _I_ TabberBody : public Sheet, public Typed<TabberBody>, public Styled<TabberBody>
	{
	public:
		TabberBody();

		using Typed<TabberBody>::cls;
	};

	class MK_UI_EXPORT Tabber : public Sheet, public Styled<Tabber>
	{
	public:
		Tabber(Style* style = nullptr, bool downtabs = false);
		~Tabber();

		void select(size_t index);

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void headerClicked(Button* button);

		void showTab(Tab* tab);
		void showTab(size_t index);

	protected:
		Sheet* mHeaders;
		Sheet* mTabs;
		Tab* mCurrentTab;
		bool mDownTabs;
	};
}

#endif
