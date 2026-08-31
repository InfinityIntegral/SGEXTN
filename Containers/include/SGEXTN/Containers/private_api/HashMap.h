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

namespace SGEXTN::Containers {
enum class HashMapSlotStatus : unsigned char {
    Active = 1,
    Unused = 2,
    Deleted = 3
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapSlot {
public:
    explicit HashMapSlot();
    HashMapSlot(const HashMapSlot&) = delete;
    HashMapSlot& operator=(const HashMapSlot&) = delete;
    HashMapSlot(HashMapSlot&&) = delete;
    HashMapSlot& operator=(HashMapSlot&&) = delete;
    ~HashMapSlot();
    HashMapSlotStatus status;
    union {
        unsigned char keyConstructorRemover;
        Key keyObject;
    };
    union {
        unsigned char valueConstructorRemover;
        Value valueObject;
    };
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapIterator;
template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapConstIterator;

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMap {
private:
    friend class HashMapIterator<Key, Value, EqualityCheck, HashFunction>;
    friend class HashMapConstIterator<Key, Value, EqualityCheck, HashFunction>;
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* data_;
    int activeLength_;
    int memoryUsedLength_;
    int memoryTotalLength_;
    float loadFactor_;
    float efficiencyFactor_;
    EqualityCheck equalityCheckInstance_;
    HashFunction hashFunctionInstance_;
    [[nodiscard]] int getHashIndex(const Key& x) const;
    bool hashInto(const Key& key, const Value& value);
    void rehashAll(int newMemoryLength);
    [[nodiscard]] HashMapSlot<Key, Value, EqualityCheck, HashFunction>* getSlotFromKey(const Key& x) const;
    [[nodiscard]] HashMapSlot<Key, Value, EqualityCheck, HashFunction>* getPreviousSlot(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const;
    [[nodiscard]] HashMapSlot<Key, Value, EqualityCheck, HashFunction>* getNextSlot(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const;
public:
    explicit HashMap();
    HashMap(const HashMap& x);
    HashMap& operator=(const HashMap& x);
    HashMap(HashMap&& x) noexcept;
    HashMap& operator=(HashMap&& x) noexcept;
    ~HashMap();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    bool insert(const Key& key, const Value& value);
    bool erase(const Key& x);
    void clear();
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] int count(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] HashMapIterator<Key, Value, EqualityCheck, HashFunction> begin();
    [[nodiscard]] HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> constBegin() const;
    [[nodiscard]] HashMapIterator<Key, Value, EqualityCheck, HashFunction> end();
    [[nodiscard]] HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> constEnd() const;
    bool erase(HashMapIterator<Key, Value, EqualityCheck, HashFunction>& i);
    [[nodiscard]] HashMapIterator<Key, Value, EqualityCheck, HashFunction> find(const Key& x);
    [[nodiscard]] HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> constFind(const Key& x) const;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapIterator {
private:
    friend class HashMap<Key, Value, EqualityCheck, HashFunction>;
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* associatedSlot_;
    HashMap<Key, Value, EqualityCheck, HashFunction>* associatedMap_;
public:
    explicit HashMapIterator(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, HashMap<Key, Value, EqualityCheck, HashFunction>* map);
    HashMapIterator& operator++();
    HashMapIterator operator++(int);
    HashMapIterator& operator--();
    HashMapIterator operator--(int);
    [[nodiscard]] bool operator==(const HashMapIterator& x) const;
    [[nodiscard]] bool operator!=(const HashMapIterator& x) const;
    [[nodiscard]] const Key& key() const;
    [[nodiscard]] Value& value() const;
    [[nodiscard]] bool isEndIterator() const;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapConstIterator {
private:
    friend class HashMap<Key, Value, EqualityCheck, HashFunction>;
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* associatedSlot_;
    const HashMap<Key, Value, EqualityCheck, HashFunction>* associatedMap_;
public:
    explicit HashMapConstIterator(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, const HashMap<Key, Value, EqualityCheck, HashFunction>* map);
    HashMapConstIterator& operator++();
    HashMapConstIterator operator++(int);
    HashMapConstIterator& operator--();
    HashMapConstIterator operator--(int);
    [[nodiscard]] bool operator==(const HashMapConstIterator& x) const;
    [[nodiscard]] bool operator!=(const HashMapConstIterator& x) const;
    [[nodiscard]] const Key& key() const;
    [[nodiscard]] const Value& value() const;
    [[nodiscard]] bool isEndIterator() const;
};
}

#include <SGEXTN/Containers/private_api/HashMap_impl.h>
