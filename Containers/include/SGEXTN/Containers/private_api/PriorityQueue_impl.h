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

template <typename T, typename Comparator> SGEXTN::Containers::PriorityQueue<T, Comparator>::PriorityQueue() : private_ringBuffer(), private_comparatorInstance() {}

template <typename T, typename Comparator> const T& SGEXTN::Containers::PriorityQueue<T, Comparator>::top() const {
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue::top crashed as the priority queue is empty");}
    return private_ringBuffer.at(0);
}

template <typename T, typename Comparator> int SGEXTN::Containers::PriorityQueue<T, Comparator>::length() const {
    return private_ringBuffer.length();
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::reserve(int newMemoryLength){
    private_ringBuffer.reserve(newMemoryLength);
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::private_swap(int a, int b){
    T temp(static_cast<T&&>(private_ringBuffer.at(a)));
    private_ringBuffer.at(a) = static_cast<T&&>(private_ringBuffer.at(b));
    private_ringBuffer.at(b) = static_cast<T&&>(temp);
}

template <typename T, typename Comparator> bool SGEXTN::Containers::PriorityQueue<T, Comparator>::private_compare(int a, int b){
    return private_comparatorInstance(private_ringBuffer.at(a), private_ringBuffer.at(b));
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::push(const T& x){
    private_ringBuffer.pushBack(x);
    int i = private_ringBuffer.length() - 1;
    while(i > 0){
        const int parentIndex = (i - 1) / 2;
        if(private_compare(parentIndex, i) == true){private_swap(parentIndex, i);}
        else{break;}
        i = parentIndex;
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::pop(){
    if(private_ringBuffer.length() == 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue::pop crashed as the priority queue is empty");}
    private_swap(0, private_ringBuffer.length() - 1);
    private_ringBuffer.popBack();
    int i = 0;
    while(true){
        const int leftChild = 2 * i + 1;
        const int rightChild = 2 * i + 2;
        if(rightChild < private_ringBuffer.length()){
            if(private_compare(i, leftChild) == false && private_compare(i, rightChild) == false){break;}
            if(private_compare(leftChild, rightChild) == true){
                private_swap(i, rightChild);
                i = rightChild;
            }
            else{
                private_swap(i, leftChild);
                i = leftChild;
            }
        }
        else if(leftChild < private_ringBuffer.length()){
            if(private_compare(i, leftChild) == true){private_swap(i, leftChild);}
            break;
        }
        else{break;}
    }
}

template <typename T, typename Comparator> void SGEXTN::Containers::PriorityQueue<T, Comparator>::clear(){
    private_ringBuffer.clear();
}
