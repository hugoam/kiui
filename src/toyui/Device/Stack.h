//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DEVICESTACK_H
#define TOY_DEVICESTACK_H

/* toy */
#include <toyobj/Iterable/VectorObserver.h>
#include <toyui/Forward.h>
#include <toyui/Style/Style.h>
#include <toyui/Device/Device.h>

namespace toy
{
	typedef std::function<void(Object&)> ObjectCallback;
	typedef std::function<unique_ptr<Device>(Stack& stack, Object& object)> DeviceMaker;
	
	template <class T_Device>
	unique_ptr<Device> make_device(Device& parent, Object& object) { UNUSED(parent); return make_unique<T_Device>(parent, object.as<TypeObject>()); }

	template <class T_Object, class T_Device>
	unique_ptr<Device> make_device(Device& parent, Object& object) { UNUSED(parent); return make_unique<T_Device>(parent, object.as<T_Object>()); }

	template <class T_Device>
	unique_ptr<Device> make_object_device(Device& parent, Object& object) { UNUSED(parent); return make_unique<T_Device>(parent, object.as<TypeObject>()); }

	template <class T_Object, class T_Device>
	unique_ptr<Device> make_object_device(Device& parent, Object& object) { UNUSED(parent); return make_unique<T_Device>(parent, object.as<T_Object>(), T_Object::cls()); }

	template <class T_Device>
	unique_ptr<Device> make_ref_device(Device& parent, Lref& lref) { UNUSED(parent); return make_unique<T_Device>(parent, lref); }

	template <class T_Object, class T_Device>
	unique_ptr<Device> make_ref_device(Device& parent, Lref& lref) { UNUSED(parent); return make_unique<T_Device>(parent, lref->as<T_Object>()); }

	template <class T_Object, class T_Device>
	unique_ptr<Device> make_typed_ref_device(Device& parent, Lref& lref) { UNUSED(parent); return make_unique<T_Device>(parent, lref->as<T_Object>(), lref->type()); }

	class TOY_UI_EXPORT StackCallback
	{
	public:
		virtual void on(Object& object) { UNUSED(object); }
		virtual void off(Object& object) { UNUSED(object); }
	};

	class TOY_UI_EXPORT Stack : public Device, public StoreObserver<TypeObject>, public StoreObserver<Object>
	{
	public:
		Stack(Device& parent, DeviceType& deviceType, Type& elementType);
		Stack(Device& parent, DeviceType& deviceType);
		Stack(Device& parent, Type& elementType);
		Stack(Device& parent);

		Stack& maker(DeviceMaker maker);

		template <class T>
		Stack& store(std::vector<T*> objects)
		{
			m_storeObserver = make_unique<ObjectVectorObserver<T>>(objects, *this);
			return *this;
		}

		template <class T>
		Stack& tstore(Store<T>& objects)
		{
			m_storeObserver = make_unique<GenericObserver<T>>(objects, *this);
			return *this;
		}

		Stack& store(ObjectVector objects, Type& type);
		Stack& store(Store<Object>& objects);
		Stack& store(Store<TypeObject>& objects);

		Stack& picker(ObjectCallback callback);
		Stack& selecter(Store<Object>& selection);
		Stack& selecter(Store<TypeObject>& selection);

		void expand();
		void collapse();

		void add(Object& object, Type& type);
		void remove(Object& object, Type& type);

		void handleAdd(TypeObject& object);
		void handleRemove(TypeObject& object);

		void handleAdd(Object& object);
		void handleRemove(Object& object);

		void on(Object& object);
		void off(Object& object);

		Device& mappedDevice(Object& object) const;

		static DeviceType& cls() { static DeviceType ty("Stack", Device::cls()); return ty; }

	protected:
		DeviceMaker m_maker;
		unique_ptr<Observer> m_storeObserver;
		unique_ptr<StackCallback> m_callback;
		Type* m_elementType;

		std::map<Object*, Device*> m_devices;
	};

	class TOY_UI_EXPORT PickCallback : public StackCallback
	{
	public:
		PickCallback(ObjectCallback callback) : m_callback(callback) {}

		virtual void on(Object& object) { m_callback(object); }
		virtual void off(Object& object) { UNUSED(object); }

	protected:
		ObjectCallback m_callback;
	};

	class TOY_UI_EXPORT StoreCallback : public StackCallback
	{
	public:
		StoreCallback(Store<Object>& selection) : m_selection(selection) {}

		virtual void on(Object& object) { m_selection.select(object); }
		virtual void off(Object& object) { m_selection.remove(object); }

	protected:
		Store<Object>& m_selection;
	};

	class TOY_UI_EXPORT SelectCallback : public StackCallback
	{
	public:
		SelectCallback(Store<TypeObject>& selection) : m_selection(selection) {}

		virtual void on(Object& object) { m_selection.select(object.as<TypeObject>()); }
		virtual void off(Object& object) { m_selection.remove(object.as<TypeObject>()); }

	protected:
		Store<TypeObject>& m_selection;
	};
}

#endif // TOY_DIAGRAM_H
