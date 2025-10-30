#include <SGWCustomisationPageControl.h>
#include <private_api_Widgets/SGWSingCorrectCustomisationPage.h>
#include <private_api_Widgets/SGWFontSizeCustomisationPage.h>

void (*SGWCustomisationPageControl::themeColoursCustomisationPageActivationFunction)() = nullptr;

void SGWCustomisationPageControl::enableThemeColoursCustomisationPage(){
    if(SGWCustomisationPageControl::themeColoursCustomisationPageActivationFunction != nullptr){SGWCustomisationPageControl::themeColoursCustomisationPageActivationFunction();}
}

void SGWCustomisationPageControl::enableFontSizeCustomisationPage(){
    SGWFontSizeCustomisationPage::activate();
}

void SGWCustomisationPageControl::enableSingCorrectCustomisationPage(){
    SGWSingCorrectCustomisationPage::activate();
}
