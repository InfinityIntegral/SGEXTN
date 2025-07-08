#include "sgxthemecolourspage.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QQuickItem>

QQuickItem* SGXThemeColoursPage::instance = nullptr;

void SGXThemeColoursPage::activate(){
    if(SGXThemeColoursPage::instance == nullptr){SGXThemeColoursPage::initialise();}
    (*SGXThemeColoursPage::instance).setVisible(true);
}

void SGXThemeColoursPage::initialise(){
    SGXThemeColoursPage::instance = SGXQuickUIInterface::createScrollView(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 30.0f, 0.0f, 0.5f, 8);
    SGXQuickUIInterface::createTitle(SGXThemeColoursPage::instance, "Theme Colours", 0.5f, -6.0f, 0.0f, 0.5f, 0.0f, 12.0f, 0.0f, 2.0f);
}
