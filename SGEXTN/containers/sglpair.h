#ifndef SGLPAIR_H
#define SGLPAIR_H

template <typename T1, typename T2> class SGLPair {
public:
    T1 first;
    T2 second;
    SGLPair(T1 first, T2 second);
};

template <typename T1, typename T2> SGLPair<T1, T2>::SGLPair(T1 first, T2 second){
    (*this).first = first;
    (*this).second = second;
}

#endif // SGLPAIR_H
