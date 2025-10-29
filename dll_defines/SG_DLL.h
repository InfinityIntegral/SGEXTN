#ifndef SG_DLL_H
#define SG_DLL_H

#if defined(_WIN32) || defined(_WIN64)
  #define SG_DLL_EXPORT __declspec(dllexport)
  #define SG_DLL_IMPORT __declspec(dllimport)
#else
  #if __GNUC__ >= 4
    #define SG_DLL_EXPORT __attribute__((visibility("default")))
    #define SG_DLL_IMPORT __attribute__((visibility("default")))
  #else
    #define SG_DLL_EXPORT
    #define SG_DLL_IMPORT
  #endif
#endif

#endif // SG_DLL_H
