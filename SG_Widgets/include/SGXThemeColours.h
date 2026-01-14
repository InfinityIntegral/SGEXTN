#ifndef SGXTHEMECOLOURS_H
#define SGXTHEMECOLOURS_H

#include <SGXColourRGBA.h>
#include <SGLArray.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGXThemeColours
{
public:
    SGXThemeColours() = delete;
    static SGXColourRGBA getThemeColour(int themeColour);
    static SGLArray<SGXColourRGBA> generateSincerityUIThemeSet(SGXColourRGBA baseColour, bool darkMode);
};

#endif // SGXTHEMECOLOURS_H
