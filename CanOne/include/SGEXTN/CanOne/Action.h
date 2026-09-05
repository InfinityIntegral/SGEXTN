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
#include <SGEXTN/CanOne/private_api/BaseAction.h>
#include <SGEXTN/CanOne/private_api/ArgumentStorage.h>
#include <SGEXTN/CanOne/private_api/StorableType.h>
#include <SGEXTN/CanOne/private_api/FunctionPointers.h>

namespace SGEXTN::CanOne {
template <typename ReturnType> class Action {
private:
    SGEXTN::CanOne::BaseAction<ReturnType>* actionPointer_;
public:
    Action();
    Action(const Action& x);
    Action& operator=(const Action& x);
    Action(Action&& x) noexcept;
    Action& operator=(Action&& x) noexcept;
    ~Action();
    template <typename... ArgTypes> Action(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> function, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments);
    template <typename ClassName, typename... ArgTypes> Action(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments);
    template <typename ClassName, typename... ArgTypes> Action(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, const ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments);
    [[nodiscard]] ReturnType execute() const;
    template <typename... ArgTypes> [[nodiscard]] SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& function(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr);
    template <typename... ArgTypes> [[nodiscard]] const SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& function(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr) const;
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& function(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr);
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] const SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& function(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const;
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& function(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr);
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] const SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& function(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const;
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] ClassName*& objectInstance(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr);
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] ClassName*const& objectInstance(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const;
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] const ClassName*& objectInstance(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr);
    template <typename ClassName, typename... ArgTypes> [[nodiscard]] const ClassName*const& objectInstance(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const;
    template <int I, typename... ArgTypes> [[nodiscard]] typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& argument(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr);
    template <int I, typename... ArgTypes> [[nodiscard]] const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& argument(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr) const;
    template <int I, typename ClassName, typename... ArgTypes> [[nodiscard]] typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& argument(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr);
    template <int I, typename ClassName, typename... ArgTypes> [[nodiscard]] const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& argument(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const;
    template <int I, typename ClassName, typename... ArgTypes> [[nodiscard]] typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& argument(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr);
    template <int I, typename ClassName, typename... ArgTypes> [[nodiscard]] const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& argument(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const;
};
}

#include <SGEXTN/CanOne/private_api/Action_impl.h>
