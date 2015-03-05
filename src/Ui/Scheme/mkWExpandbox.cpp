//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWExpandbox.h>

#include <Ui/Widget/mkSheet.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

namespace mk
{
	WExpandbox::WExpandbox(string title, bool collapsed)
		: Sheet("expandbox")
		, mTitle(title)
		, mCollapsed(collapsed)
	{}

	WExpandbox::~WExpandbox()
	{}

	void WExpandbox::build()
	{
		Sheet::build();
		mHeader = this->makeappend<Sheet>(mClas + "header");
		mExpandButton = mHeader->makeappend<WToggle>("expandbutton", std::bind(&WExpandbox::expand, this), std::bind(&WExpandbox::collapse, this), !mCollapsed);
		mTitleLabel = mHeader->makeappend<WLabel>(mTitle, "title");
		mContainer = this->makeappend<Sheet>(mClas + "container");

		mContainer->frame()->hide();
	}

	Widget* WExpandbox::vappend(unique_ptr<Widget> widget)
	{
		if(!mCollapsed && mContainer->frame()->hidden())
			mContainer->frame()->show();
		return mContainer->append(std::move(widget));
	}

	unique_ptr<Widget> WExpandbox::vrelease(Widget* widget)
	{
		return mContainer->release(widget);
	}

	void WExpandbox::expand()
	{
		mContainer->frame()->show();
		mCollapsed = false;
	}

	void WExpandbox::collapse()
	{
		mContainer->frame()->hide();
		mCollapsed = true;
	}

	Expandbox::Expandbox(string title, bool collapsed)
		: Form("expandbox", "", [this, collapsed]() { return make_unique<WExpandbox>(this->name(), collapsed); })
	{
		if(title != "")
			this->setName(title);
	}
}
