#include "sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QCoreApplication>
#include <QtCore/Qt>
#include <QList>
#include "../quickui/sgxthemecoloursetting.h"
#include <QQmlEngine>
#include "../quickui/sgxquickuiinterface.h"
#include "../quickui/sgxquickresizer.h"
#include <QQuickWindow>
#include <QIcon>
#include <QObject>
#include <qqml.h>
#include <QGuiApplication>

//QFont* SGXCentral::standardFont = nullptr;
//QFont* SGXCentral::iconsFont = nullptr;

void SGXCentral::initialise(){
    QCoreApplication::setApplicationName(SGUCentralManagement::applicationName);
    QCoreApplication::setApplicationVersion(SGUCentralManagement::applicationVersion);
    QCoreApplication::setOrganizationName("05524F.sg");
    const QIcon temp_appicon(":/assets/05524Flogo.png");
    QGuiApplication::setWindowIcon(temp_appicon);
    SGXQuickUIInterface::themeColoursInstance = new SGXThemeColourSetting();
    qmlRegisterSingletonInstance("ThemeColours", 0, 0, "ThemeColours", SGXQuickUIInterface::themeColoursInstance);
    SGXQuickUIInterface::resizerInstance = new SGXQuickResizer();
    qmlRegisterSingletonInstance("Resizer", 0, 0, "Resizer", SGXQuickUIInterface::resizerInstance);
    (*SGXQuickUIInterface::e).load(":/QML/root.qml");
    SGXQuickUIInterface::rootWindow = (*qobject_cast<QQuickWindow*>((*SGXQuickUIInterface::e).rootObjects().first())).contentItem();
    
    connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    QCoreApplication::setAttribute(Qt::AA_SynthesizeMouseForUnhandledTouchEvents);
    QCoreApplication::setAttribute(Qt::AA_SynthesizeTouchForUnhandledMouseEvents);
    /*{
        QList l = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/standard.otf"));
        SGXCentral::standardFont = new QFont(l.first()); // NOLINT(cppcoreguidelines-owning-memory)
        l = QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/assets/icons.otf"));
        SGXCentral::iconsFont = new QFont(l.first()); // NOLINT(cppcoreguidelines-owning-memory)
    }*/
    connect(SGXQuickUIInterface::rootWindow, &QQuickItem::widthChanged, SGXQuickUIInterface::resizerInstance, &SGXQuickResizer::updateAppWindowSize);
    connect(SGXQuickUIInterface::rootWindow, &QQuickItem::heightChanged, SGXQuickUIInterface::resizerInstance, &SGXQuickResizer::updateAppWindowSize);
    SGXQuickUIInterface::rootWidgetTemplate = new QQmlComponent(SGXQuickUIInterface::e, ":/QML/rootwidget.qml");
    SGXQuickUIInterface::rootWidget = SGXQuickUIInterface::createRootWidget(SGXQuickUIInterface::rootWindow);
    (*SGXQuickUIInterface::resizerInstance).updateAppWindowSize();
    SGUCentralManagement::initialise();
}

void SGXCentral::terminate(){
    SGUCentralManagement::terminate();
    delete SGXQuickUIInterface::resizerInstance;
    delete SGXQuickUIInterface::themeColoursInstance;
    //delete SGXCentral::iconsFont; // NOLINT(cppcoreguidelines-owning-memory)
    //delete SGXCentral::standardFont; // NOLINT(cppcoreguidelines-owning-memory)
}
