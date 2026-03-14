#include <SGEXTN_Structs_ContrastUtilities.h>
#include <SGEXTN_Structs_RgbaColour.h>
#include <SGEXTN_Math_FloatMath.h>

float SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour bg, SGEXTN::Structs::RgbaColour fg){
    fg = bg.applyTint(fg, true);
    float bgLuminance = 0.2126729f * SGEXTN::Math::FloatMath<float>::powerOf(bg.getRedFloat(), 2.4f) + 0.7151522f * SGEXTN::Math::FloatMath<float>::powerOf(bg.getGreenFloat(), 2.4f) + 0.0721750f * SGEXTN::Math::FloatMath<float>::powerOf(bg.getBlueFloat(), 2.4f);
    float fgLuminance = 0.2126729f * SGEXTN::Math::FloatMath<float>::powerOf(fg.getRedFloat(), 2.4f) + 0.7151522f * SGEXTN::Math::FloatMath<float>::powerOf(fg.getGreenFloat(), 2.4f) + 0.0721750f * SGEXTN::Math::FloatMath<float>::powerOf(fg.getBlueFloat(), 2.4f);
    if(bgLuminance <= 0.022f){bgLuminance += SGEXTN::Math::FloatMath<float>::powerOf(0.022f - bgLuminance, 1.414f);}
    if(fgLuminance <= 0.022f){fgLuminance += SGEXTN::Math::FloatMath<float>::powerOf(0.022f - fgLuminance, 1.414f);}
    if(SGEXTN::Math::FloatMath<float>::absoluteValue(bgLuminance - fgLuminance) < 0.0005f){return 0.0f;}
    float rawContrast = 0.0f;
    float finalContrast = 0.0f;
    if(bgLuminance > fgLuminance){
        rawContrast = 1.14f * (SGEXTN::Math::FloatMath<float>::powerOf(bgLuminance, 0.56f) - SGEXTN::Math::FloatMath<float>::powerOf(fgLuminance, 0.57f));
        if(rawContrast >= 0.1f){finalContrast = rawContrast - 0.027f;}
    }
    else{
        rawContrast = 1.14f * (SGEXTN::Math::FloatMath<float>::powerOf(bgLuminance, 0.65f) - SGEXTN::Math::FloatMath<float>::powerOf(fgLuminance, 0.62f));
        if(rawContrast <= -0.1f){finalContrast = rawContrast + 0.027f;}
    }
    return (100.0f * finalContrast);
}

float SGEXTN::Structs::ContrastUtilities::safeContrast(float sizeUnit, bool bold, bool bodyText){
    if(sizeUnit < 0.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::ContrastUtilities::safeContrast crashed because size unit of text cannot be negative");}
    float fontSize = sizeUnit * 28.0f;
    float requiredContrast = 195.0f;
    if(bold == false){
        if(fontSize >= 96.0f){requiredContrast = 33.0f;}
        else if(fontSize >= 72.0f){requiredContrast = 35.0f;}
        else if(fontSize >= 60.0f){requiredContrast = 38.0f;}
        else if(fontSize >= 48.0f){requiredContrast = 40.0f;}
        else if(fontSize >= 42.0f){requiredContrast = 43.0f;}
        else if(fontSize >= 36.0f){requiredContrast = 45.0f;}
        else if(fontSize >= 32.0f){requiredContrast = 50.0f;}
        else if(fontSize >= 28.0f){requiredContrast = 55.0f;}
        else if(fontSize >= 24.0f){requiredContrast = 60.0f;}
        else if(fontSize >= 21.0f){requiredContrast = 70.0f;}
        else if(fontSize >= 18.0f){requiredContrast = 75.0f;}
        else if(fontSize >= 16.0f){requiredContrast = 90.0f;}
        else if(fontSize >= 15.0f){requiredContrast = 100.0f;}
        if(bodyText == true){
            if(fontSize >= 42.0f){requiredContrast = 195.0f;}
            if(requiredContrast < 70.0f){requiredContrast += 15.0f;}
        }
    }
    else{
        if(fontSize >= 60.0f){requiredContrast = 30.0f;}
        else if(fontSize >= 48.0f){requiredContrast = 33.0f;}
        else if(fontSize >= 42.0f){requiredContrast = 35.0f;}
        else if(fontSize >= 36.0f){requiredContrast = 38.0f;}
        else if(fontSize >= 32.0f){requiredContrast = 40.0f;}
        else if(fontSize >= 28.0f){requiredContrast = 43.0f;}
        else if(fontSize >= 24.0f){requiredContrast = 45.0f;}
        else if(fontSize >= 21.0f){requiredContrast = 50.0f;}
        else if(fontSize >= 18.0f){requiredContrast = 55.0f;}
        else if(fontSize >= 16.0f){requiredContrast = 60.0f;}
        else if(fontSize >= 15.0f){requiredContrast = 70.0f;}
        else if(fontSize >= 14.0f){requiredContrast = 75.0f;}
        if(bodyText == true){
            if(fontSize >= 42.0f){requiredContrast = 195.0f;}
            if(requiredContrast < 75.0f){requiredContrast += 15.0f;}
        }
    }
    requiredContrast += 5.0f;
    return requiredContrast;
}