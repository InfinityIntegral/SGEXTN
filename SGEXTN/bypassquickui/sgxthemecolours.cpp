#include "sgxthemecolours.h"
#include "../primitives/sgxcolourrgba.h"
#include "../quickui/sgxquickinterface.h"
#include "../quickui/sgxthemecoloursetting.h"
#include <QColor>

SGXColourRGBA SGXThemeColours::getThemeColour(int themeColour){
    const QColor colour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour(themeColour);
    return SGXColourRGBA(colour.red(), colour.green(), colour.blue(), colour.alpha());
}
