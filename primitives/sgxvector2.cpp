#include "sgxvector2.h"
#include <cmath>

SGXVector2::SGXVector2(float x, float y){
    (*this).x = x;
    (*this).y = y;
}

SGXVector2 SGXVector2::origin = SGXVector2(0.0f, 0.0f);

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
    a *= (3.14159265358979f / 180.0f);
    x = std::cosf(a);
    y = std::sinf(a);
    (*this) *= m;
}

void SGXVector2::invert(){
    (*this) *= (-1.0f);
}

void SGXVector2::rotate180(){
    (*this) *= (-1.0f);
}

void SGXVector2::rotateCounterclockwise90(){
    (*this) = SGXVector2((-1.0f) * y, x);
}

void SGXVector2::rotateClockwise90(){
    (*this) = SGXVector2(y, (-1.0f) * x);
}

void SGXVector2::rotateCounterclockwise(float a){
    a *= (3.14159265358979f / 180.0f);
    (*this) = SGXVector2(x * std::cosf(a) - y * std::sinf(a), x * std::sinf(a) + y * std::cosf(a));
}

void SGXVector2::rotateClockwise(float a){
    a *= (3.14159265358979f / 180.0f);
    (*this) = SGXVector2(x * std::cosf(a) + y * std::sinf(a), (-1.0f) * x * std::sinf(a) + y * std::cosf(a));
}

bool SGXVector2::isCollinear(SGXVector2 a, SGXVector2 b, float limit) const {
    float arg = (a - (*this)).getArgument() - (b - (*this)).getArgument();
    arg = std::fmodf(arg, 180.0f);
    if(arg < -90.0f){arg += 180.0f;}
    else if(arg > 90.0f){arg -= 180.0f;}
    if(arg >= (-1.0f) * limit && arg <= limit){return true;}
    return false;
}

bool SGXVector2::isParallel(SGXVector2 a2, SGXVector2 b1, SGXVector2 b2, float limit) const {
    float arg = (a2 - (*this)).getArgument() - (b2 - b1).getArgument();
    arg = std::fmodf(arg, 180.0f);
    if(arg < -90.0f){arg += 180.0f;}
    else if(arg > 90.0f){arg -= 180.0f;}
    if(arg >= (-1.0f) * limit && arg <= limit){return true;}
    return false;
}

bool SGXVector2::isPerpendicular(SGXVector2 a, SGXVector2 b, float limit) const {
    float arg = (a - (*this)).getArgument() - (b - (*this)).getArgument() + 90.0f;
    arg = std::fmodf(arg, 180.0f);
    if(arg < -90.0f){arg += 180.0f;}
    else if(arg > 90.0f){arg -= 180.0f;}
    if(arg >= (-1.0f) * limit && arg <= limit){return true;}
    return false;
}

SGXVector2 SGXVector2::midpoint(SGXVector2 x) const {
    return (0.5f * ((*this) + x));
}

SGXVector2 SGXVector2::linearInterpolate(SGXVector2 x, float f) const {
    return (f * (*this) + (1.0f - f) * x);
}

void SGXVector2::reflectAcrossX(){
    x *= (-1.0f);
}

void SGXVector2::reflectAcrossY(){
    y *= (-1.0f);
}

void SGXVector2::reflectAcrossPoint(SGXVector2 x){
    (*this) = 2 * x - (*this);
}

void SGXVector2::reflectAcrossLine(float m, float c){
    return reflectAcrossPoint(SGXVector2((m * y + x - m * c) / (m * m + 1.0f), (m * m * y + m * x + c) / (m * m + 1.0f)));
}
