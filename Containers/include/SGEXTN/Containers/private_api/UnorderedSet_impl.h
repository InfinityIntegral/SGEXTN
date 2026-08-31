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

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::UnorderedSetCustomisable() : hashMap_() {}

template <typename T, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::length() const {
    return hashMap_.length();
}

template <typename T, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    hashMap_.reserve(newMemoryLength);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::insert(const T& x){
    return hashMap_.insert(x, false);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::erase(const T& x){
    return hashMap_.erase(x);
}

template <typename T, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::clear(){
    hashMap_.clear();
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::contains(const T& x) const {
    return hashMap_.contains(x);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::begin(){
    return SGEXTN::Containers::UnorderedSetIterator(hashMap_.begin());
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::constBegin() const {
    return SGEXTN::Containers::UnorderedSetConstIterator(hashMap_.constBegin());
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::end(){
    return SGEXTN::Containers::UnorderedSetIterator(hashMap_.end());
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::constEnd() const {
    return SGEXTN::Containers::UnorderedSetConstIterator(hashMap_.constEnd());
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::erase(SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& i){
    return hashMap_.erase(i.hashMapIterator_);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::find(const T& x){
    return SGEXTN::Containers::UnorderedSetIterator(hashMap_.find(x));
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetCustomisable<T, EqualityCheck, HashFunction>::constFind(const T& x) const {
    return SGEXTN::Containers::UnorderedSetConstIterator(hashMap_.constFind(x));
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::UnorderedSetIterator(SGEXTN::Containers::HashMapIterator<T, bool, EqualityCheck, HashFunction> i) : hashMapIterator_(i) {}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::UnorderedSetConstIterator(SGEXTN::Containers::HashMapConstIterator<T, bool, EqualityCheck, HashFunction> i) : hashMapIterator_(i) {}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator++(){
    hashMapIterator_++;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedSetIterator prev = (*this);
    hashMapIterator_++;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator--(){
    hashMapIterator_--;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedSetIterator prev = (*this);
    hashMapIterator_--;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ == x.hashMapIterator_);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ != x.hashMapIterator_);
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator*() const {
    if(hashMapIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSetIterator::operator* crashed because the iterator is the end iterator");}
    return hashMapIterator_.key();
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator++(){
    hashMapIterator_++;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedSetConstIterator prev = (*this);
    hashMapIterator_++;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator--(){
    hashMapIterator_--;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedSetConstIterator prev = (*this);
    hashMapIterator_--;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ == x.hashMapIterator_);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ != x.hashMapIterator_);
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator*() const {
    if(hashMapIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSetConstIterator::operator* crashed because the iterator is the end iterator");}
    return hashMapIterator_.key();
}
