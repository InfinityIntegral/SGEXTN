#pragma once
#include <private_api/SGEXTN_Containers_HashMap.h>

namespace SGEXTN {
namespace Containers {
template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetIterator;
template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetConstIterator;

template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSet {
public:
    HashMap<T, bool, EqualityCheck, HashFunction> private_hashMap;
    UnorderedSet();
    [[nodiscard]] int length() const;
    void reserve(int newMemoryLength);
    bool insert(const T& x);
    bool erase(const T& x);
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] UnorderedSetIterator<T, EqualityCheck, HashFunction> begin();
    [[nodiscard]] UnorderedSetConstIterator<T, EqualityCheck, HashFunction> constBegin() const;
    [[nodiscard]] UnorderedSetIterator<T, EqualityCheck, HashFunction> end();
    [[nodiscard]] UnorderedSetConstIterator<T, EqualityCheck, HashFunction> constEnd() const;
    bool erase(UnorderedSetIterator<T, EqualityCheck, HashFunction>& i);
    [[nodiscard]] UnorderedSetIterator<T, EqualityCheck, HashFunction> find(const T& x);
    [[nodiscard]] UnorderedSetConstIterator<T, EqualityCheck, HashFunction> constFind(const T& x) const;
};

template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetIterator {
public:
    HashMapIterator<T, bool, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedSetIterator(HashMapIterator<T, bool, EqualityCheck, HashFunction> i);
    UnorderedSetIterator& operator++();
    UnorderedSetIterator operator++(int);
    UnorderedSetIterator& operator--();
    UnorderedSetIterator operator--(int);
    bool operator==(const UnorderedSetIterator& x);
    bool operator!=(const UnorderedSetIterator& x);
    const T& operator*();
};

template <typename T, typename EqualityCheck, typename HashFunction> class UnorderedSetConstIterator {
public:
    HashMapConstIterator<T, bool, EqualityCheck, HashFunction> private_hashMapIterator;
    UnorderedSetConstIterator(HashMapConstIterator<T, bool, EqualityCheck, HashFunction> i);
    UnorderedSetConstIterator& operator++();
    UnorderedSetConstIterator operator++(int);
    UnorderedSetConstIterator& operator--();
    UnorderedSetConstIterator operator--(int);
    bool operator==(const UnorderedSetConstIterator& x);
    bool operator!=(const UnorderedSetConstIterator& x);
    const T& operator*();
};
}
}

#include <private_api/SGEXTN_Containers_UnorderedSet_impl.h>
