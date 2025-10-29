#ifndef SG_BUILD_MATH_H
#define SG_BUILD_MATH_H

#include <SG_DLL.h>

#ifdef SG_BUILDING_MATH
    #define SG_MATH_DLL SG_DLL_EXPORT
#else
    #define SG_MATH_DLL SG_DLL_IMPORT
#endif

#endif // SG_BUILD_MATH_H
