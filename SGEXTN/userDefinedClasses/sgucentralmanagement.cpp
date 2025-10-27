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
#include "../widgets/instantiable/sgwcolourpickerwidget.h"
// this is run immediately after GUI is created, use it to initialise the UI
void SGUCentralManagement::initialise(){
    new SGWColourPickerWidget(SGWWidget::parentWidget, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f, -1.0f, 1.0f, -1.0f, SGXColourRGBA(255, 0, 200, 200));
}

// this is run after the application is created but before the GUI, use it to set default theme colours of your app
// do not use anything GUI related in this function, they are not set up yet
void SGUCentralManagement::setDefaultTheme(){

}

// this is run after builtin fonts are imported, use it to import other fonts
// use commands in the format
// QFontDatabase::addApplicationFont([path to your fonts in your assets folder]);
// you must add a font with name AppIcons.sg if you want any icons
void SGUCentralManagement::importExtraFonts(){

}

// this is run before the application terminates, use it to save user data
void SGUCentralManagement::terminate(){

}

void SGUCentralManagement::interpretCmdArgs(int argc, char **argv){
    (void)argc;
    (void)argv;
}
