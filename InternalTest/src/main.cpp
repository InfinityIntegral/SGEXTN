//#include <SGEXTN_EntryPoint.h>
//#include <SGXCentral.h>
#include <private_api/SGEXTN_InternalTest_ContainersTest.h>
#include <private_api/SGEXTN_InternalTest_MathTest.h>
#include <private_api/SGEXTN_InternalTest_StructsTest.h>
#include <private_api/SGEXTN_InternalTest_StringTest.h>
#include <SGEXTN_ApplicationBase_Debug.h>

namespace {
void test(){

}

void init(){
    //SGXCentral::applicationName = "internal test";
    //SGXCentral::applicationVersion = "v6.4.0";
    //SGXCentral::organisationName = "05524F (Singapore)";
    //SGXCentral::customInitialise = &test;
    //SGXCentral::folderName = "SGEXTN";
}
}

int main(int /*argc*/, char** /*argv*/){
    //return SGEXTN(argc, argv, &init);
    SGEXTN::InternalTest::ContainersTest::testAll();
    SGEXTN::InternalTest::MathTest::testAll();
    SGEXTN::InternalTest::StructsTest::testAll();
    SGEXTN::InternalTest::StringTest::testAll();
    SG("all tests pass");
}
