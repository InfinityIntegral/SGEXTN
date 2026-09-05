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
template <typename T> class ActionStorage;
template <typename T> class ActionAccess;

template <typename ReturnType, typename... ArgTypes> class ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>> final : public SGEXTN::CanOne::BaseAction<ReturnType> {
private:
    friend class SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>;
    SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> functionPointer_;
    SGEXTN::CanOne::ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...> args_;
public:
    explicit ActionStorage(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> function, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments);
    [[nodiscard]] ReturnType execute() const override;
    [[nodiscard]] SGEXTN::CanOne::BaseAction<ReturnType>* copyBasePointer() const override;
    [[nodiscard]] SGEXTN::CanOne::BaseAction<ReturnType>* moveBasePointer() && override;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>> final : public SGEXTN::CanOne::BaseAction<ReturnType> {
private:
    friend class SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>;
    SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> functionPointer_;
    ClassName* objectInstance_;
    SGEXTN::CanOne::ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...> args_;
public:
    ActionStorage(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments);
    [[nodiscard]] ReturnType execute() const override;
    [[nodiscard]] SGEXTN::CanOne::BaseAction<ReturnType>* copyBasePointer() const override;
    [[nodiscard]] SGEXTN::CanOne::BaseAction<ReturnType>* moveBasePointer() && override;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>> final : public SGEXTN::CanOne::BaseAction<ReturnType> {
private:
    friend class SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>;
    SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> functionPointer_;
    const ClassName* objectInstance_;
    SGEXTN::CanOne::ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...> args_;
public:
    ActionStorage(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, const ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments);
    [[nodiscard]] ReturnType execute() const override;
    [[nodiscard]] SGEXTN::CanOne::BaseAction<ReturnType>* copyBasePointer() const override;
    [[nodiscard]] SGEXTN::CanOne::BaseAction<ReturnType>* moveBasePointer() && override;
};

class CallFunction {
private:
    template <typename T> friend class SGEXTN::CanOne::ActionStorage;
    template <typename ReturnType, typename... ArgTypes, int... SequenceTerms> [[nodiscard]] static ReturnType callStaticFunction(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> function, const ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...>& arguments, SGEXTN::CanOne::ArgStoreIntegerSequence<SequenceTerms...> sequence);
    template <typename ReturnType, typename ClassName, typename... ArgTypes, int... SequenceTerms> [[nodiscard]] static ReturnType callNonConstMemberFunction(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, ClassName* objectInstance, const ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...>& arguments, SGEXTN::CanOne::ArgStoreIntegerSequence<SequenceTerms...> sequence);
    template <typename ReturnType, typename ClassName, typename... ArgTypes, int... SequenceTerms> [[nodiscard]] static ReturnType callConstMemberFunction(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, const ClassName* objectInstance, const ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...>& arguments, SGEXTN::CanOne::ArgStoreIntegerSequence<SequenceTerms...> sequence);
};

template <typename From, typename To> class EnrefDerefCast;

template <typename T> class EnrefDerefCast<T, T> {
private:
    friend class SGEXTN::CanOne::CallFunction;
    [[nodiscard]] static T cast(T x);
};

template <typename T> class EnrefDerefCast<T*, T&> {
private:
    friend class SGEXTN::CanOne::CallFunction;
    [[nodiscard]] static T& cast(T* x);
};

template <typename T> class EnrefDerefCast<T, const T&> {
private:
    friend class SGEXTN::CanOne::CallFunction;
    [[nodiscard]] static const T& cast(const T& x);
};
}

#include <SGEXTN/CanOne/private_api/ActionStorage_impl.h>
