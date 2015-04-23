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
#include <deque>

namespace mk
{
	class MK_UI_EXPORT _I_ Sheet : public Widget
	{
	public:
		Sheet(FrameType frameType = STRIPE);
		~Sheet();

		void nextFrame(size_t tick, size_t delta);

		inline Stripe& stripe() { return mFrame->as<Stripe>(); }
		inline const std::vector<unique_ptr<Widget>>& contents() { return mContents; }
		inline size_t count() { return mContents.size(); }

		inline Widget* at(size_t index) { return mContents.at(index).get(); }

		void bind(Sheet* parent, size_t index);
		void rebind(Sheet* parent, size_t index);

		virtual Widget& vappend(unique_ptr<Widget> widget) { return append(std::move(widget)); }
		virtual unique_ptr<Widget> vrelease(Widget& widget) { return widget.unbind(); }

		Widget& insert(unique_ptr<Widget> widget, size_t index);
		Widget& append(unique_ptr<Widget> widget);
		unique_ptr<Widget> release(Widget& widget);
		unique_ptr<Widget> release(size_t index);

		void clear();

		void cleanup();

		template <class T, class... Args>
		inline T& emplace(Args&&... args)
		{
			return this->vappend(make_unique<T>(std::forward<Args>(args)...)).template as<T>();
		}

		static StyleType& cls() { static StyleType ty(Widget::cls()); return ty; }

	protected:
		template <class T, class... Args>
		inline T& makeappend(Args&&... args)
		{
			return this->append(make_unique<T>(std::forward<Args>(args)...)).template as<T>();
		}

		template <class T, class... Args>
		inline T& makeinsert(size_t index, Args&&... args)
		{
			return this->insert(make_unique<T>(std::forward<Args>(args)...), index).template as<T>();
		}

	protected:
		std::vector<unique_ptr<Widget>> mContents;
	};

	class MK_UI_EXPORT _I_ LayerSheet : public Sheet
	{
	public:
		LayerSheet();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Board : public Sheet
	{
	public:
		Board();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ WrapSheet : public Sheet
	{
	public:
		WrapSheet();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ ScrollSheet : public Sheet
	{
	public:
		ScrollSheet(FrameType frameType = STRIPE);
		~ScrollSheet();

		void nextFrame(size_t tick, size_t delta);

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		ScrollArea& mScrollArea;
	};

	class MK_UI_EXPORT GridSheet : public Sheet
	{
	public:
		GridSheet(Dimension dim);

		Style* hoverCursor() { return &mHoverCursor; }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		virtual void gridResized(Widget& first, Widget& second) { UNUSED(first); UNUSED(second); }

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }

	protected:
		Dimension mDim;
		Widget* mResizing;
		Style& mHoverCursor;
	};

	class MK_UI_EXPORT _I_ Cursor : public Widget
	{
	public:
		Cursor(RootSheet& rootSheet);

		void nextFrame();
		void setPosition(float x, float y);

		void hover(Widget& hovered);
		void unhover();

		void tooltipOn();
		void tooltipOff();

		static StyleType& cls() { static StyleType ty(Widget::cls()); return ty; }

	protected:
		bool mDirty;
		Widget* mHovered;
		std::vector<Widget*> mUnderHover;
		Tooltip& mTooltip;
		Clock mTooltipClock;
	};

	class MK_UI_EXPORT ResizeCursorX : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty(Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT ResizeCursorY
	{
	public:
		static StyleType& cls() { static StyleType ty(Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT MoveCursor : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty(Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT ResizeCursorDiagLeft : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty(Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT ResizeCursorDiagRight : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty(Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT CaretCursor : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty(Cursor::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ Caret : public Widget
	{
	public:
		Caret(Frame* textFrame);

		size_t index() { return mIndex; }

		void setIndex(size_t index) { mIndex = index; mDirty = true; }
		
		void moveTo(size_t index);
		void moveRight();
		void moveLeft();

		void nextFrame(size_t tick, size_t delta);

		static StyleType& cls() { static StyleType ty(Widget::cls()); return ty; }

	protected:
		Frame* mTextFrame;
		size_t mIndex;
		bool mDirty;
	};

	class MK_UI_EXPORT _I_ Tooltip : public Widget
	{
	public:
		Tooltip(const string& label);
		~Tooltip();

		const string& label() { return mLabel; }

		void setLabel(const string& label);

		static StyleType& cls() { static StyleType ty(Widget::cls()); return ty; }

	protected:
		string mLabel;
	};

	class MK_UI_EXPORT Sequence : public Sheet
	{
	public:
		Sequence();

		static StyleType& cls() { static StyleType ty(Sheet::cls()); return ty; }
	};
}

#endif // MK_SHEET_H_INCLUDED
