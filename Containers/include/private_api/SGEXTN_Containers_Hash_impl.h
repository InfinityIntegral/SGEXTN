/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

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
