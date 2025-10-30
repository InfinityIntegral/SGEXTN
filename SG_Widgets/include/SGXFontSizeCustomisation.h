#ifndef SGXFONTSIZECUSTOMISATION_H
#define SGXFONTSIZECUSTOMISATION_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGXFontSizeCustomisation
{
public:
    SGXFontSizeCustomisation() = delete;
    static void loadFontSize();
    static void syncFontSize();
    static void updateFontSize();
    static float fontSize;
    static float defaultFontSize;
};

#endif // SGXFONTSIZECUSTOMISATION_H
