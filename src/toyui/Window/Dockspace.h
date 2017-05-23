//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DOCKSPACE_H
#define TOY_DOCKSPACE_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Button/Button.h>
#include <toyui/Container/Tabber.h>
#include <toyui/Frame/Grid.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Placeholder : public Board
	{
	public:
		Placeholder(Wedge& parent);

		static Type& cls() { static Type ty("Placeholder", Board::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT DockTab
	{
	public:
		static Type& cls() { static Type ty("DockTab", Tab::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Docksection : public Tabber
	{
	public:
		Docksection(Wedge& parent, Dockline& dockline);

		Dockline& dockline() { return *m_dockline; }
		void setDockline(Dockline& dockline) { m_dockline = &dockline; }

		Tab& addTab(const string& name);

		void dock(Window& window);
		void undock(Window& window);

		Docksection& docktarget(Dimension dim, bool after);
		Docksection& docktarget(float x, float y);

		static Type& cls() { static Type ty("Docksection", Tabber::cls()); return ty; }

	protected:
		Dockline* m_dockline;
	};

	class _I_ TOY_UI_EXPORT Dockline : public GridSheet
	{
	public:
		Dockline(Wedge& parent, Dockspace& dockspace, Dockline* dockline, Dimension dim);

		Dockspace& dockspace() { return m_dockspace; }
		Docksection* docksection() { return m_docksection; }
		Dockline* dockline() { return m_dockline; }

		Docksection& insertSection(size_t index);
		Docksection& divideSection(size_t index);
		Docksection& appendSection();
		void moveSection(Docksection& docksection);
		void removeSection();
		void collapseSection();

		Dockline& appendLine();
		void removeLine(Dockline& dockline);

		Dockline& findLine(const GridIndex& dockid);
		Docksection& findOrCreateSection(const GridIndex& dockid);

		void resetSpans();

		virtual bool mouseEntered(MouseEvent& mouseEvent);

		static Type& cls() { static Type ty("Dockline", GridSheet::cls()); return ty; }

	protected:
		Dockspace& m_dockspace;
		Docksection* m_docksection;
		Dockline* m_dockline;
	};

	class _I_ TOY_UI_EXPORT MasterDockline : public Dockline
	{
	public:
		MasterDockline(Dockspace& dockspace);

		static Type& cls() { static Type ty("MasterDockline", Dockline::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Dockspace : public Layout
	{
	public:
		Dockspace(Wedge& parent);

		Dockline& mainline() { return m_mainLine; }

		Docksection& addSection(const GridIndex& dockid);
		Window& addDockWindow(const string& name, const GridIndex& dockid);
		
		static Type& cls() { static Type ty("Dockspace", Layout::cls()); return ty; }

	protected:
		MasterDockline m_mainLine;
	};
}

#endif
