#include <iostream>
#include <string>

int main(){
    int n;
    std::cin >> n;
    std::string arr[n];
    for(int i=0; i<n; i++){
        std::string k;
        std::string v;
        std::cin >> k >> v;
        arr[i] = ("(*SGXSingCorrectCore::database).insert(\"" + k + "\", QChar(0x" + v + "));\n");
    }
    for(int i=0; i<n; i++){
        std::cout << arr[i];
    }
}