#ifndef SG_BUILD_WIDGETS_H
#define SG_BUILD_WIDGETS_H

#include <SG_DLL.h>

#ifdef SG_BUILDING_WIDGETS
    #define SG_WIDGETS_DLL SG_DLL_EXPORT
#else
    #define SG_WIDGETS_DLL SG_DLL_IMPORT
#endif

#endif // SG_BUILD_WIDGETS_H
