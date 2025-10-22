#include "sgrdatabuffer.h"
#include <rhi/qrhi.h>

SGRDataBuffer::~SGRDataBuffer(){
    (*data).destroy();
    delete data;
}
