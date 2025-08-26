#ifndef SGXCOLOURHSLA_H
#define SGXCOLOURHSLA_H

#include "sgxcolourrgba.h"
#include <QDebug>
#include <bit>

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
    return (seed ^ std::bit_cast<unsigned int>(x.h) ^ std::bit_cast<unsigned int>(x.s) ^ std::bit_cast<unsigned int>(x.l) ^ std::bit_cast<unsigned int>(x.a));
}

inline QDebug operator<<(QDebug s, SGXColourHSLA x){
    s << ("HSLA colour with h = " + QString::number(x.h) + ", s = " + QString::number(x.s) + ", l = " + QString::number(x.l) + ", a = " + QString::number(x.a));
    return s;
}

#endif // SGXCOLOURHSLA_H
