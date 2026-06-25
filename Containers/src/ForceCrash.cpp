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

#include <SGEXTN/Containers/ForceCrash.h>
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
