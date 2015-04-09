//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_SHEET_H_INCLUDED
#define MK_SHEET_H_INCLUDED

/* mk */
#include <Object/mkId.h>
#include <Object/String/mkString.h>
#include <Object/Util/mkUpdatable.h>
#include <Object/Util/mkTimer.h>
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkStripe.h>

#include <memory>

namespace mk
{
	class MK_UI_EXPORT _I_ Sheet : public Widget, public Typed<Sheet>
	{
	public:
		Sheet(Style* style, FrameType frameType = STRIPE);
		~Sheet();

		void nextFrame(size_t tick, size_t delta);

		inline Stripe* stripe() { return mFrame->as<Stripe>(); }
		inline const std::vector<unique_ptr<Widget>>& contents() { return mContents; }
		inline size_t count() { return mContents.size(); }

		inline Widget* at(size_t index) { return mContents.at(index).get(); }

		void bind(Sheet* parent, size_t index);
		void rebind(Sheet* parent, size_t index);

		virtual Widget* vappend(unique_ptr<Widget> widget) { return append(std::move(widget)); }
		virtual unique_ptr<Widget> vrelease(Widget* widget) { return widget->unbind(); }

		Widget* insert(unique_ptr<Widget> widget, size_t index);
		Widget* append(unique_ptr<Widget> widget);
		unique_ptr<Widget> release(Widget* widget);
		unique_ptr<Widget> release(size_t index);

		void clear();

		void cleanup();

		template <class T, class... Args>
		inline T* emplace(Args&&... args)
		{
			return this->vappend(make_unique<T>(std::forward<Args>(args)...))->template as<T>();
		}

		using Typed<Sheet>::cls;

	protected:
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

	class MK_UI_EXPORT _I_ ScrollSheet : public Sheet, public Typed<ScrollSheet, Sheet>, public Styled<ScrollSheet>
	{
	public:
		ScrollSheet(Style* style);
		~ScrollSheet();

		void nextFrame(size_t tick, size_t delta);

		Widget* vappend(unique_ptr<Widget> widget);
		unique_ptr<Widget> vrelease(Widget* widget);

		using Typed<ScrollSheet, Sheet>::cls;

	protected:
		Sheet* mSheet;
		Scrollbar* mScrollbar;
	};

	class MK_UI_EXPORT GridSheet : public Sheet
	{
	public:
		GridSheet(Dimension dim, Style* style);

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

	class MK_UI_EXPORT _I_ Cursor : public Widget, public Typed<Cursor, Widget>, public Styled<Cursor>
	{
	public:
		Cursor(RootSheet* rootSheet);

		Widget* hovered() { return mHovered; }

		void nextFrame();
		void setPosition(float x, float y);

		void hover(Widget* hovered);
		void unhover(Widget* hovered);

		void tooltipOn();
		void tooltipOff();

		using Typed<Cursor, Widget>::cls;

	protected:
		bool mDirty;
		Widget* mHovered;
		Tooltip* mTooltip;
		Clock mTooltipClock;
	};

	class MK_UI_EXPORT ResizeCursorX : public Object, public Typed<ResizeCursorX>, public Styled<ResizeCursorX>
	{};

	class MK_UI_EXPORT ResizeCursorY : public Object, public Typed<ResizeCursorY>, public Styled<ResizeCursorY>
	{};

	class MK_UI_EXPORT MoveCursor : public Object, public Typed<MoveCursor>, public Styled<MoveCursor>
	{};

	class MK_UI_EXPORT ResizeCursorDiagLeft : public Object, public Typed<ResizeCursorDiagLeft>, public Styled<ResizeCursorDiagLeft>
	{};

	class MK_UI_EXPORT ResizeCursorDiagRight : public Object, public Typed<ResizeCursorDiagRight>, public Styled<ResizeCursorDiagRight>
	{};

	class MK_UI_EXPORT CaretCursor : public Object, public Typed<CaretCursor>, public Styled<CaretCursor>
	{};

	class MK_UI_EXPORT _I_ Caret : public Widget, public Typed<Caret, Widget>, public Styled<Caret>
	{
	public:
		Caret(Frame* textFrame);

		size_t index() { return mIndex; }

		void setIndex(size_t index) { mIndex = index; mDirty = true; }

		void nextFrame(size_t tick, size_t delta);

		using Typed<Caret, Widget>::cls;

	protected:
		Frame* mTextFrame;
		size_t mIndex;
		bool mDirty;
	};

	class MK_UI_EXPORT _I_ Tooltip : public Widget, public Typed<Tooltip, Widget>, public Styled<Tooltip>
	{
	public:
		Tooltip(const string& label);
		~Tooltip();

		const string& label() { return mLabel; }

		void setLabel(const string& label);

		using Typed<Tooltip, Widget>::cls;

	protected:
		string mLabel;
	};
}

#endif // MK_SHEET_H_INCLUDED
