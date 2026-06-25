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
namespace Utilities {
class RgbaColour;

class BuildLah_SGEXTN_Utilities ContrastUtilities {
public:
    [[nodiscard]] static float getContrast(SGEXTN::Utilities::RgbaColour bg, SGEXTN::Utilities::RgbaColour fg);
    [[nodiscard]] static float getAbsoluteContrast(SGEXTN::Utilities::RgbaColour bg, SGEXTN::Utilities::RgbaColour fg);
    [[nodiscard]] static SGEXTN::Utilities::RgbaColour getForegroundLightMode(SGEXTN::Utilities::RgbaColour bg, float targetContrast, bool* isPossible);
    [[nodiscard]] static SGEXTN::Utilities::RgbaColour getForegroundDarkMode(SGEXTN::Utilities::RgbaColour bg, float targetContrast, bool* isPossible);
    [[nodiscard]] static SGEXTN::Utilities::RgbaColour getBackgroundLightMode(SGEXTN::Utilities::RgbaColour fg, float targetContrast, bool* isPossible);
    [[nodiscard]] static SGEXTN::Utilities::RgbaColour getBackgroundDarkMode(SGEXTN::Utilities::RgbaColour fg, float targetContrast, bool* isPossible);
    [[nodiscard]] static float safeContrast(float sizeUnit, bool bold, bool bodyText);
};
}
}
