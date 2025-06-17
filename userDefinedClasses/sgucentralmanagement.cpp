#include "sgucentralmanagement.h"
#include <QString>
#include "../primitives/sgxcolourrgba.h"

// do not forget to replace the icons font file based on the app

// name of your application
QString SGUCentralManagement::applicationName = "";
// version number of your application, does not have to be number
QString SGUCentralManagement::applicationVersion = "";

// set your theme colours
SGXColourRGBA SGUCentralManagement::themeColour0 = SGXColourRGBA(0, 0, 0);
SGXColourRGBA SGUCentralManagement::themeColour1 = SGXColourRGBA(64, 0, 50);
SGXColourRGBA SGUCentralManagement::themeColour2 = SGXColourRGBA(128, 0, 100);
SGXColourRGBA SGUCentralManagement::themeColour3 = SGXColourRGBA(192, 0, 150);
SGXColourRGBA SGUCentralManagement::themeColour4 = SGXColourRGBA(255, 0, 200);
SGXColourRGBA SGUCentralManagement::themeColour5 = SGXColourRGBA(255, 64, 214);
SGXColourRGBA SGUCentralManagement::themeColour6 = SGXColourRGBA(255, 128, 228);
SGXColourRGBA SGUCentralManagement::themeColour7 = SGXColourRGBA(255, 192, 242);
SGXColourRGBA SGUCentralManagement::themeColour8 = SGXColourRGBA(255, 255, 255);

// you are recommended to use the theme colours that you defined to set the below colours
SGXColourRGBA SGUCentralManagement::rootWindowColour = SGUCentralManagement::themeColour6;
SGXColourRGBA SGUCentralManagement::renderSpaceColour = SGUCentralManagement::themeColour4;
SGXColourRGBA SGUCentralManagement::widgetColour1 = SGUCentralManagement::themeColour4;
SGXColourRGBA SGUCentralManagement::widgetColour2 = SGUCentralManagement::themeColour8;
SGXColourRGBA SGUCentralManagement::widgetColour3 = SGUCentralManagement::themeColour6;
SGXColourRGBA SGUCentralManagement::textBackgroundColour = SGUCentralManagement::themeColour8;
SGXColourRGBA SGUCentralManagement::textForegroundColour = SGUCentralManagement::themeColour4;
SGXColourRGBA SGUCentralManagement::buttonBackgroundColour = SGUCentralManagement::themeColour4;
SGXColourRGBA SGUCentralManagement::buttonForegroundColour = SGUCentralManagement::themeColour8;
SGXColourRGBA SGUCentralManagement::buttonHoverBackgroundColour = SGUCentralManagement::themeColour3;
SGXColourRGBA SGUCentralManagement::buttonHoverForegroundColour = SGUCentralManagement::themeColour7;
SGXColourRGBA SGUCentralManagement::buttonPressedBackgroundColour = SGUCentralManagement::themeColour2;
SGXColourRGBA SGUCentralManagement::buttonPressedForegroundColour = SGUCentralManagement::themeColour6;
SGXColourRGBA SGUCentralManagement::unselectedButtonBackgroundColour = SGUCentralManagement::themeColour5;
SGXColourRGBA SGUCentralManagement::unselectedButtonForegroundColour = SGUCentralManagement::themeColour8;
SGXColourRGBA SGUCentralManagement::unselectedButtonHoverBackgroundColour = SGUCentralManagement::themeColour4;
SGXColourRGBA SGUCentralManagement::unselectedButtonHoverForegroundColour = SGUCentralManagement::themeColour7;
SGXColourRGBA SGUCentralManagement::inputFieldBackgroundColour = SGUCentralManagement::themeColour4;
SGXColourRGBA SGUCentralManagement::inputFieldForegroundColour = SGUCentralManagement::themeColour8;
SGXColourRGBA SGUCentralManagement::inputFieldSelectedHighlightBackgroundColour = SGUCentralManagement::themeColour6;
SGXColourRGBA SGUCentralManagement::inputFieldSelectedHighlightForegroundColour = SGUCentralManagement::themeColour2;
SGXColourRGBA SGUCentralManagement::inputFieldHoverBackgroundColour = SGUCentralManagement::themeColour3;
SGXColourRGBA SGUCentralManagement::inputFieldHoverForegroundColour = SGUCentralManagement::themeColour7;
SGXColourRGBA SGUCentralManagement::inputFieldFocusedBackgroundColour = SGUCentralManagement::themeColour2;
SGXColourRGBA SGUCentralManagement::inputFieldFocusedForegroundColour = SGUCentralManagement::themeColour6;
SGXColourRGBA SGUCentralManagement::scrollBarBackgroundColour = SGUCentralManagement::themeColour6;
SGXColourRGBA SGUCentralManagement::scrollBarForegroundColour = SGUCentralManagement::themeColour4;
SGXColourRGBA SGUCentralManagement::scrollBarForegroundHoverColour = SGUCentralManagement::themeColour3;
SGXColourRGBA SGUCentralManagement::scrollBarForegroundPressedColour = SGUCentralManagement::themeColour2;

// is run when app opens
void SGUCentralManagement::initialise(){
    
}

// is run when app closes
void SGUCentralManagement::terminate(){
    
}
