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
    return std::sqrt(getMagnitudeSquare());
}

float SGXVector2::getDistanceSquare(SGXVector2 x) const {
    return (((*this).x - x.x) * ((*this).x - x.x) + ((*this).y - x.y) * ((*this).y - x.y));
}

float SGXVector2::getDistance(SGXVector2 x) const {
    return std::sqrt(getDistanceSquare(x));
}

void SGXVector2::normalise(){
    (*this) /= getMagnitude();
}

void SGXVector2::normaliseGivenMagnitude(float m){
    (*this) /= (getMagnitude() / m);
}
