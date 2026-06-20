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

template <typename T, typename Comparator> SGEXTN::Containers::Set<T, Comparator>::Set() : private_avlTree() {}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::length() const {
    return private_avlTree.length();
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::insert(const T& x){
    return private_avlTree.insert(x, false, false);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::erase(const T& x){
    return private_avlTree.erase(x);
}

template <typename T, typename Comparator> void SGEXTN::Containers::Set<T, Comparator>::clear(){
    private_avlTree.clear();
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::contains(const T& x) const {
    return private_avlTree.contains(x);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::begin(){
    return SGEXTN::Containers::SetIterator(private_avlTree.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::constBegin() const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.constBegin());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::end(){
    return SGEXTN::Containers::SetIterator(private_avlTree.end());
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::constEnd() const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.constEnd());
}

template <typename T, typename Comparator> bool SGEXTN::Containers::Set<T, Comparator>::erase(SGEXTN::Containers::SetIterator<T, Comparator>& i){
    return private_avlTree.erase(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::find(const T& x){
    return SGEXTN::Containers::SetIterator(private_avlTree.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::constFind(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.constFind(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::lowerBound(const T& x){
    return SGEXTN::Containers::SetIterator(private_avlTree.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::constLowerBound(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.constLowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::upperBound(const T& x){
    return SGEXTN::Containers::SetIterator(private_avlTree.upperBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::constUpperBound(const T& x) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.constUpperBound(x));
}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::indexOf(const T& x) const {
    return private_avlTree.indexOf(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::indexOf(SGEXTN::Containers::SetIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> int SGEXTN::Containers::Set<T, Comparator>::indexOf(SGEXTN::Containers::SetConstIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::Set<T, Comparator>::elementAt(int n) const {
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set::elementAt crashed because the index is negative");}
    if(n >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set::elementAt crashed because the index points beyond the end of the set");}
    return private_avlTree.keyAt(n);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::SetIterator(private_avlTree.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::Set<T, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::SetConstIterator(private_avlTree.constIteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::SetIterator(AVLTreeIterator<T, bool, Comparator> i) : private_avlTreeIterator(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>& SGEXTN::Containers::SetIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::operator++(int){
    SetIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator>& SGEXTN::Containers::SetIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetIterator<T, Comparator> SGEXTN::Containers::SetIterator<T, Comparator>::operator--(int){
    SetIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetIterator<T, Comparator>::operator==(const SGEXTN::Containers::SetIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetIterator<T, Comparator>::operator!=(const SGEXTN::Containers::SetIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::SetIterator<T, Comparator>::operator*() const {
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::SetIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::SetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i) : private_avlTreeIterator(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::operator++(int){
    SGEXTN::Containers::SetConstIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator> SGEXTN::Containers::SetConstIterator<T, Comparator>::operator--(int){
    SGEXTN::Containers::SetConstIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetConstIterator<T, Comparator>::operator==(const SGEXTN::Containers::SetConstIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::SetConstIterator<T, Comparator>::operator!=(const SGEXTN::Containers::SetConstIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::SetConstIterator<T, Comparator>::operator*() const {
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::SetConstIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}
