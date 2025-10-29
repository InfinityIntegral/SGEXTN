#ifndef SGEXTN_ENTRYPOINT_H
#define SGEXTN_ENTRYPOINT_H

#ifdef SG_USING_CORE
#include <SGXCentral.h>

#ifdef SG_USING_FILESYSTEM
#include <SGXFileSystem.h>
#endif

int SGEXTN(int argc, char **argv, void (*initialiseFunction)()){
    SGXCentral::createApplication(argc, argv, initialiseFunction);
    
#ifdef SG_USING_FILESYSTEM
    SGXCentral::sgFileSystemInitFolders = &SGXFileSystem::initialiseAppFolder;
#endif
    
    SGXCentral::initialise();
    
#ifndef SG_SINGLE_FRAME
    return SGXCentral::startEventLoop();
#else
    return 0;
#endif
}
#else
#error "SGEXTN entry point can only be used if you use the SGEXTN Core module, otherwise write your own int main() because nothing need to be initialised, you can still use SGEXTN Containers and Math modules"
#endif

#endif // SGEXTN_ENTRYPOINT_H
