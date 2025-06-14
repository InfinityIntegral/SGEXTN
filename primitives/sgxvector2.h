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
    /*
method list:
- vector addition
- vector subtraction
- multiplication by constant
- division by constant
- arithmetic addition
- arithmetic subtraction
- arithmetic multiplication
- arithmetic division
- get magnitude
- get squared magnitude
- normalise
- normalise with given magnitude
- redirect using argument
- get argument
- get distance
- get squared distance
- get angle between
- invert
- rotate 90 clockwise
- rotate 90 counterclockwise
- rotate 180
- rotate clockwise
- rotate counterclockwise
- reflect across line
- reflect across point
- project to another vector
- floor function
- ceiling function
- round function
- floor with custom unit
- ceiling with custom unit
- round with custom unit
- distance to line
- distance to segment
- distance to circle
- get nearest point on line
- get nearest point on segment
- get nearest point on circle
- zero vector
- positive x unit vector
- positive y unit vector
- (1/sqrt2, 1/sqrt2)
- (1, 1)
- is collinear
- is parallel
- is perpendicular
- midpoint
- reflect across x
- reflect across y
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
