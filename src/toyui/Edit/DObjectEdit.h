#ifndef TOY_DOBJECTEDIT_H
#define TOY_DOBJECTEDIT_H

/* toy headers */
#include <toyobj/Typed.h>
#include <toyobj/Store/Array.h>
#include <toyobj/Reflect/Echo.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>
#include <toyui/Widget/Value.h>
#include <toyui/Device/Stack.h>
#include <toyui/Edit/DValueEdit.h>

/* std */
#include <functional>

namespace toy
{
	class TOY_UI_EXPORT DMemberEdit : public Device
	{
	public:
		DMemberEdit(Device& parent, Echomember& member);

		Echomember& member() { return m_member; }

		void assign();
		void collect();

		static DeviceType& cls() { static DeviceType ty("DMemberEdit", Device::cls()); return ty; }

	protected:
		Echomember& m_member;
		Lref m_lref;
		Lref& m_value;
		DValue& m_device;
	};

	class TOY_UI_EXPORT DObjectEdit : public DValue
	{
	public:
		DObjectEdit(Device& parent, Echobject& object);
		DObjectEdit(Device& parent, Object& object, Type& type);

		Object& object() { return m_object.object(); }
		Type& type() { return m_object.type(); }

		//void updateDevices();

		void updateDevice();
		void updateObject();

		//void updateMembers(LrefVector& args);

		void handleValueChanged();

		static DeviceType& cls() { static DeviceType ty("DObjectEdit", Device::cls()); return ty; }

	protected:
		Echobject m_instance;
		Echobject& m_object;

		Stack& m_members;
	};

	class TOY_UI_EXPORT DPartEdit : public Device
	{
	public:
		DPartEdit(Device& parent, Echobject& object);
		DPartEdit(Device& parent, Object& object, Type& type);

		DObjectEdit& objectEdit() { return m_objectEdit; }

		static DeviceType& cls() { static DeviceType ty("DPartEdit", Device::cls()); return ty; }

	protected:
		DObjectEdit& m_objectEdit;
	};

	class TOY_UI_EXPORT DModularEdit : public Device
	{
	public:
		DModularEdit(Device& parent, Echobject& object);

		static DeviceType& cls() { static DeviceType ty("DModularEdit", Device::cls()); return ty; }

	protected:
		DObjectEdit& m_objectEdit;
		Stack& m_parts;
	};

	class TOY_UI_EXPORT DEdit : public Device
	{
	public:
		DEdit(Device& parent);

		void edit(Object& object, Type& type);
		void edit(Echobject& echobject);

		static DeviceType& cls() { static DeviceType ty("DEdit", Device::cls()); return ty; }

	protected:
		DObjectEdit* m_objectEdit;
	};
}

#endif // TOY_DOBJECTEDIT_H
