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

#include <SGEXTN/InternalTest/private_api/DebugTest.h>
#include <SGEXTN/CoreText/String.h>
#include <SGEXTN/Utilities/RgbaColour.h>
#define SGEXTN_internal_permanentAllowDebug
#include <SGEXTN/CoreText/Debug.h>
#undef SGEXTN_internal_permanentAllowDebug
#include <SGEXTN/Containers/ForceCrash.h>
#include <SGEXTN/CoreText/Character.h>
#include <SGEXTN/Containers/Array.h>

namespace {
SGEXTN::CoreText::String lastSentString;

void logIntoString(const char* s){
    const SGEXTN::CoreText::String msg = s;
    lastSentString = msg.substringCharactersRight(msg.characterLength() - msg.findFirstCharactersFromLeft(" : ") - 3);
}
}

void SGEXTN::InternalTest::DebugTest::runTest(){
    void (*originalFunction)(const char*) = nullptr;
    if((*SGEXTN::CoreText::Debug::logFunctionList).length() > 0){
        originalFunction = (*SGEXTN::CoreText::Debug::logFunctionList).at(0);
        (*SGEXTN::CoreText::Debug::logFunctionList).at(0) = &logIntoString;
    }
    SG(true);
    if(lastSentString != "true"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log bool true fail");}
    SG(false);
    if(lastSentString != "false"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log bool false fail");}
    SG(static_cast<unsigned char>('a'));
    if(lastSentString != "61"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log C char fail");}
    SG(SGEXTN::CoreText::DebugPrintCCharMode::Character)('a');
    if(lastSentString != "a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log C char as character fail");}
    SG(static_cast<short>(26));
    if(lastSentString != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log short fail");}
    SG(static_cast<unsigned short>(26));
    if(lastSentString != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log unsigned short fail");}
    SG(26);
    if(lastSentString != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log int fail");}
    SG(static_cast<unsigned int>(26));
    if(lastSentString != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log unsigned int fail");}
    SG(static_cast<long long>(26));
    if(lastSentString != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log long long fail");}
    SG(static_cast<unsigned long long>(26));
    if(lastSentString != "26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log unsigned long long fail");}
    SG(0.25f);
    if(lastSentString != "0.25000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log float fail");}
    SG(static_cast<double>(0.25f));
    if(lastSentString != "0.25000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log double fail");}
    SG(SGEXTN::CoreText::DebugPrintIntegerMode(16))(26);
    if(lastSentString != "1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log int custom formatting fail");}
    SG(SGEXTN::CoreText::DebugPrintFloatingPointMode(2, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 5))(0.25f);
    if(lastSentString != "1.0000^-10"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log float custom formatting fail");}
    SG(SGEXTN::CoreText::Character());
    if(lastSentString != SGEXTN::CoreText::Character()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log character fail");}
    const SGEXTN::CoreText::String stringToLog = "abc";
    SG(stringToLog);
    if(lastSentString != "abc"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string fail");}
    SG(SGEXTN::CoreText::DebugPrintStringMode::Byte)(stringToLog);
    if(lastSentString != "61 62 63"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string as bytes fail");}
    SG(SGEXTN::CoreText::DebugPrintStringMode::CodePoint)(stringToLog);
    if(lastSentString != "0061 0062 0063"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string as code points fail");}
    SG("test");
    if(lastSentString != "test"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string literal fail");}
    SG(1)(2)(3)(SGEXTN::CoreText::DebugPrintIntegerMode(2))(4)(5);
    if(lastSentString != "1 - 2 - 3 - 100 - 101"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log multiple objects fail");}
    SG(SGEXTN::Utilities::RgbaColour());
    if(lastSentString != "rgba(255, 0, 200, 255)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log custom class fail");}
    int* (*const testFunction1)(const int&) = nullptr;
    const void (SGEXTN::InternalTest::DebugTest::*const testFunction2)(int, int, float) = nullptr;
    SGEXTN::CoreText::String (SGEXTN::InternalTest::DebugTest::*const testFunction3)() const = nullptr;
    SG(testFunction1)(testFunction2)(testFunction3);
    if(lastSentString != "nullptr - nullptr - nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log function pointers fail");}
    int* intPointer = nullptr;
    SG(intPointer);
    if(lastSentString != "nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log nullptr fail");}
    SG(SGEXTN::CoreText::DebugPrintPointerMode::TryDeref)(intPointer);
    if(lastSentString != "nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log nullptr try deref fail");}
    intPointer = new int(26);
    SG(intPointer);
    if(lastSentString != "not nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log pointer fail");}
    SG(SGEXTN::CoreText::DebugPrintPointerMode::TryDeref)(intPointer);
    if(lastSentString != "&( 26 )"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log pointer try deref fail");}
    (*(intPointer)) = -26;
    SG(SGEXTN::CoreText::DebugPrintPointerMode::TryDeref)(intPointer);
    if(lastSentString != "&( -26 )"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log pointer value update fail");}
    delete intPointer;
    const int* constIntPointer = nullptr;
    SG(constIntPointer);
    if(lastSentString != "nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log const nullptr fail");}
    SG(SGEXTN::CoreText::DebugPrintPointerMode::TryDeref)(constIntPointer);
    if(lastSentString != "nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log const nullptr try deref fail");}
    constIntPointer = new int(26);
    SG(constIntPointer);
    if(lastSentString != "not nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log const pointer fail");}
    SG(SGEXTN::CoreText::DebugPrintPointerMode::TryDeref)(constIntPointer);
    if(lastSentString != "&( 26 )"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log const pointer try deref fail");}
    delete constIntPointer;
    SG(SGEXTN::Containers::Array<int>({1, 2, 3, 4, 5}));
    if(lastSentString != "[ 1, 2, 3, 4, 5 ]"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log array fail");}
    SG(SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure);
    if(lastSentString != "FloatPrecisionFormat::SignificantFigure (0x01)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log enum class fail");}
    intPointer = new int(726);
    {
        const SGEXTN::CoreText::DebugDefaultModeOverride changeDefaults(SGEXTN::CoreText::DebugPrintIntegerMode(3), SGEXTN::CoreText::DebugPrintFloatingPointMode(10, SGEXTN::CoreText::FloatPrecisionFormat::FractionalDigit, 2), SGEXTN::CoreText::DebugPrintCCharMode::Character, SGEXTN::CoreText::DebugPrintStringMode::Byte, SGEXTN::CoreText::DebugPrintPointerMode::TryDeref);
        SG(726);
        if(lastSentString != "222220"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default integer mode fail");}
        SG(26.2607f);
        if(lastSentString != "26.26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default floating point mode fail");}
        SG('A');
        if(lastSentString != "A"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default C char mode fail");}
        SG(SGEXTN::CoreText::String("hi"));
        if(lastSentString != "68 69"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default string mode fail");}
        SG(intPointer);
        if(lastSentString != "&( 222220 )"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default pointer mode fail");}
    }
    SG(726);
    if(lastSentString != "726"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default integer mode fail");}
    SG(26.2607f);
    if(lastSentString != "26.261"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default floating point mode fail");}
    SG('A');
    if(lastSentString != "41"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default C char mode fail");}
    SG(SGEXTN::CoreText::String("hi"));
    if(lastSentString != "hi"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default string mode fail");}
    SG(intPointer);
    if(lastSentString != "not nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug switch default pointer mode fail");}
    delete intPointer;
    if((*SGEXTN::CoreText::Debug::logFunctionList).length() > 0){(*SGEXTN::CoreText::Debug::logFunctionList).at(0) = originalFunction;}
}
