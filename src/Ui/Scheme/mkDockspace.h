//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WDOCKSPACE_H
#define MK_WDOCKSPACE_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Scheme/mkTabber.h>

namespace mk
{
	class MK_UI_EXPORT _I_ Docksection : public Tabber, public Typed<Docksection, Tabber>, public Styled<Docksection>
	{
	public:
		Docksection(Dockline* dockline, size_t index, Style* style);
		~Docksection();

		size_t index() { return mIndex; }
		Dockline* dockline() { return mDockline; }

		void setDockline(Dockline* dockline) { mDockline = dockline; }

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		void dock(Window* window);
		void undock(Window* window);

		Docksection* docktarget(Dimension dim, bool after);
		Docksection* docktarget(float x, float y);

		using Typed<Docksection, Tabber>::cls;
		using Styled<Docksection>::styleCls;

	protected:
		Dockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT _I_ Dockline : public GridSheet, public Typed<Dockline, Sheet>
	{
	public:
		Dockline(Dockspace* dockspace, Dockline* dockline, Dimension dim, size_t index, Style* style);
		~Dockline();

		Dimension dim() { return mDim; }
		size_t index() { return mIndex; }
		Dockline* dockline() { return mDockline; }
		Dockspace* dockspace() { return mDockspace; }

		Dockline* insertLine(size_t index, bool replace = false, float span = 1.f);
		Docksection* insertSection(size_t index, Style* style = nullptr, float span = 1.f);

		void removeSection(Docksection* docksection);
		void removeLine(Dockline* dockline);

		Dockline* findLine(std::vector<string>& ids);

		Docksection* findOrCreateSection(const string& dockid, Style* style = nullptr);
		Docksection* findSection(const string& dockid);

		using Typed<Dockline, Sheet>::cls;

	protected:
		Dockspace* mDockspace;
		Dockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT _I_ DocklineX : public Dockline, public Typed<DocklineX, Dockline>, public Styled<DocklineX>
	{
	public:
		DocklineX(Dockspace* dockspace, Dockline* dockline, size_t index);

		using Typed<DocklineX, Dockline>::cls;
	};

	class MK_UI_EXPORT _I_ DocklineY : public Dockline, public Typed<DocklineY, Dockline>, public Styled<DocklineY>
	{
	public:
		DocklineY(Dockspace* dockspace, Dockline* dockline, size_t index);

		using Typed<DocklineY, Dockline>::cls;
	};

	class MK_UI_EXPORT _I_ MasterDockline : public Dockline, public Typed<MasterDockline, Dockline>, public Styled<MasterDockline>
	{
	public:
		MasterDockline(Dockspace* dockspace);

		using Typed<MasterDockline, Dockline>::cls;
	};

	class MK_UI_EXPORT _I_ Dockspace : public Sheet, public Typed<Dockspace, Sheet>, public Styled<Dockspace>
	{
	public:
		Dockspace();

		Dockline* mainline() { return mMainLine; }

		void addSection(const string& name);

		Widget* vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget* widget);

		using Typed<Dockspace, Sheet>::cls;

	protected:
		MasterDockline* mMainLine;
	};
}

#endif
