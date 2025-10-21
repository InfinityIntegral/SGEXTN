#include "sgrdatabuffer.h"
#include <rhi/qrhi.h>

SGRDataBuffer::SGRDataBuffer(SGRDataBuffer &&x){
    (*this).rhi = x.rhi;
    (*this).data = x.data;
    x.rhi = nullptr;
    x.data = nullptr;
}

SGRDataBuffer::~SGRDataBuffer(){
    (*data).destroy();
    delete data;
}
