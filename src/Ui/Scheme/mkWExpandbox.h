//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WEXPANDBOX_H
#define MK_WEXPANDBOX_H

/* mk */
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT WExpandbox : public Sheet
	{
	public:
		WExpandbox(string title, bool collapsed = false);
		~WExpandbox();

		void build();

		Sheet* header() { return mHeader; }

		Widget* vappend(std::unique_ptr<Widget> widget);
		std::unique_ptr<Widget> vrelease(Widget* widget);

		void expand();
		void collapse();

	protected:
		string mTitle;
		Sheet* mHeader;
		Sheet* mContainer;
		WToggle* mExpandButton;
		WLabel* mTitleLabel;
		bool mCollapsed;
	};

	class MK_UI_EXPORT Expandbox : public Form
	{
	public:
		Expandbox(string title = "", bool collapsed = false);
	};

}

#endif
