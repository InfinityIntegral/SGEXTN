#ifndef SGXCOLOURHSLA_H
#define SGXCOLOURHSLA_H

#include "sgxcolourrgba.h"

class SGXColourHSLA
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
    void setHue(float h);
    void setSaturation(float s);
    void setLightness(float l);
    void setTransparency(float a);
    void invertHue();
    void invertSaturation();
    void invertLightness();
    void linearTransformSaturation(float m, float c);
    void linearTransformLightness(float m, float c);
    void linearTransformTransparency(float m, float c);
    void offsetHue(float c);
    [[nodiscard]] SGXColourRGBA toRGBA() const;
};

inline unsigned int qHash(SGXColourHSLA x, unsigned int seed = 0){
    return (seed ^ static_cast<unsigned int>(x.h) ^ static_cast<unsigned int>(x.s) ^ static_cast<unsigned int>(x.l) ^ static_cast<unsigned int>(x.a));
}

#endif // SGXCOLOURHSLA_H
