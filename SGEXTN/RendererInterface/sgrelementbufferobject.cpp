#include "sgrelementbufferobject.h"
#include <rhi/qrhi.h>
#include "sgrbaserenderer.h"
#include "sgrrenderernode.h"

SGRElementBufferObject::SGRElementBufferObject(SGRBaseRenderer *renderControl, int bufferSize){
    (*this).rhi = (*(*renderControl).node).rhi;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::IndexBuffer, bufferSize);
    (*(*this).data).create();
}
