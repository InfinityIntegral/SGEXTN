#ifndef SGRTEXTURE_H
#define SGRTEXTURE_H

class QRhi;
class SGRImage;
class QRhiTexture;
class SGRBaseRenderer;
class QRhiSampler;
class SGRTexture
{
public:
    SGRTexture(QRhi* rhi);
    SGRTexture(const SGRTexture&) = delete;
    SGRTexture& operator=(const SGRTexture&) = delete;
    SGRTexture(SGRTexture&&) = delete;
    SGRTexture& operator=(SGRTexture&&) = delete;
    ~SGRTexture();
    QRhiTexture* data;
    QRhiSampler* textureSampler;
    QRhi* rhi;
};

#endif // SGRTEXTURE_H
