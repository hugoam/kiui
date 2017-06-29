//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_INPUTDISPATCHER_H
#define TOY_INPUTDISPATCHER_H

/* toy */
#include <toyobj/Type.h>
#include <toyobj/Util/Unique.h>
#include <toyui/Forward.h>
#include <toyui/Input/KeyCode.h>

#include <vector>
#include <memory>

namespace toy
{
	enum InputModifier : unsigned int
	{
		INPUT_SHIFT = 1 << 0,
		INPUT_CTRL = 1 << 1,
		INPUT_ALT = 1 << 2
	};

	enum DeviceType : unsigned int
	{
		DEVICE_NONE = 0,
		DEVICE_KEYBOARD = 1 << 0,
		DEVICE_MOUSE = 1 << 1,
		DEVICE_MOUSE_LEFT_BUTTON = 1 << 2,
		DEVICE_MOUSE_RIGHT_BUTTON = 1 << 3,
		DEVICE_MOUSE_MIDDLE_BUTTON = 1 << 4,
		DEVICE_MOUSE_ALL = DEVICE_MOUSE | DEVICE_MOUSE_LEFT_BUTTON | DEVICE_MOUSE_RIGHT_BUTTON | DEVICE_MOUSE_MIDDLE_BUTTON,
		DEVICE_ALL = DEVICE_KEYBOARD | DEVICE_MOUSE_ALL
	};

	enum EventType
	{
		EVENT_NONE,
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

	struct TOY_UI_EXPORT InputEvent
	{
		DeviceType deviceType;
		EventType eventType;
		bool consumed;
		bool abort;
		InputModifier modifiers;

		std::vector<Widget*> visited;

		InputEvent(DeviceType deviceType, EventType eventType) : deviceType(deviceType), eventType(eventType), consumed(false), abort(false) {}
		virtual ~InputEvent() {}

		virtual void dispatch(RootSheet& rootSheet) {}
		virtual bool receive(InputAdapter& receiver) { return false; }
	};

	class TOY_UI_EXPORT InputWindow : public Object
	{
	public:
		virtual bool nextFrame() = 0;

		virtual void initInput(RenderWindow& renderWindow, Mouse& mouse, Keyboard& keyboard) = 0;
		virtual void resize(size_t width, size_t height) = 0;

		static Type& cls() { static Type ty; return ty; }
	};

	enum ControlMode
	{
		CM_WEAK,
		CM_CONTROL,
		CM_MODAL,
		CM_ABSOLUTE
	};

	class TOY_UI_EXPORT InputReceiver
	{
	public:
		InputReceiver() : m_propagate(nullptr) {}

		virtual InputReceiver* controlEvent(InputEvent& inputEvent) { return this; }
		virtual InputReceiver* receiveEvent(InputEvent& inputEvent) = 0;
		virtual InputReceiver* propagateEvent(InputEvent& inputEvent) { return m_propagate; }

		void propagateTo(InputReceiver* propagate) { m_propagate = propagate; }

		virtual void control(bool modal) {};
		virtual void uncontrol(bool modal) {};

	protected:
		InputReceiver* m_propagate;
	};

	class TOY_UI_EXPORT InputAdapter : public InputReceiver
	{
	public:
		InputAdapter();
		~InputAdapter();

		virtual InputReceiver* receiveEvent(InputEvent& inputEvent);

		virtual bool keyUp(KeyEvent& keyEvent) { UNUSED(keyEvent); return false; };
		virtual bool keyStroke(KeyEvent& keyEvent) { UNUSED(keyEvent); return false; };
		virtual bool keyDown(KeyEvent& keyEvent) { UNUSED(keyEvent); return false; };

		virtual bool mouseMoved(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };

		virtual bool mouseEntered(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool mouseLeaved(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };

		virtual bool mousePressed(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return true; };
		virtual bool mouseReleased(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return true; };

		virtual bool mouseWheel(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };

		virtual bool leftClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool rightClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool middleClick(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };

		virtual bool rightDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool rightDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool rightDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };

		virtual bool leftDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool leftDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool leftDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };

		virtual bool middleDragStart(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool middleDrag(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };
		virtual bool middleDragEnd(MouseEvent& mouseEvent) { UNUSED(mouseEvent); return false; };

	protected:
		unique_ptr<ControlNode> m_controlGraph;
	};

	class TOY_UI_EXPORT ControlNode : public Struct//: public InputReceiver
	{
	public:
		ControlNode(InputReceiver& receiver, ControlNode* parent, ControlMode mode, DeviceType device);
		~ControlNode();

		ControlMode controlMode() { return m_controlMode; }
		DeviceType deviceFilter() { return m_device; }

		InputReceiver* dispatchEvent(InputEvent& inputEvent, InputReceiver* topReceiver = nullptr);

		virtual InputReceiver* controlEvent(InputEvent& inputEvent);

		ControlNode* findReceiver(InputReceiver& receiver);

		void takeControl(InputReceiver& receiver, ControlMode mode, DeviceType device);
		void yieldControl(InputReceiver& receiver);

		bool controls(DeviceType device);

	protected:
		InputReceiver* m_receiver;
		ControlNode* m_parent;
		ControlMode m_controlMode;
		DeviceType m_device;

		unique_ptr<ControlNode> m_controller;
	};

	class TOY_UI_EXPORT ControlSwitch : public ControlNode
	{
	public:
		ControlSwitch(InputReceiver& receiver);

		ControlNode& channel(DeviceType device);

		virtual InputReceiver* controlEvent(InputEvent& inputEvent);

		bool takeControl(InputReceiver& receiver, InputReceiver& controller, ControlMode mode, DeviceType channel);
		void takeControl(InputReceiver& receiver, ControlMode mode, DeviceType channels);
		void yieldControl(InputReceiver& receiver);

	protected:
		std::vector<DeviceType> m_channels;
		std::vector<unique_ptr<ControlNode>> m_controllers;
	};
}

#endif // TOY_INPUTDISPATCHER_H
