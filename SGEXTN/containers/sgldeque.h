#ifndef SGLDEQUE_H
#define SGLDEQUE_H

#include "sglcrash.h"

template <typename T> class SGLDeque {
public:
    SGLDeque();
    SGLDeque(int count);
    SGLDeque(int count, const T& defaultValue);
    SGLDeque(const SGLDeque& x);
    SGLDeque& operator=(const SGLDeque& x);
    SGLDeque(SGLDeque&& x) noexcept;
    SGLDeque& operator=(SGLDeque&& x) noexcept;
    ~SGLDeque();
    void assign(int count, const T& defaultValue);
    void fill(const T& defaultValue);
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] const T& front() const;
    [[nodiscard]] const T& back() const;
    [[nodiscard]] int length() const;
    void pushBack(const T& x);
    void popBack();
    void pushFront(const T& x);
    void popFront();
    void reserve(int newMemoryLength);
    [[nodiscard]] T* pointerToData(int n);
protected:
    T* dataInternal;
    int startInternal;
    int endInternal;
    int memoryLengthInternal;
};

template <typename T> SGLDeque<T>::SGLDeque(){
    dataInternal = nullptr;
    startInternal = 0;
    endInternal = 0;
    memoryLengthInternal = 0;
}

template <typename T> SGLDeque<T>::SGLDeque(int count){
    dataInternal = new T[count];
    startInternal = 0;
    endInternal = count;
    memoryLengthInternal = count;
}

template <typename T> SGLDeque<T>::SGLDeque(int count, const T& defaultValue){
    dataInternal = new T[count];
    startInternal = 0;
    endInternal = count;
    memoryLengthInternal = count;
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> SGLDeque<T>::SGLDeque(const SGLDeque& x){
    dataInternal = new T[x.endInternal - x.startInternal];
    startInternal = 0;
    endInternal = x.endInternal - x.startInternal;
    memoryLengthInternal = endInternal;
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + x.startInternal + i));
    }
}

template <typename T> SGLDeque<T>& SGLDeque<T>::operator=(const SGLDeque& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new T[x.endInternal - x.startInternal];
    startInternal = 0;
    endInternal = x.endInternal - x.startInternal;
    memoryLengthInternal = endInternal;
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + x.startInternal + i));
    }
    return (*this);
}

template <typename T> SGLDeque<T>::SGLDeque(SGLDeque&& x) noexcept {
    (*this).dataInternal = x.dataInternal;
    (*this).startInternal = x.startInternal;
    (*this).endInternal = x.endInternal;
    (*this).memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.startInternal = 0;
    x.endInternal = 0;
    x.memoryLengthInternal = 0;
}

template <typename T> SGLDeque<T>& SGLDeque<T>::operator=(SGLDeque&& x) noexcept {
    delete[] dataInternal;
    (*this).dataInternal = x.dataInternal;
    (*this).startInternal = x.startInternal;
    (*this).endInternal = x.endInternal;
    (*this).memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.startInternal = 0;
    x.endInternal = 0;
    x.memoryLengthInternal = 0;
    return (*this);
}

template <typename T> SGLDeque<T>::~SGLDeque(){
    delete[] dataInternal;
}

template <typename T> void SGLDeque<T>::assign(int count, const T& defaultValue){
    delete[] dataInternal;
    dataInternal = new T[count];
    startInternal = 0;
    endInternal = count;
    memoryLengthInternal = count;
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> void SGLDeque<T>::fill(const T& defaultValue){
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = defaultValue;
    }
}

template <typename T> T& SGLDeque<T>::at(int i){
    if(i < 0 || i >= endInternal - startInternal){SGLCrash::crash();}
    return (*(dataInternal + startInternal + i));
}

template <typename T> const T& SGLDeque<T>::at(int i) const {
    if(i < 0 || i >= endInternal - startInternal){SGLCrash::crash();}
    return (*(dataInternal + startInternal + i));
}

template <typename T> const T& SGLDeque<T>::front() const {
    return (*(dataInternal + startInternal));
}

template <typename T> const T& SGLDeque<T>::back() const {
    return (*(dataInternal + endInternal - 1));
}

template <typename T> int SGLDeque<T>::length() const {
    return (endInternal - startInternal);
}

template <typename T> void SGLDeque<T>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    T* oldPointer = dataInternal;
    int oldStart = startInternal;
    int oldEnd = endInternal;
    dataInternal = new T[newMemoryLength];
    startInternal = newMemoryLength / 3;
    endInternal = startInternal + (oldEnd - oldStart);
    memoryLengthInternal = newMemoryLength;
    for(int i=0; i<endInternal-startInternal; i++){
        (*(dataInternal + startInternal + i)) = (*(oldPointer + oldStart + i));
    }
    delete[] oldPointer;
}

template <typename T> T* SGLDeque<T>::pointerToData(int n){
    return (dataInternal + startInternal + n);
}

template <typename T> void SGLDeque<T>::pushBack(const T& x){
    if(memoryLengthInternal == 0){reserve(1);}
    else if(endInternal == memoryLengthInternal){reserve(3 * memoryLengthInternal);}
    endInternal++;
    (*(dataInternal + endInternal - 1)) = x;
}

template <typename T> void SGLDeque<T>::popBack(){
    endInternal--;
}

template <typename T> void SGLDeque<T>::pushFront(const T& x){
    if(memoryLengthInternal == 0){reserve(1);}
    else if(startInternal == 0){reserve(3 * memoryLengthInternal);}
    startInternal--;
    (*(dataInternal + startInternal)) = x;
}

template <typename T> void SGLDeque<T>::popFront(){
    startInternal++;
}

#endif // SGLDEQUE_H
