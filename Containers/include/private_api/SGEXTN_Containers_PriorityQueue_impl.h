#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueue<T, Comparator>::PriorityQueue(){
    private_data = nullptr;
    private_length = 0;
    private_memoryLength = 0;
    private_comparatorInstance = Comparator();
}

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueue<T, Comparator>::PriorityQueue(const PriorityQueue& x){
    private_data = new T[x.private_length];
    private_length = x.private_length;
    private_memoryLength = x.private_length;
    private_comparatorInstance = x.private_comparatorInstance;
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = (*(x.private_data + i));
    }
}

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueue<T, Comparator>& SGEXTN::Containers::PriorityQueue<T, Comparator>::operator=(const PriorityQueue& x){
    if(this == &x){return (*this);}
    delete[] private_data;
    private_data = new T[x.private_length];
    private_length = x.private_length;
    private_memoryLength = x.private_length;
    private_comparatorInstance = x.private_comparatorInstance;
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = (*(x.private_data + i));
    }
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueue<T, Comparator>::PriorityQueue(PriorityQueue&& x) noexcept {
    private_data = x.private_data;
    private_length = x.private_length;
    private_memoryLength = x.private_memoryLength;
    private_comparatorInstance = x.private_comparatorInstance;
    x.private_data = nullptr;
    x.private_length = 0;
    x.private_memoryLength = 0;
}

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueue<T, Comparator>& SGEXTN::Containers::PriorityQueue<T, Comparator>::operator=(PriorityQueue&& x) noexcept {
    delete[] private_data;
    private_data = x.private_data;
    private_length = x.private_length;
    private_memoryLength = x.private_memoryLength;
    private_comparatorInstance = x.private_comparatorInstance;
    x.private_data = nullptr;
    x.private_length = 0;
    x.private_memoryLength = 0;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueue<T, Comparator>::~PriorityQueue(){
    delete[] private_data;
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::PriorityQueue<T, Comparator>::top() const {
    if(private_length == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue::top crashed as the priority queue is empty");}
    return (*private_data);
}

template <typename T, typename Comparator> int SGEXTN::Containers::PriorityQueue<T, Comparator>::length() const {
    return private_length;
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::reserve(int newMemoryLength){
    if(newMemoryLength <= private_memoryLength){return;}
    T* oldPointer = private_data;
    private_data = new T[newMemoryLength];
    private_memoryLength = newMemoryLength;
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = (*(oldPointer + i));
    }
    delete[] oldPointer;
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::private_swap(int a, int b){
    T temp = (*(private_data + a));
    (*(private_data + a)) = (*(private_data + b));
    (*(private_data + b)) = temp;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::PriorityQueue<T, Comparator>::private_compare(int a, int b){
    return private_comparatorInstance((*(private_data + a)), (*(private_data + b)));
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::push(const T& x){
    if(private_length == private_memoryLength){reserve(2 * private_memoryLength + 1);}
    private_length++;
    (*(private_data + private_length - 1)) = x;
    int i = private_length - 1;
    while(i > 0){
        int parentIndex = (i - 1) / 2;
        if(private_compare(parentIndex, i) == true){private_swap(parentIndex, i);}
        else{break;}
        i = parentIndex;
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::pop(){
    if(private_length == 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue::pop crashed as the priority queue is empty");}
    (*private_data) = (*(private_data + private_length - 1));
    private_length--;
    int i = 0;
    while(true){
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;
        if(rightChild < private_length){
            if(private_compare(i, leftChild) == false && private_compare(i, rightChild) == false){break;}
            if(private_compare(leftChild, rightChild) == true){
                private_swap(i, rightChild);
                i = rightChild;
            }
            else{
                private_swap(i, leftChild);
                i = leftChild;
            }
        }
        else if(leftChild < private_length){
            if(private_compare(i, leftChild) == true){private_swap(i, leftChild);}
            break;
        }
        else{break;}
    }
}
