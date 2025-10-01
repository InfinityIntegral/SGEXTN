#ifndef SGLVECTOR_H
#define SGLVECTOR_H

#include "sglcrash.h"

template <typename T> class SGLVector {
public:
    SGLVector();
    SGLVector(int count);
    SGLVector(int count, const T& defaultValue);
    SGLVector(const SGLVector& x);
    SGLVector& operator=(const SGLVector& x);
    SGLVector(SGLVector&& x) noexcept;
    SGLVector& operator=(SGLVector&& x) noexcept;
    ~SGLVector();
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] const T& back() const;
    [[nodiscard]] int length() const;
    void assign(int count, const T& defaultValue);
    void fill(const T& defaultValue);
    void reserve(int newMemoryLength);
    void pushBack(const T& x);
    void popBack();
    [[nodiscard]] T* pointerToData(int n);
protected:
    T* dataInternal;
    int lengthInternal;
    int memoryLengthInternal;
};

template <typename T> SGLVector<T>::SGLVector(){
    dataInternal = nullptr;
    lengthInternal = 0;
    memoryLengthInternal = 0;
}

template <typename T> SGLVector<T>::SGLVector(int count){
    dataInternal = new T[count];
    lengthInternal = count;
    memoryLengthInternal = count;
}

template <typename T> SGLVector<T>::SGLVector(int count, const T& defaultValue){
    dataInternal = new T[count];
    lengthInternal = count;
    memoryLengthInternal = count;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> SGLVector<T>::SGLVector(const SGLVector& x){
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.lengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
}

template <typename T> SGLVector<T>& SGLVector<T>::operator=(const SGLVector& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.lengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
}

template <typename T> SGLVector<T>::SGLVector(SGLVector&& x) noexcept {
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryLengthInternal = 0;
}

template <typename T> SGLVector<T>& SGLVector<T>::operator=(SGLVector&& x) noexcept {
    delete[] dataInternal;
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryLengthInternal = 0;
}

template <typename T> SGLVector<T>::~SGLVector(){
    delete[] dataInternal;
}

template <typename T> T& SGLVector<T>::at(int i){
    if(i < 0 || i > lengthInternal){SGLCrash::crash();}
    return (*(dataInternal + i));
}

template <typename T> const T& SGLVector<T>::at(int i) const {
    if(i < 0 || i > lengthInternal){SGLCrash::crash();}
    return (*(dataInternal + i));
}

template <typename T> const T& SGLVector<T>::back() const {
    return (*(dataInternal + lengthInternal - 1));
}

template <typename T> int SGLVector<T>::length() const {
    return lengthInternal;
}

template <typename T> void SGLVector<T>::assign(int count, const T& defaultValue){
    delete[] dataInternal;
    dataInternal = new T[count];
    lengthInternal = count;
    memoryLengthInternal = count;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> void SGLVector<T>::fill(const T& defaultValue){
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> void SGLVector<T>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    T* oldPointer = dataInternal;
    dataInternal = new T[newMemoryLength];
    memoryLengthInternal = newMemoryLength;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(oldPointer + i));
    }
    delete[] oldPointer;
}

template <typename T> void SGLVector<T>::pushBack(const T& x){
    if(memoryLengthInternal == 0){reserve(1);}
    else if(lengthInternal == memoryLengthInternal){reserve(2 * memoryLengthInternal);}
    lengthInternal++;
    (*(dataInternal + lengthInternal - 1)) = x;
}

template <typename T> void SGLVector<T>::popBack(){
    lengthInternal--;
}

template <typename T> T* SGLVector<T>::pointerToData(int n){
    return (dataInternal + n);
}

#endif // SGLVECTOR_H
