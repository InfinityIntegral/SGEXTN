#ifndef SGWCUSTOMISATIONPAGECONTROL_H
#define SGWCUSTOMISATIONPAGECONTROL_H

#include <private_api_Widgets/SG_Build_Widgets.h>

class SG_WIDGETS_DLL SGWCustomisationPageControl
{
public:
    SGWCustomisationPageControl() = delete;
    static void enableThemeColoursCustomisationPage();
    static void enableFontSizeCustomisationPage();
    static void enableSingCorrectCustomisationPage();
};

#endif // SGWCUSTOMISATIONPAGECONTROL_H
