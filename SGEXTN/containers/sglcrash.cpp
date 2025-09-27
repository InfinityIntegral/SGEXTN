#include "sglcrash.h"
#include <stdexcept>

void SGLCrash::crash(){
    throw std::out_of_range("You attempted to access a object in a SGEXTN Container Library container by providing the at() function with a out of range argument.");
}
