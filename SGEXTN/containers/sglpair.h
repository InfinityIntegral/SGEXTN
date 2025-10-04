#ifndef SGLPAIR_H
#define SGLPAIR_H

#include "sglhash.h"
#include "sglspan.h"
#include "sglarray.h"
#include "sglhashalgorithm.h"

template <typename T1, typename T2> class SGLPair {
public:
    T1 first;
    T2 second;
    SGLPair() = default;
    SGLPair(T1 first, T2 second);
    [[nodiscard]] bool operator==(const SGLPair& x) const;
    [[nodiscard]] bool operator!=(const SGLPair& x) const;
    [[nodiscard]] bool operator<(const SGLPair& x) const;
    [[nodiscard]] bool operator>(const SGLPair& x) const;
    [[nodiscard]] int hash() const;
};

template <typename T1, typename T2> SGLPair<T1, T2>::SGLPair(T1 first, T2 second){
    (*this).first = first;
    (*this).second = second;
}

template <typename T1, typename T2> bool SGLPair<T1, T2>::operator==(const SGLPair& x) const {
    return (first == x.first && second == x.second);
}

template <typename T1, typename T2> bool SGLPair<T1, T2>::operator!=(const SGLPair& x) const {
    return (first != x.first || second != x.second);
}

template <typename T1, typename T2> bool SGLPair<T1, T2>::operator<(const SGLPair& x) const {
    if(first < x.first){return true;}
    if(first > x.first){return false;}
    if(second < x.second){return true;}
    if(second > x.second){return false;}
    return false;
}

template <typename T1, typename T2> bool SGLPair<T1, T2>::operator>(const SGLPair& x) const {
    if(first < x.first){return false;}
    if(first > x.first){return true;}
    if(second < x.second){return false;}
    if(second > x.second){return true;}
    return false;
}

template <typename T1, typename T2> int SGLPair<T1, T2>::hash() const {
    SGLArray<int> hashArray(2);
    hashArray.at(0) = SGLHash<T1>()(first);
    hashArray.at(1) = SGLHash<T2>()(second);
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 2 * sizeof(int)));
}

#endif // SGLPAIR_H
