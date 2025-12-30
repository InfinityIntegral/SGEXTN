#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

#include <SGXString.h>

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXCentral
{
public:
    SGXCentral() = delete;
    static void initialise();
    static void terminate();
    static SGXString applicationName;
    static SGXString applicationVersion;
    static SGXString organisationName;
    static SGXString folderName;
    static SGXString pathToAppIcon;
    static SGXString infoWebsite;
    static void (*interpretCmdArgs)(int, char**);
    static void (*customInitialise)();
    static void (*customTerminate)();
    static void (*setCustomTheme)();
    static void (*importCustomFonts)();
    static void createApplication(int argc, char** argv, void (*initialiseFunction)());
    static int actualArgc;
    static char** actualArgv;
    static int startEventLoop();
    static void (*sgFileSystemInitFolders)();
    static void (*sgWidgetsInit0)();
    static void (*sgWidgetsInit1)();
    static void (*sgWidgetsInit2)();
    static void (*sgWidgetsInit3)();
    static void (*sgWidgetsInit4)();
    static void (*sgWidgetsInit5)();
};

#endif // SGXCENTRAL_H
