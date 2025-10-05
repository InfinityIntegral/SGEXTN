#ifndef SGUCENTRALMANAGEMENT_H
#define SGUCENTRALMANAGEMENT_H

#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxstring.h"

class SGUCentralManagement
{
public:
    SGUCentralManagement() = delete;
    static void initialise();
    static void terminate();
    static void earlyInitialise();
    static void initialiseExtraFonts();
    static void initialiseCustomRendering();
    static SGXString applicationName;
    static SGXString applicationVersion;
    static SGXString organisationName;
    static SGXString rootFolderName;
    static float scaleFactor;
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

#endif // SGUCENTRALMANAGEMENT_H
