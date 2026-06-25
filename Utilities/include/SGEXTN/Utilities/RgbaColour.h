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
class BuildLah_SGEXTN_Utilities RgbaColour {
public:
    unsigned int private_data;
    RgbaColour();
    RgbaColour(unsigned int data);
    RgbaColour(int r, int g, int b, int a);
    RgbaColour(int r, int g, int b);
    RgbaColour(float r, float g, float b, float a);
    RgbaColour(float r, float g, float b);
    [[nodiscard]] int getRed() const;
    [[nodiscard]] int getGreen() const;
    [[nodiscard]] int getBlue() const;
    [[nodiscard]] int getTransparency() const;
    [[nodiscard]] float getRedFloat() const;
    [[nodiscard]] float getGreenFloat() const;
    [[nodiscard]] float getBlueFloat() const;
    [[nodiscard]] float getTransparencyFloat() const;
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    void setTransparency(int a);
    void setRedFloat(float r);
    void setGreenFloat(float g);
    void setBlueFloat(float b);
    void setTransparencyFloat(float a);
    [[nodiscard]] SGEXTN::CoreText::String rgbHtmlString() const;
    [[nodiscard]] SGEXTN::CoreText::String rgbaHtmlString() const;
    [[nodiscard]] SGEXTN::CoreText::String rgbHexString() const;
    [[nodiscard]] SGEXTN::CoreText::String rgbaHexString() const;
    [[nodiscard]] SGEXTN::CoreText::String rgbFloatHtmlString() const;
    [[nodiscard]] SGEXTN::CoreText::String rgbaFloatHtmlString() const;
    [[nodiscard]] bool operator==(RgbaColour x) const;
    [[nodiscard]] bool operator!=(RgbaColour x) const;
    [[nodiscard]] bool operator<(RgbaColour x) const;
    [[nodiscard]] bool operator>(RgbaColour x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGEXTN::CoreText::String debugPrint() const;
    void gammaCorrectBegin(float& r, float& g, float& b) const;
    void gammaCorrectEnd(float r, float g, float b);
    [[nodiscard]] RgbaColour linearTransformRed(float m, float c, bool gammaCorrect) const;
    [[nodiscard]] RgbaColour linearTransformGreen(float m, float c, bool gammaCorrect) const;
    [[nodiscard]] RgbaColour linearTransformBlue(float m, float c, bool gammaCorrect) const;
    [[nodiscard]] RgbaColour linearTransformTransparency(float m, float c) const;
    [[nodiscard]] RgbaColour applyTint(RgbaColour x, bool gammaCorrect) const;
    [[nodiscard]] RgbaColour applyTintSeparateTransparency(RgbaColour x, float transparency, bool gammaCorrect) const;
    [[nodiscard]] RgbaColour interpolate(RgbaColour other, float thisStrength, bool gammaCorrect) const;
    [[nodiscard]] RgbaColour complement(bool gammaCorrect) const;
};
}
}
