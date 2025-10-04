#ifndef SGLTUPLE5_H
#define SGLTUPLE5_H

#include "sglhash.h"
#include "sglspan.h"
#include "sglarray.h"
#include "sglhashalgorithm.h"

template <typename T1, typename T2, typename T3, typename T4, typename T5> class SGLTuple5 {
public:
    T1 first;
    T2 second;
    T3 third;
    T4 fourth;
    T5 fifth;
    SGLTuple5() = default;
    SGLTuple5(T1 first, T2 second, T3 third, T4 fourth, T5 fifth);
    [[nodiscard]] bool operator==(const SGLTuple5& x) const;
    [[nodiscard]] bool operator!=(const SGLTuple5& x) const;
    [[nodiscard]] bool operator<(const SGLTuple5& x) const;
    [[nodiscard]] bool operator>(const SGLTuple5& x) const;
    [[nodiscard]] int hash() const;
};

template <typename T1, typename T2, typename T3, typename T4, typename T5> SGLTuple5<T1, T2, T3, T4, T5>::SGLTuple5(T1 first, T2 second, T3 third, T4 fourth, T5 fifth){
    (*this).first = first;
    (*this).second = second;
    (*this).third = third;
    (*this).fourth = fourth;
    (*this).fifth = fifth;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5> bool SGLTuple5<T1, T2, T3, T4, T5>::operator==(const SGLTuple5& x) const {
    return (first == x.first && second == x.second && third == x.third && fourth == x.fourth && fifth == x.fifth);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5> bool SGLTuple5<T1, T2, T3, T4, T5>::operator!=(const SGLTuple5& x) const {
    return (first != x.first || second != x.second || third != x.third || fourth != x.fourth || fifth != x.fifth);
}

template <typename T1, typename T2, typename T3, typename T4, typename T5> bool SGLTuple5<T1, T2, T3, T4, T5>::operator<(const SGLTuple5& x) const {
    if(first < x.first){return true;}
    if(first > x.first){return false;}
    if(second < x.second){return true;}
    if(second > x.second){return false;}
    if(third < x.third){return true;}
    if(third > x.third){return false;}
    if(fourth < x.fourth){return true;}
    if(fourth > x.fourth){return false;}
    if(fifth < x.fifth){return true;}
    if(fifth > x.fifth){return false;}
    return false;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5> bool SGLTuple5<T1, T2, T3, T4, T5>::operator>(const SGLTuple5& x) const {
    if(first < x.first){return false;}
    if(first > x.first){return true;}
    if(second < x.second){return false;}
    if(second > x.second){return true;}
    if(third < x.third){return false;}
    if(third > x.third){return true;}
    if(fourth < x.fourth){return false;}
    if(fourth > x.fourth){return true;}
    if(fifth < x.fifth){return false;}
    if(fifth > x.fifth){return true;}
    return false;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5> int SGLTuple5<T1, T2, T3, T4, T5>::hash() const {
    SGLArray<int> hashArray(5);
    hashArray.at(0) = SGLHash<T1>()(first);
    hashArray.at(1) = SGLHash<T2>()(second);
    hashArray.at(2) = SGLHash<T3>()(third);
    hashArray.at(3) = SGLHash<T4>()(fourth);
    hashArray.at(4) = SGLHash<T5>()(fifth);
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 5 * sizeof(int)));
}

#endif // SGLTUPLE5_H
