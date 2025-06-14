#ifndef SGXVECTOR2_H
#define SGXVECTOR2_H

#include <QString>
#include <bit>
#include <QDebug>

class SGXVector2
{
public:
    float x; // x coordinate
    float y; // y coordinate
    SGXVector2(float x, float y); // constructs a SGXVector2 from component coordinates
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
    /*
method list:
- redirect using argument
- get argument
- get angle between

- invert
- rotate 90 clockwise
- rotate 90 counterclockwise
- rotate 180
- rotate clockwise
- rotate counterclockwise

- is collinear
- is parallel
- is perpendicular
- midpoint
- linear interpolation

- reflect across x
- reflect across y
- reflect across line
- reflect across point

- project to x
- project to y
- project to another vector

- distance to line
- distance to segment
- distance to circle

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
