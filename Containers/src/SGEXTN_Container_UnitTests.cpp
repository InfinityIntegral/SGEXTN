#include <private_api/SGEXTN_Containers_UnitTests.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_Containers_Span.h>
#include <SGEXTN_Containers_LessThan.h>
#include <SGEXTN_Containers_MoreThan.h>

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
