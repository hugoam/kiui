//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DEVICE_H
#define TOY_DEVICE_H

/* toy */
#include <toyobj/Typed.h>
#include <toyobj/Ref.h>
#include <toyobj/Indexer.h>
#include <toyobj/Util/Updatable.h>
#include <toyobj/Util/Unique.h>
#include <toyui/Forward.h>
#include <toyui/Style/Style.h>
#include <toyui/Device/DeviceMapper.h>

#include <map>

namespace toy
{
	class TOY_UI_EXPORT DeviceType : public Type
	{
	public:
		DeviceType(const string& name);
		DeviceType(const string& name, DeviceType& base, bool inheritMapping = false);

		DeviceMapping& mapping() { return *m_mapping; }

		void map(DeviceMapping& mapping) { m_mapping = &mapping; }
		DeviceMapping& map() { m_mapping = &*m_ownmapping; return *m_ownmapping; }

	protected:
		unique_ptr<DeviceMapping> m_ownmapping;
		DeviceMapping* m_mapping;
	};

	class _I_ TOY_UI_EXPORT Device : public TypeObject, public Updatable
	{
	public:
		Device(Device& parent, DeviceType& deviceType);
		~Device();

		Device* parent() { return m_parent; }
		Id index() const { return m_index; }
		size_t update() const { return m_update; }
		std::vector<unique_ptr<Device>>& contents() { return m_contents; }

		Widget& widget() { return *m_widget; }
		Sheet& sheet() { return *m_sheet; }

		RootDevice& rootDevice();
		UiWindow& uiWindow();
		User& user();
		DeviceMapper& deviceMapper();

		void refresh();

		void stack(Stack& stack);

		void mapping(DeviceMapping& mapping);

		void map();
		void map(unique_ptr<Widget> widget, Sheet* sheet, Sheet* parent);

		Device& append(unique_ptr<Device> device);
		void remove(Device& device);
		void popback();
		void clear();
		void destroy();

		void nextFrame(size_t tick, size_t delta);

		static DeviceType& cls() { static DeviceType ty("Device"); return ty; }

	public:
		template <class T, class... Args>
		inline T& emplace(Args&&... args) { return this->append(make_unique<T>(*this, std::forward<Args>(args)...)).template as<T>(); }

	protected:
		Device(DeviceType& type, Sheet& sheet);

	protected:
		DeviceType& m_deviceType;
		Device* m_parent;
		Stack* m_stack;
		size_t m_index;
		size_t m_update;

		DeviceMapping* m_mapping;
		bool m_mapped;

		Widget* m_widget;
		Sheet* m_sheet;

		std::vector<unique_ptr<Device>> m_contents;
		//std::map<Device*, Widget*> m_mappedWidgets;
	};

	typedef std::function<void()> Callback;

	class TOY_UI_EXPORT EmptyDevice : public Device
	{
	public:
		EmptyDevice(Device& parent);

		static DeviceType& cls() { static DeviceType ty("EmptyDevice", Device::cls()); return ty; }
	};

	class TOY_UI_EXPORT Response : public Device
	{
	public:
		Response(Device& parent, const string& name, Callback callback);

		const string& name() { return m_name; }
		
		void trigger();

		static DeviceType& cls() { static DeviceType ty("Response", Device::cls()); return ty; }

	protected:
		string m_name;
		Callback m_callback;
	};
}

#endif // TOY_DEVICE_H
