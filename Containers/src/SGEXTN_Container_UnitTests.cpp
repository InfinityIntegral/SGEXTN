#include <private_api/SGEXTN_Containers_UnitTests.h>
#include <SGEXTN_Containers_EqualTo.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_Array.h>

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
