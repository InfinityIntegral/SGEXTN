#include "sglcrash.h"
#include <stdexcept>

void SGLCrash::crash(){
    throw std::out_of_range("You attempted to access a object in a SGEXTN Container Library container by providing the at() function with a out of range argument.");
}

void SGLCrash::crashOnInsert(){
    throw std::out_of_range("You attempted to insert a element or key into a SGLSet / SGLUnorderedSet / SGLMap / SGLUnorderedMap when the element or key already exists in the data structure.");
}

void SGLCrash::crashOnRemove(){
    throw std::out_of_range("You attempted to remove a element or key from a SGLSet / SGLUnorderedSet / SGLMultiSet / SGLUnorderedMultiSet / SGLMap / SGLUnorderedMap / SGLMultiMap / SGLUnorderedMultiMap when the element or key does not exist in the data structure.");
}
