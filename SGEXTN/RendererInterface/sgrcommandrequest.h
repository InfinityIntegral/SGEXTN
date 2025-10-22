#ifndef SGRCOMMANDREQUEST_H
#define SGRCOMMANDREQUEST_H

class QRhiCommandBuffer;
class SGRVertexBufferObject;
class SGRElementBufferObject;
template <typename T> class SGLVector;
template <typename T1, typename T2> class SGLPair;
class SGRCommandRequest
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
    int eboOffset;
    bool buffersAttached;
    void addVertexBufferObject(SGRVertexBufferObject* vbo, int shaderDeclaredBinding);
    void chooseElementBufferObject(SGRElementBufferObject* ebo, int vertexIndexOffset);
    void finaliseForDraw();
    void drawUsingIndex(int numberOfTriangles, int startLocation);
};

#endif // SGRCOMMANDREQUEST_H
