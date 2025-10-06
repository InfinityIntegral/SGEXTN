#ifndef SGXTHEMECOLOURSCUSTOMISATION_H
#define SGXTHEMECOLOURSCUSTOMISATION_H

#include "../primitives/sgxcolourrgba.h"

class SGXThemeColoursCustomisation
{
public:
    SGXThemeColoursCustomisation() = delete;
    static void loadThemeColours();
    static void syncThemeColours();
    static SGXColourRGBA themeColour0;
    static SGXColourRGBA themeColour1;
    static SGXColourRGBA themeColour2;
    static SGXColourRGBA themeColour3;
    static SGXColourRGBA themeColour4;
    static SGXColourRGBA themeColour5;
    static SGXColourRGBA themeColour6;
    static SGXColourRGBA themeColour7;
    static SGXColourRGBA themeColour8;
};

#endif // SGXTHEMECOLOURSCUSTOMISATION_H
