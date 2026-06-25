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

template <typename T, typename Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::MultiSet() : private_avlTree() {}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::length() const {
    return private_avlTree.length();
}

template <typename T, typename Comparator> void SGEXTN::Containers::MultiSet<T, Comparator>::insert(const T& x){
    private_avlTree.insert(x, false, true);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSet<T, Comparator>::erase(const T& x){
    return private_avlTree.erase(x);
}

template <typename T, typename Comparator> void SGEXTN::Containers::MultiSet<T, Comparator>::clear(){
    private_avlTree.clear();
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSet<T, Comparator>::contains(const T& x) const {
    return private_avlTree.contains(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::count(const T& x) const {
    return private_avlTree.count(x);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::begin(){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.begin());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constBegin() const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.constBegin());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::end(){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.end());
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constEnd() const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.constEnd());
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSet<T, Comparator>::erase(SGEXTN::Containers::MultiSetIterator<T, Comparator>& i){
    return private_avlTree.erase(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::find(const T& x){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.find(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constFind(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.constFind(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::lowerBound(const T& x){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.lowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constLowerBound(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.constLowerBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::upperBound(const T& x){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.upperBound(x));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constUpperBound(const T& x) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.constUpperBound(x));
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::indexOf(const T& x) const {
    return private_avlTree.indexOf(x);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::indexOf(SGEXTN::Containers::MultiSetIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> int SGEXTN::Containers::MultiSet<T, Comparator>::indexOf(SGEXTN::Containers::MultiSetConstIterator<T, Comparator> i) const {
    return private_avlTree.indexOf(i.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSet<T, Comparator>::elementAt(int n) const {
    if(n < 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet::elementAt crashed because the index is negative");}
    if(n >= length()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet::elementAt crashed because the index points beyond the end of the set");}
    return private_avlTree.keyAt(n);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::iteratorAt(int n){
    return SGEXTN::Containers::MultiSetIterator(private_avlTree.iteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSet<T, Comparator>::constIteratorAt(int n) const {
    return SGEXTN::Containers::MultiSetConstIterator(private_avlTree.constIteratorAt(n));
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::MultiSetIterator(AVLTreeIterator<T, bool, Comparator> i) : private_avlTreeIterator(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator++(int){
    MultiSetIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator> SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator--(int){
    MultiSetIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator==(const SGEXTN::Containers::MultiSetIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator!=(const SGEXTN::Containers::MultiSetIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSetIterator<T, Comparator>::operator*() const {
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSetIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::MultiSetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i) : private_avlTreeIterator(i) {}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator++(){
    private_avlTreeIterator++;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator++(int){
    SGEXTN::Containers::MultiSetConstIterator prev = (*this);
    private_avlTreeIterator++;
    return prev;
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator--(){
    private_avlTreeIterator--;
    return (*this);
}

template <typename T, typename Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator> SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator--(int){
    SGEXTN::Containers::MultiSetConstIterator prev = (*this);
    private_avlTreeIterator--;
    return prev;
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator==(const SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator == x.private_avlTreeIterator);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator!=(const SGEXTN::Containers::MultiSetConstIterator<T, Comparator>& x) const {
    return (private_avlTreeIterator != x.private_avlTreeIterator);
}

template <typename T, typename Comparator> const T& SGEXTN::Containers::MultiSetConstIterator<T, Comparator>::operator*() const {
    if(private_avlTreeIterator.associatedNode == nullptr){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSetConstIterator::operator* crashed as the iterator is the end iterator");}
    return private_avlTreeIterator.key();
}
