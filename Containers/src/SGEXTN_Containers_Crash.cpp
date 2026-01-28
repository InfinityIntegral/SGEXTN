#include <private_api/SGEXTN_Containers_Crash.h>
#include <stdexcept>
#include <string>
#include <iostream>

void (*SGEXTN::Containers::Crash::logCrashMessage)(const char*) = nullptr;

void SGEXTN::Containers::Crash::crash(const char* msg){
    std::string message(msg);
    message = std::string("FATAL ERROR: ") + message + "\n";
    if(SGEXTN::Containers::Crash::logCrashMessage != nullptr){SGEXTN::Containers::Crash::logCrashMessage(message.c_str());}
    throw std::runtime_error(message);
}

void SGEXTN::Containers::Crash::warn(const char* msg){
    std::string message(msg);
    message = std::string("WARNING: ") + message + "\n";
    if(SGEXTN::Containers::Crash::logCrashMessage != nullptr){SGEXTN::Containers::Crash::logCrashMessage(message.c_str());}
    std::cerr << message;
}
