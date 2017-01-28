
#ifndef MK_UIEXAMPLE_CONFIG_H
#define MK_UIEXAMPLE_CONFIG_H

#include <Ui/mkUiConfig.h>

#if defined _WIN32 || defined __CYGWIN__
  #ifdef UIEXAMPLE_EXPORT
    #ifdef __GNUC__
      #define MK_UIEXAMPLE_EXPORT __attribute__ ((dllexport))
    #else
      #define MK_UIEXAMPLE_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define MK_UIEXAMPLE_EXPORT __attribute__ ((dllimport))
    #else
      #define MK_UIEXAMPLE_EXPORT __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define MK_UIEXAMPLE_EXPORT __attribute__ ((visibility ("default")))
    #define DLL_LOCAL __attribute__ ((visibility ("hidden")))
  #else
    #define MK_UIEXAMPLE_EXPORT
    #define DLL_LOCAL
  #endif
#endif

#endif
