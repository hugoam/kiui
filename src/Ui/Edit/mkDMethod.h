#ifndef MK_DMETHOD_H
#define MK_DMETHOD_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkProcedure.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkDevice.h>

namespace mk
{
	class MK_UI_EXPORT DParam : public Device
	{
	public:
		DParam(Device& parent, Lref& arg, string argName);

		const string& name();

		static DeviceType& cls() { static DeviceType ty("DParam", Device::cls()); return ty; }

	protected:
		string m_name;
	};

	class MK_UI_EXPORT DMethodCall : public Device
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

	class MK_UI_EXPORT DMethod : public Device
	{
	public:
		DMethod(Device& parent, Method& method, Object& object, Type& type);
		DMethod(Device& parent, Echomethod& method);

		static DeviceType& cls() { static DeviceType ty("DMethod", Device::cls()); return ty; }

	protected:
		DMethodCall& m_methodCall;
	};
}

#endif // MK_DMETHOD_H
