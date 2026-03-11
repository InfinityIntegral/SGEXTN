#include <SGEXTN_Structs_ContrastUtilities.h>
#include <SGEXTN_Structs_RgbaColour.h>
#include <SGEXTN_Math_FloatMath.h>

float SGEXTN::Structs::ContrastUtilities::getContrast(SGEXTN::Structs::RgbaColour fg, SGEXTN::Structs::RgbaColour bg){
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
