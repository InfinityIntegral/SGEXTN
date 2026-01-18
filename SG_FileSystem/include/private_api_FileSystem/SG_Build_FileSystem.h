#pragma once

#include <SG_DLL.h>

#ifdef SG_BUILDING_FILESYSTEM
    #define SG_FILESYSTEM_DLL SG_DLL_EXPORT
#else
    #define SG_FILESYSTEM_DLL SG_DLL_IMPORT
#endif
