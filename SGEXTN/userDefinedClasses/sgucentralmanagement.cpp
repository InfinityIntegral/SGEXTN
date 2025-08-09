#include "sgucentralmanagement.h"
#include <QString>
#include "../primitives/sgxcolourrgba.h"

// pls update README and license
// also change the application name in the .pro
// do not forget to replace the icons font file and app icon in assets.qrc based on the app, do not change their file paths though
// the icons font file can be of any type (otf, ttf, etc) that Qt support, but its name must be AppIcons.sg and the internal font family name must be AppIcons.sg

// name of your application
QString SGUCentralManagement::applicationName = "SGEXTN";
// version number of your application, does not have to be number
QString SGUCentralManagement::applicationVersion = "v2";
// name of your organisation
QString SGUCentralManagement::organisationName = "05524F.sg (Singapore)";
// name of root folder of your application, only use uppercase or lowercase letters, definitely no banned characters, no dots, no spaces, no hyphens, no underscores, avoid numbers, avoid non ASCII characters
QString SGUCentralManagement::rootFolderName = "SGEXTN";

// theme colours of your application
SGXColourRGBA SGUCentralManagement::themeColour0 = SGXColourRGBA(0, 0, 0);
SGXColourRGBA SGUCentralManagement::themeColour1 = SGXColourRGBA(64, 0, 50);
SGXColourRGBA SGUCentralManagement::themeColour2 = SGXColourRGBA(128, 0, 100);
SGXColourRGBA SGUCentralManagement::themeColour3 = SGXColourRGBA(191, 0, 150);
SGXColourRGBA SGUCentralManagement::themeColour4 = SGXColourRGBA(255, 0, 200);
SGXColourRGBA SGUCentralManagement::themeColour5 = SGXColourRGBA(255, 64, 214);
SGXColourRGBA SGUCentralManagement::themeColour6 = SGXColourRGBA(255, 128, 227);
SGXColourRGBA SGUCentralManagement::themeColour7 = SGXColourRGBA(255, 191, 241);
SGXColourRGBA SGUCentralManagement::themeColour8 = SGXColourRGBA(255, 255, 255);

// customise vesicle properties for the animation
float SGUCentralManagement::cuteVesiclesMembraneThickness = 0.05f;
float SGUCentralManagement::cuteVesiclesMaximumCenterDistance = 1.5f;
float SGUCentralManagement::cuteVesiclesMaximumVelocity = 0.01f;
float SGUCentralManagement::cuteVesiclesMaximumAcceleration = 0.01f;
float SGUCentralManagement::cuteVesiclesMaximumRadiusChange = 0.01f;
float SGUCentralManagement::cuteVesiclesMinimumRadius = 0.1f;
float SGUCentralManagement::cuteVesiclesMaximumRadius = 0.35f;
float SGUCentralManagement::cuteVesiclesMaximumRadiusOffsetChange = 0.1f;
float SGUCentralManagement::cuteVesiclesMaximumRadiusOffset = 0.1f;
SGXColourRGBA SGUCentralManagement::cuteVesiclesMembraneColour = SGXColourRGBA(255, 0, 200);
SGXColourRGBA SGUCentralManagement::cuteVesiclesContentsColour = SGXColourRGBA(255, 255, 255);
float SGUCentralManagement::cuteVesiclesCenterTransparency = 0.1f;
float SGUCentralManagement::cuteVesiclesEdgeTransparency = 0.05f;
float SGUCentralManagement::cuteVesiclesMembraneTransparency = 0.2f;
float SGUCentralManagement::cuteVesiclesFrameRate = 10.0f;
#include "../widgets/sgwcolourpickerwidget.h"
#include "../widgets/sgwwidget.h"
// this is run immediately after GUI is created, use it to initialise the UI
void SGUCentralManagement::initialise(){
    new SGWColourPickerWidget(SGWWidget::parentWidget, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 2.0f, 0.0f, 1.0f, SGXColourRGBA(0, 0, 0));
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
