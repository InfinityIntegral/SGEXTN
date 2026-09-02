/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN/Utilities/HslaColour.h>
#include <SGEXTN/Utilities/RgbaColour.h>
#include <SGEXTN/Math/FloatMath.h>
#include <SGEXTN/SingText/String.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

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

SGEXTN::Utilities::HslaColour::HslaColour() : hue_(313.0f), saturation_(100.0f), lightness_(50.0f), transparency_(100.0f) {}

SGEXTN::Utilities::HslaColour::HslaColour(SGEXTN::Utilities::RgbaColour x) : hue_(313.0f), saturation_(0.0f), lightness_(50.0f), transparency_(x.getTransparencyFloat() * 100.0f){
    const float r = x.getRedFloat();
    const float g = x.getGreenFloat();
    const float b = x.getBlueFloat();
    const float h = maximumOf3(r, g, b);
    const float l = minimumOf3(r, g, b);
    lightness_ = 0.5f * (l + h);
    if(l != h){
        const float d = h - l;
        if(lightness_ > 0.5f){saturation_ = d / (2.0f - h - l);}
        else{saturation_ = d / (h + l);}
        if(h == r){
            hue_ = (g - b) / d;
            if(g < b){hue_ += 6.0f;}
        }
        else if(h == g){hue_ = (b - r) / d + 2.0f;}
        else if(h == b){hue_ = (r - g) / d + 4.0f;}
        hue_ /= 6.0f;
    }
    hue_ *= 360.0f;
    saturation_ *= 100.0f;
    lightness_ *= 100.0f;
    hue_ = limitTo360(hue_);
    saturation_ = limitTo100(saturation_);
    lightness_ = limitTo100(lightness_);
}

SGEXTN::Utilities::HslaColour::HslaColour(float h, float s, float l) : hue_(limitTo360(h)), saturation_(limitTo100(s)), lightness_(limitTo100(l)), transparency_(100.0f) {}

SGEXTN::Utilities::HslaColour::HslaColour(float h, float s, float l, float a) : hue_(limitTo360(h)), saturation_(limitTo100(s)), lightness_(limitTo100(l)), transparency_(limitTo100(a)) {}

SGEXTN::SingText::String SGEXTN::Utilities::HslaColour::debugPrint() const {
    return SGEXTN::SingText::String("hsla(") + SGEXTN::SingText::String::stringFromFloat(hue_, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 0) + ", " + SGEXTN::SingText::String::stringFromFloat(saturation_, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 0) + ", " + SGEXTN::SingText::String::stringFromFloat(lightness_, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 0) + ", " + SGEXTN::SingText::String::stringFromFloat(transparency_, 10, SGEXTN::SingText::FloatPrecisionFormat::FractionalDigit, 0) + ")";
}

bool SGEXTN::Utilities::HslaColour::sendOut(SGEXTN::Utilities::HslaColour x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<float, float, float, float>::sendOut(x.hue_, x.saturation_, x.lightness_, x.transparency_, data);
}

bool SGEXTN::Utilities::HslaColour::sendIn(SGEXTN::Utilities::HslaColour& x, SGEXTN::Containers::Span<unsigned char> data){
    float h = 0.0f;
    float s = 0.0f;
    float l = 0.0f;
    float a = 0.0f;
    const bool isValid = SGEXTN::Containers::Serialise<float, float, float, float>::sendIn(h, s, l, a, data);
    if(isValid == false || h < 0.0f || h > 360.0f || s < 0.0f || s > 100.0f || l < 0.0f || l > 100.0f || a < 0.0f || a > 100.0f){return false;}
    x = SGEXTN::Utilities::HslaColour(h, s, l, a);
    return true;
}

int SGEXTN::Utilities::HslaColour::size(){
    return 16;
}

float SGEXTN::Utilities::HslaColour::getHue() const {
    return hue_;
}

float SGEXTN::Utilities::HslaColour::getSaturation() const {
    return saturation_;
}

float SGEXTN::Utilities::HslaColour::getLightness() const {
    return lightness_;
}

float SGEXTN::Utilities::HslaColour::getTransparency() const {
    return transparency_;
}

void SGEXTN::Utilities::HslaColour::setHue(float h){
    hue_ = limitTo360(h);
}

void SGEXTN::Utilities::HslaColour::setSaturation(float s){
    saturation_ = limitTo100(s);
}

void SGEXTN::Utilities::HslaColour::setLightness(float l){
    lightness_ = limitTo100(l);
}

void SGEXTN::Utilities::HslaColour::setTransparency(float a){
    transparency_ = limitTo100(a);
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::invertHue() const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setHue(hue_ + 180.0f);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::invertSaturation() const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setSaturation(100.0f - saturation_);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::invertLightness() const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setLightness(100.0f - lightness_);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::linearTransformSaturation(float m, float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setSaturation(m * saturation_ + c);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::linearTransformLightness(float m, float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setLightness(m * lightness_ + c);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::linearTransformTransparency(float m, float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setTransparency(m * transparency_ + c);
    return copy;
}

SGEXTN::Utilities::HslaColour SGEXTN::Utilities::HslaColour::offsetHue(float c) const {
    SGEXTN::Utilities::HslaColour copy = (*this);
    copy.setHue(hue_ + c);
    return copy;
}

SGEXTN::Utilities::RgbaColour SGEXTN::Utilities::HslaColour::toRGBA() const {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    const float xh = hue_ / 360.0f;
    const float xs = saturation_ / 100.0f;
    const float xl = lightness_ / 100.0f;
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
    return SGEXTN::Utilities::RgbaColour(r, g, b, transparency_ / 100.0f);
}
