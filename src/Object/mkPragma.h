//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_PRAGMA_H
#define MK_PRAGMA_H

#if _MSC_VER
#	pragma warning (disable : 4251) // members are private, so there's no risk them being accessed by the user
#	pragma warning (disable : 4512) // objects cannot be copied / assigned anyway
#endif

#endif // MK_PRAGMA_H
