#include <SGRElementBufferObject.h>
#include <rhi/qrhi.h>
#include <SGRBaseRenderer.h>
#include <private_api_RI/SGRRendererNode.h>
#include <SGRDataBuffer.h>
#include <private_api_Containers/SGLCrash.h>

SGRElementBufferObject::SGRElementBufferObject(SGRBaseRenderer *renderControl, int bufferSize) : SGRDataBuffer(){
    if(bufferSize < 0){SGLCrash::crash("SGRElementBufferObject constructor crashed as the size is negative");}
    if(renderControl == nullptr){SGLCrash::crash("SGRElementBufferObject constructor crashed as the associated render control object is nullptr");}
    (*this).rhi = (*(*renderControl).node).rhi;
    (*this).data = (*rhi).newBuffer(QRhiBuffer::Dynamic, QRhiBuffer::IndexBuffer, bufferSize);
    (*(*this).data).create();
}
