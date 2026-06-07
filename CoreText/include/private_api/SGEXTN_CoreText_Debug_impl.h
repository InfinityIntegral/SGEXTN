#pragma once

template <typename T> SGEXTN::CoreText::Debug& SGEXTN::CoreText::Debug::operator()(const T& x){
    debugInfo += SGEXTN::CoreText::String(" - ") + x.debugLog();
    return (*this);
}