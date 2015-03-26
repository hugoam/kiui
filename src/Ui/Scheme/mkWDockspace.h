//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WDOCKSPACE_H
#define MK_WDOCKSPACE_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Scheme/mkWTabber.h>

namespace mk
{
	class MK_UI_EXPORT _I_ WDocksection : public WTabber, public Typed<WDocksection>, public Styled<WDocksection>
	{
	public:
		WDocksection(WDockline* dockline, size_t index, Style* style);
		~WDocksection();

		void build();

		size_t index() { return mIndex; }
		WDockline* dockline() { return mDockline; }

		void setDockline(WDockline* dockline) { mDockline = dockline; }

		unique_ptr<Widget> vrelease(Widget* widget);

		void dock(WWindow* window);
		void undock(WWindow* window);

		WDocksection* docktarget(Dimension dim, bool after);
		WDocksection* docktarget(float x, float y);

		using Typed<WDocksection>::cls;
		using Styled<WDocksection>::styleCls;

	protected:
		WDockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT _I_ WDockline : public GridSheet, public Typed<WDockline>
	{
	public:
		WDockline(WDockspace* dockspace, WDockline* dockline, Dimension dim, size_t index, Style* style);
		~WDockline();

		void build();

		Dimension dim() { return mDim; }
		size_t index() { return mIndex; }
		WDockline* dockline() { return mDockline; }
		WDockspace* dockspace() { return mDockspace; }

		WDockline* insertLine(size_t index, bool replace = false, float span = 1.f);
		WDocksection* insertSection(size_t index, Style* style = nullptr, float span = 1.f);

		void removeSection(WDocksection* docksection);
		void removeLine(WDockline* dockline);

		WDockline* findLine(std::vector<string>& ids);

		WDocksection* findOrCreateSection(const string& dockid, Style* style = nullptr);
		WDocksection* findSection(const string& dockid);

		using Typed<WDockline>::cls;

	protected:
		WDockspace* mDockspace;
		WDockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT _I_ WDocklineX : public WDockline, public Typed<WDocklineX>, public Styled<WDocklineX>
	{
	public:
		WDocklineX(WDockspace* dockspace, WDockline* dockline, size_t index);

		using Typed<WDocklineX>::cls;
	};

	class MK_UI_EXPORT _I_ WDocklineY : public WDockline, public Typed<WDocklineY>, public Styled<WDocklineY>
	{
	public:
		WDocklineY(WDockspace* dockspace, WDockline* dockline, size_t index);

		using Typed<WDocklineY>::cls;
	};

	class MK_UI_EXPORT _I_ WMasterDockline : public WDockline, public Typed<WMasterDockline>, public Styled<WMasterDockline>
	{
	public:
		WMasterDockline(WDockspace* dockspace);

		using Typed<WMasterDockline>::cls;
	};

	class MK_UI_EXPORT _I_ WDockspace : public Sheet, public Typed<WDockspace>, public Styled<WDockspace>
	{
	public:
		WDockspace();

		void build();

		WDockline* mainline() { return mMainLine; }

		void addSection(const string& name);

		Widget* vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget* widget);

		using Typed<WDockspace>::cls;

	protected:
		WMasterDockline* mMainLine;
	};

	class MK_UI_EXPORT Dockspace : public Form, public Typed<Dockspace, Form>
	{
	public:
		Dockspace(Style* style = nullptr);

		using Typed<Dockspace, Form>::cls;
	};
}

#endif
