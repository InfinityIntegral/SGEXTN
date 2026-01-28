#pragma once

namespace SGEXTN {
namespace Containers {
enum class HashMapSlotStatus {Active, Unused, Deleted};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapSlot {
public:
    HashMapSlot();
    HashMapSlotStatus status;
    Key key;
    Value value;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapIterator;
template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapConstIterator;

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMap {
public:
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* data;
    int activeLength;
    int memoryUsedLength;
    int memoryTotalLength;
    float loadFactor;
    float efficiencyFactor;
    EqualityCheck equalityCheckInstance;
    HashFunction hashFunctionInstance;
    [[nodiscard]] int getHashIndex(const Key& x) const;
    bool rehash(const Key& key, const Value& value, bool allowDuplicate);
    void rehashAll(int newMemoryLength);
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* getSlotFromKey(const Key& x) const;
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* getPreviousSlot(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const;
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* getNextSlot(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* x) const;
    HashMap();
    HashMap(const HashMap& x);
    HashMap& operator=(const HashMap& x);
    HashMap(HashMap&& x) noexcept;
    HashMap& operator=(HashMap&& x) noexcept;
    ~HashMap();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    bool insert(const Key& key, const Value& value, bool allowDuplicate);
    bool erase(const Key& x);
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
public:
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* associatedSlot;
    HashMap<Key, Value, EqualityCheck, HashFunction>* associatedMap;
    HashMapIterator(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, HashMap<Key, Value, EqualityCheck, HashFunction>* map);
    HashMapIterator& operator++();
    HashMapIterator operator++(int);
    HashMapIterator& operator--();
    HashMapIterator operator--(int);
    bool operator==(const HashMapIterator& x);
    bool operator!=(const HashMapIterator& x);
    const Key& key();
    Value& value();
    HashMapIterator() = default;
};

template <typename Key, typename Value, typename EqualityCheck, typename HashFunction> class HashMapConstIterator {
public:
    HashMapSlot<Key, Value, EqualityCheck, HashFunction>* associatedSlot;
    const HashMap<Key, Value, EqualityCheck, HashFunction>* associatedMap;
    HashMapConstIterator(HashMapSlot<Key, Value, EqualityCheck, HashFunction>* slot, const HashMap<Key, Value, EqualityCheck, HashFunction>* map);
    HashMapConstIterator& operator++();
    HashMapConstIterator operator++(int);
    HashMapConstIterator& operator--();
    HashMapConstIterator operator--(int);
    bool operator==(const HashMapConstIterator& x);
    bool operator!=(const HashMapConstIterator& x);
    const Key& key();
    const Value& value();
    HashMapConstIterator() = default;
};
}
}

#include <private_api/SGEXTN_Containers_HashMap_impl.h>
