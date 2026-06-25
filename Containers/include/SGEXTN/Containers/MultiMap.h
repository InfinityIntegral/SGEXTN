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
#include <SGEXTN/Containers/private_api/AVLTree.h>

namespace SGEXTN {
namespace Containers {
template <typename Key, typename Value, typename Comparator> class MultiMapIterator;
template <typename Key, typename Value, typename Comparator> class MultiMapConstIterator;

template <typename Key, typename Value, typename Comparator> class MultiMap {
public:
    AVLTree<Key, Value, Comparator> private_avlTree;
    MultiMap();
    [[nodiscard]] int length() const;
    void insert(const Key& key, const Value& value);
    bool erase(const Key& x);
    void clear();
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] int count(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> begin();
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> constBegin() const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> end();
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> constEnd() const;
    bool erase(MultiMapIterator<Key, Value, Comparator>& i);
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> find(const Key& x);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> constFind(const Key& x) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> lowerBound(const Key& x);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> constLowerBound(const Key& x) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> upperBound(const Key& x);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> constUpperBound(const Key& x) const;
    [[nodiscard]] int indexOf(const Key& x) const;
    [[nodiscard]] int indexOf(MultiMapIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] int indexOf(MultiMapConstIterator<Key, Value, Comparator> i) const;
    [[nodiscard]] const Key& keyAt(int n) const;
    [[nodiscard]] Value& valueAt(int n);
    [[nodiscard]] const Value& valueAt(int n) const;
    [[nodiscard]] MultiMapIterator<Key, Value, Comparator> iteratorAt(int n);
    [[nodiscard]] MultiMapConstIterator<Key, Value, Comparator> constIteratorAt(int n) const;
};

template <typename Key, typename Value, typename Comparator> class MultiMapIterator {
public:
    AVLTreeIterator<Key, Value, Comparator> private_avlTreeIterator;
    MultiMapIterator(AVLTreeIterator<Key, Value, Comparator> i);
    MultiMapIterator& operator++();
    MultiMapIterator operator++(int);
    MultiMapIterator& operator--();
    MultiMapIterator operator--(int);
    [[nodiscard]] bool operator==(const MultiMapIterator& x) const;
    [[nodiscard]] bool operator!=(const MultiMapIterator& x) const;
    [[nodiscard]] const Key& key() const;
    [[nodiscard]] Value& value() const;
};

template <typename Key, typename Value, typename Comparator> class MultiMapConstIterator {
public:
    AVLTreeConstIterator<Key, Value, Comparator> private_avlTreeIterator;
    MultiMapConstIterator(AVLTreeConstIterator<Key, Value, Comparator> i);
    MultiMapConstIterator& operator++();
    MultiMapConstIterator operator++(int);
    MultiMapConstIterator& operator--();
    MultiMapConstIterator operator--(int);
    [[nodiscard]] bool operator==(const MultiMapConstIterator& x) const;
    [[nodiscard]] bool operator!=(const MultiMapConstIterator& x) const;
    [[nodiscard]] const Key& key() const;
    [[nodiscard]] const Value& value() const;
};
}
}

#include <SGEXTN/Containers/private_api/MultiMap_impl.h>
