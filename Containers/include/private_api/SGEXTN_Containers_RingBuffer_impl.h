#pragma once

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(){
    private_data = nullptr;
    private_start = 0;
    private_length = 0;
    private_memoryLength = 0;
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(int count){
    private_data = new T[count];
    private_start = 0;
    private_length = count;
    private_memoryLength = count;
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(int count, const T& defaultValue){
    private_data = new T[count];
    private_start = 0;
    private_length = count;
    private_memoryLength = count;
    for(int i=0; i<count; i++){
        (*(private_data + i)) = defaultValue;
    }
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(const RingBuffer& x){
    private_data = new T[x.length()];
    private_start = 0;
    private_length = x.length();
    private_memoryLength = x.length();
    for(int i=0; i<x.length(); i++){
        (*(private_data + i)) = x.at(i);
    }
}

template <typename T> SGEXTN::Containers::RingBuffer<T>& SGEXTN::Containers::RingBuffer<T>::operator=(const RingBuffer& x){
    if(this == &x){return (*this);}
    delete[] private_data;
    private_data = new T[x.length()];
    private_start = 0;
    private_length = x.length();
    private_memoryLength = x.length();
    for(int i=0; i<x.length(); i++){
        (*(private_data + i)) = x.at(i);
    }
    return (*this);
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::RingBuffer(RingBuffer&& x) noexcept {
    private_data = x.private_data;
    private_start = x.private_start;
    private_length = x.private_length;
    private_memoryLength = x.private_memoryLength;
    x.private_data = nullptr;
    x.private_start = 0;
    x.private_length = 0;
    x.private_memoryLength = 0;
}

template <typename T> SGEXTN::Containers::RingBuffer<T>& SGEXTN::Containers::RingBuffer<T>::operator=(RingBuffer&& x) noexcept {
    delete[] private_data;
    private_data = x.private_data;
    private_start = x.private_start;
    private_length = x.private_length;
    private_memoryLength = x.private_memoryLength;
    x.private_data = nullptr;
    x.private_start = 0;
    x.private_length = 0;
    x.private_memoryLength = 0;
    return (*this);
}

template <typename T> SGEXTN::Containers::RingBuffer<T>::~RingBuffer(){
    delete[] private_data;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::fill(const T& defaultValue){
    for(int i=0; i<length(); i++){
        at(i) = defaultValue;
    }
}

template <typename T> int SGEXTN::Containers::RingBuffer<T>::private_getMemoryIndex(int i) const {
    int idx = i + private_start;
    if(idx < private_memoryLength){return idx;}
    return (idx - private_memoryLength);
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::at(int i){
    return (*(private_data + private_getMemoryIndex(i)));
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::at(int i) const {
    return (*(private_data + private_getMemoryIndex(i)));
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::front(){
    return at(0);
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::front() const {
    return at(0);
}

template <typename T> T& SGEXTN::Containers::RingBuffer<T>::back(){
    return at(length() - 1);
}

template <typename T> const T& SGEXTN::Containers::RingBuffer<T>::back() const {
    return at(length() - 1);
}

template <typename T> int SGEXTN::Containers::RingBuffer<T>::length() const {
    return private_length;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::pushBack(const T& x){
    if(private_length == private_memoryLength){reserve(2 * private_memoryLength + 1);}
    private_length++;
    back() = x;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::popBack(){
    private_length--;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::pushFront(const T& x){
    if(private_length == private_memoryLength){reserve(2 * private_memoryLength + 1);}
    private_length++;
    private_start--;
    if(private_start < 0){private_start += private_memoryLength;}
    front() = x;
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::popFront(){
    private_length--;
    private_start++;
    if(private_start >= private_memoryLength){private_start -= private_memoryLength;}
}

template <typename T> void SGEXTN::Containers::RingBuffer<T>::reserve(int newMemoryLength){
    if(newMemoryLength <= private_memoryLength){return;}
    T* newPointer = new T[newMemoryLength];
    for(int i=0; i<private_length; i++){
        (*(newPointer + i)) = at(i);
    }
    delete[] private_data;
    private_data = newPointer;
    private_start = 0;
    private_memoryLength = newMemoryLength;
}

template <typename T> T* SGEXTN::Containers::RingBuffer<T>::pointerToData(int n){
    return (private_data + private_getMemoryIndex(n));
}

template <typename T> const T* SGEXTN::Containers::RingBuffer<T>::pointerToData(int n) const {
    return (private_data + private_getMemoryIndex(n));
}
