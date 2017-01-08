#ifndef MK_DOBJECTEDIT_H
#define MK_DOBJECTEDIT_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/Store/mkArray.h>
#include <Object/Reflect/mkEcho.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkDevice.h>
#include <Ui/Widget/mkValue.h>
#include <Ui/Device/mkStack.h>
#include <Ui/Edit/mkDValueEdit.h>

/* Standard */
#include <functional>

namespace mk
{
	class MK_UI_EXPORT DMemberEdit : public Device
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

	class MK_UI_EXPORT DObjectEdit : public DValue
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

	class MK_UI_EXPORT DPartEdit : public Device
	{
	public:
		DPartEdit(Device& parent, Echobject& object);
		DPartEdit(Device& parent, Object& object, Type& type);

		DObjectEdit& objectEdit() { return m_objectEdit; }

		static DeviceType& cls() { static DeviceType ty("DPartEdit", Device::cls()); return ty; }

	protected:
		DObjectEdit& m_objectEdit;
	};

	class MK_UI_EXPORT DModularEdit : public Device
	{
	public:
		DModularEdit(Device& parent, Echobject& object);

		static DeviceType& cls() { static DeviceType ty("DModularEdit", Device::cls()); return ty; }

	protected:
		DObjectEdit& m_objectEdit;
		Stack& m_parts;
	};

	class MK_UI_EXPORT DEdit : public Device
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

#endif // MK_DOBJECTEDIT_H
