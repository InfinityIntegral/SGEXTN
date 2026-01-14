#include <SGXThemeColours.h>
#include <SGXColourRGBA.h>
#include <private_api_Widgets/SGXQuickInterface.h>
#include <private_api_Widgets/SGXThemeColourSetting.h>
#include <QColor>
#include <SGLArray.h>
#include <SGXColourHSLA.h>

SGXColourRGBA SGXThemeColours::getThemeColour(int themeColour){
    const QColor colour = (*SGXQuickInterface::themeColoursSingleton).getThemeColour(themeColour);
    return SGXColourRGBA(colour.red(), colour.green(), colour.blue(), colour.alpha());
}

SGLArray<SGXColourRGBA> SGXThemeColours::generateSincerityUIThemeSet(SGXColourRGBA baseColour, bool darkMode){
    SGLArray<SGXColourRGBA> arr(6);
    if(darkMode == false){
        arr.at(0) = SGXColourHSLA(baseColour).getColourWithContrast(0.9f);
        arr.at(1) = SGXColourHSLA(baseColour).getColourWithContrast(0.6f);
        arr.at(2) = SGXColourHSLA(baseColour).getColourWithContrast(0.3f);
        arr.at(3) = SGXColourHSLA(baseColour).getColourWithContrast(2.0f);
        arr.at(4) = SGXColourHSLA(baseColour).getColourWithContrast(1.85f);
        arr.at(5) = SGXColourHSLA(baseColour).getColourWithContrast(1.7f);
    }
    else{
        arr.at(0) = SGXColourHSLA(baseColour).getColourWithContrast(2.0f);
        arr.at(1) = SGXColourHSLA(baseColour).getColourWithContrast(1.85f);
        arr.at(2) = SGXColourHSLA(baseColour).getColourWithContrast(1.7f);
        arr.at(3) = SGXColourHSLA(baseColour).getColourWithContrast(0.9f);
        arr.at(4) = SGXColourHSLA(baseColour).getColourWithContrast(0.6f);
        arr.at(5) = SGXColourHSLA(baseColour).getColourWithContrast(0.3f);
    }
    return arr;
}
