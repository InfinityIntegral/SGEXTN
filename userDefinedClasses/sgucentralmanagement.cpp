#include "sgucentralmanagement.h"
#include <QString>
#include "../primitives/sgxcolourrgba.h"

// do not forget to replace the icons font file based on the app

// name of your application
QString SGUCentralManagement::applicationName = "";
// version number of your application, does not have to be number
QString SGUCentralManagement::applicationVersion = "";

SGXColourRGBA SGUCentralManagement::themeColour0 = SGXColourRGBA(0, 0, 0);
SGXColourRGBA SGUCentralManagement::themeColour1 = SGXColourRGBA(64, 0, 50);
SGXColourRGBA SGUCentralManagement::themeColour2 = SGXColourRGBA(128, 0, 100);
SGXColourRGBA SGUCentralManagement::themeColour3 = SGXColourRGBA(192, 0, 150);
SGXColourRGBA SGUCentralManagement::themeColour4 = SGXColourRGBA(255, 0, 200);
SGXColourRGBA SGUCentralManagement::themeColour5 = SGXColourRGBA(255, 64, 214);
SGXColourRGBA SGUCentralManagement::themeColour6 = SGXColourRGBA(255, 128, 228);
SGXColourRGBA SGUCentralManagement::themeColour7 = SGXColourRGBA(255, 192, 242);
SGXColourRGBA SGUCentralManagement::themeColour8 = SGXColourRGBA(255, 255, 255);

void SGUCentralManagement::initialise(){
    
}

void SGUCentralManagement::earlyInitialise(){
    
}

// is run when app closes
void SGUCentralManagement::terminate(){
    
}
