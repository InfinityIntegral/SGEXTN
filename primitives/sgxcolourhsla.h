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
    /*
methods list:
- constructor from RGBA
- constructor from HSLA values
- equality comparator
- inequality comparator
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
