#include <iostream>
#include <main.h>
#include <private_api_Containers/SGLCrash.h>
#include <SGLArray.h>

int main(int argc, char** argv){
    (void)argc;
    (void)argv;
    std::cout << "\n";
    std::cout << "Hello, Singapore";
#ifdef SG_BUILDING_INTERNALTEST
    std::cout << "\ndefines ok\n";
#endif
    std::cout << func();
    std::cout << "\n";
    std::cout << (&SGLCrash::crash);
    std::cout << "\n";
    SGLArray<int> a(1, 2, 3, 4, 5);
    for(int i=0; i<a.length(); i++){
        std::cout << a.at(i) << " ";
    }
}
