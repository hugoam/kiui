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
	class MK_UI_EXPORT _I_ DockWindow : public Object, public Typed<DockWindow>, public Styled<DockWindow>
	{};

	class MK_UI_EXPORT _I_ ShrinkWindow : public Object, public Typed<ShrinkWindow>, public Styled<ShrinkWindow>
	{};

	class MK_UI_EXPORT _I_ WindowHeader : public Sheet, public Typed<WindowHeader>, public Styled<WindowHeader>
	{
	public:
		WindowHeader(Window* window);

		Style* hoverCursor() { return MoveCursor::styleCls(); }
		const string& tooltip() { return mTooltip; }

		Label* title() { return mTitle; }
		Button* closeButton() { return mCloseButton; }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		using Typed<WindowHeader>::cls;

	protected:
		Window* mWindow;
		Label* mTitle;
		Button* mCloseButton;
		string mTooltip;
	};

	class MK_UI_EXPORT _I_ WindowSizer : public Sheet, public Typed<WindowSizer>, public Styled<WindowSizer>
	{
	public:
		WindowSizer(Window* window);

		Style* hoverCursor() { return ResizeCursorDiagRight::styleCls(); }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		using Typed<WindowSizer>::cls;

	protected:
		Window* mWindow;
		bool mResizeLeft;
	};

	class MK_UI_EXPORT _I_ WindowBody : public Sheet, public Typed<WindowBody>, public Styled<WindowBody>
	{
	public:
		WindowBody();

		using Typed<WindowBody>::cls;
	};

	class MK_UI_EXPORT _I_ CloseButton : public Button, public Typed<CloseButton>, public Styled<CloseButton>
	{
	public:
		CloseButton(const Trigger& trigger);

		using Typed<CloseButton>::cls;
		using Styled<CloseButton>::styleCls;
	};

	class MK_UI_EXPORT Window : public Sheet, public Styled<Window>
	{
	public:
		Window(const string& title, bool closable = true, bool dockable = false, const Trigger& onClose = nullptr, Docksection* dock = nullptr);
		~Window();

		const string& name();

		bool dockable() { return mDockable; }
		bool movable() { return mMovable; }
		bool closable() { return mClosable; }
		
		WindowBody* body() { return mBody; }
		Docksection* dock() { return mDock; }

		void bind(Sheet* parent, size_t index);

		void toggleClosable();
		void toggleMovable();
		void toggleResizable();
		void showTitlebar();
		void hideTitlebar();

		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

		Widget* vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget* widget);

		void dock(Docksection* docksection);
		void undock();

		void docked();
		void undocked();

		void close();

	protected:
		string mName;
		bool mClosable;
		bool mDockable;
		bool mMovable;
		bool mSizable;
		Widget* mContent;
		Trigger mOnClose;
		WindowHeader* mHeader;
		WindowBody* mBody;
		WindowSizer* mFooter;

		Docksection* mDock;
	};
}

#endif
