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
#include <SGEXTN/CanOne/private_api/FunctionPointers.h>
#include <SGEXTN/CanOne/private_api/BaseAction.h>
#include <SGEXTN/CanOne/private_api/ActionStorage.h>

namespace SGEXTN::CanOne {
template <typename T> class ActionAccess;

template <typename ReturnType, typename... ArgTypes> class ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>> {
public:
    [[nodiscard]] static SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& getFunction(BaseAction<ReturnType>* baseAction);
    [[nodiscard]] static const SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& getFunction(const BaseAction<ReturnType>* baseAction);
    template <int I> [[nodiscard]] static typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& getArg(BaseAction<ReturnType>* baseAction);
    template <int I> [[nodiscard]] static const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& getArg(const BaseAction<ReturnType>* baseAction);
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>> {
public:
    [[nodiscard]] static SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& getFunction(BaseAction<ReturnType>* baseAction);
    [[nodiscard]] static const SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& getFunction(const BaseAction<ReturnType>* baseAction);
    [[nodiscard]] static ClassName*& getObjectInstance(BaseAction<ReturnType>* baseAction);
    [[nodiscard]] static ClassName*const& getObjectInstance(const BaseAction<ReturnType>* baseAction);
    template <int I> [[nodiscard]] static typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& getArg(BaseAction<ReturnType>* baseAction);
    template <int I> [[nodiscard]] static const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& getArg(const BaseAction<ReturnType>* baseAction);
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>> {
public:
    [[nodiscard]] static SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& getFunction(BaseAction<ReturnType>* baseAction);
    [[nodiscard]] static const SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& getFunction(const BaseAction<ReturnType>* baseAction);
    [[nodiscard]] static const ClassName*& getObjectInstance(BaseAction<ReturnType>* baseAction);
    [[nodiscard]] static const ClassName*const& getObjectInstance(const BaseAction<ReturnType>* baseAction);
    template <int I> [[nodiscard]] static typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& getArg(BaseAction<ReturnType>* baseAction);
    template <int I> [[nodiscard]] static const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& getArg(const BaseAction<ReturnType>* baseAction);
};
}

#include <SGEXTN/CanOne/private_api/ActionAccess_impl.h>
