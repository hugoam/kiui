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
		auto it = m_keyUpHandlers.find(keyEvent.code);
		if(it != m_keyUpHandlers.end())
		{
			(*it).second();
			keyEvent.consumed = true;
		}
	}

	void KeyInputFrame::keyDown(KeyEvent& keyEvent)
	{
		auto it = m_keyDownHandlers.find(keyEvent.code);
		if(it != m_keyDownHandlers.end())
		{
			(*it).second();
			keyEvent.consumed = true;
		}
	}

	Controller::Controller(ControlMode controlMode, InputEvent::DeviceType deviceType)
		: KeyInputFrame()
		, m_controlMode(controlMode)
		, m_deviceType(deviceType)
		, m_inputWidget(nullptr)
	{
		m_keyUpHandlers[KC_ESCAPE] = [this]() { this->yield(); };
	}

	void Controller::take(Widget& inputWidget)
	{
		m_parentFrame = &inputWidget;
		m_inputWidget = &inputWidget;
		InputFrame::m_controlMode = m_controlMode;
		inputWidget.takeControl(m_controlMode, m_deviceType);
		this->takeControl(m_controlMode, m_deviceType);
	}

	void Controller::yield()
	{
		this->yieldControl();
		m_inputWidget->yieldControl();
		m_parentFrame = nullptr;
		m_inputWidget = nullptr;
	}

	void Controller::leftClick(MouseEvent& mouseEvent)
	{
		DimFloat local = m_inputWidget->frame().localPosition(mouseEvent.posX, mouseEvent.posY);
		if(!m_inputWidget->frame().inside(local.x(), local.y()))
			this->yield();
	}
}
