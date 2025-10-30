#include <SGRElementBufferObject.h>
#include <rhi/qrhi.h>
#include <SGRBaseRenderer.h>
#include <private_api_RI/SGRRendererNode.h>
#include <SGRDataBuffer.h>

SGRElementBufferObject::SGRElementBufferObject(SGRBaseRenderer *renderControl, int bufferSize) : SGRDataBuffer(){
    (*this).rhi = (*(*renderControl).node).rhi;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::IndexBuffer, bufferSize);
    (*(*this).data).create();
}
