#ifndef SGWTHEMECUSTOMISATIONPAGE_H
#define SGWTHEMECUSTOMISATIONPAGE_H

#include <private_api_Widgets/SG_Build_Widgets.h>

#include <SGLArray.h>
#include <SGXColourRGBA.h>

class SGWBackground;
class SGXString;
class SGWBlankWidget;
class SGWInput;
class SGWWidget;
class SGWThemeCustomisationPage {
public:
    static SGWBackground* optionsInstance;
    static SGWBackground* initialiseOptions();
    static void activate();
    static void useOption(const SGXString& x);
    static void hideOptionsPage();
    static SGLArray<SGXColourRGBA> parseAttachedString(const SGXString& s);
    static void showTestPage();
    static SGWBackground* initialiseTestPage();
    static SGWBackground* testPageInstance;
    static SGLArray<SGXColourRGBA> previousTheme;
    static void cancelThemeChange();
    static void confirmThemeChange();
    static SGWBackground* customBasePageInstance;
    static SGWBackground* initialiseCustomBasePage();
    static void cancelCustomBaseThemeChange();
    static void confirmCustomBaseThemeChange();
    static SGLArray<SGXColourRGBA> customThemeColours;
    static SGLArray<SGWBlankWidget*> customThemeColourDisplays;
    static SGWInput* customThemeBaseRedInput;
    static SGWInput* customThemeBaseGreenInput;
    static SGWInput* customThemeBaseBlueInput;
    static SGWWidget* customThemeBaseWarn;
    static void updateColoursCustomBase();
    static bool customThemeBaseDarkMode;
    static void resetCustomThemeBasePage();
};

#endif // SGWTHEMECUSTOMISATIONPAGE_H
