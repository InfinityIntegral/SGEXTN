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
#include <SGEXTN/CanOne/Action.h>
#include <SGEXTN/CanOne/private_api/ActionStorage.h>
#include <SGEXTN/CanOne/private_api/ActionAccess.h>

template <typename ReturnType> SGEXTN::CanOne::Action<ReturnType>::Action(){
    actionPointer_ = nullptr;
}

template <typename ReturnType> SGEXTN::CanOne::Action<ReturnType>::Action(const SGEXTN::CanOne::Action<ReturnType>& x){
    if(x.actionPointer_ == nullptr){actionPointer_ = nullptr;}
    else{actionPointer_ = (*x.actionPointer_).copyBasePointer();}
}

template <typename ReturnType> SGEXTN::CanOne::Action<ReturnType>& SGEXTN::CanOne::Action<ReturnType>::operator=(const SGEXTN::CanOne::Action<ReturnType>& x){
    if(this == &x){return (*this);}
    delete actionPointer_;
    if(x.actionPointer_ == nullptr){actionPointer_ = nullptr;}
    else{actionPointer_ = (*x.actionPointer_).copyBasePointer();}
    return (*this);
}

template <typename ReturnType> SGEXTN::CanOne::Action<ReturnType>::Action(SGEXTN::CanOne::Action<ReturnType>&& x) noexcept {
    actionPointer_ = x.actionPointer_;
    x.actionPointer_ = nullptr;
}

template <typename ReturnType> SGEXTN::CanOne::Action<ReturnType>& SGEXTN::CanOne::Action<ReturnType>::operator=(SGEXTN::CanOne::Action<ReturnType>&& x) noexcept {
    if(this == &x){return (*this);}
    delete actionPointer_;
    actionPointer_ = x.actionPointer_;
    x.actionPointer_ = nullptr;
    return (*this);
}

template <typename ReturnType> SGEXTN::CanOne::Action<ReturnType>::~Action(){
    delete actionPointer_;
}

template <typename ReturnType> template <typename... ArgTypes> SGEXTN::CanOne::Action<ReturnType>::Action(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> function, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments){
    actionPointer_ = new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>(function, arguments...);
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> SGEXTN::CanOne::Action<ReturnType>::Action(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments){
    actionPointer_ = new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>(function, obj, arguments...);
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> SGEXTN::CanOne::Action<ReturnType>::Action(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> function, const ClassName* obj, const typename SGEXTN::CanOne::StorableType<ArgTypes>::StoreType&... arguments){
    actionPointer_ = new SGEXTN::CanOne::ActionStorage<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>(function, obj, arguments...);
}

template <typename ReturnType> ReturnType SGEXTN::CanOne::Action<ReturnType>::execute() const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::execute crashed because the action is empty");}
    return (*actionPointer_).execute();
}

template <typename ReturnType> template <typename... ArgTypes> SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& SGEXTN::CanOne::Action<ReturnType>::function([[maybe_unused]] SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::getFunction(actionPointer_);
}

template <typename ReturnType> template <typename... ArgTypes> const SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>& SGEXTN::CanOne::Action<ReturnType>::function([[maybe_unused]] SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::getFunction(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::Action<ReturnType>::function([[maybe_unused]] SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(actionPointer_);
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> const SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::Action<ReturnType>::function([[maybe_unused]] SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::Action<ReturnType>::function([[maybe_unused]] SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(actionPointer_);
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> const SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>& SGEXTN::CanOne::Action<ReturnType>::function([[maybe_unused]] SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::function crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getFunction(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> ClassName*& SGEXTN::CanOne::Action<ReturnType>::objectInstance([[maybe_unused]] SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(actionPointer_);
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> ClassName*const& SGEXTN::CanOne::Action<ReturnType>::objectInstance([[maybe_unused]] SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> const ClassName*& SGEXTN::CanOne::Action<ReturnType>::objectInstance([[maybe_unused]] SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(actionPointer_);
}

template <typename ReturnType> template <typename ClassName, typename... ArgTypes> const ClassName*const& SGEXTN::CanOne::Action<ReturnType>::objectInstance([[maybe_unused]] SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::objectInstance crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::getObjectInstance(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}


template <typename ReturnType> template <int I, typename... ArgTypes> typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::Action<ReturnType>::argument(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::template getArg<I>(actionPointer_);
}

template <typename ReturnType> template <int I, typename... ArgTypes> const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::Action<ReturnType>::argument(SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::StaticFunction<ReturnType, ArgTypes...>>::template getArg<I>(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}

template <typename ReturnType> template <int I, typename ClassName, typename... ArgTypes> typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::Action<ReturnType>::argument(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::template getArg<I>(actionPointer_);
}

template <typename ReturnType> template <int I, typename ClassName, typename... ArgTypes> const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::Action<ReturnType>::argument(SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::NonConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::template getArg<I>(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}

template <typename ReturnType> template <int I, typename ClassName, typename... ArgTypes> typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::Action<ReturnType>::argument(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr){
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::template getArg<I>(actionPointer_);
}

template <typename ReturnType> template <int I, typename ClassName, typename... ArgTypes> const typename SGEXTN::CanOne::StorableType<typename SGEXTN::CanOne::GetTypeInArgStore<I, ArgTypes...>::RetrievedType>::StoreType& SGEXTN::CanOne::Action<ReturnType>::argument(SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...> typeIndicatorNullptr) const {
    if(actionPointer_ == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::CanOne::Action::argument crashed because the action is empty");}
    return SGEXTN::CanOne::ActionAccess<SGEXTN::CanOne::ConstMemberFunction<ReturnType, ClassName, ArgTypes...>>::template getArg<I>(static_cast<const SGEXTN::CanOne::BaseAction<ReturnType>*>(actionPointer_));
}
