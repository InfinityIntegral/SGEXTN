#include <private_api/SGEXTN_Math_UnitTests.h>
#include <private_api/SGEXTN_Containers_Crash.h>

void SGEXTN::Math::UnitTests::checkDataSizes(){
    if(sizeof(char) != 1){SGEXTN::Containers::Crash::warn("unexpected char size");}
    if(sizeof(short) != 2){SGEXTN::Containers::Crash::warn("unpected short size");}
    if(sizeof(int) != 4){SGEXTN::Containers::Crash::warn("unexpected int size");}
    if(sizeof(long long) != 8){SGEXTN::Containers::Crash::warn("unexpected long long size");}
    if(sizeof(float) != 4){SGEXTN::Containers::Crash::warn("unexpected float size");}
    if(sizeof(double) != 8){SGEXTN::Containers::Crash::warn("unexpected double size");}
}
