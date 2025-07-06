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
    x = std::fmodf(x, 360.0f);
    if(x < 0.0f){x += 360.0f;}
}

inline float temp_HueIntermediatesToRGB(float p, float q, float t){
    if(t < 0.0f){t += 1.0f;}
    else if(t > 1.0f){t -= 1.0f;}
    if(t < 1.0f / 6.0f){return (p + 6.0f * t * (q - p));}
    if(t < 0.5f){return q;}
    if(t < 2.0f / 3.0f){return (p + 6.0f * (2.0f / 3.0f - t) * (q - p));}
    return p;
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
    if((*this).h < 0.0f){(*this).h = 0.0f;}
    else if((*this).h > 360.0f){(*this).h = 360.0f;}
    if((*this).s < 0.0f){(*this).s = 0.0f;}
    else if((*this).s > 100.0f){(*this).s = 100.0f;}
    if((*this).l < 0.0f){(*this).l = 0.0f;}
    else if((*this).l > 100.0f){(*this).l = 100.0f;}
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

bool SGXColourHSLA::operator<(SGXColourHSLA x) const {
    if(h != x.h){return (h < x.h);}
    if(s != x.s){return (s < x.s);}
    if(l != x.l){return (l < x.l);}
    return (a < x.a);
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

void SGXColourHSLA::invertHue(){
    setHue(h + 180.0f);
}

void SGXColourHSLA::invertSaturation(){
    setSaturation(100.0f - s);
}

void SGXColourHSLA::invertLightness(){
    setLightness(100.0f - s);
}

void SGXColourHSLA::linearTransformSaturation(float m, float c){
    setSaturation(m * s + c);
}

void SGXColourHSLA::linearTransformLightness(float m, float c){
    setLightness(m * l + c);
}

void SGXColourHSLA::linearTransformTransparency(float m, float c){
    setTransparency(m * a + c);
}

void SGXColourHSLA::offsetHue(float c){
    setHue(h + c);
}

SGXColourRGBA SGXColourHSLA::toRGBA() const {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float xh = (*this).h;
    float xs = (*this).s;
    float xl = (*this).l;
    xh /= 360.0f;
    xs /= 100.0f;
    xl /= 100.0f;
    if(xs == 0.0f){
        r = xl;
        g = xl;
        b = xl;
    }
    else{
        float q = 0.0f;
        if(xl < 0.5f){q = xl * (1.0f + xs);}
        else{q = xl + xs - xl * xs;}
        const float p = 2.0f * xl - q;
        r = temp_HueIntermediatesToRGB(p, q, xh + 1.0f / 3.0f);
        g = temp_HueIntermediatesToRGB(p, q, xh);
        b = temp_HueIntermediatesToRGB(p, q, xh - 1.0f / 3.0f);
    }
    SGXColourRGBA x = SGXColourRGBA(255, 255, 255);
    x.setRedUsingFloat(r);
    x.setGreenUsingFloat(g);
    x.setBlueUsingFloat(b);
    return x;
}
