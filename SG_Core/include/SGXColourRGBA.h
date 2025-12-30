#ifndef SGXCOLOURRGBA_H
#define SGXCOLOURRGBA_H

#include <SGXString.h>

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXColourRGBA
{
public:
    unsigned int x;
    SGXColourRGBA() = default;
    SGXColourRGBA(unsigned int x0);
    SGXColourRGBA(int r, int g, int b, int a);
    SGXColourRGBA(int r, int g, int b);
    SGXColourRGBA(float r, float g, float b, float a);
    SGXColourRGBA(float r, float g, float b);
    [[nodiscard]] int getRed() const;
    [[nodiscard]] int getGreen() const;
    [[nodiscard]] int getBlue() const;
    [[nodiscard]] int getTransparency() const;
    [[nodiscard]] float getRedAsFloat() const;
    [[nodiscard]] float getGreenAsFloat() const;
    [[nodiscard]] float getBlueAsFloat() const;
    [[nodiscard]] float getTransparencyAsFloat() const;
    SGXColourRGBA& setRed(int r);
    SGXColourRGBA& setGreen(int g);
    SGXColourRGBA& setBlue(int b);
    SGXColourRGBA& setTransparency(int a);
    SGXColourRGBA& setRedUsingFloat(float r);
    SGXColourRGBA& setGreenUsingFloat(float g);
    SGXColourRGBA& setBlueUsingFloat(float b);
    SGXColourRGBA& setTransparencyUsingFloat(float a);
    [[nodiscard]] SGXString getStringForPrintingRGBHTML() const;
    [[nodiscard]] SGXString getStringForPrintingRGBAHTML() const;
    [[nodiscard]] SGXString getStringForPrintingRGBHex() const;
    [[nodiscard]] SGXString getStringForPrintingRGBAHex() const;
    [[nodiscard]] SGXString getStringForPrintingRGBFloatHTML() const;
    [[nodiscard]] SGXString getStringForPrintingRGBAFloatHTML() const;
    [[nodiscard]] bool operator==(SGXColourRGBA x) const;
    [[nodiscard]] bool operator!=(SGXColourRGBA x) const;
    [[nodiscard]] bool operator<(SGXColourRGBA x) const;
    [[nodiscard]] bool operator>(SGXColourRGBA x) const;
    [[nodiscard]] int hash() const;
    SGXColourRGBA& linearTransformRed(float m, float c);
    SGXColourRGBA& linearTransformGreen(float m, float c);
    SGXColourRGBA& linearTransformBlue(float m, float c);
    SGXColourRGBA& linearTransformTransparency(float m, float c);
    void gammaCorrectBegin(float& r, float& g, float& b) const;
    void gammaCorrectEnd(float r, float g, float b);
    SGXColourRGBA& linearTransformRedWithGamma(float m, float c);
    SGXColourRGBA& linearTransformGreenWithGamma(float m, float c);
    SGXColourRGBA& linearTransformBlueWithGamma(float m, float c);
    SGXColourRGBA& applyTint(SGXColourRGBA x);
    SGXColourRGBA& applyTintSeparateTransparency(SGXColourRGBA x, int a);
    SGXColourRGBA& applyTintSeparateTransparencyUsingFloat(SGXColourRGBA x, float a);
    SGXColourRGBA& applyTintNoGammaCorrection(SGXColourRGBA x);
    SGXColourRGBA& applyTintNoGammaCorrectionSeparateTransparency(SGXColourRGBA x, int a);
    SGXColourRGBA& applyTintNoGammaCorrectionSeparateTransparencyUsingFloat(SGXColourRGBA x, float a);
    [[nodiscard]] SGXColourRGBA linearInterpolate(SGXColourRGBA x, float f) const;
    [[nodiscard]] SGXColourRGBA linearInterpolateGammaCorrection(SGXColourRGBA x, float f) const;
    SGXColourRGBA& toComplementColour();
};

#endif // SGXCOLOURRGBA_H
