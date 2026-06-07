#include <private_api/SGEXTN_InternalTest_ContainersTest.h>
#include <private_api/SGEXTN_InternalTest_MathTest.h>
#include <private_api/SGEXTN_InternalTest_UtilitiesTest.h>
#include <private_api/SGEXTN_InternalTest_CoreTextTest.h>
#include <SGEXTN_CoreText_Debug.h>

int main(int /*argc*/, char** /*argv*/){
    SGEXTN::InternalTest::ContainersTest::testAll();
    SGEXTN::InternalTest::MathTest::testAll();
    SGEXTN::InternalTest::UtilitiesTest::testAll();
    SGEXTN::InternalTest::CoreTextTest::testAll();
    SG("all tests pass");
}
