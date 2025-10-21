#include "sgrvertexbufferobject.h"
#include <rhi/qrhi.h>

SGRVertexBufferObject::SGRVertexBufferObject(QRhi *rhi, int bufferSize){
    (*this).rhi = rhi;
    (*this).bufferSize = bufferSize;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::VertexBuffer, bufferSize);
    (*(*this).data).create();
}
