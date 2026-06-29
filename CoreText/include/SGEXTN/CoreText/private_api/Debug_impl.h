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

template <typename T> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const T& x) const {
    return x.debugPrint();
}

template <typename T> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const T* x) const {
    if(x == nullptr){return "nullptr";}
    if(pointerMode == SGEXTN::CoreText::DebugPrintPointerMode::NullCheck){return "not nullptr";}
    return (SGEXTN::CoreText::String("&(") + debugPrint(*x) + ")");
}

template <typename T> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(T* x) const {
    if(x == nullptr){return "nullptr";}
    if(pointerMode == SGEXTN::CoreText::DebugPrintPointerMode::NullCheck){return "not nullptr";}
    return (SGEXTN::CoreText::String("&(") + debugPrint(*x) + ")");
}

template <typename ReturnType, typename... ArgTypes> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(ReturnType (*x)(ArgTypes...)) const {
    if(x == nullptr){return "nullptr";}
    return "not nullptr";
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(ReturnType (ClassName::*x)(ArgTypes...)) const {
    if(x == nullptr){return "nullptr";}
    return "not nullptr";
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(ReturnType (ClassName::*x)(ArgTypes...) const) const {
    if(x == nullptr){return "nullptr";}
    return "not nullptr";
}

template <typename T> SGEXTN::CoreText::String SGEXTN::CoreText::Debug::debugPrint(const SGEXTN::Containers::Array<T>& x) const {
    SGEXTN::CoreText::String output = "[";
    for(int i=0; i<x.length()-1; i++){
        output += debugPrint(x.at(i));
        output += ", ";
    }
    if(x.length() != 0){output += debugPrint(x.at(x.length() - 1));}
    output += "]";
    return output;
}

template <typename T> SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(const T& x){
    if(debugInfo != ""){debugInfo += " - ";}
    debugInfo += debugPrint(x);
    return (*this);
}
