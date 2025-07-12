#include "sgxthemecolourspage.h"
#include "../quickui/sgxquickuiinterface.h"
#include <QQuickItem>
#include <QString>
#include "../primitives/sgxcolourrgba.h"
#include <array>
#include "../customisation/sgxthemecolourscustomisation.h"
#include "../customisation/sgxvesiclespropertiescustomisation.h"
#include "../userDefinedClasses/sgucentralmanagement.h"

QQuickItem* SGXThemeColoursPage::instance = nullptr;
std::array<QQuickItem*, 9> SGXThemeColoursPage::customLightColoursDisplay = {};
QQuickItem* SGXThemeColoursPage::customLightMainColourPicker = nullptr;
std::array<QQuickItem*, 9> SGXThemeColoursPage::customDarkColoursDisplay = {};
QQuickItem* SGXThemeColoursPage::customDarkMainColourPicker = nullptr;
std::array<QQuickItem*, 9> SGXThemeColoursPage::customAnyColoursDisplay = {};
std::array<QQuickItem*, 9> SGXThemeColoursPage::customAnyColourPicker = {};
std::array<SGXColourRGBA, 9> SGXThemeColoursPage::coloursToSet = {};
QQuickItem* SGXThemeColoursPage::confirmDialog = nullptr;
bool SGXThemeColoursPage::includeVesicleInTheme = false;

void SGXThemeColoursPage::activate(){
    if(SGXThemeColoursPage::instance == nullptr){SGXThemeColoursPage::initialise();}
    (*SGXThemeColoursPage::instance).setVisible(true);
}

void SGXThemeColoursPage::initialise(){
    SGXThemeColoursPage::instance = SGXQuickUIInterface::createScrollView(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 108.0f, 0.0f, 0.5f, 8);
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
    SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::instance, "Custom Light", &SGXThemeColoursPage::setThemeCustomLight, 0.0f, 0.5f, 0.0f, 46.0f, 1.0f, -1.5f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXThemeColoursPage::instance, "main theme colour:", 0.0f, 0.5f, 0.0f, 47.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXThemeColoursPage::customLightMainColourPicker = SGXQuickUIInterface::createColourPicker(SGXThemeColoursPage::instance, 0.5f, 0.1f, 0.0f, 47.5f, 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 100));
    connect(SGXThemeColoursPage::customLightMainColourPicker, &QQuickItem::opacityChanged, &SGXThemeColoursPage::updateThemeCustomLight);
    SGXThemeColoursPage::customLightColoursDisplay[0] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.0f / 11.1f, 0.5f - 0.0f / 11.f * 1.5f, 0.0f, 49.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[1] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.2f / 11.1f, 0.5f - 0.2f / 11.f * 1.5f, 0.0f, 49.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[2] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.4f / 11.1f, 0.5f - 0.4f / 11.f * 1.5f, 0.0f, 49.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[3] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 1.2f / 11.1f, 0.5f - 1.2f / 11.f * 1.5f, 0.0f, 49.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[4] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 2.0f / 11.1f, 0.5f - 2.0f / 11.f * 1.5f, 0.0f, 49.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[5] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 4.5f / 11.1f, 0.5f - 4.5f / 11.f * 1.5f, 0.0f, 49.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[6] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 5.3f / 11.1f, 0.5f - 5.3f / 11.f * 1.5f, 0.0f, 49.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[7] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 7.8f / 11.1f, 0.5f - 7.8f / 11.f * 1.5f, 0.0f, 49.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customLightColoursDisplay[8] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 8.6f / 11.1f, 0.5f - 8.6f / 11.f * 1.5f, 0.0f, 49.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    s = "Custom Light is a custom theme allowing the user to choose any main theme colour. The remaining theme colours will be interpolated from the main theme colour, mostly between white and the main theme colour. Note that Be the Light is equivalent to Custom Light with the main colour being 05524F pink and For Our Nation is equivalent to Custom Light with the main colour being Singapore red.";
    SGXQuickUIInterface::createLongText(SGXThemeColoursPage::instance, s, 0.0f, 0.5f, 0.0f, 51.5f, 1.0f, -1.5f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXThemeColoursPage::updateThemeCustomLight();
    SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::instance, "Custom Dark", &SGXThemeColoursPage::setThemeCustomDark, 0.0f, 0.5f, 0.0f, 62.0f, 1.0f, -1.5f, 0.0f, 1.0f);
    SGXQuickUIInterface::createRightText(SGXThemeColoursPage::instance, "main theme colour:", 0.0f, 0.5f, 0.0f, 63.5f, 0.5f, -0.6f, 0.0f, 1.0f);
    SGXThemeColoursPage::customDarkMainColourPicker = SGXQuickUIInterface::createColourPicker(SGXThemeColoursPage::instance, 0.5f, 0.1f, 0.0f, 63.5f, 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(255, 0, 100));
    connect(SGXThemeColoursPage::customDarkMainColourPicker, &QQuickItem::opacityChanged, &SGXThemeColoursPage::updateThemeCustomDark);
    SGXThemeColoursPage::customDarkColoursDisplay[0] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.0f / 11.1f, 0.5f - 0.0f / 11.f * 1.5f, 0.0f, 65.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[1] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.2f / 11.1f, 0.5f - 0.2f / 11.f * 1.5f, 0.0f, 65.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[2] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.4f / 11.1f, 0.5f - 0.4f / 11.f * 1.5f, 0.0f, 65.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[3] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 1.2f / 11.1f, 0.5f - 1.2f / 11.f * 1.5f, 0.0f, 65.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[4] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 2.0f / 11.1f, 0.5f - 2.0f / 11.f * 1.5f, 0.0f, 65.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[5] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 4.5f / 11.1f, 0.5f - 4.5f / 11.f * 1.5f, 0.0f, 65.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[6] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 5.3f / 11.1f, 0.5f - 5.3f / 11.f * 1.5f, 0.0f, 65.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[7] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 7.8f / 11.1f, 0.5f - 7.8f / 11.f * 1.5f, 0.0f, 65.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customDarkColoursDisplay[8] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 8.6f / 11.1f, 0.5f - 8.6f / 11.f * 1.5f, 0.0f, 65.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    s = "Custom Dark is a custom theme allowing the user to choose any main theme colour. The remaining theme colours will be interpolated from the main theme colour, mostly between black and the main theme colour. Note that Shine From Within is equivalent to Custom Dark with the main colour being 05524F pink.";
    SGXQuickUIInterface::createLongText(SGXThemeColoursPage::instance, s, 0.0f, 0.5f, 0.0f, 67.5f, 1.0f, -1.5f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXThemeColoursPage::updateThemeCustomDark();
    SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::instance, "Custom Any", &SGXThemeColoursPage::setThemeCustomDark, 0.0f, 0.5f, 0.0f, 78.0f, 1.0f, -1.5f, 0.0f, 1.0f);
    for(int i=0; i<=8; i++){
        SGXQuickUIInterface::createRightText(SGXThemeColoursPage::instance, "theme colour " + QString::number(i) + ":", 0.0f, 0.5f, 0.0f, 79.5f + 1.5f * static_cast<float>(i), 0.5f, -0.6f, 0.0f, 1.0f);
        SGXThemeColoursPage::customAnyColourPicker.at(i) = SGXQuickUIInterface::createColourPicker(SGXThemeColoursPage::instance, 0.5f, 0.1f, 0.0f, 79.5f + 1.5f * static_cast<float>(i), 0.0f, 4.0f, 0.0f, 1.0f, SGXColourRGBA(1.0f, 0.0f, static_cast<float>(i) / 8.0f));
        connect(SGXThemeColoursPage::customAnyColourPicker.at(i), &QQuickItem::opacityChanged, &SGXThemeColoursPage::updateThemeCustomAny);
    }
    SGXThemeColoursPage::customAnyColoursDisplay[0] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.0f / 11.1f, 0.5f - 0.0f / 11.f * 1.5f, 0.0f, 93.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[1] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.2f / 11.1f, 0.5f - 0.2f / 11.f * 1.5f, 0.0f, 93.0f, 0.2f / 11.1f, -1.5f * 0.2f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[2] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 0.4f / 11.1f, 0.5f - 0.4f / 11.f * 1.5f, 0.0f, 93.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[3] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 1.2f / 11.1f, 0.5f - 1.2f / 11.f * 1.5f, 0.0f, 93.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[4] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 2.0f / 11.1f, 0.5f - 2.0f / 11.f * 1.5f, 0.0f, 93.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[5] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 4.5f / 11.1f, 0.5f - 4.5f / 11.f * 1.5f, 0.0f, 93.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[6] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 5.3f / 11.1f, 0.5f - 5.3f / 11.f * 1.5f, 0.0f, 93.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[7] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 7.8f / 11.1f, 0.5f - 7.8f / 11.f * 1.5f, 0.0f, 93.0f, 0.8f / 11.1f, -1.5f * 0.8f / 11.1f, 0.0f, 2.0f, -1);
    SGXThemeColoursPage::customAnyColoursDisplay[8] = SGXQuickUIInterface::createWidget(SGXThemeColoursPage::instance, 8.6f / 11.1f, 0.5f - 8.6f / 11.f * 1.5f, 0.0f, 93.0f, 2.5f / 11.1f, -1.5f * 2.5f / 11.1f, 0.0f, 2.0f, -1);
    s = "Custom Any gives the user full control over all theme colours by allowing all 9 theme colours to be set directly.";
    SGXQuickUIInterface::createLongText(SGXThemeColoursPage::instance, s, 0.0f, 0.5f, 0.0f, 95.5f, 1.0f, -1.5f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 0.5f);
    SGXThemeColoursPage::updateThemeCustomAny();
}

void SGXThemeColoursPage::setThemeDefaultLight(){
    SGXThemeColoursPage::coloursToSet[0] = SGXColourRGBA(0, 0, 0);
    SGXThemeColoursPage::coloursToSet[1] = SGXColourRGBA(64, 0, 50);
    SGXThemeColoursPage::coloursToSet[2] = SGXColourRGBA(128, 0, 100);
    SGXThemeColoursPage::coloursToSet[3] = SGXColourRGBA(191, 0, 150);
    SGXThemeColoursPage::coloursToSet[4] = SGXColourRGBA(255, 0, 200);
    SGXThemeColoursPage::coloursToSet[5] = SGXColourRGBA(255, 64, 214);
    SGXThemeColoursPage::coloursToSet[6] = SGXColourRGBA(255, 128, 227);
    SGXThemeColoursPage::coloursToSet[7] = SGXColourRGBA(255, 191, 241);
    SGXThemeColoursPage::coloursToSet[8] = SGXColourRGBA(255, 255, 255);
    SGXThemeColoursPage::includeVesicleInTheme = true;
    SGXThemeColoursPage::activateConfirmDialog();
}

void SGXThemeColoursPage::setThemeDefaultDark(){
    SGXThemeColoursPage::coloursToSet[0] = SGXColourRGBA(255, 255, 255);
    SGXThemeColoursPage::coloursToSet[1] = SGXColourRGBA(255, 191, 241);
    SGXThemeColoursPage::coloursToSet[2] = SGXColourRGBA(255, 128, 227);
    SGXThemeColoursPage::coloursToSet[3] = SGXColourRGBA(255, 64, 214);
    SGXThemeColoursPage::coloursToSet[4] = SGXColourRGBA(255, 0, 200);
    SGXThemeColoursPage::coloursToSet[5] = SGXColourRGBA(191, 0, 150);
    SGXThemeColoursPage::coloursToSet[6] = SGXColourRGBA(128, 0, 100);
    SGXThemeColoursPage::coloursToSet[7] = SGXColourRGBA(64, 0, 50);
    SGXThemeColoursPage::coloursToSet[8] = SGXColourRGBA(0, 0, 0);
    SGXThemeColoursPage::includeVesicleInTheme = true;
    SGXThemeColoursPage::activateConfirmDialog();
}

void SGXThemeColoursPage::setThemeForOurNation(){
    SGXThemeColoursPage::coloursToSet[0] = SGXColourRGBA(0, 0, 0);
    SGXThemeColoursPage::coloursToSet[1] = SGXColourRGBA(60, 9, 14);
    SGXThemeColoursPage::coloursToSet[2] = SGXColourRGBA(119, 19, 27);
    SGXThemeColoursPage::coloursToSet[3] = SGXColourRGBA(179, 28, 41);
    SGXThemeColoursPage::coloursToSet[4] = SGXColourRGBA(238, 37, 54);
    SGXThemeColoursPage::coloursToSet[5] = SGXColourRGBA(242, 92, 104);
    SGXThemeColoursPage::coloursToSet[6] = SGXColourRGBA(247, 146, 155);
    SGXThemeColoursPage::coloursToSet[7] = SGXColourRGBA(251, 201, 205);
    SGXThemeColoursPage::coloursToSet[8] = SGXColourRGBA(255, 255, 255);
    SGXThemeColoursPage::includeVesicleInTheme = true;
    SGXThemeColoursPage::activateConfirmDialog();
}

void SGXThemeColoursPage::setThemeCustomLight(){
    
}

void SGXThemeColoursPage::setThemeCustomDark(){
    
}

void SGXThemeColoursPage::setThemeCustomAny(){
    
}

void SGXThemeColoursPage::updateThemeCustomLight(){
    bool ignore = false;
    SGXColourRGBA mainColour = SGXQuickUIInterface::getColourPickerColour(SGXThemeColoursPage::customLightMainColourPicker, ignore);
    mainColour.setTransparency(255);
    for(int i=0; i<4; i++){
        const SGXColourRGBA themeColour = mainColour.linearInterpolate(SGXColourRGBA(0, 0, 0), 0.25f * static_cast<float>(i));
        (*SGXThemeColoursPage::customLightColoursDisplay.at(i)).setProperty("color", themeColour.getQColour());
    }
    (*SGXThemeColoursPage::customLightColoursDisplay[4]).setProperty("color", mainColour.getQColour());
    for(int i=0; i<4; i++){
        const SGXColourRGBA themeColour = mainColour.linearInterpolate(SGXColourRGBA(255, 255, 255), 0.25f * static_cast<float>(3 - i));
        (*SGXThemeColoursPage::customLightColoursDisplay.at(5 + i)).setProperty("color", themeColour.getQColour());
    }
}

void SGXThemeColoursPage::updateThemeCustomDark(){
    bool ignore = false;
    SGXColourRGBA mainColour = SGXQuickUIInterface::getColourPickerColour(SGXThemeColoursPage::customDarkMainColourPicker, ignore);
    mainColour.setTransparency(255);
    for(int i=0; i<4; i++){
        const SGXColourRGBA themeColour = mainColour.linearInterpolate(SGXColourRGBA(255, 255, 255), 0.25f * static_cast<float>(i));
        (*SGXThemeColoursPage::customDarkColoursDisplay.at(i)).setProperty("color", themeColour.getQColour());
    }
    (*SGXThemeColoursPage::customDarkColoursDisplay[4]).setProperty("color", mainColour.getQColour());
    for(int i=0; i<4; i++){
        const SGXColourRGBA themeColour = mainColour.linearInterpolate(SGXColourRGBA(0, 0, 0), 0.25f * static_cast<float>(3 - i));
        (*SGXThemeColoursPage::customDarkColoursDisplay.at(5 + i)).setProperty("color", themeColour.getQColour());
    }
}

void SGXThemeColoursPage::updateThemeCustomAny(){
    bool ignore = false;
    for(int i=0; i<=8; i++){
        SGXColourRGBA col = SGXQuickUIInterface::getColourPickerColour(SGXThemeColoursPage::customAnyColourPicker.at(i), ignore);
        col.setTransparency(255);
        (*SGXThemeColoursPage::customAnyColoursDisplay.at(i)).setProperty("color", col.getQColour());
    }
}

void SGXThemeColoursPage::cancelThemeColourSettings(){
    (*SGXThemeColoursPage::confirmDialog).setVisible(false);
}

void SGXThemeColoursPage::confirmThemeColourSettings(){
    SGUCentralManagement::themeColour0 = SGXThemeColoursPage::coloursToSet[0];
    SGUCentralManagement::themeColour1 = SGXThemeColoursPage::coloursToSet[1];
    SGUCentralManagement::themeColour2 = SGXThemeColoursPage::coloursToSet[2];
    SGUCentralManagement::themeColour3 = SGXThemeColoursPage::coloursToSet[3];
    SGUCentralManagement::themeColour4 = SGXThemeColoursPage::coloursToSet[4];
    SGUCentralManagement::themeColour5 = SGXThemeColoursPage::coloursToSet[5];
    SGUCentralManagement::themeColour6 = SGXThemeColoursPage::coloursToSet[6];
    SGUCentralManagement::themeColour7 = SGXThemeColoursPage::coloursToSet[7];
    SGUCentralManagement::themeColour8 = SGXThemeColoursPage::coloursToSet[8];
    SGXThemeColoursCustomisation::syncThemeColours();
    if(SGXThemeColoursPage::includeVesicleInTheme == true){
        SGUCentralManagement::cuteVesiclesMembraneColour = SGUCentralManagement::themeColour4;
        SGUCentralManagement::cuteVesiclesContentsColour = SGUCentralManagement::themeColour8;
        SGXVesiclesPropertiesCustomisation::syncVesicleProperties();
    }
    (*SGXThemeColoursPage::confirmDialog).setVisible(false);
}

void SGXThemeColoursPage::activateConfirmDialog(){
    if(SGXThemeColoursPage::confirmDialog == nullptr){
        SGXThemeColoursPage::confirmDialog = SGXQuickUIInterface::createWidget(SGXQuickUIInterface::parentWidget, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 6);
        const QString s = "By pressing \"confirm\" below, you will change the theme to the one that you have selected. You will have to restart the application for the new theme to be applied. Also note that the National Day theme change takes priority over custom themes, so your theme is locked at For Our Nation during the National Day period.";
        SGXQuickUIInterface::createLongText(SGXThemeColoursPage::confirmDialog, s, 0.5f, -5.0f, 0.5f, -5.0f, 0.0f, 10.0f, 0.0f, 9.0f, 0.0f, 1.0f, 0.0f, 0.5f);
        SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::confirmDialog, "cancel", &SGXThemeColoursPage::cancelThemeColourSettings, 0.5f, -5.0f, 0.5f, 4.0f, 0.0f, 5.0f, 0.0f, 1.0f);
        SGXQuickUIInterface::createTextButton(SGXThemeColoursPage::confirmDialog, "confirm", &SGXThemeColoursPage::confirmThemeColourSettings, 0.5f, 0.0f, 0.5f, 4.0f, 0.0f, 5.0f, 0.0f, 1.0f);
    }
    (*SGXThemeColoursPage::confirmDialog).setVisible(true);
}
