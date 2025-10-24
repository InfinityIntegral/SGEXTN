#include "sgrcommandrequest.h"
#include <rhi/qrhi.h>
#include "../containers/sglpair.h"
#include "../containers/sglvector.h"
#include "sgrvertexbufferobject.h"
#include "sgrelementbufferobject.h"
#include <stdexcept>

SGRCommandRequest::SGRCommandRequest(QRhiCommandBuffer *commandBuffer){
    (*this).commandBuffer = commandBuffer;
    (*this).vbos = new SGLVector<SGLPair<int, SGRVertexBufferObject*>>();
    (*this).ebo = nullptr;
    (*this).buffersAttached = false;
}

SGRCommandRequest::~SGRCommandRequest(){
    delete vbos;
}

void SGRCommandRequest::addVertexBufferObject(SGRVertexBufferObject *vbo, int bufferOffsetInBytes){
    (*vbos).pushBack(SGLPair<int, SGRVertexBufferObject*>(bufferOffsetInBytes, vbo));
}

void SGRCommandRequest::chooseElementBufferObject(SGRElementBufferObject *ebo){
    (*this).ebo = ebo;
}

void SGRCommandRequest::finaliseForDraw(){
    if((*vbos).length() == 0){throw std::runtime_error("you forgot to bind vertex buffer objects, use SGRCommandRequest::addVertexBufferObject to bind them, you can bind multiple vertex buffer objects");}
    if(ebo == nullptr){throw std::runtime_error("you forgot to bind a element buffer object, use SGRCommandRequest::chooseElementBufferObject to bind it, SG RI forces use of element buffer objects even when the performance gain is not significant");}
    SGLVector<QRhiCommandBuffer::VertexInput> vboBindings;
    for(int i=0; i<(*vbos).length(); i++){
        vboBindings.pushBack(QRhiCommandBuffer::VertexInput((*(*vbos).at(i).second).data, (*vbos).at(i).first));
    }
    (*commandBuffer).setVertexInput(0, vboBindings.length(), vboBindings.pointerToData(0), (*ebo).data, 0, QRhiCommandBuffer::IndexUInt32);
    buffersAttached = true;
}

void SGRCommandRequest::drawTriangles(int numberOfTriangles, int startLocation){
    if(buffersAttached == false){throw std::runtime_error("you forgot to attach the vertex buffer objects and element buffer objects by finalising the command request before drawing, use SGRCommandRequest::finaliseForDraw to attach the buffers");}
    (*commandBuffer).drawIndexed(3 * numberOfTriangles, 1, startLocation, 0, 0);
}
