//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_PRAGMA_H_INCLUDED
#define MK_PRAGMA_H_INCLUDED

#if OGRE_COMPILER == OGRE_COMPILER_MSVC
#	pragma warning (disable : 4251) // members are private, so there's no risk them being accessed by the user
#	pragma warning (disable : 4231) // 'nonstandard' extension is now part of C++11 standard, so this warning is useless
#	pragma warning (disable : 4275) // @kludge because of Vector3 and Quaternion inheriting from statically linked LinearMath.lib
#endif

#endif // MK_PRAGMA_H_INCLUDED
