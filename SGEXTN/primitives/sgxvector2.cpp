#include "sgxvector2.h"
#include <cmath>
#include <algorithm>
#include <numbers>

namespace{
inline bool temp_isBetween(float x, float a, float b){
    if(a <= b){
        if(x >= a && x <= b){return true;}
        return false;
    }
    if(x <= a && x >= b){return true;}
    return false;
}
}

SGXVector2::SGXVector2(float x, float y){
    (*this).x = x;
    (*this).y = y;
}

const SGXVector2 SGXVector2::origin = SGXVector2(0.0f, 0.0f);

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
    return (std::atan2f(y, x) * 180.0f / std::numbers::pi_v<float>);
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
    a *= (std::numbers::pi_v<float> / 180.0f);
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
    a *= (std::numbers::pi_v<float> / 180.0f);
    (*this) = SGXVector2(x * std::cosf(a) - y * std::sinf(a), x * std::sinf(a) + y * std::cosf(a));
}

void SGXVector2::rotateClockwise(float a){
    a *= (std::numbers::pi_v<float> / 180.0f);
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

SGXVector2 SGXVector2::getNearestPointOnLine(float x1, float y1, float x2, float y2) const {
    const float f = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return SGXVector2(x1 + f * (x2 - x1), y1 + f * (y2 - y1));
}

void SGXVector2::projectToLine(float x1, float y1, float x2, float y2){
    const float f = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    (*this) = SGXVector2(x1 + f * (x2 - x1), y1 + f * (y2 - y1));
}

void SGXVector2::reflectAcrossLine(float x1, float y1, float x2, float y2){
    reflectAcrossPoint(getNearestPointOnLine(x1, y1, x2, y2));
}

void SGXVector2::projectToX(){
    y = 0;
}

void SGXVector2::projectToY(){
    x = 0;
}

float SGXVector2::getDistanceToLine(float x1, float y1, float x2, float y2) const {
    return getDistance(getNearestPointOnLine(x1, y1, x2, y2));
}

float SGXVector2::getDistanceToSegment(float x1, float y1, float x2, float y2) const {
    const SGXVector2 v = getNearestPointOnLine(x1, y1, x2, y2);
    if(temp_isBetween(v.x, x1, x2) || temp_isBetween(v.y, y1, y2)){return getDistance(v);}
    return std::min(getDistance(SGXVector2(x1, y1)), getDistance(SGXVector2(x2, y2)));
}

float SGXVector2::getDistanceToCircle(float a, float b, float r) const {
    SGXVector2 v = (*this);
    v -= SGXVector2(a, b);
    return v.getMagnitude() - r; 
}

SGXVector2 SGXVector2::getNearestPointOnSegment(float x1, float y1, float x2, float y2) const {
    SGXVector2 v = getNearestPointOnLine(x1, y1, x2, y2);
    if(temp_isBetween(v.x, x1, x2) || temp_isBetween(v.y, y1, y2)){return v;}
    if(getDistanceSquare(SGXVector2(x1, y1)) <= getDistanceSquare(SGXVector2(x2, y2))){return SGXVector2(x1, y1);}
    return SGXVector2(x2, y2);
}

SGXVector2 SGXVector2::getNearestPointOnCircle(float a, float b, float r) const {
    SGXVector2 v = ((*this) - SGXVector2(a, b));
    v.normaliseGivenMagnitude(r);
    return (v + SGXVector2(a, b));
}
