#pragma once
#include <SGEXTN_Structs_RgbaColour.h>

namespace SGEXTN {
namespace Structs {
class BUILDLAH_DLL_SGEXTN_Structs ContrastUtilities {
public:
    static float getContrast(SGEXTN::Structs::RgbaColour bg, SGEXTN::Structs::RgbaColour fg);
    static float getAbsoluteContrast(SGEXTN::Structs::RgbaColour bg, SGEXTN::Structs::RgbaColour fg);
    static SGEXTN::Structs::RgbaColour getForegroundLightMode(SGEXTN::Structs::RgbaColour bg, float targetContrast, bool* isPossible);
    static SGEXTN::Structs::RgbaColour getForegroundDarkMode(SGEXTN::Structs::RgbaColour bg, float targetContrast, bool* isPossible);
    static SGEXTN::Structs::RgbaColour getBackgroundLightMode(SGEXTN::Structs::RgbaColour fg, float targetContrast, bool* isPossible);
    static SGEXTN::Structs::RgbaColour getBackgroundDarkMode(SGEXTN::Structs::RgbaColour fg, float targetContrast, bool* isPossible);
    static float safeContrast(float sizeUnit, bool bold, bool bodyText);
};
}
}
