#include <SGEXTN_Structs_HslaColour.h>
#include <SGEXTN_Structs_RgbaColour.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_HashAlgorithm.h>
#include <SGEXTN_ApplicationBase_OldString.h>
#include <SGEXTN_Containers_Span.h>

namespace {
float maximumOf3(float a, float b, float c){
    return SGEXTN::Math::FloatMath<float>::maximum(a, SGEXTN::Math::FloatMath<float>::maximum(b, c));
}

float minimumOf3(float a, float b, float c){
    return SGEXTN::Math::FloatMath<float>::minimum(a, SGEXTN::Math::FloatMath<float>::minimum(b, c));
}

void limitTo100(float& x){
    if(x < 0.0f){x = 0.0f;}
    else if(x > 100.0f){x = 100.0f;}
}

void limitTo360(float& x){
    x = SGEXTN::Math::FloatMath<float>::modulo(x, 360.0f);
    if(x < 0.0f){x += 360.0f;}
}

float hueIntermediatesToRGB(float p, float q, float t){
    if(t < 0.0f){t += 1.0f;}
    else if(t > 1.0f){t -= 1.0f;}
    if(t < 1.0f / 6.0f){return (p + 6.0f * t * (q - p));}
    if(t < 0.5f){return q;}
    if(t < 2.0f / 3.0f){return (p + 6.0f * (2.0f / 3.0f - t) * (q - p));}
    return p;
}
}

SGEXTN::Structs::HslaColour::HslaColour(){
    private_hue = 313.0f;
    private_saturation = 100.0f;
    private_lightness = 50.0f;
    private_transparency = 255.0f;
}

SGEXTN::Structs::HslaColour::HslaColour(SGEXTN::Structs::RgbaColour x){
    private_transparency = x.getTransparencyFloat() * 100.0f;
    const float r = x.getRedFloat();
    const float g = x.getGreenFloat();
    const float b = x.getBlueFloat();
    const float h = maximumOf3(r, g, b);
    const float l = minimumOf3(r, g, b);
    private_hue = 313.0f;
    private_saturation = 0.0f;
    private_lightness = 0.5f * (l + h);
    if(l != h){
        const float d = h - l;
        if(private_lightness > 0.5f){private_saturation = d / (2.0f - h - l);}
        else{private_saturation = d / (h + l);}
        if(h == r){
            private_hue = (g - b) / d;
            if(g < b){private_hue += 6.0f;}
        }
        else if(h == g){private_hue = (b - r) / d + 2.0f;}
        else if(h == b){private_hue = (r - g) / d + 4.0f;}
        private_hue /= 6.0f;
    }
    private_hue *= 360.0f;
    private_saturation *= 100.0f;
    private_lightness *= 100.0f;
    limitTo360(private_hue);
    limitTo100(private_saturation);
    limitTo100(private_lightness);
}

SGEXTN::Structs::HslaColour::HslaColour(float h, float s, float l){
    limitTo360(h);
    limitTo100(s);
    limitTo100(l);
    private_hue = h;
    private_saturation = s;
    private_lightness = l;
    private_transparency = 100.0f;
}

SGEXTN::Structs::HslaColour::HslaColour(float h, float s, float l, float a){
    limitTo360(h);
    limitTo100(s);
    limitTo100(l);
    limitTo100(a);
    private_hue = h;
    private_saturation = s;
    private_lightness = l;
    private_transparency = a;
}

bool SGEXTN::Structs::HslaColour::operator==(SGEXTN::Structs::HslaColour x) const {
    return ((private_hue == x.private_hue) && (private_saturation == x.private_saturation) && (private_lightness == x.private_lightness) && (private_transparency == x.private_transparency));
}

bool SGEXTN::Structs::HslaColour::operator!=(SGEXTN::Structs::HslaColour x) const {
    return ((private_hue != x.private_hue) || (private_saturation != x.private_saturation) || (private_lightness != x.private_lightness) || (private_transparency != x.private_transparency));
}

bool SGEXTN::Structs::HslaColour::operator<(SGEXTN::Structs::HslaColour x) const {
    if(private_hue != x.private_hue){return (private_hue < x.private_hue);}
    if(private_saturation != x.private_saturation){return (private_saturation < x.private_saturation);}
    if(private_lightness != x.private_lightness){return (private_lightness < x.private_lightness);}
    return (private_transparency < x.private_transparency);
}

bool SGEXTN::Structs::HslaColour::operator>(SGEXTN::Structs::HslaColour x) const {
    if(private_hue != x.private_hue){return (private_hue > x.private_hue);}
    if(private_saturation != x.private_saturation){return (private_saturation > x.private_saturation);}
    if(private_lightness != x.private_lightness){return (private_lightness > x.private_lightness);}
    return (private_transparency > x.private_transparency);
}

int SGEXTN::Structs::HslaColour::hash() const {
    SGEXTN::Containers::Array<int> hashArray(4);
    hashArray.at(0) = SGEXTN::Containers::Hash<float>()(private_hue);
    hashArray.at(1) = SGEXTN::Containers::Hash<float>()(private_saturation);
    hashArray.at(2) = SGEXTN::Containers::Hash<float>()(private_lightness);
    hashArray.at(3) = SGEXTN::Containers::Hash<float>()(private_transparency);
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 4 * sizeof(int)));
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::HslaColour::debugLog() const {
    return SGEXTN::ApplicationBase::OldString("hsla(") + SGEXTN::ApplicationBase::OldString::stringFromFloat(private_hue, SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 0) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(private_saturation, SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 0) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(private_lightness, SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 0) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(private_transparency, SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 0) + ")";
}

float SGEXTN::Structs::HslaColour::getHue() const {
    return private_hue;
}

float SGEXTN::Structs::HslaColour::getSaturation() const {
    return private_saturation;
}

float SGEXTN::Structs::HslaColour::getLightness() const {
    return private_lightness;
}

float SGEXTN::Structs::HslaColour::getTransparency() const {
    return private_transparency;
}

void SGEXTN::Structs::HslaColour::setHue(float h){
    limitTo360(h);
    private_hue = h;
}

void SGEXTN::Structs::HslaColour::setSaturation(float s){
    limitTo100(s);
    private_saturation = s;
}

void SGEXTN::Structs::HslaColour::setLightness(float l){
    limitTo100(l);
    private_lightness = l;
}

void SGEXTN::Structs::HslaColour::setTransparency(float a){
    limitTo100(a);
    private_transparency = a;
}

SGEXTN::Structs::HslaColour SGEXTN::Structs::HslaColour::invertHue() const {
    SGEXTN::Structs::HslaColour copy = (*this);
    copy.setHue(private_hue + 180.0f);
    return copy;
}

SGEXTN::Structs::HslaColour SGEXTN::Structs::HslaColour::invertSaturation() const {
    SGEXTN::Structs::HslaColour copy = (*this);
    copy.setSaturation(100.0f - private_saturation);
    return copy;
}

SGEXTN::Structs::HslaColour SGEXTN::Structs::HslaColour::invertLightness() const {
    SGEXTN::Structs::HslaColour copy = (*this);
    copy.setLightness(100.0f - private_lightness);
    return copy;
}

SGEXTN::Structs::HslaColour SGEXTN::Structs::HslaColour::linearTransformSaturation(float m, float c) const {
    SGEXTN::Structs::HslaColour copy = (*this);
    copy.setSaturation(m * private_saturation + c);
    return copy;
}

SGEXTN::Structs::HslaColour SGEXTN::Structs::HslaColour::linearTransformLightness(float m, float c) const {
    SGEXTN::Structs::HslaColour copy = (*this);
    copy.setLightness(m * private_lightness + c);
    return copy;
}

SGEXTN::Structs::HslaColour SGEXTN::Structs::HslaColour::linearTransformTransparency(float m, float c) const {
    SGEXTN::Structs::HslaColour copy = (*this);
    copy.setTransparency(m * private_transparency + c);
    return copy;
}

SGEXTN::Structs::HslaColour SGEXTN::Structs::HslaColour::offsetHue(float c) const {
    SGEXTN::Structs::HslaColour copy = (*this);
    copy.setHue(private_hue + c);
    return copy;
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::HslaColour::toRGBA() const {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    const float xh = private_hue / 360.0f;
    const float xs = private_saturation / 100.0f;
    const float xl = private_lightness / 100.0f;
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
        r = hueIntermediatesToRGB(p, q, xh + 1.0f / 3.0f);
        g = hueIntermediatesToRGB(p, q, xh);
        b = hueIntermediatesToRGB(p, q, xh - 1.0f / 3.0f);
    }
    return SGEXTN::Structs::RgbaColour(r, g, b, private_transparency / 100.0f);
}
