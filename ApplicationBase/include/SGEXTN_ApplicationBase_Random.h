#pragma once
namespace SGEXTN {
namespace ApplicationBase {
class BUILDLAH_DLL_SGEXTN_ApplicationBase Random {
public:
    [[nodiscard]] static float normalisedFloat();
    [[nodiscard]] static double normalisedDouble();
    [[nodiscard]] static int signedInt32();
    [[nodiscard]] static unsigned int unsignedInt32();
    [[nodiscard]] static long long signedInt64();
    [[nodiscard]] static unsigned long long unsignedInt64();
};
}
}
