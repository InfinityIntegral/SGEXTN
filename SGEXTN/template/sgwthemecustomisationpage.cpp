#include "sgwthemecustomisationpage.h"
#include "../widgets/instantiable/sgwpagebackground.h"
#include "../widgets/instantiable/sgwtextbutton.h"
#include "../widgets/noninstantiable/sgwbackground.h"
#include "../widgets/noninstantiable/sgwwidget.h"
#include "../widgets/noninstantiable/sgwbutton.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/instantiable/sgwsequentialscrollview.h"
#include "../widgets/instantiable/sgwsequentiallonglabel.h"
#include "../widgets/noninstantiable/sgwlabel.h"
#include "../containers/sglarray.h"
#include "../widgets/instantiable/sgwblankwidget.h"
#include "../primitives/sgxstring.h"
#include "../widgets/instantiable/sgwtextlabel.h"
#include "../widgets/enums/sgwhorizontalalignment.h"
#include "../widgets/instantiable/sgwcolourpickerwidget.h"
#include "../primitives/sgxcolourhsla.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include "../customisation/sgxthemecolourscustomisation.h"
#include "../widgets/instantiable/sgwlonglabel.h"
#include "../notifications/sgwnotify.h"
#include "../rng/sgxrandomnumbergenerator.h"

SGWBackground* SGWThemeCustomisationPage::menuInstance = nullptr;
SGWBackground* SGWThemeCustomisationPage::detailsInstance = nullptr;
SGWButton* SGWThemeCustomisationPage::cancelButton = nullptr;
SGWButton* SGWThemeCustomisationPage::confirmButton = nullptr;
SGWBackground* SGWThemeCustomisationPage::detailsScroll = nullptr;
SGWLabel* SGWThemeCustomisationPage::detailsInfo = nullptr;
SGLArray<SGWBlankWidget*> SGWThemeCustomisationPage::coloursDisplay = SGLArray<SGWBlankWidget*>(9);
SGLArray<SGXColourRGBA> SGWThemeCustomisationPage::themeColours = SGLArray<SGXColourRGBA>(9);
SGXString SGWThemeCustomisationPage::infoString = "";
bool SGWThemeCustomisationPage::isUsingCustomLight = false;
SGWLabel* SGWThemeCustomisationPage::customLightLabel = nullptr;
SGWColourPickerWidget* SGWThemeCustomisationPage::customLightColourPicker = nullptr;
bool SGWThemeCustomisationPage::isUsingCustomDark = false;
SGWLabel* SGWThemeCustomisationPage::customDarkLabel = nullptr;
SGWColourPickerWidget* SGWThemeCustomisationPage::customDarkColourPicker = nullptr;
bool SGWThemeCustomisationPage::isUsingCustomAny = false;
SGWLabel* SGWThemeCustomisationPage::customAnyLabel = nullptr;
SGLArray<SGWColourPickerWidget*> SGWThemeCustomisationPage::customAnyColourPicker = SGLArray<SGWColourPickerWidget*>(9);
SGWBackground* SGWThemeCustomisationPage::notifInstance = nullptr;

void SGWThemeCustomisationPage::activate(){
    SGWBackground::enable(SGWThemeCustomisationPage::menuInstance, &SGWThemeCustomisationPage::initialise, nullptr);
}

SGWBackground* SGWThemeCustomisationPage::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6);
    SGWButton* b = nullptr;
    b = new SGWTextButton(bg, "Be the Light", &SGWThemeCustomisationPage::showThemeDefaultLight, 0.0f, 0.0f, 0.5f, -3.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(255, 0, 200));
    (*b).setForegroundColour(SGXColourRGBA(255, 255, 255));
    (*b).setBackgroundHoverColour(SGXColourRGBA(191, 0, 150));
    (*b).setForegroundHoverColour(SGXColourRGBA(255, 191, 241));
    (*b).setBackgroundFocusColour(SGXColourRGBA(128, 0, 100));
    (*b).setForegroundFocusColour(SGXColourRGBA(255, 128, 227));
    b = new SGWTextButton(bg, "Shine From Within", &SGWThemeCustomisationPage::showThemeDefaultDark, 0.0f, 0.0f, 0.5f, -2.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(255, 0, 200));
    (*b).setForegroundColour(SGXColourRGBA(0, 0, 0));
    (*b).setBackgroundHoverColour(SGXColourRGBA(255, 64, 214));
    (*b).setForegroundHoverColour(SGXColourRGBA(64, 0, 50));
    (*b).setBackgroundFocusColour(SGXColourRGBA(255, 128, 227));
    (*b).setForegroundFocusColour(SGXColourRGBA(128, 0, 100));
    b = new SGWTextButton(bg, "For Our Nation", &SGWThemeCustomisationPage::showThemeForOurNation, 0.0f, 0.0f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(238, 37, 54));
    (*b).setForegroundColour(SGXColourRGBA(255, 255, 255));
    (*b).setBackgroundHoverColour(SGXColourRGBA(179, 28, 41));
    (*b).setForegroundHoverColour(SGXColourRGBA(251, 201, 205));
    (*b).setBackgroundFocusColour(SGXColourRGBA(119, 19, 27));
    (*b).setForegroundFocusColour(SGXColourRGBA(247, 146, 155));
    b = new SGWTextButton(bg, "Custom Light", &SGWThemeCustomisationPage::showThemeCustomLight, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(128, 128, 128));
    (*b).setForegroundColour(SGXColourRGBA(255, 255, 255));
    (*b).setBackgroundHoverColour(SGXColourRGBA(96, 96, 96));
    (*b).setForegroundHoverColour(SGXColourRGBA(224, 224, 224));
    (*b).setBackgroundFocusColour(SGXColourRGBA(64, 64, 64));
    (*b).setForegroundFocusColour(SGXColourRGBA(192, 192, 192));
    b = new SGWTextButton(bg, "Custom Dark", &SGWThemeCustomisationPage::showThemeCustomDark, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(128, 128, 128));
    (*b).setForegroundColour(SGXColourRGBA(0, 0, 0));
    (*b).setBackgroundHoverColour(SGXColourRGBA(160, 160, 160));
    (*b).setForegroundHoverColour(SGXColourRGBA(32, 32, 32));
    (*b).setBackgroundFocusColour(SGXColourRGBA(192, 192, 192));
    (*b).setForegroundFocusColour(SGXColourRGBA(64, 64, 64));
    b = new SGWTextButton(bg, "Custom Any", &SGWThemeCustomisationPage::showThemeCustomAny, 0.0f, 0.0f, 0.5f, 2.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(128, 0, 128));
    (*b).setForegroundColour(SGXColourRGBA(255, 0, 255));
    (*b).setBackgroundHoverColour(SGXColourRGBA(128, 128, 0));
    (*b).setForegroundHoverColour(SGXColourRGBA(255, 255, 0));
    (*b).setBackgroundFocusColour(SGXColourRGBA(0, 128, 128));
    (*b).setForegroundFocusColour(SGXColourRGBA(0, 255, 255));
    return bg;
}

SGWBackground* SGWThemeCustomisationPage::initialiseDetailsPage(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 8);
    SGWThemeCustomisationPage::detailsScroll = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8);
    SGWThemeCustomisationPage::cancelButton = new SGWTextButton(bg, "cancel", &SGWThemeCustomisationPage::cancelChanges, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGWThemeCustomisationPage::confirmButton = new SGWTextButton(bg, "apply theme", &SGWThemeCustomisationPage::confirmChanges, 0.5f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    new SGWBlankWidget(SGWThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, -1);
    if(SGWThemeCustomisationPage::isUsingCustomLight == true){
        SGWWidget* p = new SGWBlankWidget(SGWThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.5f, -1);
        SGWThemeCustomisationPage::customLightLabel = new SGWTextLabel(p, "base colour:", 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, -0.1f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
        SGWThemeCustomisationPage::customLightColourPicker = new SGWColourPickerWidget(p, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWThemeCustomisationPage::themeColours.at(4));
        (*SGWThemeCustomisationPage::customLightColourPicker).setAttachedFunction(&SGWThemeCustomisationPage::updateCustomLight);
    }
    else{
        SGWThemeCustomisationPage::customLightLabel = nullptr;
        SGWThemeCustomisationPage::customLightColourPicker = nullptr;
    }
    if(SGWThemeCustomisationPage::isUsingCustomDark == true){
        SGWWidget* p = new SGWBlankWidget(SGWThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.5f, -1);
        SGWThemeCustomisationPage::customDarkLabel = new SGWTextLabel(p, "base colour:", 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, -0.1f, 0.0f, 1.0f, SGWHorizontalAlignment::Right, false);
        SGWThemeCustomisationPage::customDarkColourPicker = new SGWColourPickerWidget(p, 0.5f, 0.1f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 1.0f, SGWThemeCustomisationPage::themeColours.at(4));
        (*SGWThemeCustomisationPage::customDarkColourPicker).setAttachedFunction(&SGWThemeCustomisationPage::updateCustomDark);
    }
    else{
        SGWThemeCustomisationPage::customDarkLabel = nullptr;
        SGWThemeCustomisationPage::customDarkColourPicker = nullptr;
    }
    if(SGWThemeCustomisationPage::isUsingCustomAny == true){
        SGWWidget* p = new SGWBlankWidget(SGWThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.5f, -1);
        SGWThemeCustomisationPage::customAnyLabel = new SGWTextLabel(p, "pls adjust colours below", 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, SGWHorizontalAlignment::Center, false);
    }
    SGWWidget* s = new SGWBlankWidget(SGWThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.5f, -1);
    SGWThemeCustomisationPage::detailsInfo = new SGWSequentialLongLabel(SGWThemeCustomisationPage::detailsScroll, "", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    float x = 0.0f;
    for(int i=0; i<9; i++){
        float w = 1.0f;
        if(i == 4 || i == 6 || i == 8){w = 3.0f;}
        SGWThemeCustomisationPage::coloursDisplay.at(i) = new SGWBlankWidget(s, x / 15.0f, 0.0f, 0.0f, 0.0f, w / 15.0f, 0.0f, 0.0f, 2.0f, i);
        x += w;
    }
    if(SGWThemeCustomisationPage::isUsingCustomAny == false){
        SGWThemeCustomisationPage::customAnyLabel = nullptr;
        for(int i=0; i<9; i++){
            SGWThemeCustomisationPage::customAnyColourPicker.at(i) = nullptr;
        }
    }
    else{
        for(int i=0; i<9; i++){
            SGWThemeCustomisationPage::customAnyColourPicker.at(i) = new SGWColourPickerWidget(SGWThemeCustomisationPage::coloursDisplay.at(i), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, SGWThemeCustomisationPage::themeColours.at(i));
            (*SGWThemeCustomisationPage::customAnyColourPicker.at(i)).setAttachedFunction(&SGWThemeCustomisationPage::updateCustomAny);
        }
    }
    SGWThemeCustomisationPage::isUsingCustomLight = false;
    SGWThemeCustomisationPage::isUsingCustomDark = false;
    SGWThemeCustomisationPage::isUsingCustomAny = false;
    return bg;
}

void SGWThemeCustomisationPage::updateElements(){
    (*SGWThemeCustomisationPage::detailsInfo).setTextFromString(SGWThemeCustomisationPage::infoString);
    for(int i=0; i<9; i++){
        (*SGWThemeCustomisationPage::coloursDisplay.at(i)).setColour(SGWThemeCustomisationPage::themeColours.at(i));
    }
    (*SGWThemeCustomisationPage::detailsInfo).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(8));
    (*SGWThemeCustomisationPage::detailsInfo).setForegroundColour(SGWThemeCustomisationPage::themeColours.at(4));
    (*SGWThemeCustomisationPage::detailsInstance).setColour(SGWThemeCustomisationPage::themeColours.at(8));
    (*SGWThemeCustomisationPage::cancelButton).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(4));
    (*SGWThemeCustomisationPage::cancelButton).setForegroundColour(SGWThemeCustomisationPage::themeColours.at(8));
    (*SGWThemeCustomisationPage::cancelButton).setBackgroundHoverColour(SGWThemeCustomisationPage::themeColours.at(3));
    (*SGWThemeCustomisationPage::cancelButton).setForegroundHoverColour(SGWThemeCustomisationPage::themeColours.at(7));
    (*SGWThemeCustomisationPage::cancelButton).setBackgroundFocusColour(SGWThemeCustomisationPage::themeColours.at(2));
    (*SGWThemeCustomisationPage::cancelButton).setForegroundFocusColour(SGWThemeCustomisationPage::themeColours.at(6));
    (*SGWThemeCustomisationPage::confirmButton).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(4));
    (*SGWThemeCustomisationPage::confirmButton).setForegroundColour(SGWThemeCustomisationPage::themeColours.at(8));
    (*SGWThemeCustomisationPage::confirmButton).setBackgroundHoverColour(SGWThemeCustomisationPage::themeColours.at(3));
    (*SGWThemeCustomisationPage::confirmButton).setForegroundHoverColour(SGWThemeCustomisationPage::themeColours.at(7));
    (*SGWThemeCustomisationPage::confirmButton).setBackgroundFocusColour(SGWThemeCustomisationPage::themeColours.at(2));
    (*SGWThemeCustomisationPage::confirmButton).setForegroundFocusColour(SGWThemeCustomisationPage::themeColours.at(6));
    (*SGWThemeCustomisationPage::detailsScroll).setColour(SGWThemeCustomisationPage::themeColours.at(8));
    SGWSequentialScrollView* x = static_cast<SGWSequentialScrollView*>(SGWThemeCustomisationPage::detailsScroll);
    (*x).setScrollbarBackgroundColour(SGWThemeCustomisationPage::themeColours.at(4));
    (*x).setScrollbarForegroundColour(SGWThemeCustomisationPage::themeColours.at(6));
    (*x).setScrollbarBackgroundHoverColour(SGWThemeCustomisationPage::themeColours.at(3));
    (*x).setScrollbarForegroundHoverColour(SGWThemeCustomisationPage::themeColours.at(5));
    (*x).setScrollbarBackgroundFocusColour(SGWThemeCustomisationPage::themeColours.at(2));
    (*x).setScrollbarForegroundFocusColour(SGWThemeCustomisationPage::themeColours.at(4));
    if(SGWThemeCustomisationPage::customLightColourPicker != nullptr){
        (*SGWThemeCustomisationPage::customLightLabel).setForegroundColour(SGWThemeCustomisationPage::themeColours.at(4));
        (*SGWThemeCustomisationPage::customLightLabel).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(8));
        (*SGWThemeCustomisationPage::customLightColourPicker).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(4));
        (*SGWThemeCustomisationPage::customLightColourPicker).setBackgroundHoverColour(SGWThemeCustomisationPage::themeColours.at(3));
        (*SGWThemeCustomisationPage::customLightColourPicker).setBackgroundFocusColour(SGWThemeCustomisationPage::themeColours.at(2));
    }
    if(SGWThemeCustomisationPage::customDarkColourPicker != nullptr){
        (*SGWThemeCustomisationPage::customDarkLabel).setForegroundColour(SGWThemeCustomisationPage::themeColours.at(4));
        (*SGWThemeCustomisationPage::customDarkLabel).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(8));
        (*SGWThemeCustomisationPage::customDarkColourPicker).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(4));
        (*SGWThemeCustomisationPage::customDarkColourPicker).setBackgroundHoverColour(SGWThemeCustomisationPage::themeColours.at(3));
        (*SGWThemeCustomisationPage::customDarkColourPicker).setBackgroundFocusColour(SGWThemeCustomisationPage::themeColours.at(2));
    }
    if(SGWThemeCustomisationPage::customAnyColourPicker.at(0) != nullptr){
        (*SGWThemeCustomisationPage::customAnyLabel).setForegroundColour(SGWThemeCustomisationPage::themeColours.at(4));
        (*SGWThemeCustomisationPage::customAnyLabel).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(8));
        for(int i=0; i<9; i++){
            (*SGWThemeCustomisationPage::customAnyColourPicker.at(i)).setBackgroundColour(SGWThemeCustomisationPage::themeColours.at(4));
            (*SGWThemeCustomisationPage::customAnyColourPicker.at(i)).setBackgroundHoverColour(SGWThemeCustomisationPage::themeColours.at(3));
            (*SGWThemeCustomisationPage::customAnyColourPicker.at(i)).setBackgroundFocusColour(SGWThemeCustomisationPage::themeColours.at(2));
        }
    }
}

void SGWThemeCustomisationPage::showThemeDefaultLight(SGWButton */*unused*/){
    SGWThemeCustomisationPage::infoString = "we can be the light\nfor the world to be better\nlight every heart\nbe the sun of hope\n(Be the Light, 2020)\n\nBe the Light is the default light mode theme of all SGEXTN apps, featuring a white background typical for light mode themes with the iconic bright pink accent used by SGEXTN. The theme represents positivity, kindness, and Singaporean values in general, and is inspired by the National Day song of the same name.";
    SGWThemeCustomisationPage::themeColours.at(0) = SGXColourRGBA(0, 0, 0);
    SGWThemeCustomisationPage::themeColours.at(1) = SGXColourRGBA(64, 0, 50);
    SGWThemeCustomisationPage::themeColours.at(2) = SGXColourRGBA(128, 0, 100);
    SGWThemeCustomisationPage::themeColours.at(3) = SGXColourRGBA(191, 0, 150);
    SGWThemeCustomisationPage::themeColours.at(4) = SGXColourRGBA(255, 0, 200);
    SGWThemeCustomisationPage::themeColours.at(5) = SGXColourRGBA(255, 64, 214);
    SGWThemeCustomisationPage::themeColours.at(6) = SGXColourRGBA(255, 128, 227);
    SGWThemeCustomisationPage::themeColours.at(7) = SGXColourRGBA(255, 191, 241);
    SGWThemeCustomisationPage::themeColours.at(8) = SGXColourRGBA(255, 255, 255);
    SGWBackground::enable(SGWThemeCustomisationPage::detailsInstance, &SGWThemeCustomisationPage::initialiseDetailsPage, &SGWThemeCustomisationPage::updateElements);
}

void SGWThemeCustomisationPage::showThemeDefaultDark(SGWButton */*unused*/){
    SGWThemeCustomisationPage::infoString = "although life has changed\nwe can lend a helping hand\nthinking back, we'll see\nthe path of light shines from within\n(Be the Light, 2020)\n\nShine From Within is the default dark mode theme of all SGEXTN apps, featuring a black background typical for dark mode themes with the iconic bright pink accent used by SGEXTN. Similar to its light mode equivalent, the theme represents positivity, kindness, and Singaporean values in general, and is inspired by the National Day song Be the Light.";
    SGWThemeCustomisationPage::themeColours.at(0) = SGXColourRGBA(255, 255, 255);
    SGWThemeCustomisationPage::themeColours.at(1) = SGXColourRGBA(255, 191, 241);
    SGWThemeCustomisationPage::themeColours.at(2) = SGXColourRGBA(255, 128, 227);
    SGWThemeCustomisationPage::themeColours.at(3) = SGXColourRGBA(255, 64, 214);
    SGWThemeCustomisationPage::themeColours.at(4) = SGXColourRGBA(255, 0, 200);
    SGWThemeCustomisationPage::themeColours.at(5) = SGXColourRGBA(191, 0, 150);
    SGWThemeCustomisationPage::themeColours.at(6) = SGXColourRGBA(128, 0, 100);
    SGWThemeCustomisationPage::themeColours.at(7) = SGXColourRGBA(64, 0, 50);
    SGWThemeCustomisationPage::themeColours.at(8) = SGXColourRGBA(0, 0, 0);
    SGWBackground::enable(SGWThemeCustomisationPage::detailsInstance, &SGWThemeCustomisationPage::initialiseDetailsPage, &SGWThemeCustomisationPage::updateElements);
}

void SGWThemeCustomisationPage::showThemeForOurNation(SGWButton */*unused*/){
    SGWThemeCustomisationPage::infoString = "You, my people, my home,\nour lives, defend and uphold,\nmay the good we achieve,\nas one nation,\nbe shared with the world\n(My People My Home, 1995)\n\nFor Our Nation is the National Day special theme applied to all SGEXTN apps during the National Day period, overwriting any theme settings defined by the user. The theme features a mix of red and white, both being the exact same colour as the colours on our flag. The name of the theme comes from our pledge.";
    SGWThemeCustomisationPage::themeColours.at(0) = SGXColourRGBA(0, 0, 0);
    SGWThemeCustomisationPage::themeColours.at(1) = SGXColourRGBA(60, 9, 14);
    SGWThemeCustomisationPage::themeColours.at(2) = SGXColourRGBA(119, 19, 27);
    SGWThemeCustomisationPage::themeColours.at(3) = SGXColourRGBA(179, 28, 41);
    SGWThemeCustomisationPage::themeColours.at(4) = SGXColourRGBA(238, 37, 54);
    SGWThemeCustomisationPage::themeColours.at(5) = SGXColourRGBA(242, 92, 104);
    SGWThemeCustomisationPage::themeColours.at(6) = SGXColourRGBA(247, 146, 155);
    SGWThemeCustomisationPage::themeColours.at(7) = SGXColourRGBA(251, 201, 205);
    SGWThemeCustomisationPage::themeColours.at(8) = SGXColourRGBA(255, 255, 255);
    SGWBackground::enable(SGWThemeCustomisationPage::detailsInstance, &SGWThemeCustomisationPage::initialiseDetailsPage, &SGWThemeCustomisationPage::updateElements);
}

void SGWThemeCustomisationPage::showThemeCustomLight(SGWButton */*unused*/){
    SGWThemeCustomisationPage::infoString = "Custom Light is a custom theme allowing the user to choose any main theme colour. The remaining theme colours will be interpolated from the main theme colour, mostly between white and the main theme colour.";
    SGWThemeCustomisationPage::isUsingCustomLight = true;
    const SGXColourRGBA baseColour = SGXColourRGBA(static_cast<int>(100.0f * SGXRandomNumberGenerator::rng0To1() + 50.0f), static_cast<int>(100.0f * SGXRandomNumberGenerator::rng0To1() + 50.0f), static_cast<int>(100.0f * SGXRandomNumberGenerator::rng0To1() + 50.0f));
    const SGXColourRGBA black = SGXColourRGBA(0, 0, 0);
    const SGXColourRGBA white = SGXColourRGBA(255, 255, 255);
    SGWThemeCustomisationPage::themeColours.at(0) = black;
    SGWThemeCustomisationPage::themeColours.at(1) = baseColour.linearInterpolate(black, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(2) = baseColour.linearInterpolate(black, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(3) = baseColour.linearInterpolate(black, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(4) = baseColour;
    SGWThemeCustomisationPage::themeColours.at(5) = baseColour.linearInterpolate(white, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(6) = baseColour.linearInterpolate(white, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(7) = baseColour.linearInterpolate(white, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(8) = white;
    SGWBackground::enable(SGWThemeCustomisationPage::detailsInstance, &SGWThemeCustomisationPage::initialiseDetailsPage, &SGWThemeCustomisationPage::updateElements);
}

void SGWThemeCustomisationPage::showThemeCustomDark(SGWButton */*unused*/){
    SGWThemeCustomisationPage::infoString = "Custom Dark is a custom theme allowing the user to choose any main theme colour. The remaining theme colours will be interpolated from the main theme colour, mostly between black and the main theme colour.";
    SGWThemeCustomisationPage::isUsingCustomDark = true;
    const SGXColourRGBA baseColour = SGXColourRGBA(static_cast<int>(100.0f * SGXRandomNumberGenerator::rng0To1() + 155.0f), static_cast<int>(100.0f * SGXRandomNumberGenerator::rng0To1() + 155.0f), static_cast<int>(100.0f * SGXRandomNumberGenerator::rng0To1() + 155.0f));
    const SGXColourRGBA black = SGXColourRGBA(0, 0, 0);
    const SGXColourRGBA white = SGXColourRGBA(255, 255, 255);
    SGWThemeCustomisationPage::themeColours.at(0) = white;
    SGWThemeCustomisationPage::themeColours.at(1) = baseColour.linearInterpolate(white, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(2) = baseColour.linearInterpolate(white, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(3) = baseColour.linearInterpolate(white, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(4) = baseColour;
    SGWThemeCustomisationPage::themeColours.at(5) = baseColour.linearInterpolate(black, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(6) = baseColour.linearInterpolate(black, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(7) = baseColour.linearInterpolate(black, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(8) = black;
    SGWBackground::enable(SGWThemeCustomisationPage::detailsInstance, &SGWThemeCustomisationPage::initialiseDetailsPage, &SGWThemeCustomisationPage::updateElements);
}

void SGWThemeCustomisationPage::showThemeCustomAny(SGWButton */*unused*/){
    SGWThemeCustomisationPage::infoString = "Custom Any gives the user full control over all theme colours by allowing all 9 theme colours to be set directly.";
    SGWThemeCustomisationPage::isUsingCustomAny = true;
    for(int i=0; i<9; i++){
        SGWThemeCustomisationPage::themeColours.at(i) = SGXColourHSLA(360.0f * static_cast<float>(SGXRandomNumberGenerator::rng0To1()), 50.0f, 12.5f * static_cast<float>(i), 100.0f).toRGBA();
    }
    SGWBackground::enable(SGWThemeCustomisationPage::detailsInstance, &SGWThemeCustomisationPage::initialiseDetailsPage, &SGWThemeCustomisationPage::updateElements);
}

void SGWThemeCustomisationPage::updateCustomLight(SGWColourPickerWidget *selector){
    SGXColourRGBA baseColour = (*selector).getColour();
    baseColour.setTransparency(255);
    const SGXColourRGBA black = SGXColourRGBA(0, 0, 0);
    const SGXColourRGBA white = SGXColourRGBA(255, 255, 255);
    SGWThemeCustomisationPage::themeColours.at(0) = black;
    SGWThemeCustomisationPage::themeColours.at(1) = baseColour.linearInterpolate(black, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(2) = baseColour.linearInterpolate(black, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(3) = baseColour.linearInterpolate(black, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(4) = baseColour;
    SGWThemeCustomisationPage::themeColours.at(5) = baseColour.linearInterpolate(white, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(6) = baseColour.linearInterpolate(white, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(7) = baseColour.linearInterpolate(white, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(8) = white;
    SGWThemeCustomisationPage::updateElements();
}

void SGWThemeCustomisationPage::updateCustomDark(SGWColourPickerWidget *selector){
    SGXColourRGBA baseColour = (*selector).getColour();
    baseColour.setTransparency(255);
    const SGXColourRGBA black = SGXColourRGBA(0, 0, 0);
    const SGXColourRGBA white = SGXColourRGBA(255, 255, 255);
    SGWThemeCustomisationPage::themeColours.at(0) = white;
    SGWThemeCustomisationPage::themeColours.at(1) = baseColour.linearInterpolate(white, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(2) = baseColour.linearInterpolate(white, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(3) = baseColour.linearInterpolate(white, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(4) = baseColour;
    SGWThemeCustomisationPage::themeColours.at(5) = baseColour.linearInterpolate(black, 0.75f);
    SGWThemeCustomisationPage::themeColours.at(6) = baseColour.linearInterpolate(black, 0.5f);
    SGWThemeCustomisationPage::themeColours.at(7) = baseColour.linearInterpolate(black, 0.25f);
    SGWThemeCustomisationPage::themeColours.at(8) = black;
    SGWThemeCustomisationPage::updateElements();
}

void SGWThemeCustomisationPage::updateCustomAny(SGWColourPickerWidget *selector){
    int n = -1;
    for(int i=0; i<9; i++){
        if(SGWThemeCustomisationPage::customAnyColourPicker.at(i) == selector){n = i;}
    }
    SGXColourRGBA baseColour = (*selector).getColour();
    baseColour.setTransparency(255);
    SGWThemeCustomisationPage::themeColours.at(n) = baseColour;
    SGWThemeCustomisationPage::updateElements();
}

void SGWThemeCustomisationPage::cancelChanges(SGWButton */*unused*/){
    SGWBackground::disable(SGWThemeCustomisationPage::menuInstance);
    SGWBackground::disable(SGWThemeCustomisationPage::detailsInstance);
}

void SGWThemeCustomisationPage::confirmChanges(SGWButton */*unused*/){
    SGUCentralManagement::themeColour0 = SGWThemeCustomisationPage::themeColours.at(0);
    SGUCentralManagement::themeColour1 = SGWThemeCustomisationPage::themeColours.at(1);
    SGUCentralManagement::themeColour2 = SGWThemeCustomisationPage::themeColours.at(2);
    SGUCentralManagement::themeColour3 = SGWThemeCustomisationPage::themeColours.at(3);
    SGUCentralManagement::themeColour4 = SGWThemeCustomisationPage::themeColours.at(4);
    SGUCentralManagement::themeColour5 = SGWThemeCustomisationPage::themeColours.at(5);
    SGUCentralManagement::themeColour6 = SGWThemeCustomisationPage::themeColours.at(6);
    SGUCentralManagement::themeColour7 = SGWThemeCustomisationPage::themeColours.at(7);
    SGUCentralManagement::themeColour8 = SGWThemeCustomisationPage::themeColours.at(8);
    SGXThemeColoursCustomisation::syncThemeColours();
    SGWBackground::disable(SGWThemeCustomisationPage::menuInstance);
    SGWBackground::disable(SGWThemeCustomisationPage::detailsInstance);
    SGWNotify::notify("theme updated");
    SGWBackground::enable(SGWThemeCustomisationPage::notifInstance, &SGWThemeCustomisationPage::notifInitialise, nullptr);
}

SGWBackground* SGWThemeCustomisationPage::notifInitialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 8);
    const SGXString s = "Theme colours are not updated immediately, you must restart the app for changes to take effect.\n\nDuring the National Day period, the theme is locked at For Our Nation to celebrate. Any theme changes applied during that duration will take effect after the period ends.";
    new SGWLongLabel(bg, s, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWTextButton(bg, "ok", &SGWThemeCustomisationPage::closeNotif, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWThemeCustomisationPage::closeNotif(SGWButton */*unused*/){
    SGWBackground::disable(SGWThemeCustomisationPage::notifInstance);
}
