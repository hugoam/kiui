//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_CONTROLLER_H
#define TOY_CONTROLLER_H

/* toy */
#include <toyui/Input/KeyCode.h>
#include <toyui/Input/InputDispatcher.h>

/* std */
#include <map>
#include <vector>
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT KeyInputFrame : public InputAdapter
	{
	public:
		KeyInputFrame();

		void keyUp(KeyEvent& keyEvent);
		void keyDown(KeyEvent& keyEvent);

	protected:
		typedef std::function<void()> KeyHandler;
		typedef std::map<KeyCode, KeyHandler> KeyMap;

		KeyMap m_keyDownHandlers;
		KeyMap m_keyUpHandlers;
	};

	class TOY_UI_EXPORT Controller : public KeyInputFrame
	{
	public:
		Controller(ControlMode controlMode, DeviceType deviceType = DEVICE_ALL);

		ControlMode controlMode() { return m_controlMode; }

		void take(Widget& inputWidget);
		void yield();

		virtual void leftClick(MouseEvent& mouseEvent);

	protected:
		ControlMode m_controlMode;
		DeviceType m_deviceType;
		Widget* m_inputWidget;
	};
}

#endif // TOY_CONTROLLER_H
