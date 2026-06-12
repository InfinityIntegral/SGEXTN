#include <SGEXTN_Utilities_RgbaColour.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Math_FloatMath.h>
#include <SGEXTN_Containers_ForceCrash.h>

namespace {
int boundInt(int x){
    if(x < 0){return 0;}
    if(x > 255){return 255;}
    return x;
}

float boundFloat(float x){
    if(x < 0.0f){return 0.0f;}
    if(x > 1.0f){return 1.0f;}
    return x;
}

unsigned int toUnsignedInt(float x){
    return static_cast<unsigned int>(SGEXTN::Math::FloatMath<float>::roundToInt(255.0f * x));
}

unsigned int toUnsignedInt(int x){
    return static_cast<unsigned int>(x);
}

unsigned int packChannels(unsigned int r, unsigned int g, unsigned int b, unsigned int a){
    return ((r << 24u) | (g << 16u) | (b << 8u) | a);
}

unsigned int setChannelByOffset(unsigned int original, unsigned int offset, unsigned int newData){
    return ((original & (~(0xFF << offset))) | (newData << offset));
}

float srgbToLinear(float x){
    if(x <= 0.04045f){return (x / 12.92f);}
    return SGEXTN::Math::FloatMath<float>::powerOf((x + 0.055f) / 1.055f, 2.4f);
}

float linearToSrgb(float x){
    if(x <= 0.0031308f){return (12.92f * x);}
    return (1.055f * SGEXTN::Math::FloatMath<float>::powerOf(x, 1.0f / 2.4f) - 0.055f);
}
}

SGEXTN::Utilities::RgbaColour::RgbaColour() : private_data(0xff00c8ff) {}

SGEXTN::Utilities::RgbaColour::RgbaColour(unsigned int data) : private_data(data) {}

SGEXTN::Utilities::RgbaColour::RgbaColour(int r, int g, int b, int a) : private_data(packChannels(toUnsignedInt(boundInt(r)), toUnsignedInt(boundInt(g)), toUnsignedInt(boundInt(b)), toUnsignedInt(boundInt(a)))) {}

SGEXTN::Utilities::RgbaColour::RgbaColour(int r, int g, int b) : private_data(packChannels(toUnsignedInt(boundInt(r)), toUnsignedInt(boundInt(g)), toUnsignedInt(boundInt(b)), 255u)) {}

SGEXTN::Utilities::RgbaColour::RgbaColour(float r, float g, float b, float a) : private_data(packChannels(toUnsignedInt(boundFloat(r)), toUnsignedInt(boundFloat(g)), toUnsignedInt(boundFloat(b)), toUnsignedInt(boundFloat(a)))) {}

SGEXTN::Utilities::RgbaColour::RgbaColour(float r, float g, float b) : private_data(packChannels(toUnsignedInt(boundFloat(r)), toUnsignedInt(boundFloat(g)), toUnsignedInt(boundFloat(b)), 255u)) {}

int SGEXTN::Utilities::RgbaColour::getRed() const {
    return static_cast<int>(private_data >> 24u);
}

int SGEXTN::Utilities::RgbaColour::getGreen() const {
    return static_cast<int>(0xFFu & (private_data >> 16u));
}

int SGEXTN::Utilities::RgbaColour::getBlue() const {
    return static_cast<int>(0xFFu & (private_data >> 8u));
}

int SGEXTN::Utilities::RgbaColour::getTransparency() const {
    return static_cast<int>(0xFFu & private_data);
}

float SGEXTN::Utilities::RgbaColour::getRedFloat() const {
    return (static_cast<float>(getRed()) / 255.0f);
}

float SGEXTN::Utilities::RgbaColour::getGreenFloat() const {
    return (static_cast<float>(getGreen()) / 255.0f);
}

float SGEXTN::Utilities::RgbaColour::getBlueFloat() const {
    return (static_cast<float>(getBlue()) / 255.0f);
}

float SGEXTN::Utilities::RgbaColour::getTransparencyFloat() const {
    return (static_cast<float>(getTransparency()) / 255.0f);
}

void SGEXTN::Utilities::RgbaColour::setRed(int r){
    private_data = setChannelByOffset(private_data, 24u, toUnsignedInt(boundInt(r)));
}

void SGEXTN::Utilities::RgbaColour::setGreen(int g){
    private_data = setChannelByOffset(private_data, 16u, toUnsignedInt(boundInt(g)));
}

void SGEXTN::Utilities::RgbaColour::setBlue(int b){
    private_data = setChannelByOffset(private_data, 8u, toUnsignedInt(boundInt(b)));
}

void SGEXTN::Utilities::RgbaColour::setTransparency(int a){
    private_data = setChannelByOffset(private_data, 0u, toUnsignedInt(boundInt(a)));
}

void SGEXTN::Utilities::RgbaColour::setRedFloat(float r){
    private_data = setChannelByOffset(private_data, 24u, toUnsignedInt(boundFloat(r)));
}

void SGEXTN::Utilities::RgbaColour::setGreenFloat(float g){
    private_data = setChannelByOffset(private_data, 16u, toUnsignedInt(boundFloat(g)));
}

void SGEXTN::Utilities::RgbaColour::setBlueFloat(float b){
    private_data = setChannelByOffset(private_data, 8u, toUnsignedInt(boundFloat(b)));
}

void SGEXTN::Utilities::RgbaColour::setTransparencyFloat(float a){
    private_data = setChannelByOffset(private_data, 0u, toUnsignedInt(boundFloat(a)));
}

SGEXTN::CoreText::String SGEXTN::Utilities::RgbaColour::rgbHtmlString() const {
    return (SGEXTN::CoreText::String("rgb(") + SGEXTN::CoreText::String::stringFromInt(getRed(), 10) + ", " + SGEXTN::CoreText::String::stringFromInt(getGreen(), 10) + ", " + SGEXTN::CoreText::String::stringFromInt(getBlue(), 10) + ")");
}

SGEXTN::CoreText::String SGEXTN::Utilities::RgbaColour::rgbaHtmlString() const {
    return (SGEXTN::CoreText::String("rgba(") + SGEXTN::CoreText::String::stringFromInt(getRed(), 10) + ", " + SGEXTN::CoreText::String::stringFromInt(getGreen(), 10) + ", " + SGEXTN::CoreText::String::stringFromInt(getBlue(), 10) + ", " + SGEXTN::CoreText::String::stringFromInt(getTransparency(), 10 ) + ")");
}

SGEXTN::CoreText::String SGEXTN::Utilities::RgbaColour::rgbHexString() const {
    return (SGEXTN::CoreText::String::stringFromInt(getRed(), 16).fillLeftToByteLength(2, '0') + SGEXTN::CoreText::String::stringFromInt(getGreen(), 16).fillLeftToByteLength(2, '0') + SGEXTN::CoreText::String::stringFromInt(getBlue(), 16).fillLeftToByteLength(2, '0'));
}

SGEXTN::CoreText::String SGEXTN::Utilities::RgbaColour::rgbaHexString() const {
    return (SGEXTN::CoreText::String::stringFromInt(getRed(), 16).fillLeftToByteLength(2, '0') + SGEXTN::CoreText::String::stringFromInt(getGreen(), 16).fillLeftToByteLength(2, '0') + SGEXTN::CoreText::String::stringFromInt(getBlue(), 16).fillLeftToByteLength(2, '0') + SGEXTN::CoreText::String::stringFromInt(getTransparency(), 16).fillLeftToByteLength(2, '0'));
}

SGEXTN::CoreText::String SGEXTN::Utilities::RgbaColour::rgbFloatHtmlString() const {
    return (SGEXTN::CoreText::String("rgb(") + SGEXTN::CoreText::String::stringFromFloat(getRedFloat(), 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) + ", " + SGEXTN::CoreText::String::stringFromFloat(getGreenFloat(), 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) + ", " + SGEXTN::CoreText::String::stringFromFloat(getBlueFloat(), 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) + ")");
}

SGEXTN::CoreText::String SGEXTN::Utilities::RgbaColour::rgbaFloatHtmlString() const {
    return (SGEXTN::CoreText::String("rgba(") + SGEXTN::CoreText::String::stringFromFloat(getRedFloat(), 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) + ", " + SGEXTN::CoreText::String::stringFromFloat(getGreenFloat(), 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) + ", " + SGEXTN::CoreText::String::stringFromFloat(getBlueFloat(), 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) + ", " + SGEXTN::CoreText::String::stringFromFloat(getTransparencyFloat(), 10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 3) +  ")");
}

bool SGEXTN::Utilities::RgbaColour::operator==(SGEXTN::Utilities::RgbaColour x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::Utilities::RgbaColour::operator!=(SGEXTN::Utilities::RgbaColour x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::Utilities::RgbaColour::operator<(SGEXTN::Utilities::RgbaColour x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::Utilities::RgbaColour::operator>(SGEXTN::Utilities::RgbaColour x) const {
    return (private_data > x.private_data);
}

int SGEXTN::Utilities::RgbaColour::hash() const {
    return SGEXTN::Containers::Hash<unsigned int>()(private_data);
}

SGEXTN::CoreText::String SGEXTN::Utilities::RgbaColour::debugPrint() const {
    return rgbaHtmlString();
}

void SGEXTN::Utilities::RgbaColour::gammaCorrectBegin(float& r, float& g, float& b) const {
    r = srgbToLinear(getRedFloat());
    g = srgbToLinear(getGreenFloat());
    b = srgbToLinear(getBlueFloat());
}

void SGEXTN::Utilities::RgbaColour::gammaCorrectEnd(float r, float g, float b){
    setRedFloat(linearToSrgb(r));
    setGreenFloat(linearToSrgb(g));
    setBlueFloat(linearToSrgb(b));
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::linearTransformRed(float m, float c, bool gammaCorrect) const {
    float r = getRedFloat();
    if(gammaCorrect == true){r = srgbToLinear(r);}
    r = boundFloat(m * r + c);
    if(gammaCorrect == true){r = linearToSrgb(r);}
    SGEXTN::Utilities::RgbaColour output = (*this);
    output.setRedFloat(r);
    return output;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::linearTransformGreen(float m, float c, bool gammaCorrect) const {
    float g = getGreenFloat();
    if(gammaCorrect == true){g = srgbToLinear(g);}
    g = boundFloat(m * g + c);
    if(gammaCorrect == true){g = linearToSrgb(g);}
    SGEXTN::Utilities::RgbaColour output = (*this);
    output.setGreenFloat(g);
    return output;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::linearTransformBlue(float m, float c, bool gammaCorrect) const {
    float b = getBlueFloat();
    if(gammaCorrect == true){b = srgbToLinear(b);}
    b = boundFloat(m * b + c);
    if(gammaCorrect == true){b = linearToSrgb(b);}
    SGEXTN::Utilities::RgbaColour output = (*this);
    output.setBlueFloat(b);
    return output;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::linearTransformTransparency(float m, float c) const {
    float a = getTransparencyFloat();
    a = boundFloat(m * a + c);
    SGEXTN::Utilities::RgbaColour output = (*this);
    output.setTransparencyFloat(a);
    return output;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::applyTint(RgbaColour x, bool gammaCorrect) const {
    return applyTintSeparateTransparency(x, x.getTransparencyFloat(), gammaCorrect);
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::applyTintSeparateTransparency(RgbaColour x, float transparency, bool gammaCorrect) const {
    if(transparency < 0.0f || transparency > 1.0f){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Utilities::RgbaColour::applyTintSeparateTransparency crashed because the transparency is below 0 or above 1, if you want to intentionally produce a negative mixing effect, use SGEXTN::Utilities::RgbaColour::interpolate instead and set thisStrength to below 0 or above 1");}
    float r1 = getRedFloat();
    float g1 = getGreenFloat();
    float b1 = getBlueFloat();
    float r2 = x.getRedFloat();
    float g2 = x.getGreenFloat();
    float b2 = x.getBlueFloat();
    const float a1 = getTransparencyFloat();
    const float a2 = transparency;
    if(gammaCorrect == true){
        r1 = srgbToLinear(r1);
        g1 = srgbToLinear(g1);
        b1 = srgbToLinear(b1);
        r2 = srgbToLinear(r2);
        g2 = srgbToLinear(g2);
        b2 = srgbToLinear(b2);
    }
    const float a = a2 + a1 * (1.0f - a2);
    if(a == 0.0f){return SGEXTN::Utilities::RgbaColour(0, 0, 0, 0);}
    float r = boundFloat((r2 * a2 + r1 * a1 * (1.0f - a2)) / a);
    float g = boundFloat((g2 * a2 + g1 * a1 * (1.0f - a2)) / a);
    float b = boundFloat((b2 * a2 + b1 * a1 * (1.0f - a2)) / a);
    if(gammaCorrect == true){
        r = linearToSrgb(r);
        g = linearToSrgb(g);
        b = linearToSrgb(b);
    }
    return SGEXTN::Utilities::RgbaColour(r, g, b, a);
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::interpolate(RgbaColour other, float thisStrength, bool gammaCorrect) const {
    float r1 = getRedFloat();
    float g1 = getGreenFloat();
    float b1 = getBlueFloat();
    float r2 = other.getRedFloat();
    float g2 = other.getGreenFloat();
    float b2 = other.getBlueFloat();
    if(gammaCorrect == true){
        r1 = srgbToLinear(r1);
        g1 = srgbToLinear(g1);
        b1 = srgbToLinear(b1);
        r2 = srgbToLinear(r2);
        g2 = srgbToLinear(g2);
        b2 = srgbToLinear(b2);
    }
    float r = boundFloat(r2 * (1.0f - thisStrength) + r1 * thisStrength);
    float g = boundFloat(g2 * (1.0f - thisStrength) + g1 * thisStrength);
    float b = boundFloat(b2 * (1.0f - thisStrength) + b1 * thisStrength);
    if(gammaCorrect == true){
        r = linearToSrgb(r);
        g = linearToSrgb(g);
        b = linearToSrgb(b);
    }
    const float a = other.getTransparencyFloat() * (1.0f - thisStrength) + getTransparencyFloat() * thisStrength;
    return SGEXTN::Utilities::RgbaColour(r, g, b, a);
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::RgbaColour::complement(bool gammaCorrect) const {
    float r = getRedFloat();
    float g = getGreenFloat();
    float b = getBlueFloat();
    if(gammaCorrect == true){
        r = srgbToLinear(r);
        g = srgbToLinear(g);
        b = srgbToLinear(b);
    }
    r = 1.0f - r;
    g = 1.0f - g;
    b = 1.0f - b;
    if(gammaCorrect == true){
        r = linearToSrgb(r);
        g = linearToSrgb(g);
        b = linearToSrgb(b);
    }
    return SGEXTN::Utilities::RgbaColour(r, g, b, getTransparencyFloat());
}
