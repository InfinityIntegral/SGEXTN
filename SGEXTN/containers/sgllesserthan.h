#ifndef SGLLESSERTHAN_H
#define SGLLESSERTHAN_H

#include "sglspan.h"

template <typename T> class SGLLesserThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> bool SGLLesserThan<T>::operator()(const T& a, const T& b) const {
    return (a < b);
}

template <typename T> class SGLLesserThan<T*> {
public:
    [[nodiscard]] bool operator()(T* const & a, T* const & b) const;
};

template <typename T> bool SGLLesserThan<T*>::operator()(T* const & a, T* const & b) const {
    SGLSpan<const unsigned char> spanA(reinterpret_cast<const unsigned char*>(&a), sizeof(T*));
    SGLSpan<const unsigned char> spanB(reinterpret_cast<const unsigned char*>(&b), sizeof(T*));
    for(int i=0; i<spanA.length(); i++){
        if(spanA.at(i) != spanB.at(i)){return (spanA.at(i) < spanB.at(i));}
    }
    return false;
}

#endif // SGLLESSERTHAN_H
