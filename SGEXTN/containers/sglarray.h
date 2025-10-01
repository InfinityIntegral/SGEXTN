#ifndef SGLARRAY_H
#define SGLARRAY_H

#include "sglcrash.h"

template <typename T> class SGLArray {
public:
    SGLArray(int count);
    SGLArray(int count, const T& defaultValue);
    SGLArray(const SGLArray& x);
    SGLArray& operator=(const SGLArray& x);
    SGLArray(SGLArray&& x) noexcept;
    SGLArray& operator=(SGLArray&& x) noexcept;
    ~SGLArray();
    void assign(int count, const T& defaultValue);
    void fill(const T& defaultValue);
    [[nodiscard]] int length() const;
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] T* pointerToData(int n);
protected:
    T* dataInternal;
    int lengthInternal;
};

template <typename T> SGLArray<T>::SGLArray(int count){
    dataInternal = new T[count];
    lengthInternal = count;
}

template <typename T> SGLArray<T>::SGLArray(int count, const T& defaultValue){
    dataInternal = new T[count];
    lengthInternal = count;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> SGLArray<T>::SGLArray(const SGLArray& x){
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
}

template <typename T> SGLArray<T>& SGLArray<T>::operator=(const SGLArray& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
    return (*this);
}

template <typename T> SGLArray<T>::SGLArray(SGLArray&& x) noexcept {
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
}

template <typename T> SGLArray<T>& SGLArray<T>::operator=(SGLArray&& x) noexcept {
    delete[] dataInternal;
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    return (*this);
}

template <typename T> SGLArray<T>::~SGLArray(){
    delete[] dataInternal;
}

template <typename T> void SGLArray<T>::assign(int count, const T& defaultValue){
    delete[] dataInternal;
    dataInternal = new T[count];
    lengthInternal = count;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> void SGLArray<T>::fill(const T& defaultValue){
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> int SGLArray<T>::length() const {
    return lengthInternal;
}

template <typename T> T& SGLArray<T>::at(int i){
    if(i < 0 || i >= lengthInternal){SGLCrash::crash();}
    return (*(dataInternal + i));
}

template <typename T> const T& SGLArray<T>::at(int i) const {
    if(i < 0 || i >= lengthInternal){SGLCrash::crash();}
    return (*(dataInternal + i));
}

template <typename T> T* SGLArray<T>::pointerToData(int n){
    return (dataInternal + n);
}

#endif // SGLARRAY_H
