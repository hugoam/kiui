//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WEXPANDBOX_H
#define MK_WEXPANDBOX_H

/* mk */
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT ExpandboxHeader : public Sheet, public Styled<ExpandboxHeader>
	{
	public:
		ExpandboxHeader();
	};

	class MK_UI_EXPORT ExpandboxBody : public Sheet, public Styled<ExpandboxBody>
	{
	public:
		ExpandboxBody();
	};

	class MK_UI_EXPORT ExpandboxToggle : public Toggle, public Styled<ExpandboxToggle>
	{
	public:
		ExpandboxToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on);
	};

	class MK_UI_EXPORT Expandbox : public Sheet, public Styled<Expandbox>
	{
	public:
		Expandbox(const string& title, bool collapsed = false, bool build = true);
		~Expandbox();

		Sheet* header() { return mHeader; }

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void expand();
		void collapse();

	protected:
		string mTitle;
		Sheet* mHeader;
		Sheet* mContainer;
		Toggle* mExpandButton;
		Label* mTitleLabel;
		bool mCollapsed;
	};
}

#endif
