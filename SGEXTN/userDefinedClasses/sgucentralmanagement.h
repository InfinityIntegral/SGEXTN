#ifndef SGUCENTRALMANAGEMENT_H
#define SGUCENTRALMANAGEMENT_H

#include <QObject>
#include <qtmetamacros.h>
#include "../primitives/sgxcolourrgba.h"

class SGUCentralManagement : public QObject // non instantiable class for essential application data that should be defined by the user, including application name, theme colours, custom initialisation and custom termination
{
    // follow the instructions in the corresponding .cpp file pls
    Q_OBJECT
public:
    SGUCentralManagement() = delete;
    static void initialise(); // initialisation function run when app opens
    static void terminate(); // temination function run when app closes
    static void earlyInitialise(); // initialisation function run before GUI is created
    static void initialiseExtraFonts(); // initialisation function run immediately after the SingScript.sg font is imported
    static void initialiseCustomRendering(); // initialisation function run immediately after SGEXTN builtin rendering types are registered with QML
    static QString applicationName; // name of application displayed
    static QString applicationVersion; // version number of application
    static QString organisationName; // name of your organisation
    static QString rootFolderName; // name of root folder of your application
    static SGXColourRGBA themeColour0; // theme colour 0, default black
    static SGXColourRGBA themeColour1; // theme colour 1
    static SGXColourRGBA themeColour2; // theme colour 2
    static SGXColourRGBA themeColour3; // theme colour 3
    static SGXColourRGBA themeColour4; // theme colour 4, default bright pink
    static SGXColourRGBA themeColour5; // theme colour 5
    static SGXColourRGBA themeColour6; // theme colour 6
    static SGXColourRGBA themeColour7; // theme colour 7
    static SGXColourRGBA themeColour8; // theme colour 8, default white
    static float cuteVesiclesMembraneThickness; // thickness of vesicle membrane in units, where 1 unit is half the maximum of the parent widget's width and height
    static float cuteVesiclesMaximumCenterDistance; // maximum possible distance on both axis that a vesicle can be from the center of the screen in units, where 1 unit is half the maximum of the parent widget's width and height
    static float cuteVesiclesMaximumVelocity; // maximum possible speed on both axis that a vesicle can move at in units per second, where 1 unit is half the maximum of the parent widget's width and height
    static float cuteVesiclesMaximumAcceleration; // maximum possible acceleration on both axis for vesicles in units per second, where 1 unit is half the maximum of the parent widget's width and height
    static float cuteVesiclesMaximumRadiusChange; // maximum possible rate of change of a vesicle's radius in units per second, where 1 unit is half the maximum of the parent widget's width and height
    static float cuteVesiclesMinimumRadius; // minimum vesicle radius in units, where 1 unit is half the maximum of the parent widget's width and height
    static float cuteVesiclesMaximumRadius; // maximum vesicle radius in units, where 1 unit is half the maximum of the parent widget's width and height
    static float cuteVesiclesMaximumRadiusOffsetChange; // maximum possible rate of change of the radius offset on vesicles as a ratio to the radius, the radius offset is used to give the vesicles a squishy feel
    static float cuteVesiclesMaximumRadiusOffset; // maximum possible radius offset in both directions on vesicles as a ratio to the radius, the radius offset is used to give the vesicles a squishy feel
    static SGXColourRGBA cuteVesiclesMembraneColour; // colour of the membrane (phospholipid bilayer) on vesicles
    static SGXColourRGBA cuteVesiclesContentsColour; // colour of vesicle contents
    static float cuteVesiclesCenterTransparency; // transparency of vesicle at its center, here there is most contents
    static float cuteVesiclesEdgeTransparency; // transparency of vesicle at its edge, here there is least contents
    static float cuteVesiclesMembraneTransparency; // transparency of vesicle membrane (phospholipid bilayer)
    static float cuteVesiclesFrameRate; // frame count per second of vesicle animation
};

#endif // SGUCENTRALMANAGEMENT_H
