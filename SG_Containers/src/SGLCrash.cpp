#include <private_api_Containers/SGLCrash.h>
#include <stdexcept>

void SGLCrash::crash(const char *msg){
    throw std::runtime_error(msg);
}
