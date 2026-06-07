#include <SGEXTN_Containers_PlacementNew.h>

SGEXTN::Containers::PlacementNew SGEXTN::Containers::PlacementNew::placeholder;

void* operator new(decltype(sizeof(int)) /*unused*/, SGEXTN::Containers::PlacementNew /*unused*/, void* p) noexcept {
    return p;
}