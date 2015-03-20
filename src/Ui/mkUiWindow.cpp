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
#include <Ui/Widget/mkRootSheet.h>

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
		, mController(nullptr)
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

		mController = mRootSheet;
	}

	void UiWindow::init()
	{
		mStyler->prepare();
		mRootSheet->build();

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

	bool UiWindow::nextFrame()
	{
		size_t tick = mClock.readTick();
		size_t delta = mClock.stepTick();

		mRootSheet->nextFrame(tick, delta);
		return !mShutdownRequested;
	}

	void UiWindow::dispatchMousePressed(float x, float y, MouseButton button)
	{
		mRootSheet->mousePressed(x, y, button);
	}

	void UiWindow::dispatchMouseMoved(float x, float y, float xDif, float yDif)
	{
		mRootSheet->mouseMoved(x, y, xDif, yDif);
	}

	void UiWindow::dispatchMouseReleased(float x, float y, MouseButton button)
	{
		mRootSheet->mouseReleased(x, y, button);
	}

	void UiWindow::dispatchMouseWheeled(float x, float y, float amount)
	{
		mRootSheet->mouseWheel(x, y, amount);
	}

	void UiWindow::dispatchKeyPressed(KeyCode key, char c)
	{
		if(key == KC_ESCAPE)
			mShutdownRequested = true;
		else if(key == KC_LSHIFT || key == KC_RSHIFT)
			mShiftPressed = true;

		mRootSheet->keyDown(key, c);
	}

	void UiWindow::dispatchKeyReleased(KeyCode key, char c)
	{
		if(key == KC_LSHIFT || key == KC_RSHIFT)
			mShiftPressed = false;

		mRootSheet->keyUp(key, c);
	}
}
