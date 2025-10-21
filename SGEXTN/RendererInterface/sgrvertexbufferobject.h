#ifndef SGRVERTEXBUFFEROBJECT_H
#define SGRVERTEXBUFFEROBJECT_H

#include "sgrdatabuffer.h"

class QRhi;
class SGRVertexBufferObject : public SGRDataBuffer
{
public:
    SGRVertexBufferObject(QRhi* rhi, int bufferSize);
};

#endif // SGRVERTEXBUFFEROBJECT_H
