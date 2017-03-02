//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Input/InputDispatcher.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Widget/Sheet.h>

#include <cassert>

namespace toy
{
	InputFrame::InputFrame()
		: m_controller(nullptr)
		, m_controlled(nullptr)
		, m_parentFrame(nullptr)
		, m_controlMode(CM_CONTROL)
		, m_deviceFilter(InputEvent::ALL_DEVICES)
	{}

	InputFrame::~InputFrame()
	{
		if(m_controlled)
			this->yieldControl();
	}

	InputFrame& InputFrame::rootFrame()
	{
		return m_parentFrame->rootFrame();
	}

	InputFrame& InputFrame::rootController()
	{
		if(m_controlled)
			return *this;
		return m_parentFrame->rootController();
	}

	InputReceiver* InputFrame::controlEvent(InputEvent& inputEvent)
	{
		if(m_controller)
			return m_controller->controlEvent(inputEvent);

		return this;
	}

	InputReceiver* InputFrame::propagateEvent(InputEvent& inputEvent)
	{
		return m_parentFrame->controlEvent(inputEvent);
	}

	InputReceiver* InputFrame::dispatchEvent(InputEvent& inputEvent)
	{
		InputFrame& rootReceiver = this->rootFrame();
		InputReceiver* topReceiver = this->controlEvent(inputEvent);
		InputReceiver* consumer = topReceiver;
		InputReceiver* receiver = topReceiver;

		while(receiver != &rootReceiver)
		{
			if(!inputEvent.consumed)
				consumer = receiver->receiveEvent(inputEvent);
			else 
				receiver->receiveEvent(inputEvent);
			if(inputEvent.abort) break;
			receiver = receiver->propagateEvent(inputEvent);
		}

		return consumer;
	}

	InputReceiver* InputFrame::receiveEvent(InputEvent& inputEvent)
	{
		return this->dispatchEvent(inputEvent);
	}

	void InputFrame::takeControl(ControlMode mode, InputEvent::DeviceType device)
	{
		m_controlMode = mode;
		m_deviceFilter = device;
		InputFrame& root = this->rootController();
		if(&root != this)
			this->takeControl(root);
	}

	void InputFrame::takeControl(InputFrame& inputFrame)
	{
		if(inputFrame.m_controller)
			inputFrame.m_controller->yieldControl();

		this->control();
		m_controlled = &inputFrame;
		m_controlled->m_controller = this;

		//printf(">>>>> %s TAKE CONTROL OF %s\n", static_cast<Widget&>(*this).style().name(), static_cast<Widget&>(*m_controlled).style().name());
	}

	void InputFrame::yieldControl()
	{
		m_controlMode = CM_NONE;
		m_deviceFilter = InputEvent::ALL_DEVICES;

		if(!m_controlled)
			return;

		//printf(">>>>> %s YIELD CONTROL OF %s\n", static_cast<Widget&>(*this).style().name(), static_cast<Widget&>(*m_controlled).style().name());

		this->uncontrol();
		m_controlled->m_controller = nullptr;
		m_controlled = nullptr;

	}

	bool InputFrame::consumes(InputEvent::DeviceType device)
	{
		return m_deviceFilter & device;
	}

	void InputWidget::mouseMoved(MouseEvent& mouseEvent)
	{
		if(m_controlMode >= CM_MODAL)
			mouseEvent.abort = true;
	}

	InputReceiver* InputWidget::receiveEvent(InputEvent& inputEvent)
	{
		if(inputEvent.consumed /*&& inputEvent.eventType != InputEvent::EVENT_MOVED*/)
			return this;

		inputEvent.consumed = true;

		if(m_controlMode >= CM_MODAL)
			inputEvent.abort = true;

		inputEvent.visited.push_back(static_cast<Widget*>(this));

		if(inputEvent.deviceType >= InputEvent::DEVICE_MOUSE)
		{
			MouseEvent& mouseEvent = static_cast<MouseEvent&>(inputEvent);
			Frame& frame = static_cast<Widget&>(*this).frame();
			DimFloat absolute = frame.absolutePosition();
			mouseEvent.relativeX = (mouseEvent.posX - absolute[DIM_X]) / frame.scale();
			mouseEvent.relativeY = (mouseEvent.posY - absolute[DIM_Y]) / frame.scale();
		}

		if(inputEvent.deviceType == InputEvent::DEVICE_KEYBOARD && inputEvent.eventType == InputEvent::EVENT_PRESSED)
			this->keyDown(static_cast<KeyEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_KEYBOARD && inputEvent.eventType == InputEvent::EVENT_RELEASED)
			this->keyUp(static_cast<KeyEvent&>(inputEvent));

		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE && inputEvent.eventType == InputEvent::EVENT_MOVED)
			this->mouseMoved(static_cast<MouseEvent&>(inputEvent));

		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE && inputEvent.eventType == InputEvent::EVENT_ENTERED)
			this->mouseEntered(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE && inputEvent.eventType == InputEvent::EVENT_LEAVED)
			this->mouseLeaved(static_cast<MouseEvent&>(inputEvent));

		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_LEFT_BUTTON && inputEvent.eventType == InputEvent::EVENT_STROKED)
			this->leftClick(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_RIGHT_BUTTON && inputEvent.eventType == InputEvent::EVENT_STROKED)
			this->rightClick(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_MIDDLE_BUTTON && inputEvent.eventType == InputEvent::EVENT_STROKED)
			this->middleClick(static_cast<MouseEvent&>(inputEvent));

		else
			inputEvent.abort = true;



		if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_LEFT_BUTTON && inputEvent.eventType == InputEvent::EVENT_PRESSED)
			this->mousePressed(static_cast<MouseEvent&>(inputEvent));
		if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_LEFT_BUTTON && inputEvent.eventType == InputEvent::EVENT_RELEASED)
			this->mouseReleased(static_cast<MouseEvent&>(inputEvent));

		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_MIDDLE_BUTTON && inputEvent.eventType == InputEvent::EVENT_MOVED)
			this->mouseWheel(static_cast<MouseEvent&>(inputEvent));



		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_LEFT_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED_START)
			this->leftDragStart(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_LEFT_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED)
			this->leftDrag(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_LEFT_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED_END)
			this->leftDragEnd(static_cast<MouseEvent&>(inputEvent));


		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_RIGHT_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED_START)
			this->rightDragStart(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_RIGHT_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED)
			this->rightDrag(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_RIGHT_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED_END)
			this->rightDragEnd(static_cast<MouseEvent&>(inputEvent));


		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_MIDDLE_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED_START)
			this->middleDragStart(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_MIDDLE_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED)
			this->middleDrag(static_cast<MouseEvent&>(inputEvent));
		else if(inputEvent.deviceType == InputEvent::DEVICE_MOUSE_MIDDLE_BUTTON && inputEvent.eventType == InputEvent::EVENT_DRAGGED_END)
			this->middleDragEnd(static_cast<MouseEvent&>(inputEvent));

		return this;
	}
}
