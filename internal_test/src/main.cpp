#include <SGEXTN_EntryPoint.h>
#include <SGXCentral.h>

namespace {
void test(){

}

void init(){
    SGXCentral::applicationName = "internal test";
    SGXCentral::applicationVersion = "v6.2.0";
    SGXCentral::organisationName = "05524F (Singapore)";
    SGXCentral::customInitialise = &test;
    SGXCentral::folderName = "SGEXTN";
}
}

int main(int argc, char** argv){
    return SGEXTN(argc, argv, &init);
}
