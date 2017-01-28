//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.
#ifndef TOY_DMETHOD_H
#define TOY_DMETHOD_H

/* toy */
#include <toyobj/Typed.h>
#include <toyobj/Procedure.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>

namespace toy
{
	class TOY_UI_EXPORT DParam : public Device
	{
	public:
		DParam(Device& parent, Lref& arg, string argName);

		const string& name();

		static DeviceType& cls() { static DeviceType ty("DParam", Device::cls()); return ty; }

	protected:
		string m_name;
	};

	class TOY_UI_EXPORT DMethodCall : public Device
	{
	public:
		DMethodCall(Device& parent, Method& method, Object& object, Type& type);

		void call();

		static DeviceType& cls() { static DeviceType ty("DMethodCall", Device::cls()); return ty; }

	protected:
		Method& m_method;
		Object& m_object;
		Type& m_type;
		LrefVector m_args;
		std::vector<DParam*> m_params;
	};

	class TOY_UI_EXPORT DMethod : public Device
	{
	public:
		DMethod(Device& parent, Method& method, Object& object, Type& type);
		DMethod(Device& parent, Echomethod& method);

		static DeviceType& cls() { static DeviceType ty("DMethod", Device::cls()); return ty; }

	protected:
		DMethodCall& m_methodCall;
	};
}

#endif // TOY_DMETHOD_H
