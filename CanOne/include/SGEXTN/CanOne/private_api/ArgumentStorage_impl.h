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

template <int I, typename T> template <typename ArgType> SGEXTN::CanOne::ArgStoreNode<I, T>::ArgStoreNode(ArgType&& argToMove) : storedValue_(static_cast<ArgType&&>(argToMove)){}

template <int... Is, typename... Ts> template <typename... ArgTypes> SGEXTN::CanOne::ArgStoreInternal<SGEXTN::CanOne::ArgStoreIntegerSequence<Is...>, Ts...>::ArgStoreInternal(ArgTypes&&... argsToMove) : SGEXTN::CanOne::ArgStoreNode<Is, Ts>(static_cast<ArgTypes&&>(argsToMove))... {}

template <typename... Ts> template <typename... ArgTypes> SGEXTN::CanOne::ArgumentStorage<Ts...>::ArgumentStorage(ArgTypes&&... data) : SGEXTN::CanOne::ArgStoreInternal<typename SGEXTN::CanOne::CreateArgStoreIntegerSequence<sizeof...(Ts)>::SequenceType, Ts...>(static_cast<ArgTypes&&>(data)...){}

template <typename... Ts> template <int I> typename SGEXTN::CanOne::GetTypeInArgStore<I, Ts...>::RetrievedType& SGEXTN::CanOne::ArgumentStorage<Ts...>::at(){
    return static_cast<SGEXTN::CanOne::ArgStoreNode<I, typename SGEXTN::CanOne::GetTypeInArgStore<I, Ts...>::RetrievedType>&>(static_cast<SGEXTN::CanOne::ArgStoreInternal<typename SGEXTN::CanOne::CreateArgStoreIntegerSequence<sizeof...(Ts)>::SequenceType, Ts...>&>(*this)).storedValue_;
}

template <typename... Ts> template <int I> const typename SGEXTN::CanOne::GetTypeInArgStore<I, Ts...>::RetrievedType& SGEXTN::CanOne::ArgumentStorage<Ts...>::at() const {
    return static_cast<const SGEXTN::CanOne::ArgStoreNode<I, typename SGEXTN::CanOne::GetTypeInArgStore<I, Ts...>::RetrievedType>&>(static_cast<const SGEXTN::CanOne::ArgStoreInternal<typename SGEXTN::CanOne::CreateArgStoreIntegerSequence<sizeof...(Ts)>::SequenceType, Ts...>&>(*this)).storedValue_;
}

template <typename... Ts> int SGEXTN::CanOne::ArgumentStorage<Ts...>::elementCount() const {
    return sizeof...(Ts);
}
