#include "sgrdatabuffer.h"
#include <rhi/qrhi.h>

SGRDataBuffer::~SGRDataBuffer(){
    (*data).destroy();
    delete data;
}

int SGRDataBuffer::length() const {
    return (*data).size();
}

void SGRDataBuffer::doubleBuffer(){
    (*data).setSize(2 * (*data).size());
}
