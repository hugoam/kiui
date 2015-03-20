//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Form/mkForm.h>
#include <Ui/Frame/mkInk.h>
#include <Ui/Frame/mkFrame.h>
#include <Ui/Frame/mkStripe.h>
#include <Ui/Frame/mkLayer.h>

#include <Ui/Widget/mkWScrollbar.h>

#include <Ui/mkUiWindow.h>
#include <Ui/mkUiLayout.h>

#include <Object/Store/mkReverse.h>

#include <iostream>

namespace mk
{
	RootSheet::RootSheet(UiWindow* window, Form* form, bool absolute)
		: Sheet(styleCls(), form)
		, mWindow(window)
		, mDragging(nullptr)
		, mLeftPressed(false)
		, mActiveFrame(this)
		, mHovered(this)
		, mController(this)
	{
		if(absolute)
			mFrame = make_unique<Layer>(nullptr, this, 0);
	}

	void RootSheet::build()
	{
		mCursor = this->makeappend<Cursor>();
		mTooltip = this->makeappend<Tooltip>("");
	}

	void RootSheet::nextFrame(size_t tick, size_t delta)
	{
		Sheet::nextFrame(tick, delta);

		mTooltipTimer += mTooltipClock.step();
		if(mTooltipTimer > 0.5f && !mTooltip->frame()->visible() && !mTooltip->label().empty())
			this->tooltipOn();

		mCursor->nextFrame();
	}

	void RootSheet::activate(Widget* widget)
	{
		mActiveFrame->deactivate();
		mActiveFrame = widget;
	}

	void RootSheet::deactivate(Widget* widget)
	{
		UNUSED(widget);
		mActiveFrame = this;
	}

	void RootSheet::unhover()
	{
		mHovered = this;
	}

	void RootSheet::contextOn(Widget* contextMenu)
	{
		mContextMenu = contextMenu;
		mContextMenu->frame()->setPosition(mLastX, mLastY);
	}

	void RootSheet::contextOff()
	{
		mContextMenu = nullptr;
	}

	void RootSheet::tooltipOn()
	{
		mTooltip->show();
		mTooltip->frame()->setPosition(mLastX, mCursor->frame()->dsize(DIM_Y) + mLastY);
	}

	void RootSheet::tooltipOff()
	{
		mTooltip->hide();
	}

	void RootSheet::modalOn(Widget* widget)
	{
		mModalFrame = widget;
		mModalWidget.modalOn(widget);
	}

	void RootSheet::modalOff()
	{
		mModalFrame = nullptr;
		mModalWidget.modalOff();
	}

	void RootSheet::takeControl(Controller* controller)
	{
		if(mController)
			mController->deactivated();
		controller->setLower(this);
		mController = controller;
		mController->activated();
	}

	void RootSheet::stackControl(Controller* controller)
	{
		controller->setLower(mController);
		mController = controller;
		mController->activated();
	}

	void RootSheet::yieldControl(Controller* controller)
	{
		controller->deactivated();
		mController = controller->lower();
	}

	InputReceiver* RootSheet::controlMouse(float x, float y)
	{
		Widget* widget = this->pinpoint(x, y);
		if(widget == this)
			return this;
		else
			return widget->controlMouse(x, y);
	}

	InputReceiver* RootSheet::controlKey()
	{
		return mActiveFrame;
	}

	bool RootSheet::keyUp(KeyCode code, char c)
	{
		InputReceiver* receiver = mController->controlKey();

		while(receiver != this && !receiver->keyUp(code, c))
			receiver = receiver->propagateKey();
	
		return true;
	}

	bool RootSheet::keyDown(KeyCode code, char c)
	{
		InputReceiver* receiver = mController->controlKey();

		while(receiver != this && !receiver->keyDown(code, c))
			receiver = receiver->propagateKey();

		return true;
	}

	bool RootSheet::mouseMoved(float xPos, float yPos, float xDif, float yDif)
	{
		mLastX = xPos;
		mLastY = yPos;

		mCursor->setPosition(xPos, yPos);

		InputReceiver* receiver = mController->controlMouse(xPos, yPos);

		while(receiver != this && !receiver->mouseMoved(xPos, yPos, xDif, yDif))
			receiver = receiver->propagateMouse(xPos, yPos);

		if(receiver != mHovered)
		{
			mHovered->mouseLeaved(xPos, yPos);
			receiver->mouseEntered(xPos, yPos);

			mHovered = receiver;

			if(mTooltip->frame()->visible())
				this->tooltipOff();

			mTooltipTimer = 0.f;
			mTooltip->setLabel(static_cast<Widget*>(mHovered)->tooltip());
		}

		return true;
	}

	bool RootSheet::mouseWheel(float xPos, float yPos, float amount)
	{
		InputReceiver* receiver = mController->controlMouse(xPos, yPos);

		while(receiver != this && !receiver->mouseWheel(xPos, yPos, amount))
			receiver = receiver->propagateMouse(xPos, yPos);

		return true;
	}

	bool RootSheet::mousePressed(float xPos, float yPos, MouseButton button)
	{
		mLastPressedX = xPos;
		mLastPressedY = yPos;

		InputReceiver* receiver = mController->controlMouse(xPos, yPos);

		while(receiver != this && !receiver->mousePressed(xPos, yPos, button))
			receiver = receiver->propagateMouse(xPos, yPos);
	
		return true;
	}

	bool RootSheet::mouseReleased(float xPos, float yPos, MouseButton button)
	{
		InputReceiver* receiver = mController->controlMouse(xPos, yPos);

		while(receiver != this && !receiver->mouseReleased(xPos, yPos, button))
			receiver = receiver->propagateMouse(xPos, yPos);
	
		return true;
	}

	ModalWidget::ModalWidget()
		: mModals()
	{}

	ModalWidget::~ModalWidget()
	{}

	void ModalWidget::modalOn(Widget* widget)
	{
		mModals.push_back(widget);
		if(mModals.size() == 1)
			this->stack(widget);
	}

	void ModalWidget::modalOff()
	{
		mModals.pop_back();
		if(mModals.size() == 0)
			this->yield();
	}

	InputReceiver* ModalWidget::controlMouse(float x, float y)
	{
		InputReceiver* receiver = mModals.back()->controlMouse(x, y);
		if(receiver)
			return receiver;
		else
			return mModals.back();
	}

	InputReceiver* ModalWidget::controlKey()
	{
		return mModals.back();
	}
}
