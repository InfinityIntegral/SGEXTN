#include <SGEXTN_CoreText_Debug.h>
#include <SGEXTN_CoreText_Character.h>
#include <SGEXTN_CoreText_String.h>
#include <iostream>
#include <locale>
#include <cwchar>
#include <SGEXTN_Containers_ForceCrash.h>

namespace {
SGEXTN::Containers::ForceCrashLogFunctionRegistrar forceCrashLogFunctionRegistrarInstance(&SGEXTN::CoreText::Debug::logCrashMessage);

const char* printUtf8String(const unsigned char* data, int byteLength, bool& mustDeleteOutputUsingArrayDelete){
    mustDeleteOutputUsingArrayDelete = false;
    if(byteLength == 0){return "";}
    const std::locale cmdConsoleLocale("");
    char16_t* utf16Buffer = new char16_t[byteLength];
    const std::codecvt<char16_t, char8_t, std::mbstate_t>& utf8ToUtf16Facet = std::use_facet<std::codecvt<char16_t, char8_t, std::mbstate_t>>(cmdConsoleLocale);
    const char8_t* utf8Data = reinterpret_cast<const char8_t*>(data);
    std::mbstate_t utf8ToUtf16State = {};
    const char8_t* nextUtf8ToConvertToUtf16 = utf8Data;
    // NOLINTNEXTLINE(misc-const-correctness)
    char16_t* nextUtf16SlotToContainConvertedUtf8 = utf16Buffer;
    std::codecvt_base::result conversionResult = utf8ToUtf16Facet.in(utf8ToUtf16State, utf8Data, utf8Data + byteLength, nextUtf8ToConvertToUtf16, utf16Buffer, utf16Buffer + byteLength, nextUtf16SlotToContainConvertedUtf8);
    if(conversionResult != std::codecvt_base::ok){
        delete[] utf16Buffer;
        return "invalid string";
    }
    const int utf16Length = static_cast<int>(nextUtf16SlotToContainConvertedUtf8 - utf16Buffer);
    const std::codecvt<char16_t, char, std::mbstate_t>& utf16ToSystemEncodingFacet = std::use_facet<std::codecvt<char16_t, char, std::mbstate_t>>(cmdConsoleLocale);
    const int maximumSystemEncodingLength = (utf16Length * utf16ToSystemEncodingFacet.max_length()) + 1;
    mustDeleteOutputUsingArrayDelete = true;
    char* systemEncodingBuffer = new char[maximumSystemEncodingLength];
    std::mbstate_t utf16ToSystemEncodingState = {};
    const char16_t* nextUtf16ToConvertToSystemEncoding = utf16Buffer;
    char* nextSystemEncodingSlotToContainConvertedUtf16 = systemEncodingBuffer;
    conversionResult = utf16ToSystemEncodingFacet.out(utf16ToSystemEncodingState, utf16Buffer, utf16Buffer + utf16Length, nextUtf16ToConvertToSystemEncoding, systemEncodingBuffer, systemEncodingBuffer + maximumSystemEncodingLength, nextSystemEncodingSlotToContainConvertedUtf16);
    delete[] utf16Buffer;
    if(conversionResult != std::codecvt_base::ok){
        mustDeleteOutputUsingArrayDelete = false;
        delete[] systemEncodingBuffer;
        return "";
    }
    (*nextSystemEncodingSlotToContainConvertedUtf16) = '\0';
    return systemEncodingBuffer;
}
}

SGEXTN::CoreText::Debug::Debug(const SGEXTN::CoreText::String& fileName, int lineNumber) : debugInfo(""), metaInfo("") {
    SGEXTN::CoreText::String actualFileName = fileName.replaceCharacters("\\", "/");
    actualFileName = actualFileName.substringCharactersRight(actualFileName.characterLength() - actualFileName.findFirstCharactersFromRight("/") - 1);
    metaInfo = actualFileName + ", line " + SGEXTN::CoreText::String::stringFromInt(lineNumber, 10);
}

SGEXTN::CoreText::Debug::~Debug(){
    SGEXTN::CoreText::String logData = "";
    if(debugInfo == ""){logData = SGEXTN::CoreText::String("SG - ") + metaInfo;}
    else{logData = SGEXTN::CoreText::String("SG") + debugInfo;}
    bool mustDelete = false;
    const char* cString = printUtf8String(&logData.byteAt(0), logData.byteLength(), mustDelete);
    logCrashMessage(cString);
    if(mustDelete == true){delete[] cString;}
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(bool x){
    if(x == true){debugInfo += " - true";}
    else{debugInfo += " - false";}
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(unsigned char x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x), 10) + " or " + x;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(short x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromShort(x, 10);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(unsigned short x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromUnsignedShort(x, 10);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(int x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromInt(x, 10);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(unsigned int x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromUnsignedInt(x, 10);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(long long x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromLongLong(x, 10);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(unsigned long long x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromUnsignedLongLong(x, 10);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(float x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromFloat(x, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 5);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(double x){
    debugInfo += SGEXTN::CoreText::String(" - ") + SGEXTN::CoreText::String::stringFromDouble(x, 10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 5);
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(const SGEXTN::CoreText::Character& x){
    debugInfo += SGEXTN::CoreText::String(" - ") + x;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(const SGEXTN::CoreText::String& x){
    debugInfo += SGEXTN::CoreText::String(" - ") + x;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(const char* x){
    debugInfo += SGEXTN::CoreText::String(" - ") + x;
    return (*this);
}

void SGEXTN::CoreText::Debug::logCrashMessage(const char* msg){
    std::cerr << msg << "\n";
}
