#include <toyui/Config.h>
#include <toyui/Edit/DMethod.h>

#include <toyobj/Reflect/Method.h>

#include <toyui/Widget/Value.h>
#include <toyui/Widget/RootSheet.h>

#include <toyui/Edit/DValueEdit.h>

#include <toyui/Device/RootDevice.h>

#include <iostream>

namespace toy
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