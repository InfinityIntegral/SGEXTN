#pragma once

#include <SG_DLL.h>

#ifdef SG_BUILDING_WIDGETS
    #define SG_WIDGETS_DLL SG_DLL_EXPORT
#else
    #define SG_WIDGETS_DLL SG_DLL_IMPORT
#endif
