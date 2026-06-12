#pragma once
#include <SGEXTN_Containers_Span.h>
#include <private_api/SGEXTN_Containers_HashAlgorithm.h>

template <typename T> int SGEXTN::Containers::Hash<T>::operator()(const T& x) const {
    return x.hash();
}

template <typename... Ts> int SGEXTN::Containers::Hash<Ts...>::operator()(Ts... xs) const {
    constexpr int argCount = (sizeof...(Ts));
    int buffer[argCount] = {SGEXTN::Containers::Hash<Ts>{}(xs)...};
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(buffer), argCount * sizeof(int)));
}

template <typename T> int SGEXTN::Containers::Hash<T*>::operator()(const T* x) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(T*)));
}

template <typename ReturnType, typename... ArgTypes> int SGEXTN::Containers::Hash<ReturnType (*)(ArgTypes...)>::operator()(ReturnType (*x)(ArgTypes...)) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(ReturnType (*)(ArgTypes...))));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> int SGEXTN::Containers::Hash<ReturnType (ClassName::*)(ArgTypes...)>::operator()(ReturnType (ClassName::*x)(ArgTypes...)) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(ReturnType (ClassName::*)(ArgTypes...))));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> int SGEXTN::Containers::Hash<ReturnType (ClassName::*)(ArgTypes...) const>::operator()(ReturnType (ClassName::*x)(ArgTypes...) const) const {
    return SGEXTN::Containers::HashAlgorithm::wyHash32(SGEXTN::Containers::Span<const unsigned char>(reinterpret_cast<const unsigned char*>(&x), sizeof(ReturnType (ClassName::*)(ArgTypes...) const)));
}