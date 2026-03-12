#include <private_api/SGEXTN_Structs_UnitTests.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Structs_RgbaColour.h>
#include <SGEXTN_Structs_HslaColour.h>
#include <SGEXTN_Structs_ContrastUtilities.h>

namespace {
bool isCloseEnough(float a, float b){
    return ((a > b - 0.001f) && (a < b + 0.001f));
}

bool isCloseEnoughWCAG3(float a, float b){
    return ((a > b - 0.1f) && (a < b + 0.1f));
}
}

void SGEXTN::Structs::UnitTests::testAll(){
    SGEXTN::Structs::UnitTests::testRgbaColour();
    SGEXTN::Structs::UnitTests::testHslaColour();
    SGEXTN::Structs::UnitTests::testContrastUtilities();
}

void SGEXTN::Structs::UnitTests::testRgbaColour(){
    SGEXTN::Structs::RgbaColour col(255, 0, 200, 255);
    if(col.getRed() != 255 || col.getGreen() != 0 || col.getBlue() != 200 || col.getTransparency() != 255){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgba int constructor fail");}
    col = SGEXTN::Structs::RgbaColour(255, 0, 200);
    if(col.getRed() != 255 || col.getGreen() != 0 || col.getBlue() != 200 || col.getTransparency() != 255){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgb int constructor fail");}
    col = SGEXTN::Structs::RgbaColour(1.0f, 0.0f, 0.75f, 1.0f);
    if(col.getRedFloat() != 1.0f || col.getGreenFloat() != 0.0f || col.getBlueFloat() != 191.0f / 255.0f || col.getTransparencyFloat() != 1.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgba float constructor fail");}
    col = SGEXTN::Structs::RgbaColour(1.0f, 0.0f, 0.75f);
    if(col.getRedFloat() != 1.0f || col.getGreenFloat() != 0.0f || col.getBlueFloat() != 191.0f / 255.0f || col.getTransparencyFloat() != 1.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgb float constructor fail");}
    col.setRed(45);
    if(col.getRed() != 45){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set red int fail");}
    col.setGreen(95);
    if(col.getGreen() != 95){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set green int fail");}
    col.setBlue(145);
    if(col.getBlue() != 145){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set blue int fail");}
    col.setTransparency(195);
    if(col.getTransparency() != 195){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set transparency int fail");}
    col.setRedFloat(0.2f);
    if(col.getRedFloat() != 0.2f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set red float fail");}
    col.setGreenFloat(0.4f);
    if(col.getGreenFloat() != 0.4f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set green float fail");}
    col.setBlueFloat(0.6f);
    if(col.getBlueFloat() != 0.6f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set blue float fail");}
    col.setTransparencyFloat(0.8f);
    if(col.getTransparencyFloat() != 0.8f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - set transparency float fail");}
    if(SGEXTN::Structs::RgbaColour(255, 0, 200, 255) == SGEXTN::Structs::RgbaColour(255, 0, 200, 254)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - equality check fail");}
    if(SGEXTN::Structs::RgbaColour(255, 0, 200, 255) != SGEXTN::Structs::RgbaColour(255, 0, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - inequality check fail");}
    col = SGEXTN::Structs::RgbaColour(255, 0, 200);
    if(col.rgbHexString() != "ff00c8"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgb hex string fail");}
    if(col.rgbaHexString() != "ff00c8ff"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgba hex string fail");}
    if(col.rgbHtmlString() != "rgb(255, 0, 200)"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgb html string fail");}
    if(col.rgbaHtmlString() != "rgba(255, 0, 200, 255)"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgba html string fail");}
    if(col.rgbFloatHtmlString() != "rgb(1.000, 0.000, 0.784)"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgb html float string fail");}
    if(col.rgbaFloatHtmlString() != "rgba(1.000, 0.000, 0.784, 1.000)"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - rgba html float string fail");}
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    col.gammaCorrectBegin(r, g, b);
    if(isCloseEnough(r, 1.0f) == false || isCloseEnough(g, 0.0f) == false || isCloseEnough(b, 0.57758f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - gamma correct begin fail");}
    col.gammaCorrectEnd(0.001f, 0.4f, 0.6f);
    if(col.getRed() != 3 || col.getGreen() != 170 || col.getBlue() != 203){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - gamma correct end fail");}
    col = SGEXTN::Structs::RgbaColour(100, 150, 200);
    if(col.linearTransformRed(0.5f, 0.1f, false) != SGEXTN::Structs::RgbaColour(76, 150, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform red no gamma correct fail");}
    if(col.linearTransformRed(0.5f, -1.2f, false) != SGEXTN::Structs::RgbaColour(0, 150, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform red no gamma correct underflow fail");}
    if(col.linearTransformRed(1.2f, 1.5f, false) != SGEXTN::Structs::RgbaColour(255, 150, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform red no gamma correct overflow fail");}
    if(col.linearTransformRed(0.5f, 0.1f, true) != SGEXTN::Structs::RgbaColour(113, 150, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform red fail");}
    if(col.linearTransformRed(0.5f, -1.2f, true) != SGEXTN::Structs::RgbaColour(0, 150, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform red underflow fail");}
    if(col.linearTransformRed(1.2f, 1.0f, true) != SGEXTN::Structs::RgbaColour(255, 150, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform red overflow fail");}
    if(col.linearTransformGreen(0.5f, 0.1f, false) != SGEXTN::Structs::RgbaColour(100, 101, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform green no gamma correct fail");}
    if(col.linearTransformGreen(0.5f, -1.2f, false) != SGEXTN::Structs::RgbaColour(100, 0, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform green no gamma correct underflow fail");}
    if(col.linearTransformGreen(1.2f, 1.5f, false) != SGEXTN::Structs::RgbaColour(100, 255, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform green no gamma correct overflow fail");}
    if(col.linearTransformGreen(0.5f, 0.1f, true) != SGEXTN::Structs::RgbaColour(100, 138, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform green fail");}
    if(col.linearTransformGreen(0.5f, -1.2f, true) != SGEXTN::Structs::RgbaColour(100, 0, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform green underflow fail");}
    if(col.linearTransformGreen(1.2f, 1.0f, true) != SGEXTN::Structs::RgbaColour(100, 255, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform green overflow fail");}
    if(col.linearTransformBlue(0.5f, 0.1f, false) != SGEXTN::Structs::RgbaColour(100, 150, 126)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform blue no gamma correct fail");}
    if(col.linearTransformBlue(0.5f, -1.2f, false) != SGEXTN::Structs::RgbaColour(100, 150, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform blue no gamma correct underflow fail");}
    if(col.linearTransformBlue(1.2f, 1.5f, false) != SGEXTN::Structs::RgbaColour(100, 150, 255)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform blue no gamma correct overflow fail");}
    if(col.linearTransformBlue(0.5f, 0.1f, true) != SGEXTN::Structs::RgbaColour(100, 150, 167)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform blue fail");}
    if(col.linearTransformBlue(0.5f, -1.2f, true) != SGEXTN::Structs::RgbaColour(100, 150, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform blue underflow fail");}
    if(col.linearTransformBlue(1.2f, 1.0f, true) != SGEXTN::Structs::RgbaColour(100, 150, 255)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform blue overflow fail");}
    if(col.linearTransformTransparency(0.5f, 0.1f) != SGEXTN::Structs::RgbaColour(100, 150, 200, 153)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform transparency fail");}
    if(col.linearTransformTransparency(0.5f, -1.2f) != SGEXTN::Structs::RgbaColour(100, 150, 200, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform transparency underflow fail");}
    if(col.linearTransformTransparency(1.2f, 1.0f) != SGEXTN::Structs::RgbaColour(100, 150, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - linear transform transparency overflow fail");}
    if(col.applyTint(SGEXTN::Structs::RgbaColour(255, 0, 200, 204), false) != SGEXTN::Structs::RgbaColour(224, 30, 200, 255)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - apply tint no gamma correct fail");}
    if(col.applyTint(SGEXTN::Structs::RgbaColour(255, 0, 200, 204), true) != SGEXTN::Structs::RgbaColour(234, 70, 200, 255)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - apply tint fail");}
    if(col.applyTintSeparateTransparency(SGEXTN::Structs::RgbaColour(255, 0, 200), 0.8f, false) != SGEXTN::Structs::RgbaColour(224, 30, 200, 255)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - apply tint separate transparency no gamma correct fail");}
    if(col.applyTintSeparateTransparency(SGEXTN::Structs::RgbaColour(255, 0, 200), 0.8f, true) != SGEXTN::Structs::RgbaColour(234, 70, 200, 255)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - apply tint separate transparency fail");}
    if(col.interpolate(SGEXTN::Structs::RgbaColour(255, 0, 200), 0.8f, false) != SGEXTN::Structs::RgbaColour(131, 120, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - interpolate no gamma correct fail");}
    if(col.interpolate(SGEXTN::Structs::RgbaColour(255, 0, 200), -0.2f, false) != SGEXTN::Structs::RgbaColour(255, 0, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - interpolate no gamma correct negative strength fail");}
    if(col.interpolate(SGEXTN::Structs::RgbaColour(255, 0, 200), 1.2f, false) != SGEXTN::Structs::RgbaColour(69, 180, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - interpolate no gamma correct very high strength fail");}
    if(col.interpolate(SGEXTN::Structs::RgbaColour(255, 0, 200), 0.8f, true) != SGEXTN::Structs::RgbaColour(149, 135, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - interpolate fail");}
    if(col.interpolate(SGEXTN::Structs::RgbaColour(255, 0, 200), -0.2f, true) != SGEXTN::Structs::RgbaColour(255, 0, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - interpolate negative strength fail");}
    if(col.interpolate(SGEXTN::Structs::RgbaColour(255, 0, 200), 1.2f, true) != SGEXTN::Structs::RgbaColour(0, 163, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - interpolate very high strength fail");}
    if(SGEXTN::Structs::RgbaColour(255, 0, 200).complement(false) != SGEXTN::Structs::RgbaColour(0, 255, 55)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - complement no gamma correct fail");}
    if(SGEXTN::Structs::RgbaColour(255, 0, 200).complement(true) != SGEXTN::Structs::RgbaColour(0, 255, 174)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - complement fail");}
}

void SGEXTN::Structs::UnitTests::testHslaColour(){
    SGEXTN::Structs::HslaColour col = SGEXTN::Structs::HslaColour(313.0f, 100.0f, 50.0f);
    if(col.getHue() != 313.0f || col.getSaturation() != 100.0f || col.getLightness() != 50.0f || col.getTransparency() != 100.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - getters or constructor from HSLA values fail");}
    col = SGEXTN::Structs::HslaColour(SGEXTN::Structs::RgbaColour(255, 0, 200));
    if(isCloseEnoughWCAG3(col.getHue(), 313.0f) == false || isCloseEnoughWCAG3(col.getSaturation(), 100.0f) == false || isCloseEnoughWCAG3(col.getLightness(), 50.0f) == false || isCloseEnough(col.getTransparency(), 100.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - RGBA constructor fail");}
    if(SGEXTN::Structs::HslaColour(SGEXTN::Structs::RgbaColour(255, 0, 200, 0)) == SGEXTN::Structs::HslaColour(SGEXTN::Structs::RgbaColour(255, 0, 200))){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - equality check fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 0.0f, 100.0f, 100.0f) != SGEXTN::Structs::HslaColour(313.0f, 0.0f, 100.0f)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - inequality check fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 0.0f, 100.0f).debugLog() != "hsla(313, 0, 100, 100)"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - debug log fail");}
    col.setHue(40.0f);
    col.setSaturation(10.0f);
    col.setLightness(20.0f);
    col.setTransparency(30.0f);
    if(col.getHue() != 40.0f || col.getSaturation() != 10.0f || col.getLightness() != 20.0f || col.getTransparency() != 30.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - setter fail");}
    if(isCloseEnough(col.invertHue().getHue(), 220.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - invert hue fail");}
    if(isCloseEnough(col.invertSaturation().getSaturation(), 90.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - invert saturation fail");}
    if(isCloseEnough(col.invertLightness().getLightness(), 80.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - invert lightness fail");}
    if(isCloseEnough(col.offsetHue(50.0f).getHue(), 90.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - offset hue fail");}
    if(isCloseEnough(col.offsetHue(330.0f).getHue(), 10.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - offset hue overflow fail");}
    if(isCloseEnough(col.offsetHue(-50.0f).getHue(), 350.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - offset hue underflow fail");}
    if(isCloseEnough(col.linearTransformSaturation(0.5f, 50.0f).getSaturation(), 55.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform saturation fail");}
    if(isCloseEnough(col.linearTransformSaturation(4.0f, 90.0f).getSaturation(), 100.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform saturation overflow fail");}
    if(isCloseEnough(col.linearTransformSaturation(-2.0f, 0.0f).getSaturation(), 0.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform saturation underflow fail");}
    if(isCloseEnough(col.linearTransformLightness(0.5f, 50.0f).getLightness(), 60.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform lightness fail");}
    if(isCloseEnough(col.linearTransformLightness(4.0f, 90.0f).getLightness(), 100.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform lightness overflow fail");}
    if(isCloseEnough(col.linearTransformLightness(-2.0f, 0.0f).getLightness(), 0.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform lightness underflow fail");}
    if(isCloseEnough(col.linearTransformTransparency(0.5f, 50.0f).getTransparency(), 65.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform transparency fail");}
    if(isCloseEnough(col.linearTransformTransparency(4.0f, 90.0f).getTransparency(), 100.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform transparency overflow fail");}
    if(isCloseEnough(col.linearTransformTransparency(-2.0f, 0.0f).getTransparency(), 0.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - linear transform transparency underflow fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 0.0f).toRGBA() != SGEXTN::Structs::RgbaColour(0, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 0 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 10.0f).toRGBA() != SGEXTN::Structs::RgbaColour(51, 0, 40)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 1 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 20.0f).toRGBA() != SGEXTN::Structs::RgbaColour(102, 0, 80)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 2 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 30.0f).toRGBA() != SGEXTN::Structs::RgbaColour(153, 0, 120)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 3 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 40.0f).toRGBA() != SGEXTN::Structs::RgbaColour(204, 0, 160)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 4 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 50.0f).toRGBA() != SGEXTN::Structs::RgbaColour(255, 0, 200)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 5 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 60.0f).toRGBA() != SGEXTN::Structs::RgbaColour(255, 51, 211)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 6 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 70.0f).toRGBA() != SGEXTN::Structs::RgbaColour(255, 102, 222)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 7 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 80.0f).toRGBA() != SGEXTN::Structs::RgbaColour(255, 153, 233)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 8 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 90.0f).toRGBA() != SGEXTN::Structs::RgbaColour(255, 204, 244)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 9 fail");}
    if(SGEXTN::Structs::HslaColour(313.0f, 100.0f, 100.0f).toRGBA() != SGEXTN::Structs::RgbaColour(255, 255, 255)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::HslaColour - hsl to rgb test case 10 fail");}
}

void SGEXTN::Structs::UnitTests::testContrastUtilities(){
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 255, 255), SGEXTN::Structs::RgbaColour(0, 0, 0)), 106.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 1 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(0, 0, 0), SGEXTN::Structs::RgbaColour(0, 0, 0)), 0.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 2 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 255, 255), SGEXTN::Structs::RgbaColour(118, 118, 118)), 71.6f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 3 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 100, 0), SGEXTN::Structs::RgbaColour(20, 20, 20)), 47.9f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 4 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(123, 131, 222), SGEXTN::Structs::RgbaColour(34, 45, 67)), 36.8f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 5 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(23, 162, 184), SGEXTN::Structs::RgbaColour(255, 255, 255)), -62.1f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 6 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 255, 255), SGEXTN::Structs::RgbaColour(183, 21, 64)), 80.6f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 7 fail");}
}
