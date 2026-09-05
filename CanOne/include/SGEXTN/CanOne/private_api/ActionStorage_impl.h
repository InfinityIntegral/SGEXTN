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
#include <SGEXTN/Containers/ForceCrash.h>

template <typename ReturnType, typename... ArgTypes> SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::ActionStorage(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> function, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments) : functionPointer_(function), args_(arguments...){}

template <typename ReturnType, typename... ArgTypes> ReturnType SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::execute() const {
    if(functionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::execute crashed because the function pointer is nullptr");}
    return SGEXTN::CanOne::CallFunction::callStaticFunction(functionPointer_, args_, typename SGEXTN::CanOne::CreateArgStoreIntegerSequence<sizeof...(ArgTypes)>::SequenceType());
}

template <typename ReturnType, typename... ArgTypes> SGEXTN::CanOne::BaseAction<ReturnType>* SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::copyBasePointer() const {
    return static_cast<SGEXTN::CanOne::BaseAction<ReturnType>*>(new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>(*this));
}

template <typename ReturnType, typename... ArgTypes> SGEXTN::CanOne::BaseAction<ReturnType>* SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::moveBasePointer() && {
    return static_cast<SGEXTN::CanOne::BaseAction<ReturnType>*>(new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>(static_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>&&>(*this)));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::ActionStorage(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments) : functionPointer_(function), objectInstance_(obj), args_(arguments...){}

template <typename ReturnType, typename ClassName, typename... ArgTypes> ReturnType SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::execute() const {
    if(functionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::execute crashed because the function pointer is nullptr");}
    if(objectInstance_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::execute crashed because the object instance to call the member function on does not exist");}
    return SGEXTN::CanOne::CallFunction::callNonConstMemberFunction(functionPointer_, objectInstance_, args_, typename SGEXTN::CanOne::CreateArgStoreIntegerSequence<sizeof...(ArgTypes)>::SequenceType());
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::BaseAction<ReturnType>* SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::copyBasePointer() const {
    return static_cast<SGEXTN::CanOne::BaseAction<ReturnType>*>(new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>(*this));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::BaseAction<ReturnType>* SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::moveBasePointer() && {
    return static_cast<SGEXTN::CanOne::BaseAction<ReturnType>*>(new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>(static_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>&&>(*this)));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::ActionStorage(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, const ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments) : functionPointer_(function), objectInstance_(obj), args_(arguments...){}

template <typename ReturnType, typename ClassName, typename... ArgTypes> ReturnType SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::execute() const {
    if(functionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::execute crashed because the function pointer is nullptr");}
    if(objectInstance_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::execute crashed because the object instance to call the member function on does not exist");}
    return SGEXTN::CanOne::CallFunction::callConstMemberFunction(functionPointer_, objectInstance_, args_, typename SGEXTN::CanOne::CreateArgStoreIntegerSequence<sizeof...(ArgTypes)>::SequenceType());
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::BaseAction<ReturnType>* SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::copyBasePointer() const {
    return static_cast<SGEXTN::CanOne::BaseAction<ReturnType>*>(new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>(*this));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::BaseAction<ReturnType>* SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::moveBasePointer() && {
    return static_cast<SGEXTN::CanOne::BaseAction<ReturnType>*>(new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>(static_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>&&>(*this)));
}

template <typename ReturnType, typename... ArgTypes, int... SequenceTerms> ReturnType SGEXTN::CanOne::CallFunction::callStaticFunction(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> function, const ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...>& arguments, [[maybe_unused]] SGEXTN::CanOne::ArgStoreIntegerSequence<SequenceTerms...> sequence){
    return ((*function)(SGEXTN::CanOne::EnrefDerefCast<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType, ArgTypes>::cast(arguments.template at<SequenceTerms>())...));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes, int... SequenceTerms> ReturnType SGEXTN::CanOne::CallFunction::callNonConstMemberFunction(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, ClassName* objectInstance, const ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...>& arguments, [[maybe_unused]] SGEXTN::CanOne::ArgStoreIntegerSequence<SequenceTerms...> sequence){
    return (((*objectInstance).*function)(SGEXTN::CanOne::EnrefDerefCast<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType, ArgTypes>::cast(arguments.template at<SequenceTerms>())...));
}

template <typename ReturnType, typename ClassName, typename... ArgTypes, int... SequenceTerms> ReturnType SGEXTN::CanOne::CallFunction::callConstMemberFunction(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, const ClassName* objectInstance, const ArgumentStorage<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType...>& arguments, [[maybe_unused]] SGEXTN::CanOne::ArgStoreIntegerSequence<SequenceTerms...> sequence){
    return (((*objectInstance).*function)(SGEXTN::CanOne::EnrefDerefCast<typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType, ArgTypes>::cast(arguments.template at<SequenceTerms>())...));
}

template <typename T> T SGEXTN::CanOne::EnrefDerefCast<T, T>::cast(T x){
    return x;
}

template <typename T> T& SGEXTN::CanOne::EnrefDerefCast<T*, T&>::cast(T* x){
    return (*x);
}

template <typename T> const T& SGEXTN::CanOne::EnrefDerefCast<T, const T&>::cast(const T& x){
    return (*(&x));
}
