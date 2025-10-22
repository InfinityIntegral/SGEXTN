#ifndef SGRVERTEXBUFFEROBJECT_H
#define SGRVERTEXBUFFEROBJECT_H

#include "sgrdatabuffer.h"

class SGRBaseRenderer;
class SGRVertexBufferObject : public SGRDataBuffer
{
public:
    SGRVertexBufferObject(SGRBaseRenderer* renderControl, int bufferSize);
};

#endif // SGRVERTEXBUFFEROBJECT_H
