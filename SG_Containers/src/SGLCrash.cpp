#include <private_api_Containers/SGLCrash.h>
#include <stdexcept>

void SGLCrash::crash(){
    throw std::runtime_error("You attempted to access a object in a SGEXTN Container Library container by providing the at() function with a out of range argument.");
}

void SGLCrash::crashOnDeleteTimer(){
    throw std::runtime_error("You attempted to directly delete a SGXTimer, this is not allowed, instead call SGXTimer::deleteTimer to delete it safely.");
}
