//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_WWINDOW_H
#define MK_WWINDOW_H

/* mk */
#include <Ui/mkUiForward.h>
#include <Ui/Scheme/mkScheme.h>
#include <Ui/Widget/mkSheet.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Form/mkForm.h>

namespace mk
{
	class MK_UI_EXPORT _I_ WDockWindow : public Object, public Typed<WDockWindow>, public Styled<WDockWindow>
	{};

	class MK_UI_EXPORT _I_ WShrinkWindow : public Object, public Typed<WShrinkWindow>, public Styled<WShrinkWindow>
	{};

	class MK_UI_EXPORT _I_ WWindowHeader : public Sheet, public Typed<WWindowHeader>, public Styled<WWindowHeader>
	{
	public:
		WWindowHeader(WWindow* window);

		void build();

		Style* hoverCursor() { return MoveCursor::styleCls(); }

		WLabel* title() { return mTitle; }
		WButton* closeButton() { return mCloseButton; }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		using Typed<WWindowHeader>::cls;

	protected:
		WWindow* mWindow;
		WLabel* mTitle;
		WButton* mCloseButton;
	};

	class MK_UI_EXPORT _I_ WWindowSizer : public Sheet, public Typed<WWindowSizer>, public Styled<WWindowSizer>
	{
	public:
		WWindowSizer(WWindow* window);

		Style* hoverCursor() { return ResizeCursorDiagRight::styleCls(); }

		bool leftDragStart(float xPos, float yPos);
		bool leftDrag(float xPos, float yPos, float xDif, float yDif);
		bool leftDragEnd(float xPos, float yPos);

		using Typed<WWindowSizer>::cls;

	protected:
		WWindow* mWindow;
		bool mResizeLeft;
	};

	class MK_UI_EXPORT _I_ WWindowBody : public Sheet, public Typed<WWindowBody>, public Styled<WWindowBody>
	{
	public:
		WWindowBody();

		using Typed<WWindowBody>::cls;
	};

	class MK_UI_EXPORT _I_ WCloseButton : public WButton, public Typed<WCloseButton>, public Styled<WCloseButton>
	{
	public:
		WCloseButton(const Trigger& trigger);

		using Typed<WCloseButton>::cls;
		using Styled<WCloseButton>::styleCls;
	};

	class MK_UI_EXPORT WWindow : public Sheet, public Styled<WWindow>
	{
	public:
		WWindow(const Trigger& onClose, string title, bool closable = true, bool dockable = false, WDocksection* dock = nullptr);
		~WWindow();

		void build();

		const string& name();

		FrameType frameType() { return LAYER; }
		bool dockable() { return mDockable; }
		bool movable() { return mMovable; }
		bool closable() { return mClosable; }

		WDocksection* dock() { return mDock; }

		void toggleClosable();
		void toggleMovable();
		void toggleResizable();
		void showTitlebar();
		void hideTitlebar();

		bool leftClick(float x, float y);
		bool rightClick(float x, float y);

		Widget* vappend(unique_ptr<Widget> widget);
		//unique_ptr<Widget> vrelease(Widget* widget);

		void dock(WDocksection* docksection);
		void undock();

		void close();

	protected:
		string mName;
		bool mClosable;
		bool mDockable;
		bool mMovable;
		bool mSizable;
		Widget* mContent;
		Trigger mOnClose;
		WWindowHeader* mHeader;
		WWindowBody* mBody;
		WWindowSizer* mFooter;

		WDocksection* mDock;
	};

	class MK_UI_EXPORT Window : public Form
	{
	public:
		Window(unique_ptr<Form> content, bool closable = true, bool dockable = false, const Trigger& onClose = nullptr);

		void onClose(Widget* widget);

	protected:
		Trigger mOnClose;
	};
}

#endif
