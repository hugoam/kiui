//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkTabber.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkWidgets.h>

#include <Ui/Frame/mkFrame.h>

using namespace std::placeholders;

namespace mk
{
	TabHeader::TabHeader(const string& label, const Trigger& trigger)
		: Button(label, styleCls(), trigger)
	{}

	Tab::Tab(Button* header, bool active)
		: Sheet(styleCls())
		, mHeader(header)
		, mActive(active)
	{
		if(!mActive)
			this->hide();
		else
			mHeader->activate();
	}

	unique_ptr<Widget> Tab::vrelease(Widget* widget)
	{
		return mParent->parent()->vrelease(widget);
	}

	TabberHead::TabberHead()
		: Sheet(styleCls())
	{}

	TabberBody::TabberBody()
		: Sheet(styleCls())
	{}

	Tabber::Tabber(Style* style, bool downtabs)
		: Sheet(style ? style : styleCls())
		, mCurrentTab(nullptr)
		, mDownTabs(downtabs)
	{
		mHeaders = this->makeappend<TabberHead>();
		mTabs = this->makeappend<TabberBody>();

		//if(mDownTabs)
		//	mFrame->as<Stripe>()->move(0, 1);
		mHeaders->hide();
	}

	Tabber::~Tabber()
	{}

	Widget* Tabber::vappend(unique_ptr<Widget> widget)
	{
		Button* header = mHeaders->emplace<TabHeader>(widget->name(), std::bind(&Tabber::headerClicked, this, _1));
		Tab* tab = mTabs->emplace<Tab>(header, mCurrentTab == nullptr);

		if(!mCurrentTab)
			mCurrentTab = tab;
		else if(mTabs->count() == 2)
			mHeaders->show();

		return tab->append(std::move(widget));
	}

	unique_ptr<Widget> Tabber::vrelease(Widget* widget)
	{
		Tab* tab = widget->parent()->as<Tab>();

		if(tab == mCurrentTab)
			mCurrentTab = nullptr;

		unique_ptr<Widget> unique = widget->unbind();
		tab->header()->destroy();
		tab->destroy();

		if(mTabs->count() > 0)
			this->showTab(size_t(0));
		if(mTabs->count() == 1)
			mHeaders->hide();

		return unique;
	}

	void Tabber::headerClicked(Button* header)
	{
		this->showTab(header->frame()->index());
	}

	void Tabber::showTab(Tab* tab)
	{
		if(mCurrentTab)
		{
			mCurrentTab->hide();
			mCurrentTab->header()->deactivate();
		}
		tab->show();
		tab->header()->activate();
		mCurrentTab = tab;
	}

	void Tabber::showTab(size_t index)
	{
		this->showTab(mTabs->at(index)->as<Tab>());
	}
}
