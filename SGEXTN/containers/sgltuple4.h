#ifndef SGLTUPLE4_H
#define SGLTUPLE4_H

template <typename T1, typename T2, typename T3, typename T4> class SGLTuple4 {
public:
    T1 first;
    T2 second;
    T3 third;
    T4 fourth;
    SGLTuple4(T1 first, T2 second, T3 third, T4 fourth);
};

template <typename T1, typename T2, typename T3, typename T4> SGLTuple4<T1, T2, T3, T4>::SGLTuple4(T1 first, T2 second, T3 third, T4 fourth){
    (*this).first = first;
    (*this).second = second;
    (*this).third = third;
    (*this).fourth = fourth;
}

#endif // SGLTUPLE4_H
