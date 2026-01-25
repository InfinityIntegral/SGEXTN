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
    [[nodiscard]] bool contains(const Key& x) const;
    [[nodiscard]] Value& at(const Key& x);
    [[nodiscard]] const Value& at(const Key& x) const;
    [[nodiscard]] UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> begin();
    [[nodiscard]] UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> begin() const;
    [[nodiscard]] UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> end();
    [[nodiscard]] UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> end() const;
    bool erase(UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction>& i);
    [[nodiscard]] UnorderedMapIterator<Key, Value, EqualityCheck, HashFunction> find(const Key& x);
    [[nodiscard]] UnorderedMapConstIterator<Key, Value, EqualityCheck, HashFunction> find(const Key& x) const;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMapIterator {
public:
    HashMapIterator<Key, Value, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedMapIterator(HashMapIterator<Key, Value, EqualityCheck, HashFunction> i);
    UnorderedMapIterator& operator++();
    UnorderedMapIterator operator++(int);
    UnorderedMapIterator& operator--();
    UnorderedMapIterator operator--(int);
    bool operator==(const UnorderedMapIterator& x);
    bool operator!=(const UnorderedMapIterator& x);
    const Key& key();
    Value& value();
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class UnorderedMapConstIterator {
public:
    HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedMapConstIterator(HashMapConstIterator<Key, Value, EqualityCheck, HashFunction> i);
    UnorderedMapConstIterator& operator++();
    UnorderedMapConstIterator operator++(int);
    UnorderedMapConstIterator& operator--();
    UnorderedMapConstIterator operator--(int);
    bool operator==(const UnorderedMapConstIterator& x);
    bool operator!=(const UnorderedMapConstIterator& x);
    const Key& key();
    const Value& value();
};
}
}

#include <private_api/SGEXTN_Containers_UnorderedMap_impl.h>
