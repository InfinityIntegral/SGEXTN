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
#include <private_api/SGEXTN_Containers_HashMap.h>

namespace SGEXTN {
namespace Containers {
template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMapIterator;
template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMapConstIterator;

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMap {
public:
    HashMap<Key, Value, EqualityCheck, HashFunction> private_hashMap;
    UnorderedMap();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    bool insert(const Key& key, const Value& value);
    bool erase(const Key& x);
    void clear();
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> begin();
    [[nodiscard]] UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> constBegin() const;
    [[nodiscard]] UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> end();
    [[nodiscard]] UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> constEnd() const;
    bool erase(UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& i);
    [[nodiscard]] UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> find(const Key& x);
    [[nodiscard]] UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> constFind(const Key& x) const;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMapIterator {
public:
    HashMapIterator<Key, Value, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedMapIterator(HashMapIterator<Key, Value, EqualityCheck, HashFunction> i);
    UnorderedMapIterator& operator++();
    UnorderedMapIterator operator++(int);
    UnorderedMapIterator& operator--();
    UnorderedMapIterator operator--(int);
    [[nodiscard]] bool operator==(const UnorderedMapIterator& x) const;
    [[nodiscard]] bool operator!=(const UnorderedMapIterator& x) const;
    [[nodiscard]] const Key& key() const;
    [[nodiscard]] Value& value() const;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMapConstIterator {
public:
    HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedMapConstIterator(HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> i);
    UnorderedMapConstIterator& operator++();
    UnorderedMapConstIterator operator++(int);
    UnorderedMapConstIterator& operator--();
    UnorderedMapConstIterator operator--(int);
    [[nodiscard]] bool operator==(const UnorderedMapConstIterator& x) const;
    [[nodiscard]] bool operator!=(const UnorderedMapConstIterator& x) const;
    [[nodiscard]] const Key& key() const;
    [[nodiscard]] const Value& value() const;
};
}
}

#include <private_api/SGEXTN_Containers_UnorderedMap_impl.h>
