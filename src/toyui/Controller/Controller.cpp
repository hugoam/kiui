//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Controller/Controller.h>

#include <toyui/Widget/RootSheet.h>

#include <toyui/Input/InputDevice.h>

namespace toy
{
	KeyInputFrame::KeyInputFrame()
		: InputAdapter()
	{}

	bool KeyInputFrame::keyUp(KeyEvent& keyEvent)
	{
		auto it = m_keyUpHandlers.find(keyEvent.code);
		if(it != m_keyUpHandlers.end())
		{
			(*it).second();
			return true;
		}
		return false;
	}

	bool KeyInputFrame::keyDown(KeyEvent& keyEvent)
	{
		auto it = m_keyDownHandlers.find(keyEvent.code);
		if(it != m_keyDownHandlers.end())
		{
			(*it).second();
			return true;
		}
		return false;
	}

	Controller::Controller(ControlMode controlMode, DeviceType deviceType)
		: KeyInputFrame()
		, m_controlMode(controlMode)
		, m_deviceType(deviceType)
		, m_inputWidget(nullptr)
		, m_rootSheet(nullptr)
	{
		m_keyUpHandlers[KC_ESCAPE] = [this]() { this->yield(); };

/*#if 1 // DEBUG
		InputReceiver::m_name = "Controller";
#endif*/
	}

	Controller::~Controller()
	{
		this->yield();
	}

	void Controller::take(Widget& inputWidget)
	{
		m_inputWidget = &inputWidget;
		inputWidget.giveControl(*this, m_controlMode, DEVICE_MOUSE_ALL);
		inputWidget.rootController().takeControl(*this, m_controlMode, DEVICE_KEYBOARD);
		m_rootSheet = &inputWidget.rootSheet();
	}

	void Controller::yield()
	{
		if(!m_inputWidget) return;
		m_rootSheet->m_controller.yieldControl(*this);
		//m_inputWidget->rootController().yieldControl(*this);
		m_inputWidget = nullptr;
	}

	bool Controller::leftClick(MouseEvent& mouseEvent)
	{
		if(m_controlMode < CM_MODAL)
			return false;

		DimFloat local = m_inputWidget->frame().localPosition(mouseEvent.pos);
		if(!m_inputWidget->frame().inside(local))
			this->yield();

		return true;
	}
}
