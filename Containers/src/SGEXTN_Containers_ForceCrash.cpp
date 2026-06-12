#include <SGEXTN_Containers_ForceCrash.h>
#include <cstring>
#include <cstdlib>
#include <iostream>

namespace {
void memoryCopy(const char* source, char* destination, int length){
    std::memcpy(destination, source, length);
}

int cStringLength(const char* s){
    return static_cast<int>(std::strlen(s));
}
}

void SGEXTN::Containers::ForceCrash::logMessage(const char* prefix, const char* msg){
    const int prefixLength = cStringLength(prefix);
    const int msgLength = cStringLength(msg);
    char* message = new char[prefixLength + msgLength + 1];
    memoryCopy(prefix, message, prefixLength);
    memoryCopy(msg, message + prefixLength, msgLength);
    (*(message + prefixLength + msgLength)) = '\0';
    std::cerr << message << "\n";
    delete[] message;
}

void SGEXTN::Containers::ForceCrash::immediateCrash(const char* msg){
    SGEXTN::Containers::ForceCrash::logMessage("SGEXTN triggered fatal error: ", msg);
    std::abort();
}

void SGEXTN::Containers::ForceCrash::basicWarn(const char* msg){
    SGEXTN::Containers::ForceCrash::logMessage("SGEXTN triggered warning: ", msg);
}