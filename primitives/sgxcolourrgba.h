#ifndef SGXCOLOURRGBA_H
#define SGXCOLOURRGBA_H

#include <QString>

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
    [[nodiscard]] int getRed() const; // retrieve red component as int between 0 and 255 inclusive
    [[nodiscard]] int getGreen() const; // retrieve green component as int between 0 and 255 inclusive
    [[nodiscard]] int getBlue() const; // retrieve blue component as int between 0 and 255 inclusive
    [[nodiscard]] int getTransparency() const; // retrieve transparency component as int between 0 and 255 inclusive
    [[nodiscard]] float getRedAsFloat() const; // retrieve red component as float between 0 and 1 inclusive
    [[nodiscard]] float getGreenAsFloat() const; // retrieve green component as float between 0 and 1 inclusive
    [[nodiscard]] float getBlueAsFloat() const; // retrieve blue component as float between 0 and 1 inclusive
    [[nodiscard]] float getTransparencyAsFloat() const; // retrieve transparency component as float between 0    and 1 inclusive
    void setRed(int r); // modify red component using int between 0 and 255 inclusive
    void setGreen(int g); // modify green component using int between 0 and 255 inclusive
    void setBlue(int b); // modify blue component using int between 0 and 255 inclusive
    void setTransparency(int a); // modify transparency component using int between 0 and 255 inclusive
    void setRedUsingFloat(float r); // modify red component using float between 0 and 1 inclusive
    void setGreenUsingFloat(float g); // modify green component using float between 0 and 1 inclusive
    void setBlueUsingFloat(float b); // modify blue component using float between 0 and 1 inclusive
    void setTransparencyUsingFloat(float a); // modify transparency component using float between 0 and 1 inclusive
    [[nodiscard]] QString getStringForPrintingRGBHTML() const; // generate HTML style string for debugging using int values between 0 and 255 inclusive, ignores transparency
    [[nodiscard]] QString getStringForPrintingRGBAHTML() const; // generate HTML style string for debugging using int values between 0 and 255 inclusive
    [[nodiscard]] QString getStringForPrintingRGBHex() const; // generate hex code string, ignores transparency
    [[nodiscard]] QString getStringForPrintingRGBAHex() const; // generate hex code string
    [[nodiscard]] QString getStringForPrintingRGBFloatHTML() const; // generate HTML style string for debugging using float values between 0 and 1 inclusive, ignores transparency
    [[nodiscard]] QString getStringForPrintingRGBAFloatHTML() const; // generate HTML style string for debugging using float values between 0 and 1 inclusive
    [[nodiscard]] bool operator==(SGXColourRGBA x) const; // equality comparator by comparing colour not struct instance memory location
    [[nodiscard]] bool operator!=(SGXColourRGBA x) const; // inequality comparator by comparing colour not struct instance memory location
    void linearTransformRed(float m, float c); // do x -> mx + c transform on red channel with appropriate bounding
    void linearTransformGreen(float m, float c); // do x -> mx + c transform on green channel with appropriate bounding
    void linearTransformBlue(float m, float c); // do x -> mx + c transform on blue channel with appropriate bounding
    void linearTransformTransparency(float m, float c); // do x -> mx + c transform on transparency channel with appropriate bounding
    /*
methods list:
- apply tint
- apply tint with separate transparency
- linear interpolation
- invert
    */
};

#endif // SGXCOLOURRGBA_H
