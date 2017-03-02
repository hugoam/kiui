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

namespace toy
{
	class _I_ TOY_UI_EXPORT Placeholder : public Board
	{
	public:
		Placeholder(Piece& parent, const string& name);

		const string& name() { return m_name; }

		static Type& cls() { static Type ty("Placeholder", Board::cls()); return ty; }

	protected:
		string m_name;
	};

	class _I_ TOY_UI_EXPORT Docksection : public Tabber
	{
	public:
		Docksection(Piece& parent, Dockline& dockline);

		Dockline* dockline() { return m_dockline; }

		void setDockline(Dockline* dockline) { m_dockline = dockline; }

		void handleRemove(Widget& widget);

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
		Dockline(Piece& parent, Dockspace& dockspace, Dockline* dockline, Dimension dim);

		Dimension dim() { return m_dim; }
		Dockline* dockline() { return m_dockline; }
		Dockspace& dockspace() { return m_dockspace; }

		Dockline& insertLine(size_t index, bool replace = false, float span = 1.f);
		Docksection& insertSection(size_t index, float span = 1.f);

		void removeSection(Docksection& docksection);
		void removeLine(Dockline& dockline);

		Dockline& findLine(std::vector<string>& ids);
		Dockline& findLine(const string& dockid);
		Docksection& findOrCreateSection(const string& dockid);

		static Type& cls() { static Type ty("Dockline", GridSheet::cls()); return ty; }

	protected:
		Dockspace& m_dockspace;
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
		Dockspace(Piece& parent);

		Dockline& mainline() { return m_mainLine; }

		Docksection& addSection();
		Window& addDockWindow(const string& name);
		
		virtual Container& emplaceContainer();

		static Type& cls() { static Type ty("Dockspace", Layout::cls()); return ty; }

	protected:
		MasterDockline m_mainLine;
	};
}

#endif
