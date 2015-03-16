//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WTABBER_H
#define MK_WTABBER_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT WTabHeader : public WButton, public Styled<WTabHeader>
	{
	public:
		WTabHeader(const string& label, const Trigger& trigger);

		using Styled<WTabHeader>::styleCls;
	};

	class MK_UI_EXPORT _I_ WTab : public Sheet, public Typed<WTab>, public Styled<WTab>
	{
	public:
		WTab(WButton* header, bool active);

		void build();

		WButton* header() { return mHeader; }

		using Typed<WTab>::cls;

	protected:
		WButton* mHeader;
		bool mActive;
	};

	class MK_UI_EXPORT _I_ WTabberHead : public Sheet, public Typed<WTabberHead>, public Styled<WTabberHead>
	{
	public:
		WTabberHead();

		using Typed<WTabberHead>::cls;
	};

	class MK_UI_EXPORT _I_ WTabberBody : public Sheet, public Typed<WTabberBody>, public Styled<WTabberBody>
	{
	public:
		WTabberBody();

		using Typed<WTabberBody>::cls;
	};

	class MK_UI_EXPORT WTabber : public Sheet, public Styled<WTabber>
	{
	public:
		WTabber(Style* style = nullptr, bool downtabs = false);
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
