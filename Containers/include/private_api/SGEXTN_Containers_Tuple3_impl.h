#pragma once
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_Span.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_HashAlgorithm.h>

template <typename T1, typename T2, typename T3> SGEXTN::Containers::Tuple3<T1, T2, T3>::Tuple3(T1 first, T2 second, T3 third){
    (*this).first = first;
    (*this).second = second;
    (*this).third = third;
}

template <typename T1, typename T2, typename T3> bool SGEXTN::Containers::Tuple3<T1, T2, T3>::operator==(const Tuple3& x) const {
    return (first == x.first && second == x.second && third == x.third);
}

template <typename T1, typename T2, typename T3> bool SGEXTN::Containers::Tuple3<T1, T2, T3>::operator!=(const Tuple3& x) const {
    return (first != x.first || second != x.second || third != x.third);
}

template <typename T1, typename T2, typename T3> bool SGEXTN::Containers::Tuple3<T1, T2, T3>::operator<(const Tuple3& x) const {
    if(first != x.first){return (first < x.first);}
    if(second != x.second){return (second < x.second);}
    return (third < x.third);
}

template <typename T1, typename T2, typename T3> bool SGEXTN::Containers::Tuple3<T1, T2, T3>::operator>(const Tuple3& x) const {
    if(first != x.first){return (first > x.first);}
    if(second != x.second){return (second > x.second);}
    return (third > x.third);
}

template <typename T1, typename T2, typename T3> int SGEXTN::Containers::Tuple3<T1, T2, T3>::hash() const {
    SGEXTN::Containers::Array<int> hashArray(3);
    hashArray.at(0) = SGEXTN::Containers::Hash<T1>()(first);
    hashArray.at(1) = SGEXTN::Containers::Hash<T2>()(second);
    hashArray.at(2) = SGEXTN::Containers::Hash<T3>()(third);
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 3 * sizeof(int)));
}
