//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_SHEET_H_INCLUDED
#define MK_SHEET_H_INCLUDED

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
	class MK_UI_EXPORT _I_ Sheet : public Widget
	{
	public:
		Sheet(Style* style, Form* form = nullptr);
		~Sheet();

		void nextFrame(size_t tick, size_t delta);

		FrameType frameType() { return STRIPE; }

		inline Stripe* stripe() { return mFrame->as<Stripe>(); }
		inline const std::vector<unique_ptr<Widget>>& contents() { return mContents; }
		inline size_t count() { return mContents.size(); }

		virtual Sheet* vaddwrapper(Widget* widget) { UNUSED(widget); return nullptr; }
		virtual Widget* vappend(unique_ptr<Widget> widget) { return append(std::move(widget)); }
		virtual unique_ptr<Widget> vrelease(Widget* widget) { return widget->unbind(); }

		Widget* insert(unique_ptr<Widget> widget, size_t index);
		Widget* append(unique_ptr<Widget> widget);
		unique_ptr<Widget> release(Widget* widget);
		unique_ptr<Widget> release(size_t index);
		Widget* at(size_t index) { return mContents.at(index).get(); }

		void clear();

		template <class T, class... Args>
		inline T* vmakeappend(Args&&... args)
		{
			return this->vappend(make_unique<T>(std::forward<Args>(args)...))->template as<T>();
		}

		template <class T, class... Args>
		inline T* makeappend(Args&&... args)
		{
			return this->append(make_unique<T>(std::forward<Args>(args)...))->template as<T>();
		}

		template <class T, class... Args>
		inline T* makeinsert(size_t index, Args&&... args)
		{
			return this->insert(make_unique<T>(std::forward<Args>(args)...), index)->template as<T>();
		}

	protected:
		std::vector<unique_ptr<Widget>> mContents;
	};

	class MK_UI_EXPORT _I_ ScrollSheet : public Sheet
	{
	public:
		ScrollSheet(Style* style, Form* form = nullptr);
		~ScrollSheet();

		void build();

		void nextFrame(size_t tick, size_t delta);

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

	protected:
		Sheet* mSheet;
		WScrollbar* mScrollbar;
	};

	class MK_UI_EXPORT GridSheet : public Sheet
	{
	public:
		GridSheet(Dimension dim, Style* style, Form* form = nullptr);

		void build();

		Style* hoverCursor() { return mHoverCursor; }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		virtual void gridResized(Widget* first, Widget* second) { UNUSED(first); UNUSED(second); }

	protected:
		Dimension mDim;
		Widget* mResizing;
		Style* mHoverCursor;
	};

	class MK_UI_EXPORT _I_ Cursor : public Widget, public Typed<Cursor>, public Styled<Cursor>
	{
	public:
		Cursor();

		FrameType frameType() { return LAYER; }
		size_t zorder() { return 15; }

		void nextFrame();
		void setPosition(float x, float y);
		void hover(Widget* hovered);
		void unhover(Widget* hovered);

		using Typed<Cursor>::cls;

	protected:
		bool mDirty;
	};

	class MK_UI_EXPORT ResizeCursorX : public Object, public Typed<ResizeCursorX>, public Styled<ResizeCursorX>
	{};

	class MK_UI_EXPORT ResizeCursorY : public Object, public Typed<ResizeCursorY>, public Styled<ResizeCursorY>
	{};

	class MK_UI_EXPORT _I_ Tooltip : public Widget, public Typed<Tooltip>, public Styled<Tooltip>
	{
	public:
		Tooltip(const string& label);
		~Tooltip();

		const string& label() { return mLabel; }
		FrameType frameType() { return LAYER; }
		size_t zorder() { return 14; }

		void setLabel(const string& label);

		using Typed<Tooltip>::cls;

	protected:
		string mLabel;
	};
}

#endif // MK_SHEET_H_INCLUDED
