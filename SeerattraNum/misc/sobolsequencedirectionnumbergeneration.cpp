#include <string>
#include <fstream>
#include <array>
#include <iostream>
#include <cstdlib>
#include <iterator>
#include <format>

constexpr int MAXIMUM_DIMENSION_COUNT = 21200;

std::string toHexString(unsigned int n){
    const std::string numericalString = std::format("{:08x}", n);
    std::string output = "\\x" + numericalString.substr(0, 2) + "\\x" + numericalString.substr(2, 2) + "\\x" + numericalString.substr(4, 2) + "\\x" + numericalString.substr(6, 2);
    return output;
}

int main(){
    std::ifstream templateFile("sobolsequencelookuptemplate.txt");
    std::ifstream dataFile("sobolsequencedirectionnumbers.txt");
    std::ofstream outputFile("../src/SobolSequenceLookup.cpp");
    const std::string templateString((std::istreambuf_iterator<char>(templateFile)), std::istreambuf_iterator<char>());
    outputFile << templateString;
    std::array<int, MAXIMUM_DIMENSION_COUNT> degrees = {};
    std::array<int, MAXIMUM_DIMENSION_COUNT> coefficients = {};
    std::array<std::array<unsigned int, 32>, MAXIMUM_DIMENSION_COUNT> directionNumbers = {};
    std::string discard;
    for(int i=0; i<4; i++){
        dataFile >> discard;
    }
    for(int i=0; i<MAXIMUM_DIMENSION_COUNT; i++){
        int dimension = 0;
        dataFile >> dimension;
        if(dimension != i + 2){
            std::cerr << "dimension number wrong at " << i << ", received " << dimension << "\n";
            std::abort();
        }
        dataFile >> degrees.at(i);
        dataFile >> coefficients.at(i);
        for(int j=0; j<degrees.at(i); j++){
            dataFile >> directionNumbers.at(i).at(j);
        }
    }
    for(int i=0; i<MAXIMUM_DIMENSION_COUNT; i++){
        for(int j=degrees.at(i); j<32; j++){
            unsigned int thisDirectionNumber = directionNumbers.at(i).at(j - degrees.at(i));
            for(int k=1; k<degrees.at(i); k++){
                if((coefficients.at(i) & (1 << (k-1))) != 0){thisDirectionNumber = thisDirectionNumber ^ (directionNumbers.at(i).at(j - k) << (degrees.at(i) - k));}
            }
            thisDirectionNumber = thisDirectionNumber ^ (directionNumbers.at(i).at(j - degrees.at(i)) << degrees.at(i));
            directionNumbers.at(i).at(j) = thisDirectionNumber;
        }
    }
    for(int i=0; i<MAXIMUM_DIMENSION_COUNT; i++){
        for(int j=0; j<32; j++){
            directionNumbers.at(i).at(j) = (directionNumbers.at(i).at(j) << (31 - j));
        }
    }
    for(int i=0; i<MAXIMUM_DIMENSION_COUNT/100; i++){
        outputFile << "\"";
        for(int j=0; j<100; j++){
            for(int k=0; k<32; k++){
                outputFile << toHexString(directionNumbers.at(100 * i + j).at(k));
            }
        }
        outputFile << "\"\n";
    }
    outputFile << ";\n";
}
