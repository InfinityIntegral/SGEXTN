#ifndef SGLMORETHAN_H
#define SGLMORETHAN_H

template <typename T> class SGLMoreThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> bool SGLMoreThan<T>::operator()(const T& a, const T& b) const {
    return (a > b);
}

#endif // SGLMORETHAN_H
