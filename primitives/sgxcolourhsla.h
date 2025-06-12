#ifndef SGXCOLOURHSLA_H
#define SGXCOLOURHSLA_H

#include "sgxcolourrgba.h"

class SGXColourHSLA
{
public:
    float h; // hue as float between 0 to 360
    float s; // saturation as float between 0 to 100
    float l; // saturation as float between 0 to 100
    float a; // transparency as float between 0 to 100
    SGXColourHSLA(SGXColourRGBA x); // construct HSLA colour from RGBA colour for colour-based computation
    SGXColourHSLA(float h, float s, float l, float a); // construct HSLA colour from its components, where h is a float between 0 to 360 inclusive, s, l, a are floats between 0 to 100 inclusive
    [[nodiscard]] bool operator==(SGXColourHSLA x) const; // equality comparator by comparing colour not struct instance memory location
    [[nodiscard]] bool operator!=(SGXColourHSLA x) const; // inequality comparator by comparing colour not struct instance memory location
    /*
methods list:
- change saturate
- change lightness
- invert hue
- invert saturation
- invert lightness
- linear transform saturation
- linear transform lightness
- offset hue
     */
};

#endif // SGXCOLOURHSLA_H
