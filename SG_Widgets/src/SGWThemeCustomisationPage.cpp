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
#include <SGWInput.h>
#include <SGXThemeColours.h>

SGWBackground* SGWThemeCustomisationPage::optionsInstance = nullptr;
SGWBackground* SGWThemeCustomisationPage::testPageInstance = nullptr;
SGLArray<SGXColourRGBA> SGWThemeCustomisationPage::previousTheme = SGLArray<SGXColourRGBA>(0);
SGWBackground* SGWThemeCustomisationPage::customBasePageInstance = nullptr;
SGLArray<SGXColourRGBA> SGWThemeCustomisationPage::customThemeColours = SGLArray<SGXColourRGBA>(0);
SGLArray<SGWBlankWidget*> SGWThemeCustomisationPage::customThemeColourDisplays = SGLArray<SGWBlankWidget*>(6, static_cast<SGWBlankWidget*>(nullptr));
SGWInput* SGWThemeCustomisationPage::customThemeBaseRedInput = nullptr;
SGWInput* SGWThemeCustomisationPage::customThemeBaseGreenInput = nullptr;
SGWInput* SGWThemeCustomisationPage::customThemeBaseBlueInput = nullptr;
SGWWidget* SGWThemeCustomisationPage::customThemeBaseWarn = nullptr;
bool SGWThemeCustomisationPage::customThemeBaseDarkMode = false;

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
        SGWButton* themeButton = new SGWTextButton(bg, "custom (light)", nullptr, 0.0f, 0.0f, 0.0f, static_cast<float>(themes.length()), 1.0f, 0.0f, 0.0f, 1.0f);
        (*themeButton).attachedString = "C1L";
        (*themeButton).clickFunctionWithString = &SGWThemeCustomisationPage::useOption;
    }
    {
        SGWButton* themeButton = new SGWTextButton(bg, "custom (dark)", nullptr, 0.0f, 0.0f, 0.0f, static_cast<float>(themes.length()) + 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
        (*themeButton).attachedString = "C1D";
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
    if(x == "C1L"){
        SGWThemeCustomisationPage::customThemeBaseDarkMode = false;
        SGWBackground::enable(SGWThemeCustomisationPage::customBasePageInstance, &SGWThemeCustomisationPage::initialiseCustomBasePage, &SGWThemeCustomisationPage::resetCustomThemeBasePage);
        return;
    }
    if(x == "C1D"){
        SGWThemeCustomisationPage::customThemeBaseDarkMode = true;
        SGWBackground::enable(SGWThemeCustomisationPage::customBasePageInstance, &SGWThemeCustomisationPage::initialiseCustomBasePage, &SGWThemeCustomisationPage::resetCustomThemeBasePage);
        return;
    }
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

SGWBackground* SGWThemeCustomisationPage::initialiseCustomBasePage(){
    SGWThemeCustomisationPage::customThemeColours = SGXThemeColoursCustomisation::themeColours;
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    for(int i=0; i<6; i++){
        SGWThemeCustomisationPage::customThemeColourDisplays.at(i) = new SGWBlankWidget(bg, static_cast<float>(i) / 6.0f, 0.0f, 0.0f, 0.0f, 1.0f / 6.0f, 0.0f, 0.0f, 2.0f);
        (*SGWThemeCustomisationPage::customThemeColourDisplays.at(i)).setColour(SGWThemeCustomisationPage::customThemeColours.at(i));
    }
    new SGWTextLabel(bg, "base colour: ", 0.0f, 0.5f, 0.0f, 2.5f, 0.0f, 4.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
    SGWThemeCustomisationPage::customThemeBaseRedInput = new SGWTextInput(bg, "red", &SGWThemeCustomisationPage::updateColoursCustomBase, 0.0f, 4.5f, 0.0f, 2.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWThemeCustomisationPage::customThemeBaseGreenInput = new SGWTextInput(bg, "green", &SGWThemeCustomisationPage::updateColoursCustomBase, 0.0f, 7.0f, 0.0f, 2.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWThemeCustomisationPage::customThemeBaseBlueInput = new SGWTextInput(bg, "blue", &SGWThemeCustomisationPage::updateColoursCustomBase, 0.0f, 9.5f, 0.0f, 2.5f, 0.0f, 2.0f, 0.0f, 1.0f);
    SGWThemeCustomisationPage::customThemeBaseWarn = new SGWTextLabel(bg, "integer between 0 and 255 inclusive", 0.0f, 4.5f, 0.0f, 3.5f, 0.0f, 8.0f, 0.0f, 0.75f, SGWHorizontalAlignment::Left, true);
    new SGWTextButton(bg, "cancel", &SGWThemeCustomisationPage::cancelCustomBaseThemeChange, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    new SGWTextButton(bg, "confirm", &SGWThemeCustomisationPage::confirmCustomBaseThemeChange, 0.5f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWThemeCustomisationPage::cancelCustomBaseThemeChange(){
    SGWBackground::disable(SGWThemeCustomisationPage::customBasePageInstance);
}

void SGWThemeCustomisationPage::confirmCustomBaseThemeChange(){
    SGWBackground::disable(SGWThemeCustomisationPage::customBasePageInstance);
    SGXThemeColoursCustomisation::themeColours = SGWThemeCustomisationPage::customThemeColours;
    SGXThemeColoursCustomisation::syncThemeColours();
}

void SGWThemeCustomisationPage::updateColoursCustomBase(){
    bool isValid = false;
    bool canContinue = true;
    int r = (*SGWThemeCustomisationPage::customThemeBaseRedInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){
        canContinue = false;
        (*SGWThemeCustomisationPage::customThemeBaseRedInput).setInvalid(true);
    }
    else{(*SGWThemeCustomisationPage::customThemeBaseRedInput).setInvalid(false);}
    int g = (*SGWThemeCustomisationPage::customThemeBaseGreenInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){
        canContinue = false;
        (*SGWThemeCustomisationPage::customThemeBaseGreenInput).setInvalid(true);
    }
    else{(*SGWThemeCustomisationPage::customThemeBaseGreenInput).setInvalid(false);}
    int b = (*SGWThemeCustomisationPage::customThemeBaseBlueInput).getTextAsInt(&isValid, 0, 255);
    if(isValid == false){
        canContinue = false;
        (*SGWThemeCustomisationPage::customThemeBaseBlueInput).setInvalid(true);
    }
    else{(*SGWThemeCustomisationPage::customThemeBaseBlueInput).setInvalid(false);}
    if(canContinue == false){
        (*SGWThemeCustomisationPage::customThemeBaseWarn).setItemVisibility(true);
        return;
    }
    (*SGWThemeCustomisationPage::customThemeBaseWarn).setItemVisibility(false);
    SGWThemeCustomisationPage::customThemeColours = SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA(r, g, b), SGWThemeCustomisationPage::customThemeBaseDarkMode);
    for(int i=0; i<6; i++){
        (*SGWThemeCustomisationPage::customThemeColourDisplays.at(i)).setColour(SGWThemeCustomisationPage::customThemeColours.at(i));
    }
}

void SGWThemeCustomisationPage::resetCustomThemeBasePage(){
    (*SGWThemeCustomisationPage::customThemeBaseRedInput).setTextFromInt(255);
    (*SGWThemeCustomisationPage::customThemeBaseGreenInput).setTextFromInt(0);
    (*SGWThemeCustomisationPage::customThemeBaseBlueInput).setTextFromInt(200);
    SGWThemeCustomisationPage::updateColoursCustomBase();
}
