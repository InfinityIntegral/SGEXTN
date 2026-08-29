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

#pragma once
#include <SGEXTN/Containers/private_api/TypeTraits.h>
#include <SGEXTN/CoreText/String.h>
#include <SGEXTN/CoreText/Character.h>
#include <SGEXTN/Containers/ForceCrash.h>

namespace SGEXTN::CoreText {
template <typename EnumClass, EnumClass E> class EnumNameExtractor {
public:
    [[nodiscard]] static SGEXTN::CoreText::String getName();
};

template <typename EnumClass, EnumClass E> SGEXTN::CoreText::String SGEXTN::CoreText::EnumNameExtractor<EnumClass, E>::getName(){
    SGEXTN::CoreText::String functionArgsSignature;
#ifdef _MSC_VER
    functionArgsSignature = __FUNCSIG__;
#elif defined(__GNUC__) || defined(__clang__)
    functionArgsSignature = __PRETTY_FUNCTION__;
#else
    return "(enum name not available)";
#endif
    if(functionArgsSignature.containsCharacters("::getName") == true && functionArgsSignature.findFirstCharactersFromRight("::getName") == functionArgsSignature.findFirstCharactersFromRight("::")){functionArgsSignature = functionArgsSignature.substringCharactersLeft(functionArgsSignature.findFirstCharactersFromRight("::getName"));}
    const int separatorIndex = functionArgsSignature.findFirstCharactersFromRight("::");
    if(separatorIndex == -1){return "(enum name not available)";}
    int nameBegin = separatorIndex - 1;
    int nameEnd = separatorIndex + 2;
    for(int i=nameBegin; i>0; i--){
        const SGEXTN::CoreText::Character nextChar = functionArgsSignature.getCharacterAt(i - 1);
        if(nextChar.isEnglishAlphanumeric() == false && nextChar != '_'){
            nameBegin = i;
            break;
        }
    }
    for(int i=nameEnd; i<functionArgsSignature.characterLength()-1; i++){
        const SGEXTN::CoreText::Character nextChar = functionArgsSignature.getCharacterAt(i + 1);
        if(nextChar.isEnglishAlphanumeric() == false && nextChar != '_'){
            nameEnd = i;
            break;
        }
    }
    SGEXTN::CoreText::String output = functionArgsSignature.substringCharacters(nameBegin, nameEnd - nameBegin + 1);
    output += (SGEXTN::CoreText::String(" (0x") + SGEXTN::CoreText::String::stringFromInt(static_cast<int>(static_cast<unsigned char>(E)), 16).fillLeftToCharacterLength(2, '0') + ")");
    return output;
}

template <typename EnumClass, unsigned char N> class EnumNameScanner {
public:
    static SGEXTN::CoreText::String scan(unsigned char current);
};

template <typename EnumClass, unsigned char N> SGEXTN::CoreText::String SGEXTN::CoreText::EnumNameScanner<EnumClass, N>::scan(unsigned char current){
    if(current == N){return SGEXTN::CoreText::EnumNameExtractor<EnumClass, static_cast<EnumClass>(N)>::getName();}
    if constexpr(N == static_cast<unsigned char>(0xff)){return "(enum name not available)";}
    else{return SGEXTN::CoreText::EnumNameScanner<EnumClass, N+1>::scan(current);}
}

template <typename EnumClass> class EnumNameScanner<EnumClass, static_cast<unsigned char>(0xff)> {
public:
    static SGEXTN::CoreText::String scan(unsigned char current);
};

template <typename EnumClass> SGEXTN::CoreText::String SGEXTN::CoreText::EnumNameScanner<EnumClass, 255>::scan(unsigned char current){
    if(current == 255){return SGEXTN::CoreText::EnumNameExtractor<EnumClass, static_cast<EnumClass>(255)>::getName();}
    return "(enum name not available)";
}
}

template <typename T> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const T& x) const {
    if constexpr(requires{SGEXTN::Containers::IsObjectPointer<T>::isPointer;} == true){
        if(x == nullptr){return "nullptr";}
        if(pointerMode == SGEXTN::CoreText::DebugPrintPointerMode::NullCheck){return "not nullptr";}
        return (SGEXTN::CoreText::String("&( ") + debugPrint(*x) + " )");
    }
    if constexpr(requires{SGEXTN::Containers::IsPointer<T>::isPointer;} == true){
        if(x == nullptr){return "nullptr";}
        return "not nullptr";
    }
    if constexpr (requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = SGEXTN::Containers::CreateInstance<T>::getInstance();} == false && requires{SGEXTN::Containers::CreateAssignable<unsigned char>::getInstance() = static_cast<unsigned char>(SGEXTN::Containers::CreateInstance<T>::getInstance());} == true && requires{SGEXTN::Containers::IsTrue<bool, sizeof(T) == 1>::isTrue;} == true){
        const unsigned char enumValue = static_cast<unsigned char>(x);
        return SGEXTN::CoreText::EnumNameScanner<T, static_cast<unsigned char>(0)>::scan(enumValue);
    }
    if constexpr(requires{x.debugPrint();} == true){return x.debugPrint();}
    SGEXTN_IMMEDIATE_CRASH("SGEXTN debugging utilities requires custom type T to have SGEXTN::CoreText::String T::debugPrint() const;  defined to work");
}

template <typename T> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const SGEXTN::Containers::Array<T>& x) const {
    SGEXTN::CoreText::String output = "[ ";
    for(int i=0; i<x.length()-1; i++){
        output += debugPrint(x.at(i));
        output += ", ";
    }
    if(x.length() != 0){output += debugPrint(x.at(x.length() - 1));}
    output += " ]";
    return output;
}

template <typename T> SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(const T& x){
    if(debugInfo != ""){debugInfo += " - ";}
    debugInfo += debugPrint(x);
    return (*this);
}
