#ifndef SGRELEMENTBUFFEROBJECT_H
#define SGRELEMENTBUFFEROBJECT_H

#include "sgrdatabuffer.h"

class SGRBaseRenderer;
class SGRElementBufferObject : public SGRDataBuffer
{
public:
    SGRElementBufferObject(SGRBaseRenderer* renderControl, int bufferSize);
};

#endif // SGRELEMENTBUFFEROBJECT_H
