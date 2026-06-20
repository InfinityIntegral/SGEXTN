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
#include <private_api/SGEXTN_Containers_AVLTree.h>

namespace SGEXTN {
namespace Containers {
template <typename T, typename Comparator> class SetIterator;
template <typename T, typename Comparator> class SetConstIterator;

template <typename T, typename Comparator> class Set {
public:
    AVLTree<T, bool, Comparator> private_avlTree;
    Set();
    [[nodiscard]] int length() const;
    bool insert(const T& x);
    bool erase(const T& x);
    void clear();
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] SetIterator<T, Comparator> begin();
    [[nodiscard]] SetConstIterator<T, Comparator> constBegin() const;
    [[nodiscard]] SetIterator<T, Comparator> end();
    [[nodiscard]] SetConstIterator<T, Comparator> constEnd() const;
    bool erase(SetIterator<T, Comparator>& i);
    [[nodiscard]] SetIterator<T, Comparator> find(const T& x);
    [[nodiscard]] SetConstIterator<T, Comparator> constFind(const T& x) const;
    [[nodiscard]] SetIterator<T, Comparator> lowerBound(const T& x);
    [[nodiscard]] SetConstIterator<T, Comparator> constLowerBound(const T& x) const;
    [[nodiscard]] SetIterator<T, Comparator> upperBound(const T& x);
    [[nodiscard]] SetConstIterator<T, Comparator> constUpperBound(const T& x) const;
    [[nodiscard]] int indexOf(const T& x) const;
    [[nodiscard]] int indexOf(SetIterator<T, Comparator> i) const;
    [[nodiscard]] int indexOf(SetConstIterator<T, Comparator> i) const;
    [[nodiscard]] const T& elementAt(int n) const;
    [[nodiscard]] SetIterator<T, Comparator> iteratorAt(int n);
    [[nodiscard]] SetConstIterator<T, Comparator> constIteratorAt(int n) const;
};

template <typename T, typename Comparator> class SetIterator {
public:
    AVLTreeIterator<T, bool, Comparator> private_avlTreeIterator;
    SetIterator(AVLTreeIterator<T, bool, Comparator> i);
    SetIterator& operator++();
    SetIterator operator++(int);
    SetIterator& operator--();
    SetIterator operator--(int);
    [[nodiscard]] bool operator==(const SetIterator& x) const;
    [[nodiscard]] bool operator!=(const SetIterator& x) const;
    [[nodiscard]] const T& operator*() const;
};

template <typename T, typename Comparator> class SetConstIterator {
public:
    AVLTreeConstIterator<T, bool, Comparator> private_avlTreeIterator;
    SetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i);
    SetConstIterator& operator++();
    SetConstIterator operator++(int);
    SetConstIterator& operator--();
    SetConstIterator operator--(int);
    [[nodiscard]] bool operator==(const SetConstIterator& x) const;
    [[nodiscard]] bool operator!=(const SetConstIterator& x) const;
    [[nodiscard]] const T& operator*() const;
};
}
}

#include <private_api/SGEXTN_Containers_Set_impl.h>
