#pragma once

namespace SGEXTN {
namespace InternalTest {
class BUILDLAH_DLL_SGEXTN_InternalTest ExternalTest {
public:
    static void testAll();
    static bool ifTestAll;
    static void testDateTimeExternal();
    static bool ifTestDateTimeExternal;
    static void testUnicodeQueryExternal();
    static bool ifTestUnicodeQueryExternal;
    static void testUnicodeExternal();
    static bool ifTestUnicodeExternal;
    static void testNumericalParsing();
    static bool ifTestNumericalParsing;
};
}
}