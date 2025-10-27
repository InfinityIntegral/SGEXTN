#include "sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QCoreApplication>
#include "../quickui/sgxthemecoloursetting.h"
#include "../quickui/sgxquickresizer.h"
#include <QQuickWindow>
#include <QIcon>
#include <QObject>
#include <qqml.h>
#include <QGuiApplication>
#include <QFontDatabase>
#include "../filesystem/sgxfilesystem.h"
#include <QStandardPaths>
#include "../filesystem/sgxfilebinutilities.h"
#include "../customisation/sgxthemecolourscustomisation.h"
#include "../SingCorrect/sgxsingcorrectcore.h"
#include "../quickui/sgxsingcorrectquickinterface.h"
#include "../SingCorrect/sgxsingcorrectcustomisation.h"
#include "../quickui/sgxquickinterface.h"
#include "../widgets/unique/sgwstatusbar.h"
#include <QQmlApplicationEngine>
#include "../widgets/noninstantiable/sgwbackground.h"
#include "../primitives/sgxidentifier.h"
#include "../customisation/sgxfontsizecustomisation.h"
#include <QQuickItem>
#include "../widgets/enums/sgwdefaultfonts.h"
#include <qlogging.h>
#include <QQuickStyle>
#include <QLocale>

void SGXCentral::initialise(){
    QLocale::setDefault(QLocale(QLocale::English, QLocale::Singapore));
    QQuickStyle::setStyle("Basic");
    SGXQuickInterface::e = new QQmlApplicationEngine();
    
    QCoreApplication::setApplicationName(*SGUCentralManagement::applicationName.data);
    QCoreApplication::setApplicationVersion(*SGUCentralManagement::applicationVersion.data);
    QCoreApplication::setOrganizationName(*SGUCentralManagement::organisationName.data);
    QGuiApplication::setWindowIcon(QIcon(":/SGEXTN/assets/appicon.png"));
    
    const SGXString standardPath = "";
    (*standardPath.data) = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    SGXFileSystem::rootFilePath = SGXFileSystem::joinFilePaths(standardPath, SGUCentralManagement::rootFolderName);
    SGXFileSystem::userDataFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "yourdata");
    SGXFileSystem::configFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "settings");
    SGXFileBinUtilities::binFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "recyclebin");
    if(SGXFileSystem::folderExists(SGXFileSystem::userDataFilePath) == false){SGXFileSystem::createFolder(SGXFileSystem::userDataFilePath);}
    if(SGXFileSystem::folderExists(SGXFileSystem::configFilePath) == false){SGXFileSystem::createFolder(SGXFileSystem::configFilePath);}
    SGXFileBinUtilities::loadBinData();
    
    SGUCentralManagement::setDefaultTheme();
    SGXThemeColoursCustomisation::loadThemeColours();

    SGXQuickInterface::themeColoursSingleton = new SGXThemeColourSetting();
    qmlRegisterSingletonInstance("ThemeColours", 0, 0, "ThemeColours", SGXQuickInterface::themeColoursSingleton);
    SGXQuickInterface::resizerSingleton = new SGXQuickResizer();
    qmlRegisterSingletonInstance("Resizer", 0, 0, "Resizer", SGXQuickInterface::resizerSingleton);
    SGXSingCorrectCore::instance = new SGXSingCorrectQuickInterface();
    qmlRegisterSingletonInstance("SingCorrect", 0, 0, "SingCorrect", SGXSingCorrectCore::instance);
    SGXFontSizeCustomisation::loadFontSize();
    (*SGXQuickInterface::e).load(":/SGEXTN/QML/root.qml");

    QObject::connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    SGWDefaultFonts::addFont(":/SGEXTN/assets/SingScript.sg");
    QFontDatabase::addApplicationFallbackFontFamily(QChar::Script_Common, (*SGWDefaultFonts::textFont.data));
    QFontDatabase::addApplicationFallbackFontFamily(QChar::Script_Latin, (*SGWDefaultFonts::textFont.data));
    SGUCentralManagement::importExtraFonts();
    if(QFontDatabase::families().contains(*SGWDefaultFonts::textFont.data) == false){qWarning() << "SingScript.sg font is not found, the application will not display text and symbols used in Mathematics, Science, and Informatics correctly, to fix this, do not clear the QFontDatabase";}
    if(QFontDatabase::families().contains(*SGWDefaultFonts::iconsFont.data) == false){qWarning() << "AppIcons.sg font is not found, application icons will not be displayed correctly, to fix this, use the static function SGWDefaultFont::addFont to add the correct font from its file path when importing extra fonts. You may ignore this warning if you are not using SGWidget icons or icon buttons";}

    SGXQuickInterface::applicationWindow = static_cast<QQuickWindow*>((*SGXQuickInterface::e).rootObjects().first());
    SGXQuickInterface::rootWindow = (*SGXQuickInterface::applicationWindow).contentItem();
    QObject::connect(SGXQuickInterface::rootWindow, &QQuickItem::widthChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
    QObject::connect(SGXQuickInterface::rootWindow, &QQuickItem::heightChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
    SGXQuickInterface::createTemplates();
    SGXQuickInterface::buildBase();
    (*SGXQuickInterface::resizerSingleton).updateAppWindowSize();

    SGXSingCorrectCore::initialise();
    SGXSingCorrectCustomisation::loadFileData();

    SGUCentralManagement::initialise();
}

void SGXCentral::terminate(){
    SGUCentralManagement::terminate();
    SGXSingCorrectCore::terminate();
    SGXQuickInterface::deleteTemplates();
    SGXQuickInterface::deleteSingletons();
    SGWStatusBar::terminate();
    SGWBackground::terminate();
    SGXIdentifier::terminate();
    (*SGXQuickInterface::applicationWindow).close();
    (*SGXQuickInterface::applicationWindow).deleteLater();
    (*SGXQuickInterface::e).deleteLater();
}

int SGEXTN(int argc, char **argv){
    QGuiApplication app(argc, argv); // NOLINT(misc-const-correctness)
    SGUCentralManagement::interpretCmdArgs(argc, argv);
    SGXCentral::initialise();
    return QGuiApplication::exec();
}
