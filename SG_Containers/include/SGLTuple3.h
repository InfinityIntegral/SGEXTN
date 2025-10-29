#ifndef SGLTUPLE3_H
#define SGLTUPLE3_H

#include <SGLHash.h>
#include <SGLSpan.h>
#include <SGLArray.h>
#include <SGLHashAlgorithm.h>

template <typename T1, typename T2, typename T3> class SGLTuple3 {
public:
    T1 first;
    T2 second;
    T3 third;
    SGLTuple3() = default;
    SGLTuple3(T1 first, T2 second, T3 third);
    [[nodiscard]] bool operator==(const SGLTuple3& x) const;
    [[nodiscard]] bool operator!=(const SGLTuple3& x) const;
    [[nodiscard]] bool operator<(const SGLTuple3& x) const;
    [[nodiscard]] bool operator>(const SGLTuple3& x) const;
    [[nodiscard]] int hash() const;
};

template <typename T1, typename T2, typename T3> SGLTuple3<T1, T2, T3>::SGLTuple3(T1 first, T2 second, T3 third){
    (*this).first = first;
    (*this).second = second;
    (*this).third = third;
}

template <typename T1, typename T2, typename T3> bool SGLTuple3<T1, T2, T3>::operator==(const SGLTuple3& x) const {
    return (first == x.first && second == x.second && third == x.third);
}

template <typename T1, typename T2, typename T3> bool SGLTuple3<T1, T2, T3>::operator!=(const SGLTuple3& x) const {
    return (first != x.first || second != x.second || third != x.third);
}

template <typename T1, typename T2, typename T3> bool SGLTuple3<T1, T2, T3>::operator<(const SGLTuple3& x) const {
    if(first < x.first){return true;}
    if(first > x.first){return false;}
    if(second < x.second){return true;}
    if(second > x.second){return false;}
    if(third < x.third){return true;}
    if(third > x.third){return false;}
    return false;
}

template <typename T1, typename T2, typename T3> bool SGLTuple3<T1, T2, T3>::operator>(const SGLTuple3& x) const {
    if(first < x.first){return false;}
    if(first > x.first){return true;}
    if(second < x.second){return false;}
    if(second > x.second){return true;}
    if(third < x.third){return false;}
    if(third > x.third){return true;}
    return false;
}

template <typename T1, typename T2, typename T3> int SGLTuple3<T1, T2, T3>::hash() const {
    SGLArray<int> hashArray(3);
    hashArray.at(0) = SGLHash<T1>()(first);
    hashArray.at(1) = SGLHash<T2>()(second);
    hashArray.at(2) = SGLHash<T3>()(third);
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 3 * sizeof(int)));
}

#endif // SGLTUPLE3_H
