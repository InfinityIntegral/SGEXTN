#ifndef SGLQUEUE_H
#define SGLQUEUE_H

#include <private_api_Containers/SGLCrash.h>

template <typename T> class SGLQueue {
public:
    SGLQueue();
    SGLQueue(const SGLQueue& x);
    SGLQueue& operator=(const SGLQueue& x);
    SGLQueue(SGLQueue&& x) noexcept;
    SGLQueue& operator=(SGLQueue&& x) noexcept;
    ~SGLQueue();
    [[nodiscard]] const T& front() const;
    [[nodiscard]] const T& back() const;
    [[nodiscard]] int length() const;
    void push(const T& x);
    void pop();
    void reserve(int newMemoryLength);
protected:
    T* dataInternal;
    int startInternal;
    int endInternal;
    int memoryLengthInternal;
    int getMemoryIndex(int logicalIndex);
};

template <typename T> int SGLQueue<T>::getMemoryIndex(int logicalIndex){
    int memoryIndex = logicalIndex % memoryLengthInternal;
    if(memoryIndex < 0){memoryIndex += memoryLengthInternal;}
    return memoryIndex;
}

template <typename T> SGLQueue<T>::SGLQueue(){
    dataInternal = nullptr;
    startInternal = 0;
    endInternal = 0;
    memoryLengthInternal = 0;
}

template <typename T> SGLQueue<T>::SGLQueue(const SGLQueue& x){
    dataInternal = new T[x.endInternal - x.startInternal];
    startInternal = 0;
    endInternal = x.endInternal - x.startInternal;
    memoryLengthInternal = x.endInternal - x.startInternal;
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + x.startInternal + i));
    }
}

template <typename T> SGLQueue<T>& SGLQueue<T>::operator=(const SGLQueue& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new T[x.endInternal - x.startInternal];
    startInternal = 0;
    endInternal = x.endInternal - x.startInternal;
    memoryLengthInternal = x.endInternal - x.startInternal;
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + x.startInternal + i));
    }
    return (*this);
}

template <typename T> SGLQueue<T>::SGLQueue(SGLQueue&& x) noexcept {
    dataInternal = x.dataInternal;
    startInternal = x.startInternal;
    endInternal = x.endInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.startInternal = 0;
    x.endInternal = 0;
    x.memoryLengthInternal = 0;
}

template <typename T> SGLQueue<T>& SGLQueue<T>::operator=(SGLQueue&& x) noexcept {
    delete[] dataInternal;
    dataInternal = x.dataInternal;
    startInternal = x.startInternal;
    endInternal = x.endInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.startInternal = 0;
    x.endInternal = 0;
    x.memoryLengthInternal = 0;
    return (*this);
}

template <typename T> SGLQueue<T>::~SGLQueue(){
    delete[] dataInternal;
}

template <typename T> const T& SGLQueue<T>::front() const {
    if(endInternal - startInternal == 0){SGLCrash::crash("SGLQueue::front crashed because the queue is empty");}
    return (*(dataInternal + startInternal));
}

template <typename T> const T& SGLQueue<T>::back() const {
    if(endInternal - startInternal == 0){SGLCrash::crash("SGLQueue::back crashed because the queue is empty");}
    return (*(dataInternal + endInternal - 1));
}

template <typename T> int SGLQueue<T>::length() const {
    return (endInternal - startInternal);
}

template <typename T> void SGLQueue<T>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    T* oldPointer = dataInternal;
    int oldStart = startInternal;
    int oldEnd = endInternal;
    dataInternal = new T[newMemoryLength];
    startInternal = 0;
    endInternal = oldEnd - oldStart;
    memoryLengthInternal = newMemoryLength;
    for(int i=startInternal; i<endInternal; i++){
        (*(dataInternal + i)) = (*(oldPointer + oldStart + i)); // NOLINT(clang-analyzer-security.ArrayBound)
    }
    delete[] oldPointer;
}

template <typename T> void SGLQueue<T>::push(const T& x){
    if(memoryLengthInternal == 0){reserve(1);}
    if(endInternal == memoryLengthInternal){reserve(2 * memoryLengthInternal);}
    endInternal++;
    (*(dataInternal + endInternal - 1)) = x;
}

template <typename T> void SGLQueue<T>::pop(){
    if(endInternal - startInternal == 0){SGLCrash::crash("SGLQueue::pop crashed because the queue is empty");}
    startInternal++;
}

#endif // SGLQUEUE_H
