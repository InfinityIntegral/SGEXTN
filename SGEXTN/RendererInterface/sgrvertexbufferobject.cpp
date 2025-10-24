#include "sgrvertexbufferobject.h"
#include <rhi/qrhi.h>
#include "sgrbaserenderer.h"
#include "sgrrenderernode.h"
#include "sgrdatabuffer.h"

SGRVertexBufferObject::SGRVertexBufferObject(SGRBaseRenderer *renderControl, int bufferSize) : SGRDataBuffer(){
    (*this).rhi = (*(*renderControl).node).rhi;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::VertexBuffer, bufferSize);
    (*(*this).data).create();
}
