#include "sgwthemecustomisationpage.h"
#include "../widgets/sgwpagebackground.h"
#include "../widgets/sgwtextbutton.h"
#include "../widgets/sgwbackground.h"
#include "../widgets/sgwwidget.h"
#include "../widgets/sgwbutton.h"
#include "../primitives/sgxcolourrgba.h"
#include "../widgets/sgwsequentialscrollview.h"
#include "../widgets/sgwsequentiallonglabel.h"
#include "../widgets/sgwlabel.h"
#include <array>
#include "../widgets/sgwblankwidget.h"

SGWBackground* SGWThemeCustomisationPage::menuInstance = nullptr;
SGWBackground* SGWThemeCustomisationPage::detailsInstance = nullptr;
SGWButton* SGWThemeCustomisationPage::cancelButton = nullptr;
SGWButton* SGWThemeCustomisationPage::confirmButton = nullptr;
SGWBackground* SGWThemeCustomisationPage::detailsScroll = nullptr;
SGWLabel* SGWThemeCustomisationPage::detailsInfo = nullptr;
std::array<SGWBlankWidget*, 9> SGWThemeCustomisationPage::coloursDisplay = {};
std::array<SGXColourRGBA, 9> SGWThemeCustomisationPage::themeColours = {};

void SGWThemeCustomisationPage::activate(){
    SGWBackground::enable(SGWThemeCustomisationPage::menuInstance, &SGWThemeCustomisationPage::initialise, nullptr);
}

SGWBackground* SGWThemeCustomisationPage::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6, false);
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
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 8, false);
    SGWThemeCustomisationPage::detailsScroll = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, 8, false);
    SGWThemeCustomisationPage::cancelButton = new SGWTextButton(bg, "cancel", nullptr, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGWThemeCustomisationPage::confirmButton = new SGWTextButton(bg, "choose", nullptr, 0.5f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    new SGWBlankWidget(SGWThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f, -1);
    SGWWidget* s = new SGWBlankWidget(SGWThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.0f, -1);
    SGWThemeCustomisationPage::detailsInfo = new SGWSequentialLongLabel(SGWThemeCustomisationPage::detailsScroll, "", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    float x = 0.0f;
    for(int i=0; i<9; i++){
        float w = 1.0f;
        if(i == 4 || i == 6 || i == 8){w = 3.0f;}
        SGWThemeCustomisationPage::coloursDisplay.at(i) = new SGWBlankWidget(s, x / 15.0f, 0.0f, 0.0f, 0.0f, w / 15.0f, 0.0f, 0.0f, 2.0f, i);
        x += w;
    }
    return bg;
}

void SGWThemeCustomisationPage::showThemeDefaultLight(SGWButton */*unused*/){
    SGWBackground::enable(SGWThemeCustomisationPage::detailsInstance, &SGWThemeCustomisationPage::initialiseDetailsPage, nullptr);
}

void SGWThemeCustomisationPage::showThemeDefaultDark(SGWButton */*unused*/){
    
}

void SGWThemeCustomisationPage::showThemeForOurNation(SGWButton */*unused*/){
    
}

void SGWThemeCustomisationPage::showThemeCustomLight(SGWButton */*unused*/){
    
}

void SGWThemeCustomisationPage::showThemeCustomDark(SGWButton */*unused*/){
    
}

void SGWThemeCustomisationPage::showThemeCustomAny(SGWButton */*unused*/){
    
}
