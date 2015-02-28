//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABBER_H
#define MK_WTABBER_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT WTab : public Sheet
	{
	public:
		WTab(WButton* header, bool active);

		void build();

		WButton* header() { return mHeader; }

	protected:
		WButton* mHeader;
		bool mActive;
	};

	class MK_UI_EXPORT WTabber : public Sheet
	{
	public:
		WTabber(string cls, bool downtabs = false);
		~WTabber();

		void build();

		void select(size_t index);

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void headerClicked(WButton* button);

		void showTab(WTab* tab);
		void showTab(size_t index);

	protected:
		Sheet* mHeaders;
		Sheet* mTabs;
		WTab* mCurrentTab;
		bool mDownTabs;
	};

	class MK_UI_EXPORT Tabber : public Form
	{
	public:
		Tabber();
	};
}

#endif
