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

#include <private_api/SGEXTN_InternalTest_SeerattraNumTest.h>
#include <SGEXTN_SeerattraNum_TrueRandom.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_SeerattraNum_SimpleRandom.h>

void SGEXTN::InternalTest::SeerattraNumTest::testTrueRandom(){
    SGEXTN::Containers::UnorderedSet<int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> randomInts32;
    while(randomInts32.length() < 100){
        randomInts32.insert(SGEXTN::SeerattraNum::TrueRandom::randomInt32());
    }
    SGEXTN::Containers::UnorderedSet<long long, SGEXTN::Containers::EqualTo<long long>, SGEXTN::Containers::Hash<long long>> randomInts64;
    while(randomInts64.length() < 100){
        randomInts64.insert(SGEXTN::SeerattraNum::TrueRandom::randomInt64());
    }
    SGEXTN::Containers::UnorderedSet<unsigned int, SGEXTN::Containers::EqualTo<unsigned int>, SGEXTN::Containers::Hash<unsigned int>> randomUnsignedInts32;
    while(randomUnsignedInts32.length() < 100){
        randomUnsignedInts32.insert(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32());
    }
    SGEXTN::Containers::UnorderedSet<unsigned long long, SGEXTN::Containers::EqualTo<unsigned long long>, SGEXTN::Containers::Hash<unsigned long long>> randomUnsignedInts64;
    while(randomUnsignedInts64.length() < 100){
        randomUnsignedInts64.insert(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64());
    }
    SGEXTN::Containers::UnorderedSet<float, SGEXTN::Containers::EqualTo<float>, SGEXTN::Containers::Hash<float>> randomFloats32;
    while(randomFloats32.length() < 100){
        randomFloats32.insert(SGEXTN::SeerattraNum::TrueRandom::randomFloat32());
    }
    SGEXTN::Containers::UnorderedSet<double, SGEXTN::Containers::EqualTo<double>, SGEXTN::Containers::Hash<double>> randomFloats64;
    while(randomFloats64.length() < 100){
        randomFloats64.insert(SGEXTN::SeerattraNum::TrueRandom::randomFloat64());
    }
    if(SGEXTN::SeerattraNum::TrueRandom::randomInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 32 bit integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 64 bit integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 32 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomUnsignedInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 64 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomFloat32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 32 bit floating point number fail");}
    if(SGEXTN::SeerattraNum::TrueRandom::randomFloat64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::TrueRandom generate array of 64 bit floating point number fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testSimpleRandom(){
    SGEXTN::Containers::UnorderedSet<int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> randomInts32;
    while(randomInts32.length() < 100){
        randomInts32.insert(SGEXTN::SeerattraNum::SimpleRandom::randomInt32());
    }
    SGEXTN::Containers::UnorderedSet<long long, SGEXTN::Containers::EqualTo<long long>, SGEXTN::Containers::Hash<long long>> randomInts64;
    while(randomInts64.length() < 100){
        randomInts64.insert(SGEXTN::SeerattraNum::SimpleRandom::randomInt64());
    }
    SGEXTN::Containers::UnorderedSet<unsigned int, SGEXTN::Containers::EqualTo<unsigned int>, SGEXTN::Containers::Hash<unsigned int>> randomUnsignedInts32;
    while(randomUnsignedInts32.length() < 100){
        randomUnsignedInts32.insert(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32());
    }
    SGEXTN::Containers::UnorderedSet<unsigned long long, SGEXTN::Containers::EqualTo<unsigned long long>, SGEXTN::Containers::Hash<unsigned long long>> randomUnsignedInts64;
    while(randomUnsignedInts64.length() < 100){
        randomUnsignedInts64.insert(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64());
    }
    SGEXTN::Containers::UnorderedSet<float, SGEXTN::Containers::EqualTo<float>, SGEXTN::Containers::Hash<float>> randomFloats32;
    while(randomFloats32.length() < 100){
        randomFloats32.insert(SGEXTN::SeerattraNum::SimpleRandom::randomFloat32());
    }
    SGEXTN::Containers::UnorderedSet<double, SGEXTN::Containers::EqualTo<double>, SGEXTN::Containers::Hash<double>> randomFloats64;
    while(randomFloats64.length() < 100){
        randomFloats64.insert(SGEXTN::SeerattraNum::SimpleRandom::randomFloat64());
    }
    if(SGEXTN::SeerattraNum::SimpleRandom::randomInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 32 bit integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 64 bit integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 32 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomUnsignedInt64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 64 bit unsigned integer fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomFloat32Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 32 bit floating point number fail");}
    if(SGEXTN::SeerattraNum::SimpleRandom::randomFloat64Array(100).length() != 100){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Seerattra::SimpleRandom generate array of 64 bit floating point number fail");}
}

void SGEXTN::InternalTest::SeerattraNumTest::testAll(){
    SGEXTN::InternalTest::SeerattraNumTest::testTrueRandom();
    SGEXTN::InternalTest::SeerattraNumTest::testSimpleRandom();
}
