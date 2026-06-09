#include <private_api/SGEXTN_Containers_Crash.h>
#include <cstring>
#include <cstdlib>

namespace {
void memoryCopy(const char* source, char* destination, int length){
    std::memcpy(destination, source, length);
}

int cStringLength(const char* s){
    return static_cast<int>(std::strlen(s));
}
}

void (*SGEXTN::Containers::Crash::logCrashMessage)(const char*) = nullptr;

void SGEXTN::Containers::Crash::basicLogMessage(const char* prefix, const char* msg){
    const int prefixLength = cStringLength(prefix);
    const int msgLength = cStringLength(msg);
    char* message = new char[prefixLength + msgLength + 1];
    memoryCopy(prefix, message, prefixLength);
    memoryCopy(msg, message + prefixLength, msgLength);
    (*(message + prefixLength + msgLength)) = '\0';
    if(SGEXTN::Containers::Crash::logCrashMessage != nullptr){SGEXTN::Containers::Crash::logCrashMessage(message);}
    delete[] message;
}

void SGEXTN::Containers::Crash::crash(const char* msg){
    SGEXTN::Containers::Crash::basicLogMessage("SGEXTN triggered fatal error: ", msg);
    std::abort();
}

void SGEXTN::Containers::Crash::warn(const char* msg){
    SGEXTN::Containers::Crash::basicLogMessage("SGEXTN triggered warning: ", msg);
}
