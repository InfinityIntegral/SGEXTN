#include "sgrdatabuffer.h"
#include <rhi/qrhi.h>

SGRDataBuffer::~SGRDataBuffer(){
    (*data).destroy();
    delete data;
}

int SGRDataBuffer::length() const {
    return static_cast<int>((*data).size());
}

void SGRDataBuffer::doubleBuffer() const {
    (*data).setSize(2 * (*data).size());
}
