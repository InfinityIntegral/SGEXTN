#include <SGXVector2.h>
#include <SGXString.h>
#include <SGLHash.h>
#include <SGLSpan.h>
#include <SGLArray.h>
#include <SGLHashAlgorithm.h>
#include <SGLFloatConstants.h>
#include <SGLFloatMath.h>

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

bool SGXVector2::operator>(SGXVector2 x) const {
    if((*this).x != x.x){return ((*this).x > x.x);}
    return ((*this).y > x.y);
}

int SGXVector2::hash() const {
    SGLArray<int> hashArray(2);
    hashArray.at(0) = SGLHash<float>()(x);
    hashArray.at(1) = SGLHash<float>()(y);
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 2 * sizeof(int)));
}

SGXString SGXVector2::getStringForPrinting() const {
    return (SGXString("(") + SGXString::floatToString(x) + ", " + SGXString::floatToString(y) + ")");
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
    return SGLFloatMath::squareRoot(getMagnitudeSquare());
}

float SGXVector2::getDistanceSquare(SGXVector2 a, SGXVector2 b){
    return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

float SGXVector2::getDistance(SGXVector2 a, SGXVector2 b){
    return SGLFloatMath::squareRoot(SGXVector2::getDistanceSquare(a, b));
}

SGXVector2& SGXVector2::normalise(){
    (*this) /= getMagnitude();
    return (*this);
}

SGXVector2& SGXVector2::normaliseGivenMagnitude(float m){
    (*this) /= (getMagnitude() / m);
    return (*this);
}

float SGXVector2::getArgument() const {
    return (SGLFloatMath::arctangentQuadrantAware(y, x) * 180.0f / SGLFloatConstants::pi());
}

float SGXVector2::getAngleBetween(SGXVector2 a, SGXVector2 b){
    float f = b.getArgument() - a.getArgument();
    f = SGLFloatMath::modulo(f, 360.0f);
    if(f <= -180.0f){f += 360.0f;}
    else if(f > 180.0f){f -= 360.0f;}
    return f;
}

SGXVector2& SGXVector2::redirectUsingArgument(float a){
    const float m = getMagnitude();
    a *= (SGLFloatConstants::pi() / 180.0f);
    x = SGLFloatMath::cosine(a);
    y = SGLFloatMath::sine(a);
    (*this) *= m;
    return (*this);
}

SGXVector2& SGXVector2::invert(){
    (*this) *= (-1.0f);
    return (*this);
}

SGXVector2& SGXVector2::rotate180(){
    (*this) *= (-1.0f);
    return (*this);
}

SGXVector2& SGXVector2::rotateCounterclockwise90(){
    (*this) = SGXVector2((-1.0f) * y, x);
    return (*this);
}

SGXVector2& SGXVector2::rotateClockwise90(){
    (*this) = SGXVector2(y, (-1.0f) * x);
    return (*this);
}

SGXVector2& SGXVector2::rotateCounterclockwise(float a){
    a *= (SGLFloatConstants::pi() / 180.0f);
    (*this) = SGXVector2(x * SGLFloatMath::cosine(a) - y * SGLFloatMath::sine(a), x * SGLFloatMath::sine(a) + y * SGLFloatMath::cosine(a));
    return (*this);
}

SGXVector2& SGXVector2::rotateClockwise(float a){
    a *= (SGLFloatConstants::pi() / 180.0f);
    (*this) = SGXVector2(x * SGLFloatMath::cosine(a) + y * SGLFloatMath::sine(a), (-1.0f) * x * SGLFloatMath::sine(a) + y * SGLFloatMath::cosine(a));
    return (*this);
}

bool SGXVector2::isCollinear(SGXVector2 x, SGXVector2 a, SGXVector2 b, float limit){
    float arg = (a - x).getArgument() - (b - x).getArgument();
    arg = SGLFloatMath::modulo(arg, 180.0f);
    if(arg < -90.0f){arg += 180.0f;}
    else if(arg > 90.0f){arg -= 180.0f;}
    if(arg >= (-1.0f) * limit && arg <= limit){return true;}
    return false;
}

bool SGXVector2::isParallel(SGXVector2 a1, SGXVector2 a2, SGXVector2 b1, SGXVector2 b2, float limit){
    float arg = (a2 - a1).getArgument() - (b2 - b1).getArgument();
    arg = SGLFloatMath::modulo(arg, 180.0f);
    if(arg < -90.0f){arg += 180.0f;}
    else if(arg > 90.0f){arg -= 180.0f;}
    if(arg >= (-1.0f) * limit && arg <= limit){return true;}
    return false;
}

bool SGXVector2::isPerpendicular(SGXVector2 x, SGXVector2 a, SGXVector2 b, float limit){
    float arg = (a - x).getArgument() - (b - x).getArgument() + 90.0f;
    arg = SGLFloatMath::modulo(arg, 180.0f);
    if(arg < -90.0f){arg += 180.0f;}
    else if(arg > 90.0f){arg -= 180.0f;}
    if(arg >= (-1.0f) * limit && arg <= limit){return true;}
    return false;
}

SGXVector2 SGXVector2::midpoint(SGXVector2 a, SGXVector2 b){
    return (0.5f * (a + b));
}

SGXVector2 SGXVector2::linearInterpolate(SGXVector2 a, SGXVector2 b, float f){
    return (f * a + (1.0f - f) * b);
}

SGXVector2& SGXVector2::reflectAcrossX(){
    x *= (-1.0f);
    return (*this);
}

SGXVector2& SGXVector2::reflectAcrossY(){
    y *= (-1.0f);
    return (*this);
}

SGXVector2& SGXVector2::reflectAcrossPoint(SGXVector2 x){
    (*this) = 2 * x - (*this);
    return (*this);
}

SGXVector2 SGXVector2::getNearestPointOnLine(SGXVector2 a, SGXVector2 b) const {
    const float f = ((x - a.x) * (b.x - a.x) + (y - a.y) * (b.y - a.y)) / SGXVector2::getDistanceSquare(a, b);
    return SGXVector2(a.x + f * (b.x - a.x), a.y + f * (b.y - a.y));
}

SGXVector2& SGXVector2::projectToLine(SGXVector2 a, SGXVector2 b){
    const float f = ((x - a.x) * (b.x - a.x) + (y - a.y) * (b.y - a.y)) / SGXVector2::getDistanceSquare(a, b);
    (*this) = SGXVector2(a.x + f * (b.x - a.x), a.y + f * (b.y - a.y));
    return (*this);
}

SGXVector2& SGXVector2::reflectAcrossLine(SGXVector2 a, SGXVector2 b){
    reflectAcrossPoint(getNearestPointOnLine(a, b));
    return (*this);
}

SGXVector2& SGXVector2::projectToX(){
    y = 0;
    return (*this);
}

SGXVector2& SGXVector2::projectToY(){
    x = 0;
    return (*this);
}

float SGXVector2::getDistanceToLine(SGXVector2 a, SGXVector2 b) const {
    return SGXVector2::getDistance((*this), getNearestPointOnLine(a, b));
}

float SGXVector2::getDistanceToSegment(SGXVector2 a, SGXVector2 b) const {
    const SGXVector2 v = getNearestPointOnLine(a, b);
    if(temp_isBetween(v.x, a.x, b.x) || temp_isBetween(v.y, a.y, b.y)){return SGXVector2::getDistance((*this), v);}
    if(SGXVector2::getDistanceSquare((*this), a) < SGXVector2::getDistanceSquare((*this), b)){return SGXVector2::getDistance((*this), a);}
    return SGXVector2::getDistance((*this), b);
}

float SGXVector2::getDistanceToCircle(float a, float b, float r) const {
    SGXVector2 v = (*this);
    v -= SGXVector2(a, b);
    return v.getMagnitude() - r;
}

SGXVector2 SGXVector2::getNearestPointOnSegment(SGXVector2 a, SGXVector2 b) const {
    SGXVector2 v = getNearestPointOnLine(a, b);
    if(temp_isBetween(v.x, a.x, b.x) || temp_isBetween(v.y, a.y, b.y)){return v;}
    if(SGXVector2::getDistanceSquare((*this), a) <= SGXVector2::getDistanceSquare((*this), b)){return a;}
    return b;
}

SGXVector2 SGXVector2::getNearestPointOnCircle(float a, float b, float r) const {
    SGXVector2 v = ((*this) - SGXVector2(a, b));
    v.normaliseGivenMagnitude(r);
    return (v + SGXVector2(a, b));
}

float SGXVector2::dotProduct(SGXVector2 a, SGXVector2 b){
    return (a.x * b.x + a.y * b.y);
}

float SGXVector2::crossProduct(SGXVector2 a, SGXVector2 b){
    return (a.x * b.y + a.y * b.x);
}
