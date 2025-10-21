#ifndef SGRELEMENTBUFFEROBJECT_H
#define SGRELEMENTBUFFEROBJECT_H

#include "sgrdatabuffer.h"

class QRhi;
class SGRElementBufferObject : public SGRDataBuffer
{
public:
    SGRElementBufferObject(QRhi* rhi, int bufferSize);
};

#endif // SGRELEMENTBUFFEROBJECT_H
