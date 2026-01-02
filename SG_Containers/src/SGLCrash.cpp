#include <private_api_Containers/SGLCrash.h>
#include <stdexcept>
#include <string>

void SGLCrash::crash(const char *msg){
    std::string message(msg);
    message = std::string("\nERROR\n") + message + "\nSGEXTN framework has detected misuse of API and has crashed to prevent undefined behaviour\nPls read the documentation to see how to properly use the mentioned function\nRun the app with a debugger by clicking the button below the run button for a stack trace";
    throw std::runtime_error(message);
}
