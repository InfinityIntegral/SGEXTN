#ifndef SGXVECTOR2_H
#define SGXVECTOR2_H

#include <QString>
#include <bit>
#include <QDebug>

class SGXVector2 // stores 2 dimensional coordinates that can mean the vector from the origin to the point or just the point itself, depending on context
{
public:
    float x; // x coordinate
    float y; // y coordinate
    SGXVector2(float x, float y); // constructs a SGXVector2 from component coordinates
    static SGXVector2 origin; // zero vector
    [[nodiscard]] bool operator==(SGXVector2 x) const; // equality comparator by comparing coordinates not struct instance memory location
    [[nodiscard]] bool operator!=(SGXVector2 x) const; // inequality comparator by comparing coordinates not struct instance memory location
    [[nodiscard]] bool operator<(SGXVector2 x) const; // < comparator for use in sorted data structures
    [[nodiscard]] QString getStringForPrinting() const; // generate string to print out
    [[nodiscard]] SGXVector2 operator+(SGXVector2 x) const; // vector addition
    [[nodiscard]] SGXVector2 operator-(SGXVector2 x) const; // vector subtraction
    [[nodiscard]] SGXVector2 operator*(float m) const; // multiplication of vector by constant
    friend SGXVector2 operator*(float m, SGXVector2 x); // multiplication of vector by constant
    [[nodiscard]] SGXVector2 operator/(float m) const; // division of vector by constant
    SGXVector2& operator+=(SGXVector2 x); // vector addition followed by assignment to original vector
    SGXVector2& operator-=(SGXVector2 x); // vector subtraction followed by assignment to original vector
    SGXVector2& operator*=(float m); // multiplication of vector by constant followed by assignment to original vector
    SGXVector2& operator/=(float m); // division of vector by constant followed by assignment to original vector
    [[nodiscard]] float getMagnitude() const; // compute magnitude of the vector, or distance from the origin to the endpoint
    [[nodiscard]] float getMagnitudeSquare() const; // compute the square of the magnitude, which is the distance from the origin to the endpoint, to avoid slow square root function
    void normalise(); // set the magnitude of the vector to 1 without changing its direction
    void normaliseGivenMagnitude(float m); // set the magnitude of the vector to m without changing its direction
    [[nodiscard]] float getDistance(SGXVector2 x) const; // compute distance between endpoints of the 2 vectors
    [[nodiscard]] float getDistanceSquare(SGXVector2 x) const; // compute squared distance between endpoints of the 2 vectors to avoid slow square root function
    [[nodiscard]] float getArgument() const; // compute argument of vector, that is the angle to rotate in degrees counterclockwise from the positive x direction to reach the direction in which the vector is pointing at
    [[nodiscard]] float getAngleBetween(SGXVector2 x) const; // compute the angle to rotate in degrees counterclockwise from this vector to reach the direction in which x is pointing at
    void redirectUsingArgument(float a); // change the direction of the vector to have argument a without changing its magnitude, where argument is the angle to rotate in degrees counterclockwise from the positive x direction to reach the direction in which the vector is pointing at
    void invert(); // invert the direction of the vector, equivalent to multiplying by -1 or rotating 180 degrees
    void rotateClockwise90(); // rotate vector clockwise by 90 degrees
    void rotateCounterclockwise90(); // rotate vector counterclockwise by 90 degrees
    void rotate180(); // rotate vector by 180 degrees in either direction, equivalent to inverting it
    void rotateClockwise(float a); // rotate vector clockwise by a degrees
    void rotateCounterclockwise(float a); // rotate vector counterclockwise by a degrees
    [[nodiscard]] bool isCollinear(SGXVector2 a, SGXVector2 b, float limit = 1.0f) const; // supposing X is the endpoint of this vector, A is the endpoint of a, and B is the endpoint of b, this function computes if A, X, B are collinear, where limit is the maximum number of degrees that angle AXB can deviate from 0 or 180
    [[nodiscard]] bool isParallel(SGXVector2 a2, SGXVector2 b1, SGXVector2 b2, float limit = 1.0f) const; // supposing A1 is the endpoint of this vector, A2 is the endpoint of a2, B1 is the endpoint of b1, and B2 is the endpoint of b2, this function computes if A1A1 and B1B2 are parallel, where limit is the maximum number of degrees allowed for the angle between the x axis and each line
    [[nodiscard]] bool isPerpendicular(SGXVector2 a, SGXVector2 b, float limit = 1.0f) const; // supposing X is the endpoint of this vector, A is the endpoint of a, and B is the endpoint of b, this function computes if A, X, B are perpendicular, where limit is the maximum number of degrees that angle AXB can deviate from 90
    [[nodiscard]] SGXVector2 midpoint(SGXVector2 x) const; // computes the midpoint between the endpoints of this vector and x
    [[nodiscard]] SGXVector2 linearInterpolate(SGXVector2 x, float f) const; // computes the point f of the way from the endpoint of this vector to the endpoint of x, f can be below 0 or above 1
    void reflectAcrossX(); // reflects this vector across x axis
    void reflectAcrossY(); // reflects this vector across y axis
    void reflectAcrossPoint(SGXVector2 x); // compute position of endpoint of this vector after it has been reflected across the endpoint of x and set it as the new endpoint
    void reflectAcrossLine(float x1, float y1, float x2, float y2); // compute position of endpoint of this vector after it has been reflected across the line passing through (x1, y1) and (x2, y2) and set it as the new endpoint
    void projectToX(); // compute position of endpoint of this vector when projected onto the x axis and set it as the new endpoint
    void projectToY(); // compute position of endpoint of this vector when projected onto the y axis and set it as the new endpoint
    void projectToLine(float x1, float y1, float x2, float y2); // compute position of endpoint of this vector when projected onto the line passing through (x1, y1) and (x2, y2) and set it as the new endpoint
    [[nodiscard]] float getDistanceToLine(float x1, float y1, float x2, float y2) const; // compute distance from endpoint of this vector to the line passing through (x1, y1) and (x2, y2)
    [[nodiscard]] float getDistanceToSegment(float x1, float y1, float x2, float y2) const; // compute distance from endpoint of this vector to the segment formed by joining (x1, y1) with (x2, y2)
    [[nodiscard]] float getDistanceToCircle(float a, float b, float r) const; // compute distance from endpoint of this vector to the circle (x - a)^2 + (y - b)^2 = r^2, returns negative of the distance to the circle's circumference if the endpoint is inside the circle
    /*
method list:
- get nearest point on line
- get nearest point on segment
- get nearest point on circle
    */
};

inline unsigned int qHash(SGXVector2 x, unsigned int seed = 0){
    return (std::bit_cast<unsigned int>(x.x) ^ std::bit_cast<unsigned int>(x.y) ^ seed);
}

inline QDebug operator<<(QDebug s, SGXVector2 x){
    s << x.getStringForPrinting();
    return s;
}

#endif // SGXVECTOR2_H
