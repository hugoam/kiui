//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_STYLEPARSER_H
#define TOY_STYLEPARSER_H

/* toy */
#include <toyui/Types.h>
#include <toyobj/Util/Unique.h>
#include <toyui/Style/Style.h>

namespace toy
{
	TOY_UI_EXPORT void load_default_style_sheet(Styler& styler);
	TOY_UI_EXPORT void load_style_sheet(Styler& styler, const string& path);
}

#endif // TOY_STYLEPARSER_H
