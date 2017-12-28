//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DOCKSPACE_H
#define TOY_DOCKSPACE_H

/* toy */
#include <toyui/Types.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Cursor.h>
#include <toyui/Button/Button.h>
#include <toyui/Container/Tabber.h>
#include <toyui/Solver/Grid.h>

namespace toy
{
	class _refl_ TOY_UI_EXPORT Docksection : public Tabber
	{
	public:
		Docksection(const Params& params, Dockline& dockline);

		Dockline* m_dockline;

		Tab& addTab(const string& name);

		void dock(Window& window);
		void undock(Window& window);

		Docksection& docktarget(Dimension dim, bool after);
		Docksection& docktarget(const DimFloat& pos);
	};

	class _refl_ TOY_UI_EXPORT Dockline : public GridSheet
	{
	public:
		Dockline(const Params& params, Dockspace& dockspace, Dockline* dockline, Dimension dim);

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

	public:
		Dockspace& m_dockspace;
		Docksection* m_docksection;
		Dockline* m_dockline;
	};

	class _refl_ TOY_UI_EXPORT Dockspace : public Wedge
	{
	public:
		Dockspace(const Params& params);

		Docksection& addSection(const GridIndex& dockid);
		Window& addDockWindow(const string& name, const GridIndex& dockid, float span = 0.f);

		struct Styles
		{
			Style docktab = { "Docktab", Tabber::styles().tab };
			Style placeholder = { "Placeholder", Widget::styles().board, Args{ { &InkStyle::m_background_colour, Colour::Blue } } };

			Style dockline = { cls<Dockline>(), Widget::styles().gridsheet };
			Style dockline_x = { "DocklineX", dockline, Args{ { &InkStyle::m_hover_cursor, &Cursor::styles().resize_x } } };
			Style dockline_y = { "DocklineY", dockline, Args{ { &InkStyle::m_hover_cursor, &Cursor::styles().resize_y } } };

			Style dockspace = { cls<Dockspace>(), Widget::styles().layout, Args{ { &Layout::m_opacity, OPAQUE }, { &Layout::m_spacing, DimFloat(6.f) } } };
		};
		static Styles& styles() { static Styles styles; return styles; }

	protected:
		Dockline m_mainLine;
	};
}

#endif
