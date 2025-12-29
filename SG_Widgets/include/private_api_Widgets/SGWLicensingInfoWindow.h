#ifndef SGWLICENSINGINFOWINDOW_H
#define SGWLICENSINGINFOWINDOW_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWBackground;
class SG_WIDGETS_DLL SGWLicensingInfoWindow {
public:
    static SGWBackground* instance;
    static SGWBackground* initialise();
    static void activate();
    static void disable();
};

#endif // SGWLICENSINGINFOWINDOW_H
