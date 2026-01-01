#ifndef SGLSTACK_H
#define SGLSTACK_H

#include <private_api_Containers/SGLCrash.h>

template <typename T> class SGLStack {
public:
    SGLStack();
    SGLStack(const SGLStack& x);
    SGLStack& operator=(const SGLStack& x);
    SGLStack(SGLStack&& x) noexcept;
    SGLStack& operator=(SGLStack&& x) noexcept;
    ~SGLStack();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] int length() const;
    void push(const T& x);
    void pop();
    void reserve(int newMemoryLength);
protected:
    T* dataInternal;
    int lengthInternal;
    int memoryLengthInternal;
};

template <typename T> SGLStack<T>::SGLStack(){
    dataInternal = nullptr;
    lengthInternal = 0;
    memoryLengthInternal = 0;
}

template <typename T> SGLStack<T>::SGLStack(const SGLStack& x){
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.lengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
}

template <typename T> SGLStack<T>& SGLStack<T>::operator=(const SGLStack& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.lengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
    return (*this);
}

template <typename T> SGLStack<T>::SGLStack(SGLStack&& x) noexcept {
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryLengthInternal = 0;
}

template <typename T> SGLStack<T>& SGLStack<T>::operator=(SGLStack&& x) noexcept {
    delete[] dataInternal;
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryLengthInternal = 0;
    return (*this);
}

template <typename T> SGLStack<T>::~SGLStack(){
    delete[] dataInternal;
}

template <typename T> const T& SGLStack<T>::top() const {
    if(lengthInternal == 0){SGLCrash::crash("SGLStack::top crashed as the stack is empty");}
    return (*(dataInternal + lengthInternal - 1));
}

template <typename T> int SGLStack<T>::length() const {
    return lengthInternal;
}

template <typename T> void SGLStack<T>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    T* oldPointer = dataInternal;
    dataInternal = new T[newMemoryLength];
    memoryLengthInternal = newMemoryLength;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(oldPointer + i)); // NOLINT(clang-analyzer-security.ArrayBound)
    }
    delete[] oldPointer;
}

template <typename T> void SGLStack<T>::push(const T& x){
    if(memoryLengthInternal == 0){reserve(1);}
    else if(lengthInternal == memoryLengthInternal){reserve(2 * memoryLengthInternal);}
    lengthInternal++;
    (*(dataInternal + lengthInternal - 1)) = x; // NOLINT(clang-analyzer-security.ArrayBound)
}

template <typename T> void SGLStack<T>::pop(){
    if(lengthInternal == 0){SGLCrash::crash("SGLStack::pop crashed as the stack is empty");}
    lengthInternal--;
}

#endif // SGLSTACK_H
