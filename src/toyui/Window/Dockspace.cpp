//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Window/Dockspace.h>

#include <toyui/Window/Window.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	Docksection::Docksection(Wedge& parent, Dockline& dockline)
		: Tabber(parent, cls(), false)
		, m_dockline(&dockline)
	{}

	void Docksection::dock(Window& window)
	{
		Tab& tab = this->addTab(window.name());
		window.container()->store().transfer(window, tab);
	}

	void Docksection::undock(Window& window)
	{
		Tab& tab = *window.findContainer<Tab>();
		window.container()->store().transfer(window, this->rootSheet());
		this->removeTab(tab);

		if(m_tabs.contents().empty())
			m_dockline->removeSection();
	}

	Tab& Docksection::addTab(const string& name)
	{
		Tab& tab = Tabber::addTab(name);
		tab.setStyle(Docksection::DockTab());
		return tab;
	}

	Docksection& Docksection::docktarget(Dimension dim, bool after)
	{
		if(m_dockline->dim() == dim)
			return m_dockline->divideSection((after ? 1 : 0));
		else
			return m_dockline->dockline()->insertSection(m_dockline->index() + (after ? 1 : 0));
	}

	Docksection& Docksection::docktarget(const DimFloat& pos)
	{
		DimFloat local = m_frame->localPosition(pos);
		if(local.x() < m_frame->d_size.x() * 0.25f)
			return this->docktarget(DIM_X, false); // dock left
		else if(local.x() > m_frame->d_size.x() * 0.75f)
			return this->docktarget(DIM_X, true); // dock right
		else if(local.y() < m_frame->d_size.y() * 0.25f)
			return this->docktarget(DIM_Y, false); // dock under
		else if(local.y() > m_frame->d_size.y() * 0.75f)
			return this->docktarget(DIM_Y, true); // dock above
		else
			return *this; // dock on
	}

	Dockline::Dockline(Wedge& parent, Dockspace& dockspace, Dockline* dockline, Dimension dim)
		: GridSheet(parent, dim, nullptr, cls())
		, m_dockspace(dockspace)
		, m_dockline(dockline)
		, m_docksection(nullptr)
	{
		m_frame->d_length = dim;
	}

	void Dockline::resetSpans()
	{
		for(Widget* widget : m_contents)
			widget->frame().setSpanDim(m_dim, 1.f);
	}

	Docksection& Dockline::insertSection(size_t index)
	{
		Dockline& dockline = this->appendLine();
		this->move(m_contents.size() - 1, index);
		this->resetSpans();
		return dockline.appendSection();
	}

	Docksection& Dockline::divideSection(size_t index)
	{
		Dockline& firstline = this->appendLine();
		Dockline& secondline = this->appendLine();

		Dockline& replace = index == 1 ? firstline : secondline;
		Dockline& result = index == 0 ? firstline : secondline;
		replace.moveSection(*m_docksection);

		return result.appendSection();
	}

	Docksection& Dockline::appendSection()
	{
		if(m_docksection == nullptr)
			m_docksection = &this->emplace<Docksection>(*this);
		return *m_docksection;
	}

	void Dockline::moveSection(Docksection& docksection)
	{
		docksection.dockline().store().transfer(docksection, *this);
		docksection.setDockline(*this);
		m_docksection = &docksection;
	}

	Dockline& Dockline::appendLine()
	{
		Dockline& dockline = this->emplace<Dockline>(m_dockspace, this, m_dim == DIM_X ? DIM_Y : DIM_X);
		return dockline;
	}

	void Dockline::removeSection()
	{
		m_docksection->extract();
		m_dockline->removeLine(*this);
	}

	void Dockline::collapseSection()
	{
		Dockline& firstline = m_contents.at(0)->as<Dockline>();
		Dockline* line = &firstline;

		while(line->contents().size() == 1 && !line->docksection())
			line = &line->contents().at(0)->as<Dockline>();

		if(line->docksection())
		{
			this->moveSection(*line->docksection());
			this->store().remove(firstline);
		}
	}

	void Dockline::removeLine(Dockline& line)
	{
		line.extract();
		this->resetSpans();

		if(m_contents.size() == 1)
			this->collapseSection();

		if(m_contents.empty() && m_dockline)
			m_dockline->removeLine(*this);
	}

	Dockline& Dockline::findLine(const GridIndex& inputDockid)
	{
		GridIndex dockid = inputDockid;
		std::reverse(dockid.begin(), dockid.end());

		Dockline* dockline = this;

		while(dockid.size() > 0)
		{
			size_t index = dockid.back(); dockid.pop_back();
			while(index >= dockline->count())
				dockline->appendLine();
			dockline = &dockline->at(index).as<Dockline>();
		}

		return *dockline;
	}

	Docksection& Dockline::findOrCreateSection(const GridIndex& dockid)
	{
		Dockline& dockline = this->findLine(dockid);
		return dockline.appendSection();
	}

	bool Dockline::mouseEntered(MouseEvent& mouseEvent)
	{
		this->rootSheet().cursor().setStyle(m_dim == DIM_X ? Cursor::ResizeX() : Cursor::ResizeY());
		return true;
	}

	Dockspace::Dockspace(Wedge& parent)
		: Wedge(parent, cls())
		, m_mainLine(*this, *this, nullptr, DIM_Y)
	{}

	Docksection& Dockspace::addSection(const GridIndex& dockid)
	{
		Docksection& section = m_mainLine.findOrCreateSection(dockid);
		return section;
	}

	Window& Dockspace::addDockWindow(const string& name, const GridIndex& dockid)
	{
		Docksection& section = this->addSection(dockid);
		Window& window = section.addTab(name).emplace<Window>(name, static_cast<WindowState>(WINDOW_DOCKABLE | WINDOW_DEFAULT), nullptr, &section);
		return window;
	}
}
