/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#pragma once

namespace SGEXTN {
namespace CoreText {
class String;
}

namespace Utilities {
class RgbaColour;

class BuildLah_SGEXTN_Utilities HslaColour {
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
    [[nodiscard]] float getHue() const;
    [[nodiscard]] float getSaturation() const;
    [[nodiscard]] float getLightness() const;
    [[nodiscard]] float getTransparency() const;
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
