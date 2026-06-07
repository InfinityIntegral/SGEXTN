#pragma once

namespace SGEXTN {
namespace InternalTest {
class BUILDLAH_DLL_SGEXTN_InternalTest CoreTextTest {
public:
    static void testAll();
    static void testUnicodeQuery();
    static void testCharacter();
    static void testString();
    static void runExternalUnicodeTests();
    static void runExternalNumericParsingTests();
};
}
}