#pragma once

#include <SG_DLL.h>

#ifdef SG_BUILDING_CONTAINERS
    #define SG_CONTAINERS_DLL SG_DLL_EXPORT
#else
    #define SG_CONTAINERS_DLL SG_DLL_IMPORT
#endif
