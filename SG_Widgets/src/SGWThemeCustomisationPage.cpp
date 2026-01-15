#include <private_api_Widgets/SGWThemeCustomisationPage.h>
#include <SGWBackground.h>
#include <SGXString.h>
#include <SGWPageBackground.h>
#include <SGWScrollView.h>
#include <private_api_Widgets/SGXThemeSet.h>
#include <SGWWidget.h>
#include <SGWTextLabel.h>
#include <SGWHorizontalAlignment.h>
#include <SGWTextButton.h>
#include <SGWButton.h>
#include <SGLArray.h>
#include <SGXColourRGBA.h>
#include <SGXThemeColoursCustomisation.h>
#include <SGWSequentialLongLabel.h>
#include <SGWBlankWidget.h>
#include <SGWLongLabel.h>
#include <SGWTextInput.h>

SGWBackground* SGWThemeCustomisationPage::optionsInstance = nullptr;
SGWBackground* SGWThemeCustomisationPage::testPageInstance = nullptr;
SGLArray<SGXColourRGBA> SGWThemeCustomisationPage::previousTheme = SGLArray<SGXColourRGBA>(0);

SGWBackground* SGWThemeCustomisationPage::initialiseOptions(){
    SGWBackground* pageBg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    new SGWTextLabel(pageBg, "Choose Theme", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 2.0f, SGWHorizontalAlignment::Center, false);
    new SGWTextButton(pageBg, "cancel", &SGWThemeCustomisationPage::hideOptionsPage, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    SGLArray<SGXThemeSet> themes(SGXThemeSet::standardLight, SGXThemeSet::standardDark, SGXThemeSet::mathLight, SGXThemeSet::mathDark, SGXThemeSet::scienceLight, SGXThemeSet::scienceDark, SGXThemeSet::englishLight, SGXThemeSet::englishDark, SGXThemeSet::chineseLight, SGXThemeSet::chineseDark, SGXThemeSet::malayLight, SGXThemeSet::malayDark, SGXThemeSet::tamilLight, SGXThemeSet::tamilDark);
    SGWWidget* bg = new SGWScrollView(pageBg, 0.0f, 0.0f, 0.0f, 3.0f, 1.0f, 0.0f, 1.0f, -4.5f, 0.0f, 2.0f + static_cast<float>(themes.length()), 0.0f, 0.5f);
    for(int i=0; i<themes.length(); i++){
        SGWButton* themeButton = new SGWTextButton(bg, themes.at(i).themeName, nullptr, 0.0f, 0.0f, 0.0f, static_cast<float>(i), 1.0f, 0.0f, 0.0f, 1.0f);
        SGXString themeCode = "";
        for(int j=0; j<6; j++){
            themeCode += SGXString::intToStringBase16(themes.at(i).colours.at(j).getRed()).fillLeftToLength(2, '0');
            themeCode += SGXString::intToStringBase16(themes.at(i).colours.at(j).getGreen()).fillLeftToLength(2, '0');
            themeCode += SGXString::intToStringBase16(themes.at(i).colours.at(j).getBlue()).fillLeftToLength(2, '0');
        }
        (*themeButton).attachedString = themeCode;
        (*themeButton).clickFunctionWithString = &SGWThemeCustomisationPage::useOption;
        (*themeButton).setBackgroundColour(themes.at(i).colours.at(3));
        (*themeButton).setForegroundColour(themes.at(i).colours.at(0));
        (*themeButton).setBackgroundHoverColour(themes.at(i).colours.at(4));
        (*themeButton).setForegroundHoverColour(themes.at(i).colours.at(1));
        (*themeButton).setBackgroundFocusColour(themes.at(i).colours.at(5));
        (*themeButton).setForegroundFocusColour(themes.at(i).colours.at(2));
    }
    {
        SGWButton* themeButton = new SGWTextButton(bg, "custom (Sincerity UI)", nullptr, 0.0f, 0.0f, 0.0f, static_cast<float>(themes.length()), 1.0f, 0.0f, 0.0f, 1.0f);
        (*themeButton).attachedString = "C1";
        (*themeButton).clickFunctionWithString = &SGWThemeCustomisationPage::useOption;
    }
    {
        SGWButton* themeButton = new SGWTextButton(bg, "custom (anything)", nullptr, 0.0f, 0.0f, 0.0f, static_cast<float>(themes.length()) + 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        (*themeButton).attachedString = "C2";
        (*themeButton).clickFunctionWithString = &SGWThemeCustomisationPage::useOption;
    }
    return pageBg;
}

void SGWThemeCustomisationPage::activate(){
    SGWBackground::enable(SGWThemeCustomisationPage::optionsInstance, &SGWThemeCustomisationPage::initialiseOptions, nullptr);
}

void SGWThemeCustomisationPage::hideOptionsPage(){
    SGWBackground::disable(SGWThemeCustomisationPage::optionsInstance);
}

SGLArray<SGXColourRGBA> SGWThemeCustomisationPage::parseAttachedString(const SGXString &s){
    if(s.length() != 36){return SGLArray<SGXColourRGBA>(0);}
    SGLArray<SGXColourRGBA> colours(6);
    for(int i=0; i<6; i++){
        colours.at(i).setTransparency(255);
        colours.at(i).setRed(s.substring(6 * i, 2).parseToIntBase16(nullptr));
        colours.at(i).setGreen(s.substring(6 * i + 2, 2).parseToIntBase16(nullptr));
        colours.at(i).setBlue(s.substring(6 * i + 4, 2).parseToIntBase16(nullptr));
    }
    return colours;
}

void SGWThemeCustomisationPage::useOption(const SGXString &x){
    SGWThemeCustomisationPage::hideOptionsPage();
    if(x == "C1" || x == "C2"){return;}
    SGWThemeCustomisationPage::previousTheme = SGXThemeColoursCustomisation::themeColours;
    SGXThemeColoursCustomisation::themeColours = SGWThemeCustomisationPage::parseAttachedString(x);
    SGWThemeCustomisationPage::showTestPage();
}

SGWBackground* SGWThemeCustomisationPage::initialiseTestPage(){
    SGWPageBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    new SGWLongLabel(bg, SGXThemeSet::styleText, 0.0f, 0.5f, 0.0f, 0.5f, 0.75f, -0.0f, 1.0f, -4.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.5f);
    new SGWTextLabel(bg, "a)", 0.0f, 0.5f, 1.0f, -4.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    new SGWTextInput(bg, "answer", nullptr, 0.0f, 2.5f, 1.0f, -2.5f, 0.75f, -3.0f, 0.0f, 1.0f);
    new SGWTextLabel(bg, "b)", 0.0f, 0.5f, 1.0f, -2.5f, 0.0f, 2.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    new SGWTextInput(bg, "answer", nullptr, 0.0f, 2.5f, 1.0f, -4.0f, 0.75f, -3.0f, 0.0f, 1.0f);
    SGWLabel* rightSidebar = new SGWSequentialLongLabel(bg, "do not write in this space", 0.75f, 0.6f, 0.0f, 0.5f, 0.25f, -1.0f, 0.0f, 1.0f);
    (*rightSidebar).setHorizontalAlignment(SGWHorizontalAlignment::Center);
    SGWBlankWidget* pageDivider = new SGWBlankWidget(bg, 0.75f, 0.0f, 0.0f, 0.0f, 0.0f, 0.1f, 1.0f, -1.0f);
    new SGWTextButton(bg, "cancel", &SGWThemeCustomisationPage::cancelThemeChange, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    new SGWTextButton(bg, "confirm", &SGWThemeCustomisationPage::confirmThemeChange, 0.5f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    (*pageDivider).setThemeColour(0);
    return bg;
}

void SGWThemeCustomisationPage::showTestPage(){
    SGWBackground::enable(SGWThemeCustomisationPage::testPageInstance, &SGWThemeCustomisationPage::initialiseTestPage, nullptr);
}

void SGWThemeCustomisationPage::cancelThemeChange(){
    SGXThemeColoursCustomisation::themeColours = SGWThemeCustomisationPage::previousTheme;
    SGWBackground::disable(SGWThemeCustomisationPage::testPageInstance);
}

void SGWThemeCustomisationPage::confirmThemeChange(){
    SGXThemeColoursCustomisation::syncThemeColours();
    SGWBackground::disable(SGWThemeCustomisationPage::testPageInstance);
}
