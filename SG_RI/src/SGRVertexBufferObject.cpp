#include <SGRVertexBufferObject.h>
#include <rhi/qrhi.h>
#include <SGRBaseRenderer.h>
#include <private_api_RI/SGRRendererNode.h>
#include <SGRDataBuffer.h>

SGRVertexBufferObject::SGRVertexBufferObject(SGRBaseRenderer *renderControl, int bufferSize) : SGRDataBuffer(){
    (*this).rhi = (*(*renderControl).node).rhi;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::VertexBuffer, bufferSize);
    (*(*this).data).create();
}
