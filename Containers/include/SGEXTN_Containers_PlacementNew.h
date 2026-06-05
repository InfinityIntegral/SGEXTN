#pragma once

namespace SGEXTN {
namespace Containers {
class PlacementNew {
public:
    static PlacementNew placeholder;
};
}
}

void* operator new(decltype(sizeof(0)) /*unused*/, SGEXTN::Containers::PlacementNew /*unused*/, void* p) noexcept;