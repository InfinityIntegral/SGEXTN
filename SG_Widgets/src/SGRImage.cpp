#include <SGRImage.h>
#include <QImage>
#include <QColor>
#include <SGLFloatMath.h>
#include <SGXColourRGBA.h>

SGRImage::SGRImage(const SGRImage &x){
    (*this).data = new QImage();
    (*(*this).data) = (*x.data);
}

SGRImage& SGRImage::operator=(const SGRImage& x){
    if(this == &x){return (*this);}
    (*(*this).data) = (*x.data);
    return (*this);
}

SGRImage::SGRImage(SGRImage &&x) noexcept {
    (*this).data = x.data;
    x.data = nullptr;
}

SGRImage& SGRImage::operator=(SGRImage&& x) noexcept {
    delete (*this).data;
    (*this).data = x.data;
    x.data = nullptr;
    return (*this);
}

SGRImage::~SGRImage(){
    delete data;
}

SGRImage::SGRImage(int w, int h){
    data = new QImage(w, h, QImage::Format_RGBA8888);
}

SGRImage::SGRImage(int w, int h, SGXColourRGBA c){
    data = new QImage(w, h, QImage::Format_RGBA8888);
    (*data).fill(QColor(c.getRed(), c.getGreen(), c.getBlue(), c.getTransparency()));
}

SGRImage::SGRImage(const SGXString &filePath){
    data = new QImage(*filePath.data);
    (*data) = (*data).convertToFormat(QImage::Format_RGBA8888);
}

int SGRImage::width() const {
    return (*data).width();
}

int SGRImage::height() const {
    return (*data).height();
}

SGXColourRGBA SGRImage::colourAt(int x, int y) const {
    const QColor c = (*data).pixelColor(x, y);
    return SGXColourRGBA(c.red(), c.green(), c.blue(), c.alpha());
}

void SGRImage::setColourAt(int x, int y, SGXColourRGBA c) const {
    const QColor col(c.getRed(), c.getGreen(), c.getBlue(), c.getTransparency());
    (*data).setPixelColor(x, y, col);
}

SGXColourRGBA SGRImage::interpolatedColourAt(float x, float y) const {
    int x0 = SGLFloatMath::floorToInt(x);
    int x1 = SGLFloatMath::ceilingToInt(x);
    const float dx = x - static_cast<float>(x0);
    int y0 = SGLFloatMath::floorToInt(y);
    int y1 = SGLFloatMath::ceilingToInt(y);
    const float dy = y - static_cast<float>(y0);
    x0 %= width();
    if(x0 < 0){x0 += width();}
    x1 %= width();
    if(x1 < 0){x1 += width();}
    y0 %= height();
    if(y0 < 0){y0 += height();}
    y1 %= height();
    if(y1 < 0){y1 += height();}
    const SGXColourRGBA c00 = colourAt(x0, y0);
    const SGXColourRGBA c01 = colourAt(x0, y1);
    const SGXColourRGBA c10 = colourAt(x1, y0);
    const SGXColourRGBA c11 = colourAt(x1, y1);
    const SGXColourRGBA c0 = c01.linearInterpolate(c00, dy);
    const SGXColourRGBA c1 = c11.linearInterpolate(c10, dy);
    return c1.linearInterpolate(c0, dx);
}

void SGRImage::saveToFile(const SGXString &filePath) const {
    (*data).save((*filePath.data), "PNG");
}
