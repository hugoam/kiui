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
	WExpandboxHeader::WExpandboxHeader()
		: Sheet(styleCls())
	{}

	WExpandboxBody::WExpandboxBody()
		: Sheet(styleCls())
	{}

	WExpandboxToggle::WExpandboxToggle(const Trigger& triggerOn, const Trigger& triggerOff, bool on)
		: WToggle(styleCls(), triggerOn, triggerOff, on)
	{}

	WExpandbox::WExpandbox(Form* form, const string& title, bool collapsed)
		: Sheet(styleCls(), form)
		, mTitle(title)
		, mCollapsed(collapsed)
	{}

	WExpandbox::~WExpandbox()
	{}

	void WExpandbox::build()
	{
		Sheet::build();
		mHeader = this->makeappend<WExpandboxHeader>();
		mContainer = this->makeappend<WExpandboxBody>();

		mExpandButton = mHeader->makeappend<WExpandboxToggle>(std::bind(&WExpandbox::expand, this), std::bind(&WExpandbox::collapse, this), !mCollapsed);
		mTitleLabel = mHeader->makeappend<WTitle>(mTitle);

		mContainer->hide();
	}

	Widget* WExpandbox::vappend(unique_ptr<Widget> widget)
	{
		if(!mCollapsed && mContainer->frame()->hidden())
			mContainer->show();
		return mContainer->append(std::move(widget));
	}

	unique_ptr<Widget> WExpandbox::vrelease(Widget* widget)
	{
		return mContainer->release(widget);
	}

	void WExpandbox::expand()
	{
		mContainer->show();
		mCollapsed = false;
	}

	void WExpandbox::collapse()
	{
		mContainer->hide();
		mCollapsed = true;
	}

	Expandbox::Expandbox(const string& title, bool collapsed)
		: Form(nullptr, title, [this, collapsed]() { return make_unique<WExpandbox>(this, this->label(), collapsed); })
		//: Form("expandbox", "", [this, collapsed]() { return make_unique<WExpandbox>(this->name(), collapsed); })
		//: Form("expandbox", "", [title, collapsed]() { return make_unique<WExpandbox>(title, collapsed); })
	{
		//if(!title.empty())
			//this->setName(title);
	}
}
