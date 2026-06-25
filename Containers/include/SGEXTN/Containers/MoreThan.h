/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#pragma once

namespace SGEXTN {
namespace Containers {
template <typename T> class MoreThan {
public:
    [[nodiscard]] bool operator()(const T& a, const T& b) const;
};

template <typename T> class MoreThan<T*> {
public:
    [[nodiscard]] bool operator()(const T* a, const T* b) const;
};

template <typename ReturnType, typename... ArgTypes> class MoreThan<ReturnType (*)(ArgTypes...)> {
public:
    [[nodiscard]] bool operator()(ReturnType (*a)(ArgTypes...), ReturnType (*b)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class MoreThan<ReturnType (ClassName::*)(ArgTypes...)> {
public:
    [[nodiscard]] bool operator()(ReturnType (ClassName::*a)(ArgTypes...), ReturnType (ClassName::*b)(ArgTypes...)) const;
};

template <typename ReturnType, typename ClassName, typename... ArgTypes> class MoreThan<ReturnType (ClassName::*)(ArgTypes...) const> {
public:
    [[nodiscard]] bool operator()(ReturnType (ClassName::*a)(ArgTypes...) const, ReturnType (ClassName::*b)(ArgTypes...) const) const;
};
}
}

#include <SGEXTN/Containers/private_api/MoreThan_impl.h>
