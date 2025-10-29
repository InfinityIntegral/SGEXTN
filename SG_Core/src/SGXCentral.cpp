#include <QLocale>
#include <QCoreApplication>
#include <QObject>
#include <SGXIdentifier.h>
#include <SGXCentral.h>
#include <SGXString.h>
#include <QGuiApplication>

SGXString SGXCentral::applicationName = "app name not set";
SGXString SGXCentral::applicationVersion = "app version not set";
SGXString SGXCentral::organisationName = "organisation name not set";
void (*SGXCentral::interpretCmdArgs)(int, char**) = nullptr;
void (*SGXCentral::customInitialise)() = nullptr;
void (*SGXCentral::customTerminate)() = nullptr;

void SGXCentral::initialise(){
    QLocale::setDefault(QLocale(QLocale::English, QLocale::Singapore));
    /* widgets
    QQuickStyle::setStyle("Basic");
    SGXQuickInterface::e = new QQmlApplicationEngine();
    */
    
    QCoreApplication::setApplicationName(*SGXCentral::applicationName.data);
    QCoreApplication::setApplicationVersion(*SGXCentral::applicationVersion.data);
    QCoreApplication::setOrganizationName(*SGXCentral::organisationName.data);
    /* widgets
    QGuiApplication::setWindowIcon(QIcon(":/SGEXTN/assets/appicon.png"));
    */
    
    /* file system
    const SGXString standardPath = "";
    (*standardPath.data) = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    SGXFileSystem::rootFilePath = SGXFileSystem::joinFilePaths(standardPath, SGUCentralManagement::rootFolderName);
    SGXFileSystem::userDataFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "yourdata");
    SGXFileSystem::configFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "settings");
    SGXFileBinUtilities::binFilePath = SGXFileSystem::joinFilePaths(SGXFileSystem::rootFilePath, "recyclebin");
    if(SGXFileSystem::folderExists(SGXFileSystem::userDataFilePath) == false){SGXFileSystem::createFolder(SGXFileSystem::userDataFilePath);}
    if(SGXFileSystem::folderExists(SGXFileSystem::configFilePath) == false){SGXFileSystem::createFolder(SGXFileSystem::configFilePath);}
    SGXFileBinUtilities::loadBinData();
    */
    
    /* widgets
    SGUCentralManagement::setDefaultTheme();
    SGXThemeColoursCustomisation::loadThemeColours();
    */

    /* widgets
    SGXQuickInterface::themeColoursSingleton = new SGXThemeColourSetting();
    qmlRegisterSingletonInstance("ThemeColours", 0, 0, "ThemeColours", SGXQuickInterface::themeColoursSingleton);
    SGXQuickInterface::resizerSingleton = new SGXQuickResizer();
    qmlRegisterSingletonInstance("Resizer", 0, 0, "Resizer", SGXQuickInterface::resizerSingleton);
    SGXSingCorrectCore::instance = new SGXSingCorrectQuickInterface();
    qmlRegisterSingletonInstance("SingCorrect", 0, 0, "SingCorrect", SGXSingCorrectCore::instance);
    SGXFontSizeCustomisation::loadFontSize();
    (*SGXQuickInterface::e).load(":/SGEXTN/QML/root.qml");
    */

    QObject::connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    /* widgets
    SGWDefaultFonts::addFont(":/SGEXTN/assets/SingScript.sg");
    QFontDatabase::addApplicationFallbackFontFamily(QChar::Script_Common, (*SGWDefaultFonts::textFont.data));
    QFontDatabase::addApplicationFallbackFontFamily(QChar::Script_Latin, (*SGWDefaultFonts::textFont.data));
    SGUCentralManagement::importExtraFonts();
    if(QFontDatabase::families().contains(*SGWDefaultFonts::textFont.data) == false){qWarning() << "SingScript.sg font is not found, the application will not display text and symbols used in Mathematics, Science, and Informatics correctly, to fix this, do not clear the QFontDatabase";}
    if(QFontDatabase::families().contains(*SGWDefaultFonts::iconsFont.data) == false){qWarning() << "AppIcons.sg font is not found, application icons will not be displayed correctly, to fix this, use the static function SGWDefaultFont::addFont to add the correct font from its file path when importing extra fonts. You may ignore this warning if you are not using SGWidget icons or icon buttons";}
    */

    /* widgets
    SGXQuickInterface::applicationWindow = static_cast<QQuickWindow*>((*SGXQuickInterface::e).rootObjects().first());
    SGXQuickInterface::rootWindow = (*SGXQuickInterface::applicationWindow).contentItem();
    QObject::connect(SGXQuickInterface::rootWindow, &QQuickItem::widthChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
    QObject::connect(SGXQuickInterface::rootWindow, &QQuickItem::heightChanged, SGXQuickInterface::resizerSingleton, &SGXQuickResizer::updateAppWindowSize);
    SGXQuickInterface::createTemplates();
    SGXQuickInterface::buildBase();
    (*SGXQuickInterface::resizerSingleton).updateAppWindowSize();
    */

    /* widgets
    SGXSingCorrectCore::initialise();
    SGXSingCorrectCustomisation::loadFileData();
    */

    if(SGXCentral::customInitialise != nullptr){SGXCentral::customInitialise();}
}

void SGXCentral::terminate(){
    if(SGXCentral::customTerminate != nullptr){SGXCentral::customTerminate();}
    /* widgets
    SGXSingCorrectCore::terminate();
    SGXQuickInterface::deleteTemplates();
    SGXQuickInterface::deleteSingletons();
    SGWStatusBar::terminate();
    SGWBackground::terminate();
    (*SGXQuickInterface::applicationWindow).close();
    (*SGXQuickInterface::applicationWindow).deleteLater();
    (*SGXQuickInterface::e).deleteLater();
    */
    SGXIdentifier::terminate();
}

int SGEXTN(int argc, char **argv, void (*initialiseFunction)()){
    QGuiApplication app(argc, argv); // NOLINT(misc-const-correctness)
    if(SGXCentral::interpretCmdArgs != nullptr){SGXCentral::interpretCmdArgs(argc, argv);}
    initialiseFunction();
    SGXCentral::initialise();
    return QGuiApplication::exec();
}
