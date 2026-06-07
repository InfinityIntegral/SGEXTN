#include <SGEXTN_ApplicationBase_Debug.h>
#include <SGEXTN_ApplicationBase_Character.h>
#include <SGEXTN_ApplicationBase_String.h>
#include <iostream>
#include <locale>
#include <cstddef>

namespace {
const char* printUtf8String(unsigned char* data, int byteLength, bool& mustDeleteOutputUsingArrayDelete){
    mustDeleteOutputUsingArrayDelete = false;
    if(byteLength == 0){return "";}
    std::locale cmdConsoleLocale("");
    char16_t* utf16Buffer = new char16_t[byteLength];
    const std::codecvt<char16_t, char8_t, std::mbstate_t>& utf8ToUtf16Facet = std::use_facet<std::codecvt<char16_t, char8_t, std::mbstate_t>>(cmdConsoleLocale);
    const char8_t* utf8Data = reinterpret_cast<const char8_t*>(data);
    std::mbstate_t utf8ToUtf16State = {};
    const char8_t* nextUtf8ToConvertToUtf16 = utf8Data;
    char16_t* nextUtf16SlotToContainConvertedUtf8 = utf16Buffer;
    std::codecvt_base::result conversionResult = utf8ToUtf16Facet.in(utf8ToUtf16State, utf8Data, utf8Data + byteLength, nextUtf8ToConvertToUtf16, utf16Buffer, utf16Buffer + byteLength, nextUtf16SlotToContainConvertedUtf8);
    if(conversionResult != std::codecvt_base::ok){
        delete[] utf16Buffer;
        return "invalid string";
    }
    int utf16Length = static_cast<int>(nextUtf16SlotToContainConvertedUtf8 - utf16Buffer);
    const std::codecvt<char16_t, char, std::mbstate_t>& utf16ToSystemEncodingFacet = std::use_facet<std::codecvt<char16_t, char, std::mbstate_t>>(cmdConsoleLocale);
    int maximumSystemEncodingLength = (utf16Length * utf16ToSystemEncodingFacet.max_length()) + 1;
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

SGEXTN::ApplicationBase::Debug::Debug(const SGEXTN::ApplicationBase::String& fileName, int lineNumber) : debugInfo(""), metaInfo("") {
    SGEXTN::ApplicationBase::String actualFileName = fileName.replaceCharacters("\\", "/");
    actualFileName = actualFileName.substringCharactersRight(actualFileName.characterLength() - actualFileName.findFirstCharactersFromRight("/") - 1);
    metaInfo = actualFileName + ", line " + SGEXTN::ApplicationBase::String::stringFromInt(lineNumber, 10);
}

SGEXTN::ApplicationBase::Debug::~Debug(){
    SGEXTN::ApplicationBase::String logData = "";
    if(debugInfo == ""){logData = SGEXTN::ApplicationBase::String("SG - ") + metaInfo;}
    else{logData = SGEXTN::ApplicationBase::String("SG") + debugInfo;}
    bool mustDelete = false;
    const char* cString = printUtf8String(&logData.byteAt(0), logData.byteLength(), mustDelete);
    std::cerr << cString << "\n";
    if(mustDelete == true){delete[] cString;}
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(bool x){
    if(x == true){debugInfo += " - true";}
    else{debugInfo += " - false";}
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned char x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromInt(static_cast<int>(x), 10) + " or " + x;
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(short x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromShort(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned short x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromUnsignedShort(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(int x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromInt(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned int x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromUnsignedInt(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(long long x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromLongLong(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(unsigned long long x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromUnsignedLongLong(x, 10);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(float x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromFloat(x, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 5);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(double x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + SGEXTN::ApplicationBase::String::stringFromDouble(x, 10, SGEXTN::ApplicationBase::FloatPrecisionFormat::SignificantFigure, 5);
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const SGEXTN::ApplicationBase::Character& x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + x;
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const SGEXTN::ApplicationBase::String& x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + x;
    return (*this);
}

SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const char* x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + x;
    return (*this);
}

void SGEXTN::ApplicationBase::Debug::logCrashMessage(const char* msg){
    SG(msg);
}
