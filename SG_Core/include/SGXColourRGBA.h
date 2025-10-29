#ifndef SGXCOLOURRGBA_H
#define SGXCOLOURRGBA_H

#include <SGXString.h>

class SGXColourRGBA
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
    void setRed(int r);
    void setGreen(int g);
    void setBlue(int b);
    void setTransparency(int a);
    void setRedUsingFloat(float r);
    void setGreenUsingFloat(float g);
    void setBlueUsingFloat(float b);
    void setTransparencyUsingFloat(float a);
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
    void linearTransformRed(float m, float c);
    void linearTransformGreen(float m, float c);
    void linearTransformBlue(float m, float c);
    void linearTransformTransparency(float m, float c);
    void gammaCorrectBegin(float& r, float& g, float& b) const;
    void gammaCorrectEnd(float r, float g, float b);
    void linearTransformRedWithGamma(float m, float c);
    void linearTransformGreenWithGamma(float m, float c);
    void linearTransformBlueWithGamma(float m, float c);
    void applyTint(SGXColourRGBA x);
    void applyTintSeparateTransparency(SGXColourRGBA x, int a);
    void applyTintSeparateTransparencyUsingFloat(SGXColourRGBA x, float a);
    void applyTintNoGammaCorrection(SGXColourRGBA x);
    void applyTintNoGammaCorrectionSeparateTransparency(SGXColourRGBA x, int a);
    void applyTintNoGammaCorrectionSeparateTransparencyUsingFloat(SGXColourRGBA x, float a);
    [[nodiscard]] SGXColourRGBA linearInterpolate(SGXColourRGBA x, float f) const;
    [[nodiscard]] SGXColourRGBA linearInterpolateGammaCorrection(SGXColourRGBA x, float f) const;
    void toComplementColour();
};

#endif // SGXCOLOURRGBA_H
