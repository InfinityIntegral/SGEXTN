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
