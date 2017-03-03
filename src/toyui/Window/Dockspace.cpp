//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Dockspace.h>

#include <toyobj/String/StringConvert.h>

#include <toyui/Widget/Layout.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Frame/Stripe.h>

#include <toyui/Window/Window.h>

#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Placeholder::Placeholder(Wedge& parent, const string& name)
		: Container(parent, cls())
		, m_name(name)
	{}

	Docksection::Docksection(Wedge& parent, Dockline& dockline)
		: Tabber(parent, cls(), true)
		, m_dockline(&dockline)
	{}

	void Docksection::dock(Window& window)
	{
		this->emplaceContainer().append(window.container()->release(window));
	}

	void Docksection::undock(Window& window)
	{
		RootSheet& rootSheet = this->rootSheet();
		rootSheet.append(window.container()->release(window));
	}

	void Docksection::handleRemove(Widget& widget)
	{
		if(m_containerContents.size() == 0)
			m_dockline->removeSection(*this);
	}

	Docksection& Docksection::docktarget(Dimension dim, bool after)
	{
		float span = m_frame->dsize(m_dockline->dim()) / m_dockline->frame().dsize(m_dockline->dim());
		span = std::min(span, this->frame().dspan(m_dockline->dim()) / 2.f);

		if(m_dockline->dim() == dim)
		{
			m_frame->setSpanDim(m_dockline->dim(), m_frame->dspan(m_dockline->dim()) - span);
			return m_dockline->insertSection(this->index() + (after ? 1 : 0), span);
		}
		else
		{
			return m_dockline->insertLine(this->index(), true, span).insertSection(after ? 1 : 0);
		}
	}

	Docksection& Docksection::docktarget(float x, float y)
	{
		if(x < m_frame->dsize(DIM_X) * 0.25f)
			return this->docktarget(DIM_X, false); // dock left
		else if(x > m_frame->dsize(DIM_X) * 0.75f)
			return this->docktarget(DIM_X, true); // dock right
		else if(y < m_frame->dsize(DIM_Y) * 0.25f)
			return this->docktarget(DIM_Y, false); // dock under
		else if(y > m_frame->dsize(DIM_Y) * 0.75f)
			return this->docktarget(DIM_Y, true); // dock above
		else
			return *this; // dock on
	}

	Dockline::Dockline(Wedge& parent, Dockspace& dockspace, Dockline* dockline, Dimension dim)
		: GridSheet(parent, dim, cls())
		, m_dockspace(dockspace)
		, m_dockline(dockline)
	{
		m_frame->setLength(dim);
	}

	Dockline& Dockline::insertLine(size_t index, bool replace, float span)
	{
		Dockline& dockline = this->insert(make_unique<Dockline>(*this, m_dockspace, this, m_dim == DIM_X ? DIM_Y : DIM_X), index).as<Dockline>();

		if(replace)
			dockline.frame().setSpanDim(m_dim, this->stripe().contents()[index + 1]->dspan(m_dim));
		else
			dockline.frame().setSpanDim(m_dim, span);

		if(replace)
			dockline.append(this->release(*this->contents().at(index + 1)));

		return dockline;
	}

	Docksection& Dockline::insertSection(size_t index, float span)
	{
		Docksection& docksection = this->insert(make_unique<Docksection>(*this, *this), index).as<Docksection>();
		docksection.frame().setSpanDim(m_dim, span);
		return docksection;
	}

	void Dockline::removeSection(Docksection& section)
	{
		Frame& givespan = this->stripe().first(section.frame()) ? this->stripe().next(section.frame()) : this->stripe().prev(section.frame());
		givespan.setSpanDim(m_dim, givespan.dspan(m_dim) + section.frame().dspan(m_dim));

		section.destroy();

		if(m_contents.size() == 1 && m_dockline)
			m_dockline->removeLine(*this);
	}

	void Dockline::removeLine(Dockline& line)
	{
		Widget& section = this->insert(line.release(*line.contents().at(0)), line.as<Widget>().index());
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
				dockline = &dockline->at(index).as<Dockline>();
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
			return dockline.at(index).as<Docksection>();
		else
			return dockline.insertSection(index);
	}

	MasterDockline::MasterDockline(Dockspace& dockspace)
		: Dockline(dockspace, dockspace, nullptr, DIM_X)
	{}

	Dockspace::Dockspace(Wedge& parent)
		: Container(parent, cls())
		, m_mainLine(*this)
	{}

	Docksection& Dockspace::addSection()
	{
		string dockid = toString(m_mainLine.count());
		Docksection& section = m_mainLine.findOrCreateSection(dockid);
		return section;
	}

	Window& Dockspace::addDockWindow(const string& name)
	{
		Docksection& section = this->addSection();
		Window& window = section.emplace<Window>(name, static_cast<WindowState>(WINDOW_DOCKABLE | WINDOW_DEFAULT), nullptr, &section);
		window.docked();
		return window;
	}

	Container& Dockspace::emplaceContainer()
	{
		return this->addDockWindow("").emplaceContainer();
	}
}
