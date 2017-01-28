//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Device/Device.h>

#include <toyobj/String/StringConvert.h>
#include <toyobj/Iterable/Reverse.h>

#include <toyui/Device/RootDevice.h>
#include <toyui/Device/Stack.h>

#include <toyui/Frame/Frame.h>
#include <toyui/Widget/Widget.h>
#include <toyui/Widget/Sheet.h>

#include <assert.h>

namespace toy
{
	DeviceType::DeviceType(const string& name)
		: Type(TYPE, name)
		, m_ownmapping(make_unique<DeviceMapping>())
		, m_mapping(&*m_ownmapping)
	{}

	DeviceType::DeviceType(const string& name, DeviceType& base, bool inheritMapping)
		: Type(base, TYPE, name)
		, m_ownmapping(make_unique<DeviceMapping>(&base.mapping()))
		, m_mapping(inheritMapping ? &*base.m_ownmapping : &*m_ownmapping)
	{}

	Device::Device(Device& parent, DeviceType& deviceType)
		: TypeObject(deviceType)
		, m_deviceType(deviceType)
		, m_parent(&parent)
		, m_stack(parent.type().upcast(Stack::cls()) ? &parent.as<Stack>() : nullptr)
		, m_index(0)
		, m_mapping(nullptr)
		, m_mapped(false)
		, m_widget(nullptr)
		, m_sheet(nullptr)
	{

	}

	Device::Device(DeviceType& deviceType, Sheet& sheet)
		: TypeObject(deviceType)
		, m_deviceType(deviceType)
		, m_parent(nullptr)
		, m_stack(nullptr)
		, m_index(0)
		, m_mapping(nullptr)
		, m_mapped(false)
		, m_widget(&sheet)
		, m_sheet(&sheet)
	{
	}

	Device::~Device()
	{
		m_widget->resetDevice();
		m_contents.clear();
	}

	RootDevice& Device::rootDevice()
	{
		return m_parent ? m_parent->rootDevice() : this->as<RootDevice>();
	}

	UiWindow& Device::uiWindow()
	{
		return this->rootDevice().uiWindow();
	}

	DeviceMapper& Device::deviceMapper()
	{
		return this->rootDevice().deviceMapper();
	}

	User& Device::user()
	{
		return this->rootDevice().user();
	}

	void Device::destroy()
	{
		m_parent->remove(*this);
	}

	void Device::mapping(DeviceMapping& mapping)
	{
		m_mapping = &mapping;
	}

	void Device::refresh()
	{
		if(m_mapped)
			m_mapping ? m_mapping->refresh(*this) : m_deviceType.mapping().refresh(*this);
	}

	void Device::map()
	{
		if(!m_mapped)
			m_mapping ? m_mapping->map(*this) : m_deviceType.mapping().map(*this);

		this->refresh();

		for(auto& device : m_contents)
			device->map();
	}

	void Device::map(unique_ptr<Widget> widgetPtr, Sheet* sheet, Sheet* parent)
	{
		m_widget = widgetPtr.get();
		m_sheet = sheet;
		m_mapped = true;

		m_widget->setDevice(*this);

		if(parent)
			parent->vappend(std::move(widgetPtr));
	}

	void Device::stack(Stack& stack)
	{
		m_stack = &stack;
	}

	Device& Device::append(unique_ptr<Device> devicePtr)
	{
		assert(devicePtr->m_parent == this);

		Device& device = *devicePtr;
		m_contents.emplace_back(std::move(devicePtr));

		if(m_mapped && !device.m_mapped)
			device.map();

		return device;
	}

	void Device::remove(Device& device)
	{
		auto pred = [&device](const unique_ptr<Device>& pt) { return &device == pt.get(); };
		m_contents.erase(std::remove_if(m_contents.begin(), m_contents.end(), pred), m_contents.end());
	}

	void Device::popback()
	{
		m_contents.pop_back();
	}

	void Device::clear()
	{
		for(auto& device : m_contents)
			device->m_widget->remove();
		m_contents.clear();
	}

	void Device::nextFrame(size_t tick, size_t delta)
	{
		UNUSED(tick); UNUSED(delta);
	}

	EmptyDevice::EmptyDevice(Device& parent)
		: Device(parent, cls())
	{}

	Response::Response(Device& parent, const string& name, Callback callback)
		: Device(parent, cls())
		, m_name(name)
		, m_callback(callback)
	{}

	void Response::trigger()
	{
		m_callback();
	}
}
