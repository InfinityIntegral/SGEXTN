#ifndef SGRIMAGE_H
#define SGRIMAGE_H

#include <SGXColourRGBA.h>

#include <private_api_Widgets/SG_Build_Widgets.h>

class QImage;
class SGXString;
class SG_WIDGETS_DLL SGRImage
{
public:
    SGRImage(int w, int h, SGXColourRGBA c);
    SGRImage(int w, int h);
    SGRImage(const SGXString& filePath);
    SGRImage(const SGRImage& x);
    SGRImage& operator=(const SGRImage& x);
    SGRImage(SGRImage&& x) noexcept;
    SGRImage& operator=(SGRImage&& x) noexcept;
    ~SGRImage();
    QImage* data;
    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;
    [[nodiscard]] SGXColourRGBA colourAt(int x, int y) const;
    void setColourAt(int x, int y, SGXColourRGBA c) const;
    [[nodiscard]] SGXColourRGBA interpolatedColourAt(float x, float y) const;
    void saveToFile(const SGXString& filePath) const;
};

#endif // SGRIMAGE_H
