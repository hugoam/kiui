//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Controller/mkController.h>

#include <Ui/Widget/mkWidget.h>
#include <Ui/Frame/mkInk.h> //@ inclusion-kludge
#include <Ui/mkUiWindow.h>

namespace mk
{
	Controller::Controller()
		: mLower(nullptr)
	{}

	Controller::~Controller()
	{}

	InputReceiver* Controller::controlMouse(float x, float y)
	{
		UNUSED(x); UNUSED(y);
		return this;
	}

	InputReceiver* Controller::controlKey()
	{
		return this;
	}

	InputReceiver* Controller::propagateMouse(float x, float y)
	{
		return mLower->controlMouse(x, y);
	}

	InputReceiver* Controller::propagateKey()
	{
		return mLower->controlKey();
	}

	void Controller::take(Widget* widget)
	{
		mWidget = widget;
		mWidget->uiWindow()->takeControl(this);
	}

	void Controller::stack(Widget* widget)
	{
		mWidget = widget;
		mWidget->uiWindow()->stackControl(this);
	}

	void Controller::yield()
	{
		mWidget->uiWindow()->yieldControl(this);
	}

	bool Controller::keyUp(KeyCode keyCode, char c)
	{
		UNUSED(c);
		auto it = keyUpHandlers.find(keyCode);
		if(it != keyUpHandlers.end())
		{
			(*it).second();
			return true;
		}
		return false;
	}

	bool Controller::keyDown(KeyCode keyCode, char c)
	{
		UNUSED(c);
		auto it = keyDownHandlers.find(keyCode);
		if(it != keyDownHandlers.end())
		{
			(*it).second();
			return true;
		}
		return false;
	}
}
