//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Device/mkStack.h>

#include <Object/String/mkStringConvert.h>
#include <Object/Iterable/mkReverse.h>

#include <Ui/Frame/mkFrame.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

#include <Ui/Device/mkHook.h>

namespace mk
{
	Stack::Stack(Device& parent, DeviceType& deviceType, Type& elementType)
		: Device(parent, deviceType)
		, m_maker([&elementType](Device& parent, Object& object) { UNUSED(parent); return make_unique<Hook>(parent, object, elementType); })
		, m_elementType(&elementType)
	{}

	Stack::Stack(Device& parent, DeviceType& deviceType)
		: Device(parent, deviceType)
		, m_maker(&make_object_device<Hook>)
	{}

	Stack::Stack(Device& parent, Type& elementType)
		: Device(parent, cls())
		, m_maker([&elementType](Device& parent, Object& object) { UNUSED(parent); return make_unique<Hook>(parent, object, elementType); })
	{}

	Stack::Stack(Device& parent)
		: Device(parent, cls())
		, m_maker(&make_object_device<Hook>)
	{}

	Stack& Stack::maker(DeviceMaker maker)
	{
		m_maker = maker;
		return *this;
	}

	Stack& Stack::store(ObjectVector objects, Type& type)
	{
		m_elementType = &type;
		for(Object* object : objects)
			this->add(*object, type);
		return *this;
	}
	
	Stack& Stack::store(Store<TypeObject>& objects)
	{
		objects.observe(*this);
		return *this;
	}

	Stack& Stack::store(Store<Object>& objects)
	{
		m_elementType = &objects.elementType();
		objects.observe(*this);
		return *this;
	}

	Stack& Stack::picker(ObjectCallback callback)
	{
		m_callback = make_unique<PickCallback>(callback);
		return *this;
	}

	Stack& Stack::selecter(Store<Object>& selection)
	{
		m_callback = make_unique<StoreCallback>(selection);
		return *this;
	}

	Stack& Stack::selecter(Store<TypeObject>& selection)
	{
		m_callback = make_unique<SelectCallback>(selection);
		return *this;
	}

	void Stack::expand()
	{}

	void Stack::collapse()
	{}

	void Stack::add(Object& object, Type& type)
	{
		std::unique_ptr<Device> device = m_maker(*this, object);
		device->stack(*this);
		m_devices[&object] = device.get();
		this->append(std::move(device));
	}

	void Stack::remove(Object& object, Type& type)
	{
		Device& device = *m_devices[&object];
		this->as<Device>().remove(device);
		m_devices.erase(m_devices.find(&object));
	}

	void Stack::on(Object& object)
	{
		m_callback->on(object);
	}

	void Stack::off(Object& object)
	{
		m_callback->off(object);
	}

	void Stack::handleAdd(TypeObject& object)
	{
		this->add(object, object.type());
	}

	void Stack::handleRemove(TypeObject& object)
	{
		this->remove(object, object.type());
	}

	void Stack::handleAdd(Object& object)
	{
		this->add(object, *m_elementType);
	}

	void Stack::handleRemove(Object& object)
	{
		this->remove(object, *m_elementType);
	}

	Device& Stack::mappedDevice(Object& object) const
	{
		return *m_devices.at(&object);
	}

	/*void Stack::nextFrame(size_t tick, size_t delta)
	{
		bool updated = false;
		for(auto& member : m_contents)
			if(member->update() > m_update)
				updated = true;

		if(updated)
			this->updateDevices();
	}*/
}
