//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//	freely, subject to the following restrictions:
//
//	1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//	2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//
//	3. This notice may not be removed or altered from any source distribution.
//

#ifndef MK_UICONFIG_H_INCLUDED
#define MK_UICONFIG_H_INCLUDED

#include <Object/mkObjectConfig.h>

#if defined _WIN32 || defined __CYGWIN__
  #ifdef UI_EXPORT
    #ifdef __GNUC__
      #define MK_UI_EXPORT __attribute__ ((dllexport))
    #else
      #define MK_UI_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define MK_UI_EXPORT __attribute__ ((dllimport))
    #else
      #define MK_UI_EXPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define MK_UI_EXPORT __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define MK_UI_EXPORT
    #define DLL_LOCAL
  #endif
#endif

#endif // MK_UICONFIG_H_INCLUDED
