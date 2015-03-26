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

#include <Ui/Widget/mkRootSheet.h>

#include <iostream>

namespace mk
{
	WDocksection::WDocksection(WDockline* dockline, size_t index, Style* style)
		: WTabber(style ? style : styleCls(), true)
		, mDockline(dockline)
		, mIndex(index)
	{
		mType = cls();
	}

	WDocksection::~WDocksection()
	{}

	void WDocksection::build()
	{
		WTabber::build();
	}

	void WDocksection::dock(WWindow* window)
	{
		this->vappend(window->parent()->vrelease(window));
	}

	void WDocksection::undock(WWindow* window)
	{
		this->rootSheet()->append(WTabber::vrelease(window));

		if(mTabs->count() == 0)
			mDockline->removeSection(this);
	}

	unique_ptr<Widget> WDocksection::vrelease(Widget* widget)
	{
		unique_ptr<Widget> unique = WTabber::vrelease(widget);

		if(mTabs->count() == 0)
			mDockline->removeSection(this);

		return unique;
	}

	WDocksection* WDocksection::docktarget(Dimension dim, bool after)
	{
		float span = mFrame->dsize(mDockline->dim()) / mDockline->frame()->dsize(mDockline->dim());
		span = std::min(span, this->frame()->dspan(mDockline->dim()) / 2.f);

		if(mDockline->dim() == dim)
		{
			mFrame->setSpanDim(mDockline->dim(), mFrame->dspan(mDockline->dim()) - span);
			return mDockline->insertSection(mFrame->index() + (after ? 1 : 0), nullptr, span);
		}
		else
		{
			return mDockline->insertLine(mFrame->index(), true, span)->insertSection(after ? 1 : 0);
		}
	}

	WDocksection* WDocksection::docktarget(float xPos, float yPos)
	{
		float xRel = xPos - mFrame->dabsolute(DIM_X);
		float yRel = yPos - mFrame->dabsolute(DIM_Y);

		if(xRel < mFrame->dsize(DIM_X) * 0.25f)
			return this->docktarget(DIM_X, false); // dock left
		else if(xRel > mFrame->dsize(DIM_X) * 0.75f)
			return this->docktarget(DIM_X, true); // dock right
		else if(yRel < mFrame->dsize(DIM_Y) * 0.25f)
			return this->docktarget(DIM_Y, false); // dock under
		else if(yRel > mFrame->dsize(DIM_Y) * 0.75f)
			return this->docktarget(DIM_Y, true); // dock above
		else
			return this; // dock on
	}

	WDockline::WDockline(WDockspace* dockspace, WDockline* dockline, Dimension dim, size_t index, Style* style)
		: GridSheet(dim, style)
		, mDockspace(dockspace)
		, mDockline(dockline)
		, mIndex(index)
	{
		mType = cls();
	}

	WDockline::~WDockline()
	{}

	void WDockline::build()
	{
		GridSheet::build();
	}

	WDockline* WDockline::insertLine(size_t index, bool replace, float span)
	{
		WDockline* dockline;

		if(mDim == DIM_X)
			dockline = this->makeinsert<WDocklineY>(index, mDockspace, this, index);
		else
			dockline = this->makeinsert<WDocklineX>(index, mDockspace, this, index);

		if(replace)
			dockline->frame()->setSpanDim(mDim, this->stripe()->contents()[index + 1]->dspan(mDim));
		else
			dockline->frame()->setSpanDim(mDim, span);

		if(replace)
			dockline->append(this->release(index + 1));

		return dockline;
	}

	WDocksection* WDockline::insertSection(size_t index, Style* style, float span)
	{
		WDocksection* docksection = this->makeinsert<WDocksection>(index, this, index, style);
		docksection->frame()->setSpanDim(mDim, span);
		return docksection;
	}

	void WDockline::removeSection(WDocksection* section)
	{
		Frame* givespan = section->frame()->index() > 0 ? section->prev()->frame() : section->next()->frame();
		givespan->setSpanDim(mDim, givespan->dspan(mDim) + section->frame()->dspan(mDim));

		section->destroy();

		if(mContents.size() == 1 && mDockline)
			mDockline->removeLine(this);
	}

	void WDockline::removeLine(WDockline* line)
	{
		Widget* section = this->insert(line->release(0U), line->frame()->index());
		section->as<WDocksection>()->setDockline(this);
		section->frame()->setSpanDim(mDim, line->frame()->dspan(mDim));

		line->destroy();

		if(mContents.size() == 1 && mDockline)
			mDockline->removeLine(this);
	}

	WDockline* WDockline::findLine(std::vector<string>& ids)
	{
		WDockline* dockline = this;

		ids.pop_back(); // first is us
		while(ids.size() > 1)
		{
			size_t index = fromString<size_t>(ids.back());
			if(index < dockline->count())
				dockline = dockline->at(index)->as<WDockline>();
			else
				dockline = dockline->insertLine(index);
			ids.pop_back();
		}

		return dockline;
	}

	WDocksection* WDockline::findOrCreateSection(const string& dockid, Style* style)
	{
		std::vector<string> ids = splitString(dockid, ".");
		std::reverse(ids.begin(), ids.end());

		WDockline* dockline = this->findLine(ids);

		size_t index = fromString<size_t>(ids.back());
		if(index < dockline->count())
			return dockline->at(index)->as<WDocksection>();
		else
			return dockline->insertSection(index, style);
	}

	WDocksection* WDockline::findSection(const string& dockid)
	{
		return findOrCreateSection(dockid);
	}

	WDocklineX::WDocklineX(WDockspace* dockspace, WDockline* dockline, size_t index)
		: WDockline(dockspace, dockline, DIM_X, index, styleCls())
	{}

	WDocklineY::WDocklineY(WDockspace* dockspace, WDockline* dockline, size_t index)
		: WDockline(dockspace, dockline, DIM_Y, index, styleCls())
	{}

	WMasterDockline::WMasterDockline(WDockspace* dockspace)
		: WDockline(dockspace, nullptr, DIM_X, 0, styleCls())
	{}

	WDockspace::WDockspace()
		: Sheet(styleCls())
	{}

	void WDockspace::build()
	{
		Sheet::build();
		mMainLine = this->makeappend<WMasterDockline>(this);
	}

	Widget* WDockspace::vappend(unique_ptr<Widget> widget)
	{
		string dockid = widget->form()->attrs()["dockid"]->get<string>();
		WDocksection* section = mMainLine->findOrCreateSection(dockid);
		WWindow* window = section->vmakeappend<WWindow>(nullptr, widget->name(), true, true, section);
		return window->vappend(std::move(widget));
	}

	Dockspace::Dockspace(Style* style)
		: Form(style, "", []() { return make_unique<WDockspace>(); })
	{
		mType = cls();
	}
}
