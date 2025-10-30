#ifndef SGRTEXTURE_H
#define SGRTEXTURE_H

#include <private_api_RI/SG_Build_RI.h>

class QRhi;
class SGRImage;
class QRhiTexture;
class SGRBaseRenderer;
class QRhiSampler;
class SG_RI_DLL SGRTexture
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
