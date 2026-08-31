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

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::UnorderedMapCustomisable() : hashMap_() {}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::length() const {
    return hashMap_.length();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    hashMap_.reserve(newMemoryLength);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::insert(const Key& key, const Value& value){
    return hashMap_.insert(key, value);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::erase(const Key& x){
    return hashMap_.erase(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::clear(){
    hashMap_.clear();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::contains(const Key& x) const {
    return hashMap_.contains(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::at(const Key& x){
    if(contains(x) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap::at crashed because the provided key is not in the map");}
    return hashMap_.at(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::at(const Key& x) const {
    if(contains(x) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap::at crashed because the provided key is not in the map");}
    return hashMap_.at(x);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::begin(){
    return SGEXTN::Containers::UnorderedMapIterator(hashMap_.begin());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::constBegin() const {
    return SGEXTN::Containers::UnorderedMapConstIterator(hashMap_.constBegin());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::end(){
    return SGEXTN::Containers::UnorderedMapIterator(hashMap_.end());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::constEnd() const {
    return SGEXTN::Containers::UnorderedMapConstIterator(hashMap_.constEnd());
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::erase(SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& i){
    return hashMap_.erase(i.hashMapIterator_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::find(const Key& x){
    return SGEXTN::Containers::UnorderedMapIterator(hashMap_.find(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapCustomisable<Key, Value, EqualityCheck, HashFunction>::constFind(const Key& x) const {
    return SGEXTN::Containers::UnorderedMapConstIterator(hashMap_.constFind(x));
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::UnorderedMapIterator(SGEXTN::Containers::HashMapIterator<Key, Value, EqualityCheck, HashFunction> i) : hashMapIterator_(i) {}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    hashMapIterator_++;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedMapIterator prev = (*this);
    hashMapIterator_++;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    hashMapIterator_--;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedMapIterator prev = (*this);
    hashMapIterator_--;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ == x.hashMapIterator_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ != x.hashMapIterator_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::key() const {
    if(hashMapIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMapIterator::key crashed because the iterator is the end iterator");}
    return hashMapIterator_.key();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> Value& SGEXTN::Containers::UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>::value() const {
    if(hashMapIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMapIterator::value crashed because the iterator is the end iterator");}
    return hashMapIterator_.value();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::UnorderedMapConstIterator(SGEXTN::Containers::HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> i) : hashMapIterator_(i) {}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(){
    hashMapIterator_++;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedMapConstIterator prev = (*this);
    hashMapIterator_++;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(){
    hashMapIterator_--;
    return (*this);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedMapConstIterator prev = (*this);
    hashMapIterator_--;
    return prev;
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ == x.hashMapIterator_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>& x) const {
    return (hashMapIterator_ != x.hashMapIterator_);
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Key& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::key() const {
    if(hashMapIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMapConstIterator::key crashed because the iterator is the end iterator");}
    return hashMapIterator_.key();
}

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> const Value& SGEXTN::Containers::UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction>::value() const {
    if(hashMapIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMapConstIterator::value crashed because the iterator is the end iterator");}
    return hashMapIterator_.value();
}
