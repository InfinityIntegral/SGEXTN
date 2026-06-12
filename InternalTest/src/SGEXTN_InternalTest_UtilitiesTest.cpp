#include <private_api/SGEXTN_InternalTest_UtilitiesTest.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_Utilities_RgbaColour.h>
#include <SGEXTN_Utilities_HslaColour.h>
#include <SGEXTN_Utilities_ContrastUtilities.h>
#include <SGEXTN_Utilities_Identifier.h>
#include <SGEXTN_Utilities_IdentifierRegistry.h>
#include <SGEXTN_Utilities_DateTime.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_Containers_Array.h>

namespace {
bool isCloseEnough(float a, float b){
    return ((a > b - 0.001f) && (a < b + 0.001f));
}

bool isCloseEnoughWCAG3(float a, float b){
    return ((a > b - 0.1f) && (a < b + 0.1f));
}
}

void SGEXTN::InternalTest::UtilitiesTest::testAll(){
    SGEXTN::InternalTest::UtilitiesTest::testRgbaColour();
    SGEXTN::InternalTest::UtilitiesTest::testHslaColour();
    SGEXTN::InternalTest::UtilitiesTest::testContrastUtilities();
    SGEXTN::InternalTest::UtilitiesTest::testIdentifier();
    SGEXTN::InternalTest::UtilitiesTest::testIdentifierRegistry();
    SGEXTN::InternalTest::UtilitiesTest::testDateTime();
}

void SGEXTN::InternalTest::UtilitiesTest::testRgbaColour(){
    SGEXTN::Utilities::RgbaColour col(255, 0, 200, 255);
    if(col.getRed() != 255 || col.getGreen() != 0 || col.getBlue() != 200 || col.getTransparency() != 255){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgba int constructor fail");}
    col = SGEXTN::Utilities::RgbaColour(255, 0, 200);
    if(col.getRed() != 255 || col.getGreen() != 0 || col.getBlue() != 200 || col.getTransparency() != 255){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgb int constructor fail");}
    col = SGEXTN::Utilities::RgbaColour(1.0f, 0.0f, 0.75f, 1.0f);
    if(col.getRedFloat() != 1.0f || col.getGreenFloat() != 0.0f || col.getBlueFloat() != 191.0f / 255.0f || col.getTransparencyFloat() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgba float constructor fail");}
    col = SGEXTN::Utilities::RgbaColour(1.0f, 0.0f, 0.75f);
    if(col.getRedFloat() != 1.0f || col.getGreenFloat() != 0.0f || col.getBlueFloat() != 191.0f / 255.0f || col.getTransparencyFloat() != 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgb float constructor fail");}
    col.setRed(45);
    if(col.getRed() != 45){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set red int fail");}
    col.setGreen(95);
    if(col.getGreen() != 95){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set green int fail");}
    col.setBlue(145);
    if(col.getBlue() != 145){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set blue int fail");}
    col.setTransparency(195);
    if(col.getTransparency() != 195){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set transparency int fail");}
    col.setRedFloat(0.2f);
    if(col.getRedFloat() != 0.2f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set red float fail");}
    col.setGreenFloat(0.4f);
    if(col.getGreenFloat() != 0.4f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set green float fail");}
    col.setBlueFloat(0.6f);
    if(col.getBlueFloat() != 0.6f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set blue float fail");}
    col.setTransparencyFloat(0.8f);
    if(col.getTransparencyFloat() != 0.8f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - set transparency float fail");}
    if(SGEXTN::Utilities::RgbaColour(255, 0, 200, 255) == SGEXTN::Utilities::RgbaColour(255, 0, 200, 254)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - equality check fail");}
    if(SGEXTN::Utilities::RgbaColour(255, 0, 200, 255) != SGEXTN::Utilities::RgbaColour(255, 0, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - inequality check fail");}
    if(SGEXTN::Utilities::RgbaColour(255, 0, 200, 255).debugPrint() != "rgba(255, 0, 200, 255)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - debug log fail");}
    col = SGEXTN::Utilities::RgbaColour(255, 0, 200);
    if(col.rgbHexString() != "ff00c8"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgb hex string fail");}
    if(col.rgbaHexString() != "ff00c8ff"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgba hex string fail");}
    if(col.rgbHtmlString() != "rgb(255, 0, 200)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgb html string fail");}
    if(col.rgbaHtmlString() != "rgba(255, 0, 200, 255)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgba html string fail");}
    if(col.rgbFloatHtmlString() != "rgb(1.000, 0.000, 0.784)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgb html float string fail");}
    if(col.rgbaFloatHtmlString() != "rgba(1.000, 0.000, 0.784, 1.000)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - rgba html float string fail");}
    col.setBlue(128);
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    col.gammaCorrectBegin(r, g, b);
    if(isCloseEnough(r, 1.0f) == false || isCloseEnough(g, 0.0f) == false || isCloseEnough(b, 0.21586f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - gamma correct begin fail");}
    col.gammaCorrectEnd(0.001f, 0.4f, 0.6f);
    if(col.getRed() != 3 || col.getGreen() != 170 || col.getBlue() != 203){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - gamma correct end fail");}
    col = SGEXTN::Utilities::RgbaColour(100, 150, 200);
    if(col.linearTransformRed(0.5f, 0.1f, false) != SGEXTN::Utilities::RgbaColour(76, 150, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform red no gamma correct fail");}
    if(col.linearTransformRed(0.5f, -1.2f, false) != SGEXTN::Utilities::RgbaColour(0, 150, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform red no gamma correct underflow fail");}
    if(col.linearTransformRed(1.2f, 1.5f, false) != SGEXTN::Utilities::RgbaColour(255, 150, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform red no gamma correct overflow fail");}
    if(col.linearTransformRed(0.5f, 0.1f, true) != SGEXTN::Utilities::RgbaColour(113, 150, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform red fail");}
    if(col.linearTransformRed(0.5f, -1.2f, true) != SGEXTN::Utilities::RgbaColour(0, 150, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform red underflow fail");}
    if(col.linearTransformRed(1.2f, 1.0f, true) != SGEXTN::Utilities::RgbaColour(255, 150, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform red overflow fail");}
    if(col.linearTransformGreen(0.5f, 0.1f, false) != SGEXTN::Utilities::RgbaColour(100, 101, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform green no gamma correct fail");}
    if(col.linearTransformGreen(0.5f, -1.2f, false) != SGEXTN::Utilities::RgbaColour(100, 0, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform green no gamma correct underflow fail");}
    if(col.linearTransformGreen(1.2f, 1.5f, false) != SGEXTN::Utilities::RgbaColour(100, 255, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform green no gamma correct overflow fail");}
    if(col.linearTransformGreen(0.5f, 0.1f, true) != SGEXTN::Utilities::RgbaColour(100, 138, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform green fail");}
    if(col.linearTransformGreen(0.5f, -1.2f, true) != SGEXTN::Utilities::RgbaColour(100, 0, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform green underflow fail");}
    if(col.linearTransformGreen(1.2f, 1.0f, true) != SGEXTN::Utilities::RgbaColour(100, 255, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform green overflow fail");}
    if(col.linearTransformBlue(0.5f, 0.1f, false) != SGEXTN::Utilities::RgbaColour(100, 150, 126)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform blue no gamma correct fail");}
    if(col.linearTransformBlue(0.5f, -1.2f, false) != SGEXTN::Utilities::RgbaColour(100, 150, 0)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform blue no gamma correct underflow fail");}
    if(col.linearTransformBlue(1.2f, 1.5f, false) != SGEXTN::Utilities::RgbaColour(100, 150, 255)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform blue no gamma correct overflow fail");}
    if(col.linearTransformBlue(0.5f, 0.1f, true) != SGEXTN::Utilities::RgbaColour(100, 150, 167)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform blue fail");}
    if(col.linearTransformBlue(0.5f, -1.2f, true) != SGEXTN::Utilities::RgbaColour(100, 150, 0)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform blue underflow fail");}
    if(col.linearTransformBlue(1.2f, 1.0f, true) != SGEXTN::Utilities::RgbaColour(100, 150, 255)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform blue overflow fail");}
    if(col.linearTransformTransparency(0.5f, 0.1f) != SGEXTN::Utilities::RgbaColour(100, 150, 200, 153)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform transparency fail");}
    if(col.linearTransformTransparency(0.5f, -1.2f) != SGEXTN::Utilities::RgbaColour(100, 150, 200, 0)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform transparency underflow fail");}
    if(col.linearTransformTransparency(1.2f, 1.0f) != SGEXTN::Utilities::RgbaColour(100, 150, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - linear transform transparency overflow fail");}
    if(col.applyTint(SGEXTN::Utilities::RgbaColour(255, 0, 200, 204), false) != SGEXTN::Utilities::RgbaColour(224, 30, 200, 255)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - apply tint no gamma correct fail");}
    if(col.applyTint(SGEXTN::Utilities::RgbaColour(255, 0, 200, 204), true) != SGEXTN::Utilities::RgbaColour(234, 70, 200, 255)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - apply tint fail");}
    if(col.applyTintSeparateTransparency(SGEXTN::Utilities::RgbaColour(255, 0, 200), 0.8f, false) != SGEXTN::Utilities::RgbaColour(224, 30, 200, 255)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - apply tint separate transparency no gamma correct fail");}
    if(col.applyTintSeparateTransparency(SGEXTN::Utilities::RgbaColour(255, 0, 200), 0.8f, true) != SGEXTN::Utilities::RgbaColour(234, 70, 200, 255)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - apply tint separate transparency fail");}
    if(col.interpolate(SGEXTN::Utilities::RgbaColour(255, 0, 200), 0.8f, false) != SGEXTN::Utilities::RgbaColour(131, 120, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - interpolate no gamma correct fail");}
    if(col.interpolate(SGEXTN::Utilities::RgbaColour(255, 0, 200), -0.2f, false) != SGEXTN::Utilities::RgbaColour(255, 0, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - interpolate no gamma correct negative strength fail");}
    if(col.interpolate(SGEXTN::Utilities::RgbaColour(255, 0, 200), 1.2f, false) != SGEXTN::Utilities::RgbaColour(69, 180, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - interpolate no gamma correct very high strength fail");}
    if(col.interpolate(SGEXTN::Utilities::RgbaColour(255, 0, 200), 0.8f, true) != SGEXTN::Utilities::RgbaColour(149, 135, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - interpolate fail");}
    if(col.interpolate(SGEXTN::Utilities::RgbaColour(255, 0, 200), -0.2f, true) != SGEXTN::Utilities::RgbaColour(255, 0, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - interpolate negative strength fail");}
    if(col.interpolate(SGEXTN::Utilities::RgbaColour(255, 0, 200), 1.2f, true) != SGEXTN::Utilities::RgbaColour(0, 163, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - interpolate very high strength fail");}
    if(SGEXTN::Utilities::RgbaColour(255, 0, 200).complement(false) != SGEXTN::Utilities::RgbaColour(0, 255, 55)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - complement no gamma correct fail");}
    if(SGEXTN::Utilities::RgbaColour(255, 0, 200).complement(true) != SGEXTN::Utilities::RgbaColour(0, 255, 174)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour - complement fail");}
}

void SGEXTN::InternalTest::UtilitiesTest::testHslaColour(){
    SGEXTN::Utilities::HslaColour col = SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 50.0f);
    if(col.getHue() != 313.0f || col.getSaturation() != 100.0f || col.getLightness() != 50.0f || col.getTransparency() != 100.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - getters or constructor from HSLA values fail");}
    col = SGEXTN::Utilities::HslaColour(SGEXTN::Utilities::RgbaColour(255, 0, 200));
    if(isCloseEnoughWCAG3(col.getHue(), 313.0f) == false || isCloseEnoughWCAG3(col.getSaturation(), 100.0f) == false || isCloseEnoughWCAG3(col.getLightness(), 50.0f) == false || isCloseEnough(col.getTransparency(), 100.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - RGBA constructor fail");}
    if(SGEXTN::Utilities::HslaColour(SGEXTN::Utilities::RgbaColour(255, 0, 200, 0)) == SGEXTN::Utilities::HslaColour(SGEXTN::Utilities::RgbaColour(255, 0, 200))){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - equality check fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 0.0f, 100.0f, 100.0f) != SGEXTN::Utilities::HslaColour(313.0f, 0.0f, 100.0f)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - inequality check fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 0.0f, 100.0f).debugPrint() != "hsla(313, 0, 100, 100)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - debug log fail");}
    col.setHue(40.0f);
    col.setSaturation(10.0f);
    col.setLightness(20.0f);
    col.setTransparency(30.0f);
    if(col.getHue() != 40.0f || col.getSaturation() != 10.0f || col.getLightness() != 20.0f || col.getTransparency() != 30.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - setter fail");}
    if(isCloseEnough(col.invertHue().getHue(), 220.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - invert hue fail");}
    if(isCloseEnough(col.invertSaturation().getSaturation(), 90.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - invert saturation fail");}
    if(isCloseEnough(col.invertLightness().getLightness(), 80.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - invert lightness fail");}
    if(isCloseEnough(col.offsetHue(50.0f).getHue(), 90.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - offset hue fail");}
    if(isCloseEnough(col.offsetHue(330.0f).getHue(), 10.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - offset hue overflow fail");}
    if(isCloseEnough(col.offsetHue(-50.0f).getHue(), 350.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - offset hue underflow fail");}
    if(isCloseEnough(col.linearTransformSaturation(0.5f, 50.0f).getSaturation(), 55.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform saturation fail");}
    if(isCloseEnough(col.linearTransformSaturation(4.0f, 90.0f).getSaturation(), 100.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform saturation overflow fail");}
    if(isCloseEnough(col.linearTransformSaturation(-2.0f, 0.0f).getSaturation(), 0.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform saturation underflow fail");}
    if(isCloseEnough(col.linearTransformLightness(0.5f, 50.0f).getLightness(), 60.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform lightness fail");}
    if(isCloseEnough(col.linearTransformLightness(4.0f, 90.0f).getLightness(), 100.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform lightness overflow fail");}
    if(isCloseEnough(col.linearTransformLightness(-2.0f, 0.0f).getLightness(), 0.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform lightness underflow fail");}
    if(isCloseEnough(col.linearTransformTransparency(0.5f, 50.0f).getTransparency(), 65.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform transparency fail");}
    if(isCloseEnough(col.linearTransformTransparency(4.0f, 90.0f).getTransparency(), 100.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform transparency overflow fail");}
    if(isCloseEnough(col.linearTransformTransparency(-2.0f, 0.0f).getTransparency(), 0.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - linear transform transparency underflow fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 0.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(0, 0, 0)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 0 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 10.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(51, 0, 40)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 1 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 20.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(102, 0, 80)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 2 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 30.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(153, 0, 120)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 3 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 40.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(204, 0, 160)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 4 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 50.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(255, 0, 200)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 5 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 60.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(255, 51, 211)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 6 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 70.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(255, 102, 222)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 7 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 80.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(255, 153, 233)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 8 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 90.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(255, 204, 244)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 9 fail");}
    if(SGEXTN::Utilities::HslaColour(313.0f, 100.0f, 100.0f).toRGBA() != SGEXTN::Utilities::RgbaColour(255, 255, 255)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::HslaColour - hsl to rgb test case 10 fail");}
}

void SGEXTN::InternalTest::UtilitiesTest::testContrastUtilities(){
    if(isCloseEnoughWCAG3(SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour(255, 255, 255), SGEXTN::Utilities::RgbaColour(0, 0, 0)), 106.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - WCAG3 test 1 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour(0, 0, 0), SGEXTN::Utilities::RgbaColour(0, 0, 0)), 0.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - WCAG3 test 2 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour(255, 255, 255), SGEXTN::Utilities::RgbaColour(118, 118, 118)), 71.6f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - WCAG3 test 3 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour(255, 100, 0), SGEXTN::Utilities::RgbaColour(20, 20, 20)), 47.9f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - WCAG3 test 4 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour(123, 131, 222), SGEXTN::Utilities::RgbaColour(34, 45, 67)), 36.8f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - WCAG3 test 5 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour(23, 162, 184), SGEXTN::Utilities::RgbaColour(255, 255, 255)), -62.1f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - WCAG3 test 6 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour(255, 255, 255), SGEXTN::Utilities::RgbaColour(183, 21, 64)), 80.6f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - WCAG3 test 7 fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(0.1f, false, false), 200.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast too small text fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(1.0f, false, false), 60.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(2.0f, false, true), 200.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast too big body text fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(0.7f, false, true), 80.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast body text fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(1.0f, false, true), 75.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast body text +15 fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(1.0f, true, false), 48.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast bold text fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(2.0f, true, true), 200.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast too big body text fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(0.5f, true, true), 80.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast body text fail");}
    if(isCloseEnough(SGEXTN::Utilities::ContrastUtilities::safeContrast(1.0f, true, true), 63.0f) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - safe contrast body text +15 fail");}
    bool isPossible = false;
    if(SGEXTN::Utilities::ContrastUtilities::getForegroundLightMode(SGEXTN::Utilities::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(171, 0, 135) || isPossible == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get foreground light possible fail");}
    if(SGEXTN::Utilities::ContrastUtilities::getForegroundLightMode(SGEXTN::Utilities::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(0, 0, 0) || isPossible == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get foreground light impossible fail");}
    if(SGEXTN::Utilities::ContrastUtilities::getForegroundDarkMode(SGEXTN::Utilities::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(255, 158, 234) || isPossible == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get foreground dark possible fail");}
    if(SGEXTN::Utilities::ContrastUtilities::getForegroundDarkMode(SGEXTN::Utilities::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(255, 255, 255) || isPossible == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get foreground dark impossible fail");}
    if(SGEXTN::Utilities::ContrastUtilities::getBackgroundLightMode(SGEXTN::Utilities::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(255, 160, 234) || isPossible == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get background light possible fail");}
    if(SGEXTN::Utilities::ContrastUtilities::getBackgroundLightMode(SGEXTN::Utilities::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(255, 255, 255) || isPossible == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get background light impossible fail");}
    if(SGEXTN::Utilities::ContrastUtilities::getBackgroundDarkMode(SGEXTN::Utilities::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(185, 0, 145) || isPossible == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get background dark possible fail");}
    if(SGEXTN::Utilities::ContrastUtilities::getBackgroundDarkMode(SGEXTN::Utilities::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Utilities::RgbaColour(0, 0, 0) || isPossible == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities - get background dark impossible fail");}
}

void SGEXTN::InternalTest::UtilitiesTest::testIdentifier(){
    if(SGEXTN::Utilities::Identifier::nullIdentifier().private_data != 0u){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::Identifier - null identifier generation fail");}
    SGEXTN::Utilities::Identifier a;
    a.private_data = 1u;
    SGEXTN::Utilities::Identifier b;
    b.private_data = 0u;
    if(a == b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::Identifier - equality check fail");}
    if(SGEXTN::Utilities::Identifier::nullIdentifier() != b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::Identifier - inequality check fail");}
    a.private_data = 726726u;
    if(a.getStringForPrinting() != "000b16c6"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::Identifier - print string fail");}
    if(b.debugPrint() != "00000000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::Identifier - debug log fail");}
}

void SGEXTN::InternalTest::UtilitiesTest::testIdentifierRegistry(){
    SGEXTN::Utilities::IdentifierRegistry registry;
    bool isValid = false;
    SGEXTN::Utilities::Identifier id = registry.parseAndRegisterIdentifier(1u, &isValid);
    if(isValid == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry parse valid fail");}
    id = registry.parseAndRegisterIdentifier(0u, &isValid);
    if(isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry parse zero fail");}
    isValid = true;
    id = registry.parseAndRegisterIdentifier(1u, &isValid);
    if(isValid == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry parse invalid fail");}
    if(registry.contains(id) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry contains check existing identifier fail");}
    if(registry.contains(SGEXTN::Utilities::Identifier::nullIdentifier()) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry contains check null identifier fail");}
    id.private_data = 2u;
    if(registry.contains(id) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry contains check nonexistent identifier fail");}
    if(registry.unregister(id) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry unregister nonexistent identifier fail");}
    if(registry.unregister(SGEXTN::Utilities::Identifier::nullIdentifier()) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry unregister null identifier fail");}
    id.private_data = 1u;
    if(registry.unregister(id) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry unregister existing identifier fail");}
    if(registry.contains(id) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::IdentifierRegistry contains unregistered identifier fail");}
    SGEXTN::Containers::Array<SGEXTN::Utilities::Identifier> ids(1000);
    for(int i=0; i<1000; i++){
        ids.at(i) = registry.generateAndRegisterIdentifier();
    }
    if(registry.length() != 1000){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::Identifier check length fail");}
}

void SGEXTN::InternalTest::UtilitiesTest::testDateTime(){
    if(SGEXTN::Utilities::DateTime() != SGEXTN::Utilities::DateTime(0, 8, 9, 10, 30, 0)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime default constructor fail");}
    SGEXTN::Utilities::DateTime zero;
    const SGEXTN::Utilities::DateTime a;
    const SGEXTN::Utilities::DateTime b(21, 1, 1, 0, 0, 0);
    if(a == b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime equality check fail");}
    if(a != SGEXTN::Utilities::DateTime(0, 8, 9, 10, 30, 0)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime inequality check fail");}
    if(b < a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime less than operator fail");}
    if(a > b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime more than operator fail");}
    if(b <= a){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime less than equal to operator fail");}
    if(a >= b){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime more than equal to operator fail");}
    if(a.debugPrint() != "SG00-08-09 10:30:00"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime debug log print fail");}
    if(a != SGEXTN::Utilities::DateTime::beginningOfTime()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime beginning of time fail");}
    if(SGEXTN::Utilities::DateTime::convertToGlobalYear(0) != 1965){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime standard to global year fail");}
    if(SGEXTN::Utilities::DateTime(60, 6, 15, 0, 0, 0).isNationalDayPeriod() == true || SGEXTN::Utilities::DateTime(60, 7, 15, 0, 0, 0).isNationalDayPeriod() == false || SGEXTN::Utilities::DateTime(60, 8, 15, 0, 0, 0).isNationalDayPeriod() == false || SGEXTN::Utilities::DateTime(60, 9, 15, 0, 0, 0).isNationalDayPeriod() == false || SGEXTN::Utilities::DateTime(60, 10, 15, 0, 0, 0).isNationalDayPeriod() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime National Day period check fail");}
    if(SGEXTN::Utilities::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::NationalDay) == true || SGEXTN::Utilities::DateTime(60, 8, 9, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::NationalDay) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime significant day check National Day fail");}
    if(SGEXTN::Utilities::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::DayBeforeNationalDay) == true || SGEXTN::Utilities::DateTime(60, 8, 8, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::DayBeforeNationalDay) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime significant day check day before National Day fail");}
    if(SGEXTN::Utilities::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::DayAfterNationalDay) == true || SGEXTN::Utilities::DateTime(60, 8, 10, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::DayAfterNationalDay) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime significant day check day after National Day fail");}
    if(SGEXTN::Utilities::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::TotalDefenceDay) == true || SGEXTN::Utilities::DateTime(60, 2, 15, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::TotalDefenceDay) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime significant day check Total Defence Day fail");}
    if(SGEXTN::Utilities::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::RacialHarmonyDay) == true || SGEXTN::Utilities::DateTime(60, 7, 21, 0, 0, 0).isSignificantDate(SGEXTN::Utilities::SignificantDates::RacialHarmonyDay) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime significant day check Racial Harmony Day fail");}
    zero = SGEXTN::Utilities::DateTime::beginningOfTime();
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::Display, false, true) != "SG00-08-09 10:30:00"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string display format standard year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::Display, false, false) != "SG00-08-09"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string display format standard year fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::Display, true, true) != "1965-08-09 10:30:00"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string display format global year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::Display, true, false) != "1965-08-09"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string display format global year fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::FileName, false, true) != "000809103000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string file name format standard year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::FileName, false, false) != "000809"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string file name format standard year fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::FileName, true, true) != "19650809103000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string file name format global year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::FileName, true, false) != "19650809"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string file name format global year fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::ShortestReadable, false, true) != "SG00 0809 103000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string shortest readable format standard year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::ShortestReadable, false, false) != "SG00 0809"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string shortest readable format standard year fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::ShortestReadable, true, true) != "19650809 103000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string shortest readable format global year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Utilities::TimeFormat::ShortestReadable, true, false) != "19650809"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string shortest readable format global year fail");}
    if(zero.getDisplayString("%\\SG%2year%\\ %2month%2day%\\ %2hour%2minute%2second") != "SG00 0809 103000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::DateTime display string custom format fail");}
}
