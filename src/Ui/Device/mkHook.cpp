//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Device/mkHook.h>
#include <Ui/Device/mkStack.h>

#include <Ui/Widget/mkButton.h>

namespace mk
{
	Hook::Hook(Device& parent, Echobject& object)
		: Device(parent, cls())
		, m_echobject(object)
	{}

	Hook::Hook(Device& parent, Object& object, Type& type)
		: Device(parent, cls())
		, m_echobject(object, type)
	{}

	Hook::Hook(Device& parent, TypeObject& object)
		: Device(parent, cls())
		, m_echobject(object, object.type())
	{}

	void Hook::on()
	{
		m_stack->on(m_echobject.object());
	}

	void Hook::off()
	{
		m_stack->off(m_echobject.object());
	}
}
