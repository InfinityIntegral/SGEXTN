#ifndef SGXVECTOR2_H
#define SGXVECTOR2_H

#include <SGXString.h>

#include <private_api_Core/SG_Build_Core.h>

class SG_CORE_DLL SGXVector2
{
public:
    float x;
    float y;
    SGXVector2() = default;
    SGXVector2(float x, float y);
    static const SGXVector2 origin;
    [[nodiscard]] bool operator==(SGXVector2 x) const;
    [[nodiscard]] bool operator!=(SGXVector2 x) const;
    [[nodiscard]] bool operator<(SGXVector2 x) const;
    [[nodiscard]] bool operator>(SGXVector2 x) const;
    [[nodiscard]] int hash() const;
    [[nodiscard]] SGXString getStringForPrinting() const;
    [[nodiscard]] SGXVector2 operator+(SGXVector2 x) const;
    [[nodiscard]] SGXVector2 operator-(SGXVector2 x) const;
    [[nodiscard]] SGXVector2 operator*(float m) const;
    friend SGXVector2 operator*(float m, SGXVector2 x);
    [[nodiscard]] SGXVector2 operator/(float m) const;
    SGXVector2& operator+=(SGXVector2 x);
    SGXVector2& operator-=(SGXVector2 x);
    SGXVector2& operator*=(float m);
    SGXVector2& operator/=(float m);
    [[nodiscard]] float getMagnitude() const;
    [[nodiscard]] float getMagnitudeSquare() const;
    SGXVector2& normalise();
    SGXVector2& normaliseGivenMagnitude(float m);
    static float getDistance(SGXVector2 a, SGXVector2 b);
    static float getDistanceSquare(SGXVector2 a, SGXVector2 b);
    [[nodiscard]] float getArgument() const;
    static float getAngleBetween(SGXVector2 a, SGXVector2 b);
    SGXVector2& redirectUsingArgument(float a);
    SGXVector2& invert();
    SGXVector2& rotateClockwise90();
    SGXVector2& rotateCounterclockwise90();
    SGXVector2& rotate180();
    SGXVector2& rotateClockwise(float a);
    SGXVector2& rotateCounterclockwise(float a);
    static bool isCollinear(SGXVector2 x, SGXVector2 a, SGXVector2 b, float limit);
    static bool isParallel(SGXVector2 a1, SGXVector2 a2, SGXVector2 b1, SGXVector2 b2, float limit);
    static bool isPerpendicular(SGXVector2 x, SGXVector2 a, SGXVector2 b, float limit);
    static SGXVector2 midpoint(SGXVector2 a, SGXVector2 b);
    static SGXVector2 linearInterpolate(SGXVector2 a, SGXVector2 b, float f);
    SGXVector2& reflectAcrossX();
    SGXVector2& reflectAcrossY();
    SGXVector2& reflectAcrossPoint(SGXVector2 x);
    SGXVector2& reflectAcrossLine(SGXVector2 a, SGXVector2 b);
    SGXVector2& projectToX();
    SGXVector2& projectToY();
    SGXVector2& projectToLine(SGXVector2 a, SGXVector2 b);
    [[nodiscard]] float getDistanceToLine(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] float getDistanceToSegment(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] float getDistanceToCircle(float a, float b, float r) const;
    [[nodiscard]] SGXVector2 getNearestPointOnLine(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] SGXVector2 getNearestPointOnSegment(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] SGXVector2 getNearestPointOnCircle(float a, float b, float r) const;
    static float dotProduct(SGXVector2 a, SGXVector2 b);
    static float crossProduct(SGXVector2 a, SGXVector2 b);
};

#endif // SGXVECTOR2_H
