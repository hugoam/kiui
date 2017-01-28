//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.
#ifndef TOY_FNEWOBJECT_H
#define TOY_FNEWOBJECT_H

/* toy */
#include <toyobj/Store/Array.h>
#include <toyobj/Reflect/Injector.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>

namespace toy
{
	class TOY_UI_EXPORT DRootObjectCreate : public Device
	{
	public:
		DRootObjectCreate(Device& parent);

		Stack& types() { return m_types; }

		void selectType(Type& type);

		static DeviceType& cls() { static DeviceType ty("DRootObjectCreate", Device::cls()); return ty; }

	private:
		Array<Type> m_rootTypes;
		Stack& m_types;
		Device* m_objectCreate;
	};

	class TOY_UI_EXPORT DCreateArg : public Device
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

	class TOY_UI_EXPORT DProtoCreate : public Device
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

	class TOY_UI_EXPORT DObjectCreate : public Device
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

#endif // TOY_FNEWOBJECT_H
