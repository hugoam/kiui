//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUTDEVICE_H
#define TOY_INPUTDEVICE_H

/* toy */
#include <toyobj/Object.h>
#include <toyui/Input/KeyCode.h>
#include <toyui/Forward.h>

#include <vector>

namespace toy
{
	struct TOY_UI_EXPORT InputEvent
	{
		enum DeviceType : unsigned int
		{
			DEVICE_KEYBOARD = 1 << 0,
			DEVICE_MOUSE = 1 << 1,
			DEVICE_MOUSE_LEFT_BUTTON = 1 << 2,
			DEVICE_MOUSE_RIGHT_BUTTON = 1 << 3,
			DEVICE_MOUSE_MIDDLE_BUTTON = 1 << 4,
			ALL_DEVICES = DEVICE_KEYBOARD | DEVICE_MOUSE | DEVICE_MOUSE_LEFT_BUTTON | DEVICE_MOUSE_RIGHT_BUTTON | DEVICE_MOUSE_MIDDLE_BUTTON
		};

		enum EventType
		{
			EVENT_ENTERED,
			EVENT_LEAVED,
			EVENT_PRESSED,
			EVENT_RELEASED,
			EVENT_MOVED,
			EVENT_STROKED,
			EVENT_DRAGGED,
			EVENT_DRAGGED_START,
			EVENT_DRAGGED_END
		};

		InputFrame* rootFrame;
		DeviceType deviceType;
		EventType eventType;
		bool consumed;
		bool abort;

		std::vector<Widget*> visited;

		InputEvent(DeviceType deviceType, EventType eventType) : rootFrame(nullptr), deviceType(deviceType), eventType(eventType), consumed(false), abort(false) {}
	};

	struct TOY_UI_EXPORT KeyEvent : public InputEvent
	{
		KeyCode code;
		char c;

		KeyEvent(DeviceType deviceType, EventType eventType, KeyCode code, char c) : InputEvent(deviceType, eventType), code(code), c(c) {}
	};

	struct TOY_UI_EXPORT KeyDownEvent : public KeyEvent
	{
		KeyDownEvent(KeyCode code, char c) : KeyEvent(DEVICE_KEYBOARD, EVENT_PRESSED, code, c) {}
	};

	struct TOY_UI_EXPORT KeyUpEvent : public KeyEvent
	{
		KeyUpEvent(KeyCode code, char c) : KeyEvent(DEVICE_KEYBOARD, EVENT_RELEASED, code, c) {}
	};

	struct TOY_UI_EXPORT KeyCharEvent : public KeyEvent
	{
		KeyCharEvent(KeyCode code, char c) : KeyEvent(DEVICE_KEYBOARD, EVENT_STROKED, code, c) {}
	};

	struct TOY_UI_EXPORT MouseEvent : public InputEvent
	{
		float posX;
		float posY;
		float deltaX;
		float deltaY;
		float deltaZ;
		float lastPressedX;
		float lastPressedY;

		MouseButtonCode button;

		MouseEvent(DeviceType deviceType, EventType eventType, float x, float y) : InputEvent(deviceType, eventType), posX(x), posY(y), deltaX(0.f), deltaY(0.f), deltaZ(0.f), lastPressedX(0.f), lastPressedY(0.f), button(NO_BUTTON) {}
	};

	struct TOY_UI_EXPORT MouseMoveEvent : public MouseEvent
	{
		MouseMoveEvent(float x, float y) : MouseEvent(DEVICE_MOUSE, EVENT_MOVED, x, y) {}
	};

	struct TOY_UI_EXPORT MousePressEvent : public MouseEvent
	{
		MousePressEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_PRESSED, x, y) {}
	};

	struct TOY_UI_EXPORT MouseReleaseEvent : public MouseEvent
	{
		MouseReleaseEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_RELEASED, x, y) {}
	};

	struct TOY_UI_EXPORT MouseWheelEvent : public MouseEvent
	{
		MouseWheelEvent(float x, float y, float amount) : MouseEvent(DEVICE_MOUSE_MIDDLE_BUTTON, EVENT_MOVED, x, y) { deltaZ = amount; }
	};

	struct TOY_UI_EXPORT MouseClickEvent : public MouseEvent
	{
		MouseClickEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_STROKED, x, y) {}
	};

	struct TOY_UI_EXPORT MouseDragEvent : public MouseEvent
	{
		MouseDragEvent(DeviceType deviceType, float x, float y, float dx, float dy) : MouseEvent(deviceType, EVENT_DRAGGED, x, y) { deltaX = dx; deltaY = dy; }
	};

	struct TOY_UI_EXPORT MouseDragStartEvent : public MouseEvent
	{
		MouseDragStartEvent(DeviceType deviceType, float x, float y, float startX, float startY) : MouseEvent(deviceType, EVENT_DRAGGED_START, x, y) { lastPressedX = startX; lastPressedY = startY; }
	};

	struct TOY_UI_EXPORT MouseDragEndEvent : public MouseEvent
	{
		MouseDragEndEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_DRAGGED_END, x, y) {}
	};

	struct TOY_UI_EXPORT MouseEnterEvent : public MouseEvent
	{
		MouseEnterEvent(float x, float y) : MouseEvent(DEVICE_MOUSE, EVENT_ENTERED, x, y) {}
	};

	struct TOY_UI_EXPORT MouseLeaveEvent : public MouseEvent
	{
		MouseLeaveEvent(float x, float y) : MouseEvent(DEVICE_MOUSE, EVENT_LEAVED, x, y) {}
	};

	class TOY_UI_EXPORT InputDevice
	{
	public:
		InputDevice(RootSheet& rootSheet);

		RootSheet& rootSheet() { return m_rootSheet; }

	protected:
		RootSheet& m_rootSheet;
		InputFrame& m_rootFrame;
	};

	class TOY_UI_EXPORT Keyboard : public InputDevice
	{
	public:
		Keyboard(RootSheet& rootSheet);

		bool shiftPressed() { return m_shiftPressed; }
		bool ctrlPressed() { return m_ctrlPressed; }

		void nextFrame();

		void dispatchKeyPressed(KeyCode key, char c);
		void dispatchKeyReleased(KeyCode key, char c);

	protected:
		bool m_shiftPressed;
		bool m_ctrlPressed;
	};

	class TOY_UI_EXPORT MouseButton : public InputDevice
	{
	public:
		MouseButton(Mouse& mouse, InputEvent::DeviceType deviceType);

		InputReceiver* pressedFrame() { return m_pressedFrame; }
		float pressedX() { return m_pressedX; }
		float pressedY() { return m_pressedY; }

		void mousePressed(float x, float y);
		void mouseMoved(MouseMoveEvent& mouseEvent);
		void mouseReleased(float x, float y);

		void dragStart(MouseEvent& mouseEvent);
		void dragEnd(MouseEvent& mouseEvent);
		void dragMove(MouseEvent& mouseEvent);
		void click(MouseEvent& mouseEvent);

		void handleDestroyWidget(Widget& widget);

	protected:
		Mouse& m_mouse;
		InputEvent::DeviceType m_deviceType;

		bool m_pressed;
		bool m_dragging;

		InputReceiver* m_pressedFrame;
		float m_pressedX;
		float m_pressedY;
	};

	class TOY_UI_EXPORT Mouse : public InputDevice
	{
	public:
		Mouse(RootSheet& rootSheet);

		float lastX() { return m_lastX; }
		float lastY() { return m_lastY; }

		void nextFrame();

		void transformMouseEvent(MouseEvent& mouseEvent);

		void dispatchMousePressed(float x, float y, MouseButtonCode button);
		void dispatchMouseMoved(float x, float y, float xDif, float yDif);
		void dispatchMouseReleased(float x, float y, MouseButtonCode button);
		void dispatchMouseWheeled(float x, float y, float amount);

		void mouseFocus(float x, float y, std::vector<Widget*>& inputFrame);

		void handleDestroyWidget(Widget& widget);

	protected:
		MouseButton m_leftButton;
		MouseButton m_rightButton;
		MouseButton m_middleButton;

		float m_lastX;
		float m_lastY;
		
		std::vector<Widget*> m_focused;
	};
}

#endif // TOY_INPUTDEVICE_H
