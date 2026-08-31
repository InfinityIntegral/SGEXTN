/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN/Utilities/IdentifierRegistry.h>
#include <SGEXTN/Containers/UnorderedSet.h>
#include <SGEXTN/Utilities/Identifier.h>
#include <chrono>
#include <random>

namespace {
bool randomEngineIsSeeded = false;
std::random_device randomDevice;
std::minstd_rand randomEngine(randomDevice());

void reSeedRandomEngine(){
    const unsigned int currentTime = static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
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

SGEXTN::Utilities::IdentifierRegistry::IdentifierRegistry(){}

SGEXTN::Utilities::Identifier SGEXTN::Utilities::IdentifierRegistry::generateAndRegisterIdentifier(){
    while(true){
        const unsigned int n = getRandomNumber();
        if(contents_.contains(n) == false){
            SGEXTN::Utilities::Identifier id;
            id.data_ = n;
            contents_.insert(n);
            return id;
        }
        reSeedRandomEngine();
    }
}

SGEXTN::Utilities::Identifier SGEXTN::Utilities::IdentifierRegistry::parseAndRegisterIdentifier(unsigned int data, bool* isValid){
    SGEXTN::Utilities::Identifier id;
    id.data_ = data;
    if(isValid != nullptr){
        if(data == 0u || contents_.contains(data) == true){(*isValid) = false;}
        else{(*isValid) = true;}
    }
    if(data != 0u){contents_.insert(data);}
    return id;
}

bool SGEXTN::Utilities::IdentifierRegistry::unregister(SGEXTN::Utilities::Identifier id){
    if(id.data_ == 0u){return false;}
    return contents_.erase(id.data_);
}

bool SGEXTN::Utilities::IdentifierRegistry::contains(SGEXTN::Utilities::Identifier id) const {
    if(id.data_ == 0u){return false;}
    return contents_.contains(id.data_);
}

int SGEXTN::Utilities::IdentifierRegistry::length() const {
    return contents_.length();
}
