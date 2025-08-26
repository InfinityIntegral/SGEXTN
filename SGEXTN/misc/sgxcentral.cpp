#include "sgxcentral.h"
#include "../userDefinedClasses/sgucentralmanagement.h"
#include <QCoreApplication>
#include <QList>
#include "../quickui/sgxthemecoloursetting.h"
#include "../quickui/sgxquickresizer.h"
#include <QQuickWindow>
#include <QIcon>
#include <QObject>
#include <qqml.h>
#include <QGuiApplication>
#include <QFontDatabase>
#include "../cutevesicles/sgxrendercutevesiclesquickuielement.h"
#include "../filesystem/sgxfilesystem.h"
#include <QStandardPaths>
#include "../filesystem/sgxfilebinutilities.h"
#include "../customisation/sgxthemecolourscustomisation.h"
#include "../customisation/sgxvesiclespropertiescustomisation.h"
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicequickuielement.h"
#include "../colourpickerrendering/saturationchoice/sgxrendercolourpickersaturationchoicequickuielement.h"
#include "../colourpickerrendering/lightnesschoice/sgxrendercolourpickerlightnesschoicequickuielement.h"
#include "../colourpickerrendering/transparencychoice/sgxrendercolourpickertransparencychoicequickuielement.h"
#include "../colourbackground/sgxrendercolourbackgroundquickuielement.h"
#include "../SingCorrect/sgxsingcorrectcore.h"
#include "../SingCorrect/sgxsingcorrectquickinterface.h"
#include "../SingCorrect/sgxsingcorrectcustomisation.h"
#include "../quickui/sgxquickinterface.h"
#include "../widgets/unique/sgwstatusbar.h"

void SGXCentral::initialise(){
    SGXFileSystem::rootFilePath = SGXFileSystem::joinFilePaths(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), SGUCentralManagement::rootFolderName);
    SGXFileSystem::userDataFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "yourdata");
    SGXFileSystem::configFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "settings");
    SGXFileBinUtilities::binFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "recyclebin");
    if(SGXFileSystem::folderExists(SGXFileSystem::userDataFilePath) != 1){SGXFileSystem::createFolder(SGXFileSystem::userDataFilePath);}
    if(SGXFileSystem::folderExists(SGXFileSystem::configFilePath) != 1){SGXFileSystem::createFolder(SGXFileSystem::configFilePath);}
    SGXFileBinUtilities::loadBinData();

    SGUCentralManagement::earlyInitialise();

    QCoreApplication::setApplicationName(SGUCentralManagement::applicationName);
    QCoreApplication::setApplicationVersion(SGUCentralManagement::applicationVersion);
    QCoreApplication::setOrganizationName(SGUCentralManagement::organisationName);
    const QIcon temp_appicon(":/SGEXTN/assets/appicon.png");
    QGuiApplication::setWindowIcon(temp_appicon);

    SGXThemeColoursCustomisation::loadThemeColours();
    SGXVesiclesPropertiesCustomisation::loadVesicleProperties();

    SGXQuickInterface::themeColoursSingleton = new SGXThemeColourSetting();
    qmlRegisterSingletonInstance("ThemeColours", 0, 0, "ThemeColours", SGXQuickInterface::themeColoursSingleton);
    SGXQuickInterface::resizerSingleton = new SGXQuickResizer();
    qmlRegisterSingletonInstance("Resizer", 0, 0, "Resizer", SGXQuickInterface::resizerSingleton);
    SGXSingCorrectCore::instance = new SGXSingCorrectQuickInterface();
    qmlRegisterSingletonInstance("SingCorrect", 0, 0, "SingCorrect", SGXSingCorrectCore::instance);

    qmlRegisterType<SGXRenderCuteVesiclesQuickUIElement>("CuteVesicles", 0, 0, "CuteVesicles");
    qmlRegisterType<SGXRenderColourPickerHueChoiceQuickUIElement>("ColourPickerHueChoice", 0, 0, "ColourPickerHueChoice");
    qmlRegisterType<SGXRenderColourPickerSaturationChoiceQuickUIElement>("ColourPickerSaturationChoice", 0, 0, "ColourPickerSaturationChoice");
    qmlRegisterType<SGXRenderColourPickerLightnessChoiceQuickUIElement>("ColourPickerLightnessChoice", 0, 0, "ColourPickerLightnessChoice");
    qmlRegisterType<SGXRenderColourPickerTransparencyChoiceQuickUIElement>("ColourPickerTransparencyChoice", 0, 0, "ColourPickerTransparencyChoice");
    qmlRegisterType<SGXRenderColourBackgroundQuickUIElement>("ColourBackground", 0, 0, "ColourBackground");

    SGUCentralManagement::initialiseCustomRendering();
    (*SGXQuickInterface::e).load(":/SGEXTN/QML/root.qml");

    connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    QFontDatabase::addApplicationFont(":/SGEXTN/assets/SingScript.sg");
    QFontDatabase::addApplicationFont(":/SGEXTN/assets/AppIcons.sg");
    SGUCentralManagement::initialiseExtraFonts();

    SGXQuickInterface::applicationWindow = qobject_cast<QQuickWindow*>((*SGXQuickInterface::e).rootObjects().first());
    SGXQuickInterface::rootWindow = (*SGXQuickInterface::applicationWindow).contentItem();
    connect(SGXQuickInterface::rootWindow, &QQuickItem::widthChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
    connect(SGXQuickInterface::rootWindow, &QQuickItem::heightChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
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
    (*SGXQuickInterface::applicationWindow).close();
    (*SGXQuickInterface::applicationWindow).deleteLater();
}
