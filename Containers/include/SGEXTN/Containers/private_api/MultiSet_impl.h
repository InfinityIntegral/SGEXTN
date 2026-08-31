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

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::MultiSetCustomisable() : avlTree_() {}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::length() const {
    return avlTree_.length();
}

template <typename T, typename Comparator> void SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::insert(const T& x){
    avlTree_.insert(x, false, true);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::erase(const T& x){
    return avlTree_.erase(x);
}

template <typename T, typename Comparator> void SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::clear(){
    avlTree_.clear();
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::contains(const T& x) const {
    return avlTree_.contains(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::count(const T& x) const {
    return avlTree_.count(x);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::begin(){
    return SGEXTN::Containers::MultiSetIterator(avlTree_.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::constBegin() const {
    return SGEXTN::Containers::MultiSetConstIterator(avlTree_.constBegin());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::end(){
    return SGEXTN::Containers::MultiSetIterator(avlTree_.end());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::constEnd() const {
    return SGEXTN::Containers::MultiSetConstIterator(avlTree_.constEnd());
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::erase(SGEXTN::Containers::MultiSetIterator<T, Comparator>& i){
    return avlTree_.erase(i.avlTreeIterator_);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::find(const T& x){
    return SGEXTN::Containers::MultiSetIterator(avlTree_.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::constFind(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(avlTree_.constFind(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::lowerBound(const T& x){
    return SGEXTN::Containers::MultiSetIterator(avlTree_.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::constLowerBound(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(avlTree_.constLowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::upperBound(const T& x){
    return SGEXTN::Containers::MultiSetIterator(avlTree_.upperBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::constUpperBound(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(avlTree_.constUpperBound(x));
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::indexOf(const T& x) const {
    return avlTree_.indexOf(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::indexOf(SGEXTN::Containers::MultiSetIterator<T, Comparator> i) const {
    return avlTree_.indexOf(i.avlTreeIterator_);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::indexOf(SGEXTN::Containers::MultiSetConstIterator<T, Comparator> i) const {
    return avlTree_.indexOf(i.avlTreeIterator_);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::elementAt(int n) const {
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet::elementAt crashed because the index is negative");}
    if(n >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet::elementAt crashed because the index points beyond the end of the set");}
    return avlTree_.keyAt(n);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::MultiSetIterator(avlTree_.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetCustomisable<T, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::MultiSetConstIterator(avlTree_.constIteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::MultiSetIterator(AVLTreeIterator<T, bool, Comparator> i) : avlTreeIterator_(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator++(){
    avlTreeIterator_++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator++(int){
    MultiSetIterator prev = (*this);
    avlTreeIterator_++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator--(){
    avlTreeIterator_--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator--(int){
    MultiSetIterator prev = (*this);
    avlTreeIterator_--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator==(const SGEXTN::Containers::MultiSetIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ == x.avlTreeIterator_);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator!=(const SGEXTN::Containers::MultiSetIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ != x.avlTreeIterator_);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator*() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSetIterator::operator* crashed as the iterator is the end iterator");}
    return avlTreeIterator_.key();
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::MultiSetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i) : avlTreeIterator_(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator++(){
    avlTreeIterator_++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator++(int){
    SGEXTN::Containers::MultiSetConstIterator prev = (*this);
    avlTreeIterator_++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator--(){
    avlTreeIterator_--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator--(int){
    SGEXTN::Containers::MultiSetConstIterator prev = (*this);
    avlTreeIterator_--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator==(const SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ == x.avlTreeIterator_);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator!=(const SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& x) const {
    return (avlTreeIterator_ != x.avlTreeIterator_);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator*() const {
    if(avlTreeIterator_.isEndIterator() == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSetConstIterator::operator* crashed as the iterator is the end iterator");}
    return avlTreeIterator_.key();
}
