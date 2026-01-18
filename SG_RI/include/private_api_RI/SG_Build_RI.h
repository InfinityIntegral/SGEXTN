#pragma once

#include <SG_DLL.h>

#ifdef SG_BUILDING_RI
    #define SG_RI_DLL SG_DLL_EXPORT
#else
    #define SG_RI_DLL SG_DLL_IMPORT
#endif
