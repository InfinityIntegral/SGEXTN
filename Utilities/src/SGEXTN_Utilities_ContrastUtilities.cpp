#include <SGEXTN_Utilities_ContrastUtilities.h>
#include <SGEXTN_Utilities_RgbaColour.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_Utilities_HslaColour.h>
#include <SGEXTN_Math_FloatConstants.h>
#include <SGEXTN_Containers_ForceCrash.h>

float SGEXTN::Utilities::ContrastUtilities::getContrast(SGEXTN::Utilities::RgbaColour bg, SGEXTN::Utilities::RgbaColour fg){
    fg = bg.applyTint(fg, true);
    float bgLuminance = 0.2126729f * SGEXTN::Math::FloatMath<float>::powerOf(bg.getRedFloat(), 2.4f) + 0.7151522f * SGEXTN::Math::FloatMath<float>::powerOf(bg.getGreenFloat(), 2.4f) + 0.0721750f * SGEXTN::Math::FloatMath<float>::powerOf(bg.getBlueFloat(), 2.4f);
    float fgLuminance = 0.2126729f * SGEXTN::Math::FloatMath<float>::powerOf(fg.getRedFloat(), 2.4f) + 0.7151522f * SGEXTN::Math::FloatMath<float>::powerOf(fg.getGreenFloat(), 2.4f) + 0.0721750f * SGEXTN::Math::FloatMath<float>::powerOf(fg.getBlueFloat(), 2.4f);
    if(bgLuminance <= 0.022f){bgLuminance += SGEXTN::Math::FloatMath<float>::powerOf(0.022f - bgLuminance, SGEXTN::Math::FloatConstants<float>::squareRoot2());}
    if(fgLuminance <= 0.022f){fgLuminance += SGEXTN::Math::FloatMath<float>::powerOf(0.022f - fgLuminance, SGEXTN::Math::FloatConstants<float>::squareRoot2());}
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

float SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(SGEXTN::Utilities::RgbaColour bg, SGEXTN::Utilities::RgbaColour fg){
    return SGEXTN::Math::FloatMath<float>::absoluteValue(SGEXTN::Utilities::ContrastUtilities::getContrast(bg, fg));
}

float SGEXTN::Utilities::ContrastUtilities::safeContrast(float sizeUnit, bool bold, bool bodyText){
    if(sizeUnit < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities::safeContrast crashed because size unit of text cannot be negative");}
    const float fontSize = sizeUnit * 28.0f;
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

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::ContrastUtilities::getForegroundLightMode(RgbaColour bg, float targetContrast, bool* isPossible){
    if(targetContrast < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities::getForegroundLightMode crashed because target contrast cannot be negative, always pass absolute value of intended contrast");}
    const SGEXTN::Utilities::HslaColour referenceColour = SGEXTN::Utilities::HslaColour(bg);
    float low = 0.0f;
    float high = referenceColour.getLightness();
    SGEXTN::Utilities::HslaColour newColour = referenceColour;
    while(high - low > 0.001){
        const float m = 0.5f * (low + high);
        newColour.setLightness(m);
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(bg, newColour.toRGBA()) >= targetContrast){low = m;}
        else{high = m;}
    }
    newColour.setLightness(low);
    SGEXTN::Utilities::RgbaColour outputColour = newColour.toRGBA();
    if(isPossible != nullptr){
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(bg, outputColour) >= targetContrast){(*isPossible) = true;}
        else{(*isPossible) = false;}
    }
    return outputColour;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::ContrastUtilities::getForegroundDarkMode(RgbaColour bg, float targetContrast, bool* isPossible){
    if(targetContrast < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities::getForegroundDarkMode crashed because target contrast cannot be negative, always pass absolute value of intended contrast");}
    const SGEXTN::Utilities::HslaColour referenceColour = SGEXTN::Utilities::HslaColour(bg);
    float low = referenceColour.getLightness();
    float high = 100.0f;
    SGEXTN::Utilities::HslaColour newColour = referenceColour;
    while(high - low > 0.001){
        const float m = 0.5f * (low + high);
        newColour.setLightness(m);
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(bg, newColour.toRGBA()) >= targetContrast){high = m;}
        else{low = m;}
    }
    newColour.setLightness(high);
    SGEXTN::Utilities::RgbaColour outputColour = newColour.toRGBA();
    if(isPossible != nullptr){
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(bg, outputColour) >= targetContrast){(*isPossible) = true;}
        else{(*isPossible) = false;}
    }
    return outputColour;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::ContrastUtilities::getBackgroundLightMode(RgbaColour fg, float targetContrast, bool* isPossible){
    if(targetContrast < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities::getBackgroundLightMode crashed because target contrast cannot be negative, always pass absolute value of intended contrast");}
    const SGEXTN::Utilities::HslaColour referenceColour = SGEXTN::Utilities::HslaColour(fg);
    float low = referenceColour.getLightness();
    float high = 100.0f;
    SGEXTN::Utilities::HslaColour newColour = referenceColour;
    while(high - low > 0.001){
        const float m = 0.5f * (low + high);
        newColour.setLightness(m);
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(newColour.toRGBA(), fg) >= targetContrast){high = m;}
        else{low = m;}
    }
    newColour.setLightness(high);
    SGEXTN::Utilities::RgbaColour outputColour = newColour.toRGBA();
    if(isPossible != nullptr){
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(outputColour, fg) >= targetContrast){(*isPossible) = true;}
        else{(*isPossible) = false;}
    }
    return outputColour;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::ContrastUtilities::getBackgroundDarkMode(RgbaColour fg, float targetContrast, bool* isPossible){
    if(targetContrast < 0.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::ContrastUtilities::getBackgroundDarkMode crashed because target contrast cannot be negative, always pass absolute value of intended contrast");}
    const SGEXTN::Utilities::HslaColour referenceColour = SGEXTN::Utilities::HslaColour(fg);
    float low = 0.0f;
    float high = referenceColour.getLightness();
    SGEXTN::Utilities::HslaColour newColour = referenceColour;
    while(high - low > 0.001){
        const float m = 0.5f * (low + high);
        newColour.setLightness(m);
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(newColour.toRGBA(), fg) >= targetContrast){low = m;}
        else{high = m;}
    }
    newColour.setLightness(low);
    SGEXTN::Utilities::RgbaColour outputColour = newColour.toRGBA();
    if(isPossible != nullptr){
        if(SGEXTN::Utilities::ContrastUtilities::getAbsoluteContrast(outputColour, fg) >= targetContrast){(*isPossible) = true;}
        else{(*isPossible) = false;}
    }
    return outputColour;
}