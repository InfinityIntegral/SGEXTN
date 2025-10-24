#include "sgrvertexbufferobject.h"
#include <rhi/qrhi.h>
#include "sgrbaserenderer.h"
#include "sgrrenderernode.h"

SGRVertexBufferObject::SGRVertexBufferObject(SGRBaseRenderer *renderControl, int bufferSize){
    (*this).rhi = (*(*renderControl).node).rhi;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::VertexBuffer, bufferSize);
    (*(*this).data).create();
}
