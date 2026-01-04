#include <private_api_Widgets/SGWWidgetInitialisation.h>
#include <QQuickStyle>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <QQmlApplicationEngine>
#include <private_api_Widgets/SGXThemeColourSetting.h>
#include <private_api_Widgets/SGXQuickResizer.h>
#include <private_api_Widgets/SGXSingCorrectQuickInterface.h>
#include <private_api_Widgets/SGXFontSizeCustomisation.h>
#include <SGWDefaultFonts.h>
#include <QFontDatabase>
#include <QQuickWindow>
#include <QQuickItem>
#include <SGXSingCorrectCore.h>
#include <private_api_Widgets/SGXSingCorrectCustomisation.h>
#include <SGXThemeColoursCustomisation.h>
#include <private_api_Widgets/SGWStatusBar.h>
#include <SGXCentral.h>
#include <qqml.h>
#include <QChar>
#include <qlogging.h>
#include <QObject>
#include <QCoreApplication>
#include <QEventLoop>
#include <SGXDebug.h>

void SGWWidgetInitialisation::init0(){
    QQuickStyle::setStyle("Basic");
    SGXQuickInterface::e = new QQmlApplicationEngine();
}

void SGWWidgetInitialisation::init1(){
    SGXThemeColoursCustomisation::loadThemeColours();
}

void SGWWidgetInitialisation::init2(){
    SGXQuickInterface::themeColoursSingleton = new SGXThemeColourSetting();
    qmlRegisterSingletonInstance("ThemeColours", 0, 0, "ThemeColours", SGXQuickInterface::themeColoursSingleton);
    SGXQuickInterface::resizerSingleton = new SGXQuickResizer();
    qmlRegisterSingletonInstance("Resizer", 0, 0, "Resizer", SGXQuickInterface::resizerSingleton);
    SGXSingCorrectCore::instance = new SGXSingCorrectQuickInterface();
    qmlRegisterSingletonInstance("SingCorrect", 0, 0, "SingCorrect", SGXSingCorrectCore::instance);
    SGXFontSizeCustomisation::loadFontSize();
    (*SGXQuickInterface::e).load(":/SGEXTN/Root.qml");
}

void SGWWidgetInitialisation::init3(){
    SGWDefaultFonts::addFont(":/SGEXTN/SingScript.sg");
    QFontDatabase::addApplicationFallbackFontFamily(QChar::Script_Common, (*SGWDefaultFonts::textFont.data));
    QFontDatabase::addApplicationFallbackFontFamily(QChar::Script_Latin, (*SGWDefaultFonts::textFont.data));
    if(SGXCentral::importCustomFonts != nullptr){SGXCentral::importCustomFonts();}
    if(QFontDatabase::families().contains(*SGWDefaultFonts::textFont.data) == false){qWarning() << "SingScript.sg font is not found, the application will not display text and symbols used in Mathematics, Science, and Informatics correctly, to fix this, do not clear the QFontDatabase";}
    if(QFontDatabase::families().contains(*SGWDefaultFonts::iconsFont.data) == false){SG("AppIcons.sg font is not found, application icons will not be displayed correctly, to fix this, use the static function SGWDefaultFont::addFont to add the correct font from its file path when importing extra fonts. You may ignore this warning if you are not using SGWidget icons or icon buttons");}
}

void SGWWidgetInitialisation::init4(){
    SGXQuickInterface::applicationWindow = static_cast<QQuickWindow*>((*SGXQuickInterface::e).rootObjects().first());
    SGXQuickInterface::rootWindow = (*SGXQuickInterface::applicationWindow).contentItem();
    QObject::connect(SGXQuickInterface::rootWindow, &QQuickItem::widthChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
    QObject::connect(SGXQuickInterface::rootWindow, &QQuickItem::heightChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
    SGXQuickInterface::createTemplates();
    SGXQuickInterface::buildBase();
    (*SGXQuickInterface::resizerSingleton).updateAppWindowSize();
}

void SGWWidgetInitialisation::init5(){
    SGXSingCorrectCore::initialise();
    SGXSingCorrectCustomisation::loadFileData();
}
