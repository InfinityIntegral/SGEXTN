#include <SGEXTN_Structs_IdentifierRegistry.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Structs_Identifier.h>
#include <chrono>
#include <random>

namespace {
bool randomEngineIsSeeded = false;
std::random_device randomDevice;
std::minstd_rand randomEngine;

void reSeedRandomEngine(){
    unsigned int currentTime = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
    randomEngine.seed(randomDevice() ^ currentTime);
}

unsigned int getRandomNumber(){
    if(randomEngineIsSeeded == false){
        reSeedRandomEngine();
        randomEngineIsSeeded = true;
    }
    return randomEngine();
}
}

SGEXTN::Structs::Identifier SGEXTN::Structs::IdentifierRegistry::generateAndRegisterIdentifier(){
    while(true){
        const unsigned int n = getRandomNumber();
        if(private_contents.contains(n) == false){
            SGEXTN::Structs::Identifier id;
            id.private_data = n;
            private_contents.insert(n);
            return id;
        }
        reSeedRandomEngine();
    }
}

SGEXTN::Structs::Identifier SGEXTN::Structs::IdentifierRegistry::parseAndRegisterIdentifier(unsigned int data, bool* isValid){
    SGEXTN::Structs::Identifier id;
    id.private_data = data;
    if(isValid != nullptr){
        if(data == 0u || private_contents.contains(data) == true){(*isValid) = false;}
        else{(*isValid) = true;}
    }
    if(data != 0u){private_contents.insert(data);}
    return id;
}

bool SGEXTN::Structs::IdentifierRegistry::unregister(SGEXTN::Structs::Identifier id){
    if(id.private_data == 0u){return false;}
    return private_contents.erase(id.private_data);
}

bool SGEXTN::Structs::IdentifierRegistry::contains(SGEXTN::Structs::Identifier id) const {
    if(id.private_data == 0u){return false;}
    return private_contents.contains(id.private_data);
}