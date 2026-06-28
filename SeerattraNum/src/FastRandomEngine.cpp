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

#include <SGEXTN/SeerattraNum/private_api/FastRandomEngine.h>
#include <SGEXTN/Containers/Hash.h>

SGEXTN::SeerattraNum::FastRandomEngine::FastRandomEngine(int initialSeed) : internalSeed(initialSeed), internalIndex(0){}

unsigned int SGEXTN::SeerattraNum::FastRandomEngine::operator()(){
    const unsigned int output = static_cast<unsigned int>(SGEXTN::Containers::Hash<int, int>()(internalSeed, internalIndex));
    internalIndex++;
    return output;
}

void SGEXTN::SeerattraNum::FastRandomEngine::seed(int seed){
    internalSeed = seed;
    internalIndex = 0;
}
