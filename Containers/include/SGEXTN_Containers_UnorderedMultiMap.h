#pragma once
#include <private_api/SGEXTN_Containers_HashMap.h>

namespace SGEXTN {
namespace Containers {
template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMultiMapIterator;
template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMultiMapConstIterator;

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMultiMap {
public:
    HashMap<Key, Value, EqualityCheck, HashFunction> private_hashMap;
    UnorderedMultiMap();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    bool insert(const Key& key, const Value& value);
    bool erase(const Key& x);
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] int count(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> begin();
    [[nodiscard]] UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> begin() const;
    [[nodiscard]] UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> end();
    [[nodiscard]] UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> end() const;
    bool erase(UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction>& i);
    [[nodiscard]] UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> find(const Key& x);
    [[nodiscard]] UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> find(const Key& x) const;
    [[nodiscard]] UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> equalRangeBegin(const Key& x);
    [[nodiscard]] UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> equalRangeBegin(const Key& x) const;
    [[nodiscard]] UnorderedMultiMapIterator<Key, Value, EqualityCheck, HashFunction> equalRangeEnd(const Key& x);
    [[nodiscard]] UnorderedMultiMapConstIterator<Key, Value, EqualityCheck, HashFunction> equalRangeEnd(const Key& x) const;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMultiMapIterator {
public:
    HashMapIterator<Key, Value, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedMultiMapIterator(HashMapIterator<Key, Value, EqualityCheck, HashFunction> i);
    UnorderedMultiMapIterator& operator++();
    UnorderedMultiMapIterator operator++(int);
    UnorderedMultiMapIterator& operator--();
    UnorderedMultiMapIterator operator--(int);
    bool operator==(const UnorderedMultiMapIterator& x);
    bool operator!=(const UnorderedMultiMapIterator& x);
    const Key& key();
    Value& value();
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMultiMapConstIterator {
public:
    HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedMultiMapConstIterator(HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> i);
    UnorderedMultiMapConstIterator& operator++();
    UnorderedMultiMapConstIterator operator++(int);
    UnorderedMultiMapConstIterator& operator--();
    UnorderedMultiMapConstIterator operator--(int);
    bool operator==(const UnorderedMultiMapConstIterator& x);
    bool operator!=(const UnorderedMultiMapConstIterator& x);
    const Key& key();
    const Value& value();
};
}
}

#include <private_api/SGEXTN_Containers_UnorderedMultiMap_impl.h>
