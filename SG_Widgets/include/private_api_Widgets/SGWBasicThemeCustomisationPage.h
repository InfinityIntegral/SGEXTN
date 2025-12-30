#ifndef SGWBASICTHEMECUSTOMISATIONPAGE_H
#define SGWBASICTHEMECUSTOMISATIONPAGE_H

#include <SGLArray.h>
#include <SGXColourRGBA.h>
#include <SGXString.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class SGWBackground;
class SGWButton;
class SGWLabel;
class SGWBlankWidget;
class SGWColourPickerWidget;
class SG_WIDGETS_DLL SGWBasicThemeCustomisationPage {
public:
    SGWBasicThemeCustomisationPage() = delete;
    static void activate();
    static SGWBackground* initialise();
    static SGWBackground* menuInstance;
    static void showThemeDefaultLight();
    static void showThemeDefaultDark();
    static void showThemeForOurNation();
    static SGWBackground* detailsInstance;
    static SGWButton* cancelButton;
    static SGWButton* confirmButton;
    static SGWBackground* detailsScroll;
    static SGWLabel* detailsInfo;
    static SGLArray<SGWBlankWidget*> coloursDisplay;
    static SGWBackground* initialiseDetailsPage();
    static SGLArray<SGXColourRGBA> themeColours;
    static SGXString infoString;
    static void updateElements();
    static void cancelChanges();
    static void confirmChanges();
    static SGWBackground* notifInstance;
    static SGWBackground* notifInitialise();
    static void closeNotif();
};

#endif // SGWBASICTHEMECUSTOMISATIONPAGE_H
