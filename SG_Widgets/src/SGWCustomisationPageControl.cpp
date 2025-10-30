#include <SGWCustomisationPageControl.h>
#include <private_api_Widgets/SGWSingCorrectCustomisationPage.h>
#include <private_api_Widgets/SGWFontSizeCustomisationPage.h>

void (*SGWCustomisationPageControl::enableThemeColoursCustomisationPage)() = nullptr;

void SGWCustomisationPageControl::enableFontSizeCustomisationPage(){
    SGWFontSizeCustomisationPage::activate();
}

void SGWCustomisationPageControl::enableSingCorrectCustomisationPage(){
    SGWSingCorrectCustomisationPage::activate();
}
