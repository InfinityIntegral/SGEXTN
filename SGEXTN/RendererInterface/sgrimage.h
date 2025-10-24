#ifndef SGRIMAGE_H
#define SGRIMAGE_H

#include "../primitives/sgxcolourrgba.h"

class QImage;
class SGXString;
class SGRImage
{
public:
    SGRImage(int w, int h, SGXColourRGBA c);
    SGRImage(int w, int h);
    SGRImage(const SGXString& filePath);
    SGRImage(const SGRImage& x);
    SGRImage& operator=(const SGRImage& x);
    SGRImage(SGRImage&& x);
    SGRImage& operator=(SGRImage&& x);
    ~SGRImage();
    QImage* data;
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] SGXColourRGBA colourAt(int x, int y) const;
    void setColourAt(int x, int y, SGXColourRGBA c);
    [[nodiscard]] SGXColourRGBA interpolatedColourAt(float x, float y) const;
};

#endif // SGRIMAGE_H
