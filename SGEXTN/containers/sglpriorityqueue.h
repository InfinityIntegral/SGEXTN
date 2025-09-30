#ifndef SGLPRIORITYQUEUE_H
#define SGLPRIORITYQUEUE_H

template <typename T, typename Comparator> class SGLPriorityQueue {
public:
    SGLPriorityQueue();
    SGLPriorityQueue(const SGLPriorityQueue& x);
    SGLPriorityQueue& operator=(const SGLPriorityQueue& x);
    SGLPriorityQueue(SGLPriorityQueue&& x) noexcept;
    SGLPriorityQueue& operator=(SGLPriorityQueue&& x) noexcept;
    ~SGLPriorityQueue();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] int length() const;
    void push(T x);
    void pop();
    void reserve(int newMemoryLength);
protected:
    T* dataInternal;
    int lengthInternal;
    int memoryLengthInternal;
    Comparator comparatorInstance;
    void swapInternal(int a, int b);
    bool compareInternal(int a, int b);
};

template <typename T, typename Comparator> SGLPriorityQueue<T, Comparator>::SGLPriorityQueue(){
    dataInternal = nullptr;
    lengthInternal = 0;
    memoryLengthInternal = 0;
    comparatorInstance = Comparator();
}

template <typename T, typename Comparator> SGLPriorityQueue<T, Comparator>::SGLPriorityQueue(const SGLPriorityQueue& x){
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
    comparatorInstance = Comparator();
}

template <typename T, typename Comparator> SGLPriorityQueue<T, Comparator>& SGLPriorityQueue<T, Comparator>::operator=(const SGLPriorityQueue& x){
    if(this == &x){return (*this);}
    delete[] dataInternal;
    dataInternal = new T[x.lengthInternal];
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(x.dataInternal + i));
    }
    return (*this);
}

template <typename T, typename Comparator> SGLPriorityQueue<T, Comparator>::SGLPriorityQueue(SGLPriorityQueue&& x) noexcept {
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryLengthInternal = 0;
    comparatorInstance = Comparator();
}

template <typename T, typename Comparator> SGLPriorityQueue<T, Comparator>& SGLPriorityQueue<T, Comparator>::operator=(SGLPriorityQueue&& x) noexcept {
    delete[] dataInternal;
    dataInternal = x.dataInternal;
    lengthInternal = x.lengthInternal;
    memoryLengthInternal = x.memoryLengthInternal;
    x.dataInternal = nullptr;
    x.lengthInternal = 0;
    x.memoryLengthInternal = 0;
    return (*this);
}

template <typename T, typename Comparator> SGLPriorityQueue<T, Comparator>::~SGLPriorityQueue(){
    delete[] dataInternal;
}

template <typename T, typename Comparator> const T& SGLPriorityQueue<T, Comparator>::top() const {
    return (*dataInternal);
}

template <typename T, typename Comparator> int SGLPriorityQueue<T, Comparator>::length() const {
    return lengthInternal;
}

template <typename T, typename Comparator> void SGLPriorityQueue<T, Comparator>::reserve(int newMemoryLength){
    if(newMemoryLength <= memoryLengthInternal){return;}
    T* oldPointer = dataInternal;
    dataInternal = new T[newMemoryLength];
    memoryLengthInternal = newMemoryLength;
    for(int i=0; i<lengthInternal; i++){
        (*(dataInternal + i)) = (*(oldPointer + i));
    }
    delete[] oldPointer;
}

template <typename T, typename Comparator> void SGLPriorityQueue<T, Comparator>::swapInternal(int a, int b){
    T temp = (*(dataInternal + a));
    (*(dataInternal + a)) = (*(dataInternal + b));
    (*(dataInternal + b)) = temp;
}

template <typename T, typename Comparator> bool SGLPriorityQueue<T, Comparator>::compareInternal(int a, int b){
    return comparatorInstance((*(dataInternal + a)), (*(dataInternal + b)));
}

template <typename T, typename Comparator> void SGLPriorityQueue<T, Comparator>::push(T x){
    if(memoryLengthInternal == 0){reserve(1);}
    else if(lengthInternal == memoryLengthInternal){reserve(2 * memoryLengthInternal);}
    lengthInternal++;
    (*(dataInternal + lengthInternal - 1)) = x;
    int i = lengthInternal - 1;
    while(i > 0){
        int parentIndex = (i - 1) / 2;
        if(compareInternal(parentIndex, i) == true){swapInternal(parentIndex, i);}
        else{break;}
        i = parentIndex;
    }
}

template <typename T, typename Comparator> void SGLPriorityQueue<T, Comparator>::pop(){
    (*dataInternal) = (*(dataInternal + lengthInternal - 1));
    lengthInternal--;
    int i = 0;
    while(true){
        int leftChild = 2*i + 1;
        int rightChild = 2*i + 2;
        if(rightChild < lengthInternal){
            if(compareInternal(i, leftChild) == false && compareInternal(i, rightChild) == false){break;}
            if(compareInternal(leftChild, rightChild) == true){
                swapInternal(i, rightChild);
                i = rightChild;
            }
            else{
                swapInternal(i, leftChild);
                i = leftChild;
            }
        }
        else if(leftChild < lengthInternal){
            if(compareInternal(i, leftChild) == true){swapInternal(i, leftChild);}
            break;
        }
        else{break;}
    }
}

#endif // SGLPRIORITYQUEUE_H
