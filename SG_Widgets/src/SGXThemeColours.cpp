#include <SGXThemeColours.h>
#include <SGXColourRGBA.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <private_api_Widgets/SGXThemeColourSetting.h>
#include <QColor>

SGXColourRGBA SGXThemeColours::getThemeColour(int themeColour){
    const QColor colour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour(themeColour);
    return SGXColourRGBA(colour.red(), colour.green(), colour.blue(), colour.alpha());
}
