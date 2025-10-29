#ifndef SGLEQUALSTO_H
#define SGLEQUALSTO_H

template <typename T> class SGLEqualsTo {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> bool SGLEqualsTo<T>::operator()(const T& a, const T& b) const {
    return (a == b);
}

#endif // SGLEQUALSTO_H
