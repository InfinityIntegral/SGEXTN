#ifndef SG_BUILD_CORE_H
#define SG_BUILD_CORE_H

#include <SG_DLL.h>

#ifdef SG_BUILDING_CORE
    #define SG_CORE_DLL SG_DLL_EXPORT
#else
    #define SG_CORE_DLL SG_DLL_IMPORT
#endif

#endif // SG_BUILD_CORE_H
