//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Device/Hook.h>
#include <toyui/Device/Stack.h>

#include <toyui/Widget/Button.h>

namespace toy
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
