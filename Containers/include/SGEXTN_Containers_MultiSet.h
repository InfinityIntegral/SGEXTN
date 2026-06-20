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
template <typename T, typename Comparator> class MultiSetIterator;
template <typename T, typename Comparator> class MultiSetConstIterator;

template <typename T, typename Comparator> class MultiSet {
public:
    AVLTree<T, bool, Comparator> private_avlTree;
    MultiSet();
    [[nodiscard]] int length() const;
    void insert(const T& x);
    bool erase(const T& x);
    void clear();
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] int count(const T& x) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> begin();
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constBegin() const;
    [[nodiscard]] MultiSetIterator<T, Comparator> end();
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constEnd() const;
    bool erase(MultiSetIterator<T, Comparator>& i);
    [[nodiscard]] MultiSetIterator<T, Comparator> find(const T& x);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constFind(const T& x) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> lowerBound(const T& x);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constLowerBound(const T& x) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> upperBound(const T& x);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constUpperBound(const T& x) const;
    [[nodiscard]] int indexOf(const T& x) const;
    [[nodiscard]] int indexOf(MultiSetIterator<T, Comparator> i) const;
    [[nodiscard]] int indexOf(MultiSetConstIterator<T, Comparator> i) const;
    [[nodiscard]] const T& elementAt(int n) const;
    [[nodiscard]] MultiSetIterator<T, Comparator> iteratorAt(int n);
    [[nodiscard]] MultiSetConstIterator<T, Comparator> constIteratorAt(int n) const;
};

template <typename T, typename Comparator> class MultiSetIterator {
public:
    AVLTreeIterator<T, bool, Comparator> private_avlTreeIterator;
    MultiSetIterator(AVLTreeIterator<T, bool, Comparator> i);
    MultiSetIterator& operator++();
    MultiSetIterator operator++(int);
    MultiSetIterator& operator--();
    MultiSetIterator operator--(int);
    [[nodiscard]] bool operator==(const MultiSetIterator& x) const;
    [[nodiscard]] bool operator!=(const MultiSetIterator& x) const;
    [[nodiscard]] const T& operator*() const;
};

template <typename T, typename Comparator> class MultiSetConstIterator {
public:
    AVLTreeConstIterator<T, bool, Comparator> private_avlTreeIterator;
    MultiSetConstIterator(AVLTreeConstIterator<T, bool, Comparator> i);
    MultiSetConstIterator& operator++();
    MultiSetConstIterator operator++(int);
    MultiSetConstIterator& operator--();
    MultiSetConstIterator operator--(int);
    [[nodiscard]] bool operator==(const MultiSetConstIterator& x) const;
    [[nodiscard]] bool operator!=(const MultiSetConstIterator& x) const;
    [[nodiscard]] const T& operator*() const;
};
}
}

#include <private_api/SGEXTN_Containers_MultiSet_impl.h>
