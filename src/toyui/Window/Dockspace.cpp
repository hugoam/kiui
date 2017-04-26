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
	Placeholder::Placeholder(Wedge& parent)
		: Container(parent, cls())
	{}

	Docksection::Docksection(Wedge& parent, Dockline& dockline)
		: Tabber(parent, cls(), false)
		, m_dockline(&dockline)
	{}

	void Docksection::dock(Window& window)
	{
		this->addTab(window.name()).append(window.container()->release(window));
	}

	void Docksection::undock(Window& window)
	{
		RootSheet& rootSheet = this->rootSheet();
		rootSheet.append(window.container()->release(window));

		if(m_tabs.containerContents().empty())
			m_dockline->removeSection();
	}

	Tab& Docksection::addTab(const string& name)
	{
		Tab& tab = Tabber::addTab(name);
		tab.setStyle(DockTab::cls());
		return tab;
	}

	Docksection& Docksection::docktarget(Dimension dim, bool after)
	{
		if(m_dockline->dim() == dim)
			return m_dockline->divideSection((after ? 1 : 0));
		else
			return m_dockline->dockline()->insertSection(m_dockline->index() + (after ? 1 : 0));
	}

	Docksection& Docksection::docktarget(float x, float y)
	{
		DimFloat pos = m_frame->localPosition(x, y);
		if(pos.x() < m_frame->dsize(DIM_X) * 0.25f)
			return this->docktarget(DIM_X, false); // dock left
		else if(pos.x() > m_frame->dsize(DIM_X) * 0.75f)
			return this->docktarget(DIM_X, true); // dock right
		else if(pos.y() < m_frame->dsize(DIM_Y) * 0.25f)
			return this->docktarget(DIM_Y, false); // dock under
		else if(pos.y() > m_frame->dsize(DIM_Y) * 0.75f)
			return this->docktarget(DIM_Y, true); // dock above
		else
			return *this; // dock on
	}

	Dockline::Dockline(Wedge& parent, Dockspace& dockspace, Dockline* dockline, Dimension dim)
		: GridSheet(parent, dim, cls())
		, m_dockspace(dockspace)
		, m_dockline(dockline)
		, m_docksection(nullptr)
	{
		m_frame->setLength(dim);
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
		this->append(docksection.dockline().release(docksection));
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
		m_docksection->destroy();
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
			this->release(firstline);
		}
	}

	void Dockline::removeLine(Dockline& line)
	{
		line.destroy();
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
			if(index >= dockline->count())
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

	void Dockline::mouseEntered(MouseEvent& mouseEvent)
	{
		this->rootSheet().cursor().setStyle(m_dim == DIM_X ? ResizeCursorX::cls() : ResizeCursorY::cls());
	}

	MasterDockline::MasterDockline(Dockspace& dockspace)
		: Dockline(dockspace, dockspace, nullptr, DIM_Y)
	{}

	Dockspace::Dockspace(Wedge& parent)
		: Container(parent, cls())
		, m_mainLine(*this)
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
		window.docked();
		return window;
	}
}
