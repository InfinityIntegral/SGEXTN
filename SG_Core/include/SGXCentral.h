#ifndef SGXCENTRAL_H
#define SGXCENTRAL_H

#include <SGXString.h>

class SGXCentral
{
public:
    SGXCentral() = delete;
    static void initialise();
    static void terminate();
    static SGXString applicationName;
    static SGXString applicationVersion;
    static SGXString organisationName;
    static void (*interpretCmdArgs)(int, char**);
    static void (*customInitialise)();
    static void (*customTerminate)();
};

int SGEXTN(int argc, char** argv, void (*initialiseFunction)());

#endif // SGXCENTRAL_H
