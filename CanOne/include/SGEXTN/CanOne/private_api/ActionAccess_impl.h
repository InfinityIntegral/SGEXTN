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
#include <SGEXTN/CanOne/private_api/ActionStorage.h>

template <typename ReturnType, typename... ArgTypes> SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::getFunction(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).functionPointer_;
}

template <typename ReturnType, typename... ArgTypes> const SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::getFunction(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).functionPointer_;
}

template <typename ReturnType, typename... ArgTypes> template <int I> typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::getArg(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is accessed assuming a type different from its type when created");}
    if(I < 0 || I >= (*action).args_.elementCount()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because index accessed does not refer to any valid argument index");}
    return (*action).args_.template at<I>();
}

template <typename ReturnType, typename... ArgTypes> template <int I> const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::getArg(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is accessed assuming a type different from its type when created");}
    if(I < 0 || I >= (*action).args_.elementCount()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because index accessed does not refer to any valid argument index");}
    return (*action).args_.template at<I>();
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).functionPointer_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> const SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).functionPointer_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> ClassName*& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).objectInstance_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> ClassName*const& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).objectInstance_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> template <int I> typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getArg(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is accessed assuming a type different from its type when created");}
    if(I < 0 || I >= (*action).args_.elementCount()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because index accessed does not refer to any valid argument index");}
    return (*action).args_.template at<I>();
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> template <int I> const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getArg(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is accessed assuming a type different from its type when created");}
    if(I < 0 || I >= (*action).args_.elementCount()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because index accessed does not refer to any valid argument index");}
    return (*action).args_.template at<I>();
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).functionPointer_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> const SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).functionPointer_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> const ClassName*& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).objectInstance_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> const ClassName*const& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is accessed assuming a type different from its type when created");}
    return (*action).objectInstance_;
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> template <int I> typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getArg(BaseAction<ReturnType>* baseAction){
    SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is accessed assuming a type different from its type when created");}
    if(I < 0 || I >= (*action).args_.elementCount()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because index accessed does not refer to any valid argument index");}
    return (*action).args_.template at<I>();
}

template <typename ReturnType, typename ClassName, typename... ArgTypes> template <int I> const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getArg(const BaseAction<ReturnType>* baseAction){
    const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>* action = dynamic_cast<const SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>*>(baseAction);
    if(action == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is accessed assuming a type different from its type when created");}
    if(I < 0 || I >= (*action).args_.elementCount()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because index accessed does not refer to any valid argument index");}
    return (*action).args_.template at<I>();
}
