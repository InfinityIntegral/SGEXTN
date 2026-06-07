#pragma once

template <typename T> SGEXTN::ApplicationBase::Debug& SGEXTN::ApplicationBase::Debug::operator()(const T& x){
    debugInfo += SGEXTN::ApplicationBase::String(" - ") + x.debugLog();
    return (*this);
}