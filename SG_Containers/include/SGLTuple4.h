#ifndef SGLTUPLE4_H
#define SGLTUPLE4_H

#include <SGLHash.h>
#include <SGLSpan.h>
#include <SGLArray.h>
#include <private_api_Containers/SGLHashAlgorithm.h>

template <typename T1, typename T2, typename T3, typename T4> class SGLTuple4 {
public:
    T1 first;
    T2 second;
    T3 third;
    T4 fourth;
    SGLTuple4() = default;
    SGLTuple4(T1 first, T2 second, T3 third, T4 fourth);
    [[nodiscard]] bool operator==(const SGLTuple4& x) const;
    [[nodiscard]] bool operator!=(const SGLTuple4& x) const;
    [[nodiscard]] bool operator<(const SGLTuple4& x) const;
    [[nodiscard]] bool operator>(const SGLTuple4& x) const;
    [[nodiscard]] int hash() const;
};

template <typename T1, typename T2, typename T3, typename T4> SGLTuple4<T1, T2, T3, T4>::SGLTuple4(T1 first, T2 second, T3 third, T4 fourth){
    (*this).first = first;
    (*this).second = second;
    (*this).third = third;
    (*this).fourth = fourth;
}

template <typename T1, typename T2, typename T3, typename T4> bool SGLTuple4<T1, T2, T3, T4>::operator==(const SGLTuple4& x) const {
    return (first == x.first && second == x.second && third == x.third && fourth == x.fourth);
}

template <typename T1, typename T2, typename T3, typename T4> bool SGLTuple4<T1, T2, T3, T4>::operator!=(const SGLTuple4& x) const {
    return (first != x.first || second != x.second || third != x.third || fourth != x.fourth);
}

template <typename T1, typename T2, typename T3, typename T4> bool SGLTuple4<T1, T2, T3, T4>::operator<(const SGLTuple4& x) const {
    if(first < x.first){return true;}
    if(first > x.first){return false;}
    if(second < x.second){return true;}
    if(second > x.second){return false;}
    if(third < x.third){return true;}
    if(third > x.third){return false;}
    if(fourth < x.fourth){return true;}
    if(fourth > x.fourth){return false;}
    return false;
}

template <typename T1, typename T2, typename T3, typename T4> bool SGLTuple4<T1, T2, T3, T4>::operator>(const SGLTuple4& x) const {
    if(first < x.first){return false;}
    if(first > x.first){return true;}
    if(second < x.second){return false;}
    if(second > x.second){return true;}
    if(third < x.third){return false;}
    if(third > x.third){return true;}
    if(fourth < x.fourth){return false;}
    if(fourth > x.fourth){return true;}
    return false;
}

template <typename T1, typename T2, typename T3, typename T4> int SGLTuple4<T1, T2, T3, T4>::hash() const {
    SGLArray<int> hashArray(4);
    hashArray.at(0) = SGLHash<T1>()(first);
    hashArray.at(1) = SGLHash<T2>()(second);
    hashArray.at(2) = SGLHash<T3>()(third);
    hashArray.at(3) = SGLHash<T4>()(fourth);
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 4 * sizeof(int)));
}

#endif // SGLTUPLE4_H
