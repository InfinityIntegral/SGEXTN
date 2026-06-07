#include <SGEXTN_Utilities_HslaColour.h>
#include <SGEXTN_Utilities_RgbaColour.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_Containers_Hash.h>

namespace {
float maximumOf3(float a, float b, float c){
    return SGEXTN::Math::FloatMath<float>::maximum(a, SGEXTN::Math::FloatMath<float>::maximum(b, c));
}

float minimumOf3(float a, float b, float c){
    return SGEXTN::Math::FloatMath<float>::minimum(a, SGEXTN::Math::FloatMath<float>::minimum(b, c));
}

float limitTo100(float x){
    if(x < 0.0f){return 0.0f;}
    if(x > 100.0f){return 100.0f;}
    return x;
}

float limitTo360(float x){
    x = SGEXTN::Math::FloatMath<float>::modulo(x, 360.0f);
    if(x < 0.0f){x += 360.0f;}
    return x;
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

SGEXTN::Utilities::HslaColour::HslaColour() : private_hue(313.0f), private_saturation(100.0f), private_lightness(50.0f), private_transparency(100.0f) {}

SGEXTN::Utilities::HslaColour::HslaColour(SGEXTN::Utilities::RgbaColour x) : private_hue(313.0f), private_saturation(0.0f), private_lightness(50.0f), private_transparency(x.getTransparencyFloat() * 100.0f){
    const float r = x.getRedFloat();
    const float g = x.getGreenFloat();
    const float b = x.getBlueFloat();
    const float h = maximumOf3(r, g, b);
    const float l = minimumOf3(r, g, b);
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
    private_hue = limitTo360(private_hue);
    private_saturation = limitTo100(private_saturation);
    private_lightness = limitTo100(private_lightness);
}

SGEXTN::Utilities::HslaColour::HslaColour(float h, float s, float l) : private_hue(limitTo360(h)), private_saturation(limitTo100(s)), private_lightness(limitTo100(l)), private_transparency(100.0f) {}

SGEXTN::Utilities::HslaColour::HslaColour(float h, float s, float l, float a) : private_hue(limitTo360(h)), private_saturation(limitTo100(s)), private_lightness(limitTo100(l)), private_transparency(limitTo100(a)) {}

bool SGEXTN::Utilities::HslaColour::operator==(SGEXTN::Utilities::HslaColour x) const {
    return ((private_hue == x.private_hue) && (private_saturation == x.private_saturation) && (private_lightness == x.private_lightness) && (private_transparency == x.private_transparency));
}

bool SGEXTN::Utilities::HslaColour::operator!=(SGEXTN::Utilities::HslaColour x) const {
    return ((private_hue != x.private_hue) || (private_saturation != x.private_saturation) || (private_lightness != x.private_lightness) || (private_transparency != x.private_transparency));
}

bool SGEXTN::Utilities::HslaColour::operator<(SGEXTN::Utilities::HslaColour x) const {
    if(private_hue != x.private_hue){return (private_hue < x.private_hue);}
    if(private_saturation != x.private_saturation){return (private_saturation < x.private_saturation);}
    if(private_lightness != x.private_lightness){return (private_lightness < x.private_lightness);}
    return (private_transparency < x.private_transparency);
}

bool SGEXTN::Utilities::HslaColour::operator>(SGEXTN::Utilities::HslaColour x) const {
    if(private_hue != x.private_hue){return (private_hue > x.private_hue);}
    if(private_saturation != x.private_saturation){return (private_saturation > x.private_saturation);}
    if(private_lightness != x.private_lightness){return (private_lightness > x.private_lightness);}
    return (private_transparency > x.private_transparency);
}

int SGEXTN::Utilities::HslaColour::hash() const {
    return SGEXTN::Containers::Hash<float, float, float, float>()(private_hue, private_saturation, private_lightness, private_transparency);
}

SGEXTN::CoreText::String SGEXTN::Utilities::HslaColour::debugLog() const {
    return SGEXTN::CoreText::String("hsla(") + SGEXTN::CoreText::String::stringFromFloat(private_hue, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 0) + ", " + SGEXTN::CoreText::String::stringFromFloat(private_saturation, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 0) + ", " + SGEXTN::CoreText::String::stringFromFloat(private_lightness, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 0) + ", " + SGEXTN::CoreText::String::stringFromFloat(private_transparency, 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 0) + ")";
}

float SGEXTN::Utilities::HslaColour::getHue() const {
    return private_hue;
}

float SGEXTN::Utilities::HslaColour::getSaturation() const {
    return private_saturation;
}

float SGEXTN::Utilities::HslaColour::getLightness() const {
    return private_lightness;
}

float SGEXTN::Utilities::HslaColour::getTransparency() const {
    return private_transparency;
}

void SGEXTN::Utilities::HslaColour::setHue(float h){
    private_hue = limitTo360(h);
}

void SGEXTN::Utilities::HslaColour::setSaturation(float s){
    private_saturation = limitTo100(s);
}

void SGEXTN::Utilities::HslaColour::setLightness(float l){
    private_lightness = limitTo100(l);
}

void SGEXTN::Utilities::HslaColour::setTransparency(float a){
    private_transparency = limitTo100(a);
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::invertHue() const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setHue(private_hue + 180.0f);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::invertSaturation() const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setSaturation(100.0f - private_saturation);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::invertLightness() const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setLightness(100.0f - private_lightness);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::linearTransformSaturation(float m, float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setSaturation(m * private_saturation + c);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::linearTransformLightness(float m, float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setLightness(m * private_lightness + c);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::linearTransformTransparency(float m, float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setTransparency(m * private_transparency + c);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::offsetHue(float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setHue(private_hue + c);
    return copy;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::HslaColour::toRGBA() const {
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
    return SGEXTN::Utilities::RgbaColour(r, g, b, private_transparency / 100.0f);
}
