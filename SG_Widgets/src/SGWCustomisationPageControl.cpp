#include <SGWCustomisationPageControl.h>
#include <private_api_Widgets/SGWSingCorrectCustomisationPage.h>
#include <private_api_Widgets/SGWFontSizeCustomisationPage.h>
#include <private_api_Widgets/SGWBasicThemeCustomisationPage.h>

void SGWCustomisationPageControl::enableThemeColoursCustomisationPage(){
    SGWBasicThemeCustomisationPage::activate();
}

void SGWCustomisationPageControl::enableFontSizeCustomisationPage(){
    SGWFontSizeCustomisationPage::activate();
}

void SGWCustomisationPageControl::enableSingCorrectCustomisationPage(){
    SGWSingCorrectCustomisationPage::activate();
}
