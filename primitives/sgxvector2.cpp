#include "sgxvector2.h"
#include <cmath>

SGXVector2::SGXVector2(float x, float y){
    (*this).x = x;
    (*this).y = y;
}

bool SGXVector2::operator==(SGXVector2 x) const {
    return (((*this).x == x.x) && ((*this).y == x.y));
}

bool SGXVector2::operator!=(SGXVector2 x) const {
    return (((*this).x != x.x) || ((*this).y != x.y));
}

bool SGXVector2::operator<(SGXVector2 x) const {
    if((*this).x != x.x){return ((*this).x < x.x);}
    return ((*this).y < x.y);
}

QString SGXVector2::getStringForPrinting() const {
    return ("(" + QString::number(x) + ", " + QString::number(y) + ")");
}

SGXVector2 SGXVector2::operator+(SGXVector2 x) const {
    return SGXVector2((*this).x + x.x, (*this).y + x.y);
}

SGXVector2 SGXVector2::operator-(SGXVector2 x) const {
    return SGXVector2((*this).x - x.x, (*this).y - x.y);
}

SGXVector2 SGXVector2::operator*(float m) const {
    return SGXVector2(m * x, m * y);
}

SGXVector2 operator*(float m, SGXVector2 x){
    return SGXVector2(m * x.x, m * x.y);
}

SGXVector2 SGXVector2::operator/(float m) const {
    return SGXVector2(x / m, y / m);
}

SGXVector2& SGXVector2::operator+=(SGXVector2 x){
    (*this).x += x.x;
    (*this).y += x.y;
    return (*this);
}

SGXVector2& SGXVector2::operator-=(SGXVector2 x){
    (*this).x -= x.x;
    (*this).y -= x.y;
    return (*this);
}

SGXVector2& SGXVector2::operator*=(float m){
    x *= m;
    y *= m;
    return (*this);
}

SGXVector2& SGXVector2::operator/=(float m){
    x /= m;
    y /= m;
    return (*this);
}

float SGXVector2::getMagnitudeSquare() const {
    return (x * x + y * y);
}

float SGXVector2::getMagnitude() const {
    return std::sqrtf(getMagnitudeSquare());
}

float SGXVector2::getDistanceSquare(SGXVector2 x) const {
    return (((*this).x - x.x) * ((*this).x - x.x) + ((*this).y - x.y) * ((*this).y - x.y));
}

float SGXVector2::getDistance(SGXVector2 x) const {
    return std::sqrtf(getDistanceSquare(x));
}

void SGXVector2::normalise(){
    (*this) /= getMagnitude();
}

void SGXVector2::normaliseGivenMagnitude(float m){
    (*this) /= (getMagnitude() / m);
}

float SGXVector2::getArgument() const {
    return (std::atan2f(y, x) * 180.0f / 3.14159265358979f);
}

float SGXVector2::getAngleBetween(SGXVector2 x) const {
    float f = x.getArgument() - getArgument();
    f = std::fmodf(f, 360.0f);
    if(f <= -180.0f){f += 360.0f;}
    else if(f > 180.0f){f -= 360.0f;}
    return f;
}

void SGXVector2::redirectUsingArgument(float a){
    const float m = getMagnitude();
    x = std::cosf(a);
    y = std::sinf(a);
    (*this) *= m;
}
