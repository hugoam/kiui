//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WWINDOW_H
#define MK_WWINDOW_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT _I_ DockWindow : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("DockWindow", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ ShrinkWindow : public Object
	{
	public:
		static StyleType& cls() { static StyleType ty("ShrinkWindow", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ WindowHeader : public Sequence
	{
	public:
		WindowHeader(Window& window);

		Style* hoverCursor() { return &MoveCursor::cls(); }
		const string& tooltip() { return mTooltip; }

		Label& title() { return mTitle; }
		Button* closeButton() { return mCloseButton; }

		bool leftClick(float xPos, float yPos);
		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		static StyleType& cls() { static StyleType ty("WindowHeader", Sequence::cls()); return ty; }

	protected:
		Window& mWindow;
		Label& mTitle;
		Widget& mSpacer;
		Button* mCloseButton;
		string mTooltip;
	};

	class MK_UI_EXPORT _I_ WindowSizer : public Widget
	{
	public:
		WindowSizer(Window& window, bool left);

		Style* hoverCursor() { return &ResizeCursorDiagRight::cls(); }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		static StyleType& cls() { static StyleType ty("WindowSizer", Widget::cls()); return ty; }

	protected:
		Window& mWindow;
		bool mResizeLeft;
	};

	class MK_UI_EXPORT _I_ WindowSizerLeft : public WindowSizer
	{
	public:
		WindowSizerLeft(Window& window);

		static StyleType& cls() { static StyleType ty("WindowSizerLeft", WindowSizer::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ WindowSizerRight : public WindowSizer
	{
	public:
		WindowSizerRight(Window& window);

		static StyleType& cls() { static StyleType ty("WindowSizerRight", WindowSizer::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ WindowFooter : public Sheet
	{
	public:
		WindowFooter(Window& window);

		static StyleType& cls() { static StyleType ty("WindowFooter", Sheet::cls()); return ty; }

	protected:
		WindowSizer& mFirstSizer;
		WindowSizer& mSecondSizer;
	};

	class MK_UI_EXPORT _I_ WindowBody : public Sheet
	{
	public:
		WindowBody();

		static StyleType& cls() { static StyleType ty("WindowBody", Sheet::cls()); return ty; }
	};

	class MK_UI_EXPORT _I_ CloseButton : public Button
	{
	public:
		CloseButton(const Trigger& trigger);

		static StyleType& cls() { static StyleType ty("CloseButton", Button::cls()); return ty; }
	};

	class MK_UI_EXPORT Window : public LayerSheet
	{
	public:
		Window(const string& title, bool closable = true, bool dockable = false, const Trigger& onClose = nullptr, Docksection* dock = nullptr);
		~Window();

		const string& name();

		bool dockable() { return mDockable; }
		bool movable() { return mMovable; }
		bool closable() { return mClosable; }
		
		WindowBody& body() { return mBody; }
		Docksection* dock() { return mDock; }

		void bind(Sheet* parent, size_t index);

		void toggleClosable();
		void toggleMovable();
		void toggleResizable();
		void showTitlebar();
		void hideTitlebar();

		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

		Widget& vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget& widget);

		void dock(Docksection& docksection);
		void undock();

		void docked();
		void undocked();

		void close();

		static StyleType& cls() { static StyleType ty("Window", LayerSheet::cls()); return ty; }

	protected:
		string mName;
		bool mClosable;
		bool mDockable;
		bool mMovable;
		bool mSizable;
		Widget* mContent;
		Trigger mOnClose;
		WindowHeader& mHeader;
		WindowBody& mBody;
		WindowFooter& mFooter;

		Docksection* mDock;
	};

	class MK_UI_EXPORT WindowForm : public Form
	{
	public:
		WindowForm(unique_ptr<Form> content, const string& title, bool closable = true, bool dockable = false, const Widget::Trigger& onClose = nullptr);
	};
}

#endif
