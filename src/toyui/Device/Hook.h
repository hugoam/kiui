//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_HOOK_H
#define TOY_HOOK_H

/* toy headers */
#include <toyobj/Typed.h>
#include <toyobj/Forward.h>
#include <toyobj/Reflect/Echo.h>
#include <toyui/Device/Stack.h>

namespace toy
{
	class _I_ TOY_UI_EXPORT Hook : public Device
	{
	public:
		Hook(Device& parent, Echobject& echobject);
		Hook(Device& parent, Object& object, Type& type);
		Hook(Device& parent, TypeObject& object);

		Echobject& echobject() { return m_echobject; }
		Object& object() { return m_echobject.object(); }
		Type& objectType() { return m_echobject.type(); }

		void on();
		void off();

		static DeviceType& cls() { static DeviceType ty("Hook", Device::cls()); return ty; }

	protected:
		Echobject m_echobject;
	};
}

#endif // TOY_HOOK_H
