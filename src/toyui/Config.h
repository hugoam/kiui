//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef TOY_UICONFIG_H
#define TOY_UICONFIG_H

//#define KIUI_DRAW_CACHE

#include <toyobj/Config.h>

#if defined _WIN32 || defined __CYGWIN__
  #ifdef UI_EXPORT
    #ifdef __GNUC__
      #define TOY_UI_EXPORT __attribute__ ((dllexport))
    #else
      #define TOY_UI_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define TOY_UI_EXPORT __attribute__ ((dllimport))
    #else
      #define TOY_UI_EXPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define TOY_UI_EXPORT __attribute__ ((visibility ("default")))
    #define DLL_LOCAL __attribute__ ((visibility ("hidden")))
  #else
    #define TOY_UI_EXPORT
    #define DLL_LOCAL
  #endif
#endif

#endif // TOY_UICONFIG_H
