#ifndef SGXVECTOR2_H
#define SGXVECTOR2_H

#include <QString>
#include <bit>
#include <QDebug>

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
    void reflectAcrossLine(float x1, float y1, float x2, float y2);
    void projectToX();
    void projectToY();
    void projectToLine(float x1, float y1, float x2, float y2);
    [[nodiscard]] float getDistanceToLine(float x1, float y1, float x2, float y2) const;
    [[nodiscard]] float getDistanceToSegment(float x1, float y1, float x2, float y2) const;
    [[nodiscard]] float getDistanceToCircle(float a, float b, float r) const;
    [[nodiscard]] SGXVector2 getNearestPointOnLine(float x1, float y1, float x2, float y2) const;
    [[nodiscard]] SGXVector2 getNearestPointOnSegment(float x1, float y1, float x2, float y2) const;
    [[nodiscard]] SGXVector2 getNearestPointOnCircle(float a, float b, float r) const;
};

inline unsigned int qHash(SGXVector2 x, unsigned int seed = 0){
    return (std::bit_cast<unsigned int>(x.x) ^ std::bit_cast<unsigned int>(x.y) ^ seed);
}

inline QDebug operator<<(QDebug s, SGXVector2 x){
    s << x.getStringForPrinting();
    return s;
}

#endif // SGXVECTOR2_H
