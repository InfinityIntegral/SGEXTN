#ifndef SGLLESSERTHAN_H
#define SGLLESSERTHAN_H

template <typename T> class SGLLesserThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> bool SGLLesserThan<T>::operator()(const T& a, const T& b) const {
    return (a < b);
}

#endif // SGLLESSERTHAN_H
