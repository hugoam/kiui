//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUTDEVICE_H
#define TOY_INPUTDEVICE_H

/* toy */
#include <toyobj/Object.h>
#include <toyui/Input/KeyCode.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/Style/Dim.h>
#include <toyui/Forward.h>

#include <vector>
#include <array>

namespace toy
{
	class TOY_UI_EXPORT InputDevice : public Object
	{
	public:
		InputDevice(RootSheet& rootSheet);

		RootSheet& rootSheet() { return m_rootSheet; }

		static Type& cls() { static Type ty; return ty; }

	protected:
		RootSheet& m_rootSheet;
		ControlNode& m_rootFrame;
	};

	class TOY_UI_EXPORT Keyboard : public InputDevice
	{
	public:
		Keyboard(RootSheet& rootSheet);

		bool shiftPressed() { return m_shiftPressed; }
		bool ctrlPressed() { return m_ctrlPressed; }

		void dispatchKeyPressed(KeyCode key, char c);
		void dispatchKeyReleased(KeyCode key, char c);

	protected:
		bool m_shiftPressed;
		bool m_ctrlPressed;
	};

	class TOY_UI_EXPORT MouseButton : public InputDevice
	{
	public:
		MouseButton(Mouse& mouse, DeviceType deviceType);

		void mousePressed(DimFloat pos);
		void mouseMoved(MouseEvent& mouseEvent);
		void mouseReleased(DimFloat pos);

		void dragStart(MouseEvent& mouseEvent);
		void dragEnd(MouseEvent& mouseEvent);
		void dragMove(MouseEvent& mouseEvent);
		void click(MouseEvent& mouseEvent);

	protected:
		Mouse& m_mouse;
		DeviceType m_deviceType;

		InputReceiver* m_pressed;
		InputReceiver* m_prevPressed;
		bool m_dragging;

		DimFloat m_pressedPos;
	};

	class TOY_UI_EXPORT Mouse : public InputDevice
	{
	public:
		Mouse(RootSheet& rootSheet);

		DimFloat lastPos() { return m_lastPos; }

		void transformMouseEvent(MouseEvent& mouseEvent);

		void dispatchMousePressed(DimFloat pos, MouseButtonCode button);
		void dispatchMouseMoved(DimFloat pos);
		void dispatchMouseReleased(DimFloat pos, MouseButtonCode button);
		void dispatchMouseWheeled(DimFloat pos, float amount);

		void mouseFocus(DimFloat pos, std::vector<Widget*>& inputFrame);

		void handleDestroyWidget(Widget& widget);

	protected:
		std::array<MouseButton, 3> m_buttons;

		DimFloat m_lastPos;
		
		std::vector<Widget*> m_focused;
	};

	struct TOY_UI_EXPORT MouseEvent : public InputEvent
	{
		DimFloat pos;
		DimFloat relative;
		DimFloat delta;
		float deltaZ;
		DimFloat lastPressed;

		MouseButtonCode button;

		MouseEvent(Mouse& mouse, DeviceType deviceType, EventType eventType, DimFloat pos)
			: InputEvent(deviceType, eventType)
			, pos(pos), delta(0.f, 0.f), deltaZ(0.f)
			, lastPressed(0.f, 0.f), button(NO_BUTTON)
		{
			mouse.transformMouseEvent(*this);

			if(deviceType == DEVICE_MOUSE_LEFT_BUTTON)
				button = LEFT_BUTTON;
			else if(deviceType == DEVICE_MOUSE_RIGHT_BUTTON)
				button = RIGHT_BUTTON;
			else if(deviceType == DEVICE_MOUSE_MIDDLE_BUTTON)
				button = MIDDLE_BUTTON;
		}
	};

	struct TOY_UI_EXPORT KeyEvent : public InputEvent
	{
		KeyCode code;
		char c;

		KeyEvent(DeviceType deviceType, EventType eventType, KeyCode code, char c)
			: InputEvent(deviceType, eventType), code(code), c(c)
		{}
	};
}

#endif // TOY_INPUTDEVICE_H
