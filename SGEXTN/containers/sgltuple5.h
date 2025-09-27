#ifndef SGLTUPLE5_H
#define SGLTUPLE5_H

template <typename T1, typename T2, typename T3, typename T4, typename T5> class SGLTuple5 {
public:
    T1 first;
    T2 second;
    T3 third;
    T4 fourth;
    T5 fifth;
    SGLTuple5(T1 first, T2 second, T3 third, T4 fourth, T5 fifth);
};

template <typename T1, typename T2, typename T3, typename T4, typename T5> SGLTuple5<T1, T2, T3, T4, T5>::SGLTuple5(T1 first, T2 second, T3 third, T4 fourth, T5 fifth){
    (*this).first = first;
    (*this).second = second;
    (*this).third = third;
    (*this).fourth = fourth;
    (*this).fifth = fifth;
}

#endif // SGLTUPLE5_H
