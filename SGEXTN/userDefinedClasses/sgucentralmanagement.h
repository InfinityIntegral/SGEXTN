#ifndef SGUCENTRALMANAGEMENT_H
#define SGUCENTRALMANAGEMENT_H

#include "../primitives/sgxcolourrgba.h"
#include "../primitives/sgxstring.h"

class SGUCentralManagement
{
public:
    SGUCentralManagement() = delete;
    static void initialise();
    static void terminate();
    static void earlyInitialise();
    static void initialiseExtraFonts();
    static void initialiseCustomRendering();
    static SGXString applicationName;
    static SGXString applicationVersion;
    static SGXString organisationName;
    static SGXString rootFolderName;
};

#endif // SGUCENTRALMANAGEMENT_H
