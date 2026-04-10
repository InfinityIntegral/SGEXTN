#include <SGEXTN_Structs_RgbaColour.h>
#include <SGEXTN_ApplicationBase_OldString.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Math_FloatMath.h>
#include <private_api/SGEXTN_Containers_Crash.h>

namespace {
void boundInt(int& x){
    if(x < 0){x = 0;}
    else if(x > 255){x = 255;}
}

void boundFloat(float& x){
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
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

SGEXTN::Structs::RgbaColour::RgbaColour(){
    private_data = 0xff00c8ff;
}

SGEXTN::Structs::RgbaColour::RgbaColour(unsigned int data){
    private_data = data;
}

SGEXTN::Structs::RgbaColour::RgbaColour(int r, int g, int b, int a){
    boundInt(r);
    boundInt(g);
    boundInt(b);
    boundInt(a);
    private_data = packChannels(toUnsignedInt(r), toUnsignedInt(g), toUnsignedInt(b), toUnsignedInt(a));
}

SGEXTN::Structs::RgbaColour::RgbaColour(int r, int g, int b){
    boundInt(r);
    boundInt(g);
    boundInt(b);
    private_data = packChannels(toUnsignedInt(r), toUnsignedInt(g), toUnsignedInt(b), 255u);
}

SGEXTN::Structs::RgbaColour::RgbaColour(float r, float g, float b, float a){
    boundFloat(r);
    boundFloat(g);
    boundFloat(b);
    boundFloat(a);
    private_data = packChannels(toUnsignedInt(r), toUnsignedInt(g), toUnsignedInt(b), toUnsignedInt(a));
}

SGEXTN::Structs::RgbaColour::RgbaColour(float r, float g, float b){
    boundFloat(r);
    boundFloat(g);
    boundFloat(b);
    private_data = packChannels(toUnsignedInt(r), toUnsignedInt(g), toUnsignedInt(b), 255u);
}

int SGEXTN::Structs::RgbaColour::getRed() const {
    return static_cast<int>(private_data >> 24u);
}

int SGEXTN::Structs::RgbaColour::getGreen() const {
    return static_cast<int>(0xFFu & (private_data >> 16u));
}

int SGEXTN::Structs::RgbaColour::getBlue() const {
    return static_cast<int>(0xFFu & (private_data >> 8u));
}

int SGEXTN::Structs::RgbaColour::getTransparency() const {
    return static_cast<int>(0xFFu & private_data);
}

float SGEXTN::Structs::RgbaColour::getRedFloat() const {
    return (static_cast<float>(getRed()) / 255.0f);
}

float SGEXTN::Structs::RgbaColour::getGreenFloat() const {
    return (static_cast<float>(getGreen()) / 255.0f);
}

float SGEXTN::Structs::RgbaColour::getBlueFloat() const {
    return (static_cast<float>(getBlue()) / 255.0f);
}

float SGEXTN::Structs::RgbaColour::getTransparencyFloat() const {
    return (static_cast<float>(getTransparency()) / 255.0f);
}

void SGEXTN::Structs::RgbaColour::setRed(int r){
    boundInt(r);
    private_data = setChannelByOffset(private_data, 24u, toUnsignedInt(r));
}

void SGEXTN::Structs::RgbaColour::setGreen(int g){
    boundInt(g);
    private_data = setChannelByOffset(private_data, 16u, toUnsignedInt(g));
}

void SGEXTN::Structs::RgbaColour::setBlue(int b){
    boundInt(b);
    private_data = setChannelByOffset(private_data, 8u, toUnsignedInt(b));
}

void SGEXTN::Structs::RgbaColour::setTransparency(int a){
    boundInt(a);
    private_data = setChannelByOffset(private_data, 0u, toUnsignedInt(a));
}

void SGEXTN::Structs::RgbaColour::setRedFloat(float r){
    boundFloat(r);
    private_data = setChannelByOffset(private_data, 24u, toUnsignedInt(r));
}

void SGEXTN::Structs::RgbaColour::setGreenFloat(float g){
    boundFloat(g);
    private_data = setChannelByOffset(private_data, 16u, toUnsignedInt(g));
}

void SGEXTN::Structs::RgbaColour::setBlueFloat(float b){
    boundFloat(b);
    private_data = setChannelByOffset(private_data, 8u, toUnsignedInt(b));
}

void SGEXTN::Structs::RgbaColour::setTransparencyFloat(float a){
    boundFloat(a);
    private_data = setChannelByOffset(private_data, 0u, toUnsignedInt(a));
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::RgbaColour::rgbHtmlString() const {
    return (SGEXTN::ApplicationBase::OldString("rgb(") + SGEXTN::ApplicationBase::OldString::stringFromInt(getRed(), 10) + ", " + SGEXTN::ApplicationBase::OldString::stringFromInt(getGreen(), 10) + ", " + SGEXTN::ApplicationBase::OldString::stringFromInt(getBlue(), 10) + ")");
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::RgbaColour::rgbaHtmlString() const {
    return (SGEXTN::ApplicationBase::OldString("rgba(") + SGEXTN::ApplicationBase::OldString::stringFromInt(getRed(), 10) + ", " + SGEXTN::ApplicationBase::OldString::stringFromInt(getGreen(), 10) + ", " + SGEXTN::ApplicationBase::OldString::stringFromInt(getBlue(), 10) + ", " + SGEXTN::ApplicationBase::OldString::stringFromInt(getTransparency(), 10 ) + ")");
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::RgbaColour::rgbHexString() const {
    return (SGEXTN::ApplicationBase::OldString::stringFromInt(getRed(), 16).fillLeftToLength(2, '0') + SGEXTN::ApplicationBase::OldString::stringFromInt(getGreen(), 16).fillLeftToLength(2, '0') + SGEXTN::ApplicationBase::OldString::stringFromInt(getBlue(), 16).fillLeftToLength(2, '0'));
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::RgbaColour::rgbaHexString() const {
    return (SGEXTN::ApplicationBase::OldString::stringFromInt(getRed(), 16).fillLeftToLength(2, '0') + SGEXTN::ApplicationBase::OldString::stringFromInt(getGreen(), 16).fillLeftToLength(2, '0') + SGEXTN::ApplicationBase::OldString::stringFromInt(getBlue(), 16).fillLeftToLength(2, '0') + SGEXTN::ApplicationBase::OldString::stringFromInt(getTransparency(), 16).fillLeftToLength(2, '0'));
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::RgbaColour::rgbFloatHtmlString() const {
    return (SGEXTN::ApplicationBase::OldString("rgb(") + SGEXTN::ApplicationBase::OldString::stringFromFloat(getRedFloat(), SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 3) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(getGreenFloat(), SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 3) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(getBlueFloat(), SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 3) + ")");
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::RgbaColour::rgbaFloatHtmlString() const {
    return (SGEXTN::ApplicationBase::OldString("rgba(") + SGEXTN::ApplicationBase::OldString::stringFromFloat(getRedFloat(), SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 3) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(getGreenFloat(), SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 3) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(getBlueFloat(), SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 3) + ", " + SGEXTN::ApplicationBase::OldString::stringFromFloat(getTransparencyFloat(), SGEXTN::ApplicationBase::FloatDisplayFormat::DecimalPlace, 3) +  ")");
}

bool SGEXTN::Structs::RgbaColour::operator==(SGEXTN::Structs::RgbaColour x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::Structs::RgbaColour::operator!=(SGEXTN::Structs::RgbaColour x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::Structs::RgbaColour::operator<(SGEXTN::Structs::RgbaColour x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::Structs::RgbaColour::operator>(SGEXTN::Structs::RgbaColour x) const {
    return (private_data > x.private_data);
}

int SGEXTN::Structs::RgbaColour::hash() const {
    return SGEXTN::Containers::Hash<unsigned int>()(private_data);
}

SGEXTN::ApplicationBase::OldString SGEXTN::Structs::RgbaColour::debugLog() const {
    return rgbaHtmlString();
}

void SGEXTN::Structs::RgbaColour::gammaCorrectBegin(float& r, float& g, float& b) const {
    r = srgbToLinear(getRedFloat());
    g = srgbToLinear(getGreenFloat());
    b = srgbToLinear(getBlueFloat());
}

void SGEXTN::Structs::RgbaColour::gammaCorrectEnd(float r, float g, float b){
    setRedFloat(linearToSrgb(r));
    setGreenFloat(linearToSrgb(g));
    setBlueFloat(linearToSrgb(b));
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::linearTransformRed(float m, float c, bool gammaCorrect) const {
    float r = getRedFloat();
    if(gammaCorrect == true){r = srgbToLinear(r);}
    r = m * r + c;
    boundFloat(r);
    if(gammaCorrect == true){r = linearToSrgb(r);}
    SGEXTN::Structs::RgbaColour output = (*this);
    output.setRedFloat(r);
    return output;
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::linearTransformGreen(float m, float c, bool gammaCorrect) const {
    float g = getGreenFloat();
    if(gammaCorrect == true){g = srgbToLinear(g);}
    g = m * g + c;
    boundFloat(g);
    if(gammaCorrect == true){g = linearToSrgb(g);}
    SGEXTN::Structs::RgbaColour output = (*this);
    output.setGreenFloat(g);
    return output;
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::linearTransformBlue(float m, float c, bool gammaCorrect) const {
    float b = getBlueFloat();
    if(gammaCorrect == true){b = srgbToLinear(b);}
    b = m * b + c;
    boundFloat(b);
    if(gammaCorrect == true){b = linearToSrgb(b);}
    SGEXTN::Structs::RgbaColour output = (*this);
    output.setBlueFloat(b);
    return output;
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::linearTransformTransparency(float m, float c) const {
    float a = getTransparencyFloat();
    a = m * a + c;
    boundFloat(a);
    SGEXTN::Structs::RgbaColour output = (*this);
    output.setTransparencyFloat(a);
    return output;
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::applyTint(RgbaColour x, bool gammaCorrect) const {
    return applyTintSeparateTransparency(x, x.getTransparencyFloat(), gammaCorrect);
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::applyTintSeparateTransparency(RgbaColour x, float transparency, bool gammaCorrect) const {
    if(transparency < 0.0f || transparency > 1.0f){SGEXTN::Containers::Crash::crash("SGEXTN::Structs::RgbaColour::applyTintSeparateTransparency crashed because the transparency is below 0 or above 1, if you want to intentionally produce a negative mixing effect, use SGEXTN::Structs::RgbaColour::interpolate instead and set thisStrength to below 0 or above 1");}
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
    if(a == 0.0f){return SGEXTN::Structs::RgbaColour(0, 0, 0, 0);}
    float r = (r2 * a2 + r1 * a1 * (1.0f - a2)) / a;
    float g = (g2 * a2 + g1 * a1 * (1.0f - a2)) / a;
    float b = (b2 * a2 + b1 * a1 * (1.0f - a2)) / a;
    boundFloat(r);
    boundFloat(g);
    boundFloat(b);
    if(gammaCorrect == true){
        r = linearToSrgb(r);
        g = linearToSrgb(g);
        b = linearToSrgb(b);
    }
    return SGEXTN::Structs::RgbaColour(r, g, b, a);
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::interpolate(RgbaColour other, float thisStrength, bool gammaCorrect) const {
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
    float r = r2 * (1.0f - thisStrength) + r1 * thisStrength;
    float g = g2 * (1.0f - thisStrength) + g1 * thisStrength;
    float b = b2 * (1.0f - thisStrength) + b1 * thisStrength;
    boundFloat(r);
    boundFloat(g);
    boundFloat(b);
    if(gammaCorrect == true){
        r = linearToSrgb(r);
        g = linearToSrgb(g);
        b = linearToSrgb(b);
    }
    const float a = other.getTransparencyFloat() * (1.0f - thisStrength) + getTransparencyFloat() * thisStrength;
    return SGEXTN::Structs::RgbaColour(r, g, b, a);
}

SGEXTN::Structs::RgbaColour SGEXTN::Structs::RgbaColour::complement(bool gammaCorrect) const {
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
    return SGEXTN::Structs::RgbaColour(r, g, b, getTransparencyFloat());
}
