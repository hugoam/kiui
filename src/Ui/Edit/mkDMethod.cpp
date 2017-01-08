#include <Ui/mkUiConfig.h>
#include <Ui/Edit/mkDMethod.h>

#include <Object/Reflect/mkMethod.h>

#include <Ui/Widget/mkValue.h>
#include <Ui/Widget/mkRootSheet.h>

#include <Ui/Edit/mkDValueEdit.h>

#include <Ui/Device/mkRootDevice.h>

#include <iostream>

namespace mk
{
	DParam::DParam(Device& parent, Lref& arg, string argName)
		: Device(parent, cls())
		, m_name(argName)
	{
		this->append(DValueEdit::dispatch(*this, arg));
	}

	DMethodCall::DMethodCall(Device& parent, Method& method, Object& object, Type& type)
		: Device(parent, cls())
		, m_method(method)
		, m_object(object)
		, m_type(type)
		, m_args(method.arguments())
	{
		this->emplace<Response>(method.name(), std::bind(&DMethodCall::call, this));

		for(size_t i = 0; i < m_args.size(); ++i)
			m_params.push_back(&this->emplace<DParam>(m_args[i], method.param(i).name()));
	}

	void DMethodCall::call()
	{
		m_method.call(m_object, m_args);
	}

	DMethod::DMethod(Device& parent, Method& method, Object& object, Type& type)
		: Device(parent, cls())
		, m_methodCall(this->emplace<DMethodCall>(method, object, type))
	{}

	DMethod::DMethod(Device& parent, Echomethod& echomethod)
		: DMethod(parent, echomethod.method(), echomethod.echobject().object(), echomethod.echobject().type())
	{}
}