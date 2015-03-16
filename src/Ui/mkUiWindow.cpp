//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/mkUiWindow.h>

#include <Ui/mkUiLayout.h>

#include <Ui/Form/mkRootForm.h>

#include <Object/String/mkString.h>
#include <Object/Util/mkMake.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>

#include <Ui/Scheme/mkWTabber.h>
#include <Ui/Scheme/mkWDropdown.h>
#include <Ui/Widget/mkWButton.h>
#include <Ui/Scheme/mkWWindow.h>
#include <Ui/Widget/mkWTypeIn.h>
#include <Ui/Widget/mkWContextMenu.h>

#include <Ui/Controller/mkController.h>

#include <iostream>

namespace mk
{
	std::map<string, std::function<unique_ptr<Widget>(Form*)>> UiWindow::sDispatch;

	UiWindow::UiWindow(User* user)
		: mStyler(make_unique<Styler>())
		, mController(this)
		, mDragging(nullptr)
		, mLeftPressed(false)
		, mShiftPressed(false)
		, mCtrlPressed(false)
		, mShutdownRequested(false)
		, mUser(user)
	{
		setupUiLayout(mStyler.get());
	}

	UiWindow::~UiWindow()
	{
		mRootSheet->clear();
	}

	void UiWindow::setup(RenderWindow* renderWindow, InkWindow* inkWindow, InputWindow* inputWindow)
	{
		mRenderWindow = renderWindow;
		mInkWindow = inkWindow;
		mInputWindow = inputWindow;

		mWidth = renderWindow->width();
		mHeight = renderWindow->height();

		mRootForm = make_unique<RootForm>(this);
		mRootSheet = mRootForm->sheet();

		mRootSheet->frame()->setSize(mWidth, mHeight);

		mActiveFrame = mRootSheet;
		mHovered = mRootSheet;
	}

	void UiWindow::init()
	{
		mStyler->prepare();

		mCursor = mRootSheet->makeappend<Cursor>();
		mTooltip = mRootSheet->makeappend<Tooltip>("");

		//mRenderWindow->updateSize();
	}

	void UiWindow::resize(size_t width, size_t height)
	{
		mWidth = float(width);
		mHeight = float(height);

		if(mInputWindow)
			mInputWindow->resize(width, height);

		if(mRootSheet)
			mRootSheet->frame()->setSize(float(width), float(height));
	}

	void UiWindow::activate(Widget* widget)
	{
		mActiveFrame->deactivate();
		mActiveFrame = widget;
	}

	void UiWindow::deactivate(Widget* widget)
	{
		UNUSED(widget);
		mActiveFrame = mRootSheet;
	}

	void UiWindow::unhover()
	{
		mHovered = mRootSheet;
	}

	void UiWindow::contextOn(Widget* contextMenu)
	{
		mContextMenu = contextMenu;
		mContextMenu->frame()->setPosition(mLastX, mLastY);
	}

	void UiWindow::contextOff()
	{
		mContextMenu = nullptr;
	}

	void UiWindow::tooltipOn()
	{
		mTooltip->frame()->show();
		mTooltip->frame()->setPosition(mLastX, mCursor->frame()->dsize(DIM_Y) + mLastY);
	}

	void UiWindow::tooltipOff()
	{
		mTooltip->frame()->hide();
	}

	bool UiWindow::nextFrame()
	{
		mTooltipTimer += mTooltipClock.step();
		if(mTooltipTimer > 0.5f && !mTooltip->frame()->visible() && !mTooltip->label().empty())
			this->tooltipOn();

		size_t tick = mClock.readTick();
		size_t delta = mClock.stepTick();

		mRootSheet->frame()->as<Stripe>()->nextFrame(tick, delta);
		mCursor->nextFrame();

		return !mShutdownRequested;
	}

	void UiWindow::takeControl(Controller* controller)
	{
		if(mController)
			mController->deactivated();
		controller->setLower(this);
		mController = controller;
		mController->activated();
	}

	void UiWindow::stackControl(Controller* controller)
	{
		controller->setLower(mController);
		mController = controller;
		mController->activated();
	}

	void UiWindow::yieldControl(Controller* controller)
	{
		controller->deactivated();
		mController = controller->lower();
	}

	InputReceiver* UiWindow::controlMouse(float x, float y)
	{
		Widget* widget = mRootSheet->pinpoint(x, y);
		return widget;
	}

	InputReceiver* UiWindow::controlKey()
	{
		return mActiveFrame;
	}

	void UiWindow::mousePressed(float x, float y, MouseButton button)
	{
		if(button == LEFT_BUTTON)
		{
			mXDragStart = x;
			mYDragStart = y;
			mLeftPressed = true;
		}
	}

	void UiWindow::mouseMoved(float x, float y, float xDif, float yDif)
	{
		mLastX = x;
		mLastY = y;

		mCursor->setPosition(x, y);

		if(mDragging)
		{
			mDragging->leftDrag(x, y, xDif, yDif);
		}
		else
		{
			InputReceiver* receiver = mController->controlMouse(x, y);

			while(!receiver->mouseMoved(x, y, xDif, yDif))
				receiver = receiver->propagateMouse(x, y);

			if(receiver != mHovered)
			{
				mHovered->mouseLeaved(x, y);
				mCursor->unhover(static_cast<Widget*>(mHovered));

				receiver->mouseEntered(x, y);
				mCursor->hover(static_cast<Widget*>(receiver));

				mHovered = receiver;

				if(mTooltip->frame()->visible())
					this->tooltipOff();

				mTooltipTimer = 0.f;
				mTooltip->setLabel(static_cast<Widget*>(mHovered)->tooltip());
			}

			if(mLeftPressed)
			{
				if(abs(x - mXDragStart) > 8.f || abs(y - mYDragStart) > 8.f)
				{
					/* InputReceiver* */ receiver = mController->controlMouse(mXDragStart, mYDragStart);

					while(!receiver->leftDragStart(mXDragStart, mYDragStart))
						receiver = receiver->propagateMouse(mXDragStart, mYDragStart);

					mDragging = receiver;
					static_cast<Widget*>(mDragging)->frame()->setOpacity(_VOID);
				}
			}
		}
	}

	void UiWindow::mouseReleased(float x, float y, MouseButton button)
	{
		InputReceiver* receiver = mController->controlMouse(x, y);

		if(button == LEFT_BUTTON)
		{
			if(!mDragging)
			{
				while(!receiver->leftClick(x, y))
					receiver = receiver->propagateMouse(x, y);
			}
			else
			{
				mDragging->leftDragEnd(x, y);
				static_cast<Widget*>(mDragging)->frame()->setOpacity(_OPAQUE);
				mDragging = nullptr;
			}

			mLeftPressed = false;
		}
		else if(button == RIGHT_BUTTON)
		{
			while(!receiver->rightClick(x, y))
				receiver = receiver->propagateMouse(x, y);
		}
	}

	void UiWindow::mouseWheeled(float x, float y, float amount)
	{
		InputReceiver* receiver = mController->controlMouse(x, y);

		while(!receiver->mouseWheel(x, y, amount))
			receiver = receiver->propagateMouse(x, y);
	}

	void UiWindow::keyPressed(KeyCode key, char c)
	{
		if(key == KC_ESCAPE)
			mShutdownRequested = true;
		else if(key == KC_LSHIFT || key == KC_RSHIFT)
			mShiftPressed = true;

		InputReceiver* receiver = mController->controlKey();

		while(!receiver->keyDown(key, c))
			receiver = receiver->propagateKey();
	}

	void UiWindow::keyReleased(KeyCode key, char c)
	{
		if(key == KC_LSHIFT || key == KC_RSHIFT)
			mShiftPressed = false;

		InputReceiver* receiver = mController->controlKey();

		while(!receiver->keyUp(key, c))
			receiver = receiver->propagateKey();
	}

	ModalWidget::ModalWidget(Widget* widget)
		: mWidget(widget)
	{
		this->stack(widget);
	}

	ModalWidget::~ModalWidget()
	{
		this->yield();
	}

	InputReceiver* ModalWidget::controlMouse(float x, float y)
	{
		InputReceiver* receiver = mWidget->pinpoint(x, y);
		if(receiver)
			return receiver;
		else
			return mWidget;
	}
	
	InputReceiver* ModalWidget::controlKey()
	{
		return mWidget;
	}

	void UiWindow::modalOn(Widget* widget)
	{
		mModalFrame = widget;
		mModalWidget = make_unique<ModalWidget>(widget);
	}

	void UiWindow::modalOff()
	{
		mModalFrame = nullptr;
		mModalWidget.reset();
	}

	void UiWindow::showCursor()
	{
		mCursor->frame()->show();
	}

	void UiWindow::hideCursor()
	{
		mCursor->frame()->hide();
	}

	void UiWindow::bindCursor(Widget* widget)
	{
		UNUSED(widget);
	}

	void UiWindow::freeCursor()
	{}
}
