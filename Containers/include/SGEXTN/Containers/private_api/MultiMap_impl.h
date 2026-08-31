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

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::MultiMapCustomisable() : avlTree_() {}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::length() const {
    return avlTree_.length();
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::insert(const Key& key, const Value& value){
    avlTree_.insert(key, value, true);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::erase(const Key& x){
    return avlTree_.erase(x);
}

template <typename Key, typename Value, typename Comparator> void SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::clear(){
    avlTree_.clear();
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::contains(const Key& x) const {
    return avlTree_.contains(x);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::count(const Key& x) const {
    return avlTree_.count(x);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::at(const Key& x){
    if(contains(x) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::at crashed because the key is not in the map");}
    return avlTree_.at(x);
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::at(const Key& x) const {
    if(contains(x) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::at crashed because the key is not in the map");}
    return avlTree_.at(x);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::begin(){
    return SGEXTN::Containers::MultiMapIterator(avlTree_.begin());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::constBegin() const {
    return SGEXTN::Containers::MultiMapConstIterator(avlTree_.constBegin());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::end(){
    return SGEXTN::Containers::MultiMapIterator(avlTree_.end());
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::constEnd() const {
    return SGEXTN::Containers::MultiMapConstIterator(avlTree_.constEnd());
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::erase(SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& i){
    return avlTree_.erase(i.avlTreeIterator_);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::find(const Key& x){
    return SGEXTN::Containers::MultiMapIterator(avlTree_.find(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::constFind(const Key& x) const {
    return SGEXTN::Containers::MultiMapConstIterator(avlTree_.constFind(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::lowerBound(const Key& x){
    return SGEXTN::Containers::MultiMapIterator(avlTree_.lowerBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::constLowerBound(const Key& x) const {
    return SGEXTN::Containers::MultiMapConstIterator(avlTree_.constLowerBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::upperBound(const Key& x){
    return SGEXTN::Containers::MultiMapIterator(avlTree_.upperBound(x));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::constUpperBound(const Key& x) const {
    return SGEXTN::Containers::MultiMapConstIterator(avlTree_.constUpperBound(x));
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::indexOf(const Key& x) const {
    return avlTree_.indexOf(x);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::indexOf(SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> i) const {
    return avlTree_.indexOf(i.avlTreeIterator_);
}

template <typename Key, typename Value, typename Comparator> int SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::indexOf(SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> i) const {
    return avlTree_.indexOf(i.avlTreeIterator_);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::keyAt(int n) const {
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::keyAt crashed because index is negative");}
    if(n >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::keyAt crashed because index points beyond the end of the data structure");}
    return avlTree_.keyAt(n);
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::valueAt(int n){
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::valueAt crashed because index is negative");}
    if(n >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::valueAt crashed because index points beyond the end of the data structure");}
    return avlTree_.valueAt(n);
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::valueAt(int n) const {
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::valueAt crashed because index is negative");}
    if(n >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap::valueAt crashed because index points beyond the end of the data structure");}
    return avlTree_.valueAt(n);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::MultiMapIterator(avlTree_.iteratorAt(n));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapCustomisable<Key, Value, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::MultiMapConstIterator(avlTree_.constIteratorAt(n));
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::MultiMapIterator(SGEXTN::Containers::AVLTreeIterator<Key, Value, Comparator> i) : avlTreeIterator_(i) {}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator++(){
    avlTreeIterator_++;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator++(int){
    SGEXTN::Containers::MultiMapIterator prev = (*this);
    avlTreeIterator_++;
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator--(){
    avlTreeIterator_--;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator--(int){
    SGEXTN::Containers::MultiMapIterator prev = (*this);
    avlTreeIterator_--;
    return prev;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator==(const SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& x) const {
    return (avlTreeIterator_ == x.avlTreeIterator_);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::operator!=(const SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>& x) const {
    return (avlTreeIterator_ != x.avlTreeIterator_);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::key() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMapIterator::key crashed because the iterator is the end iterator");}
    return avlTreeIterator_.key();
}

template <typename Key, typename Value, typename Comparator> Value& SGEXTN::Containers::MultiMapIterator<Key, Value, Comparator>::value() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMapIterator::value crashed because the iterator is the end iterator");}
    return avlTreeIterator_.value();
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::MultiMapConstIterator(SGEXTN::Containers::AVLTreeConstIterator<Key, Value, Comparator> i) : avlTreeIterator_(i) {}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator++(){
    avlTreeIterator_++;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator++(int){
    SGEXTN::Containers::MultiMapConstIterator prev = (*this);
    avlTreeIterator_++;
    return prev;
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator--(){
    avlTreeIterator_--;
    return (*this);
}

template <typename Key, typename Value, typename Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator> SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator--(int){
    SGEXTN::Containers::MultiMapConstIterator prev = (*this);
    avlTreeIterator_--;
    return prev;
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator==(const SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& x) const {
    return (avlTreeIterator_ == x.avlTreeIterator_);
}

template <typename Key, typename Value, typename Comparator> bool SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::operator!=(const SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>& x) const {
    return (avlTreeIterator_ != x.avlTreeIterator_);
}

template <typename Key, typename Value, typename Comparator> const Key& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::key() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMapConstIterator::key crashed because the iterator is the end iterator");}
    return avlTreeIterator_.key();
}

template <typename Key, typename Value, typename Comparator> const Value& SGEXTN::Containers::MultiMapConstIterator<Key, Value, Comparator>::value() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMapConstIterator::value crashed because the iterator is the end iterator");}
    return avlTreeIterator_.value();
}
