//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Controller/Controller.h>

#include <toyui/Widget/Widget.h>
#include <toyui/Widget/RootSheet.h>

namespace toy
{
	KeyInputFrame::KeyInputFrame()
		: InputWidget()
	{}

	void KeyInputFrame::keyUp(KeyEvent& keyEvent)
	{
		auto it = keyUpHandlers.find(keyEvent.code);
		if(it != keyUpHandlers.end())
		{
			(*it).second();
			keyEvent.consumed = true;
		}
	}

	void KeyInputFrame::keyDown(KeyEvent& keyEvent)
	{
		auto it = keyDownHandlers.find(keyEvent.code);
		if(it != keyDownHandlers.end())
		{
			(*it).second();
			keyEvent.consumed = true;
		}
	}

	Controller::Controller(ControlMode controlMode)
		: KeyInputFrame()
		, m_controlMode(controlMode)
		, m_inputWidget(nullptr)
	{}

	void Controller::take(Widget& inputWidget)
	{
		m_inputWidget = &inputWidget;
		InputFrame::m_controlMode = m_controlMode;
		this->takeControl(inputWidget);
	}

	void Controller::yield()
	{
		m_inputWidget = nullptr;
		this->yieldControl();
	}

}
