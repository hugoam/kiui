//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DIAGRAM_H
#define TOY_DIAGRAM_H

/* toy */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>

#include <memory>
#include <functional>
#include <map>

namespace toy
{
	class TOY_UI_EXPORT DeviceMapping
	{
	public:
		DeviceMapping(DeviceMapping* parent = nullptr);

		DeviceMapping& subselector(std::function<Device&(Device&)> selector) { m_subselector = selector; return *this; }
		DeviceMapping& inserter(std::function<Sheet*(Device&)> inserter) { m_inserter = inserter; return *this; }
		DeviceMapping& mapper(std::function<unique_ptr<Widget>(Device&)> mapper) { m_mapper = mapper; return *this; }
		DeviceMapping& unmapper(std::function<Device&(Widget&)> unmapper) { m_unmapper = unmapper; return *this; }
		DeviceMapping& structure(std::function<Sheet&(Device&, Sheet&)> structure) { m_structure = structure; return *this; }
		DeviceMapping& refresh(std::function<void(Device&, Widget&)> refresh) { m_refresh = refresh; return *this; }
		DeviceMapping& postinsert(std::function<void(Device&, Sheet&)> postinsert) { m_postinsert = postinsert; return *this; }

		DeviceMapping& submapper(std::function<Device&(Device&)> subselector)
		{
			m_submappers.push_back(DeviceMapping());
			return m_submappers.back().subselector(subselector);
		}

		void map(Device& device);
		void refresh(Device& device);
		Device& select(Device& parent);

	protected:
		DeviceMapping* m_parent;

		std::function<Device&(Device&)> m_subselector;
		std::function<Sheet*(Device&)> m_inserter;
		std::function<unique_ptr<Widget>(Device&)> m_mapper;
		std::function<Device&(Widget&)> m_unmapper;
		std::function<Sheet&(Device&, Sheet&)> m_structure;
		std::function<void(Device&, Sheet&)> m_postinsert;
		std::function<void(Device&, Widget&)> m_refresh;

		std::vector<DeviceMapping> m_submappers;
	};
	
	template <class T>
	class TDeviceMapping : public DeviceMapping
	{
	public:
	};


}

#endif // TOY_DIAGRAM_H
