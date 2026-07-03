#include <string>
#include <fstream>
#include <array>
#include <cstdlib>
#include <iterator>
#include <format>
#include <cmath>
#include <limits>
#include <numbers>

std::string toHexString(unsigned int n){
    const std::string numericalString = std::format("{:08x}", n);
    std::string output = "\\x" + numericalString.substr(0, 2) + "\\x" + numericalString.substr(2, 2) + "\\x" + numericalString.substr(4, 2) + "\\x" + numericalString.substr(6, 2);
    return output;
}

std::string toHexString(double d){
    const float f = static_cast<float>(d);
    const unsigned int sign = static_cast<unsigned int>(std::signbit(f));
    unsigned int exponent = 0;
    unsigned int mantissa = 0;
    if(std::isnan(f)){exponent = 255; mantissa = 0x400000;}
    else if(std::isinf(f)){exponent = 255;}
    else if(f != 0.0f){
        const int prelimExponent = std::ilogb(std::abs(f));
        if(prelimExponent < -126){mantissa = static_cast<unsigned int>(std::round(std::scalbn(std::abs(f), 23 + 126)));}
        else{
            exponent = static_cast<unsigned int>(prelimExponent + 127);
            const float scaledDownMantissa = std::scalbn(std::abs(f), -prelimExponent) - 1.0f;
            mantissa = static_cast<unsigned int>(std::round(std::scalbn(scaledDownMantissa, 23)));
        }
        if(mantissa > 0x7fffff){mantissa = mantissa & 0x7fffff; exponent++;}
    }
    const unsigned int packedBinary = (sign << 31) | (exponent << 23) | mantissa;
    return toHexString(packedBinary);
}

void getExponentialTables(std::string& width, std::string& floor){
    std::array<double, 256> widthArray = {};
    std::array<double, 256> floorArray = {};
    const double rightBound = 7.69711747013104972;
    const double rectangleArea = 0.003949653420019919;
    widthArray.at(0) = std::numeric_limits<double>::infinity();
    floorArray.at(0) = (rectangleArea - std::exp(-1.0 *rightBound)) / rectangleArea;
    widthArray.at(1) = rightBound;
    floorArray.at(1) = std::pow(std::numbers::e, -1.0 * rightBound);
    for(int i=2; i<256; i++){
        floorArray.at(i) = floorArray.at(i - 1) + rectangleArea / widthArray.at(i - 1);
        widthArray.at(i) = -1.0 * std::log(floorArray.at(i));
    }
    width = "";
    for(int i=0; i<256; i++){
        width += toHexString(widthArray.at(i));
    }
    floor = "";
    for(int i=0; i<256; i++){
        floor += toHexString(floorArray.at(i));
    }
}

void getNormalTables(std::string& hwidth, std::string& floor){
    std::array<double, 256> hwidthArray = {};
    std::array<double, 256> floorArray = {};
    const double rightBound = 3.6541528853610088;
    const double rectangleArea = 0.00492867323399;
    hwidthArray.at(0) = std::numeric_limits<double>::infinity();
    floorArray.at(0) = 0.0;
    hwidthArray.at(1) = rightBound;
    floorArray.at(1) = std::pow(std::numbers::e, -0.5 * rightBound * rightBound);
    for(int i=2; i<256; i++){
        floorArray.at(i) = floorArray.at(i - 1) + rectangleArea / hwidthArray.at(i - 1);
        hwidthArray.at(i) = std::sqrt(-2.0 * std::log(floorArray.at(i)));
    }
    hwidth = "";
    for(int i=0; i<256; i++){
        hwidth += toHexString(hwidthArray.at(i));
    }
    floor = "";
    for(int i=0; i<256; i++){
        floor += toHexString(floorArray.at(i));
    }
}

int main(){
    std::string exponentialWidth;
    std::string exponentialFloor;
    std::string normalHwidth;
    std::string normalFloor;
    getExponentialTables(exponentialWidth, exponentialFloor);
    getNormalTables(normalHwidth, normalFloor);
    std::ifstream templateFile("ziggurattablestemplate.txt");
    std::ofstream outputFile("../src/ZigguratTables.cpp");
    std::string templateString((std::istreambuf_iterator<char>(templateFile)), std::istreambuf_iterator<char>());
    templateString.replace(templateString.find("@SG_EXP_WIDTH"), 13, exponentialWidth);
    templateString.replace(templateString.find("@SG_EXP_FLOOR"), 13, exponentialFloor);
    templateString.replace(templateString.find("@SG_NORM_HWIDTH"), 15, normalHwidth);
    templateString.replace(templateString.find("@SG_NORM_FLOOR"), 14, normalFloor);
    outputFile << templateString;
}
