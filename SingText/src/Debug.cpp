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
#include <SGEXTN/SingText/Debug.h>
#undef SGEXTN_internal_permanentAllowDebug
#include <SGEXTN/SingText/Character.h>
#include <SGEXTN/SingText/String.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/Vector.h>
#include <iostream>

bool SGEXTN::SingText::Debug::registerFunction = (SGEXTN::SingText::DebugLogFunctionRegistrarInstance(&SGEXTN::SingText::Debug::logToCerr), true);

SGEXTN::Containers::Vector<void (*)(const char*)>* SGEXTN::SingText::Debug::logFunctionList = nullptr;
SGEXTN::SingText::DebugPrintIntegerMode SGEXTN::SingText::Debug::defaultIntegerMode = SGEXTN::SingText::DebugPrintIntegerMode(10);
SGEXTN::SingText::DebugPrintFloatingPointMode SGEXTN::SingText::Debug::defaultFloatingPointMode = SGEXTN::SingText::DebugPrintFloatingPointMode(10, SGEXTN::SingText::FloatPrecisionFormat::SignificantFigure, 5);
SGEXTN::SingText::DebugPrintCCharMode SGEXTN::SingText::Debug::defaultCCharMode = SGEXTN::SingText::DebugPrintCCharMode::Byte;
SGEXTN::SingText::DebugPrintStringMode SGEXTN::SingText::Debug::defaultStringMode = SGEXTN::SingText::DebugPrintStringMode::String;
SGEXTN::SingText::DebugPrintPointerMode SGEXTN::SingText::Debug::defaultPointerMode = SGEXTN::SingText::DebugPrintPointerMode::NullCheck;

SGEXTN::SingText::Debug::Debug(const SGEXTN::SingText::String& fileName, int lineNumber) : debugInfo_(""), fileName_(""), lineNumber_(""),  integerMode_(SGEXTN::SingText::Debug::defaultIntegerMode), floatingPointMode_(SGEXTN::SingText::Debug::defaultFloatingPointMode), cCharMode_(SGEXTN::SingText::Debug::defaultCCharMode), stringMode_(SGEXTN::SingText::Debug::defaultStringMode), pointerMode_(SGEXTN::SingText::Debug::defaultPointerMode){
    const SGEXTN::SingText::String actualFilePath = fileName.replaceCharacters("\\", "/");
    (*this).fileName_ = actualFilePath.substringCharactersRight(actualFilePath.characterLength() - actualFilePath.findFirstCharactersFromRight("/") - 1);
    (*this).lineNumber_ = SGEXTN::SingText::String("line ") + SGEXTN::SingText::String::stringFromInt(lineNumber, 10);
}

SGEXTN::SingText::Debug::~Debug(){
    SGEXTN::SingText::String logMessage = "SG";
    logMessage += " in ";
    logMessage += fileName_;
    logMessage += " at ";
    logMessage += lineNumber_;
    if(debugInfo_ != ""){
        logMessage += " : ";
        logMessage += debugInfo_;
    }
    logMessage += SGEXTN::SingText::Character('\0');
    const char* cString = reinterpret_cast<const char*>(logMessage.getRawPointer());
    for(int i=0; i<(*SGEXTN::SingText::Debug::logFunctionList).length(); i++){
        ((*SGEXTN::SingText::Debug::logFunctionList).at(i))(cString);
    }
}

void SGEXTN::SingText::Debug::logToCerr(const char* msg){
    std::cerr << msg << "\n";
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(bool x) const {
    int i = 0;
    if(cCharMode_ == SGEXTN::SingText::DebugPrintCCharMode::Character){i = 1;}
    if(i == -1){return "";}
    if(x == true){return "true";}
    return "false";
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(unsigned char x) const {
    if(cCharMode_ == SGEXTN::SingText::DebugPrintCCharMode::Character){return x;}
    return SGEXTN::SingText::String::stringFromInt(static_cast<int>(x), 16).fillLeftToCharacterLength(2, '0');
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(short x) const {
    return SGEXTN::SingText::String::stringFromShort(x, integerMode_.base_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(unsigned short x) const {
    return SGEXTN::SingText::String::stringFromUnsignedShort(x, integerMode_.base_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(int x) const {
    return SGEXTN::SingText::String::stringFromInt(x, integerMode_.base_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(unsigned int x) const {
    return SGEXTN::SingText::String::stringFromUnsignedInt(x, integerMode_.base_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(long long x) const {
    return SGEXTN::SingText::String::stringFromLongLong(x, integerMode_.base_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(unsigned long long x) const {
    return SGEXTN::SingText::String::stringFromUnsignedLongLong(x, integerMode_.base_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(float x) const {
    return SGEXTN::SingText::String::stringFromFloat(x, floatingPointMode_.base_, floatingPointMode_.format_, floatingPointMode_.precision_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(double x) const {
    return SGEXTN::SingText::String::stringFromDouble(x, floatingPointMode_.base_, floatingPointMode_.format_, floatingPointMode_.precision_);
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(const SGEXTN::SingText::Character& x) const {
    return debugPrint(SGEXTN::SingText::String(x));
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(const SGEXTN::SingText::String& x) const {
    if(stringMode_ == SGEXTN::SingText::DebugPrintStringMode::String){return x;}
    if(stringMode_ == SGEXTN::SingText::DebugPrintStringMode::Byte){
        SGEXTN::SingText::String output = "";
        if(x != ""){output += SGEXTN::SingText::String::stringFromInt(static_cast<int>(x.byteAt(0)), 16).fillLeftToCharacterLength(2, '0');}
        for(int i=1; i<x.byteLength(); i++){
            output += " ";
            output += SGEXTN::SingText::String::stringFromInt(static_cast<int>(x.byteAt(i)), 16).fillLeftToCharacterLength(2, '0');
        }
        return output;
    }
    if(stringMode_ == SGEXTN::SingText::DebugPrintStringMode::CodePoint){
        SGEXTN::Containers::Array<int> unicode = x.getUnicode();
        SGEXTN::SingText::String output = "";
        if(unicode.length() > 0){output += SGEXTN::SingText::String::stringFromInt(unicode.at(0), 16).fillLeftToCharacterLength(4, '0');}
        for(int i=1; i<unicode.length(); i++){
            output += " ";
            output += SGEXTN::SingText::String::stringFromInt(unicode.at(i), 16).fillLeftToCharacterLength(4, '0');
        }
        return output;
    }
    return "";
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(char x) const {
    if(cCharMode_ == SGEXTN::SingText::DebugPrintCCharMode::Character){return x;}
    return SGEXTN::SingText::String::stringFromInt(static_cast<int>(x), 16).fillLeftToCharacterLength(2, '0');
}

SGEXTN::SingText::String SGEXTN::SingText::Debug::debugPrint(const char* x) const {
    int i = 0;
    if(cCharMode_ == SGEXTN::SingText::DebugPrintCCharMode::Character){i = 1;}
    if(i == -1){return "";}
    return x;
}

SGEXTN::SingText::DebugPrintIntegerMode::DebugPrintIntegerMode(int base) : base_(base) {}

SGEXTN::SingText::DebugPrintFloatingPointMode::DebugPrintFloatingPointMode(int base, SGEXTN::SingText::FloatPrecisionFormat format, int precision) : base_(base), format_(format), precision_(precision) {}

SGEXTN::SingText::Debug& SGEXTN::SingText::Debug::operator()(SGEXTN::SingText::DebugPrintIntegerMode mode){
    integerMode_ = mode;
    return (*this);
}

SGEXTN::SingText::Debug& SGEXTN::SingText::Debug::operator()(SGEXTN::SingText::DebugPrintFloatingPointMode mode){
    floatingPointMode_ = mode;
    return (*this);
}

SGEXTN::SingText::Debug& SGEXTN::SingText::Debug::operator()(SGEXTN::SingText::DebugPrintCCharMode mode){
    cCharMode_ = mode;
    return (*this);
}

SGEXTN::SingText::Debug& SGEXTN::SingText::Debug::operator()(SGEXTN::SingText::DebugPrintStringMode mode){
    stringMode_ = mode;
    return (*this);
}

SGEXTN::SingText::Debug& SGEXTN::SingText::Debug::operator()(SGEXTN::SingText::DebugPrintPointerMode mode){
    pointerMode_ = mode;
    return (*this);
}

SGEXTN::SingText::DebugLogFunctionRegistrarInstance::DebugLogFunctionRegistrarInstance(void (*func)(const char*)){
    if(SGEXTN::SingText::Debug::logFunctionList == nullptr){SGEXTN::SingText::Debug::logFunctionList = new SGEXTN::Containers::Vector<void (*)(const char*)>();}
    (*SGEXTN::SingText::Debug::logFunctionList).pushBack(func);
}

SGEXTN::SingText::DebugDefaultModeOverride::DebugDefaultModeOverride(SGEXTN::SingText::DebugPrintIntegerMode newIntegerMode, SGEXTN::SingText::DebugPrintFloatingPointMode newFloatingPointMode, SGEXTN::SingText::DebugPrintCCharMode newCCharMode, SGEXTN::SingText::DebugPrintStringMode newStringMode, SGEXTN::SingText::DebugPrintPointerMode newPointerMode) : previousIntegerMode_(SGEXTN::SingText::Debug::defaultIntegerMode), previousFloatingPointMode_(SGEXTN::SingText::Debug::defaultFloatingPointMode), previousCCharMode_(SGEXTN::SingText::Debug::defaultCCharMode), previousStringMode_(SGEXTN::SingText::Debug::defaultStringMode), previousPointerMode_(SGEXTN::SingText::Debug::defaultPointerMode){
    SGEXTN::SingText::Debug::defaultIntegerMode = newIntegerMode;
    SGEXTN::SingText::Debug::defaultFloatingPointMode = newFloatingPointMode;
    SGEXTN::SingText::Debug::defaultCCharMode = newCCharMode;
    SGEXTN::SingText::Debug::defaultStringMode = newStringMode;
    SGEXTN::SingText::Debug::defaultPointerMode = newPointerMode;
}

SGEXTN::SingText::DebugDefaultModeOverride::~DebugDefaultModeOverride(){
    SGEXTN::SingText::Debug::defaultIntegerMode = previousIntegerMode_;
    SGEXTN::SingText::Debug::defaultFloatingPointMode = previousFloatingPointMode_;
    SGEXTN::SingText::Debug::defaultCCharMode = previousCCharMode_;
    SGEXTN::SingText::Debug::defaultStringMode = previousStringMode_;
    SGEXTN::SingText::Debug::defaultPointerMode = previousPointerMode_;
}
