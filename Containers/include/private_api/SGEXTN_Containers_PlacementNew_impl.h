#pragma once

inline SGEXTN::Containers::PlacementNew SGEXTN::Containers::PlacementNew::placeholder;

void* operator new(decltype(sizeof(0)) /*unused*/, SGEXTN::Containers::PlacementNew /*unused*/, void* p) noexcept {return p;}