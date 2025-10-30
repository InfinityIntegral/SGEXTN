#include <QLocale>
#include <QCoreApplication>
#include <QObject>
#include <SGXIdentifier.h>
#include <SGXCentral.h>
#include <SGXString.h>
#include <QGuiApplication>
#include <QIcon>

SGXString SGXCentral::applicationName = "app name not set";
SGXString SGXCentral::applicationVersion = "app version not set";
SGXString SGXCentral::organisationName = "organisation name not set";
SGXString SGXCentral::folderName = "folder name not set";
SGXString SGXCentral::pathToAppIcon = "";
void (*SGXCentral::interpretCmdArgs)(int, char**) = nullptr;
void (*SGXCentral::customInitialise)() = nullptr;
void (*SGXCentral::customTerminate)() = nullptr;
void (*SGXCentral::setCustomTheme)() = nullptr;
void (*SGXCentral::importCustomFonts)() = nullptr;

void (*SGXCentral::sgFileSystemInitFolders)() = nullptr;
void (*SGXCentral::sgWidgetsInit0)() = nullptr;
void (*SGXCentral::sgWidgetsInit1)() = nullptr;
void (*SGXCentral::sgWidgetsInit2)() = nullptr;
void (*SGXCentral::sgWidgetsInit3)() = nullptr;
void (*SGXCentral::sgWidgetsInit4)() = nullptr;
void (*SGXCentral::sgWidgetsInit5)() = nullptr;
void (*SGXCentral::sgWidgetsTerminate)() = nullptr;

void SGXCentral::initialise(){
    QLocale::setDefault(QLocale(QLocale::English, QLocale::Singapore));
    if(SGXCentral::sgWidgetsInit0 != nullptr){SGXCentral::sgWidgetsInit0();}
    
    QCoreApplication::setApplicationName(*SGXCentral::applicationName.data);
    QCoreApplication::setApplicationVersion(*SGXCentral::applicationVersion.data);
    QCoreApplication::setOrganizationName(*SGXCentral::organisationName.data);
    if(SGXCentral::pathToAppIcon != ""){QGuiApplication::setWindowIcon(QIcon(*SGXCentral::pathToAppIcon.data));}
    
    if(SGXCentral::sgFileSystemInitFolders != nullptr){SGXCentral::sgFileSystemInitFolders();}
    if(SGXCentral::setCustomTheme != nullptr){SGXCentral::setCustomTheme();}
    if(SGXCentral::sgWidgetsInit1 != nullptr){SGXCentral::sgWidgetsInit1();}
    if(SGXCentral::sgWidgetsInit2 != nullptr){SGXCentral::sgWidgetsInit2();}
    QObject::connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    if(SGXCentral::sgWidgetsInit3 != nullptr){SGXCentral::sgWidgetsInit3();}
    if(SGXCentral::sgWidgetsInit4 != nullptr){SGXCentral::sgWidgetsInit4();}
    if(SGXCentral::sgWidgetsInit5 != nullptr){SGXCentral::sgWidgetsInit5();}
    if(SGXCentral::customInitialise != nullptr){SGXCentral::customInitialise();}
}

void SGXCentral::terminate(){
    if(SGXCentral::customTerminate != nullptr){SGXCentral::customTerminate();}
    if(SGXCentral::sgWidgetsTerminate != nullptr){SGXCentral::sgWidgetsTerminate();}
    SGXIdentifier::terminate();
}

void SGXCentral::createApplication(int argc, char **argv, void (*initialiseFunction)()){
    new QGuiApplication(argc, argv); // NOLINT(misc-const-correctness)
    initialiseFunction(); // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
    if(SGXCentral::interpretCmdArgs != nullptr){SGXCentral::interpretCmdArgs(argc, argv);}
}

int SGXCentral::startEventLoop(){
    return QGuiApplication::exec();
}
