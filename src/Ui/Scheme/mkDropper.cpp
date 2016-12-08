//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Scheme/mkDropper.h>

namespace mk
{
	Dropper::Dropper(Device& parent, DeviceType& deviceType)
		: Device(parent, deviceType)
	{}

	void Dropper::drop(Device& device, size_t index)
	{
		Dropper& source = static_cast<Dropper&>(*device.parent());
		Device* swap = this->swapdrop(device, source);
		size_t swapindex = device.index();

		if(!this->candrop(device, source))
			return;

		if(swap)
		{
			if(!source.candrop(*swap, *this))
				return;
		}

		source.dropout(device, *this);
		this->dropin(device, source, index);

		if(swap)
		{
			this->dropout(*swap, source);
			source.dropin(*swap, *this, swapindex);
		}
	}
}
