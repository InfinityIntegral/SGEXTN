#ifndef SGXCOLOURHSLA_H
#define SGXCOLOURHSLA_H

#include <SGXColourRGBA.h>

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXColourHSLA
{
public:
    float h;
    float s;
    float l;
    float a;
    SGXColourHSLA() = default;
    SGXColourHSLA(SGXColourRGBA x);
    SGXColourHSLA(float h, float s, float l, float a);
    [[nodiscard]] bool operator==(SGXColourHSLA x) const;
    [[nodiscard]] bool operator!=(SGXColourHSLA x) const;
    [[nodiscard]] bool operator<(SGXColourHSLA x) const;
    [[nodiscard]] bool operator>(SGXColourHSLA x) const;
    [[nodiscard]] int hash() const;
    SGXColourHSLA& setHue(float h);
    SGXColourHSLA& setSaturation(float s);
    SGXColourHSLA& setLightness(float l);
    SGXColourHSLA& setTransparency(float a);
    SGXColourHSLA& invertHue();
    SGXColourHSLA& invertSaturation();
    SGXColourHSLA& invertLightness();
    SGXColourHSLA& linearTransformSaturation(float m, float c);
    SGXColourHSLA& linearTransformLightness(float m, float c);
    SGXColourHSLA& linearTransformTransparency(float m, float c);
    SGXColourHSLA& offsetHue(float c);
    [[nodiscard]] SGXColourRGBA toRGBA() const;
};

#endif // SGXCOLOURHSLA_H
