#include <private_api/SGEXTN_Containers_UnitTests.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_Span.h>
#include <SGEXTN_Containers_LessThan.h>
#include <SGEXTN_Containers_MoreThan.h>
#include <SGEXTN_Containers_Pair.h>
#include <SGEXTN_Containers_Tuple3.h>
#include <SGEXTN_Containers_Vector.h>
#include <SGEXTN_Containers_Queue.h>
#include <SGEXTN_Containers_Stack.h>
#include <SGEXTN_Containers_Deque.h>
#include <SGEXTN_Containers_PriorityQueue.h>
#include <SGEXTN_Containers_Set.h>

void SGEXTN::Containers::UnitTests::testEqualTo(){
    const SGEXTN::Containers::EqualTo<int> comparator;
    if(comparator(0, 0) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::EqualTo - 0 not equal to 0");}
    if(comparator(-1, 0) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::EqualTo - -1 equal to 0");}
    if(comparator(1, 0) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::EqualTo - 1 equal to 0");}
}

void SGEXTN::Containers::UnitTests::testArray(){
    SGEXTN::Containers::Array<int> arr(1, 2, 3, 4, 5);
    if(arr.at(0) != 1 || arr.at(1) != 2 || arr.at(2) != 3 || arr.at(3) != 4 || arr.at(4) != 5 || arr.length() != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array - init list fail");}
    arr = SGEXTN::Containers::Array<int>(2, 26);
    if(arr.at(0) != 26 || arr.at(1) != 26 || arr.length() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array - move assign fail");}
    SGEXTN::Containers::Array<int> arr0(3);
    arr0.at(0) = 726;
    if(arr0.at(0) != 726){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array - assign to element fail");}
    arr0 = arr;
    if(arr0.at(1) != 26 || arr0.at(0) != 26){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array - copy assign fail");}
    if(arr0.length() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array - get length info fail");}
    arr0.fill(-1);
    if(arr0.at(0) != -1 || arr0.at(1) != -1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Array - fill with default value fail");}
}

void SGEXTN::Containers::UnitTests::testSpan(){
    SGEXTN::Containers::Array<int> arr(1, 2, 3, 4, 5);
    SGEXTN::Containers::Span<int> span(arr.pointerToData(0), 5);
    if(span.at(0) != 1 || span.at(1) != 2 || span.at(2) != 3 || span.at(3) != 4 || span.at(4) != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - bind to data fail");}
    if(span.length() != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - retrieving length fail");}
    arr.at(3) = 26;
    if(span.at(3) != 26){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - reflect underlying data changes fail");}
    span.at(2) = -1;
    if(arr.at(2) != -1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - propagate underlying data changes fail");}
    SGEXTN::Containers::Span<int> subspanCenter = span.subspan(1, 3);
    if(subspanCenter.at(0) != 2 || subspanCenter.at(1) != -1 || subspanCenter.at(2) != 26 || subspanCenter.length() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - subspan center fail");}
    SGEXTN::Containers::Span<int> subspanLeft = span.subspanLeft(2);
    if(subspanLeft.at(0) != 1 || subspanLeft.at(1) != 2 || subspanLeft.length() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - subspan left fail");}
    SGEXTN::Containers::Span<int> subspanRight = span.subspanRight(2);
    if(subspanRight.at(0) != 26 || subspanRight.at(1) != 5 || subspanRight.length() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - subspan right fail");}
    if(subspanLeft.pointerToData(1) != subspanCenter.pointerToData(0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Span - inconsistent pointer to data");}
}

void SGEXTN::Containers::UnitTests::testLessThan(){
    const SGEXTN::Containers::LessThan<int> comparator;
    if(comparator(-1, 0) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::LessThan - -1 not less than 0");}
    if(comparator(0, 0) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::LessThan - 0 less than 0");}
    if(comparator(1, 0) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::LessThan - 1 less than 0");}
    const SGEXTN::Containers::LessThan<const int*> pointerComparator;
    const int i = 0;
    const int j = 0;
    if(pointerComparator(&i, &j) == false && pointerComparator(&j, &i) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::LessThan - different pointer point to same result");}
    if(pointerComparator(&i, &i) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::LessThan - same pointer point to different result");}
}

void SGEXTN::Containers::UnitTests::testMoreThan(){
    const SGEXTN::Containers::MoreThan<int> comparator;
    if(comparator(-1, 0) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MoreThan - -1 more than 0");}
    if(comparator(0, 0) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MoreThan - 0 more than 0");}
    if(comparator(1, 0) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MoreThan - 1 not more than 0");}
    const SGEXTN::Containers::MoreThan<const int*> pointerComparator;
    const int i = 0;
    const int j = 0;
    if(pointerComparator(&i, &j) == false && pointerComparator(&j, &i) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MoreThan - different pointer point to same result");}
    if(pointerComparator(&i, &i) == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::MoreThan - same pointer point to different result");}
}

void SGEXTN::Containers::UnitTests::testPair(){
    const SGEXTN::Containers::Pair<int, int> pair(0, 0);
    if(pair.first != 0 || pair.second != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - constructor init fail");}
    if(SGEXTN::Containers::Pair<int, int>(0, 0) == SGEXTN::Containers::Pair<int, int>(0, 1)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) equals (0, 1)");}
    if((SGEXTN::Containers::Pair<int, int>(0, 0) == SGEXTN::Containers::Pair<int, int>(0, 0)) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) not equal to (0, 0)");}
    if((SGEXTN::Containers::Pair<int, int>(0, 0) != SGEXTN::Containers::Pair<int, int>(0, 1)) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) equals (0, 1)");}
    if(SGEXTN::Containers::Pair<int, int>(0, 0) != SGEXTN::Containers::Pair<int, int>(0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) not equal to (0, 0)");}
    if(SGEXTN::Containers::Pair<int, int>(1, 0) < SGEXTN::Containers::Pair<int, int>(0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (1, 0) less than (0, 0)");}
    if(SGEXTN::Containers::Pair<int, int>(0, 1) < SGEXTN::Containers::Pair<int, int>(0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 1) less than (0, 0)");}
    if(SGEXTN::Containers::Pair<int, int>(1, 0) < SGEXTN::Containers::Pair<int, int>(0, 1)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (1, 0) less than (0, 1)");}
    if(SGEXTN::Containers::Pair<int, int>(0, 0) < SGEXTN::Containers::Pair<int, int>(0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) less than (0, 0)");}
    if(SGEXTN::Containers::Pair<int, int>(0, 0) > SGEXTN::Containers::Pair<int, int>(1, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) more than (1, 0)");}
    if(SGEXTN::Containers::Pair<int, int>(0, 0) > SGEXTN::Containers::Pair<int, int>(0, 1)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) more than (0, 1)");}
    if(SGEXTN::Containers::Pair<int, int>(0, 1) > SGEXTN::Containers::Pair<int, int>(1, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 1) more than (1, 0)");}
    if(SGEXTN::Containers::Pair<int, int>(0, 0) > SGEXTN::Containers::Pair<int, int>(0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Pair - (0, 0) more than (0, 0)");}
}

void SGEXTN::Containers::UnitTests::testTuple3(){
    const SGEXTN::Containers::Tuple3<int, int, int> tuple(0, 0, 0);
    if(tuple.first != 0 || tuple.second != 0 || tuple.third != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - constructor init fail");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) == SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 1)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) equals (0, 0, 1)");}
    if((SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) == SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0)) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) not equal to (0, 0, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) != SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) not equal to (0, 0, 0)");}
    if((SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) != SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 1)) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) equals to (0, 0, 1)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(1, 0, 0) < SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (1, 0, 0) less than (0, 0, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 1, 0) < SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 1, 0) less than (0, 0, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 1) < SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 1) less than (0, 0, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) < SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) less than (0, 0, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(1, 0, 0) < SGEXTN::Containers::Tuple3<int, int, int>(0, 1, 1)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (1, 0, 0) less than (0, 1, 1)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) > SGEXTN::Containers::Tuple3<int, int, int>(1, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) more than (1, 0, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) > SGEXTN::Containers::Tuple3<int, int, int>(0, 1, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) more than (0, 1, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) > SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 1)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) more than (0, 0, 1)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0) > SGEXTN::Containers::Tuple3<int, int, int>(0, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 0, 0) more than (0, 0, 0)");}
    if(SGEXTN::Containers::Tuple3<int, int, int>(0, 1, 1) > SGEXTN::Containers::Tuple3<int, int, int>(1, 0, 0)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Tuple3 - (0, 1, 1) more than (1, 0, 0)");}
}

void SGEXTN::Containers::UnitTests::testVector(){
    SGEXTN::Containers::Vector<int> v;
    v.pushBack(0);
    if(v.length() != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector - length check fail");}
    if(v.at(0) != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector - push back fail");}
    v.pushBack(2);
    v.pushBack(3);
    if(v.length() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector - length update fail");}
    v.popBack();
    if(v.length() != 2 || v.at(1) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector - pop back fail");}
    v.fill(26);
    if(v.at(0) != 26 || v.at(1) != 26 || v.length() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector - fill fail");}
    v = SGEXTN::Containers::Vector(5, 0);
    if(v.at(0) != 0 || v.at(1) != 0 || v.at(2) != 0 || v.at(3) != 0 || v.at(4) != 0 || v.length() != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector - construct fail");}
    v = SGEXTN::Containers::Vector<int>(100);
    if(v.length() != 100){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Vector - blank construct fail");}
}

void SGEXTN::Containers::UnitTests::testQueue(){
    SGEXTN::Containers::Queue<int> queue;
    queue.push(1);
    queue.push(2);
    if(queue.length() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue - length check fail");}
    if(queue.front() != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue - front element check fail");}
    if(queue.back() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue - back element check fail");}
    queue.pop();
    if(queue.length() != 1 || queue.front() != 2 || queue.back() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue - pop fail");}
    queue.push(3);
    if(queue.length() != 2 || queue.back() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Queue - push fail");}
}

void SGEXTN::Containers::UnitTests::testStack(){
    SGEXTN::Containers::Stack<int> stack;
    stack.push(1);
    stack.push(2);
    if(stack.length() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Stack - length check fail");}
    if(stack.top() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Stack - top element check fail");}
    stack.pop();
    if(stack.length() != 1 || stack.top() != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Stack - pop fail");}
    stack.push(3);
    if(stack.length() != 2 || stack.top() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Stack - push element fail");}
}

void SGEXTN::Containers::UnitTests::testDeque(){
    SGEXTN::Containers::Deque<int> dq;
    dq.pushBack(1);
    dq.pushBack(2);
    dq.pushBack(3);
    if(dq.length() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - length check fail");}
    if(dq.front() != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - front element check fail");}
    if(dq.back() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - back element check fail");}
    if(dq.at(0) != 1 || dq.at(1) != 2 || dq.at(2) != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - index access fail");}
    dq.fill(26);
    if(dq.at(0) != 26 || dq.at(1) != 26 || dq.at(2) != 26 || dq.length() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - fill reset fail");}
    dq.pushBack(1);
    if(dq.length() != 4 || dq.back() != 1 || dq.front() != 26){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - push back fail");}
    dq.popBack();
    if(dq.length() != 3 || dq.back() != 26 || dq.front() != 26){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - pop back fail");}
    dq.pushFront(1);
    if(dq.length() != 4 || dq.front() != 1 || dq.back() != 26){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - push front fail");}
    dq.popFront();
    if(dq.length() != 3 || dq.front() != 26 || dq.back() != 26){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Deque - pop front fail");}
}

void SGEXTN::Containers::UnitTests::testPriorityQueue(){
    SGEXTN::Containers::PriorityQueue<int, SGEXTN::Containers::LessThan<int>> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    if(pq.length() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - length check fail");}
    if(pq.top() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - top check fail");}
    pq.push(5);
    if(pq.length() != 4 || pq.top() != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - push bigger element fail");}
    pq.push(4);
    if(pq.length() != 5 || pq.top() != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - push in range element fail");}
    pq.pop();
    if(pq.length() != 4 || pq.top() != 4){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - pop fail");}
    pq.push(-1);
    if(pq.length() != 5 || pq.top() != 4){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - push smaller element fail");}
    pq.pop();
    if(pq.length() != 4 || pq.top() != 3){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - pop fail 2");}
    pq.pop();
    if(pq.length() != 3 || pq.top() != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - pop fail 3");}
    pq.pop();
    if(pq.length() != 2 || pq.top() != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - pop fail 4");}
    pq.pop();
    if(pq.length() != 1 || pq.top() != -1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - pop fail 5");}
    pq.pop();
    if(pq.length() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::PriorityQueue - pop fail 6");}
}

void SGEXTN::Containers::UnitTests::testSet(){
    SGEXTN::Containers::Set<int, SGEXTN::Containers::LessThan<int>> s;
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);
    s.insert(5);
    bool x = s.insert(6);
    if(s.length() != 6 || s.contains(6) == false || x == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - insert fail");}
    x = s.insert(5);
    if(x == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - duplicate insert fail");}
    if(s.length() != 6){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - length check fail");}
    x = s.erase(7);
    if(x == true){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - erase nonexistent fail");}
    x = s.erase(2);
    if(s.length() != 5 || s.contains(2) == true || x == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - erase fail");}
    if(s.contains(1) == false || s.contains(2) == true || s.contains(3) == false || s.contains(4) == false || s.contains(5) == false || s.contains(6) == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - contains check fail");}
    if((*s.begin()) != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - begin iterator fail");}
    if((*(++s.end())) != 1){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - end iterator fail");}
    SGEXTN::Containers::SetIterator<int, SGEXTN::Containers::LessThan<int>> itr = s.find(1);
    if(itr != s.begin()){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - find fail");}
    x = s.erase(itr);
    if(s.length() != 4 || s.contains(1) == true || x == false){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - erase iterator fail");}
    if((*s.lowerBound(4)) != 4){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - lower bound fail");}
    if((*s.upperBound(4)) != 5){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - upper bound fail");}
    if(s.indexOf(5) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - index of element fail");}
    if(s.indexOf(s.find(5)) != 2){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - index of iterator fail");}
    if(s.elementAt(3) != 6){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - element at fail");}
    if(s.iteratorAt(1) != s.find(4)){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - iterator at fail");}
    for(SGEXTN::Containers::SetIterator<int, SGEXTN::Containers::LessThan<int>> i = s.begin(); i != s.end(); i++){
        s.erase(i);
    }
    if(s.length() != 0){SGEXTN::Containers::Crash::crash("SGEXTN::Containers::Set - in order traversal erase fail");}
}
