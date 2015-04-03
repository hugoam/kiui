//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkExpandbox.h>

#include <Ui/Widget/mkSheet.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

namespace mk
{
	ExpandboxHeader::ExpandboxHeader()
		: Sheet(styleCls())
	{}

	ExpandboxBody::ExpandboxBody()
		: Sheet(styleCls())
	{}

	ExpandboxToggle::ExpandboxToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: Toggle(styleCls(), triggerOn, triggerOff, on)
	{}

	Expandbox::Expandbox(const string& title, bool collapsed, bool build)
		: Sheet(styleCls())
		, mTitle(title)
		, mCollapsed(collapsed)
	{
		if(build)
		{
			mHeader = this->makeappend<ExpandboxHeader>();
			mContainer = this->makeappend<ExpandboxBody>();

			mExpandButton = mHeader->emplace<ExpandboxToggle>(std::bind(&Expandbox::expand, this), std::bind(&Expandbox::collapse, this), !mCollapsed);
			mTitleLabel = mHeader->emplace<Title>(mTitle);

			mContainer->hide();
		}
	}

	Expandbox::~Expandbox()
	{}

	Widget* Expandbox::vappend(unique_ptr<Widget> widget)
	{
		if(!mCollapsed && mContainer->frame()->hidden())
			mContainer->show();
		return mContainer->append(std::move(widget));
	}

	unique_ptr<Widget> Expandbox::vrelease(Widget* widget)
	{
		return mContainer->release(widget);
	}

	void Expandbox::expand()
	{
		mContainer->show();
		mCollapsed = false;
	}

	void Expandbox::collapse()
	{
		mContainer->hide();
		mCollapsed = true;
	}
}
