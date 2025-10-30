#ifndef SGRCOMMANDREQUEST_H
#define SGRCOMMANDREQUEST_H

#include <private_api_RI/SG_Build_RI.h>

class QRhiCommandBuffer;
class SGRVertexBufferObject;
class SGRElementBufferObject;
template <typename T> class SGLVector;
template <typename T1, typename T2> class SGLPair;
class SG_RI_DLL SGRCommandRequest
{
public:
    SGRCommandRequest(QRhiCommandBuffer* commandBuffer);
    SGRCommandRequest(const SGRCommandRequest&) = delete;
    SGRCommandRequest& operator=(const SGRCommandRequest&) = delete;
    SGRCommandRequest(SGRCommandRequest&& x) = delete;
    SGRCommandRequest& operator=(SGRCommandRequest&&) = delete;
    ~SGRCommandRequest();
    QRhiCommandBuffer* commandBuffer;
    SGLVector<SGLPair<int, SGRVertexBufferObject*>>* vbos;
    SGRElementBufferObject* ebo;
    bool buffersAttached;
    void addVertexBufferObject(SGRVertexBufferObject *vbo, int bufferOffsetInBytes) const;
    void chooseElementBufferObject(SGRElementBufferObject* ebo);
    void finaliseForDraw();
    void drawTriangles(int numberOfTriangles, int startLocation) const;
};

#endif // SGRCOMMANDREQUEST_H
