#ifndef SGWTHEMECUSTOMISATIONPAGE_H
#define SGWTHEMECUSTOMISATIONPAGE_H

#include <private_api_Widgets/SG_Build_Widgets.h>

#include <SGLArray.h>
#include <SGXColourRGBA.h>

class SGWBackground;
class SGXString;
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
};

#endif // SGWTHEMECUSTOMISATIONPAGE_H
