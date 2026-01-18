#pragma once
#include <private_api/SGEXTN_Containers_Crash.h>

template <typename T> SGEXTN::Containers::Array<T>::Array(int count){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array constructor crashed because count cannot be negative");}
    private_data = new T[count]();
    private_length = count;
}

template <typename T> SGEXTN::Containers::Array<T>::Array(int count, const T& defaultValue){
    if(count < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array constructor crashed because count cannot be negative");}
    private_data = new T[count];
    private_length = count;
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = defaultValue;
    }
}

template <typename T> template <typename... Ts> SGEXTN::Containers::Array<T>::Array(Ts... data){
    private_data = new T[sizeof...(Ts)]{data...};
    private_length = sizeof...(Ts);
}

template <typename T> SGEXTN::Containers::Array<T>::Array(const Array& x){
    private_data = new T[x.private_length];
    private_length = x.private_length;
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = (*(x.private_data + i));
    }
}

template <typename T> SGEXTN::Containers::Array<T>& SGEXTN::Containers::Array<T>::operator=(const Array& x){
    if(this == &x){return (*this);}
    delete[] private_data;
    private_data = new T[x.private_length];
    private_length = x.private_length;
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = (*(x.private_data + i));
    }
    return (*this);
}

template <typename T> SGEXTN::Containers::Array<T>::Array(Array&& x) noexcept {
    private_data = x.private_data;
    private_length = x.private_length;
    x.private_data = nullptr;
    x.private_length = 0;
}

template <typename T> SGEXTN::Containers::Array<T>& SGEXTN::Containers::Array<T>::operator=(Array&& x) noexcept {
    delete[] private_data;
    private_data = x.private_data;
    private_length = x.private_length;
    x.private_data = nullptr;
    x.private_length = 0;
    return (*this);
}

template <typename T> SGEXTN::Containers::Array<T>::~Array(){
    delete[] private_data;
}

template <typename T> void SGEXTN::Containers::Array<T>::fill(const T& defaultValue){
    for(int i=0; i<private_length; i++){
        (*(private_data + i)) = defaultValue;
    }
}

template <typename T> int SGEXTN::Containers::Array<T>::length() const {
    return private_length;
}

template <typename T> T& SGEXTN::Containers::Array<T>::at(int i){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array::at crashed because index is negative");}
    if(i >= private_length){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array::at crashed because index points beyond the end of the array");}
    return (*(private_data + i));
}

template <typename T> const T& SGEXTN::Containers::Array<T>::at(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array::at crashed because index is negative");}
    if(i >= private_length){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array::at crashed because index points beyond the end of the array");}
    return (*(private_data + i));
}

template <typename T> T* SGEXTN::Containers::Array<T>::pointerToData(int n){
    return (private_data + n);
}

template <typename T> const T* SGEXTN::Containers::Array<T>::pointerToData(int n) const {
    return (private_data + n);
}
