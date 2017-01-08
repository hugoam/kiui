//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Device/mkDeviceMapper.h>

#include <Ui/Device/mkDevice.h>
#include <Ui/Widget/mkWidget.h>
#include <Ui/Widget/mkSheet.h>

namespace mk
{
	DeviceMapping::DeviceMapping(DeviceMapping* parent)
		: m_parent(parent)
		, m_inserter([](Device& device) { return device.parent() ? &device.parent()->sheet() : nullptr; })
		, m_mapper([](Device& device) { return make_unique<Sheet>(); })
		, m_postinsert([](Device& device, Sheet& sheet) {})
	{}

	void DeviceMapping::refresh(Device& device)
	{
		if(m_refresh)
			m_refresh(device, device.widget());
	}

	void DeviceMapping::map(Device& device)
	{
		Sheet* sheet = nullptr;
		unique_ptr<Widget> widget = m_mapper(device);

		if(widget->type().upcast(Sheet::cls()))
			sheet = m_structure ? &m_structure(device, widget->as<Sheet>()) : &widget->as<Sheet>();

		Sheet* parent = m_inserter(device);
		device.map(std::move(widget), sheet, parent);

		m_postinsert(device, *sheet);

		for(auto& submapper : m_submappers)
		{
			Device& subdevice = submapper.select(device);
			submapper.map(subdevice);
		}
	}

	Device& DeviceMapping::select(Device& parent)
	{
		return m_subselector(parent);
	}
}
