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

#include <Ui/Scheme/mkTabber.h>
#include <Ui/Scheme/mkDropdown.h>
#include <Ui/Widget/mkButton.h>
#include <Ui/Scheme/mkWindow.h>
#include <Ui/Widget/mkTypeIn.h>
#include <Ui/Widget/mkContextMenu.h>

#include <Ui/Controller/mkController.h>

#include <iostream>

namespace mk
{
	std::map<string, std::function<unique_ptr<Widget>(Form*)>> UiWindow::sDispatch;

	UiWindow::UiWindow(const string& resourcePath, User* user)
		: mResourcePath(resourcePath)
		, mStyler(make_unique<Styler>())
		, mController(nullptr)
		, mShiftPressed(false)
		, mCtrlPressed(false)
		, mShutdownRequested(false)
		, mRootSheet(nullptr)
		, mUser(user)
	{
		mStyler->defaultLayout();
		mStyler->defaultSkins();
	}

	UiWindow::~UiWindow()
	{
		//mRootSheet->clear();
	}

	void UiWindow::setup(RenderWindow& renderWindow, InkWindow& inkWindow, InputWindow* inputWindow)
	{
		mRenderWindow = &renderWindow;
		mInkWindow = &inkWindow;
		mInputWindow = inputWindow;

		mWidth = float(renderWindow.width());
		mHeight = float(renderWindow.height());
	}

	void UiWindow::init()
	{
		mStyler->prepare();

		mRootForm = make_unique<RootForm>(*this);
		mRootSheet = &mRootForm->rootSheet();

		mRootSheet->frame().setSize(mWidth, mHeight);

		mController = mRootSheet;

		this->resize(size_t(mWidth), size_t(mHeight));
	}

	void UiWindow::resize(size_t width, size_t height)
	{
		mWidth = float(width);
		mHeight = float(height);

		if(mInputWindow)
			mInputWindow->resize(width, height);

		if(mRootSheet)
			mRootSheet->frame().setSize(float(width), float(height));
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
