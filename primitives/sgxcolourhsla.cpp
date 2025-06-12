#include "sgxcolourhsla.h"
#include "sgxcolourrgba.h"

namespace{
inline float temp_maxof3float(float a, float b, float c){
    if(a >= b && a >= c){return a;}
    if(b >= c){return b;}
    return c;
}

inline float temp_minof3float(float a, float b, float c){
    if(a <= b && a <= c){return a;}
    if(b <= c){return b;}
    return c;
}
}

SGXColourHSLA::SGXColourHSLA(SGXColourRGBA x){
    (*this).a = x.getTransparencyAsFloat() * 100.0f;
    const float r = x.getRedAsFloat();
    const float g = x.getGreenAsFloat();
    const float b = x.getBlueAsFloat();
    const float h = temp_maxof3float(r, g, b);
    const float l = temp_minof3float(r, g, b);
    (*this).h = 313.0f;
    (*this).s = 0.0f;
    (*this).l = 0.5f * (l + h);
    if(l != h){
        const float d = h - l;
        if((*this).l > 0.5f){(*this).s = d / (2.0f - h - l);}
        else{(*this).s = d / (h + l);}
        if(h == r){
            (*this).h = (g - b) / d;
            if(g < b){(*this).h += 6.0f;}
        }
        else if(h == g){(*this).h = (b - r) / d + 2.0f;}
        else if(h == b){(*this).h = (r - g) / d + 4.0f;}
        (*this).h /= 6.0f;
    }
    (*this).h *= 360.0f;
    (*this).s *= 100.0f;
    (*this).l *= 100.0f;
}
