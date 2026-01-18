#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> SGEXTN::Containers::Span<T>::Span(T* data, int length){
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span constructor crashed because the length is negative");}
    if(data == nullptr){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span constructor crashed because the data pointer is nullptr");}
    (*this).private_data = data;
    (*this).private_length = length;
}

template <typename T> int SGEXTN::Containers::Span<T>::length() const {
    return private_length;
}

template <typename T> T& SGEXTN::Containers::Span<T>::at(int i){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::at crashed because the index is negative");}
    if(i >= private_length){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::at crashed because the index points beyond the end of the span");}
    return (*(private_data + i));
}

template <typename T> const T& SGEXTN::Containers::Span<T>::at(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::at crashed because the index is negative");}
    if(i >= private_length){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::at crashed because the index points beyond the end of the span");}
    return (*(private_data + i));
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspan(int start, int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::subspan crashed because the length is negative");}
    if(start < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::subspan crashed because the starting point is negative");}
    if(start + length > private_length){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::subspan crashed because the ending point, which is start + length - 1, will point beyond the end of the span");}
    return SGEXTN::Containers::Span(private_data + start, length);
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspanLeft(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::subspanLeft crashed because the length of the subspan is negative");}
    if(length > private_length){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::subspanLeft crashed because the length of the subspan exceeds the length of the original span");}
    return SGEXTN::Containers::Span(private_data, length);
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspanRight(int length) const {
    if(length < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::subspanRight crashed because the length of the subspan is negative");}
    if(length > private_length){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span::subspanRight crashed because the length of the subspan exceeds the length of the original span");}
    return SGEXTN::Containers::Span(private_data + private_length - length, length);
}

template <typename T> T* SGEXTN::Containers::Span<T>::pointerToData(int n){
    return (private_data + n);
}

template <typename T> const T* SGEXTN::Containers::Span<T>::pointerToData(int n) const {
    return (private_data + n);
}
