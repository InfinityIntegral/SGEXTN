#ifndef SGLSPAN_H
#define SGLSPAN_H

template <typename T> class SGLSpan {
public:
    SGLSpan(T* dataInternal, int lengthInternal);
    [[nodiscard]] int length() const;
    [[nodiscard]] T& at(int i) const;
    [[nodiscard]] SGLSpan subspan(int start, int length) const;
    [[nodiscard]] SGLSpan subspanLeft(int length) const;
    [[nodiscard]] SGLSpan subspanRight(int length) const;
    [[nodiscard]] T* pointerToData(int n) const;
protected:
    T* dataInternal;
    int lengthInternal;
};

template <typename T> SGLSpan<T>::SGLSpan(T* dataInternal, int lengthInternal){
    (*this).dataInternal = dataInternal;
    (*this).lengthInternal = lengthInternal;
}

template <typename T> int SGLSpan<T>::length() const {
    return lengthInternal;
}

template <typename T> T& SGLSpan<T>::at(int i) const {
    return (*(dataInternal + i));
}

template <typename T> SGLSpan<T> SGLSpan<T>::subspan(int start, int length) const {
    return SGLSpan(dataInternal + start, length);
}

template <typename T> SGLSpan<T> SGLSpan<T>::subspanLeft(int length) const {
    return SGLSpan(dataInternal, length);
}

template <typename T> SGLSpan<T> SGLSpan<T>::subspanRight(int length) const {
    return SGLSpan(dataInternal + lengthInternal - length, length);
}

template <typename T> T* SGLSpan<T>::pointerToData(int n) const {
    return (dataInternal + n);
}

#endif // SGLSPAN_H
