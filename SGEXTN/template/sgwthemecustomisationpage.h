#ifndef SGWTHEMECUSTOMISATIONPAGE_H
#define SGWTHEMECUSTOMISATIONPAGE_H

#include "../containers/sglarray.h"
#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxstring.h"

class SGWBackground;
class SGWButton;
class SGWLabel;
class SGWBlankWidget;
class SGWColourPickerWidget;
class SGWThemeCustomisationPage
{
public:
    SGWThemeCustomisationPage() = delete;
    static void activate();
    static SGWBackground* initialise();
    static SGWBackground* menuInstance;
    static void showThemeDefaultLight();
    static void showThemeDefaultDark();
    static void showThemeForOurNation();
    static void showThemeCustomLight();
    static void showThemeCustomDark();
    static void showThemeCustomAny();
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
    static bool isUsingCustomLight;
    static SGWLabel* customLightLabel;
    static SGWColourPickerWidget* customLightColourPicker;
    static void updateCustomLight();
    static bool isUsingCustomDark;
    static SGWLabel* customDarkLabel;
    static SGWColourPickerWidget* customDarkColourPicker;
    static void updateCustomDark();
    static bool isUsingCustomAny;
    static SGWLabel* customAnyLabel;
    static SGLArray<SGWColourPickerWidget*> customAnyColourPicker;
    static void updateCustomAny(int index);
    static void cancelChanges();
    static void confirmChanges();
    static SGWBackground* notifInstance;
    static SGWBackground* notifInitialise();
    static void closeNotif();
};

#endif // SGWTHEMECUSTOMISATIONPAGE_H
