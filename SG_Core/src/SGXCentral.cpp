#include <QLocale>
#include <QCoreApplication>
#include <QObject>
#include <SGXCentral.h>
#include <SGXString.h>
#include <QGuiApplication>
#include <QIcon>
#include <SGXTimer.h>
#include <cstring>
#include <SGXDebug.h>

SGXString SGXCentral::applicationName = "app name not set";
SGXString SGXCentral::applicationVersion = "app version not set";
SGXString SGXCentral::organisationName = "organisation name not set";
SGXString SGXCentral::folderName = "SGEXTN_app";
SGXString SGXCentral::pathToAppIcon = ":/SGEXTN/SGEXTN_icon.png";
SGXString SGXCentral::infoWebsite = "";
void (*SGXCentral::interpretCmdArgs)(int, char**) = nullptr;
void (*SGXCentral::customInitialise)() = nullptr;
void (*SGXCentral::customTerminate)() = nullptr;
void (*SGXCentral::setCustomTheme)() = nullptr;
void (*SGXCentral::importCustomFonts)() = nullptr;

int SGXCentral::actualArgc = 0;
char** SGXCentral::actualArgv = nullptr;

void (*SGXCentral::sgFileSystemInitFolders)() = nullptr;
void (*SGXCentral::sgWidgetsInit0)() = nullptr;
void (*SGXCentral::sgWidgetsInit1)() = nullptr;
void (*SGXCentral::sgWidgetsInit2)() = nullptr;
void (*SGXCentral::sgWidgetsInit3)() = nullptr;
void (*SGXCentral::sgWidgetsInit4)() = nullptr;
void (*SGXCentral::sgWidgetsInit5)() = nullptr;

void SGXCentral::initialise(){
    SGLCrash::logCrashMessage = &SGXDebug::logCrashMessage;

    bool isTest = false;
    for(int i=0; i<SGXCentral::actualArgc; i++){
        const SGXString arg(const_cast<const char*>(SGXCentral::actualArgv[i])); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if(arg == "--SG-test"){isTest = true;}
        else if(arg.substringLeft(14) == "--SG-log-file="){SGXDebug::logFile = arg.substringRight(arg.length() - 14);}
    }

    QLocale::setDefault(QLocale(QLocale::English, QLocale::Singapore));
    if(SGXCentral::sgWidgetsInit0 != nullptr){SGXCentral::sgWidgetsInit0();}
    
    QCoreApplication::setApplicationName(*SGXCentral::applicationName.data);
    QCoreApplication::setApplicationVersion(*SGXCentral::applicationVersion.data);
    QCoreApplication::setOrganizationName(*SGXCentral::organisationName.data);
    QGuiApplication::setWindowIcon(QIcon(*SGXCentral::pathToAppIcon.data));
    
    if(SGXCentral::sgFileSystemInitFolders != nullptr){SGXCentral::sgFileSystemInitFolders();}
    if(SGXCentral::setCustomTheme != nullptr){SGXCentral::setCustomTheme();}
    if(SGXCentral::sgWidgetsInit1 != nullptr){SGXCentral::sgWidgetsInit1();}
    if(SGXCentral::sgWidgetsInit2 != nullptr){SGXCentral::sgWidgetsInit2();}
    QObject::connect(qApp, &QGuiApplication::aboutToQuit, &SGXCentral::terminate); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    if(SGXCentral::sgWidgetsInit3 != nullptr){SGXCentral::sgWidgetsInit3();}
    if(SGXCentral::sgWidgetsInit4 != nullptr){SGXCentral::sgWidgetsInit4();}
    if(SGXCentral::sgWidgetsInit5 != nullptr){SGXCentral::sgWidgetsInit5();}
    if(SGXCentral::customInitialise != nullptr){SGXCentral::customInitialise();}
    if(isTest == true){SGXTimer::singleCall(0.0f, &QCoreApplication::quit);}
}

void SGXCentral::terminate(){
    if(SGXCentral::customTerminate != nullptr){SGXCentral::customTerminate();}
}

void SGXCentral::createApplication(int argc, char **argv, void (*initialiseFunction)()){
    SGXCentral::actualArgc = argc;
    SGXCentral::actualArgv = argv;
    new QGuiApplication(actualArgc, actualArgv); // NOLINT(misc-const-correctness)
    initialiseFunction(); // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)
    if(SGXCentral::interpretCmdArgs != nullptr){SGXCentral::interpretCmdArgs(actualArgc, actualArgv);}
}

int SGXCentral::startEventLoop(){
    return QGuiApplication::exec();
}
