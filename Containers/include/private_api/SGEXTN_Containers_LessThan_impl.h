#pragma once
#include <SGEXTN_Containers_Span.h>

template <typename T> bool SGEXTN::Containers::LessThan<T>::operator()(const T& a, const T& b) const {
    return (a < b);
}

template <typename T> bool SGEXTN::Containers::LessThan<T*>::operator()(T* const& a, T* const& b) const {
    return (reinterpret_cast<unsigned long long>(a) < reinterpret_cast<unsigned long long>(b));
}
