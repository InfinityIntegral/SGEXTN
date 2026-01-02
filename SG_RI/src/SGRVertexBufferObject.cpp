#include <SGRVertexBufferObject.h>
#include <rhi/qrhi.h>
#include <SGRBaseRenderer.h>
#include <private_api_RI/SGRRendererNode.h>
#include <SGRDataBuffer.h>
#include <private_api_Containers/SGLCrash.h>

SGRVertexBufferObject::SGRVertexBufferObject(SGRBaseRenderer *renderControl, int bufferSize) : SGRDataBuffer(){
    if(bufferSize < 0){SGLCrash::crash("SGRVertexBufferObject constructor crashed as the size is negative");}
    if(renderControl == nullptr){SGLCrash::crash("SGRVertexBufferObject constructor crashed as the associated render control object is nullptr");}
    (*this).rhi = (*(*renderControl).node).rhi;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::VertexBuffer, bufferSize);
    (*(*this).data).create();
}
