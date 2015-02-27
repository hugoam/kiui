//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_LAYER_H_INCLUDED
#define MK_LAYER_H_INCLUDED

/* mk */
#include <Object/mkId.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkStripe.h>

#include <memory>

namespace mk
{
	class MK_UI_EXPORT Sheet : public Widget
	{
	public:
		Sheet(string clas, Form* form = nullptr);
		~Sheet();

		void build();

		FrameType frameType() { return STRIPE; }

		inline Stripe* stripe() { return mFrame->as<Stripe>(); }
		inline Registry<Widget>* contents() { return &mContents; }

		InkStyle* elementSkin(string clas);
		LayoutStyle* elementStyle(string clas);

		virtual Sheet* vaddwrapper(Widget* widget) { return nullptr; }
		virtual Widget* vappend(std::unique_ptr<Widget> widget) { return append(std::move(widget)); }
		virtual std::unique_ptr<Widget> vrelease(Widget* widget) { return widget->unbind(); }

		Widget* insert(std::unique_ptr<Widget> widget, size_t index);
		Widget* append(std::unique_ptr<Widget> widget);
		std::unique_ptr<Widget> release(Widget* widget);
		std::unique_ptr<Widget> release(size_t index);

		void clear();

		template <class T, class... Args>
		inline T* vmakeappend(Args&&... args)
		{
			return this->vappend(make<T>(std::forward<Args>(args)...))->as<T>();
		}

		template <class T, class... Args>
		inline T* makeappend(Args&&... args)
		{
			return this->append(make<T>(std::forward<Args>(args)...))->as<T>();
		}

		template <class T, class... Args>
		inline T* makeinsert(size_t index, Args&&... args)
		{
			return this->insert(make<T>(std::forward<Args>(args)...), index)->as<T>();
		}

	protected:
		Registry<Widget> mContents;
		bool mOverrides;
	};

	class GridSheet : public Sheet
	{
	public:
		GridSheet(Dimension dim, string clas, Form* form = nullptr);

		void build();

		const string& hoverCursor() { return mHoverCursor; }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		virtual void gridResized(Widget* first, Widget* second) {}

	protected:
		Dimension mDim;
		Widget* mResizing;
		string mHoverCursor;
	};

	class ScrollSheet : public Sheet
	{
	public:
		ScrollSheet(string clas, Form* form = nullptr);

		void build();

		Widget* vappend(std::unique_ptr<Widget> widget);
		std::unique_ptr<Widget> vrelease(Widget* widget);

		void nextFrame(size_t tick, size_t delta);

	protected:
		Sheet* mScrollbox;
		Sheet* mSheet;
		string mClas;
		Form* mForm;
		WScrollbar* mScrollbar;
	};

	class Cursor : public Widget
	{
	public:
		Cursor();

		string clas() { return "cursor"; }
		size_t zorder() { return 15; }

		void nextFrame();
		void setPosition(float x, float y);
		void hover(Widget* hovered);
		void unhover(Widget* hovered);

	protected:
		bool mDirty;
	};

	class Tooltip : public Widget
	{
	public:
		Tooltip(const string& label);
		~Tooltip();

		string clas() { return "tooltip"; }
		const string& label() { return mLabel; }
		size_t zorder() { return 14; }

		void setLabel(string label);

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT RootSheet : public Sheet
	{
	public:
		RootSheet(UiWindow* window, Form* form);

		void init();

		UiWindow* uiWindow() { return mWindow; }
		RootSheet* rootWidget() { return this; }

		InkStyle* elementSkin(string clas);
		LayoutStyle* elementStyle(string clas);

	protected:
		UiWindow* mWindow;
	};
}

#endif // MK_LAYER_H_INCLUDED
