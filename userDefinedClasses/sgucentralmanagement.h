#ifndef SGUCENTRALMANAGEMENT_H
#define SGUCENTRALMANAGEMENT_H

#include <QObject>
#include <qtmetamacros.h>
#include "../primitives/sgxcolourrgba.h"

class SGUCentralManagement : public QObject // non instantiable class for essential application data that should be define by the user, including application name, theme colours, custom initialisation and custom termination
{
    Q_OBJECT
public:
    SGUCentralManagement() = delete;
    static void initialise(); // initialisation function run when app opens
    static void terminate(); // temination function run when app closes
    static void earlyInitialise();
    static QString applicationName; // name of application displayed
    static QString applicationVersion; // version number of application
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
    static SGXColourRGBA cuteVesiclesMembraneColour;
    static SGXColourRGBA cuteVesiclesContentsColour;
    static float cuteVesiclesCenterTransparency;
    static float cuteVesiclesEdgeTransparency;
    static float cuteVesiclesMembraneTransparency;
};

#endif // SGUCENTRALMANAGEMENT_H
