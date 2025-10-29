#ifndef SGLMORETHAN_H
#define SGLMORETHAN_H

#include <SGLSpan.h>

template <typename T> class SGLMoreThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> bool SGLMoreThan<T>::operator()(const T& a, const T& b) const {
    return (a > b);
}

template <typename T> class SGLMoreThan<T*> {
public:
    [[nodiscard]] bool operator()(T* const & a, T* const & b) const;
};

template <typename T> bool SGLMoreThan<T*>::operator()(T* const & a, T* const & b) const {
    SGLSpan<const unsigned char> spanA(reinterpret_cast<const unsigned char*>(&a), sizeof(T*));
    SGLSpan<const unsigned char> spanB(reinterpret_cast<const unsigned char*>(&b), sizeof(T*));
    for(int i=0; i<spanA.length(); i++){
        if(spanA.at(i) != spanB.at(i)){return (spanA.at(i) > spanB.at(i));}
    }
    return false;
}

#endif // SGLMORETHAN_H
