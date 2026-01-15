#include <private_api_Widgets/SGXThemeColourSetting.h>
#include <SGXColourRGBA.h>
#include <QColor>
#include <SGXThemeColoursCustomisation.h>

namespace {
inline QColor temp_getQColour(SGXColourRGBA x){
    return QColor(x.getRed(), x.getGreen(), x.getBlue(), x.getTransparency());
}
}

QColor SGXThemeColourSetting::getThemeColour(int x) const { // NOLINT(readability-convert-member-functions-to-static)
    if(x < 0 || x >= SGXThemeColoursCustomisation::themeColours.length()){return temp_getQColour(SGXColourRGBA(0, 0, 0, 0));}
    return temp_getQColour(SGXThemeColoursCustomisation::themeColours.at(x));
}
