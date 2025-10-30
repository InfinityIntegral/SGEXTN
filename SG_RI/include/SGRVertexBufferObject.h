#ifndef SGRVERTEXBUFFEROBJECT_H
#define SGRVERTEXBUFFEROBJECT_H

#include <SGRDataBuffer.h>

#include <private_api_RI/SG_Build_RI.h>

class SGRBaseRenderer;
class SG_RI_DLL SGRVertexBufferObject : public SGRDataBuffer
{
public:
    SGRVertexBufferObject(SGRBaseRenderer* renderControl, int bufferSize);
};

#endif // SGRVERTEXBUFFEROBJECT_H
