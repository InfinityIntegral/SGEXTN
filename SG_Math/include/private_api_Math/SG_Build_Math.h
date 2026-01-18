#pragma once

#include <SG_DLL.h>

#ifdef SG_BUILDING_MATH
    #define SG_MATH_DLL SG_DLL_EXPORT
#else
    #define SG_MATH_DLL SG_DLL_IMPORT
#endif
