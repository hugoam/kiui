//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUTDISPATCHER_H
#define TOY_INPUTDISPATCHER_H

/* toy */
#include <toyui/Forward.h>
#include <toyui/Input/KeyCode.h>

#include <vector>

#undef CM_NONE

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

		DeviceType deviceType;
		EventType eventType;
		bool consumed;
		bool abort;

		std::vector<Widget*> visited;

		InputEvent(DeviceType deviceType, EventType eventType) : deviceType(deviceType), eventType(eventType), consumed(false), abort(false) {}
		virtual ~InputEvent() {}

		virtual void dispatch(RootSheet& rootSheet) {}
	};

	struct TOY_UI_EXPORT MouseEvent : public InputEvent
	{
		float posX;
		float posY;
		float relativeX;
		float relativeY;
		float deltaX;
		float deltaY;
		float deltaZ;
		float lastPressedX;
		float lastPressedY;

		MouseButtonCode button;

		MouseEvent(DeviceType deviceType, EventType eventType, float x, float y)
			: InputEvent(deviceType, eventType)
			, posX(x), posY(y), deltaX(0.f), deltaY(0.f), deltaZ(0.f)
			, lastPressedX(0.f), lastPressedY(0.f), button(NO_BUTTON)
		{
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

	class TOY_UI_EXPORT InputWindow
	{
	public:
		virtual bool nextFrame() = 0;

		virtual void initInput(Mouse& mouse, Keyboard& keyboard) = 0;
		virtual void resize(size_t width, size_t height) = 0;
	};

	class TOY_UI_EXPORT InputReceiver
	{
	public:
		enum ControlMode
		{
			CM_NONE,
			CM_CONTROL,
			CM_MODAL,
			CM_ABSOLUTE
		};

		virtual InputReceiver* dispatchEvent(InputEvent& inputEvent) { UNUSED(inputEvent); return this; }
		virtual InputReceiver* controlEvent(InputEvent& inputEvent) { UNUSED(inputEvent); return this; }
		virtual InputReceiver* receiveEvent(InputEvent& inputEvent) { UNUSED(inputEvent); return this; }
		virtual InputReceiver* propagateEvent(InputEvent& inputEvent) { UNUSED(inputEvent); return this; }

		virtual void takeControl(ControlMode mode, InputEvent::DeviceType device = InputEvent::ALL_DEVICES) = 0;
		virtual void yieldControl() = 0;
	};

	class TOY_UI_EXPORT InputFrame : public InputReceiver
	{
	public:
		InputFrame();
		~InputFrame();

		InputFrame* parentFrame() { return m_parentFrame; }

		virtual InputFrame& rootFrame();
		virtual InputFrame& rootController();

		InputReceiver* dispatchEvent(InputEvent& inputEvent);
		InputReceiver* controlEvent(InputEvent& inputEvent);
		InputReceiver* receiveEvent(InputEvent& inputEvent);
		InputReceiver* propagateEvent(InputEvent& inputEvent);

		void takeControl(ControlMode mode, InputEvent::DeviceType device = InputEvent::ALL_DEVICES);
		void takeControl(InputFrame& inputFrame);
		void yieldControl();

		bool consumes(InputEvent::DeviceType device);

		virtual void control() {};
		virtual void uncontrol() {};

		virtual void modal() {};
		virtual void unmodal() {};

	protected:
		InputFrame* m_controller;
		InputFrame* m_controlled;
		InputFrame* m_parentFrame;
		ControlMode m_controlMode;
		InputEvent::DeviceType m_deviceFilter;
	};


	class TOY_UI_EXPORT InputWidget : public InputFrame
	{
	public:
		InputReceiver* receiveEvent(InputEvent& inputEvent);

		virtual void keyUp(KeyEvent& keyEvent) { UNUSED(keyEvent); };
		virtual void keyDown(KeyEvent& keyEvent) { UNUSED(keyEvent); };

		virtual void mouseMoved(MouseEvent& mouseEvent);

		virtual void mouseEntered(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void mouseLeaved(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void mousePressed(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void mouseReleased(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void mouseWheel(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void leftClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void rightClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void middleClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void rightDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void rightDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void rightDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void leftDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void leftDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void leftDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };

		virtual void middleDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void middleDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
		virtual void middleDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); };
	};
}

#endif // TOY_INPUTDISPATCHER_H
