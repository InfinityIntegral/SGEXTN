#pragma once

namespace SGEXTN {
namespace Containers {
class BuildLah_SGEXTN_Containers PlacementNew {
public:
    static PlacementNew placeholder;
};
}
}

BuildLah_SGEXTN_Containers void* operator new(decltype(sizeof(int)) /*unused*/, SGEXTN::Containers::PlacementNew /*unused*/, void* p) noexcept;
