#ifndef SG_BUILD_RI_H
#define SG_BUILD_RI_H

#include <SG_DLL.h>

#ifdef SG_BUILDING_RI
    #define SG_RI_DLL SG_DLL_EXPORT
#else
    #define SG_RI_DLL SG_DLL_IMPORT
#endif

#endif // SG_BUILD_RI_H
