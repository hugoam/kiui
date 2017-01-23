//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_DROPPER_H
#define TOY_DROPPER_H

/* toy headers */
#include <toyobj/Typed.h>
#include <toyui/Forward.h>
#include <toyui/Device/Device.h>

namespace toy
{
	class TOY_UI_EXPORT Dropper : public Device
	{
	public:
		Dropper(Device& parent, DeviceType& deviceType);

		void drop(Device& device, size_t position);

	protected:
		virtual Device* swapdrop(Device& device, Dropper& source) = 0;
		virtual bool candrop(Device& device, Dropper& source) = 0;
		virtual void dropin(Device& device, Dropper& source, size_t index) = 0;
		virtual void dropout(Device& device, Dropper& source) = 0;
	};
}

#endif // TOY_DROPPER_H
