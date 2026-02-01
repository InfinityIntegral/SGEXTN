#pragma once
namespace SGEXTN {
namespace ApplicationBase {
class BUILDLAH_DLL_SGEXTN_ApplicationBase Random {
public:
    static float normalisedFloat();
    static double normalisedDouble();
    static int signedInt32();
    static unsigned int unsignedInt32();
    static long long signedInt64();
    static unsigned long long unsignedInt64();
};
}
}
