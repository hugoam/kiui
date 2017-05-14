//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Input/InputDispatcher.h>

#include <toyobj/Iterable/Reverse.h>

#include <toyui/Widget/RootSheet.h>
#include <toyui/Widget/Sheet.h>

namespace toy
{
	InputReceiver::InputReceiver()
		: m_controlGraph()
	{}

	InputReceiver::~InputReceiver()
	{}

	InputReceiver* InputReceiver::controlEvent(InputEvent& inputEvent)
	{
		return this;
	}

	InputReceiver* InputReceiver::receiveEvent(InputEvent& inputEvent)
	{
		if(inputEvent.consumed)
			return this;

		inputEvent.receive(*this);
		return this;
	}

	InputReceiver* InputReceiver::propagateEvent(InputEvent& inputEvent)
	{
		return nullptr;
	}

	ControlNode::ControlNode(InputReceiver& receiver, ControlNode* parent, ControlMode mode, DeviceType device)
		: m_receiver(&receiver)
		, m_parent(parent)
		, m_controlMode(mode)
		, m_device(device)
		, m_controller()
	{
		if(parent)
			m_receiver->control();
	}

	ControlNode::~ControlNode()
	{
		m_receiver->uncontrol();
	}

	bool ControlNode::controls(DeviceType device)
	{
		bool filter = m_device & device;
		return filter && m_controlMode >= CM_CONTROL;
	}

	InputReceiver* ControlNode::dispatchEvent(InputEvent& inputEvent, InputReceiver* topReceiver)
	{
		if(!topReceiver)
			topReceiver = this->controlEvent(inputEvent);

		InputReceiver* consumer = topReceiver;
		InputReceiver* receiver = topReceiver;

		while(receiver && receiver != m_receiver)
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

	InputReceiver* ControlNode::controlEvent(InputEvent& inputEvent)
	{
		if(m_controller && m_controller->controls(inputEvent.deviceType))
			return m_controller->controlEvent(inputEvent);

		return m_receiver->controlEvent(inputEvent);
	}

	InputReceiver* ControlNode::receiveEvent(InputEvent& inputEvent)
	{
		return this->dispatchEvent(inputEvent);
	}

	InputReceiver* ControlNode::propagateEvent(InputEvent& inputEvent)
	{
		return m_parent ? m_parent->m_receiver : nullptr;
	}

	ControlNode* ControlNode::findReceiver(InputReceiver& receiver)
	{
		if(m_receiver == &receiver)
			return this;
		else if(m_controller)
			return m_controller->findReceiver(receiver);
		else
			return nullptr;
	}

	void ControlNode::takeControl(InputReceiver& receiver, ControlMode mode, DeviceType device)
	{
		if(m_controller && (mode >= CM_MODAL || m_controller->m_controlMode < CM_MODAL))
			m_controller->takeControl(receiver, mode, device);
		else
			m_controller = make_unique<ControlNode>(receiver, this, mode, static_cast<DeviceType>(m_device & device));
	}

	void ControlNode::yieldControl(InputReceiver& receiver)
	{
		if(m_controller)
			m_controller->yieldControl(receiver);

		if(m_receiver == &receiver)
			m_parent->m_controller = m_controller ? std::move(m_controller) : nullptr;
	}

	ControlSwitch::ControlSwitch(InputReceiver& receiver)
		: ControlNode(receiver, nullptr, CM_CONTROL, DEVICE_ALL)
		, m_channels{ DEVICE_MOUSE_ALL, DEVICE_KEYBOARD }
	{
		for(DeviceType channel : m_channels)
			m_controllers.emplace_back(make_unique<ControlNode>(receiver, nullptr, CM_CONTROL, channel));
	}

	ControlNode& ControlSwitch::channel(DeviceType device)
	{
		for(auto& channel : m_controllers)
			if(channel->deviceFilter() & device)
				return *channel;
	}

	InputReceiver* ControlSwitch::controlEvent(InputEvent& inputEvent)
	{
		for(auto& channel : m_controllers)
			if(channel->controls(inputEvent.deviceType))
				return channel->controlEvent(inputEvent);

		return m_receiver->controlEvent(inputEvent);
	}

	bool ControlSwitch::takeControl(InputReceiver& receiver, InputReceiver& controller, ControlMode mode, DeviceType device)
	{
		ControlNode* controlNode = this->channel(device).findReceiver(controller);
		if(controlNode)
			controlNode->takeControl(receiver, mode, device);
		return controlNode != nullptr;
	}

	void ControlSwitch::takeControl(InputReceiver& receiver, ControlMode mode, DeviceType device)
	{
		for(auto& channel : m_controllers)
			if(channel->deviceFilter() & device)
				channel->takeControl(receiver, mode, device);
	}

	void ControlSwitch::yieldControl(InputReceiver& receiver)
	{
		for(auto& channel : m_controllers)
			channel->yieldControl(receiver);
	}
}
