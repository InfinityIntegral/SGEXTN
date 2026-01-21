//#include <SGEXTN_EntryPoint.h>
//#include <SGXCentral.h>
#include <private_api/SGEXTN_Containers_UnitTests.h>

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
    SGEXTN::Containers::UnitTests::testEqualTo();
    SGEXTN::Containers::UnitTests::testArray();
    SGEXTN::Containers::UnitTests::testSpan();
    SGEXTN::Containers::UnitTests::testLessThan();
    SGEXTN::Containers::UnitTests::testMoreThan();
    SGEXTN::Containers::UnitTests::testPair();
    SGEXTN::Containers::UnitTests::testTuple3();
    SGEXTN::Containers::UnitTests::testVector();
}
