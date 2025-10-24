#include "sgrtexture.h"
#include "sgrrenderernode.h"
#include <rhi/qrhi.h>

SGRTexture::SGRTexture(QRhi *rhi){
    (*this).rhi = rhi;
    (*this).data = (*rhi).newTexture(QRhiTexture::RGBA8, QSize(1, 1));
    (*(*this).data).create();
    (*this).textureSampler = (*rhi).newSampler(QRhiSampler::Linear, QRhiSampler::Linear, QRhiSampler::None, QRhiSampler::Repeat, QRhiSampler::Repeat, QRhiSampler::Repeat);
    (*(*this).textureSampler).create();
}

SGRTexture::~SGRTexture(){
    (*data).destroy();
    delete data;
    (*textureSampler).destroy();
    delete textureSampler;
}
