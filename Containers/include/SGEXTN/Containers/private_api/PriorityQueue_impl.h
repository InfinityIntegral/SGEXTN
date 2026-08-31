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

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::PriorityQueueCustomisable() : ringBuffer_(), comparatorInstance_() {}

template <typename T, typename Comparator> const T& SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::top() const {
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue::top crashed as the priority queue is empty");}
    return ringBuffer_.at(0);
}

template <typename T, typename Comparator> int SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::length() const {
    return ringBuffer_.length();
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::reserve(int newMemoryLength){
    ringBuffer_.reserve(newMemoryLength);
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::swap(int a, int b){
    T temp(static_cast<T&&>(ringBuffer_.at(a)));
    ringBuffer_.at(a) = static_cast<T&&>(ringBuffer_.at(b));
    ringBuffer_.at(b) = static_cast<T&&>(temp);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::compare(int a, int b){
    return comparatorInstance_(ringBuffer_.at(a), ringBuffer_.at(b));
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::push(const T& x){
    ringBuffer_.pushBack(x);
    int i = ringBuffer_.length() - 1;
    while(i > 0){
        const int parentIndex = (i - 1) / 2;
        if(compare(parentIndex, i) == true){swap(parentIndex, i);}
        else{break;}
        i = parentIndex;
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::pop(){
    if(ringBuffer_.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue::pop crashed as the priority queue is empty");}
    swap(0, ringBuffer_.length() - 1);
    ringBuffer_.popBack();
    int i = 0;
    while(true){
        const int leftChild = 2 * i + 1;
        const int rightChild = 2 * i + 2;
        if(rightChild < ringBuffer_.length()){
            if(compare(i, leftChild) == false && compare(i, rightChild) == false){break;}
            if(compare(leftChild, rightChild) == true){
                swap(i, rightChild);
                i = rightChild;
            }
            else{
                swap(i, leftChild);
                i = leftChild;
            }
        }
        else if(leftChild < ringBuffer_.length()){
            if(compare(i, leftChild) == true){swap(i, leftChild);}
            break;
        }
        else{break;}
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueueCustomisable<T, Comparator>::clear(){
    ringBuffer_.clear();
}
