//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkDockspace.h>

#include <Object/String/mkStringConvert.h>

#include <Ui/Form/mkWidgets.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Form/mkRootForm.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Scheme/mkWindow.h>

#include <Ui/Widget/mkRootSheet.h>

#include <iostream>

namespace mk
{
	Docksection::Docksection(Dockline& dockline, size_t index)
		: Tabber(true)
		, mDockline(&dockline)
		, mIndex(index)
	{
		mStyle = &cls();
		mType = &cls();
	}

	Docksection::~Docksection()
	{}

	void Docksection::dock(Window& window)
	{
		this->vappend(window.parent()->vrelease(window));
	}

	void Docksection::undock(Window& window)
	{
		this->rootSheet().append(Tabber::vrelease(window));

		if(mTabs.count() == 0)
			mDockline->removeSection(*this);
	}

	Widget& Docksection::vappend(unique_ptr<Widget> widget)
	{
		return Tabber::vappend(std::move(widget));
	}

	unique_ptr<Widget> Docksection::vrelease(Widget& widget)
	{
		unique_ptr<Widget> unique = Tabber::vrelease(widget);

		if(mTabs.count() == 0)
			mDockline->removeSection(*this);

		return unique;
	}

	Docksection& Docksection::docktarget(Dimension dim, bool after)
	{
		float span = mFrame->dsize(mDockline->dim()) / mDockline->frame().dsize(mDockline->dim());
		span = std::min(span, this->frame().dspan(mDockline->dim()) / 2.f);

		if(mDockline->dim() == dim)
		{
			mFrame->setSpanDim(mDockline->dim(), mFrame->dspan(mDockline->dim()) - span);
			return mDockline->insertSection(mFrame->index() + (after ? 1 : 0), span);
		}
		else
		{
			return mDockline->insertLine(mFrame->index(), true, span).insertSection(after ? 1 : 0);
		}
	}

	Docksection& Docksection::docktarget(float xPos, float yPos)
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
			return *this; // dock on
	}

	Dockline::Dockline(Dockspace& dockspace, Dockline* dockline, Dimension dim, size_t index)
		: GridSheet(dim)
		, mDockspace(dockspace)
		, mDockline(dockline)
		, mIndex(index)
	{
		mType = &cls();
	}

	Dockline::~Dockline()
	{}

	Dockline& Dockline::insertLine(size_t index, bool replace, float span)
	{
		Dockline& dockline = mDim == DIM_X ? (Dockline&) this->makeinsert<DocklineY>(index, mDockspace, this, index)
											: (Dockline&) this->makeinsert<DocklineX>(index, mDockspace, this, index);

		if(replace)
			dockline.frame().setSpanDim(mDim, this->stripe().contents()[index + 1]->dspan(mDim));
		else
			dockline.frame().setSpanDim(mDim, span);

		if(replace)
			dockline.append(this->release(index + 1));

		return dockline;
	}

	Docksection& Dockline::insertSection(size_t index, float span)
	{
		Docksection& docksection = this->makeinsert<Docksection>(index, *this, index);
		docksection.frame().setSpanDim(mDim, span);
		return docksection;
	}

	void Dockline::removeSection(Docksection& section)
	{
		Frame& givespan = section.frame().index() > 0 ? section.prev().frame() : section.next().frame();
		givespan.setSpanDim(mDim, givespan.dspan(mDim) + section.frame().dspan(mDim));

		section.destroy();

		if(mContents.size() == 1 && mDockline)
			mDockline->removeLine(*this);
	}

	void Dockline::removeLine(Dockline& line)
	{
		Widget& section = this->insert(line.release(size_t(0)), line.frame().index());
		section.as<Docksection>().setDockline(this);
		section.frame().setSpanDim(mDim, line.frame().dspan(mDim));

		line.destroy();

		if(mContents.size() == 1 && mDockline)
			mDockline->removeLine(*this);
	}

	Dockline& Dockline::findLine(std::vector<string>& ids)
	{
		Dockline* dockline = this;

		ids.pop_back(); // first is us
		while(ids.size() > 1)
		{
			size_t index = fromString<size_t>(ids.back());
			if(index < dockline->count())
				dockline = &dockline->at(index)->as<Dockline>();
			else
				dockline = &dockline->insertLine(index);
			ids.pop_back();
		}

		return *dockline;
	}

	Docksection& Dockline::findOrCreateSection(const string& dockid)
	{
		std::vector<string> ids = splitString(dockid, ".");
		std::reverse(ids.begin(), ids.end());

		Dockline& dockline = this->findLine(ids);

		size_t index = fromString<size_t>(ids.back());
		if(index < dockline.count())
			return dockline.at(index)->as<Docksection>();
		else
			return dockline.insertSection(index);
	}

	DocklineX::DocklineX(Dockspace& dockspace, Dockline* dockline, size_t index)
		: Dockline(dockspace, dockline, DIM_X, index)
	{
		mStyle = &cls();
	}

	DocklineY::DocklineY(Dockspace& dockspace, Dockline* dockline, size_t index)
		: Dockline(dockspace, dockline, DIM_Y, index)
	{
		mStyle = &cls();
	}

	MasterDockline::MasterDockline(Dockspace& dockspace)
		: DocklineX(dockspace, nullptr, 0)
	{
		mStyle = &cls();
	}

	Dockspace::Dockspace()
		: Sheet()
		, mMainLine(this->makeappend<MasterDockline>(*this))
	{
		mStyle = &cls();
	}

	Widget& Dockspace::vappend(unique_ptr<Widget> widget)
	{
		Docksection& section = mMainLine.findOrCreateSection(widget->dockid());
		Window& window = section.emplace<Window>(widget->name(), true, true, nullptr, &section);
		window.docked();
		return window.vappend(std::move(widget));
	}
}
