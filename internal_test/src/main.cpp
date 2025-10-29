#include <iostream>

#include <main.h>

int main(int argc, char** argv){
    std::cout << "\n";
    std::cout << "Hello, Singapore";
#ifdef SG_BUILDING_INTERNALTEST
    std::cout << "\ndefines ok\n";
#endif
    std::cout << func();
    std::cout << "\n";
}
