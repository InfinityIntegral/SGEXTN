#ifndef SGXTHEMECOLOURS_H
#define SGXTHEMECOLOURS_H

#include "../primitives/sgxcolourrgba.h"

class SGXThemeColours
{
public:
    SGXThemeColours() = delete;
    static SGXColourRGBA getThemeColour(int themeColour);
};

#endif // SGXTHEMECOLOURS_H
