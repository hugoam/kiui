//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DOCKSPACE_H
#define MK_DOCKSPACE_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Scheme/mkTabber.h>

namespace mk
{
	class MK_UI_EXPORT _I_ Docksection : public Tabber
	{
	public:
		Docksection(Dockline& dockline, size_t index);
		~Docksection();

		size_t index() { return mIndex; }
		Dockline* dockline() { return mDockline; }

		void setDockline(Dockline* dockline) { mDockline = dockline; }

		Widget& vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget& widget);

		void dock(Window& window);
		void undock(Window& window);

		Docksection& docktarget(Dimension dim, bool after);
		Docksection& docktarget(float x, float y);

		static StyleType& cls() { static StyleType ty("Docksection", Tabber::cls()); return ty; }

	protected:
		Dockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT _I_ Dockline : public GridSheet
	{
	public:
		Dockline(Dockspace& dockspace, Dockline* dockline, Dimension dim, size_t index);
		~Dockline();

		Dimension dim() { return mDim; }
		size_t index() { return mIndex; }
		Dockline* dockline() { return mDockline; }
		Dockspace& dockspace() { return mDockspace; }

		Dockline& insertLine(size_t index, bool replace = false, float span = 1.f);
		Docksection& insertSection(size_t index, float span = 1.f);

		void removeSection(Docksection& docksection);
		void removeLine(Dockline& dockline);

		Dockline& findLine(std::vector<string>& ids);
		Docksection& findOrCreateSection(const string& dockid);

		static StyleType& cls() { static StyleType ty("Dockline", GridSheet::cls()); return ty; }

	protected:
		Dockspace& mDockspace;
		Dockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT _I_ DocklineX : public Dockline
	{
	public:
		DocklineX(Dockspace& dockspace, Dockline* dockline, size_t index);

		static StyleType& cls() { static StyleType ty("DocklineX", Dockline::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ DocklineY : public Dockline
	{
	public:
		DocklineY(Dockspace& dockspace, Dockline* dockline, size_t index);

		static StyleType& cls() { static StyleType ty("DocklineY", Dockline::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ MasterDockline : public DocklineX
	{
	public:
		MasterDockline(Dockspace& dockspace);

		static StyleType& cls() { static StyleType ty("MasterDockline", DocklineX::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Dockspace : public Sheet
	{
	public:
		Dockspace();

		Dockline& mainline() { return mMainLine; }

		void addSection(const string& name);

		Widget& vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget& widget);

		static StyleType& cls() { static StyleType ty("Dockspace", Sheet::cls()); return ty; }

	protected:
		MasterDockline& mMainLine;
	};
}

#endif
