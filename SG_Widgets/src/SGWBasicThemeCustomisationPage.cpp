#include <private_api_Widgets/SGWBasicThemeCustomisationPage.h>
#include <SGWPageBackground.h>
#include <SGWTextButton.h>
#include <SGWBackground.h>
#include <SGWWidget.h>
#include <SGWButton.h>
#include <SGXColourRGBA.h>
#include <SGWSequentialScrollView.h>
#include <SGWSequentialLongLabel.h>
#include <SGWLabel.h>
#include <SGLArray.h>
#include <SGWBlankWidget.h>
#include <SGXString.h>
#include <SGWTextLabel.h>
#include <SGXThemeColoursCustomisation.h>
#include <SGWLongLabel.h>
#include <SGWNotify.h>

SGWBackground* SGWBasicThemeCustomisationPage::menuInstance = nullptr;
SGWBackground* SGWBasicThemeCustomisationPage::detailsInstance = nullptr;
SGWButton* SGWBasicThemeCustomisationPage::cancelButton = nullptr;
SGWButton* SGWBasicThemeCustomisationPage::confirmButton = nullptr;
SGWBackground* SGWBasicThemeCustomisationPage::detailsScroll = nullptr;
SGWLabel* SGWBasicThemeCustomisationPage::detailsInfo = nullptr;
SGLArray<SGWBlankWidget*> SGWBasicThemeCustomisationPage::coloursDisplay = SGLArray<SGWBlankWidget*>(9);
SGLArray<SGXColourRGBA> SGWBasicThemeCustomisationPage::themeColours = SGLArray<SGXColourRGBA>(9);
SGXString SGWBasicThemeCustomisationPage::infoString = "";
SGWBackground* SGWBasicThemeCustomisationPage::notifInstance = nullptr;

void SGWBasicThemeCustomisationPage::activate(){
    SGWBackground::enable(SGWBasicThemeCustomisationPage::menuInstance, &SGWBasicThemeCustomisationPage::initialise, nullptr);
}

SGWBackground* SGWBasicThemeCustomisationPage::initialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    SGWButton* b = nullptr;
    b = new SGWTextButton(bg, "Be the Light", &SGWBasicThemeCustomisationPage::showThemeDefaultLight, 0.0f, 0.0f, 0.5f, -3.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(255, 0, 200));
    (*b).setForegroundColour(SGXColourRGBA(255, 255, 255));
    (*b).setBackgroundHoverColour(SGXColourRGBA(191, 0, 150));
    (*b).setForegroundHoverColour(SGXColourRGBA(255, 191, 241));
    (*b).setBackgroundFocusColour(SGXColourRGBA(128, 0, 100));
    (*b).setForegroundFocusColour(SGXColourRGBA(255, 128, 227));
    b = new SGWTextButton(bg, "Shine From Within", &SGWBasicThemeCustomisationPage::showThemeDefaultDark, 0.0f, 0.0f, 0.5f, -2.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(255, 0, 200));
    (*b).setForegroundColour(SGXColourRGBA(0, 0, 0));
    (*b).setBackgroundHoverColour(SGXColourRGBA(255, 64, 214));
    (*b).setForegroundHoverColour(SGXColourRGBA(64, 0, 50));
    (*b).setBackgroundFocusColour(SGXColourRGBA(255, 128, 227));
    (*b).setForegroundFocusColour(SGXColourRGBA(128, 0, 100));
    b = new SGWTextButton(bg, "For Our Nation", &SGWBasicThemeCustomisationPage::showThemeForOurNation, 0.0f, 0.0f, 0.5f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    (*b).setBackgroundColour(SGXColourRGBA(238, 37, 54));
    (*b).setForegroundColour(SGXColourRGBA(255, 255, 255));
    (*b).setBackgroundHoverColour(SGXColourRGBA(179, 28, 41));
    (*b).setForegroundHoverColour(SGXColourRGBA(251, 201, 205));
    (*b).setBackgroundFocusColour(SGXColourRGBA(119, 19, 27));
    (*b).setForegroundFocusColour(SGXColourRGBA(247, 146, 155));
    return bg;
}

SGWBackground* SGWBasicThemeCustomisationPage::initialiseDetailsPage(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    SGWBasicThemeCustomisationPage::detailsScroll = new SGWSequentialScrollView(bg, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    SGWBasicThemeCustomisationPage::cancelButton = new SGWTextButton(bg, "cancel", &SGWBasicThemeCustomisationPage::cancelChanges, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    SGWBasicThemeCustomisationPage::confirmButton = new SGWTextButton(bg, "apply theme", &SGWBasicThemeCustomisationPage::confirmChanges, 0.5f, 0.0f, 1.0f, -1.0f, 0.5f, 0.0f, 0.0f, 1.0f);
    new SGWBlankWidget(SGWBasicThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.5f);
    SGWWidget* s = new SGWBlankWidget(SGWBasicThemeCustomisationPage::detailsScroll, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 2.5f);
    SGWBasicThemeCustomisationPage::detailsInfo = new SGWSequentialLongLabel(SGWBasicThemeCustomisationPage::detailsScroll, "", 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f);
    float x = 0.0f;
    for(int i=0; i<9; i++){
        float w = 1.0f;
        if(i == 4 || i == 6 || i == 8){w = 3.0f;}
        SGWBasicThemeCustomisationPage::coloursDisplay.at(i) = new SGWBlankWidget(s, x / 15.0f, 0.0f, 0.0f, 0.0f, w / 15.0f, 0.0f, 0.0f, 2.0f);
        (*SGWBasicThemeCustomisationPage::coloursDisplay.at(i)).setThemeColour(i);
        x += w;
    }
    return bg;
}

void SGWBasicThemeCustomisationPage::updateElements(){
    (*SGWBasicThemeCustomisationPage::detailsInfo).setTextFromString(SGWBasicThemeCustomisationPage::infoString);
    for(int i=0; i<9; i++){
        (*SGWBasicThemeCustomisationPage::coloursDisplay.at(i)).setColour(SGWBasicThemeCustomisationPage::themeColours.at(i));
    }
    (*SGWBasicThemeCustomisationPage::detailsInfo).setBackgroundColour(SGWBasicThemeCustomisationPage::themeColours.at(8));
    (*SGWBasicThemeCustomisationPage::detailsInfo).setForegroundColour(SGWBasicThemeCustomisationPage::themeColours.at(4));
    (*SGWBasicThemeCustomisationPage::detailsInstance).setColour(SGWBasicThemeCustomisationPage::themeColours.at(8));
    (*SGWBasicThemeCustomisationPage::cancelButton).setBackgroundColour(SGWBasicThemeCustomisationPage::themeColours.at(4));
    (*SGWBasicThemeCustomisationPage::cancelButton).setForegroundColour(SGWBasicThemeCustomisationPage::themeColours.at(8));
    (*SGWBasicThemeCustomisationPage::cancelButton).setBackgroundHoverColour(SGWBasicThemeCustomisationPage::themeColours.at(3));
    (*SGWBasicThemeCustomisationPage::cancelButton).setForegroundHoverColour(SGWBasicThemeCustomisationPage::themeColours.at(7));
    (*SGWBasicThemeCustomisationPage::cancelButton).setBackgroundFocusColour(SGWBasicThemeCustomisationPage::themeColours.at(2));
    (*SGWBasicThemeCustomisationPage::cancelButton).setForegroundFocusColour(SGWBasicThemeCustomisationPage::themeColours.at(6));
    (*SGWBasicThemeCustomisationPage::confirmButton).setBackgroundColour(SGWBasicThemeCustomisationPage::themeColours.at(4));
    (*SGWBasicThemeCustomisationPage::confirmButton).setForegroundColour(SGWBasicThemeCustomisationPage::themeColours.at(8));
    (*SGWBasicThemeCustomisationPage::confirmButton).setBackgroundHoverColour(SGWBasicThemeCustomisationPage::themeColours.at(3));
    (*SGWBasicThemeCustomisationPage::confirmButton).setForegroundHoverColour(SGWBasicThemeCustomisationPage::themeColours.at(7));
    (*SGWBasicThemeCustomisationPage::confirmButton).setBackgroundFocusColour(SGWBasicThemeCustomisationPage::themeColours.at(2));
    (*SGWBasicThemeCustomisationPage::confirmButton).setForegroundFocusColour(SGWBasicThemeCustomisationPage::themeColours.at(6));
    (*SGWBasicThemeCustomisationPage::detailsScroll).setColour(SGWBasicThemeCustomisationPage::themeColours.at(8));
    SGWSequentialScrollView* x = static_cast<SGWSequentialScrollView*>(SGWBasicThemeCustomisationPage::detailsScroll);
    (*x).setScrollbarBackgroundColour(SGWBasicThemeCustomisationPage::themeColours.at(4));
    (*x).setScrollbarForegroundColour(SGWBasicThemeCustomisationPage::themeColours.at(6));
    (*x).setScrollbarBackgroundHoverColour(SGWBasicThemeCustomisationPage::themeColours.at(3));
    (*x).setScrollbarForegroundHoverColour(SGWBasicThemeCustomisationPage::themeColours.at(5));
    (*x).setScrollbarBackgroundFocusColour(SGWBasicThemeCustomisationPage::themeColours.at(2));
    (*x).setScrollbarForegroundFocusColour(SGWBasicThemeCustomisationPage::themeColours.at(4));
}

void SGWBasicThemeCustomisationPage::showThemeDefaultLight(){
    SGWBasicThemeCustomisationPage::infoString = "we can be the light\nfor the world to be better\nlight every heart\nbe the sun of hope\n(Be the Light, 2020)\n\nBe the Light is the default light mode theme of all SGEXTN apps, featuring a white background typical for light mode themes with the iconic bright pink accent used by SGEXTN. The theme represents positivity, kindness, and Singaporean values in general, and is inspired by the National Day song of the same name.";
    SGWBasicThemeCustomisationPage::themeColours.at(0) = SGXColourRGBA(0, 0, 0);
    SGWBasicThemeCustomisationPage::themeColours.at(1) = SGXColourRGBA(64, 0, 50);
    SGWBasicThemeCustomisationPage::themeColours.at(2) = SGXColourRGBA(128, 0, 100);
    SGWBasicThemeCustomisationPage::themeColours.at(3) = SGXColourRGBA(191, 0, 150);
    SGWBasicThemeCustomisationPage::themeColours.at(4) = SGXColourRGBA(255, 0, 200);
    SGWBasicThemeCustomisationPage::themeColours.at(5) = SGXColourRGBA(255, 64, 214);
    SGWBasicThemeCustomisationPage::themeColours.at(6) = SGXColourRGBA(255, 128, 227);
    SGWBasicThemeCustomisationPage::themeColours.at(7) = SGXColourRGBA(255, 191, 241);
    SGWBasicThemeCustomisationPage::themeColours.at(8) = SGXColourRGBA(255, 255, 255);
    SGWBackground::enable(SGWBasicThemeCustomisationPage::detailsInstance, &SGWBasicThemeCustomisationPage::initialiseDetailsPage, &SGWBasicThemeCustomisationPage::updateElements);
}

void SGWBasicThemeCustomisationPage::showThemeDefaultDark(){
    SGWBasicThemeCustomisationPage::infoString = "although life has changed\nwe can lend a helping hand\nthinking back, we'll see\nthe path of light shines from within\n(Be the Light, 2020)\n\nShine From Within is the default dark mode theme of all SGEXTN apps, featuring a black background typical for dark mode themes with the iconic bright pink accent used by SGEXTN. Similar to its light mode equivalent, the theme represents positivity, kindness, and Singaporean values in general, and is inspired by the National Day song Be the Light.";
    SGWBasicThemeCustomisationPage::themeColours.at(0) = SGXColourRGBA(255, 255, 255);
    SGWBasicThemeCustomisationPage::themeColours.at(1) = SGXColourRGBA(255, 191, 241);
    SGWBasicThemeCustomisationPage::themeColours.at(2) = SGXColourRGBA(255, 128, 227);
    SGWBasicThemeCustomisationPage::themeColours.at(3) = SGXColourRGBA(255, 64, 214);
    SGWBasicThemeCustomisationPage::themeColours.at(4) = SGXColourRGBA(255, 0, 200);
    SGWBasicThemeCustomisationPage::themeColours.at(5) = SGXColourRGBA(191, 0, 150);
    SGWBasicThemeCustomisationPage::themeColours.at(6) = SGXColourRGBA(128, 0, 100);
    SGWBasicThemeCustomisationPage::themeColours.at(7) = SGXColourRGBA(64, 0, 50);
    SGWBasicThemeCustomisationPage::themeColours.at(8) = SGXColourRGBA(0, 0, 0);
    SGWBackground::enable(SGWBasicThemeCustomisationPage::detailsInstance, &SGWBasicThemeCustomisationPage::initialiseDetailsPage, &SGWBasicThemeCustomisationPage::updateElements);
}

void SGWBasicThemeCustomisationPage::showThemeForOurNation(){
    SGWBasicThemeCustomisationPage::infoString = "You, my people, my home,\nour lives, defend and uphold,\nmay the good we achieve,\nas one nation,\nbe shared with the world\n(My People My Home, 1995)\n\nFor Our Nation is the National Day special theme applied to all SGEXTN apps during the National Day period, overwriting any theme settings defined by the user. The theme features a mix of red and white, both being the exact same colour as the colours on our flag. The name of the theme comes from our pledge.";
    SGWBasicThemeCustomisationPage::themeColours.at(0) = SGXColourRGBA(0, 0, 0);
    SGWBasicThemeCustomisationPage::themeColours.at(1) = SGXColourRGBA(60, 9, 14);
    SGWBasicThemeCustomisationPage::themeColours.at(2) = SGXColourRGBA(119, 19, 27);
    SGWBasicThemeCustomisationPage::themeColours.at(3) = SGXColourRGBA(179, 28, 41);
    SGWBasicThemeCustomisationPage::themeColours.at(4) = SGXColourRGBA(238, 37, 54);
    SGWBasicThemeCustomisationPage::themeColours.at(5) = SGXColourRGBA(242, 92, 104);
    SGWBasicThemeCustomisationPage::themeColours.at(6) = SGXColourRGBA(247, 146, 155);
    SGWBasicThemeCustomisationPage::themeColours.at(7) = SGXColourRGBA(251, 201, 205);
    SGWBasicThemeCustomisationPage::themeColours.at(8) = SGXColourRGBA(255, 255, 255);
    SGWBackground::enable(SGWBasicThemeCustomisationPage::detailsInstance, &SGWBasicThemeCustomisationPage::initialiseDetailsPage, &SGWBasicThemeCustomisationPage::updateElements);
}

void SGWBasicThemeCustomisationPage::cancelChanges(){
    SGWBackground::disable(SGWBasicThemeCustomisationPage::detailsInstance);
    SGWBackground::disable(SGWBasicThemeCustomisationPage::menuInstance);
}

void SGWBasicThemeCustomisationPage::confirmChanges(){
    SGXThemeColoursCustomisation::themeColour0 = SGWBasicThemeCustomisationPage::themeColours.at(0);
    SGXThemeColoursCustomisation::themeColour1 = SGWBasicThemeCustomisationPage::themeColours.at(1);
    SGXThemeColoursCustomisation::themeColour2 = SGWBasicThemeCustomisationPage::themeColours.at(2);
    SGXThemeColoursCustomisation::themeColour3 = SGWBasicThemeCustomisationPage::themeColours.at(3);
    SGXThemeColoursCustomisation::themeColour4 = SGWBasicThemeCustomisationPage::themeColours.at(4);
    SGXThemeColoursCustomisation::themeColour5 = SGWBasicThemeCustomisationPage::themeColours.at(5);
    SGXThemeColoursCustomisation::themeColour6 = SGWBasicThemeCustomisationPage::themeColours.at(6);
    SGXThemeColoursCustomisation::themeColour7 = SGWBasicThemeCustomisationPage::themeColours.at(7);
    SGXThemeColoursCustomisation::themeColour8 = SGWBasicThemeCustomisationPage::themeColours.at(8);
    SGXThemeColoursCustomisation::syncThemeColours();
    SGWBackground::disable(SGWBasicThemeCustomisationPage::detailsInstance);
    SGWBackground::disable(SGWBasicThemeCustomisationPage::menuInstance);
    SGWNotify::notify("theme updated");
    SGWBackground::enable(SGWBasicThemeCustomisationPage::notifInstance, &SGWBasicThemeCustomisationPage::notifInitialise, nullptr);
}

SGWBackground* SGWBasicThemeCustomisationPage::notifInitialise(){
    SGWBackground* bg = new SGWPageBackground(SGWWidget::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
    const SGXString s = "Theme colours are not updated immediately, you must restart the app for changes to take effect.\n\nDuring the National Day period, the theme is locked at For Our Nation to celebrate. Any theme changes applied during that duration will take effect after the period ends.";
    new SGWLongLabel(bg, s, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.5f);
    new SGWTextButton(bg, "ok", &SGWBasicThemeCustomisationPage::closeNotif, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
    return bg;
}

void SGWBasicThemeCustomisationPage::closeNotif(){
    SGWBackground::disable(SGWBasicThemeCustomisationPage::notifInstance);
}
