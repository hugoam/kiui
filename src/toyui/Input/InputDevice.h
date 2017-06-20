//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUTDEVICE_H
#define TOY_INPUTDEVICE_H

/* toy */
#include <toyobj/Object.h>
#include <toyui/Input/KeyCode.h>
#include <toyui/Input/InputDispatcher.h>
#include <toyui/Forward.h>
#include <toyui/Widget/RootSheet.h>

#include <vector>

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
		MouseButton(Mouse& mouse, DeviceType deviceType);

		InputReceiver* pressed() { return m_pressed; }
		float pressedX() { return m_pressedX; }
		float pressedY() { return m_pressedY; }

		void mousePressed(float x, float y);
		void mouseMoved(MouseEvent& mouseEvent);
		void mouseReleased(float x, float y);

		void dragStart(MouseEvent& mouseEvent);
		void dragEnd(MouseEvent& mouseEvent);
		void dragMove(MouseEvent& mouseEvent);
		void click(MouseEvent& mouseEvent);

		void handleUnbindWidget(Widget& widget, bool destroy);
		void handleBindWidget(Widget& widget);

	protected:
		Mouse& m_mouse;
		DeviceType m_deviceType;

		InputReceiver* m_pressed;
		InputReceiver* m_prevPressed;
		bool m_dragging;

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
		void dispatchMouseMoved(float x, float y);
		void dispatchMouseReleased(float x, float y, MouseButtonCode button);
		void dispatchMouseWheeled(float x, float y, float amount);

		void mouseFocus(float x, float y, std::vector<Widget*>& inputFrame);

		void handleUnbindWidget(Widget& widget, bool destroy);
		void handleBindWidget(Widget& widget);

	protected:
		MouseButton m_leftButton;
		MouseButton m_rightButton;
		MouseButton m_middleButton;

		float m_lastX;
		float m_lastY;
		
		std::vector<Widget*> m_focused;
	};

	struct TOY_UI_EXPORT KeyDownEvent : public KeyEvent
	{
		KeyDownEvent(KeyCode code, char c) : KeyEvent(DEVICE_KEYBOARD, EVENT_PRESSED, code, c) {}

		virtual void dispatch(RootSheet& rootSheet) { rootSheet.keyboard().dispatchKeyPressed(code, c); }
		virtual bool receive(InputAdapter& receiver) { return receiver.keyDown(*this); }
	};

	struct TOY_UI_EXPORT KeyUpEvent : public KeyEvent
	{
		KeyUpEvent(KeyCode code, char c) : KeyEvent(DEVICE_KEYBOARD, EVENT_RELEASED, code, c) {}

		virtual void dispatch(RootSheet& rootSheet) { rootSheet.keyboard().dispatchKeyReleased(code, c); }
		virtual bool receive(InputAdapter& receiver) { return receiver.keyUp(*this); }
	};

	struct TOY_UI_EXPORT KeyCharEvent : public KeyEvent
	{
		KeyCharEvent(KeyCode code, char c) : KeyEvent(DEVICE_KEYBOARD, EVENT_STROKED, code, c) {}

		//virtual void dispatch(RootSheet& rootSheet) { rootSheet.keyboard().dispatchKeyReleased(code, c); }
		virtual bool receive(InputAdapter& receiver) { return receiver.keyStroke(*this); }
	};

	struct TOY_UI_EXPORT MouseMoveEvent : public MouseEvent
	{
		MouseMoveEvent(float x, float y) : MouseEvent(DEVICE_MOUSE, EVENT_MOVED, x, y) {}

		virtual void dispatch(RootSheet& rootSheet) { rootSheet.mouse().dispatchMouseMoved(posX, posY); }
		virtual bool receive(InputAdapter& receiver) { return receiver.mouseMoved(*this); }
	};

	struct TOY_UI_EXPORT MousePressEvent : public MouseEvent
	{
		MousePressEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_PRESSED, x, y) {}

		virtual void dispatch(RootSheet& rootSheet) { rootSheet.mouse().dispatchMousePressed(posX, posY, button); }
		virtual bool receive(InputAdapter& receiver) { return receiver.mousePressed(*this); consumed = true; }
	};

	struct TOY_UI_EXPORT MouseReleaseEvent : public MouseEvent
	{
		MouseReleaseEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_RELEASED, x, y) {}

		virtual void dispatch(RootSheet& rootSheet) { rootSheet.mouse().dispatchMouseReleased(posX, posY, button); }
		virtual bool receive(InputAdapter& receiver) { return receiver.mouseReleased(*this); }
	};

	struct TOY_UI_EXPORT MouseWheelEvent : public MouseEvent
	{
		MouseWheelEvent(float x, float y, float amount) : MouseEvent(DEVICE_MOUSE_MIDDLE_BUTTON, EVENT_MOVED, x, y) { deltaZ = amount; }

		virtual void dispatch(RootSheet& rootSheet) { rootSheet.mouse().dispatchMouseWheeled(posX, posY, deltaZ); }
		virtual bool receive(InputAdapter& receiver) { return receiver.mouseWheel(*this); }
	};

	struct TOY_UI_EXPORT MouseClickEvent : public MouseEvent
	{
		MouseClickEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_STROKED, x, y) {}
		virtual bool receive(InputAdapter& receiver) {	if(deviceType == DEVICE_MOUSE_LEFT_BUTTON)
															return receiver.leftClick(*this);
														else if(deviceType == DEVICE_MOUSE_RIGHT_BUTTON)
															return receiver.rightClick(*this);
														else if(deviceType == DEVICE_MOUSE_MIDDLE_BUTTON)
															return receiver.middleClick(*this); }
	};

	struct TOY_UI_EXPORT MouseDragEvent : public MouseEvent
	{
		MouseDragEvent(DeviceType deviceType, float x, float y, float dx, float dy) : MouseEvent(deviceType, EVENT_DRAGGED, x, y) { deltaX = dx; deltaY = dy; }

		virtual bool receive(InputAdapter& receiver) {	if(deviceType == DEVICE_MOUSE_LEFT_BUTTON)
															return receiver.leftDrag(*this);
														else if(deviceType == DEVICE_MOUSE_RIGHT_BUTTON)
															return receiver.rightDrag(*this);
														else if(deviceType == DEVICE_MOUSE_MIDDLE_BUTTON)
															return receiver.middleDrag(*this); }
	};

	struct TOY_UI_EXPORT MouseDragStartEvent : public MouseEvent
	{
		MouseDragStartEvent(DeviceType deviceType, float x, float y, float startX, float startY) : MouseEvent(deviceType, EVENT_DRAGGED_START, x, y) { lastPressedX = startX; lastPressedY = startY; }
	
		virtual bool receive(InputAdapter& receiver) {	if(deviceType == DEVICE_MOUSE_LEFT_BUTTON)
															return receiver.leftDragStart(*this);
														else if(deviceType == DEVICE_MOUSE_RIGHT_BUTTON)
															return receiver.rightDragStart(*this);
														else if(deviceType == DEVICE_MOUSE_MIDDLE_BUTTON)
															return receiver.middleDragStart(*this); }
	};

	struct TOY_UI_EXPORT MouseDragEndEvent : public MouseEvent
	{
		MouseDragEndEvent(DeviceType deviceType, float x, float y) : MouseEvent(deviceType, EVENT_DRAGGED_END, x, y) {}

		virtual bool receive(InputAdapter& receiver) {	if(deviceType == DEVICE_MOUSE_LEFT_BUTTON)
															return receiver.leftDragEnd(*this);
														else if(deviceType == DEVICE_MOUSE_RIGHT_BUTTON)
															return receiver.rightDragEnd(*this);
														else if(deviceType == DEVICE_MOUSE_MIDDLE_BUTTON)
															return receiver.middleDragEnd(*this); }
	};

	struct TOY_UI_EXPORT MouseEnterEvent : public MouseEvent
	{
		MouseEnterEvent(float x, float y) : MouseEvent(DEVICE_MOUSE, EVENT_ENTERED, x, y) {}

		virtual bool receive(InputAdapter& receiver) { return receiver.mouseEntered(*this); }
	};

	struct TOY_UI_EXPORT MouseLeaveEvent : public MouseEvent
	{
		MouseLeaveEvent(float x, float y) : MouseEvent(DEVICE_MOUSE, EVENT_LEAVED, x, y) {}

		virtual bool receive(InputAdapter& receiver) { return receiver.mouseLeaved(*this); }
	};

}

#endif // TOY_INPUTDEVICE_H
