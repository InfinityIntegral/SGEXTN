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
    void setHue(float h); // set hue using float between 0 and 360 inclusive
    void setSaturation(float s); // set saturation using float between 0 and 100 inclusive
    void setLightness(float l); // set lightness using float between 0 and 100 inclusive
    void setTransparency(float a); // set transparency using float between 0 and 100 inclusive
    void invertHue(); // modify hue to obtain complementary hue
    void invertSaturation(); // modify saturation to obtain opposite saturation
    void invertLightness(); // modify lightness to obtain opposite lightness
    void linearTransformSaturation(float m, float c); // apply x -> mx + c transform to saturation
    void linearTransformLightness(float m, float c); // apply x -> mx + c transform to lightness
    void linearTransformTransparency(float m, float c); // apply x -> mx + c transform to transparency
    void offsetHue(float c); // apply offset of c to the hue, used to get nearby colours
};

#endif // SGXCOLOURHSLA_H
