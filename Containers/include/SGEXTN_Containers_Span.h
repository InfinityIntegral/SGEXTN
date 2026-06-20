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
template <typename T> class Span {
public:
    Span(T* data, int length);
    [[nodiscard]] int length() const;
    [[nodiscard]] T& at(int i);
    [[nodiscard]] const T& at(int i) const;
    [[nodiscard]] Span subspan(int start, int length) const;
    [[nodiscard]] Span subspanLeft(int length) const;
    [[nodiscard]] Span subspanRight(int length) const;
    template <typename Comparator> void sort(int start, int length);
    T* private_data;
    int private_length;
};
}
}

#include <private_api/SGEXTN_Containers_Span_impl.h>
