//#include <SGEXTN_EntryPoint.h>
//#include <SGXCentral.h>
#include <private_api/SGEXTN_Containers_UnitTests.h>
#include <private_api/SGEXTN_Math_UnitTests.h>
#include <private_api/SGEXTN_ApplicationBase_UnitTests.h>
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
    SGEXTN::Containers::UnitTests::testAll();
    SGEXTN::Math::UnitTests::testAll();
    SGEXTN::ApplicationBase::UnitTests::testAll();
    SG("all tests pass");
}
