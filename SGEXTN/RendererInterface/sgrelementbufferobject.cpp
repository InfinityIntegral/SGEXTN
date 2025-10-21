#include "sgrelementbufferobject.h"
#include <rhi/qrhi.h>

SGRElementBufferObject::SGRElementBufferObject(QRhi *rhi, int bufferSize){
    (*this).rhi = rhi;
    (*this).bufferSize = bufferSize;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::IndexBuffer, bufferSize);
    (*(*this).data).create();
}
