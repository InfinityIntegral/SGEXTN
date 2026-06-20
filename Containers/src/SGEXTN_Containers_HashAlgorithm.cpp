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

#include <SGEXTN_Containers_Span.h>
#include <private_api/SGEXTN_Containers_HashAlgorithm.h>

int SGEXTN::Containers::HashAlgorithm::wyHash32(const SGEXTN::Containers::Span<const unsigned char> &span){
    const unsigned int num0 = 0xA0761D65;
    const unsigned int num1 = 0xE7037ED1;
    const unsigned int num2 = 0x8EBC6AF1;
    const unsigned int num3 = 0x589965CC;
    int i = 0;
    const int sizeOfT = span.length();
    unsigned int hash = num0;
    while(sizeOfT - i >= 4){
        unsigned int k = 0u;
        k = k | (span.at(i));
        k = k | (span.at(i + 1) << 8);
        k = k | (span.at(i + 2) << 16);
        k = k | (span.at(i + 3) << 24);
        hash = num1 * (hash ^ k);
        hash = (hash << 13) | (hash >> 19);
        i += 4;
    }
    if(i < sizeOfT){
        unsigned int k = 0u;
        for(int j=0; j<sizeOfT-i; j++){
            k = k | (span.at(i + j) << (8 * j));
        }
        hash = num1 * (hash ^ k);
        hash = (hash << 13) | (hash >> 19);
    }
    hash = num2 * (hash ^ (hash >> 16));
    hash = num3 * (hash ^ (hash >> 13));
    hash = hash ^ (hash >> 16);
    return static_cast<int>(hash);
}
