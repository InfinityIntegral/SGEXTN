#pragma once

template <typename T> bool SGEXTN::Containers::EqualTo<T>::operator()(const T& a, const T& b) const {
    return (a == b);
}
