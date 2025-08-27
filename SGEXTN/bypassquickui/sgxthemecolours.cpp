#include "sgxthemecolours.h"
#include "../primitives/sgxcolourrgba.h"
#include "../quickui/sgxquickinterface.h"

SGXColourRGBA SGXThemeColours::getThemeColour(int themeColour){
    return (*SGXQuickInterface::themeColoursSingleton).getThemeColour(themeColour);
}
