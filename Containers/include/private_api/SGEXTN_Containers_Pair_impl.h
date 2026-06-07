#pragma once
#include <SGEXTN_Containers_Hash.h>

template <typename T1, typename T2> SGEXTN::Containers::Pair<T1, T2>::Pair() : first(), second() {}

template <typename T1, typename T2> SGEXTN::Containers::Pair<T1, T2>::Pair(const T1& first, const T2& second) : first(first), second(second) {}

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
    int hash1 = SGEXTN::Containers::Hash<T1>()(first);
    int hash2 = SGEXTN::Containers::Hash<T2>()(second);
    return SGEXTN::Containers::Hash<int, int>()(hash1, hash2);
}
