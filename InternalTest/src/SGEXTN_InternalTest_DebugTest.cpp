#include <private_api/SGEXTN_InternalTest_DebugTest.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_Utilities_RgbaColour.h>
#include <SGEXTN_CoreText_Debug.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_CoreText_Character.h>

namespace {
SGEXTN::CoreText::String lastSentString;

void logIntoString(const char* s){
    lastSentString = s;
}
}

void SGEXTN::InternalTest::DebugTest::runTest(){
    void (*originalFunction)(const char*) = nullptr;
    if((*SGEXTN::CoreText::Debug::logFunctionList).length() > 0){
        originalFunction = (*SGEXTN::CoreText::Debug::logFunctionList).at(0);
        (*SGEXTN::CoreText::Debug::logFunctionList).at(0) = &logIntoString;
    }
    SG;
    if(lastSentString != "SG in SGEXTN_InternalTest_DebugTest.cpp at line 22"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log file and line fail");}
    SG(true);
    if(lastSentString != "SG: true"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log bool true fail");}
    SG(false);
    if(lastSentString != "SG: false"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log bool false fail");}
    SG(static_cast<unsigned char>('a'));
    if(lastSentString != "SG: 61"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log C char fail");}
    SG(SGEXTN::CoreText::DebugPrintCCharMode::Character)('a');
    if(lastSentString != "SG: a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log C char as character fail");}
    SG(static_cast<short>(26));
    if(lastSentString != "SG: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log short fail");}
    SG(static_cast<unsigned short>(26));
    if(lastSentString != "SG: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log unsigned short fail");}
    SG(26);
    if(lastSentString != "SG: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log int fail");}
    SG(static_cast<unsigned int>(26));
    if(lastSentString != "SG: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log unsigned int fail");}
    SG(static_cast<long long>(26));
    if(lastSentString != "SG: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log long long fail");}
    SG(static_cast<unsigned long long>(26));
    if(lastSentString != "SG: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log unsigned long long fail");}
    SG(0.25f);
    if(lastSentString != "SG: 0.25000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log float fail");}
    SG(0.25);
    if(lastSentString != "SG: 0.25000"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log double fail");}
    SG(SGEXTN::CoreText::DebugPrintMetadataMode::Line)(26);
    if(lastSentString != "SG at line 48: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log int with line metadata fail");}
    SG(SGEXTN::CoreText::DebugPrintMetadataMode::All)(26);
    if(lastSentString != "SG in SGEXTN_InternalTest_DebugTest.cpp at line 50: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log int with line and file metadata fail");}
    SG(SGEXTN::CoreText::DebugPrintIntegerMode(16))(26);
    if(lastSentString != "SG: 1a"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log int custom formatting fail");}
    SG(SGEXTN::CoreText::DebugPrintFloatingPointMode(2, SGEXTN::CoreText::FloatPrecisionFormat::ScientificNotation, 5))(0.25f);
    if(lastSentString != "SG: 1.0000^-10"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log float custom formatting fail");}
    SG(SGEXTN::CoreText::Character());
    if(lastSentString != SGEXTN::CoreText::String("SG: ") + SGEXTN::CoreText::Character()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log character fail");}
    const SGEXTN::CoreText::String stringToLog = "abc";
    SG(stringToLog);
    if(lastSentString != "SG: abc"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string fail");}
    SG(SGEXTN::CoreText::DebugPrintStringMode::Byte)(stringToLog);
    if(lastSentString != "SG: 61 62 63"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string as bytes fail");}
    SG(SGEXTN::CoreText::DebugPrintStringMode::CodePoint)(stringToLog);
    if(lastSentString != "SG: 0061 0062 0063"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string as code points fail");}
    SG("test");
    if(lastSentString != "SG: test"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log string literal fail");}
    SG(1)(2)(3)(SGEXTN::CoreText::DebugPrintIntegerMode(2))(4)(5);
    if(lastSentString != "SG: 1 - 2 - 3 - 100 - 101"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log multiple objects fail");}
    SG(SGEXTN::Utilities::RgbaColour());
    if(lastSentString != "SG: rgba(255, 0, 200, 255)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log custom class fail");}
    // NOLINTBEGIN(misc-const-correctness)
    int* (*testFunction1)(const int&) = nullptr;
    const void (SGEXTN::InternalTest::DebugTest::*testFunction2)(int, int, float) = nullptr;
    SGEXTN::CoreText::String (SGEXTN::InternalTest::DebugTest::*testFunction3)() const = nullptr;
    // NOLINTEND(misc-const-correctness)
    SG(testFunction1)(testFunction2)(testFunction3);
    if(lastSentString != "SG: nullptr - nullptr - nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log function pointers fail");}
    int* intPointer = nullptr; // NOLINT(misc-const-correctness)
    SG(intPointer);
    if(lastSentString != "SG: nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log nullptr fail");}
    SG(SGEXTN::CoreText::DebugPrintPointerMode::TryDeref)(intPointer);
    if(lastSentString != "SG: nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log nullptr try deref fail");}
    intPointer = new int(26);
    SG(intPointer);
    if(lastSentString != "SG: not nullptr"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log pointer fail");}
    SG(SGEXTN::CoreText::DebugPrintPointerMode::TryDeref)(intPointer);
    if(lastSentString != "SG: &(26)"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log pointer try deref fail");}
    delete intPointer;
    SG_L(26);
    if(lastSentString != "SG at line 89: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log with line number fail");}
    SG_A(26);
    if(lastSentString != "SG in SGEXTN_InternalTest_DebugTest.cpp at line 91: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log with file name and line number fail");}
    SGEXTN_DEBUG_PRINT(26);
    if(lastSentString != "SG: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug long macro fail");}
    SGEXTN_DEBUG_PRINT_LINE_LOG(26);
    if(lastSentString != "SG at line 95: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log with line number long macro fail");}
    SGEXTN_DEBUG_PRINT_FULL_LOG(26);
    if(lastSentString != "SG in SGEXTN_InternalTest_DebugTest.cpp at line 97: 26"){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CoreTest::Debug log with file name and line number long macro fail");}
    if((*SGEXTN::CoreText::Debug::logFunctionList).length() > 0){(*SGEXTN::CoreText::Debug::logFunctionList).at(0) = originalFunction;}
}
