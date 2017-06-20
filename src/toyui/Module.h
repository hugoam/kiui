//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UI_MODULE_H
#define TOY_UI_MODULE_H

#include <toyobj/Module/Module.h>
#include <toyui/Generated/Types.h>

namespace toy
{
	class TOY_UI_EXPORT toyui : public Module
	{
	private:
		toyui();

		static toyui instance;

	public:
		static toyui& module() { return instance; }
	};
}

#endif
