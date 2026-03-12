#pragma once
#include <SGEXTN_Structs_RgbaColour.h>
#include <SGEXTN_ApplicationBase_String.h>

namespace SGEXTN {
namespace Structs {
class BUILDLAH_DLL_SGEXTN_Structs HslaColour {
public:
    float private_hue;
    float private_saturation;
    float private_lightness;
    float private_transparency;
    HslaColour() = default;
    HslaColour(SGEXTN::Structs::RgbaColour x);
    HslaColour(float h, float s, float l);
    HslaColour(float h, float s, float l, float a);
    [[nodiscard]] bool operator==(HslaColour x) const;
    [[nodiscard]] bool operator!=(HslaColour x) const;
    [[nodiscard]] bool operator<(HslaColour x) const;
    [[nodiscard]] bool operator>(HslaColour x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String debugLog() const;
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
    [[nodiscard]] SGEXTN::Structs::RgbaColour toRGBA() const;
};
}
}
