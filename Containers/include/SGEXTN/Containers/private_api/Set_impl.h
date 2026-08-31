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

template <typename T, typename Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::SetCustomisable() : avlTree_() {}

template <typename T, typename Comparator> int SGEXTN::Containers::SetCustomisable<T, Comparator>::length() const {
    return avlTree_.length();
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetCustomisable<T, Comparator>::insert(const T& x){
    return avlTree_.insert(x, false, false);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetCustomisable<T, Comparator>::erase(const T& x){
    return avlTree_.erase(x);
}

template <typename T, typename Comparator> void SGEXTN::Containers::SetCustomisable<T, Comparator>::clear(){
    avlTree_.clear();
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetCustomisable<T, Comparator>::contains(const T& x) const {
    return avlTree_.contains(x);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::begin(){
    return SGEXTN::Containers::SetIterator(avlTree_.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::constBegin() const {
    return SGEXTN::Containers::SetConstIterator(avlTree_.constBegin());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::end(){
    return SGEXTN::Containers::SetIterator(avlTree_.end());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::constEnd() const {
    return SGEXTN::Containers::SetConstIterator(avlTree_.constEnd());
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetCustomisable<T, Comparator>::erase(SGEXTN::Containers::SetIterator<T, Comparator>& i){
    return avlTree_.erase(i.avlTreeIterator_);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::find(const T& x){
    return SGEXTN::Containers::SetIterator(avlTree_.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::constFind(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(avlTree_.constFind(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::lowerBound(const T& x){
    return SGEXTN::Containers::SetIterator(avlTree_.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::constLowerBound(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(avlTree_.constLowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::upperBound(const T& x){
    return SGEXTN::Containers::SetIterator(avlTree_.upperBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::constUpperBound(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(avlTree_.constUpperBound(x));
}

template <typename T, typename Comparator> int SGEXTN::Containers::SetCustomisable<T, Comparator>::indexOf(const T& x) const {
    return avlTree_.indexOf(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::SetCustomisable<T, Comparator>::indexOf(SGEXTN::Containers::SetIterator<T, Comparator> i) const {
    return avlTree_.indexOf(i.avlTreeIterator_);
}

template <typename T, typename Comparator> int SGEXTN::Containers::SetCustomisable<T, Comparator>::indexOf(SGEXTN::Containers::SetConstIterator<T, Comparator> i) const {
    return avlTree_.indexOf(i.avlTreeIterator_);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::SetCustomisable<T, Comparator>::elementAt(int n) const {
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set::elementAt crashed because the index is negative");}
    if(n >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set::elementAt crashed because the index points beyond the end of the set");}
    return avlTree_.keyAt(n);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::SetIterator(avlTree_.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetCustomisable<T, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::SetConstIterator(avlTree_.constIteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::SetIterator(AVLTreeIterator<T, bool, Comparator> i) : avlTreeIterator_(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>& SGEXTN::Containers::SetIterator<T, Comparator>::operator++(){
    avlTreeIterator_++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::operator++(int){
    SetIterator prev = (*this);
    avlTreeIterator_++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>& SGEXTN::Containers::SetIterator<T, Comparator>::operator--(){
    avlTreeIterator_--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::operator--(int){
    SetIterator prev = (*this);
    avlTreeIterator_--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetIterator<T, Comparator>::operator==(const SGEXTN::Containers::SetIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ == x.avlTreeIterator_);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetIterator<T, Comparator>::operator!=(const SGEXTN::Containers::SetIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ != x.avlTreeIterator_);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::SetIterator<T, Comparator>::operator*() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::SetIterator::operator* crashed as the iterator is the end iterator");}
    return avlTreeIterator_.key();
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::SetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i) : avlTreeIterator_(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator++(){
    avlTreeIterator_++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::operator++(int){
    SGEXTN::Containers::SetConstIterator prev = (*this);
    avlTreeIterator_++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator--(){
    avlTreeIterator_--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::operator--(int){
    SGEXTN::Containers::SetConstIterator prev = (*this);
    avlTreeIterator_--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetConstIterator<T, Comparator>::operator==(const SGEXTN::Containers::SetConstIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ == x.avlTreeIterator_);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetConstIterator<T, Comparator>::operator!=(const SGEXTN::Containers::SetConstIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ != x.avlTreeIterator_);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator*() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::SetConstIterator::operator* crashed as the iterator is the end iterator");}
    return avlTreeIterator_.key();
}
