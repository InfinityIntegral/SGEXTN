#ifndef SGXTHEMECOLOURSCUSTOMISATION_H
#define SGXTHEMECOLOURSCUSTOMISATION_H

#include <SGXColourRGBA.h>
#include <SGLArray.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGXThemeColoursCustomisation
{
public:
    SGXThemeColoursCustomisation() = delete;
    static void loadThemeColours();
    static void syncThemeColours();
    static SGLArray<SGXColourRGBA> themeColours;
};

#endif // SGXTHEMECOLOURSCUSTOMISATION_H
