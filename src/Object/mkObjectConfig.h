//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_OBJECTCONFIG_H_INCLUDED
#define MK_OBJECTCONFIG_H_INCLUDED

#include <Object/mkPragma.h>

#ifdef _WIN32
	#define _CRT_SECURE_NO_DEPRECATE
	#define _SCL_SECURE_NO_WARNINGS
#endif

#define _I_ // Imprinted
#define _S_ // Serializable
#define _C_ // Constructor
#define _F_ // Function
#define _A_ // Attribute
#define _M_ // Mutable Attribute
#define _O_ // Owned Attribute
#define _N_ // Nested Attribute
#define _P_ // Pool Attribute 

#if defined OBJECT_EXPORT
	#define MK_OBJECT_EXPORT __declspec(dllexport)
#else
	#define MK_OBJECT_EXPORT __declspec(dllimport)
#endif

#define MK_FUNC_EXPORT __cdecl

#endif // mkOBJECTCONFIG_H_INCLUDED
