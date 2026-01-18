#pragma once

#include <SG_DLL.h>

#ifdef SG_BUILDING_CORE
    #define SG_CORE_DLL SG_DLL_EXPORT
#else
    #define SG_CORE_DLL SG_DLL_IMPORT
#endif
