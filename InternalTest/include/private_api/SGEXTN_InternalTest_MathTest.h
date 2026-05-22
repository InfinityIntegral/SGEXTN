#pragma once

namespace SGEXTN {
namespace InternalTest {
class BUILDLAH_DLL_SGEXTN_InternalTest MathTest {
public:
    static bool checkDataSizes();
    static void testIntegerLimits();
    static void testIntegerMath();
    static void testFloatConstants();
    static void testFloatLimits();
    static void testFloatMath();
    static void testAll();
};
}
}
