#include "sgxcolourhsla.h"
#include "sgxcolourrgba.h"
#include <cmath>

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

inline void temp_limitto100(float& x){
    if(x < 0.0f){x = 0.0f;}
    else if(x > 100.0f){x = 100.0f;}
}

inline void temp_limitto360(float& x){
    x = std::fmod(x, 360.0f);
    if(x < 0.0f){x += 360.0f;}
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

SGXColourHSLA::SGXColourHSLA(float h, float s, float l, float a){
    temp_limitto360(h);
    temp_limitto100(s);
    temp_limitto100(l);
    temp_limitto100(a);
    (*this).h = h;
    (*this).s = s;
    (*this).l = l;
    (*this).a = a;
}

bool SGXColourHSLA::operator==(SGXColourHSLA x) const {
    return ((h == x.h) && (s == x.s) && (l == x.l) && (a == x.a));
}

bool SGXColourHSLA::operator!=(SGXColourHSLA x) const {
    return ((h != x.h) || (s != x.s) || (l != x.l) || (a != x.a));
}

void SGXColourHSLA::setHue(float h){
    temp_limitto360(h);
    (*this).h = h;
}

void SGXColourHSLA::setSaturation(float s){
    temp_limitto100(s);
    (*this).s = s;
}

void SGXColourHSLA::setLightness(float l){
    temp_limitto100(l);
    (*this).l = l;
}

void SGXColourHSLA::setTransparency(float a){
    temp_limitto100(a);
    (*this).a = a;
}
