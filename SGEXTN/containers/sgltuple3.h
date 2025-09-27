#ifndef SGLTUPLE3_H
#define SGLTUPLE3_H

template <typename T1, typename T2, typename T3> class SGLTuple3 {
public:
    T1 first;
    T2 second;
    T3 third;
    SGLTuple3(T1 first, T2 second, T3 third);
};

template <typename T1, typename T2, typename T3> SGLTuple3<T1, T2, T3>::SGLTuple3(T1 first, T2 second, T3 third){
    (*this).first = first;
    (*this).second = second;
    (*this).third = third;
}

#endif // SGLTUPLE3_H
