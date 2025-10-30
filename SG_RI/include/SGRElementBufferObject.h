#ifndef SGRELEMENTBUFFEROBJECT_H
#define SGRELEMENTBUFFEROBJECT_H

#include <SGRDataBuffer.h>

#include <private_api_RI/SG_Build_RI.h>

class SGRBaseRenderer;
class SG_RI_DLL SGRElementBufferObject : public SGRDataBuffer
{
public:
    SGRElementBufferObject(SGRBaseRenderer* renderControl, int bufferSize);
};

#endif // SGRELEMENTBUFFEROBJECT_H
