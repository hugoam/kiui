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
#include <toyui/Solver/Grid.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Docksection : public Tabber
	{
	public:
		Docksection(Wedge& parent, Dockline& dockline);

		Dockline& dockline() { return *m_dockline; }
		void setDockline(Dockline& dockline) { m_dockline = &dockline; }

		Tab& addTab(const string& name);

		void dock(Window& window);
		void undock(Window& window);

		Docksection& docktarget(Dimension dim, bool after);
		Docksection& docktarget(const DimFloat& pos);

		static Type& cls() { static Type ty("Docksection", Tabber::cls()); return ty; }

		static Type& DockTab() { static Type ty("DockTab", Tab::cls()); return ty; }
		static Type& Placeholder() { static Type ty("Placeholder", Wedge::Board()); return ty; }

	protected:
		Dockline* m_dockline;
	};

	class _refl_ TOY_UI_EXPORT Dockline : public GridSheet
	{
	public:
		Dockline(Wedge& parent, Dockspace& dockspace, Dockline* dockline, Dimension dim);

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

		static Type& cls() { static Type ty("Dockline", GridSheet::cls()); return ty; }

		static Type& DocklineX() { static Type ty("DocklineX", Dockline::cls()); return ty; }
		static Type& DocklineY() { static Type ty("DocklineY", Dockline::cls()); return ty; }

	public:
		Dockspace& m_dockspace;
		Docksection* m_docksection;
		Dockline* m_dockline;
	};

	class _refl_ TOY_UI_EXPORT Dockspace : public Wedge
	{
	public:
		Dockspace(Wedge& parent);

		Docksection& addSection(const GridIndex& dockid);
		Window& addDockWindow(const string& name, const GridIndex& dockid, float span = 0.f);
		
		static Type& cls() { static Type ty("Dockspace", Wedge::Layout()); return ty; }

	protected:
		Dockline m_mainLine;
	};
}

#endif
