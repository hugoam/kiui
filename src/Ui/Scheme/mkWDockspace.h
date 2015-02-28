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
	class MK_UI_EXPORT WDocksection : public WTabber, public Typed<WDocksection>
	{
	public:
		WDocksection(WDockline* dockline, size_t index, string clas);
		~WDocksection();

		void build();

		string dockid();

		size_t index() { return mIndex; }
		WDockline* dockline() { return mDockline; }

		void setDockline(WDockline* dockline) { mDockline = dockline; }

		void updateSpan();

		void dock(WWindow* window);
		void undock(WWindow* window);

		WDocksection* docktarget(Dimension dim, size_t index, bool after);
		WDocksection* docktarget(float x, float y);

		using Typed<WDocksection>::cls;

	protected:
		WDockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT WDockline : public GridSheet, public Typed<WDockline>
	{
	public:
		WDockline(WDockspace* dockspace, WDockline* dockline, Dimension dim, size_t index);
		~WDockline();

		void build();

		string dockid();

		Dimension dim() { return mDim; }
		size_t index() { return mIndex; }
		WDockline* dockline() { return mDockline; }
		WDockspace* dockspace() { return mDockspace; }

		WDockline* insertLine(size_t index, bool replace = false);
		WDocksection* insertSection(size_t index, string clas = "");

		void removeSection(WDocksection* docksection);
		void removeLine(WDockline* dockline);

		WDockline* findLine(std::vector<string>& ids);

		WDocksection* findOrCreateSection(string dockid, string clas = "");
		WDocksection* findSection(string dockid);

		void updateSpan();

		using Typed<WDockline>::cls;

	protected:
		WDockspace* mDockspace;
		WDockline* mDockline;
		size_t mIndex;
	};

	class MK_UI_EXPORT WDockspace : public Sheet, public Typed<WDockspace>
	{
	public:
		WDockspace();

		void build();

		WDockline* mainline() { return mMainLine; }

		float getSpan(string dockid);
		void setSpan(string dockid, float span);
		void addSpan(string dockid);

		void addSection(string name);

		Widget* vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget* widget);

		using Typed<WDockspace>::cls;

	protected:
		std::map<string, float> mDockSpans;
		WDockline* mMainLine;
	};

	class MK_UI_EXPORT Dockspace : public Form
	{
	public:
		Dockspace(const string& cls = "");
	};
}

#endif
