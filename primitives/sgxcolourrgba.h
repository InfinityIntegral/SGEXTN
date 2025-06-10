#ifndef SGXCOLOURRGBA_H
#define SGXCOLOURRGBA_H

class SGXColourRGBA // stores unsigned int with each 8 bits being a colour channel in format RGBA
{
public:
    unsigned int x; // raw byte data
    SGXColourRGBA(unsigned int x0); // constructs a SGXColourRGBA from raw byte data x
    SGXColourRGBA(int r, int g, int b, int a); // constructs a SGXColourRGBA using int values for channels RGBA between 0 and 255 inclusive
    SGXColourRGBA(int r, int g, int b); // constructs a SGXColourRGBA using int values for channels RGB between 0 and 255 inclusive, transparency is set to 255 by default
    SGXColourRGBA(float r, float g, float b, float a); // constructs a SGXColourRGBA using float values for channels RGBA between 0 and 1 inclusive
    SGXColourRGBA(float r, float g, float b);
    // MAKE THIS LEH: constructor from SGXColourHSLA
    /*
methods list:
- get r
- get g
- get b
- get a
- to RGB string
- to RGBA string
- to RGB hex string
- to RGBA hex string
- equality check
- inequality check
- add colours (average with gamma)
- subtract (add inverse)
- add arithmetic
- subtract arithmetic
- multiply by constant arithmetic
- multiply by constant
- linear transform r
- linear transform g
- linear transform b
- linear transform a
- apply tint
- apply tint with separate transparency
- linear interpolation
- invert
    */
};

#endif // SGXCOLOURRGBA_H
