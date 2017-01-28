//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UICONFIG_H
#define TOY_UICONFIG_H

#include <toyobj/Config.h>

#if defined UI_EXPORT
#define TOY_UI_EXPORT TOY_EXPORT
#else
#define TOY_UI_EXPORT TOY_IMPORT
#endif

#endif // TOY_UICONFIG_H
