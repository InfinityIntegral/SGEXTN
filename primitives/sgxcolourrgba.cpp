#include "sgxcolourrgba.h"
#include <cmath>

namespace{
inline void temp_boundInt(int& x){
    if(x < 0){x = 0;}
    else if(x > 255){x = 255;}
}

inline int temp_boundFloatIntoInt(float x){
    if(x < 0.0f){x = 0.0f;}
    else if(x > 255.0f){x = 255.0f;}
    return static_cast<int>(std::round(x));
}

inline void temp_boundFloat(float& x){
    if(x < 0.0f){x = 0.0f;}
    else if(x > 1.0f){x = 1.0f;}
}

inline unsigned int temp_floatToUnsignedInt(float x){
    const int x0 = static_cast<int>(std::round(255.0f * x));
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

void SGXColourRGBA::setRed(int r){
    temp_boundInt(r);
    (*this).x = ((*this).x & 0xFFFFFFu) | (static_cast<unsigned int>(r) << 24u);
}

void SGXColourRGBA::setGreen(int g){
    temp_boundInt(g);
    (*this).x = ((*this).x & 0xFF00FFFFu) | (static_cast<unsigned int>(g) << 16u);
}

void SGXColourRGBA::setBlue(int b){
    temp_boundInt(b);
    (*this).x = ((*this).x & 0xFFFF00FFu) | (static_cast<unsigned int>(b) << 8u);
}

void SGXColourRGBA::setTransparency(int a){
    temp_boundInt(a);
    (*this).x = ((*this).x & 0xFFFFFF00u) | static_cast<unsigned int>(a);
}

void SGXColourRGBA::setRedUsingFloat(float r){
    temp_boundFloat(r);
    (*this).x = ((*this).x & 0xFFFFFFu) | (temp_floatToUnsignedInt(r) << 24u);
}

void SGXColourRGBA::setGreenUsingFloat(float g){
    temp_boundFloat(g);
    (*this).x = ((*this).x & 0xFF00FFFFu) | (temp_floatToUnsignedInt(g) << 16u);
}

void SGXColourRGBA::setBlueUsingFloat(float b){
    temp_boundFloat(b);
    (*this).x = ((*this).x & 0xFFFF00FFu) | (temp_floatToUnsignedInt(b) << 8u);
}

void SGXColourRGBA::setTransparencyUsingFloat(float a){
    temp_boundFloat(a);
    (*this).x = ((*this).x & 0xFFFFFF00u) | temp_floatToUnsignedInt(a);
}

QString SGXColourRGBA::getStringForPrintingRGBHTML() const {
    return ("rgb(" + QString::number(getRed()) + ", " + QString::number(getGreen()) + ", " + QString::number(getBlue()) + ")");
}

QString SGXColourRGBA::getStringForPrintingRGBAHTML() const {
    return ("rgb(" + QString::number(getRed()) + ", " + QString::number(getGreen()) + ", " + QString::number(getBlue()) + ", " + QString::number(getTransparency()) + ")");
}

QString SGXColourRGBA::getStringForPrintingRGBHex() const{
    return ("#" + QString::number(getRed(), 16).toUpper() + QString::number(getGreen(), 16).toUpper() + QString::number(getBlue(), 16).toUpper());
}

QString SGXColourRGBA::getStringForPrintingRGBAHex() const {
    return ("#" + QString::number(getRed(), 16).toUpper() + QString::number(getGreen(), 16).toUpper() + QString::number(getBlue(), 16).toUpper() + QString::number(getTransparency(), 16).toUpper());
}

QString SGXColourRGBA::getStringForPrintingRGBFloatHTML() const {
    return ("rgb(" + QString::number(getRedAsFloat()) + ", " + QString::number(getGreenAsFloat()) + ", " + QString::number(getBlueAsFloat()) + ")");
}

QString SGXColourRGBA::getStringForPrintingRGBAFloatHTML() const {
    return ("rgb(" + QString::number(getRedAsFloat()) + ", " + QString::number(getGreenAsFloat()) + ", " + QString::number(getBlueAsFloat()) + ", " + QString::number(getTransparencyAsFloat()) + ")");
}

bool SGXColourRGBA::operator==(SGXColourRGBA x) const {
    return ((*this).x == x.x);
}

bool SGXColourRGBA::operator!=(SGXColourRGBA x) const {
    return ((*this).x != x.x);
}

void SGXColourRGBA::linearTransformRed(float m, float c){
    float r = getRedAsFloat();
    r = m * r + c;
    setRedUsingFloat(r);
}

void SGXColourRGBA::linearTransformGreen(float m, float c){
    float g = getGreenAsFloat();
    g = m * g + c;
    setGreenUsingFloat(g);
}

void SGXColourRGBA::linearTransformBlue(float m, float c){
    float b = getBlueAsFloat();
    b = m * b + c;
    setBlueUsingFloat(b);
}

void SGXColourRGBA::linearTransformTransparency(float m, float c){
    float a = getTransparencyAsFloat();
    a = m * a + c;
    setTransparencyUsingFloat(a);
}

void SGXColourRGBA::gammaCorrectBegin(float &r, float &g, float &b) const {
    r = std::pow(getRedAsFloat(), 2.2f);
    g = std::pow(getGreenAsFloat(), 2.2f);
    b = std::pow(getBlueAsFloat(), 2.2f);
}

void SGXColourRGBA::gammaCorrectEnd(float r, float g, float b){
    setRedUsingFloat(std::pow(r, 1.0f / 2.2f));
    setGreenUsingFloat(std::pow(g, 1.0f / 2.2f));
    setBlueUsingFloat(std::pow(b, 1.0f / 2.2f));
}

void SGXColourRGBA::linearTransformRedWithGamma(float m, float c){
    float r = 0;
    float g = 0;
    float b = 0;
    gammaCorrectBegin(r, g, b);
    r = m * r + c;
    gammaCorrectEnd(r, g, b);
}

void SGXColourRGBA::linearTransformGreenWithGamma(float m, float c){
    float r = 0;
    float g = 0;
    float b = 0;
    gammaCorrectBegin(r, g, b);
    g = m * g + c;
    gammaCorrectEnd(r, g, b);
}

void SGXColourRGBA::linearTransformBlueWithGamma(float m, float c){
    float r = 0;
    float g = 0;
    float b = 0;
    gammaCorrectBegin(r, g, b);
    b = m * b + c;
    gammaCorrectEnd(r, g, b);
}
