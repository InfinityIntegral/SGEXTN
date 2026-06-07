#pragma once

namespace SGEXTN {
namespace ApplicationBase {
class String;
}

namespace Structs {
class BUILDLAH_DLL_SGEXTN_Structs RgbaColour {
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
    [[nodiscard]] SGEXTN::ApplicationBase::String rgbHtmlString() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String rgbaHtmlString() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String rgbHexString() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String rgbaHexString() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String rgbFloatHtmlString() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String rgbaFloatHtmlString() const;
    [[nodiscard]] bool operator==(RgbaColour x) const;
    [[nodiscard]] bool operator!=(RgbaColour x) const;
    [[nodiscard]] bool operator<(RgbaColour x) const;
    [[nodiscard]] bool operator>(RgbaColour x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGEXTN::ApplicationBase::String debugLog() const;
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
