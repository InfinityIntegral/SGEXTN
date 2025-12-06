#ifndef SGEXTN_ENTRYPOINT_H
#define SGEXTN_ENTRYPOINT_H

#ifdef SG_USING_CORE
#include <SGXCentral.h>

#ifdef SG_USING_FILESYSTEM
#include <SGXFileSystem.h>
#endif

#ifdef SG_USING_WIDGETS
#include <private_api_Widgets/SGWWidgetInitialisation.h>
#endif

#ifdef SG_USING_RI
#include <SGWCustomisationPageControl.h>
#include <private_api_RI/SGWThemeCustomisationPage.h>
#endif

int SGEXTN(int argc, char **argv, void (*initialiseFunction)()){
    SGXCentral::createApplication(argc, argv, initialiseFunction);
    
#ifdef SG_USING_FILESYSTEM
    SGXCentral::sgFileSystemInitFolders = &SGXFileSystem::initialiseAppFolder;
#endif
    
#ifdef SG_USING_WIDGETS
    SGXCentral::sgWidgetsInit0 = &SGWWidgetInitialisation::init0;
    SGXCentral::sgWidgetsInit1 = &SGWWidgetInitialisation::init1;
    SGXCentral::sgWidgetsInit2 = &SGWWidgetInitialisation::init2;
    SGXCentral::sgWidgetsInit3 = &SGWWidgetInitialisation::init3;
    SGXCentral::sgWidgetsInit4 = &SGWWidgetInitialisation::init4;
    SGXCentral::sgWidgetsInit5 = &SGWWidgetInitialisation::init5;
#endif
    
#ifdef SG_USING_RI
    SGWCustomisationPageControl::themeColoursCustomisationPageActivationFunction = &SGWThemeCustomisationPage::activate;
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
