#pragma once
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_Span.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_HashAlgorithm.h>

template <typename T1, typename T2> SGEXTN::Containers::Pair<T1, T2>::Pair(T1 first, T2 second){
    (*this).first = first;
    (*this).second = second;
}

template <typename T1, typename T2> bool SGEXTN::Containers::Pair<T1, T2>::operator==(const Pair& x) const {
    return (first == x.first && second == x.second);
}

template <typename T1, typename T2> bool SGEXTN::Containers::Pair<T1, T2>::operator!=(const Pair& x) const {
    return (first != x.first || second != x.second);
}

template <typename T1, typename T2> bool SGEXTN::Containers::Pair<T1, T2>::operator<(const Pair& x) const {
    if(first != x.first){return (first < x.first);}
    return (second < x.second);
}

template <typename T1, typename T2> bool SGEXTN::Containers::Pair<T1, T2>::operator>(const Pair& x) const {
    if(first != x.first){return (first > x.first);}
    return (second > x.second);
}

template <typename T1, typename T2> int SGEXTN::Containers::Pair<T1, T2>::hash() const {
    SGEXTN::Containers::Array<int> hashArray(2);
    hashArray.at(0) = SGEXTN::Containers::Hash<T1>()(first);
    hashArray.at(1) = SGEXTN::Containers::Hash<T2>()(second);
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 2 * sizeof(int)));
}
