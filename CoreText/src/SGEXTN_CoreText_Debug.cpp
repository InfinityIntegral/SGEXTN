#include <SGEXTN_CoreText_Debug.h>
#include <SGEXTN_CoreText_Character.h>
#include <SGEXTN_CoreText_String.h>
#include <iostream>
#include <locale>
#include <cwchar>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_Vector.h>

namespace {
SGEXTN::CoreText::DebugLogFunctionRegistrarInstance useLogToCerr(&SGEXTN::CoreText::Debug::logToCerr);

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

constinit SGEXTN::Containers::Vector<void (*)(const char*)>* SGEXTN::CoreText::Debug::logFunctionList = nullptr;

SGEXTN::CoreText::Debug::Debug(const SGEXTN::CoreText::String& fileName, int lineNumber) : debugInfo(""), fileName(""), lineNumber(""), metadataMode(SGEXTN::CoreText::DebugPrintMetadataMode::None), integerMode(10), floatingPointMode(10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 5), cCharMode(SGEXTN::CoreText::DebugPrintCCharMode::Byte), stringMode(SGEXTN::CoreText::DebugPrintStringMode::String), pointerMode(SGEXTN::CoreText::DebugPrintPointerMode::NullCheck) {
    const SGEXTN::CoreText::String actualFilePath = fileName.replaceCharacters("\\", "/");
    (*this).fileName = actualFilePath.substringCharactersRight(actualFilePath.characterLength() - actualFilePath.findFirstCharactersFromRight("/") - 1);
    (*this).lineNumber = SGEXTN::CoreText::String("line ") + SGEXTN::CoreText::String::stringFromInt(lineNumber, 10);
}

SGEXTN::CoreText::Debug::~Debug(){
    if(debugInfo == ""){metadataMode = SGEXTN::CoreText::DebugPrintMetadataMode::All;}
    SGEXTN::CoreText::String logMessage = "SG";
    if(metadataMode == SGEXTN::CoreText::DebugPrintMetadataMode::Line){
        logMessage += " at ";
        logMessage += lineNumber;
    }
    else if(metadataMode == SGEXTN::CoreText::DebugPrintMetadataMode::All){
        logMessage += " in ";
        logMessage += fileName;
        logMessage += " at ";
        logMessage += lineNumber;
    }
    if(debugInfo != ""){
        logMessage += ": ";
        logMessage += debugInfo;
    }
    bool mustDelete = false;
    const char* cString = printUtf8String(&logMessage.byteAt(0), logMessage.byteLength(), mustDelete);
    for(int i=0; i<(*SGEXTN::CoreText::Debug::logFunctionList).length(); i++){
        ((*SGEXTN::CoreText::Debug::logFunctionList).at(i))(cString);
    }
    if(mustDelete == true){delete[] cString;}
}

// NOLINTBEGIN(readability-convert-member-functions-to-static)
SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(bool x) const {
    if(x == true){return "true";}
    return "false";
}

void SGEXTN::CoreText::Debug::logToCerr(const char* msg){
    std::cerr << msg << "\n";
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned char x) const {
    if(cCharMode == SGEXTN::CoreText::DebugPrintCCharMode::Character){return x;}
    return SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x), 16).fillLeftToCharacterLength(2, '0');
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(short x) const {
    return SGEXTN::CoreText::String::stringFromShort(x, integerMode.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned short x) const {
    return SGEXTN::CoreText::String::stringFromUnsignedShort(x, integerMode.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(int x) const {
    return SGEXTN::CoreText::String::stringFromInt(x, integerMode.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned int x) const {
    return SGEXTN::CoreText::String::stringFromUnsignedInt(x, integerMode.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(long long x) const {
    return SGEXTN::CoreText::String::stringFromLongLong(x, integerMode.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned long long x) const {
    return SGEXTN::CoreText::String::stringFromUnsignedLongLong(x, integerMode.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(float x) const {
    return SGEXTN::CoreText::String::stringFromFloat(x, floatingPointMode.base, floatingPointMode.format, floatingPointMode.precision);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(double x) const {
    return SGEXTN::CoreText::String::stringFromDouble(x, floatingPointMode.base, floatingPointMode.format, floatingPointMode.precision);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const SGEXTN::CoreText::Character& x) const {
    return debugPrint(SGEXTN::CoreText::String(x));
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const SGEXTN::CoreText::String& x) const {
    if(stringMode == SGEXTN::CoreText::DebugPrintStringMode::String){return x;}
    if(stringMode == SGEXTN::CoreText::DebugPrintStringMode::Byte){
        SGEXTN::CoreText::String output = "";
        if(x != ""){output += SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x.byteAt(0)), 16).fillLeftToCharacterLength(2, '0');}
        for(int i=1; i<x.byteLength(); i++){
            output += " ";
            output += SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x.byteAt(i)), 16).fillLeftToCharacterLength(2, '0');
        }
        return output;
    }
    if(stringMode == SGEXTN::CoreText::DebugPrintStringMode::CodePoint){
        SGEXTN::Containers::Array<int> unicode = x.getUnicode();
        SGEXTN::CoreText::String output = "";
        if(unicode.length() > 0){output += SGEXTN::CoreText::String::stringFromInt(unicode.at(0), 16).fillLeftToCharacterLength(4, '0');}
        for(int i=1; i<unicode.length(); i++){
            output += " ";
            output += SGEXTN::CoreText::String::stringFromInt(unicode.at(i), 16).fillLeftToCharacterLength(4, '0');
        }
        return output;
    }
    return "";
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(char x) const {
    if(cCharMode == SGEXTN::CoreText::DebugPrintCCharMode::Character){return x;}
    return SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x), 16).fillLeftToCharacterLength(2, '0');
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const char* x) const {
    return x;
}
// NOLINTEND(readability-convert-member-functions-to-static)

SGEXTN::CoreText::DebugPrintIntegerMode::DebugPrintIntegerMode(int base) : base(base) {}

SGEXTN::CoreText::DebugPrintFloatingPointMode::DebugPrintFloatingPointMode(int base, SGEXTN::CoreText::FloatPrecisionFormat format, int precision) : base(base), format(format), precision(precision) {}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintMetadataMode mode){
    metadataMode = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintIntegerMode mode){
    integerMode = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintFloatingPointMode mode){
    floatingPointMode = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintCCharMode mode){
    cCharMode = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintStringMode mode){
    stringMode = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintPointerMode mode){
    pointerMode = mode;
    return (*this);
}

SGEXTN::CoreText::DebugLogFunctionRegistrarInstance::DebugLogFunctionRegistrarInstance(void (*func)(const char*)){
    if(SGEXTN::CoreText::Debug::logFunctionList == nullptr){SGEXTN::CoreText::Debug::logFunctionList = new SGEXTN::Containers::Vector<void (*)(const char*)>();}
    (*SGEXTN::CoreText::Debug::logFunctionList).pushBack(func);
}
