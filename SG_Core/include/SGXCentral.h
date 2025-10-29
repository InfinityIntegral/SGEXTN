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
    static void (*interpretCmdArgs)(int, char**);
    static void (*customInitialise)();
    static void (*customTerminate)();
    static void createApplication(int argc, char** argv, void (*initialiseFunction)());
    static int startEventLoop();
    static void (*sgFileSystemInitFolders)();
};

#endif // SGXCENTRAL_H
