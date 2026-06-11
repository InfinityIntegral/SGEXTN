#pragma once
#include <SGEXTN_Containers_ForceCrash.h>
#include <private_api/SGEXTN_Containers_Sort.h>

template <typename T> SGEXTN::Containers::Span<T>::Span(T* data, int length) : private_data(data), private_length(length) {
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span constructor crashed because the length is negative");}
    if(data == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span constructor crashed because the data pointer is nullptr");}
}

template <typename T> int SGEXTN::Containers::Span<T>::length() const {
    return private_length;
}

template <typename T> T& SGEXTN::Containers::Span<T>::at(int i){
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index is negative");}
    if(i >= private_length){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index points beyond the end of the span");}
    return (*(private_data + i));
}

template <typename T> const T& SGEXTN::Containers::Span<T>::at(int i) const {
    if(i < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index is negative");}
    if(i >= private_length){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::at crashed because the index points beyond the end of the span");}
    return (*(private_data + i));
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspan(int start, int length) const {
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspan crashed because the length is negative");}
    if(start < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspan crashed because the starting point is negative");}
    if(start + length > private_length){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspan crashed because the ending point, which is start + length - 1, will point beyond the end of the span");}
    return SGEXTN::Containers::Span(private_data + start, length);
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspanLeft(int length) const {
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanLeft crashed because the length of the subspan is negative");}
    if(length > private_length){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanLeft crashed because the length of the subspan exceeds the length of the original span");}
    return SGEXTN::Containers::Span(private_data, length);
}

template <typename T> SGEXTN::Containers::Span<T> SGEXTN::Containers::Span<T>::subspanRight(int length) const {
    if(length < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanRight crashed because the length of the subspan is negative");}
    if(length > private_length){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::subspanRight crashed because the length of the subspan exceeds the length of the original span");}
    return SGEXTN::Containers::Span(private_data + private_length - length, length);
}

template <typename T> template <typename Comparator> void SGEXTN::Containers::Span<T>::sort(int start, int length){
    if(start < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::sort crashed because start of range is negative");}
    if(start + length > (*this).length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span::sort crashed because end of range points beyond the end of the span");}
    SGEXTN::Containers::Sort<T, Comparator>::private_sort(private_data + start, length);
}