#include "sgxthemecolourspage.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QQuickItem>
#include <QString>
#include "../primitives/sgxcolourrgba.h"

QQuickItem* SGXThemeColoursPage::instance = nullptr;

void SGXThemeColoursPage::activate(){
    if(SGXThemeColoursPage::instance == nullptr){SGXThemeColoursPage::initialise();}
    (*SGXThemeColoursPage::instance).setVisible(true);
}

void SGXThemeColoursPage::initialise(){
    SGXThemeColoursPage::instance = SGXQuickUIInterface::createScrollView(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 50.0f, 0.0f, 0.5f, 8);
    SGXQuickUIInterface::createTitle(SGXThemeColoursPage::instance, "Theme Colours", 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 0.0f, 2.0f);
    SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::instance, "Be the Light", &SGXThemeColoursPage::setThemeDefaultLight, 0.0f, 0.5f, 0.0f, 2.5f, 1.0f, -1.5f, 0.0f, 1.0f);
    QQuickItem* obj = nullptr;
    QString s = "";
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.0f / 11.1f, 0.5f - 0.0f / 11.f * 1.5f, 0.0f, 4.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(0, 0, 0).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.2f / 11.1f, 0.5f - 0.2f / 11.f * 1.5f, 0.0f, 4.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(64, 0, 50).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.4f / 11.1f, 0.5f - 0.4f / 11.f * 1.5f, 0.0f, 4.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(128, 0, 100).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 1.2f / 11.1f, 0.5f - 1.2f / 11.f * 1.5f, 0.0f, 4.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(191, 0, 150).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 2.0f / 11.1f, 0.5f - 2.0f / 11.f * 1.5f, 0.0f, 4.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 0, 200).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 4.5f / 11.1f, 0.5f - 4.5f / 11.f * 1.5f, 0.0f, 4.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 64, 214).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 5.3f / 11.1f, 0.5f - 5.3f / 11.f * 1.5f, 0.0f, 4.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 128, 227).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 7.8f / 11.1f, 0.5f - 7.8f / 11.f * 1.5f, 0.0f, 4.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 191, 241).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 8.6f / 11.1f, 0.5f - 8.6f / 11.f * 1.5f, 0.0f, 4.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 255, 255).getQColour());
    s = "we can be the light\nfor the world to be better\nlight every heart\nbe the sun of hope\n(Be the Light, 2020)\n\nBe the Light is the default light mode theme of all SGEXTN apps, featuring a white background typical for light mode themes with the iconic bright pink accent used by SGEXTN. The theme represents positivity, kindness, and other Singaporean values, and is inspired by the National Day song of the same name.";
    SGXQuickUIInterface::createLongText(SGXThemeColoursPage::instance, s, 0.0f, 0.5f, 0.0f, 6.5f, 1.0f, -1.5f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::instance, "Shine From Within", &SGXThemeColoursPage::setThemeDefaultDark, 0.0f, 0.5f, 0.0f, 17.0f, 1.0f, -1.5f, 0.0f, 1.0f);
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.0f / 11.1f, 0.5f - 0.0f / 11.f * 1.5f, 0.0f, 18.5f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 255, 255).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.2f / 11.1f, 0.5f - 0.2f / 11.f * 1.5f, 0.0f, 18.5f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 191, 241).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.4f / 11.1f, 0.5f - 0.4f / 11.f * 1.5f, 0.0f, 18.5f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 128, 227).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 1.2f / 11.1f, 0.5f - 1.2f / 11.f * 1.5f, 0.0f, 18.5f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 64, 214).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 2.0f / 11.1f, 0.5f - 2.0f / 11.f * 1.5f, 0.0f, 18.5f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 0, 200).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 4.5f / 11.1f, 0.5f - 4.5f / 11.f * 1.5f, 0.0f, 18.5f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(191, 0, 150).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 5.3f / 11.1f, 0.5f - 5.3f / 11.f * 1.5f, 0.0f, 18.5f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(128, 0, 100).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 7.8f / 11.1f, 0.5f - 7.8f / 11.f * 1.5f, 0.0f, 18.5f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(64, 0, 50).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 8.6f / 11.1f, 0.5f - 8.6f / 11.f * 1.5f, 0.0f, 18.5f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(0, 0, 0).getQColour());
    s = "although life has changed\nwe can lend a helping hand\nthinking back, we'll see\nthe path of light shines from within\n(Be the Light, 2020)\n\nShine From Within is the default dark mode theme of all SGEXTN apps, featuring a black background typical for dark mode themes with the iconic bright pink accent used by SGEXTN. Similar to its light mode equivalent, the theme represents positivity, kindness, and other Singaporean values, and is inspired by the National Day song Be the Light.";
    SGXQuickUIInterface::createLongText(SGXThemeColoursPage::instance, s, 0.0f, 0.5f, 0.0f, 21.0f, 1.0f, -1.5f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::instance, "For Our Nation", &SGXThemeColoursPage::setThemeForOurNation, 0.0f, 0.5f, 0.0f, 31.5f, 1.0f, -1.5f, 0.0f, 1.0f);
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.0f / 11.1f, 0.5f - 0.0f / 11.f * 1.5f, 0.0f, 33.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(0, 0, 0).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.2f / 11.1f, 0.5f - 0.2f / 11.f * 1.5f, 0.0f, 33.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(60, 9, 14).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.4f / 11.1f, 0.5f - 0.4f / 11.f * 1.5f, 0.0f, 33.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(119, 19, 27).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 1.2f / 11.1f, 0.5f - 1.2f / 11.f * 1.5f, 0.0f, 33.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(179, 28, 41).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 2.0f / 11.1f, 0.5f - 2.0f / 11.f * 1.5f, 0.0f, 33.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(238, 37, 54).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 4.5f / 11.1f, 0.5f - 4.5f / 11.f * 1.5f, 0.0f, 33.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(242, 92, 104).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 5.3f / 11.1f, 0.5f - 5.3f / 11.f * 1.5f, 0.0f, 33.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(247, 146, 155).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 7.8f / 11.1f, 0.5f - 7.8f / 11.f * 1.5f, 0.0f, 33.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(251, 201, 205).getQColour());
    obj = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 8.6f / 11.1f, 0.5f - 8.6f / 11.f * 1.5f, 0.0f, 33.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    (*obj).setProperty("color", SGXColourRGBA(255, 255, 255).getQColour());
    s = "For Our Nation is the National Day special theme applied to all SGEXTN apps during the National Day period, overwriting any theme settings defined by the user. The theme features a mix of red and white, both being the exact same colour as the colours on our flag. The name of the theme comes from our pledge.";
    SGXQuickUIInterface::createLongText(SGXThemeColoursPage::instance, s, 0.0f, 0.5f, 0.0f, 35.5f, 1.0f, -1.5f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.5f);
}

void SGXThemeColoursPage::setThemeDefaultLight(){
    
}

void SGXThemeColoursPage::setThemeDefaultDark(){
    
}

void SGXThemeColoursPage::setThemeForOurNation(){
    
}
