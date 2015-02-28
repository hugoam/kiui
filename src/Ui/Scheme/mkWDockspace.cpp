//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkWDockspace.h>

#include <Object/String/mkStringConvert.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkRootForm.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkGrid.h>

#include <Ui/Scheme/mkWWindow.h>

#include <Ui/mkUiWindow.h>

#include <iostream>

namespace mk
{
	WDocksection::WDocksection(WDockline* dockline, size_t index, string clas)
		: WTabber(clas + " docksection", true)
		, mDockline(dockline)
		, mIndex(index)
	{
		mType = cls();

	}

	WDocksection::~WDocksection()
	{
		mDockline->dockspace()->setSpan(this->dockid(), mFrame->dspan(mDockline->dim()));
	}

	void WDocksection::build()
	{
		WTabber::build();

		mFrame->parent()->move(mFrame->index(), mIndex);
		mDockline->dockspace()->addSpan(this->dockid());
		this->updateSpan();
	}

	void WDocksection::updateSpan()
	{
		float span = mDockline->dockspace()->getSpan(this->dockid());
		mFrame->setSpanDim(mDockline->dim(), span);
		std::cerr << "Update dock " << this->dockid() << " span " << span << std::endl;
	}

	string WDocksection::dockid()
	{
		if(mDockline)
			return mDockline->dockid() + "." + toString(mFrame->index());
		else
			return toString(mFrame->index());
	}

	void WDocksection::dock(WWindow* window)
	{
		this->vappend(window->parent()->vrelease(window));
	}

	void WDocksection::undock(WWindow* window)
	{
		this->rootWidget()->append(this->vrelease(window));

		if(mTabs->contents()->size() == 0)
			mDockline->removeSection(this);
	}


	WDocksection* WDocksection::docktarget(Dimension dim, size_t index, bool after)
	{
		WDockline* dockline = mDockline;
		if(dockline->dim() == dim)
			return dockline->insertSection(index + (after ? 1 : 0));
		else
			return dockline->insertLine(index, true)->insertSection(after ? 1 : 0);
	}

	WDocksection* WDocksection::docktarget(float xPos, float yPos)
	{
		float xRel = xPos - mFrame->dabsolute(DIM_X);
		float yRel = yPos - mFrame->dabsolute(DIM_Y);

		if(xRel < mFrame->dsize(DIM_X) * 0.25f)
			return this->docktarget(DIM_X, mFrame->index(), false); // dock left
		else if(xRel > mFrame->dsize(DIM_X) * 0.75f)
			return this->docktarget(DIM_X, mFrame->index(), true); // dock right
		else if(yRel < mFrame->dsize(DIM_Y) * 0.25f)
			return this->docktarget(DIM_Y, mFrame->index(), false); // dock under
		else if(yRel > mFrame->dsize(DIM_Y) * 0.75f)
			return this->docktarget(DIM_Y, mFrame->index(), true); // dock above
		else
			return this; // dock on
	}

	WDockline::WDockline(WDockspace* dockspace, WDockline* dockline, Dimension dim, size_t index)
		: GridSheet(dim, dim == DIM_X ? "xdockline" : "ydockline")
		, mDockline(dockline)
		, mDockspace(dockspace)
		, mIndex(index)
	{
		mType = cls();
	}

	WDockline::~WDockline()
	{
		if(mDockline)
			mDockspace->setSpan(mDockline->dockid(), mFrame->dspan(mDockline->dim()));
	}

	void WDockline::build()
	{
		GridSheet::build();
		mFrame->parent()->move(mFrame->index(), mIndex);
		mDockspace->addSpan(this->dockid());
		this->updateSpan();
	}

	string WDockline::dockid()
	{
		if(mDockline)
			return mDockline->dockid() + "." + toString(mFrame->index());
		else
			return toString(mFrame->index());
	}

	void WDockline::updateSpan()
	{
		if(mDockline)
		{
			float span = mDockspace->getSpan(this->dockid());
			mFrame->setSpanDim(mDockline->dim(), span);
			std::cerr << "Update dock line " << this->dockid() << " span " << span << std::endl;
		}
	}

	WDockline* WDockline::insertLine(size_t index, bool replace)
	{
		WDockline* dockline = this->makeinsert<WDockline>(index, mDockspace, this, mDim == DIM_X ? DIM_Y : DIM_X, index);

		if(replace)
		{
			dockline->contents()->add(this->release(index + 1));
			dockline->contents()->at(dockline->contents()->size()-1)->rebind(dockline);
		}
		return dockline;
	}

	WDocksection* WDockline::insertSection(size_t index, string clas)
	{
		WDocksection* docksection = this->makeinsert<WDocksection>(index, this, index, clas);
		return docksection;
	}

	void WDockline::removeSection(WDocksection* section)
	{
		section->destroy();
		if(mContents.size() == 1)
			mParent->as<WDockline>()->removeLine(this);
	}

	void WDockline::removeLine(WDockline* line)
	{
		size_t index = line->frame()->index();
		
		WDocksection* section = line->contents()->at(0)->as<WDocksection>();
		section->as<WDocksection>()->setDockline(this);
		section->rebind(this, true, index);
		mContents.insert(line->contents()->release(size_t(0)), index);

		line->destroy();

		section->updateSpan();

		if(mContents.size() == 1)
			mParent->as<WDockline>()->removeLine(this);
	}

	WDockline* WDockline::findLine(std::vector<string>& ids)
	{
		WDockline* dockline = this;

		ids.pop_back(); // first is us
		while(ids.size() > 1)
		{
			size_t index = fromString<size_t>(ids.back());
			if(index < dockline->contents()->size())
				dockline = dockline->contents()->at(index)->as<WDockline>();
			else
				dockline = dockline->insertLine(index);
			ids.pop_back();
		}

		return dockline;
	}

	WDocksection* WDockline::findOrCreateSection(string dockid, string clas)
	{
		std::vector<string> ids = splitString(dockid, ".");
		std::reverse(ids.begin(), ids.end());

		WDockline* dockline = this->findLine(ids);

		size_t index = fromString<size_t>(ids.back());
		if(index < dockline->contents()->size())
			return dockline->contents()->at(index)->as<WDocksection>();
		else
			return dockline->insertSection(index, clas);
	}

	WDocksection* WDockline::findSection(string dockid)
	{
		return findOrCreateSection(dockid);
	}

	WDockspace::WDockspace()
		: Sheet("dockspace")
		, mDockSpans()
	{}

	void WDockspace::build()
	{
		Sheet::build();
		mMainLine = this->makeappend<WDockline>(this, nullptr, DIM_X, 0);
	}

	float WDockspace::getSpan(string dockid)
	{
		return mDockSpans[dockid];
	}

	void WDockspace::setSpan(string dockid, float span)
	{
		std::cerr << "Saving span for dock " << dockid << " value " << span << std::endl;
		mDockSpans[dockid] = span;
	}

	void WDockspace::addSpan(string dockid)
	{
		if(mDockSpans.find(dockid) == mDockSpans.end())
			mDockSpans[dockid] = 1.f;
	}

	Widget* WDockspace::vappend(unique_ptr<Widget> widget)
	{
		string dockid = widget->form()->attrs()["dockid"];
		WDocksection* section = mMainLine->findOrCreateSection(dockid);
		WWindow* window = section->vmakeappend<WWindow>(nullptr, widget->name(), true, true, section, widget->clas());
		return window->vappend(std::move(widget));
	}

	Dockspace::Dockspace(const string& cls)
		: Form(cls + " dockspace", "", []() { return make_unique<WDockspace>(); })
	{}
}
