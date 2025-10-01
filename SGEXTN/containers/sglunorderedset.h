#ifndef SGLUNORDEREDSET_H
#define SGLUNORDEREDSET_H

template <typename T, typename EqualityCheck, typename HashFunction> class SGLUnorderedSet {
protected:
    class Slot {
        friend class SGLUnorderedSet;
    public:
        static const char unused = 0;
        static const char active = 1;
        static const char deleted = 2;
        char usageStatus;
        T value;
    };
    Slot* dataInternal;
    int lengthInternal;
    int memoryLengthInternal;
    
public:
    SGLUnorderedSet();
    SGLUnorderedSet(const SGLUnorderedSet& x);
    SGLUnorderedSet& operator=(const SGLUnorderedSet& x);
    SGLUnorderedSet(SGLUnorderedSet&& x) noexcept;
    SGLUnorderedSet& operator=(SGLUnorderedSet&& x) noexcept;
    ~SGLUnorderedSet();
    [[nodiscard]] int length() const;
    void insert(const T& x);
    void erase(const T& x);
    [[nodiscard]] bool contains(const T& x) const;
    [[nodiscard]] bool count(const T& x) const;
    
    class Iterator {
        friend class SGLUnorderedSet;
    public:
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        bool operator==(Iterator x);
        bool operator!=(Iterator x);
        const T& operator*();
    protected:
        Slot* slot;
        SGLUnorderedSet* associatedSet;
        Iterator(Slot* x, SGLUnorderedSet* s);
    };
    
    class ConstIterator {
        friend class SGLUnorderedSet;
    public:
        ConstIterator& operator++();
        ConstIterator operator++(int);
        ConstIterator& operator--();
        ConstIterator operator--(int);
        bool operator==(ConstIterator x);
        bool operator!=(ConstIterator x);
        const T& operator*();
    protected:
        Slot* slot;
        const SGLUnorderedSet* associatedSet;
        ConstIterator(Slot* x, SGLUnorderedSet* s);
    };
    
    [[nodiscard]] Iterator begin();
    [[nodiscard]] Iterator end();
    [[nodiscard]] ConstIterator constBegin() const;
    [[nodiscard]] ConstIterator constEnd() const;
    void erase(Iterator x);
    [[nodiscard]] Iterator find(const T& x);
    [[nodiscard]] ConstIterator find(const T& x) const;
};

#endif // SGLUNORDEREDSET_H
