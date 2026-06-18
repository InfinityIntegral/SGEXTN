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

template <typename T> SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(const T& x){
    if(debugInfo != ""){debugInfo += " - ";}
    debugInfo += debugPrint(x);
    return (*this);
}
