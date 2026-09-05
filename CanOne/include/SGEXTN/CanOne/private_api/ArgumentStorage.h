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

namespace SGEXTN::CanOne {
template <int... Is> class ArgStoreIntegerSequence {};
template <int N, int... InFronts> class CreateArgStoreIntegerSequence : public CreateArgStoreIntegerSequence<N-1, N-1, InFronts...> {};
template <int First, int... Others> class CreateArgStoreIntegerSequence<0, First, Others...> {public: using SequenceType = SGEXTN::CanOne::ArgStoreIntegerSequence<First, Others...>;};
template <> class CreateArgStoreIntegerSequence<0> {public: using SequenceType = SGEXTN::CanOne::ArgStoreIntegerSequence<>;};

template <int I, typename... Ts> class GetTypeInArgStore {};
template <int I, typename Next, typename... Behinds> class GetTypeInArgStore<I, Next, Behinds...> {public: using RetrievedType = typename SGEXTN::CanOne::GetTypeInArgStore<I-1, Behinds...>::RetrievedType;};
template <typename Next, typename... Behinds> class GetTypeInArgStore<0, Next, Behinds...> {public: using RetrievedType = Next;};
template <int I> class GetTypeInArgStore<I> {public: using RetrievedType = void;};

template <typename IndexList, typename... Ts> class ArgStoreInternal;

template <typename... Ts> class ArgumentStorage;

template <int I, typename T> class ArgStoreNode {
private:
    template <typename... Ts> friend class SGEXTN::CanOne::ArgumentStorage;
    template <typename IndexList, typename... Ts> friend class SGEXTN::CanOne::ArgStoreInternal;
    T storedValue_;
    template <typename ArgType> explicit ArgStoreNode(ArgType&& argToMove);
};

template <int... Is, typename... Ts> class ArgStoreInternal<SGEXTN::CanOne::ArgStoreIntegerSequence<Is...>, Ts...> : private SGEXTN::CanOne::ArgStoreNode<Is, Ts>... {
private:
    friend class SGEXTN::CanOne::ArgumentStorage<Ts...>;
    ArgStoreInternal() = default;
    template <typename... ArgTypes> explicit ArgStoreInternal(ArgTypes&&... argsToMove);
};

template <typename... Ts> class ArgumentStorage : private SGEXTN::CanOne::ArgStoreInternal<typename SGEXTN::CanOne::CreateArgStoreIntegerSequence<sizeof...(Ts)>::SequenceType, Ts...> {
public:
    ArgumentStorage() = default;
    template <typename... ArgTypes> explicit ArgumentStorage(ArgTypes&&... data);
    template <int I> [[nodiscard]] typename SGEXTN::CanOne::GetTypeInArgStore<I, Ts...>::RetrievedType& at();
    template <int I> [[nodiscard]] const typename SGEXTN::CanOne::GetTypeInArgStore<I, Ts...>::RetrievedType& at() const;
    [[nodiscard]] int elementCount() const;
};
}

#include <SGEXTN/CanOne/private_api/ArgumentStorage_impl.h>
