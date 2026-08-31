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

#define SGEXTN_internal_permanentAllowDebug
#include <SGEXTN/CoreText/Debug.h>
#undef SGEXTN_internal_permanentAllowDebug
#include <SGEXTN/CoreText/Character.h>
#include <SGEXTN/CoreText/String.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/Vector.h>
#include <iostream>

bool SGEXTN::CoreText::Debug::registerFunction = (SGEXTN::CoreText::DebugLogFunctionRegistrarInstance(&SGEXTN::CoreText::Debug::logToCerr), true);

SGEXTN::Containers::Vector<void (*)(const char*)>* SGEXTN::CoreText::Debug::logFunctionList = nullptr;
SGEXTN::CoreText::DebugPrintIntegerMode SGEXTN::CoreText::Debug::defaultIntegerMode = SGEXTN::CoreText::DebugPrintIntegerMode(10);
SGEXTN::CoreText::DebugPrintFloatingPointMode SGEXTN::CoreText::Debug::defaultFloatingPointMode = SGEXTN::CoreText::DebugPrintFloatingPointMode(10, SGEXTN::CoreText::FloatPrecisionFormat::SignificantFigure, 5);
SGEXTN::CoreText::DebugPrintCCharMode SGEXTN::CoreText::Debug::defaultCCharMode = SGEXTN::CoreText::DebugPrintCCharMode::Byte;
SGEXTN::CoreText::DebugPrintStringMode SGEXTN::CoreText::Debug::defaultStringMode = SGEXTN::CoreText::DebugPrintStringMode::String;
SGEXTN::CoreText::DebugPrintPointerMode SGEXTN::CoreText::Debug::defaultPointerMode = SGEXTN::CoreText::DebugPrintPointerMode::NullCheck;

SGEXTN::CoreText::Debug::Debug(const SGEXTN::CoreText::String& fileName, int lineNumber) : debugInfo_(""), fileName_(""), lineNumber_(""),  integerMode_(SGEXTN::CoreText::Debug::defaultIntegerMode), floatingPointMode_(SGEXTN::CoreText::Debug::defaultFloatingPointMode), cCharMode_(SGEXTN::CoreText::Debug::defaultCCharMode), stringMode_(SGEXTN::CoreText::Debug::defaultStringMode), pointerMode_(SGEXTN::CoreText::Debug::defaultPointerMode){
    const SGEXTN::CoreText::String actualFilePath = fileName.replaceCharacters("\\", "/");
    (*this).fileName_ = actualFilePath.substringCharactersRight(actualFilePath.characterLength() - actualFilePath.findFirstCharactersFromRight("/") - 1);
    (*this).lineNumber_ = SGEXTN::CoreText::String("line ") + SGEXTN::CoreText::String::stringFromInt(lineNumber, 10);
}

SGEXTN::CoreText::Debug::~Debug(){
    SGEXTN::CoreText::String logMessage = "SG";
    logMessage += " in ";
    logMessage += fileName_;
    logMessage += " at ";
    logMessage += lineNumber_;
    if(debugInfo_ != ""){
        logMessage += " : ";
        logMessage += debugInfo_;
    }
    logMessage += SGEXTN::CoreText::Character('\0');
    const char* cString = reinterpret_cast<const char*>(logMessage.getRawPointer());
    for(int i=0; i<(*SGEXTN::CoreText::Debug::logFunctionList).length(); i++){
        ((*SGEXTN::CoreText::Debug::logFunctionList).at(i))(cString);
    }
}

void SGEXTN::CoreText::Debug::logToCerr(const char* msg){
    std::cerr << msg << "\n";
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(bool x) const {
    int i = 0;
    if(cCharMode_ == SGEXTN::CoreText::DebugPrintCCharMode::Character){i = 1;}
    if(i == -1){return "";}
    if(x == true){return "true";}
    return "false";
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned char x) const {
    if(cCharMode_ == SGEXTN::CoreText::DebugPrintCCharMode::Character){return x;}
    return SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x), 16).fillLeftToCharacterLength(2, '0');
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(short x) const {
    return SGEXTN::CoreText::String::stringFromShort(x, integerMode_.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned short x) const {
    return SGEXTN::CoreText::String::stringFromUnsignedShort(x, integerMode_.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(int x) const {
    return SGEXTN::CoreText::String::stringFromInt(x, integerMode_.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned int x) const {
    return SGEXTN::CoreText::String::stringFromUnsignedInt(x, integerMode_.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(long long x) const {
    return SGEXTN::CoreText::String::stringFromLongLong(x, integerMode_.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(unsigned long long x) const {
    return SGEXTN::CoreText::String::stringFromUnsignedLongLong(x, integerMode_.base);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(float x) const {
    return SGEXTN::CoreText::String::stringFromFloat(x, floatingPointMode_.base, floatingPointMode_.format, floatingPointMode_.precision);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(double x) const {
    return SGEXTN::CoreText::String::stringFromDouble(x, floatingPointMode_.base, floatingPointMode_.format, floatingPointMode_.precision);
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const SGEXTN::CoreText::Character& x) const {
    return debugPrint(SGEXTN::CoreText::String(x));
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const SGEXTN::CoreText::String& x) const {
    if(stringMode_ == SGEXTN::CoreText::DebugPrintStringMode::String){return x;}
    if(stringMode_ == SGEXTN::CoreText::DebugPrintStringMode::Byte){
        SGEXTN::CoreText::String output = "";
        if(x != ""){output += SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x.byteAt(0)), 16).fillLeftToCharacterLength(2, '0');}
        for(int i=1; i<x.byteLength(); i++){
            output += " ";
            output += SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x.byteAt(i)), 16).fillLeftToCharacterLength(2, '0');
        }
        return output;
    }
    if(stringMode_ == SGEXTN::CoreText::DebugPrintStringMode::CodePoint){
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
    if(cCharMode_ == SGEXTN::CoreText::DebugPrintCCharMode::Character){return x;}
    return SGEXTN::CoreText::String::stringFromInt(static_cast<int>(x), 16).fillLeftToCharacterLength(2, '0');
}

SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const char* x) const {
    int i = 0;
    if(cCharMode_ == SGEXTN::CoreText::DebugPrintCCharMode::Character){i = 1;}
    if(i == -1){return "";}
    return x;
}

SGEXTN::CoreText::DebugPrintIntegerMode::DebugPrintIntegerMode(int base) : base(base) {}

SGEXTN::CoreText::DebugPrintFloatingPointMode::DebugPrintFloatingPointMode(int base, SGEXTN::CoreText::FloatPrecisionFormat format, int precision) : base(base), format(format), precision(precision) {}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintIntegerMode mode){
    integerMode_ = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintFloatingPointMode mode){
    floatingPointMode_ = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintCCharMode mode){
    cCharMode_ = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintStringMode mode){
    stringMode_ = mode;
    return (*this);
}

SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(SGEXTN::CoreText::DebugPrintPointerMode mode){
    pointerMode_ = mode;
    return (*this);
}

SGEXTN::CoreText::DebugLogFunctionRegistrarInstance::DebugLogFunctionRegistrarInstance(void (*func)(const char*)){
    if(SGEXTN::CoreText::Debug::logFunctionList == nullptr){SGEXTN::CoreText::Debug::logFunctionList = new SGEXTN::Containers::Vector<void (*)(const char*)>();}
    (*SGEXTN::CoreText::Debug::logFunctionList).pushBack(func);
}

SGEXTN::CoreText::DebugDefaultModeOverride::DebugDefaultModeOverride(SGEXTN::CoreText::DebugPrintIntegerMode newIntegerMode, SGEXTN::CoreText::DebugPrintFloatingPointMode newFloatingPointMode, SGEXTN::CoreText::DebugPrintCCharMode newCCharMode, SGEXTN::CoreText::DebugPrintStringMode newStringMode, SGEXTN::CoreText::DebugPrintPointerMode newPointerMode) : previousIntegerMode_(SGEXTN::CoreText::Debug::defaultIntegerMode), previousFloatingPointMode_(SGEXTN::CoreText::Debug::defaultFloatingPointMode), previousCCharMode_(SGEXTN::CoreText::Debug::defaultCCharMode), previousStringMode_(SGEXTN::CoreText::Debug::defaultStringMode), previousPointerMode_(SGEXTN::CoreText::Debug::defaultPointerMode){
    SGEXTN::CoreText::Debug::defaultIntegerMode = newIntegerMode;
    SGEXTN::CoreText::Debug::defaultFloatingPointMode = newFloatingPointMode;
    SGEXTN::CoreText::Debug::defaultCCharMode = newCCharMode;
    SGEXTN::CoreText::Debug::defaultStringMode = newStringMode;
    SGEXTN::CoreText::Debug::defaultPointerMode = newPointerMode;
}

SGEXTN::CoreText::DebugDefaultModeOverride::~DebugDefaultModeOverride(){
    SGEXTN::CoreText::Debug::defaultIntegerMode = previousIntegerMode_;
    SGEXTN::CoreText::Debug::defaultFloatingPointMode = previousFloatingPointMode_;
    SGEXTN::CoreText::Debug::defaultCCharMode = previousCCharMode_;
    SGEXTN::CoreText::Debug::defaultStringMode = previousStringMode_;
    SGEXTN::CoreText::Debug::defaultPointerMode = previousPointerMode_;
}
