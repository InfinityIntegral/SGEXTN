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
    static SGXColourRGBA themeColour0;
    static SGXColourRGBA themeColour1;
    static SGXColourRGBA themeColour2;
    static SGXColourRGBA themeColour3;
    static SGXColourRGBA themeColour4;
    static SGXColourRGBA themeColour5;
    static SGXColourRGBA themeColour6;
    static SGXColourRGBA themeColour7;
    static SGXColourRGBA themeColour8;
    static float cuteVesiclesMembraneThickness;
    static float cuteVesiclesMaximumCenterDistance;
    static float cuteVesiclesMaximumVelocity;
    static float cuteVesiclesMaximumAcceleration;
    static float cuteVesiclesMaximumRadiusChange;
    static float cuteVesiclesMinimumRadius;
    static float cuteVesiclesMaximumRadius;
    static float cuteVesiclesMaximumRadiusOffsetChange;
    static float cuteVesiclesMaximumRadiusOffset;
    static float cuteVesiclesCenterTransparency;
    static float cuteVesiclesEdgeTransparency;
    static float cuteVesiclesMembraneTransparency;
    static float cuteVesiclesFrameRate;
};

#endif // SGUCENTRALMANAGEMENT_H
