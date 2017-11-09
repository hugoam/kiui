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
#include <functional>

namespace toy
{
	struct TOY_UI_EXPORT KeyCombo
	{
		KeyCombo(KeyCode key) : m_key(key) {}
		KeyCombo(KeyCode modifier, KeyCode key) : m_modifier(modifier), m_key(key) {}
		KeyCode m_modifier;
		KeyCode m_key;
		uint64_t value() const { return (uint64_t) m_modifier << 32 | m_key; }
		friend bool operator<(const KeyCombo& lhs, const KeyCombo& rhs) { return lhs.value() < rhs.value(); }
	};

	class TOY_UI_EXPORT KeyInputFrame : public InputAdapter
	{
	public:
		KeyInputFrame();

		virtual bool keyUp(KeyEvent& keyEvent);
		virtual bool keyDown(KeyEvent& keyEvent);

	protected:
		typedef std::function<void()> KeyHandler;

		std::map<KeyCombo, KeyHandler> m_keyDownHandlers;
		std::map<KeyCombo, KeyHandler> m_keyUpHandlers;
	};

	class TOY_UI_EXPORT Controller : public KeyInputFrame
	{
	public:
		Controller(ControlMode controlMode, DeviceType deviceType = DEVICE_ALL);
		~Controller();

		ControlMode controlMode() { return m_controlMode; }

		void take(Widget& inputWidget);
		void yield();

		virtual bool leftClick(MouseEvent& mouseEvent);

	protected:
		ControlMode m_controlMode;
		DeviceType m_deviceType;
		Widget* m_inputWidget;
		RootSheet* m_rootSheet; // @kludge
	};
}

#endif // TOY_CONTROLLER_H
