#pragma once

namespace SGEXTN {
namespace Math {
template <typename T> class BUILDLAH_DLL_SGEXTN_Math FloatConstants {
public:
    [[nodiscard]] static T eulerNumber();
    [[nodiscard]] static T eulerNumberLog2();
    [[nodiscard]] static T eulerNumberLog10();
    [[nodiscard]] static T pi();
    [[nodiscard]] static T naturalLog2();
    [[nodiscard]] static T naturalLog10();
    [[nodiscard]] static T squareRoot2();
    [[nodiscard]] static T squareRoot3();
    [[nodiscard]] static T goldenRatio();
};
}
}
