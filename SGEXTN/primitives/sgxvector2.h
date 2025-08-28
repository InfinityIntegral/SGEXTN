#ifndef SGXVECTOR2_H
#define SGXVECTOR2_H

#include <QString>

class SGXVector2
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
    [[nodiscard]] QString getStringForPrinting() const;
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
    void normalise();
    void normaliseGivenMagnitude(float m);
    [[nodiscard]] float getDistance(SGXVector2 x) const;
    [[nodiscard]] float getDistanceSquare(SGXVector2 x) const;
    [[nodiscard]] float getArgument() const;
    [[nodiscard]] float getAngleBetween(SGXVector2 x) const;
    void redirectUsingArgument(float a);
    void invert();
    void rotateClockwise90();
    void rotateCounterclockwise90();
    void rotate180();
    void rotateClockwise(float a);
    void rotateCounterclockwise(float a);
    [[nodiscard]] bool isCollinear(SGXVector2 a, SGXVector2 b, float limit = 1.0f) const;
    [[nodiscard]] bool isParallel(SGXVector2 a2, SGXVector2 b1, SGXVector2 b2, float limit = 1.0f) const;
    [[nodiscard]] bool isPerpendicular(SGXVector2 a, SGXVector2 b, float limit = 1.0f) const;
    [[nodiscard]] SGXVector2 midpoint(SGXVector2 x) const;
    [[nodiscard]] SGXVector2 linearInterpolate(SGXVector2 x, float f) const;
    void reflectAcrossX();
    void reflectAcrossY();
    void reflectAcrossPoint(SGXVector2 x);
    void reflectAcrossLine(SGXVector2 a, SGXVector2 b);
    void projectToX();
    void projectToY();
    void projectToLine(SGXVector2 a, SGXVector2 b);
    [[nodiscard]] float getDistanceToLine(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] float getDistanceToSegment(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] float getDistanceToCircle(float a, float b, float r) const;
    [[nodiscard]] SGXVector2 getNearestPointOnLine(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] SGXVector2 getNearestPointOnSegment(SGXVector2 a, SGXVector2 b) const;
    [[nodiscard]] SGXVector2 getNearestPointOnCircle(float a, float b, float r) const;
    [[nodiscard]] float dotProduct(SGXVector2 x) const;
    [[nodiscard]] float crossProduct(SGXVector2 x) const;
};

inline unsigned int qHash(SGXVector2 x, unsigned int seed = 0){
    return (static_cast<unsigned int>(x.x) ^ static_cast<unsigned int>(x.y) ^ seed);
}

#endif // SGXVECTOR2_H
