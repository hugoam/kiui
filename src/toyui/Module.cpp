//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <toyui/Config.h>
#include <toyui/Module.h>

#define TOYUI_REFLECTION_IMPL
#include <toyui/Generated/Meta.h>

namespace toy
{
	toyui toyui::instance;

	toyui::toyui()
		: Module()
	{
		toyuiCarbon(*this);
	}
}
