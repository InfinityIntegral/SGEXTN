#ifndef SGLSPAN_H
#define SGLSPAN_H

#include <private_api_Containers/SGLCrash.h>

template <typename T> class SGLSpan {
public:
    SGLSpan(T* dataInternal, int lengthInternal);
    [[nodiscard]] int length() const;
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] SGLSpan subspan(int start, int length) const;
    [[nodiscard]] SGLSpan subspanLeft(int length) const;
    [[nodiscard]] SGLSpan subspanRight(int length) const;
    [[nodiscard]] T* pointerToData(int n);
    [[nodiscard]] const T* pointerToData(int n) const;
protected:
    T* dataInternal;
    int lengthInternal;
};

template <typename T> SGLSpan<T>::SGLSpan(T* dataInternal, int lengthInternal){
    if(lengthInternal < 0){SGLCrash::crash("SGLSpan constructor crashed because the length is negative");}
    if(dataInternal == nullptr){SGLCrash::crash("SGLSpan constructor crashed because the data pointer is nullptr");}
    (*this).dataInternal = dataInternal;
    (*this).lengthInternal = lengthInternal;
}

template <typename T> int SGLSpan<T>::length() const {
    return lengthInternal;
}

template <typename T> T& SGLSpan<T>::at(int i){
    if(i < 0){SGLCrash::crash("SGLSpan::at crashed because the index is negative");}
    if(i >= lengthInternal){SGLCrash::crash("SGLSpan::at crashed because the index points beyond the end of the span");}
    return (*(dataInternal + i));
}

template <typename T> const T& SGLSpan<T>::at(int i) const {
    if(i < 0){SGLCrash::crash("SGLSpan::at crashed because the index is negative");}
    if(i >= lengthInternal){SGLCrash::crash("SGLSpan::at crashed because the index points beyond the end of the span");}
    return (*(dataInternal + i));
}

template <typename T> SGLSpan<T> SGLSpan<T>::subspan(int start, int length) const {
    if(length < 0){SGLCrash::crash("SGLSpan::subspan crashed because the length is negative");}
    if(start < 0){SGLCrash::crash("SGLSpan::subspan crashed because the starting point is negative");}
    if(start + length > lengthInternal){SGLCrash::crash("SGLSpan::subspan crashed because the ending point, which is start + length - 1, will point beyond the end of the span");}
    return SGLSpan(dataInternal + start, length);
}

template <typename T> SGLSpan<T> SGLSpan<T>::subspanLeft(int length) const {
    if(length < 0){SGLCrash::crash("SGLSpan::subspanLeft crashed because the length of the subspan is negative");}
    if(length > lengthInternal){SGLCrash::crash("SGLSpan::subspanLeft crashed because the length of the subspan exceeds the length of the original span");}
    return SGLSpan(dataInternal, length);
}

template <typename T> SGLSpan<T> SGLSpan<T>::subspanRight(int length) const {
    if(length < 0){SGLCrash::crash("SGLSpan::subspanRight crashed because the length of the subspan is negative");}
    if(length > lengthInternal){SGLCrash::crash("SGLSpan::subspanRight crashed because the length of the subspan exceeds the length of the original span");}
    return SGLSpan(dataInternal + lengthInternal - length, length);
}

template <typename T> T* SGLSpan<T>::pointerToData(int n){
    return (dataInternal + n);
}

template <typename T> const T* SGLSpan<T>::pointerToData(int n) const {
    return (dataInternal + n);
}

#endif // SGLSPAN_H
