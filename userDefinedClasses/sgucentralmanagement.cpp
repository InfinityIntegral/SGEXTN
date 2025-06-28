#include "sgucentralmanagement.h"
#include <QString>
#include "../primitives/sgxcolourrgba.h"

// do not forget to replace the icons font file based on the app

// name of your application
QString SGUCentralManagement::applicationName = "";
// version number of your application, does not have to be number
QString SGUCentralManagement::applicationVersion = "";

SGXColourRGBA SGUCentralManagement::themeColour0 = SGXColourRGBA(0, 0, 0);
SGXColourRGBA SGUCentralManagement::themeColour1 = SGXColourRGBA(136, 0, 107);
SGXColourRGBA SGUCentralManagement::themeColour2 = SGXColourRGBA(186, 0, 146);
SGXColourRGBA SGUCentralManagement::themeColour3 = SGXColourRGBA(224, 0, 175);
SGXColourRGBA SGUCentralManagement::themeColour4 = SGXColourRGBA(255, 0, 200);
SGXColourRGBA SGUCentralManagement::themeColour5 = SGXColourRGBA(255, 136, 215);
SGXColourRGBA SGUCentralManagement::themeColour6 = SGXColourRGBA(255, 186, 229);
SGXColourRGBA SGUCentralManagement::themeColour7 = SGXColourRGBA(255, 224, 243);
SGXColourRGBA SGUCentralManagement::themeColour8 = SGXColourRGBA(255, 255, 255);
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

void SGUCentralManagement::initialise(){
    
}

void SGUCentralManagement::earlyInitialise(){
    
}

void SGUCentralManagement::terminate(){
    
}
