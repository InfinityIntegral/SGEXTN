#include <SGXColourRGBA.h>
#include <SGXString.h>
#include <SGLHash.h>
#include <SGLFloatMath.h>

namespace{
inline void temp_boundInt(int& x){
    if(x < 0){x = 0;}
    else if(x > 255){x = 255;}
}

inline void temp_boundFloat(float& x){
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
}

inline unsigned int temp_floatToUnsignedInt(float x){
    const int x0 = SGLFloatMath::roundToInt(255.0f * x);
    return static_cast<unsigned int>(x0);
}
}

SGXColourRGBA::SGXColourRGBA(unsigned int x0){
    (*this).x = x0;
}

SGXColourRGBA::SGXColourRGBA(int r, int g, int b, int a){
    temp_boundInt(r);
    temp_boundInt(g);
    temp_boundInt(b);
    temp_boundInt(a);
    (*this).x = (static_cast<unsigned int>(r) << 24u) | (static_cast<unsigned int>(g) << 16u) | (static_cast<unsigned int>(b) << 8u) | (static_cast<unsigned int>(a));
}

SGXColourRGBA::SGXColourRGBA(int r, int g, int b){
    temp_boundInt(r);
    temp_boundInt(g);
    temp_boundInt(b);
    (*this).x = (static_cast<unsigned int>(r) << 24u) | (static_cast<unsigned int>(g) << 16u) | (static_cast<unsigned int>(b) << 8u) | (0xFFu);
}

SGXColourRGBA::SGXColourRGBA(float r, float g, float b, float a){
    temp_boundFloat(r);
    temp_boundFloat(g);
    temp_boundFloat(b);
    temp_boundFloat(a);
    (*this).x = (temp_floatToUnsignedInt(r) << 24u) | (temp_floatToUnsignedInt(g) << 16u) | (temp_floatToUnsignedInt(b) << 8u) | (temp_floatToUnsignedInt(a));
}

SGXColourRGBA::SGXColourRGBA(float r, float g, float b){
    temp_boundFloat(r);
    temp_boundFloat(g);
    temp_boundFloat(b);
    (*this).x = (temp_floatToUnsignedInt(r) << 24u) | (temp_floatToUnsignedInt(g) << 16u) | (temp_floatToUnsignedInt(b) << 8u) | (0xFFu);
}

int SGXColourRGBA::getRed() const {
    return static_cast<int>((*this).x >> 24u);
}

int SGXColourRGBA::getGreen() const {
    return static_cast<int>(0xFFu & ((*this).x >> 16u));
}

int SGXColourRGBA::getBlue() const {
    return static_cast<int>(0xFFu & ((*this).x >> 8u));
}

int SGXColourRGBA::getTransparency() const {
    return static_cast<int>(0xFFu & ((*this).x));
}

float SGXColourRGBA::getRedAsFloat() const {
    return (static_cast<float>(getRed()) / 255.0f);
}

float SGXColourRGBA::getGreenAsFloat() const {
    return (static_cast<float>(getGreen()) / 255.0f);
}

float SGXColourRGBA::getBlueAsFloat() const {
    return (static_cast<float>(getBlue()) / 255.0f);
}

float SGXColourRGBA::getTransparencyAsFloat() const {
    return (static_cast<float>(getTransparency()) / 255.0f);
}

SGXColourRGBA& SGXColourRGBA::setRed(int r){
    temp_boundInt(r);
    (*this).x = ((*this).x & 0xFFFFFFu) | (static_cast<unsigned int>(r) << 24u);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::setGreen(int g){
    temp_boundInt(g);
    (*this).x = ((*this).x & 0xFF00FFFFu) | (static_cast<unsigned int>(g) << 16u);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::setBlue(int b){
    temp_boundInt(b);
    (*this).x = ((*this).x & 0xFFFF00FFu) | (static_cast<unsigned int>(b) << 8u);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::setTransparency(int a){
    temp_boundInt(a);
    (*this).x = ((*this).x & 0xFFFFFF00u) | static_cast<unsigned int>(a);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::setRedUsingFloat(float r){
    temp_boundFloat(r);
    (*this).x = ((*this).x & 0xFFFFFFu) | (temp_floatToUnsignedInt(r) << 24u);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::setGreenUsingFloat(float g){
    temp_boundFloat(g);
    (*this).x = ((*this).x & 0xFF00FFFFu) | (temp_floatToUnsignedInt(g) << 16u);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::setBlueUsingFloat(float b){
    temp_boundFloat(b);
    (*this).x = ((*this).x & 0xFFFF00FFu) | (temp_floatToUnsignedInt(b) << 8u);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::setTransparencyUsingFloat(float a){
    temp_boundFloat(a);
    (*this).x = ((*this).x & 0xFFFFFF00u) | temp_floatToUnsignedInt(a);
    return (*this);
}

SGXString SGXColourRGBA::getStringForPrintingRGBHTML() const {
    return (SGXString("rgb(") + SGXString::intToString(getRed()) + ", " + SGXString::intToString(getGreen()) + ", " + SGXString::intToString(getBlue()) + ")");
}

SGXString SGXColourRGBA::getStringForPrintingRGBAHTML() const {
    return (SGXString("rgb(") + SGXString::intToString(getRed()) + ", " + SGXString::intToString(getGreen()) + ", " + SGXString::intToString(getBlue()) + ", " + SGXString::intToString(getTransparency()) + ")");
}

SGXString SGXColourRGBA::getStringForPrintingRGBHex() const{
    return (SGXString("#") + SGXString::intToStringBase16(getRed()).fillLeftToLength(2, '0') + SGXString::intToStringBase16(getGreen()).fillLeftToLength(2, '0') + SGXString::intToStringBase16(getBlue()).fillLeftToLength(2, '0'));
}

SGXString SGXColourRGBA::getStringForPrintingRGBAHex() const {
    return (SGXString("#") + SGXString::intToStringBase16(getRed()).fillLeftToLength(2, '0') + SGXString::intToStringBase16(getGreen()).fillLeftToLength(2, '0') + SGXString::intToStringBase16(getBlue()).fillLeftToLength(2, '0') + SGXString::intToStringBase16(getTransparency()).fillLeftToLength(2, '0'));
}

SGXString SGXColourRGBA::getStringForPrintingRGBFloatHTML() const {
    return (SGXString("rgb(") + SGXString::floatToString(getRedAsFloat()) + ", " + SGXString::floatToString(getGreenAsFloat()) + ", " + SGXString::floatToString(getBlueAsFloat()) + ")");
}

SGXString SGXColourRGBA::getStringForPrintingRGBAFloatHTML() const {
    return (SGXString("rgb(") + SGXString::floatToString(getRedAsFloat()) + ", " + SGXString::floatToString(getGreenAsFloat()) + ", " + SGXString::floatToString(getBlueAsFloat()) + ", " + SGXString::floatToString(getTransparencyAsFloat()) + ")");
}

bool SGXColourRGBA::operator==(SGXColourRGBA x) const {
    return ((*this).x == x.x);
}

bool SGXColourRGBA::operator!=(SGXColourRGBA x) const {
    return ((*this).x != x.x);
}

bool SGXColourRGBA::operator<(SGXColourRGBA x) const {
    return ((*this).x < x.x);
}

bool SGXColourRGBA::operator>(SGXColourRGBA x) const {
    return((*this).x > x.x);
}

int SGXColourRGBA::hash() const {
    return SGLHash<unsigned int>()(x);
}

SGXColourRGBA& SGXColourRGBA::linearTransformRed(float m, float c){
    float r = getRedAsFloat();
    r = m * r + c;
    setRedUsingFloat(r);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::linearTransformGreen(float m, float c){
    float g = getGreenAsFloat();
    g = m * g + c;
    setGreenUsingFloat(g);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::linearTransformBlue(float m, float c){
    float b = getBlueAsFloat();
    b = m * b + c;
    setBlueUsingFloat(b);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::linearTransformTransparency(float m, float c){
    float a = getTransparencyAsFloat();
    a = m * a + c;
    setTransparencyUsingFloat(a);
    return (*this);
}

void SGXColourRGBA::gammaCorrectBegin(float &r, float &g, float &b) const {
    r = SGLFloatMath::aToThePowerOfB(getRedAsFloat(), 2.2f);
    g = SGLFloatMath::aToThePowerOfB(getGreenAsFloat(), 2.2f);
    b = SGLFloatMath::aToThePowerOfB(getBlueAsFloat(), 2.2f);
}

void SGXColourRGBA::gammaCorrectEnd(float r, float g, float b){
    setRedUsingFloat(SGLFloatMath::aToThePowerOfB(r, 1.0f / 2.2f));
    setGreenUsingFloat(SGLFloatMath::aToThePowerOfB(g, 1.0f / 2.2f));
    setBlueUsingFloat(SGLFloatMath::aToThePowerOfB(b, 1.0f / 2.2f));
}

SGXColourRGBA& SGXColourRGBA::linearTransformRedWithGamma(float m, float c){
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    gammaCorrectBegin(r, g, b);
    r = m * r + c;
    gammaCorrectEnd(r, g, b);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::linearTransformGreenWithGamma(float m, float c){
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    gammaCorrectBegin(r, g, b);
    g = m * g + c;
    gammaCorrectEnd(r, g, b);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::linearTransformBlueWithGamma(float m, float c){
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    gammaCorrectBegin(r, g, b);
    b = m * b + c;
    gammaCorrectEnd(r, g, b);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::applyTint(SGXColourRGBA x){
    float r1 = 0.0f;
    float g1 = 0.0f;
    float b1 = 0.0f;
    float r2 = 0.0f;
    float g2 = 0.0f;
    float b2 = 0.0f;
    gammaCorrectBegin(r1, g1, b1);
    x.gammaCorrectBegin(r2, g2, b2);
    const float a2 = x.getTransparencyAsFloat();
    const float a1 = 1.0f - a2;
    r1 = r1 * a1 + r2 * a2;
    g1 = g1 * a1 + g2 * a2;
    b1 = b1 * a1 + b2 * a2;
    gammaCorrectEnd(r1, g1, b1);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::applyTintSeparateTransparency(SGXColourRGBA x, int a){
    float r1 = 0.0f;
    float g1 = 0.0f;
    float b1 = 0.0f;
    float r2 = 0.0f;
    float g2 = 0.0f;
    float b2 = 0.0f;
    gammaCorrectBegin(r1, g1, b1);
    x.gammaCorrectBegin(r2, g2, b2);
    const float a2 = static_cast<float>(a) / 255.0f;
    const float a1 = 1.0f - a2;
    r1 = r1 * a1 + r2 * a2;
    g1 = g1 * a1 + g2 * a2;
    b1 = b1 * a1 + b2 * a2;
    gammaCorrectEnd(r1, g1, b1);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::applyTintSeparateTransparencyUsingFloat(SGXColourRGBA x, float a){
    float r1 = 0.0f;
    float g1 = 0.0f;
    float b1 = 0.0f;
    float r2 = 0.0f;
    float g2 = 0.0f;
    float b2 = 0.0f;
    gammaCorrectBegin(r1, g1, b1);
    x.gammaCorrectBegin(r2, g2, b2);
    const float a2 = a;
    const float a1 = 1.0f - a2;
    r1 = r1 * a1 + r2 * a2;
    g1 = g1 * a1 + g2 * a2;
    b1 = b1 * a1 + b2 * a2;
    gammaCorrectEnd(r1, g1, b1);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::applyTintNoGammaCorrection(SGXColourRGBA x){
    float r1 = getRedAsFloat();
    float g1 = getGreenAsFloat();
    float b1 = getBlueAsFloat();
    const float r2 = x.getRedAsFloat();
    const float g2 = x.getGreenAsFloat();
    const float b2 = x.getBlueAsFloat();
    const float a2 = x.getTransparencyAsFloat();
    const float a1 = 1.0f - a2;
    r1 = r1 * a1 + r2 * a2;
    g1 = g1 * a1 + g2 * a2;
    b1 = b1 * a1 + b2 * a2;
    setRedUsingFloat(r1);
    setGreenUsingFloat(g1);
    setBlueUsingFloat(b1);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::applyTintNoGammaCorrectionSeparateTransparency(SGXColourRGBA x, int a){
    float r1 = getRedAsFloat();
    float g1 = getGreenAsFloat();
    float b1 = getBlueAsFloat();
    const float r2 = x.getRedAsFloat();
    const float g2 = x.getGreenAsFloat();
    const float b2 = x.getBlueAsFloat();
    const float a2 = static_cast<float>(a) / 255.0f;
    const float a1 = 1.0f - a2;
    r1 = r1 * a1 + r2 * a2;
    g1 = g1 * a1 + g2 * a2;
    b1 = b1 * a1 + b2 * a2;
    setRedUsingFloat(r1);
    setGreenUsingFloat(g1);
    setBlueUsingFloat(b1);
    return (*this);
}

SGXColourRGBA& SGXColourRGBA::applyTintNoGammaCorrectionSeparateTransparencyUsingFloat(SGXColourRGBA x, float a){
    float r1 = getRedAsFloat();
    float g1 = getGreenAsFloat();
    float b1 = getBlueAsFloat();
    const float r2 = x.getRedAsFloat();
    const float g2 = x.getGreenAsFloat();
    const float b2 = x.getBlueAsFloat();
    const float a2 = a;
    const float a1 = 1.0f - a2;
    r1 = r1 * a1 + r2 * a2;
    g1 = g1 * a1 + g2 * a2;
    b1 = b1 * a1 + b2 * a2;
    setRedUsingFloat(r1);
    setGreenUsingFloat(g1);
    setBlueUsingFloat(b1);
    return (*this);
}

SGXColourRGBA SGXColourRGBA::linearInterpolate(SGXColourRGBA x, float f) const {
    const float a1 = f;
    const float a2 = 1.0f - f;
    const float r1 = getRedAsFloat();
    const float g1 = getGreenAsFloat();
    const float b1 = getBlueAsFloat();
    float r2 = x.getRedAsFloat();
    float g2 = x.getGreenAsFloat();
    float b2 = x.getBlueAsFloat();
    r2 = r1 * a1 + r2 * a2;
    g2 = g1 * a1 + g2 * a2;
    b2 = b1 * a1 + b2 * a2;
    x.setRedUsingFloat(r2);
    x.setGreenUsingFloat(g2);
    x.setBlueUsingFloat(b2);
    x.setTransparencyUsingFloat(getTransparencyAsFloat());
    return x;
}

SGXColourRGBA SGXColourRGBA::linearInterpolateGammaCorrection(SGXColourRGBA x, float f) const {
    const float a1 = f;
    const float a2 = 1.0f - f;
    float r1 = 0.0f;
    float g1 = 0.0f;
    float b1 = 0.0f;
    gammaCorrectBegin(r1, g1, b1);
    float r2 = 0.0f;
    float g2 = 0.0f;
    float b2 = 0.0f;
    x.gammaCorrectBegin(r2, g2, b2);
    r2 = r1 * a1 + r2 * a2;
    g2 = g1 * a1 + g2 * a2;
    b2 = b1 * a1 + b2 * a2;
    x.gammaCorrectEnd(r2, g2, b2);
    x.setTransparencyUsingFloat(getTransparencyAsFloat());
    return x;
}

SGXColourRGBA& SGXColourRGBA::toComplementColour(){
    setRed(255 - getRed());
    setGreen(255 - getGreen());
    setBlue(255 - getBlue());
    return (*this);
}
