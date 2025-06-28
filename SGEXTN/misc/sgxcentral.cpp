#include "sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QCoreApplication>
#include <QList>
#include "../quickui/sgxthemecoloursetting.h"
#include "../quickui/sgxquickuiinterface.h"
#include "../quickui/sgxquickresizer.h"
#include <QQuickWindow>
#include <QIcon>
#include <QObject>
#include <qqml.h>
#include <QGuiApplication>
#include <QFontDatabase>
#include "../cutevesicles/sgxrendercutevesiclesquickuielement.h"

void SGXCentral::initialise(){
    SGUCentralManagement::earlyInitialise();
    
    QCoreApplication::setApplicationName(SGUCentralManagement::applicationName);
    QCoreApplication::setApplicationVersion(SGUCentralManagement::applicationVersion);
    QCoreApplication::setOrganizationName(SGUCentralManagement::organisationName);
    const QIcon temp_appicon(":/SGEXTN/assets/appicon.png");
    QGuiApplication::setWindowIcon(temp_appicon);
    
    SGXQuickUIInterface::themeColoursInstance = new SGXThemeColourSetting();
    qmlRegisterSingletonInstance("ThemeColours", 0, 0, "ThemeColours", SGXQuickUIInterface::themeColoursInstance);
    SGXQuickUIInterface::resizerInstance = new SGXQuickResizer();
    qmlRegisterSingletonInstance("Resizer", 0, 0, "Resizer", SGXQuickUIInterface::resizerInstance);
    qmlRegisterType<SGXRenderCuteVesiclesQuickUIElement>("CuteVesicles", 0, 0, "CuteVesicles");
    (*SGXQuickUIInterface::e).load(":/SGEXTN/QML/root.qml");
    SGXRenderCuteVesiclesQuickUIElement::framesPerSecond = SGUCentralManagement::cuteVesiclesFrameRate;
    
    connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    QFontDatabase::addApplicationFont(":/SGEXTN/assets/standard.otf");
    QFontDatabase::addApplicationFont(":/SGEXTN/assets/icons.otf");
    
    SGXQuickUIInterface::applicationWindow = qobject_cast<QQuickWindow*>((*SGXQuickUIInterface::e).rootObjects().first());
    SGXQuickUIInterface::rootWindow = (*SGXQuickUIInterface::applicationWindow).contentItem();
    connect(SGXQuickUIInterface::rootWindow, &QQuickItem::widthChanged, SGXQuickUIInterface::resizerInstance, &SGXQuickResizer::updateAppWindowSize);
    connect(SGXQuickUIInterface::rootWindow, &QQuickItem::heightChanged, SGXQuickUIInterface::resizerInstance, &SGXQuickResizer::updateAppWindowSize);
    SGXQuickUIInterface::initialise();
    SGXQuickUIInterface::buildTemplate();
    (*SGXQuickUIInterface::resizerInstance).updateAppWindowSize();
    SGUCentralManagement::initialise();
}

void SGXCentral::terminate(){
    SGUCentralManagement::terminate();
    delete SGXQuickUIInterface::resizerInstance;
    delete SGXQuickUIInterface::themeColoursInstance;
    delete SGXQuickUIInterface::touchEventFunctionsList;
    delete SGXQuickUIInterface::rootWidgetTemplate;
    delete SGXQuickUIInterface::parentWidgetTemplate;
    delete SGXQuickUIInterface::widgetTemplate;
    delete SGXQuickUIInterface::textTemplate;
    delete SGXQuickUIInterface::longTextTemplate;
    delete SGXQuickUIInterface::iconTemplate;
    delete SGXQuickUIInterface::textButtonTemplate;
    delete SGXQuickUIInterface::iconButtonTemplate;
    delete SGXQuickUIInterface::inputFieldTemplate;
    delete SGXQuickUIInterface::longInputFieldTemplate;
    delete SGXQuickUIInterface::scrollViewTemplate;
    delete SGXQuickUIInterface::touchReceiverTemplate;
    delete SGXQuickUIInterface::cuteVesiclesTemplate;
}
