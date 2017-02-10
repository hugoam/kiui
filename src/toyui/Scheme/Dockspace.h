//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DOCKSPACE_H
#define TOY_DOCKSPACE_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Widget/Sheet.h>
#include <toyui/Widget/Button.h>
#include <toyui/Scheme/Tabber.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Placeholder : public Widget
	{
	public:
		Placeholder(const string& name);

		const string& name() { return m_name; }

		static StyleType& cls() { static StyleType ty("Placeholder", Widget::cls()); return ty; }

	protected:
		string m_name;
	};

	class _I_ TOY_UI_EXPORT Docksection : public Tabber
	{
	public:
		Docksection(Dockline& dockline);

		Dockline* dockline() { return m_dockline; }

		void setDockline(Dockline* dockline) { m_dockline = dockline; }

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void dock(Window& window);
		void undock(Window& window);

		Docksection& docktarget(Dimension dim, bool after);
		Docksection& docktarget(float x, float y);

		static StyleType& cls() { static StyleType ty("Docksection", Tabber::cls()); return ty; }

	protected:
		Dockline* m_dockline;
	};

	class _I_ TOY_UI_EXPORT Dockline : public GridSheet
	{
	public:
		Dockline(Dockspace& dockspace, Dockline* dockline, Dimension dim, StyleType& type);

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

		static StyleType& cls() { static StyleType ty("Dockline", GridSheet::cls()); return ty; }

	protected:
		Dockspace& m_dockspace;
		Dockline* m_dockline;
	};

	class _I_ TOY_UI_EXPORT DocklineX : public Dockline
	{
	public:
		DocklineX(Dockspace& dockspace, Dockline* dockline);

		static StyleType& cls() { static StyleType ty("DocklineX", Dockline::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT DocklineY : public Dockline
	{
	public:
		DocklineY(Dockspace& dockspace, Dockline* dockline);

		static StyleType& cls() { static StyleType ty("DocklineY", Dockline::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT MasterDockline : public DocklineX
	{
	public:
		MasterDockline(Dockspace& dockspace);

		static StyleType& cls() { static StyleType ty("MasterDockline", DocklineX::cls()); return ty; }
	};

	class _I_ TOY_UI_EXPORT Dockspace : public Sheet
	{
	public:
		Dockspace();

		Dockline& mainline() { return m_mainLine; }

		Widget& vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget& widget);

		static StyleType& cls() { static StyleType ty("Dockspace", Sheet::cls()); return ty; }

	protected:
		MasterDockline& m_mainLine;
	};
}

#endif
