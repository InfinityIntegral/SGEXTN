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
#include <SGEXTN_Containers_ForceCrash.h>

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::UnorderedSet() : private_hashMap() {}

template <typename T, typename EqualityCheck, typename HashFunction> int SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::length() const {
    return private_hashMap.length();
}

template <typename T, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::reserve(int newMemoryLength){
    private_hashMap.reserve(newMemoryLength);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::insert(const T& x){
    return private_hashMap.insert(x, false);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::erase(const T& x){
    return private_hashMap.erase(x);
}

template <typename T, typename EqualityCheck, typename HashFunction> void SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::clear(){
    private_hashMap.clear();
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::contains(const T& x) const {
    return private_hashMap.contains(x);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::begin(){
    return SGEXTN::Containers::UnorderedSetIterator(private_hashMap.begin());
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::constBegin() const {
    return SGEXTN::Containers::UnorderedSetConstIterator(private_hashMap.constBegin());
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::end(){
    return SGEXTN::Containers::UnorderedSetIterator(private_hashMap.end());
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::constEnd() const {
    return SGEXTN::Containers::UnorderedSetConstIterator(private_hashMap.constEnd());
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::erase(SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& i){
    return private_hashMap.erase(i.private_hashMapIterator);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::find(const T& x){
    return SGEXTN::Containers::UnorderedSetIterator(private_hashMap.find(x));
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSet<T, EqualityCheck, HashFunction>::constFind(const T& x) const {
    return SGEXTN::Containers::UnorderedSetConstIterator(private_hashMap.constFind(x));
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::UnorderedSetIterator(SGEXTN::Containers::HashMapIterator<T, bool, EqualityCheck, HashFunction> i) : private_hashMapIterator(i) {}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::UnorderedSetConstIterator(SGEXTN::Containers::HashMapConstIterator<T, bool, EqualityCheck, HashFunction> i) : private_hashMapIterator(i) {}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator++(){
    private_hashMapIterator++;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedSetIterator prev = (*this);
    private_hashMapIterator++;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator--(){
    private_hashMapIterator--;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedSetIterator prev = (*this);
    private_hashMapIterator--;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& x) const {
    return (private_hashMapIterator == x.private_hashMapIterator);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>& x) const {
    return (private_hashMapIterator != x.private_hashMapIterator);
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGEXTN::Containers::UnorderedSetIterator<T, EqualityCheck, HashFunction>::operator*() const {
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSetIterator::operator* crashed because the iterator is the end iterator");}
    return private_hashMapIterator.key();
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator++(){
    private_hashMapIterator++;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator++(int){
    SGEXTN::Containers::UnorderedSetConstIterator prev = (*this);
    private_hashMapIterator++;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator--(){
    private_hashMapIterator--;
    return (*this);
}

template <typename T, typename EqualityCheck, typename HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction> SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator--(int){
    SGEXTN::Containers::UnorderedSetConstIterator prev = (*this);
    private_hashMapIterator--;
    return prev;
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator==(const SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& x) const {
    return (private_hashMapIterator == x.private_hashMapIterator);
}

template <typename T, typename EqualityCheck, typename HashFunction> bool SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator!=(const SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>& x) const {
    return (private_hashMapIterator != x.private_hashMapIterator);
}

template <typename T, typename EqualityCheck, typename HashFunction> const T& SGEXTN::Containers::UnorderedSetConstIterator<T, EqualityCheck, HashFunction>::operator*() const {
    if(private_hashMapIterator.associatedSlot == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSetConstIterator::operator* crashed because the iterator is the end iterator");}
    return private_hashMapIterator.key();
}
