#include <private_api/SGEXTN_InternalTest_ContainersTest.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <SGEXTN_Containers_ForceCrash.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_Span.h>
#include <SGEXTN_Containers_LessThan.h>
#include <SGEXTN_Containers_MoreThan.h>
#include <SGEXTN_Containers_Vector.h>
#include <SGEXTN_Containers_Queue.h>
#include <SGEXTN_Containers_Stack.h>
#include <SGEXTN_Containers_Deque.h>
#include <SGEXTN_Containers_PriorityQueue.h>
#include <SGEXTN_Containers_Set.h>
#include <SGEXTN_Containers_MultiSet.h>
#include <SGEXTN_Containers_Map.h>
#include <SGEXTN_Containers_MultiMap.h>
#include <SGEXTN_Containers_UnorderedSet.h>
#include <SGEXTN_Containers_UnorderedMap.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_ArrayVectorMove.h>

namespace {
class ConstructibleInteger {
public:
    static int lastConstruct;
    static int lastDestruct;
    int value;
    ConstructibleInteger(int x);
    ConstructibleInteger(const ConstructibleInteger& x);
    ConstructibleInteger& operator=(const ConstructibleInteger& x);
    ConstructibleInteger(ConstructibleInteger&& x) noexcept;
    ConstructibleInteger& operator=(ConstructibleInteger&& x) noexcept;
    ~ConstructibleInteger();
    [[nodiscard]] operator int() const;
    [[nodiscard]] bool operator==(const ConstructibleInteger& x) const;
    [[nodiscard]] bool operator!=(const ConstructibleInteger& x) const;
    [[nodiscard]] bool operator<(const ConstructibleInteger& x) const;
    [[nodiscard]] bool operator>(const ConstructibleInteger& x) const;
    [[nodiscard]] int hash() const;
};

int ConstructibleInteger::lastConstruct = 0;
int ConstructibleInteger::lastDestruct = 0;

ConstructibleInteger::ConstructibleInteger(int x) : value(x){
    ConstructibleInteger::lastConstruct = x;
}

ConstructibleInteger::ConstructibleInteger(const ConstructibleInteger& x) : value(x.value) {
    ConstructibleInteger::lastConstruct = value;
}

ConstructibleInteger& ConstructibleInteger::operator=(const ConstructibleInteger& x){
    if(value != -1000){ConstructibleInteger::lastDestruct = value;}
    value = x.value;
    ConstructibleInteger::lastConstruct = value;
    return (*this);
}

ConstructibleInteger::ConstructibleInteger(ConstructibleInteger&& x) noexcept : value(x.value) {
    x.value = -1000;
}

ConstructibleInteger& ConstructibleInteger::operator=(ConstructibleInteger&& x) noexcept {
    if(value != -1000){ConstructibleInteger::lastDestruct = value;}
    value = x.value;
    x.value = -1000;
    return (*this);
}

ConstructibleInteger::~ConstructibleInteger(){
    if(value != -1000){ConstructibleInteger::lastDestruct = value;}
}

ConstructibleInteger::operator int() const {
    return value;
}

bool ConstructibleInteger::operator==(const ConstructibleInteger& x) const {
    return (value == x.value);
}

bool ConstructibleInteger::operator!=(const ConstructibleInteger& x) const {
    return (value != x.value);
}

bool ConstructibleInteger::operator<(const ConstructibleInteger& x) const {
    return (value < x.value);
}

bool ConstructibleInteger::operator>(const ConstructibleInteger& x) const {
    return (value > x.value);
}

int ConstructibleInteger::hash() const {
    return SGEXTN::Containers::Hash<int>()(value);
}
}

void SGEXTN::InternalTest::ContainersTest::testEqualTo(){
    const SGEXTN::Containers::EqualTo<int> comparator;
    if(comparator(0, 0) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::EqualTo - 0 not equal to 0");}
    if(comparator(-1, 0) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::EqualTo - -1 equal to 0");}
    if(comparator(1, 0) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::EqualTo - 1 equal to 0");}
}

void SGEXTN::InternalTest::ContainersTest::testArray(){
    SGEXTN::Containers::Array<int> arr(1, 2, 3, 4, 5);
    if(arr.at(0) != 1 || arr.at(1) != 2 || arr.at(2) != 3 || arr.at(3) != 4 || arr.at(4) != 5 || arr.length() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array - init list fail");}
    arr = SGEXTN::Containers::Array<int>(2, 26);
    if(arr.at(0) != 26 || arr.at(1) != 26 || arr.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array - move assign fail");}
    SGEXTN::Containers::Array<int> arr0(3);
    arr0.at(0) = 726;
    if(arr0.at(0) != 726){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array - assign to element fail");}
    arr0 = arr;
    if(arr0.at(1) != 26 || arr0.at(0) != 26){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array - copy assign fail");}
    if(arr0.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array - get length info fail");}
    arr0.fill(-1);
    if(arr0.at(0) != -1 || arr0.at(1) != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array - fill with default value fail");}
    arr = SGEXTN::Containers::Array<int>(1000);
    for(int i=0; i<1000; i++){
        arr.at(i) = 1000 - i;
    }
    arr.sort<SGEXTN::Containers::LessThan<int>>(0, arr.length());
    for(int i=0; i<1000; i++){
        if(arr.at(i) != i + 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Array - sort array failed");}
    }
}

void SGEXTN::InternalTest::ContainersTest::testSpan(){
    SGEXTN::Containers::Array<int> arr(1, 2, 3, 4, 5);
    SGEXTN::Containers::Span<int> span(arr.private_data, 5);
    if(span.at(0) != 1 || span.at(1) != 2 || span.at(2) != 3 || span.at(3) != 4 || span.at(4) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - bind to data fail");}
    if(span.length() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - retrieving length fail");}
    arr.at(3) = 26;
    if(span.at(3) != 26){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - reflect underlying data changes fail");}
    span.at(2) = -1;
    if(arr.at(2) != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - propagate underlying data changes fail");}
    SGEXTN::Containers::Span<int> subspanCenter = span.subspan(1, 3);
    if(subspanCenter.at(0) != 2 || subspanCenter.at(1) != -1 || subspanCenter.at(2) != 26 || subspanCenter.length() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - subspan center fail");}
    SGEXTN::Containers::Span<int> subspanLeft = span.subspanLeft(2);
    if(subspanLeft.at(0) != 1 || subspanLeft.at(1) != 2 || subspanLeft.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - subspan left fail");}
    SGEXTN::Containers::Span<int> subspanRight = span.subspanRight(2);
    if(subspanRight.at(0) != 26 || subspanRight.at(1) != 5 || subspanRight.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - subspan right fail");}
    arr = SGEXTN::Containers::Array<int>(1000);
    for(int i=0; i<1000; i++){
        arr.at(i) = i + 1;
    }
    span = SGEXTN::Containers::Span<int>(arr.private_data, 1000);
    span.sort<SGEXTN::Containers::MoreThan<int>>(0, span.length());
    for(int i=0; i<1000; i++){
        if(arr.at(i) != 1000 - i){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Span - sort array failed");}
    }
}

void SGEXTN::InternalTest::ContainersTest::testLessThan(){
    const SGEXTN::Containers::LessThan<int> comparator;
    if(comparator(-1, 0) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::LessThan - -1 not less than 0");}
    if(comparator(0, 0) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::LessThan - 0 less than 0");}
    if(comparator(1, 0) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::LessThan - 1 less than 0");}
    const SGEXTN::Containers::LessThan<const int*> pointerComparator;
    const int i = 0;
    const int j = 0;
    if(pointerComparator(&i, &j) == false && pointerComparator(&j, &i) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::LessThan - different pointer point to same result");}
    if(pointerComparator(&i, &i) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::LessThan - same pointer point to different result");}
}

void SGEXTN::InternalTest::ContainersTest::testMoreThan(){
    const SGEXTN::Containers::MoreThan<int> comparator;
    if(comparator(-1, 0) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MoreThan - -1 more than 0");}
    if(comparator(0, 0) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MoreThan - 0 more than 0");}
    if(comparator(1, 0) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MoreThan - 1 not more than 0");}
    const SGEXTN::Containers::MoreThan<const int*> pointerComparator;
    const int i = 0;
    const int j = 0;
    if(pointerComparator(&i, &j) == false && pointerComparator(&j, &i) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MoreThan - different pointer point to same result");}
    if(pointerComparator(&i, &i) == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MoreThan - same pointer point to different result");}
}

void SGEXTN::InternalTest::ContainersTest::testVector(){
    SGEXTN::Containers::Vector<int> v;
    v.pushBack(0);
    if(v.length() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - length check fail");}
    if(v.at(0) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - push back fail");}
    v.pushBack(2);
    v.pushBack(3);
    if(v.length() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - length update fail");}
    v.clear();
    if(v.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - clear vector fail");}
    v.pushBack(0);
    v.pushBack(2);
    v.pushBack(3);
    v.popBack();
    if(v.length() != 2 || v.at(1) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - pop back fail");}
    v.fill(26);
    if(v.at(0) != 26 || v.at(1) != 26 || v.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - fill fail");}
    v = SGEXTN::Containers::Vector(5, 0);
    if(v.at(0) != 0 || v.at(1) != 0 || v.at(2) != 0 || v.at(3) != 0 || v.at(4) != 0 || v.length() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - construct fail");}
}

void SGEXTN::InternalTest::ContainersTest::testQueue(){
    SGEXTN::Containers::Queue<int> queue;
    queue.push(1);
    queue.push(2);
    if(queue.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - length check fail");}
    queue.clear();
    if(queue.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - clear queue fail");}
    queue.push(1);
    queue.push(2);
    if(queue.front() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - front element check fail");}
    if(queue.back() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - back element check fail");}
    queue.pop();
    if(queue.length() != 1 || queue.front() != 2 || queue.back() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - pop fail");}
    queue.push(3);
    if(queue.length() != 2 || queue.back() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - push fail");}
}

void SGEXTN::InternalTest::ContainersTest::testStack(){
    SGEXTN::Containers::Stack<int> stack;
    stack.push(1);
    stack.push(2);
    if(stack.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - length check fail");}
    stack.clear();
    if(stack.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - clear stack fail");}
    stack.push(1);
    stack.push(2);
    if(stack.top() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - top element check fail");}
    stack.pop();
    if(stack.length() != 1 || stack.top() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - pop fail");}
    stack.push(3);
    if(stack.length() != 2 || stack.top() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - push element fail");}
}

void SGEXTN::InternalTest::ContainersTest::testDeque(){
    SGEXTN::Containers::Deque<int> dq;
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);
    if(dq.length() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - length check fail");}
    if(dq.front() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - front element check fail");}
    if(dq.back() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - back element check fail");}
    if(dq.at(0) != 1 || dq.at(1) != 2 || dq.at(2) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - index access fail");}
    dq.fill(26);
    if(dq.at(0) != 26 || dq.at(1) != 26 || dq.at(2) != 26 || dq.length() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - fill reset fail");}
    dq.pushBack(1);
    if(dq.length() != 4 || dq.back() != 1 || dq.front() != 26){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push back fail");}
    dq.popBack();
    if(dq.length() != 3 || dq.back() != 26 || dq.front() != 26){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop back fail");}
    dq.pushFront(1);
    if(dq.length() != 4 || dq.front() != 1 || dq.back() != 26){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push front fail");}
    dq.clear();
    if(dq.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - clear deque fail");}
    dq.pushBack(26);
    dq.pushBack(26);
    dq.pushBack(26);
    dq.pushFront(1);
    dq.popFront();
    if(dq.length() != 3 || dq.front() != 26 || dq.back() != 26){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop front fail");}
}

void SGEXTN::InternalTest::ContainersTest::testPriorityQueue(){
    SGEXTN::Containers::PriorityQueue<int, SGEXTN::Containers::LessThan<int>> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    if(pq.length() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - length check fail");}
    if(pq.top() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - top check fail");}
    pq.push(5);
    if(pq.length() != 4 || pq.top() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push bigger element fail");}
    pq.push(4);
    if(pq.length() != 5 || pq.top() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push in range element fail");}
    pq.pop();
    if(pq.length() != 4 || pq.top() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop fail");}
    pq.push(-1);
    if(pq.length() != 5 || pq.top() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push smaller element fail");}
    pq.pop();
    if(pq.length() != 4 || pq.top() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop fail 2");}
    pq.pop();
    if(pq.length() != 3 || pq.top() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop fail 3");}
    pq.clear();
    if(pq.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - clear priority queue fail");}
    pq.push(1);
    pq.push(-1);
    pq.push(2);
    pq.pop();
    if(pq.length() != 2 || pq.top() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop fail 4");}
    pq.pop();
    if(pq.length() != 1 || pq.top() != -1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop fail 5");}
    pq.pop();
    if(pq.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop fail 6");}
}

void SGEXTN::InternalTest::ContainersTest::testSet(){
    SGEXTN::Containers::Set<int, SGEXTN::Containers::LessThan<int>> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    bool x = s.insert(6);
    if(s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - insert fail");}
    s.clear();
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - clear fail");}
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    x = s.insert(5);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - duplicate insert fail");}
    if(s.length() != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - length check fail");}
    x = s.erase(7);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase nonexistent fail");}
    x = s.erase(2);
    if(s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase fail");}
    if(s.contains(1) == false || s.contains(2) == true || s.contains(3) == false || s.contains(4) == false || s.contains(5) == false || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - contains check fail");}
    if((*s.begin()) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - begin iterator fail");}
    if((*(++s.end())) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - end iterator fail");}
    SGEXTN::Containers::SetIterator<int, SGEXTN::Containers::LessThan<int>> itr = s.find(1);
    if(itr != s.begin()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - find fail");}
    x = s.erase(itr);
    if(s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase iterator fail");}
    if((*s.lowerBound(4)) != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - lower bound fail");}
    if((*s.upperBound(4)) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - upper bound fail");}
    if(s.indexOf(5) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - index of element fail");}
    if(s.indexOf(s.find(5)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - index of iterator fail");}
    if(s.elementAt(3) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - element at fail");}
    if(s.iteratorAt(1) != s.find(4)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - iterator at fail");}
    for(SGEXTN::Containers::SetIterator<int, SGEXTN::Containers::LessThan<int>> i = s.begin(); i != s.end(); i++){
        s.erase(i);
    }
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - in order traversal erase fail");}
}

void SGEXTN::InternalTest::ContainersTest::testMultiSet(){
    SGEXTN::Containers::MultiSet<int, SGEXTN::Containers::LessThan<int>> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    if(s.length() != 6 || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - insert fail");}
    s.clear();
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - clear fail");}
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(5);
    if(s.length() != 7 || s.contains(5) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - duplicate insert fail");}
    if(s.length() != 7){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - length check fail");}
    bool x = s.erase(7);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase nonexistent fail");}
    x = s.erase(2);
    if(s.length() != 6 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase fail");}
    if(s.contains(1) == false || s.contains(2) == true || s.contains(3) == false || s.contains(4) == false || s.contains(5) == false || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - contains check fail");}
    if(s.count(1) != 1 || s.count(5) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - count check fail");}
    if((*s.begin()) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - begin iterator fail");}
    if((*(++s.end())) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - end iterator fail");}
    SGEXTN::Containers::MultiSetIterator<int, SGEXTN::Containers::LessThan<int>> itr = s.find(1);
    if(itr != s.begin()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - find fail");}
    x = s.erase(itr);
    if(s.length() != 5 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase iterator fail");}
    if((*s.lowerBound(4)) != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - lower bound fail");}
    if((*s.upperBound(4)) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - upper bound fail");}
    if(s.indexOf(5) != 2 && s.indexOf(5) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - index of element fail");}
    if(s.indexOf(s.find(5)) != 2 && s.indexOf(s.find(5)) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - index of iterator fail");}
    if(s.elementAt(4) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - element at fail");}
    if(s.iteratorAt(1) != s.find(4)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - iterator at fail");}
    for(SGEXTN::Containers::MultiSetIterator<int, SGEXTN::Containers::LessThan<int>> i = s.begin(); i != s.end(); i++){
        s.erase(i);
    }
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - in order traversal erase fail");}
}

void SGEXTN::InternalTest::ContainersTest::testMap(){
    SGEXTN::Containers::Map<int, int, SGEXTN::Containers::LessThan<int>> s;
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    bool x = s.insert(6, 6);
    if(s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - insert fail");}
    s.clear();
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - clear fail");}
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    s.insert(6, 6);
    x = s.insert(5, 0);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - duplicate insert fail");}
    if(s.length() != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - length check fail");}
    x = s.erase(7);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase nonexistent fail");}
    x = s.erase(2);
    if(s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase fail");}
    if(s.contains(1) == false || s.contains(2) == true || s.contains(3) == false || s.contains(4) == false || s.contains(5) == false || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - contains check fail");}
    s.at(3) = 0;
    if(s.at(1) != 1 || s.at(3) != 0 || s.at(4) != 4 || s.at(5) != 5 || s.at(6) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - at key fail");}
    if(s.begin().key() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - begin iterator fail");}
    if((++s.end()).value() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - end iterator fail");}
    SGEXTN::Containers::MapIterator<int, int, SGEXTN::Containers::LessThan<int>> itr = s.find(1);
    if(itr != s.begin()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - find fail");}
    x = s.erase(itr);
    if(s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase iterator fail");}
    if(s.lowerBound(4).key() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - lower bound fail");}
    if(s.upperBound(4).value() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - upper bound fail");}
    if(s.indexOf(5) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - index of element fail");}
    if(s.indexOf(s.find(5)) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - index of iterator fail");}
    if(s.keyAt(3) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - key at fail");}
    if(s.valueAt(3) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - value at fail");}
    if(s.iteratorAt(1) != s.find(4)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - iterator at fail");}
    for(SGEXTN::Containers::MapIterator<int, int, SGEXTN::Containers::LessThan<int>> i = s.begin(); i != s.end(); i++){
        s.erase(i);
    }
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - in order traversal erase fail");}
}

void SGEXTN::InternalTest::ContainersTest::testMultiMap(){
    SGEXTN::Containers::MultiMap<int, int, SGEXTN::Containers::LessThan<int>> s;
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    s.insert(6, 6);
    if(s.length() != 6 || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - insert fail");}
    s.clear();
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - clear fail");}
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    s.insert(6, 6);
    s.insert(5, 0);
    if(s.length() != 7 || s.contains(5) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - duplicate insert fail");}
    if(s.length() != 7){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - length check fail");}
    bool x = s.erase(7);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase nonexistent fail");}
    x = s.erase(2);
    if(s.length() != 6 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase fail");}
    if(s.contains(1) == false || s.contains(2) == true || s.contains(3) == false || s.contains(4) == false || s.contains(5) == false || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - contains check fail");}
    if(s.count(1) != 1 || s.count(3) != 1 || s.count(5) != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - count check fail");}
    s.at(3) = 0;
    if(s.at(1) != 1 || s.at(3) != 0 || s.at(4) != 4 || s.at(6) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - at key fail");}
    if(s.begin().key() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - begin iterator fail");}
    if((++s.end()).value() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - end iterator fail");}
    SGEXTN::Containers::MultiMapIterator<int, int, SGEXTN::Containers::LessThan<int>> itr = s.find(1);
    if(itr != s.begin()){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - find fail");}
    x = s.erase(itr);
    if(s.length() != 5 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase iterator fail");}
    if(s.lowerBound(4).key() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - lower bound fail");}
    if(s.upperBound(4).value() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - upper bound fail");}
    if(s.indexOf(5) != 2 && s.indexOf(5) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - index of element fail");}
    if(s.indexOf(s.find(5)) != 2 && s.indexOf(s.find(5)) != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - index of iterator fail");}
    if(s.keyAt(3) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - key at fail");}
    if(s.valueAt(3) != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - value at fail");}
    if(s.iteratorAt(1) != s.find(4)){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - iterator at fail");}
    for(SGEXTN::Containers::MultiMapIterator<int, int, SGEXTN::Containers::LessThan<int>> i = s.begin(); i != s.end(); i++){
        s.erase(i);
    }
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - in order traversal erase fail");}
}

void SGEXTN::InternalTest::ContainersTest::testUnorderedSet(){
    SGEXTN::Containers::UnorderedSet<int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    bool x = s.insert(6);
    if(s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - insert fail");}
    s.clear();
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - clear fail");}
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    x = s.insert(5);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - duplicate insert fail");}
    if(s.length() != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - length check fail");}
    x = s.erase(7);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase nonexistent fail");}
    x = s.erase(2);
    if(s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase fail");}
    if(s.contains(1) == false || s.contains(2) == true || s.contains(3) == false || s.contains(4) == false || s.contains(5) == false || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - contains check fail");}
    SGEXTN::Containers::UnorderedSetIterator<int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> itr = s.find(1);
    if((*itr) != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - find fail");}
    x = s.erase(itr);
    if(s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase iterator fail");}
    for(SGEXTN::Containers::UnorderedSetIterator<int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> i = s.begin(); i != s.end(); i++){
        s.erase(i);
    }
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - in order traversal erase fail");}
}

void SGEXTN::InternalTest::ContainersTest::testUnorderedMap(){
    SGEXTN::Containers::UnorderedMap<int, int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> s;
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    bool x = s.insert(6, 6);
    if(s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - insert fail");}
    s.clear();
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - clear fail");}
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    s.insert(6, 6);
    x = s.insert(5, 0);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - duplicate insert fail");}
    if(s.length() != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - length check fail");}
    x = s.erase(7);
    if(x == true){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase nonexistent fail");}
    x = s.erase(2);
    if(s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase fail");}
    if(s.contains(1) == false || s.contains(2) == true || s.contains(3) == false || s.contains(4) == false || s.contains(5) == false || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - contains check fail");}
    s.at(3) = 0;
    if(s.at(1) != 1 || s.at(3) != 0 || s.at(4) != 4 || s.at(5) != 5 || s.at(6) != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - at key fail");}
    SGEXTN::Containers::UnorderedMapIterator<int, int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> itr = s.find(1);
    if(itr.key() != 1 || itr.value() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - find fail");}
    x = s.erase(itr);
    if(s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase iterator fail");}
    for(SGEXTN::Containers::UnorderedMapIterator<int, int, SGEXTN::Containers::EqualTo<int>, SGEXTN::Containers::Hash<int>> i = s.begin(); i != s.end(); i++){
        s.erase(i);
    }
    if(s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - in order traversal erase fail");}
}

void SGEXTN::InternalTest::ContainersTest::testVectorConstructible(){
    SGEXTN::Containers::Vector<ConstructibleInteger> v;
    ConstructibleInteger::lastConstruct = 0;
    v.pushBack(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - push back 1 construct fail");}
    v.pushBack(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - push back 2 construct fail");}
    v.pushBack(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - push back 3 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    v.clear();
    if(ConstructibleInteger::lastDestruct == 0 || v.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - clear vector destruct fail");}
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    ConstructibleInteger::lastDestruct = 0;
    v.popBack();
    if(ConstructibleInteger::lastDestruct != 3 || v.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - pop back destruct 3 fail");}
    v.popBack();
    if(ConstructibleInteger::lastDestruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - pop back destruct 2 fail");}
    v.popBack();
    if(ConstructibleInteger::lastDestruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - pop back destruct 1 fail");}
}

void SGEXTN::InternalTest::ContainersTest::testQueueConstructible(){
    SGEXTN::Containers::Queue<ConstructibleInteger> v;
    ConstructibleInteger::lastConstruct = 0;
    v.push(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - push 1 construct fail");}
    v.push(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - push 2 construct fail");}
    v.push(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - push 3 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    v.clear();
    if(ConstructibleInteger::lastDestruct == 0 || v.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - clear queue destruct fail");}
    v.push(1);
    v.push(2);
    v.push(3);
    ConstructibleInteger::lastDestruct = 0;
    v.pop();
    if(ConstructibleInteger::lastDestruct != 1 || v.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - pop destruct 1 fail");}
    v.pop();
    if(ConstructibleInteger::lastDestruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - pop destruct 2 fail");}
    v.pop();
    if(ConstructibleInteger::lastDestruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Queue - pop destruct 3 fail");}
}

void SGEXTN::InternalTest::ContainersTest::testStackConstructible(){
    SGEXTN::Containers::Stack<ConstructibleInteger> v;
    ConstructibleInteger::lastConstruct = 0;
    v.push(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - push 1 construct fail");}
    v.push(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - push 2 construct fail");}
    v.push(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - push 3 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    v.clear();
    if(ConstructibleInteger::lastDestruct == 0 || v.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - clear stack destruct fail");}
    v.push(1);
    v.push(2);
    v.push(3);
    ConstructibleInteger::lastDestruct = 0;
    v.pop();
    if(ConstructibleInteger::lastDestruct != 3 || v.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - pop destruct 3 fail");}
    v.pop();
    if(ConstructibleInteger::lastDestruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - pop destruct 2 fail");}
    v.pop();
    if(ConstructibleInteger::lastDestruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Stack - pop destruct 1 fail");}
}

void SGEXTN::InternalTest::ContainersTest::testDequeConstructible(){
    SGEXTN::Containers::Deque<ConstructibleInteger> v;
    ConstructibleInteger::lastConstruct = 0;
    v.pushBack(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push back 1 construct fail");}
    v.pushBack(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push back 2 construct fail");}
    v.pushBack(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push back 3 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    v.clear();
    if(ConstructibleInteger::lastDestruct == 0 || v.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - clear deque destruct fail");}
    v.pushBack(1);
    v.pushBack(2);
    v.pushBack(3);
    ConstructibleInteger::lastConstruct = 0;
    v.pushFront(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push front 1 construct fail");}
    v.pushFront(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push front 2 construct fail");}
    v.pushFront(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - push front 3 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    v.popFront();
    if(ConstructibleInteger::lastDestruct != 3 || v.length() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop front destruct 3 fail");}
    v.popFront();
    if(ConstructibleInteger::lastDestruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop front destruct 2 fail");}
    v.popFront();
    if(ConstructibleInteger::lastDestruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop front destruct 1 fail");}
    ConstructibleInteger::lastDestruct = 0;
    v.popBack();
    if(ConstructibleInteger::lastDestruct != 3 || v.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop back destruct 3 fail");}
    v.popBack();
    if(ConstructibleInteger::lastDestruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop back destruct 2 fail");}
    v.popBack();
    if(ConstructibleInteger::lastDestruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Deque - pop back destruct 1 fail");}
}

void SGEXTN::InternalTest::ContainersTest::testPriorityQueueConstructible(){
    SGEXTN::Containers::PriorityQueue<ConstructibleInteger, SGEXTN::Containers::LessThan<ConstructibleInteger>> pq;
    ConstructibleInteger::lastConstruct = 0;
    pq.push(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push construct 1 fail");}
    pq.push(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push construct 2 fail");}
    pq.push(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push construct 3 fail");}
    pq.push(5);
    if(ConstructibleInteger::lastConstruct != 5 || pq.length() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push bigger element construct fail");}
    pq.push(4);
    if(ConstructibleInteger::lastConstruct != 4 || pq.length() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push in range element construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    pq.pop();
    if(ConstructibleInteger::lastDestruct != 5 || pq.length() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop destruct 5 fail");}
    ConstructibleInteger::lastConstruct = 0;
    pq.push(-1);
    if(ConstructibleInteger::lastConstruct != -1 || pq.length() != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - push smaller element construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    pq.pop();
    if(ConstructibleInteger::lastDestruct != 4 || pq.length() != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop destruct 4 fail");}
    pq.pop();
    if(ConstructibleInteger::lastDestruct != 3 || pq.length() != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop destruct 3 fail");}
    ConstructibleInteger::lastDestruct = 0;
    pq.clear();
    if(ConstructibleInteger::lastDestruct == 0 || pq.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - clear priority queue destruct fail");}
    pq.push(1);
    pq.push(-1);
    pq.push(2);
    ConstructibleInteger::lastDestruct = 0;
    pq.pop();
    if(ConstructibleInteger::lastDestruct != 2 || pq.length() != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop destruct 2 fail");}
    pq.pop();
    if(ConstructibleInteger::lastDestruct != 1 || pq.length() != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop destruct 1 fail");}
    pq.pop();
    if(ConstructibleInteger::lastDestruct != -1 || pq.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::PriorityQueue - pop destruct -1 fail");}
}

void SGEXTN::InternalTest::ContainersTest::testSetConstructible(){
    SGEXTN::Containers::Set<ConstructibleInteger, SGEXTN::Containers::LessThan<ConstructibleInteger>> s;
    ConstructibleInteger::lastConstruct = 0;
    s.insert(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - insert 1 construct fail");}
    s.insert(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - insert 2 construct fail");}
    s.insert(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - insert 3 construct fail");}
    s.insert(4);
    if(ConstructibleInteger::lastConstruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - insert 4 construct fail");}
    s.insert(5);
    if(ConstructibleInteger::lastConstruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - insert 5 construct fail");}
    bool x = s.insert(6);
    if(s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - insert 6 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    s.clear();
    if(ConstructibleInteger::lastDestruct == 0 || s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - clear destruct fail");}
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(2);
    if(ConstructibleInteger::lastDestruct != 2 || s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase destruct fail");}
    SGEXTN::Containers::SetIterator<ConstructibleInteger, SGEXTN::Containers::LessThan<ConstructibleInteger>> itr = s.find(1);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(itr);
    if(ConstructibleInteger::lastDestruct != 1 || s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase iterator destruct fail");}
    s.erase(3);
    if(ConstructibleInteger::lastDestruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase 3 destruct fail");}
    s.erase(4);
    if(ConstructibleInteger::lastDestruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase 4 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase 5 destruct fail");}
    s.erase(6);
    if(ConstructibleInteger::lastDestruct != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Set - erase 6 destruct fail");}
}

void SGEXTN::InternalTest::ContainersTest::testMapConstructible(){
    SGEXTN::Containers::Map<ConstructibleInteger, int, SGEXTN::Containers::LessThan<ConstructibleInteger>> s;
    ConstructibleInteger::lastConstruct = 0;
    s.insert(1, 1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - insert 1 construct fail");}
    s.insert(2, 2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - insert 2 construct fail");}
    s.insert(3, 3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - insert 3 construct fail");}
    s.insert(4, 4);
    if(ConstructibleInteger::lastConstruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - insert 4 construct fail");}
    s.insert(5, 5);
    if(ConstructibleInteger::lastConstruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - insert 5 construct fail");}
    bool x = s.insert(6, 6);
    if(ConstructibleInteger::lastConstruct != 6 || s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - insert 6 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    s.clear();
    if(ConstructibleInteger::lastDestruct == 0 || s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - clear destruct fail");}
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    s.insert(6, 6);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(2);
    if(ConstructibleInteger::lastDestruct != 2 || s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase destruct fail");}
    SGEXTN::Containers::MapIterator<ConstructibleInteger, int, SGEXTN::Containers::LessThan<ConstructibleInteger>> itr = s.find(1);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(itr);
    if(ConstructibleInteger::lastDestruct != 1 || s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase iterator destruct fail");}
    s.erase(3);
    if(ConstructibleInteger::lastDestruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase 3 destruct fail");}
    s.erase(4);
    if(ConstructibleInteger::lastDestruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase 4 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase 5 destruct fail");}
    s.erase(6);
    if(ConstructibleInteger::lastDestruct != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Map - erase 6 destruct fail");}
}

void SGEXTN::InternalTest::ContainersTest::testMultiSetConstructible(){
    SGEXTN::Containers::MultiSet<ConstructibleInteger, SGEXTN::Containers::LessThan<ConstructibleInteger>> s;
    ConstructibleInteger::lastConstruct = 0;
    s.insert(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - insert 1 construct fail");}
    s.insert(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - insert 2 construct fail");}
    s.insert(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - insert 3 construct fail");}
    s.insert(4);
    if(ConstructibleInteger::lastConstruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - insert 4 construct fail");}
    s.insert(5);
    if(ConstructibleInteger::lastConstruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - insert 5 construct fail");}
    s.insert(6);
    if(ConstructibleInteger::lastConstruct != 6 || s.length() != 6 || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - insert 6 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    s.clear();
    if(ConstructibleInteger::lastDestruct == 0 || s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - clear destruct fail");}
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    s.insert(5);
    if(ConstructibleInteger::lastConstruct != 5 || s.length() != 7 || s.contains(5) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - duplicate insert construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    bool x = s.erase(2);
    if(ConstructibleInteger::lastDestruct != 2 || s.length() != 6 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase destruct fail");}
    SGEXTN::Containers::MultiSetIterator<ConstructibleInteger, SGEXTN::Containers::LessThan<ConstructibleInteger>> itr = s.find(1);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(itr);
    if(ConstructibleInteger::lastDestruct != 1 || s.length() != 5 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase iterator destruct fail");}
    s.erase(3);
    if(ConstructibleInteger::lastDestruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase 3 destruct fail");}
    s.erase(4);
    if(ConstructibleInteger::lastDestruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase 4 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase 5 destruct fail");}
    s.erase(6);
    if(ConstructibleInteger::lastDestruct != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase 6 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiSet - erase 5 destruct fail");}
}

void SGEXTN::InternalTest::ContainersTest::testMultiMapConstructible(){
    SGEXTN::Containers::MultiMap<ConstructibleInteger, int, SGEXTN::Containers::LessThan<ConstructibleInteger>> s;
    ConstructibleInteger::lastConstruct = 0;
    s.insert(1, 1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - insert 1 construct fail");}
    s.insert(2, 2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - insert 2 construct fail");}
    s.insert(3, 3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - insert 3 construct fail");}
    s.insert(4, 4);
    if(ConstructibleInteger::lastConstruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - insert 4 construct fail");}
    s.insert(5, 5);
    if(ConstructibleInteger::lastConstruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - insert 5 construct fail");}
    s.insert(6, 6);
    if(ConstructibleInteger::lastConstruct != 6 || s.length() != 6 || s.contains(6) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - insert 6 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    s.clear();
    if(ConstructibleInteger::lastDestruct == 0 || s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - clear destruct fail");}
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    s.insert(6, 6);
    s.insert(5, 0);
    if(ConstructibleInteger::lastConstruct != 5 || s.length() != 7 || s.contains(5) == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - duplicate insert construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    bool x = s.erase(2);
    if(ConstructibleInteger::lastDestruct != 2 || s.length() != 6 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase destruct fail");}
    SGEXTN::Containers::MultiMapIterator<ConstructibleInteger, int, SGEXTN::Containers::LessThan<ConstructibleInteger>> itr = s.find(1);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(itr);
    if(ConstructibleInteger::lastDestruct != 1 || s.length() != 5 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase iterator destruct fail");}
    s.erase(3);
    if(ConstructibleInteger::lastDestruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase 3 destruct fail");}
    s.erase(4);
    if(ConstructibleInteger::lastDestruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase 4 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase 5 destruct fail");}
    s.erase(6);
    if(ConstructibleInteger::lastDestruct != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase 6 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::MultiMap - erase 5 destruct fail");}
}

void SGEXTN::InternalTest::ContainersTest::testUnorderedSetConstructible(){
    SGEXTN::Containers::UnorderedSet<ConstructibleInteger, SGEXTN::Containers::EqualTo<ConstructibleInteger>, SGEXTN::Containers::Hash<ConstructibleInteger>> s;
    ConstructibleInteger::lastConstruct = 0;
    s.insert(1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - insert 1 construct fail");}
    s.insert(2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - insert 2 construct fail");}
    s.insert(3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - insert 3 construct fail");}
    s.insert(4);
    if(ConstructibleInteger::lastConstruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - insert 4 construct fail");}
    s.insert(5);
    if(ConstructibleInteger::lastConstruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - insert 5 construct fail");}
    bool x = s.insert(6);
    if(ConstructibleInteger::lastConstruct != 6 || s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - insert 6 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    s.clear();
    if(ConstructibleInteger::lastDestruct == 0 || s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - clear destruct fail");}
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    s.insert(6);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(2);
    if(ConstructibleInteger::lastDestruct != 2 || s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase destruct fail");}
    SGEXTN::Containers::UnorderedSetIterator<ConstructibleInteger, SGEXTN::Containers::EqualTo<ConstructibleInteger>, SGEXTN::Containers::Hash<ConstructibleInteger>> itr = s.find(1);
    x = s.erase(itr);
    if(ConstructibleInteger::lastDestruct != 1 || s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase iterator destruct fail");}
    s.erase(3);
    if(ConstructibleInteger::lastDestruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase 3 destruct fail");}
    s.erase(4);
    if(ConstructibleInteger::lastDestruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase 4 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase 5 destruct fail");}
    s.erase(6);
    if(ConstructibleInteger::lastDestruct != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedSet - erase 6 destruct fail");}
}

void SGEXTN::InternalTest::ContainersTest::testUnorderedMapConstructible(){
    SGEXTN::Containers::UnorderedMap<ConstructibleInteger, ConstructibleInteger, SGEXTN::Containers::EqualTo<ConstructibleInteger>, SGEXTN::Containers::Hash<ConstructibleInteger>> s;
    ConstructibleInteger::lastConstruct = 0;
    s.insert(1, 1);
    if(ConstructibleInteger::lastConstruct != 1){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - insert 1 construct fail");}
    s.insert(2, 2);
    if(ConstructibleInteger::lastConstruct != 2){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - insert 2 construct fail");}
    s.insert(3, 3);
    if(ConstructibleInteger::lastConstruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - insert 3 construct fail");}
    s.insert(4, 4);
    if(ConstructibleInteger::lastConstruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - insert 4 construct fail");}
    s.insert(5, 5);
    if(ConstructibleInteger::lastConstruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - insert 5 construct fail");}
    bool x = s.insert(6, 6);
    if(ConstructibleInteger::lastConstruct != 6 || s.length() != 6 || s.contains(6) == false || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - insert 6 construct fail");}
    ConstructibleInteger::lastDestruct = 0;
    s.clear();
    if(ConstructibleInteger::lastDestruct == 0 || s.length() != 0){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - clear destruct fail");}
    s.insert(1, 1);
    s.insert(2, 2);
    s.insert(3, 3);
    s.insert(4, 4);
    s.insert(5, 5);
    s.insert(6, 6);
    ConstructibleInteger::lastDestruct = 0;
    x = s.erase(2);
    if(ConstructibleInteger::lastDestruct != 2 || s.length() != 5 || s.contains(2) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase destruct fail");}
    SGEXTN::Containers::UnorderedMapIterator<ConstructibleInteger, ConstructibleInteger, SGEXTN::Containers::EqualTo<ConstructibleInteger>, SGEXTN::Containers::Hash<ConstructibleInteger>> itr = s.find(1);
    x = s.erase(itr);
    if(ConstructibleInteger::lastDestruct != 1 || s.length() != 4 || s.contains(1) == true || x == false){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase iterator destruct fail");}
    s.erase(3);
    if(ConstructibleInteger::lastDestruct != 3){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase 3 destruct fail");}
    s.erase(4);
    if(ConstructibleInteger::lastDestruct != 4){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase 4 destruct fail");}
    s.erase(5);
    if(ConstructibleInteger::lastDestruct != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase 5 destruct fail");}
    s.erase(6);
    if(ConstructibleInteger::lastDestruct != 6){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::UnorderedMap - erase 6 destruct fail");}
}

void SGEXTN::InternalTest::ContainersTest::testArrayVectorMove(){
    SGEXTN::Containers::Array<int> arr = SGEXTN::Containers::Array<int>(1, 2, 3, 4, 5);
    SGEXTN::Containers::Vector<int> v = SGEXTN::Containers::ArrayVectorMove<int>::convertToVectorAndDestroyArray(arr);
    if(arr.length() != 0 || v.length() != 5 || v.at(0) != 1 || v.at(1) != 2 || v.at(2) != 3 || v.at(3) != 4 || v.at(4) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - convert array to vector fail");}
    arr = SGEXTN::Containers::ArrayVectorMove<int>::convertToArrayAndDestroyVector(v);
    if(v.length() != 0 || arr.length() != 5 || arr.at(0) != 1 || arr.at(1) != 2 || arr.at(2) != 3 || arr.at(3) != 4 || arr.at(4) != 5){SGEXTN_IMMEDIATE_CRASH("SGEXTN::Containers::Vector - convert vector to array fail");}
}

void SGEXTN::InternalTest::ContainersTest::testAll(){
    SGEXTN::InternalTest::ContainersTest::testEqualTo();
    SGEXTN::InternalTest::ContainersTest::testArray();
    SGEXTN::InternalTest::ContainersTest::testSpan();
    SGEXTN::InternalTest::ContainersTest::testLessThan();
    SGEXTN::InternalTest::ContainersTest::testMoreThan();
    SGEXTN::InternalTest::ContainersTest::testVector();
    SGEXTN::InternalTest::ContainersTest::testQueue();
    SGEXTN::InternalTest::ContainersTest::testStack();
    SGEXTN::InternalTest::ContainersTest::testDeque();
    SGEXTN::InternalTest::ContainersTest::testPriorityQueue();
    SGEXTN::InternalTest::ContainersTest::testSet();
    SGEXTN::InternalTest::ContainersTest::testMultiSet();
    SGEXTN::InternalTest::ContainersTest::testMap();
    SGEXTN::InternalTest::ContainersTest::testMultiMap();
    SGEXTN::InternalTest::ContainersTest::testUnorderedSet();
    SGEXTN::InternalTest::ContainersTest::testUnorderedMap();
    SGEXTN::InternalTest::ContainersTest::testVectorConstructible();
    SGEXTN::InternalTest::ContainersTest::testQueueConstructible();
    SGEXTN::InternalTest::ContainersTest::testStackConstructible();
    SGEXTN::InternalTest::ContainersTest::testDequeConstructible();
    SGEXTN::InternalTest::ContainersTest::testPriorityQueueConstructible();
    SGEXTN::InternalTest::ContainersTest::testSetConstructible();
    SGEXTN::InternalTest::ContainersTest::testMultiSetConstructible();
    SGEXTN::InternalTest::ContainersTest::testMapConstructible();
    SGEXTN::InternalTest::ContainersTest::testMultiMapConstructible();
    SGEXTN::InternalTest::ContainersTest::testUnorderedSetConstructible();
    SGEXTN::InternalTest::ContainersTest::testUnorderedMapConstructible();
    SGEXTN::InternalTest::ContainersTest::testArrayVectorMove();
}

class RegularStruct {
public:
    int x;
    RegularStruct(int x) : x(x) {}
};

class RegularStructLessThan {
public:
    bool operator()(const RegularStruct& a, const RegularStruct& b) const {return (a.x < b.x);}
};

class RegularStructEqualTo {
public:
    bool operator()(const RegularStruct& a, const RegularStruct& b) const {return (a.x == b.x);}
};

class RegularStructHashFunction {
public:
    int operator()(const RegularStruct& x) const {return x.x;}
};

class DefaultConstructableStruct {
public:
    int x;
    DefaultConstructableStruct() : x(0) {}
    DefaultConstructableStruct(int x) : x(x) {}
};

class EquatableStruct {
public:
    int x;
    EquatableStruct(int x) : x(x) {}
    [[nodiscard]] bool operator==(const EquatableStruct& x) const {return ((*this).x == x.x);}
    [[nodiscard]] bool operator!=(const EquatableStruct& x) const {return ((*this).x != x.x);}
};

class HashableStruct {
public:
    int x;
    HashableStruct(int x) : x(x) {}
    [[nodiscard]] int hash() const {return x;}
};

class ComparableStruct {
public:
    int x;
    ComparableStruct(int x) : x(x) {}
    [[nodiscard]] bool operator<(const ComparableStruct& x) const {return ((*this).x < x.x);}
    [[nodiscard]] bool operator>(const ComparableStruct& x) const {return ((*this).x > x.x);}
};

template class SGEXTN::Containers::Array<DefaultConstructableStruct>;
template class SGEXTN::Containers::ArrayVectorMove<DefaultConstructableStruct>;
template class SGEXTN::Containers::Deque<RegularStruct>;
template class SGEXTN::Containers::EqualTo<EquatableStruct>;
template class SGEXTN::Containers::Hash<HashableStruct>;
template class SGEXTN::Containers::LessThan<ComparableStruct>;
template class SGEXTN::Containers::Map<RegularStruct, RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MapIterator<RegularStruct, RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MapConstIterator<RegularStruct, RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MoreThan<ComparableStruct>;
template class SGEXTN::Containers::MultiMap<RegularStruct, RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MultiMapIterator<RegularStruct, RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MultiMapConstIterator<RegularStruct, RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MultiSet<RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MultiSetIterator<RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::MultiSetConstIterator<RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::PriorityQueue<RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::Queue<RegularStruct>;
template class SGEXTN::Containers::Set<RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::SetIterator<RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::SetConstIterator<RegularStruct, RegularStructLessThan>;
template class SGEXTN::Containers::Span<RegularStruct>;
template class SGEXTN::Containers::Stack<RegularStruct>;
template class SGEXTN::Containers::UnorderedMap<RegularStruct, RegularStruct, RegularStructEqualTo, RegularStructHashFunction>;
template class SGEXTN::Containers::UnorderedMapIterator<RegularStruct, RegularStruct, RegularStructEqualTo, RegularStructHashFunction>;
template class SGEXTN::Containers::UnorderedMapConstIterator<RegularStruct, RegularStruct, RegularStructEqualTo, RegularStructHashFunction>;
template class SGEXTN::Containers::UnorderedSet<RegularStruct, RegularStructEqualTo, RegularStructHashFunction>;
template class SGEXTN::Containers::UnorderedSetIterator<RegularStruct, RegularStructEqualTo, RegularStructHashFunction>;
template class SGEXTN::Containers::UnorderedSetConstIterator<RegularStruct, RegularStructEqualTo, RegularStructHashFunction>;
template class SGEXTN::Containers::Vector<RegularStruct>;

class FunctionOwner {};

template class SGEXTN::Containers::Hash<int>;
template class SGEXTN::Containers::Hash<int*>;
template class SGEXTN::Containers::Hash<void(*)()>;
template class SGEXTN::Containers::Hash<void(*)(int)>;
template class SGEXTN::Containers::Hash<void(*)(int, int, int)>;
template class SGEXTN::Containers::Hash<int(*)()>;
template class SGEXTN::Containers::Hash<int(*)(int)>;
template class SGEXTN::Containers::Hash<int(*)(int, int, int)>;
template class SGEXTN::Containers::Hash<void(FunctionOwner::*)()>;
template class SGEXTN::Containers::Hash<void(FunctionOwner::*)(int)>;
template class SGEXTN::Containers::Hash<void(FunctionOwner::*)(int, int, int)>;
template class SGEXTN::Containers::Hash<int(FunctionOwner::*)()>;
template class SGEXTN::Containers::Hash<int(FunctionOwner::*)(int)>;
template class SGEXTN::Containers::Hash<int(FunctionOwner::*)(int, int, int)>;
template class SGEXTN::Containers::Hash<void(FunctionOwner::*)()const>;
template class SGEXTN::Containers::Hash<void(FunctionOwner::*)(int)const>;
template class SGEXTN::Containers::Hash<void(FunctionOwner::*)(int, int, int)const>;
template class SGEXTN::Containers::Hash<int(FunctionOwner::*)()const>;
template class SGEXTN::Containers::Hash<int(FunctionOwner::*)(int)const>;
template class SGEXTN::Containers::Hash<int(FunctionOwner::*)(int, int, int)const>;
template class SGEXTN::Containers::LessThan<int>;
template class SGEXTN::Containers::LessThan<int*>;
template class SGEXTN::Containers::LessThan<void(*)()>;
template class SGEXTN::Containers::LessThan<void(*)(int)>;
template class SGEXTN::Containers::LessThan<void(*)(int, int, int)>;
template class SGEXTN::Containers::LessThan<int(*)()>;
template class SGEXTN::Containers::LessThan<int(*)(int)>;
template class SGEXTN::Containers::LessThan<int(*)(int, int, int)>;
template class SGEXTN::Containers::LessThan<void(FunctionOwner::*)()>;
template class SGEXTN::Containers::LessThan<void(FunctionOwner::*)(int)>;
template class SGEXTN::Containers::LessThan<void(FunctionOwner::*)(int, int, int)>;
template class SGEXTN::Containers::LessThan<int(FunctionOwner::*)()>;
template class SGEXTN::Containers::LessThan<int(FunctionOwner::*)(int)>;
template class SGEXTN::Containers::LessThan<int(FunctionOwner::*)(int, int, int)>;
template class SGEXTN::Containers::LessThan<void(FunctionOwner::*)()const>;
template class SGEXTN::Containers::LessThan<void(FunctionOwner::*)(int)const>;
template class SGEXTN::Containers::LessThan<void(FunctionOwner::*)(int, int, int)const>;
template class SGEXTN::Containers::LessThan<int(FunctionOwner::*)()const>;
template class SGEXTN::Containers::LessThan<int(FunctionOwner::*)(int)const>;
template class SGEXTN::Containers::LessThan<int(FunctionOwner::*)(int, int, int)const>;
template class SGEXTN::Containers::MoreThan<int>;
template class SGEXTN::Containers::MoreThan<int*>;
template class SGEXTN::Containers::MoreThan<void(*)()>;
template class SGEXTN::Containers::MoreThan<void(*)(int)>;
template class SGEXTN::Containers::MoreThan<void(*)(int, int, int)>;
template class SGEXTN::Containers::MoreThan<int(*)()>;
template class SGEXTN::Containers::MoreThan<int(*)(int)>;
template class SGEXTN::Containers::MoreThan<int(*)(int, int, int)>;
template class SGEXTN::Containers::MoreThan<void(FunctionOwner::*)()>;
template class SGEXTN::Containers::MoreThan<void(FunctionOwner::*)(int)>;
template class SGEXTN::Containers::MoreThan<void(FunctionOwner::*)(int, int, int)>;
template class SGEXTN::Containers::MoreThan<int(FunctionOwner::*)()>;
template class SGEXTN::Containers::MoreThan<int(FunctionOwner::*)(int)>;
template class SGEXTN::Containers::MoreThan<int(FunctionOwner::*)(int, int, int)>;
template class SGEXTN::Containers::MoreThan<void(FunctionOwner::*)()const>;
template class SGEXTN::Containers::MoreThan<void(FunctionOwner::*)(int)const>;
template class SGEXTN::Containers::MoreThan<void(FunctionOwner::*)(int, int, int)const>;
template class SGEXTN::Containers::MoreThan<int(FunctionOwner::*)()const>;
template class SGEXTN::Containers::MoreThan<int(FunctionOwner::*)(int)const>;
template class SGEXTN::Containers::MoreThan<int(FunctionOwner::*)(int, int, int)const>;