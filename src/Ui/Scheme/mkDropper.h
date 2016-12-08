//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_DROPPER_H
#define MK_DROPPER_H

/* mk headers */
#include <Object/mkTyped.h>
#include <Ui/mkUiForward.h>
#include <Ui/Device/mkDevice.h>

namespace mk
{
	class MK_UI_EXPORT Dropper : public Device
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

#endif // MK_DROPPER_H
