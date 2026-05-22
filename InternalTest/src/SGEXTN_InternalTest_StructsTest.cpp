#include <private_api/SGEXTN_InternalTest_StructsTest.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Structs_RgbaColour.h>
#include <SGEXTN_Structs_HslaColour.h>
#include <SGEXTN_Structs_ContrastUtilities.h>
#include <SGEXTN_Structs_Identifier.h>
#include <SGEXTN_Structs_IdentifierRegistry.h>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QTimeZone>
#include <SGEXTN_Structs_DateTime.h>
#include <SGEXTN_ApplicationBase_OldString.h>

namespace {
bool isCloseEnough(float a, float b){
    return ((a > b - 0.001f) && (a < b + 0.001f));
}

bool isCloseEnoughWCAG3(float a, float b){
    return ((a > b - 0.1f) && (a < b + 0.1f));
}
}

void SGEXTN::InternalTest::StructsTest::testAll(){
    SGEXTN::InternalTest::StructsTest::testRgbaColour();
    SGEXTN::InternalTest::StructsTest::testHslaColour();
    SGEXTN::InternalTest::StructsTest::testContrastUtilities();
    SGEXTN::InternalTest::StructsTest::testIdentifier();
    SGEXTN::InternalTest::StructsTest::testIdentifierRegistry();
    SGEXTN::InternalTest::StructsTest::testDateTime();
}

void SGEXTN::InternalTest::StructsTest::testRgbaColour(){
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
    col.setBlue(128);
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    col.gammaCorrectBegin(r, g, b);
    if(isCloseEnough(r, 1.0f) == false || isCloseEnough(g, 0.0f) == false || isCloseEnough(b, 0.21586f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour - gamma correct begin fail");}
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

void SGEXTN::InternalTest::StructsTest::testHslaColour(){
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

void SGEXTN::InternalTest::StructsTest::testContrastUtilities(){
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 255, 255), SGEXTN::Structs::RgbaColour(0, 0, 0)), 106.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 1 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(0, 0, 0), SGEXTN::Structs::RgbaColour(0, 0, 0)), 0.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 2 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 255, 255), SGEXTN::Structs::RgbaColour(118, 118, 118)), 71.6f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 3 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 100, 0), SGEXTN::Structs::RgbaColour(20, 20, 20)), 47.9f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 4 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(123, 131, 222), SGEXTN::Structs::RgbaColour(34, 45, 67)), 36.8f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 5 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(23, 162, 184), SGEXTN::Structs::RgbaColour(255, 255, 255)), -62.1f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 6 fail");}
    if(isCloseEnoughWCAG3(SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour(255, 255, 255), SGEXTN::Structs::RgbaColour(183, 21, 64)), 80.6f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - WCAG3 test 7 fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(0.1f, false, false), 200.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast too small text fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(1.0f, false, false), 60.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(2.0f, false, true), 200.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast too big body text fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(0.7f, false, true), 80.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast body text fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(1.0f, false, true), 75.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast body text +15 fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(1.0f, true, false), 48.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast bold text fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(2.0f, true, true), 200.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast too big body text fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(0.5f, true, true), 80.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast body text fail");}
    if(isCloseEnough(SGEXTN::Structs::ContrastUtilities::safeContrast(1.0f, true, true), 63.0f) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - safe contrast body text +15 fail");}
    bool isPossible = false;
    if(SGEXTN::Structs::ContrastUtilities::getForegroundLightMode(SGEXTN::Structs::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(171, 0, 135) || isPossible == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get foreground light possible fail");}
    if(SGEXTN::Structs::ContrastUtilities::getForegroundLightMode(SGEXTN::Structs::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(0, 0, 0) || isPossible == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get foreground light impossible fail");}
    if(SGEXTN::Structs::ContrastUtilities::getForegroundDarkMode(SGEXTN::Structs::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(255, 158, 234) || isPossible == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get foreground dark possible fail");}
    if(SGEXTN::Structs::ContrastUtilities::getForegroundDarkMode(SGEXTN::Structs::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(255, 255, 255) || isPossible == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get foreground dark impossible fail");}
    if(SGEXTN::Structs::ContrastUtilities::getBackgroundLightMode(SGEXTN::Structs::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(255, 160, 234) || isPossible == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get background light possible fail");}
    if(SGEXTN::Structs::ContrastUtilities::getBackgroundLightMode(SGEXTN::Structs::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(255, 255, 255) || isPossible == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get background light impossible fail");}
    if(SGEXTN::Structs::ContrastUtilities::getBackgroundDarkMode(SGEXTN::Structs::RgbaColour(255, 204, 244), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(185, 0, 145) || isPossible == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get background dark possible fail");}
    if(SGEXTN::Structs::ContrastUtilities::getBackgroundDarkMode(SGEXTN::Structs::RgbaColour(102, 0, 80), 60.0f, &isPossible) != SGEXTN::Structs::RgbaColour(0, 0, 0) || isPossible == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities - get background dark impossible fail");}
}

void SGEXTN::InternalTest::StructsTest::testIdentifier(){
    if(SGEXTN::Structs::Identifier::nullIdentifier().private_data != 0u){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::Identifier - null identifier generation fail");}
    SGEXTN::Structs::Identifier a;
    a.private_data = 1u;
    SGEXTN::Structs::Identifier b;
    b.private_data = 0u;
    if(a == b){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::Identifier - equality check fail");}
    if(SGEXTN::Structs::Identifier::nullIdentifier() != b){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::Identifier - inequality check fail");}
    a.private_data = 726726u;
    if(a.getStringForPrinting() != "000b16c6"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::Identifier - print string fail");}
    if(b.debugLog() != "00000000"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::Identifier - debug log fail");}
}

void SGEXTN::InternalTest::StructsTest::testIdentifierRegistry(){
    SGEXTN::Structs::IdentifierRegistry registry;
    bool isValid = false;
    SGEXTN::Structs::Identifier id = registry.parseAndRegisterIdentifier(1u, &isValid);
    if(isValid == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry parse valid fail");}
    id = registry.parseAndRegisterIdentifier(0u, &isValid);
    if(isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry parse zero fail");}
    isValid = true;
    id = registry.parseAndRegisterIdentifier(1u, &isValid);
    if(isValid == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry parse invalid fail");}
    if(registry.contains(id) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry contains check existing identifier fail");}
    if(registry.contains(SGEXTN::Structs::Identifier::nullIdentifier()) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry contains check null identifier fail");}
    id.private_data = 2u;
    if(registry.contains(id) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry contains check nonexistent identifier fail");}
    if(registry.unregister(id) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry unregister nonexistent identifier fail");}
    if(registry.unregister(SGEXTN::Structs::Identifier::nullIdentifier()) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry unregister null identifier fail");}
    id.private_data = 1u;
    if(registry.unregister(id) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry unregister existing identifier fail");}
    if(registry.contains(id) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry contains unregistered identifier fail");}
    if(registry.generateAndRegisterIdentifier() == SGEXTN::Structs::Identifier::nullIdentifier()){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::IdentifierRegistry identifier generation fail");}
}

void SGEXTN::InternalTest::StructsTest::testDateTime(){
    if(SGEXTN::Structs::DateTime() != SGEXTN::Structs::DateTime(0, 8, 9, 10, 30, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime default constructor fail");}
    SGEXTN::Structs::DateTime zero;
    const SGEXTN::Structs::DateTime a;
    const SGEXTN::Structs::DateTime b(21, 1, 1, 0, 0, 0);
    if(a == b){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime equality check fail");}
    if(a != SGEXTN::Structs::DateTime(0, 8, 9, 10, 30, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime inequality check fail");}
    if(b < a){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime less than operator fail");}
    if(a > b){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime more than operator fail");}
    if(b <= a){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime less than equal to operator fail");}
    if(a >= b){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime more than equal to operator fail");}
    if(a.debugLog() != "SG00-08-09 10:30:00"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime debug log print fail");}
    if(a != SGEXTN::Structs::DateTime::beginningOfTime()){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime beginning of time fail");}
    for(int year=-100; year<100; year++){
        for(int month=1; month<=12; month++){
            for(int day=1; day<=31; day++){
                bool isLeapYear = false;
                if((year - 35) % 4 == 0 && (year - 35) % 100 != 0){isLeapYear = true;}
                if((year - 35) % 400 == 0){isLeapYear = true;}
                if(day > 28 && month == 2 && isLeapYear == false){continue;}
                if(day > 29 && month == 2 && isLeapYear == true){continue;}
                if(day == 31 && (month == 4 || month == 6 || month == 9 || month == 11)){continue;}
                const int hour = (year % 24 + 24) % 24;
                const int minute = ((year + month + day) % 60 + 60) % 60;
                const int second = ((year + month + day) % 60 + 60) % 60;
                const QDateTime qDateTime = QDateTime(QDate(year + 1965, month, day), QTime(hour, minute, second), QTimeZone::UTC);
                const long long expected = QDateTime(QDate(1965, 8, 9), QTime(10, 30, 0), QTimeZone::UTC).secsTo(qDateTime);
                SGEXTN::Structs::DateTime thisDateTime(year, month, day, hour, minute, second);
                if(expected != thisDateTime.private_data){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime components constructor fail");}
                if(thisDateTime.getPart(SGEXTN::Structs::TimeUnit::Year) != year){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get year fail");}
                if(thisDateTime.getPart(SGEXTN::Structs::TimeUnit::Month) != month){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get month fail");}
                if(thisDateTime.getPart(SGEXTN::Structs::TimeUnit::Day) != day){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get day fail");}
                if(thisDateTime.getPart(SGEXTN::Structs::TimeUnit::Hour) != hour){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get hour fail");}
                if(thisDateTime.getPart(SGEXTN::Structs::TimeUnit::Minute) != minute){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get minute fail");}
                if(thisDateTime.getPart(SGEXTN::Structs::TimeUnit::Second) != second){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get second fail");}
                const SGEXTN::Structs::DateTime originalDateTime = thisDateTime;
                thisDateTime.setPart(SGEXTN::Structs::TimeUnit::Year, 0);
                if(thisDateTime != SGEXTN::Structs::DateTime(0, month, day, hour, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime set year fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Structs::TimeUnit::Month, 8);
                if(thisDateTime != SGEXTN::Structs::DateTime(year, 8, day, hour, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime set month fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Structs::TimeUnit::Day, 9);
                if(thisDateTime != SGEXTN::Structs::DateTime(year, month, 9, hour, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime set day fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Structs::TimeUnit::Hour, 10);
                if(thisDateTime != SGEXTN::Structs::DateTime(year, month, day, 10, minute, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime set hour fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Structs::TimeUnit::Minute, 30);
                if(thisDateTime != SGEXTN::Structs::DateTime(year, month, day, hour, 30, second)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime set minute fail");}
                thisDateTime = originalDateTime;
                thisDateTime.setPart(SGEXTN::Structs::TimeUnit::Second, 0);
                if(thisDateTime != SGEXTN::Structs::DateTime(year, month, day, hour, minute, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime set second fail");}
                thisDateTime = originalDateTime;
                if(thisDateTime.getDayOfWeek() != qDateTime.date().dayOfWeek()){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get day of week fail");}
                if(thisDateTime.getDayOfYear() != qDateTime.date().dayOfYear()){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime get day of year fail");}
                if(thisDateTime.countDaysInMonth() != qDateTime.date().daysInMonth()){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime count days in month fail");}
                if(thisDateTime.countDaysInYear() != qDateTime.date().daysInYear()){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime count days in year fail");}
                if(thisDateTime.getStartOfDay().private_data != QDateTime(QDate(1965, 8, 9), QTime(10, 30, 0), QTimeZone::UTC).secsTo(qDateTime.date().startOfDay(QTimeZone::UTC))){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime start of day fail");}
                if(thisDateTime.getEndOfDay().private_data != QDateTime(QDate(1965, 8, 9), QTime(10, 30, 0), QTimeZone::UTC).secsTo(qDateTime.date().startOfDay(QTimeZone::UTC)) + 86400ll){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime end of day fail");}
                if(thisDateTime.getWeekOfYear() != qDateTime.date().weekNumber()){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime week count fail");}
                const int diffYear = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Structs::DateTime::beginningOfTime(), SGEXTN::Structs::TimeUnit::Year);
                const int diffMonth = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Structs::DateTime::beginningOfTime(), SGEXTN::Structs::TimeUnit::Month);
                if(diffMonth < 0 || diffMonth > 11){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime time after display part month fail");}
                const int diffDay = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Structs::DateTime::beginningOfTime(), SGEXTN::Structs::TimeUnit::Day);
                if(diffDay < 0 || diffDay > 30){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime time after display part day fail");}
                const int diffHour = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Structs::DateTime::beginningOfTime(), SGEXTN::Structs::TimeUnit::Hour);
                if(diffHour < 0 || diffHour > 23){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime time after display part hour fail");}
                const int diffMinute = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Structs::DateTime::beginningOfTime(), SGEXTN::Structs::TimeUnit::Minute);
                if(diffMinute < 0 || diffMinute > 59){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime time after display part minute fail");}
                const int diffSecond = thisDateTime.getTimeAfterDisplayPart(SGEXTN::Structs::DateTime::beginningOfTime(), SGEXTN::Structs::TimeUnit::Second);
                if(diffSecond < 0 || diffSecond > 59){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime time after display part second fail");}
                zero = SGEXTN::Structs::DateTime::beginningOfTime();
                zero.advanceTime(diffYear, SGEXTN::Structs::TimeUnit::Year);
                zero.advanceTime(diffMonth, SGEXTN::Structs::TimeUnit::Month);
                zero.advanceTime(diffDay, SGEXTN::Structs::TimeUnit::Day);
                zero.advanceTime(diffHour, SGEXTN::Structs::TimeUnit::Hour);
                zero.advanceTime(diffMinute, SGEXTN::Structs::TimeUnit::Minute);
                zero.advanceTime(diffSecond, SGEXTN::Structs::TimeUnit::Second);
                if(zero != thisDateTime){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime advance time fail");}
            }
        }
    }
    if(SGEXTN::Structs::DateTime::convertToGlobalYear(0) != 1965){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime standard to global year fail");}
    if(SGEXTN::Structs::DateTime(60, 6, 15, 0, 0, 0).isNationalDayPeriod() == true || SGEXTN::Structs::DateTime(60, 7, 15, 0, 0, 0).isNationalDayPeriod() == false || SGEXTN::Structs::DateTime(60, 8, 15, 0, 0, 0).isNationalDayPeriod() == false || SGEXTN::Structs::DateTime(60, 9, 15, 0, 0, 0).isNationalDayPeriod() == false || SGEXTN::Structs::DateTime(60, 10, 15, 0, 0, 0).isNationalDayPeriod() == true){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime National Day period check fail");}
    if(SGEXTN::Structs::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::NationalDay) == true || SGEXTN::Structs::DateTime(60, 8, 9, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::NationalDay) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime significant day check National Day fail");}
    if(SGEXTN::Structs::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::DayBeforeNationalDay) == true || SGEXTN::Structs::DateTime(60, 8, 8, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::DayBeforeNationalDay) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime significant day check day before National Day fail");}
    if(SGEXTN::Structs::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::DayAfterNationalDay) == true || SGEXTN::Structs::DateTime(60, 8, 10, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::DayAfterNationalDay) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime significant day check day after National Day fail");}
    if(SGEXTN::Structs::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::TotalDefenceDay) == true || SGEXTN::Structs::DateTime(60, 2, 15, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::TotalDefenceDay) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime significant day check Total Defence Day fail");}
    if(SGEXTN::Structs::DateTime(60, 1, 1, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::RacialHarmonyDay) == true || SGEXTN::Structs::DateTime(60, 7, 21, 0, 0, 0).isSignificantDate(SGEXTN::Structs::SignificantDates::RacialHarmonyDay) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime significant day check Racial Harmony Day fail");}
    zero = SGEXTN::Structs::DateTime::beginningOfTime();
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::Display, false, true) != "SG00-08-09 10:30:00"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string display format standard year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::Display, false, false) != "SG00-08-09"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string display format standard year fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::Display, true, true) != "1965-08-09 10:30:00"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string display format global year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::Display, true, false) != "1965-08-09"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string display format global year fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::FileName, false, true) != "000809103000"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string file name format standard year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::FileName, false, false) != "000809"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string file name format standard year fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::FileName, true, true) != "19650809103000"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string file name format global year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::FileName, true, false) != "19650809"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string file name format global year fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::ShortestReadable, false, true) != "SG00 0809 103000"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string shortest readable format standard year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::ShortestReadable, false, false) != "SG00 0809"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string shortest readable format standard year fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::ShortestReadable, true, true) != "19650809 103000"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string shortest readable format global year correct to second fail");}
    if(zero.getDisplayString(SGEXTN::Structs::TimeFormat::ShortestReadable, true, false) != "19650809"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string shortest readable format global year fail");}
    if(zero.getDisplayString("%\\SG%2year%\\ %2month%2day%\\ %2hour%2minute%2second") != "SG00 0809 103000"){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::DateTime display string custom format fail");}
}
