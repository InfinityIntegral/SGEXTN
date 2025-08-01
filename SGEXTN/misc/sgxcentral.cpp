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
#include "../filesystem/sgxfilesystem.h"
#include <QStandardPaths>
#include "../filesystem/sgxfilebinutilities.h"
#include "../customisation/sgxthemecolourscustomisation.h"
#include "../customisation/sgxvesiclespropertiescustomisation.h"
#include "../template/sgxcutevesicles.h"
#include "../colourpickerrendering/huechoice/sgxrendercolourpickerhuechoicequickuielement.h"
#include "../colourpickerrendering/saturationchoice/sgxrendercolourpickersaturationchoicequickuielement.h"
#include "../colourpickerrendering/lightnesschoice/sgxrendercolourpickerlightnesschoicequickuielement.h"
#include "../colourpickerrendering/transparencychoice/sgxrendercolourpickertransparencychoicequickuielement.h"
#include "../colourbackground/sgxrendercolourbackgroundquickuielement.h"
#include "../SingCorrect/sgxsingcorrectcore.h"
#include "../SingCorrect/sgxsingcorrectquickinterface.h"

void SGXCentral::initialise(){
    SGXFileSystem::rootFilePath = SGXFileSystem::joinFilePaths(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), SGUCentralManagement::rootFolderName);
    SGXFileSystem::userDataFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "yourdata");
    SGXFileSystem::configFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "settings");
    SGXFileSystem::binFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "recyclebin");
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
    
    SGXQuickUIInterface::themeColoursInstance = new SGXThemeColourSetting();
    qmlRegisterSingletonInstance("ThemeColours", 0, 0, "ThemeColours", SGXQuickUIInterface::themeColoursInstance);
    SGXQuickUIInterface::resizerInstance = new SGXQuickResizer();
    qmlRegisterSingletonInstance("Resizer", 0, 0, "Resizer", SGXQuickUIInterface::resizerInstance);
    SGXSingCorrectCore::instance = new SGXSingCorrectQuickInterface();
    qmlRegisterSingletonInstance("SingCorrect", 0, 0, "SingCorrect", SGXSingCorrectCore::instance);
    
    qmlRegisterType<SGXRenderCuteVesiclesQuickUIElement>("CuteVesicles", 0, 0, "CuteVesicles");
    qmlRegisterType<SGXRenderColourPickerHueChoiceQuickUIElement>("ColourPickerHueChoice", 0, 0, "ColourPickerHueChoice");
    qmlRegisterType<SGXRenderColourPickerSaturationChoiceQuickUIElement>("ColourPickerSaturationChoice", 0, 0, "ColourPickerSaturationChoice");
    qmlRegisterType<SGXRenderColourPickerLightnessChoiceQuickUIElement>("ColourPickerLightnessChoice", 0, 0, "ColourPickerLightnessChoice");
    qmlRegisterType<SGXRenderColourPickerTransparencyChoiceQuickUIElement>("ColourPickerTransparencyChoice", 0, 0, "ColourPickerTransparencyChoice");
    qmlRegisterType<SGXRenderColourBackgroundQuickUIElement>("ColourBackground", 0, 0, "ColourBackground");
    SGUCentralManagement::initialiseCustomRendering();
    (*SGXQuickUIInterface::e).load(":/SGEXTN/QML/root.qml");
    SGXCuteVesicles::framesPerSecond = SGUCentralManagement::cuteVesiclesFrameRate;
    
    connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    QFontDatabase::addApplicationFont(":/SGEXTN/assets/SingScript.sg");
    QFontDatabase::addApplicationFont(":/SGEXTN/assets/AppIcons.sg");
    SGUCentralManagement::initialiseExtraFonts();
    
    SGXQuickUIInterface::applicationWindow = qobject_cast<QQuickWindow*>((*SGXQuickUIInterface::e).rootObjects().first());
    SGXQuickUIInterface::rootWindow = (*SGXQuickUIInterface::applicationWindow).contentItem();
    connect(SGXQuickUIInterface::rootWindow, &QQuickItem::widthChanged, SGXQuickUIInterface::resizerInstance, &SGXQuickResizer::updateAppWindowSize);
    connect(SGXQuickUIInterface::rootWindow, &QQuickItem::heightChanged, SGXQuickUIInterface::resizerInstance, &SGXQuickResizer::updateAppWindowSize);
    SGXQuickUIInterface::initialise();
    SGXQuickUIInterface::buildTemplate();
    (*SGXQuickUIInterface::resizerInstance).updateAppWindowSize();
    
    SGXSingCorrectCore::initialise();
    
    SGUCentralManagement::initialise();
}

void SGXCentral::terminate(){
    SGUCentralManagement::terminate();
    SGXSingCorrectCore::terminate();
    SGXQuickUIInterface::terminate();
}
