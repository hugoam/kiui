#ifndef MK_FNEWOBJECT_H
#define MK_FNEWOBJECT_H

/* mk */
#include <Object/Store/mkArray.h>
#include <Object/Reflect/mkInjector.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkDevice.h>

namespace mk
{
	class MK_UI_EXPORT DRootObjectCreate : public Device
	{
	public:
		DRootObjectCreate(Device& parent);

		Stack& types() { return m_types; }

		void selectType(Type& type);

		static DeviceType& cls() { static DeviceType ty("DRootObjectCreate", Device::cls()); return ty; }

	private:
		Array<Type> m_rootTypes;
		Stack& m_types;
		Type* m_type;
		Device* m_objectCreate;
	};

	class MK_UI_EXPORT DCreateArg : public Device
	{
	public:
		DCreateArg(Device& parent, Member& member, Lref& lref);

		Member& member() { return m_member; }

		static DeviceType& cls() { static DeviceType ty("DCreateArg", Device::cls()); return ty; }

	protected:
		Member& m_member;
		Lref m_value;
		DValue& m_device;
	};

	class MK_UI_EXPORT DProtoCreate : public Device
	{
	public:
		DProtoCreate(Device& parent, Type& type);

		Stack& prototypes() { return m_prototypes; }

		void selectProto(Type& type);

	protected:
		Type& m_type;
		Stack& m_prototypes;
		Type* m_prototype;
		DObjectCreate* m_objectCreate;
	};

	class MK_UI_EXPORT DObjectCreate : public Device
    {
    public:
		DObjectCreate(Device& parent, Type& type);

		void createObject();
		void destroyObject();
		void cancel();

		static DeviceType& cls() { static DeviceType ty("DObjectCreate", Device::cls()); return ty; }

    private:
		Type& m_type;
		Injector m_injector;
		Stack& m_values;

		Response& m_create;
		//Response& m_cancel;

    };

}

#endif // MK_FNEWOBJECT_H
