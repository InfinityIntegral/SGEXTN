#include <private_api/SGEXTN_Containers_Crash.h>
#include <stdexcept>
#include <string>

void (*SGEXTN::Containers::Crash::logCrashMessage)(const char*) = nullptr;

void SGEXTN::Containers::Crash::crash(const char *msg){
    std::string message(msg);
    message = std::string("\nERROR\n") + message + "\nSGEXTN framework has detected misuse of API and has crashed to prevent undefined behaviour\nPls read the documentation to see how to properly use the mentioned function\nRun the app with a debugger by clicking the button below the run button for a stack trace";
    if(SGEXTN::Containers::Crash::logCrashMessage != nullptr){SGEXTN::Containers::Crash::logCrashMessage(message.c_str());}
    throw std::runtime_error(message);
}
