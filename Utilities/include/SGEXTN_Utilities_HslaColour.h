#pragma once

namespace SGEXTN {
namespace CoreText {
class String;
}

namespace Utilities {
class RgbaColour;

class BUILDLAH_DLL_SGEXTN_Utilities HslaColour {
public:
    float private_hue;
    float private_saturation;
    float private_lightness;
    float private_transparency;
    HslaColour();
    HslaColour(SGEXTN::Utilities::RgbaColour x);
    HslaColour(float h, float s, float l);
    HslaColour(float h, float s, float l, float a);
    [[nodiscard]] bool operator==(HslaColour x) const;
    [[nodiscard]] bool operator!=(HslaColour x) const;
    [[nodiscard]] bool operator<(HslaColour x) const;
    [[nodiscard]] bool operator>(HslaColour x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGEXTN::CoreText::String debugPrint() const;
    float getHue() const;
    float getSaturation() const;
    float getLightness() const;
    float getTransparency() const;
    void setHue(float h);
    void setSaturation(float s);
    void setLightness(float l);
    void setTransparency(float a);
    [[nodiscard]] HslaColour invertHue() const;
    [[nodiscard]] HslaColour invertSaturation() const;
    [[nodiscard]] HslaColour invertLightness() const;
    [[nodiscard]] HslaColour linearTransformSaturation(float m, float c) const;
    [[nodiscard]] HslaColour linearTransformLightness(float m, float c) const;
    [[nodiscard]] HslaColour linearTransformTransparency(float m, float c) const;
    [[nodiscard]] HslaColour offsetHue(float c) const;
    [[nodiscard]] SGEXTN::Utilities::RgbaColour toRGBA() const;
};
}
}
