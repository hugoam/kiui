//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkDockspace.h>

#include <Object/String/mkStringConvert.h>

#include <Ui/Widget/mkWidgets.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Scheme/mkWindow.h>

#include <Ui/Widget/mkRootSheet.h>

#include <iostream>

namespace mk
{
	Docksection::Docksection(Dockline& dockline, size_t index)
		: Tabber(cls(), true)
		, m_dockline(&dockline)
		, m_index(index)
	{}

	Docksection::~Docksection()
	{}

	void Docksection::dock(Window& window)
	{
		this->vappend(window.parent()->vrelease(window));
	}

	void Docksection::undock(Window& window)
	{
		this->rootSheet().append(Tabber::vrelease(window));

		if(m_tabs.count() == 0)
			m_dockline->removeSection(*this);
	}

	Widget& Docksection::vappend(unique_ptr<Widget> widget)
	{
		return Tabber::vappend(std::move(widget));
	}

	unique_ptr<Widget> Docksection::vrelease(Widget& widget)
	{
		unique_ptr<Widget> unique = Tabber::vrelease(widget);

		if(m_tabs.count() == 0)
			m_dockline->removeSection(*this);

		return unique;
	}

	Docksection& Docksection::docktarget(Dimension dim, bool after)
	{
		float span = m_frame->dsize(m_dockline->dim()) / m_dockline->frame().dsize(m_dockline->dim());
		span = std::min(span, this->frame().dspan(m_dockline->dim()) / 2.f);

		if(m_dockline->dim() == dim)
		{
			m_frame->setSpanDim(m_dockline->dim(), m_frame->dspan(m_dockline->dim()) - span);
			return m_dockline->insertSection(m_frame->index() + (after ? 1 : 0), span);
		}
		else
		{
			return m_dockline->insertLine(m_frame->index(), true, span).insertSection(after ? 1 : 0);
		}
	}

	Docksection& Docksection::docktarget(float x, float y)
	{
		float xRel = x - m_frame->dabsolute(DIM_X);
		float yRel = y - m_frame->dabsolute(DIM_Y);

		if(xRel < m_frame->dsize(DIM_X) * 0.25f)
			return this->docktarget(DIM_X, false); // dock left
		else if(xRel > m_frame->dsize(DIM_X) * 0.75f)
			return this->docktarget(DIM_X, true); // dock right
		else if(yRel < m_frame->dsize(DIM_Y) * 0.25f)
			return this->docktarget(DIM_Y, false); // dock under
		else if(yRel > m_frame->dsize(DIM_Y) * 0.75f)
			return this->docktarget(DIM_Y, true); // dock above
		else
			return *this; // dock on
	}

	Dockline::Dockline(Dockspace& dockspace, Dockline* dockline, Dimension dim, size_t index, StyleType& type)
		: GridSheet(dim, type)
		, m_dockspace(dockspace)
		, m_dockline(dockline)
		, m_index(index)
	{}

	Dockline::~Dockline()
	{}

	Dockline& Dockline::insertLine(size_t index, bool replace, float span)
	{
		Dockline& dockline = m_dim == DIM_X ? (Dockline&) this->makeinsert<DocklineY>(index, m_dockspace, this, index)
											: (Dockline&) this->makeinsert<DocklineX>(index, m_dockspace, this, index);

		if(replace)
			dockline.frame().setSpanDim(m_dim, this->stripe().contents()[index + 1]->dspan(m_dim));
		else
			dockline.frame().setSpanDim(m_dim, span);

		if(replace)
			dockline.append(this->release(index + 1));

		return dockline;
	}

	Docksection& Dockline::insertSection(size_t index, float span)
	{
		Docksection& docksection = this->makeinsert<Docksection>(index, *this, index);
		docksection.frame().setSpanDim(m_dim, span);
		return docksection;
	}

	void Dockline::removeSection(Docksection& section)
	{
		Frame& givespan = section.frame().index() > 0 ? section.prev().frame() : section.next().frame();
		givespan.setSpanDim(m_dim, givespan.dspan(m_dim) + section.frame().dspan(m_dim));

		section.destroy();

		if(m_contents.size() == 1 && m_dockline)
			m_dockline->removeLine(*this);
	}

	void Dockline::removeLine(Dockline& line)
	{
		Widget& section = this->insert(line.release(size_t(0)), line.frame().index());
		section.as<Docksection>().setDockline(this);
		section.frame().setSpanDim(m_dim, line.frame().dspan(m_dim));

		line.destroy();

		if(m_contents.size() == 1 && m_dockline)
			m_dockline->removeLine(*this);
	}

	Dockline& Dockline::findLine(std::vector<string>& ids)
	{
		Dockline* dockline = this;

		//ids.pop_back(); // first is us
		while(ids.size() > 0)
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

	Dockline& Dockline::findLine(const string& dockid)
	{
		std::vector<string> ids = splitString(dockid, ".");
		std::reverse(ids.begin(), ids.end());

		return findLine(ids);
	}

	Docksection& Dockline::findOrCreateSection(const string& dockid)
	{
		std::vector<string> ids = splitString(dockid, ".");
		string section = ids.back();
		ids.pop_back();
		std::reverse(ids.begin(), ids.end());

		Dockline& dockline = this->findLine(ids);

		size_t index = fromString<size_t>(section);
		if(index < dockline.count())
			return dockline.at(index)->as<Docksection>();
		else
			return dockline.insertSection(index);
	}

	DocklineX::DocklineX(Dockspace& dockspace, Dockline* dockline, size_t index)
		: Dockline(dockspace, dockline, DIM_X, index, cls())
	{}

	DocklineY::DocklineY(Dockspace& dockspace, Dockline* dockline, size_t index)
		: Dockline(dockspace, dockline, DIM_Y, index, cls())
	{}

	MasterDockline::MasterDockline(Dockspace& dockspace)
		: DocklineX(dockspace, nullptr, 0)
	{}

	Dockspace::Dockspace()
		: Sheet(cls())
		, m_mainLine(this->makeappend<MasterDockline>(*this))
	{}

	Widget& Dockspace::vappend(unique_ptr<Widget> widget)
	{
		string dockid = widget->dockid();
		if (dockid == "")
			dockid = "0." + toString(m_mainLine.count());

		Docksection& section = m_mainLine.findOrCreateSection(dockid);
		Window& window = section.emplace<Window>(widget->name(), static_cast<WindowState>(WINDOW_DOCKABLE | WINDOW_DEFAULT), nullptr, &section);
		window.docked();
		return window.vappend(std::move(widget));
	}
}
