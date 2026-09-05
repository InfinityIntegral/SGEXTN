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

namespace SGEXTN::CanOne {
template <typename ReturnType> class BaseAction {
protected:
    BaseAction() = default;
    BaseAction(const BaseAction&) = default;
    BaseAction& operator=(const BaseAction&) = default;
    BaseAction(BaseAction&&) noexcept = default;
    BaseAction& operator=(BaseAction&&) noexcept = default;
public:
    [[nodiscard]] virtual ReturnType execute() const = 0;
    [[nodiscard]] virtual BaseAction<ReturnType>* copyBasePointer() const = 0;
    [[nodiscard]] virtual BaseAction<ReturnType>* moveBasePointer() && = 0;
    virtual ~BaseAction() = default;
};
}
