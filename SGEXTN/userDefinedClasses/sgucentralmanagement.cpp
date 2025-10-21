#include "sgucentralmanagement.h"
#include "../primitives/sgxstring.h"

// pls update README and license
// do not forget to replace the icons font file and app icon in assets.qrc based on the app, do not change their file paths though
// the icons font file can be of any type (otf, ttf, etc) that Qt support, but its name must be AppIcons.sg and the internal font family name must be AppIcons.sg

// name of your application
SGXString SGUCentralManagement::applicationName = "SGEXTN";
// version number of your application, does not have to be number
SGXString SGUCentralManagement::applicationVersion = "v5.1.0";
// name of your organisation
SGXString SGUCentralManagement::organisationName = "05524F.sg (Singapore)";
// name of root folder of your application, only use uppercase or lowercase letters, definitely no banned characters, no dots, no spaces, no hyphens, no underscores, avoid numbers, avoid non ASCII characters
SGXString SGUCentralManagement::rootFolderName = "SGEXTN";
// this is run immediately after GUI is created, use it to initialise the UI
void SGUCentralManagement::initialise(){
    
}

// this is run after the application is created but before the GUI, use it to edit theme colours from configuration files
// do not use anything GUI related in this function, they are not set up yet
void SGUCentralManagement::earlyInitialise(){

}

// this is run after builtin fonts are imported, use it to import other fonts
// use commands in the format
// QFontDatabase::addApplicationFont([path to your fonts in your assets folder]);
void SGUCentralManagement::initialiseExtraFonts(){

}

// this is run after builtin custom rendered widgets are registered with QML, use it to register your own custom rendering widgets
// use commands in the format
// qmlRegisterType<[type of custom widget]>([name of custom widget], 0, 0, [name of custom widget]);
void SGUCentralManagement::initialiseCustomRendering(){

}

// this is run before the application terminates, use it to save user data
void SGUCentralManagement::terminate(){

}
