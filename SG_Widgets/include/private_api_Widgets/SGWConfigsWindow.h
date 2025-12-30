#ifndef SGWCONFIGSWINDOW_H
#define SGWCONFIGSWINDOW_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWBackground;
class SG_WIDGETS_DLL SGWConfigsWindow {
public:
    SGWConfigsWindow() = delete;
    static SGWBackground* instance;
    static SGWBackground* initialise();
    static void activate();
    static void disable();
    static void view05524FHomePage();
    static void viewSGEXTNPage();
    static void viewApplicationInfoPage();
};

#endif // SGWCONFIGSWINDOW_H
