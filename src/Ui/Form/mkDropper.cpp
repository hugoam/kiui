//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <Ui/mkUiConfig.h>
#include <Ui/Form/mkDropper.h>

namespace mk
{
	Dropper::Dropper()
		: mForm()
	{}

	void Dropper::drop(Form* form, size_t index)
	{
		Dropper* source = nullptr; // @todo : form->parent()->as<Dropper>();
		Form* swap = this->swapdrop(form, source);
		size_t swapindex = form->index();

		if(!this->candrop(form, source))
			return;

		if(swap)
		{
			if(!source->candrop(swap, this))
				return;
		}

		source->dropout(form, this);
		this->dropin(form, source, index);

		if(swap)
		{
			this->dropout(swap, source);
			source->dropin(swap, this, swapindex);
		}
	}
}
