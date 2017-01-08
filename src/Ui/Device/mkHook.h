//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_HOOK_H
#define MK_HOOK_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Object/mkObjectForward.h>
#include <Object/Reflect/mkEcho.h>
#include <Ui/Device/mkStack.h>

namespace mk
{
	class MK_UI_EXPORT _I_ Hook : public Device
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

#endif // MK_HOOK_H
