/*
   Copyright 2026 05524F.sg

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
// BuildLah license check: SGEXTN 7.0.0

#include <SGEXTN/Containers/Serialisation.h>
#include <SGEXTN/Containers/Span.h>
#include <cmath>
#include <limits>

bool SGEXTN::Containers::Serialisation<bool>::sendOut(bool x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 1){return false;}
    if(x == false){data.at(0) = static_cast<unsigned char>(0);}
    else{data.at(0) = static_cast<unsigned char>(1);}
    return true;
}

bool SGEXTN::Containers::Serialisation<bool>::sendIn(bool& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 1 || static_cast<unsigned int>(data.at(0)) > 1){return false;}
    x = false;
    if(data.at(0) == static_cast<unsigned char>(1)){x = true;}
    return true;
}

int SGEXTN::Containers::Serialisation<bool>::sizeOut([[maybe_unused]] bool x){
    return 1;
}

int SGEXTN::Containers::Serialisation<bool>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 1){return -1;}
    return 1;
}

bool SGEXTN::Containers::Serialisation<unsigned char>::sendOut(unsigned char x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 1){return false;}
    data.at(0) = x;
    return true;
}

bool SGEXTN::Containers::Serialisation<unsigned char>::sendIn(unsigned char& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 1){return false;}
    x = data.at(0);
    return true;
}

int SGEXTN::Containers::Serialisation<unsigned char>::sizeOut([[maybe_unused]] unsigned char x){
    return 1;
}

int SGEXTN::Containers::Serialisation<unsigned char>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 1){return -1;}
    return 1;
}

bool SGEXTN::Containers::Serialisation<short>::sendOut(short x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 2){return false;}
    const unsigned short u = static_cast<unsigned short>(x);
    data.at(0) = u & static_cast<unsigned char>(0xff);
    data.at(1) = (u >> 8) & static_cast<unsigned char>(0xff);
    return true;
}

bool SGEXTN::Containers::Serialisation<short>::sendIn(short& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 2){return false;}
    const unsigned short u = (static_cast<unsigned short>(data.at(1)) << 8) | static_cast<unsigned short>(data.at(0));
    x = static_cast<short>(u);
    return true;
}

int SGEXTN::Containers::Serialisation<short>::sizeOut([[maybe_unused]] short x){
    return 2;
}

int SGEXTN::Containers::Serialisation<short>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 2){return -1;}
    return 2;
}

bool SGEXTN::Containers::Serialisation<unsigned short>::sendOut(unsigned short x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 2){return false;}
    data.at(0) = x & static_cast<unsigned char>(0xff);
    data.at(1) = (x >> 8) & static_cast<unsigned char>(0xff);
    return true;
}

bool SGEXTN::Containers::Serialisation<unsigned short>::sendIn(unsigned short& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 2){return false;}
    x = (static_cast<unsigned short>(data.at(1)) << 8) | static_cast<unsigned short>(data.at(0));
    return true;
}

int SGEXTN::Containers::Serialisation<unsigned short>::sizeOut([[maybe_unused]] unsigned short x){
    return 2;
}

int SGEXTN::Containers::Serialisation<unsigned short>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 2){return -1;}
    return 2;
}

bool SGEXTN::Containers::Serialisation<int>::sendOut(int x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 4){return false;}
    const unsigned int u = static_cast<unsigned int>(x);
    data.at(0) = u & static_cast<unsigned char>(0xff);
    data.at(1) = (u >> 8) & static_cast<unsigned char>(0xff);
    data.at(2) = (u >> 16) & static_cast<unsigned char>(0xff);
    data.at(3) = (u >> 24) & static_cast<unsigned char>(0xff);
    return true;
}

bool SGEXTN::Containers::Serialisation<int>::sendIn(int& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 4){return false;}
    const unsigned int u = (static_cast<unsigned int>(data.at(3)) << 24) | (static_cast<unsigned int>(data.at(2)) << 16) | (static_cast<unsigned int>(data.at(1)) << 8) | static_cast<unsigned int>(data.at(0));
    x = static_cast<int>(u);
    return true;
}

int SGEXTN::Containers::Serialisation<int>::sizeOut([[maybe_unused]] int x){
    return 4;
}

int SGEXTN::Containers::Serialisation<int>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 4){return -1;}
    return 4;
}

bool SGEXTN::Containers::Serialisation<unsigned int>::sendOut(unsigned int x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 4){return false;}
    data.at(0) = x & static_cast<unsigned char>(0xff);
    data.at(1) = (x >> 8) & static_cast<unsigned char>(0xff);
    data.at(2) = (x >> 16) & static_cast<unsigned char>(0xff);
    data.at(3) = (x >> 24) & static_cast<unsigned char>(0xff);
    return true;
}

bool SGEXTN::Containers::Serialisation<unsigned int>::sendIn(unsigned int& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 4){return false;}
    x = (static_cast<unsigned int>(data.at(3)) << 24) | (static_cast<unsigned int>(data.at(2)) << 16) | (static_cast<unsigned int>(data.at(1)) << 8) | static_cast<unsigned int>(data.at(0));
    return true;
}

int SGEXTN::Containers::Serialisation<unsigned int>::sizeOut([[maybe_unused]] unsigned int x){
    return 4;
}

int SGEXTN::Containers::Serialisation<unsigned int>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 4){return -1;}
    return 4;
}

bool SGEXTN::Containers::Serialisation<long long>::sendOut(long long x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 8){return false;}
    const unsigned long long u = static_cast<unsigned long long>(x);
    data.at(0) = u & static_cast<unsigned char>(0xff);
    data.at(1) = (u >> 8) & static_cast<unsigned char>(0xff);
    data.at(2) = (u >> 16) & static_cast<unsigned char>(0xff);
    data.at(3) = (u >> 24) & static_cast<unsigned char>(0xff);
    data.at(4) = (u >> 32) & static_cast<unsigned char>(0xff);
    data.at(5) = (u >> 40) & static_cast<unsigned char>(0xff);
    data.at(6) = (u >> 48) & static_cast<unsigned char>(0xff);
    data.at(7) = (u >> 56) & static_cast<unsigned char>(0xff);
    return true;
}

bool SGEXTN::Containers::Serialisation<long long>::sendIn(long long& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 8){return false;}
    const unsigned long long u = (static_cast<unsigned long long>(data.at(7)) << 56) | (static_cast<unsigned long long>(data.at(6)) << 48) | (static_cast<unsigned long long>(data.at(5)) << 40) | (static_cast<unsigned long long>(data.at(4)) << 32) | (static_cast<unsigned long long>(data.at(3)) << 24) | (static_cast<unsigned long long>(data.at(2)) << 16) | (static_cast<unsigned long long>(data.at(1)) << 8) | static_cast<unsigned long long>(data.at(0));
    x = static_cast<long long>(u);
    return true;
}

int SGEXTN::Containers::Serialisation<long long>::sizeOut([[maybe_unused]] long long x){
    return 8;
}

int SGEXTN::Containers::Serialisation<long long>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 8){return -1;}
    return 8;
}

bool SGEXTN::Containers::Serialisation<unsigned long long>::sendOut(unsigned long long x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 8){return false;}
    data.at(0) = x & static_cast<unsigned char>(0xff);
    data.at(1) = (x >> 8) & static_cast<unsigned char>(0xff);
    data.at(2) = (x >> 16) & static_cast<unsigned char>(0xff);
    data.at(3) = (x >> 24) & static_cast<unsigned char>(0xff);
    data.at(4) = (x >> 32) & static_cast<unsigned char>(0xff);
    data.at(5) = (x >> 40) & static_cast<unsigned char>(0xff);
    data.at(6) = (x >> 48) & static_cast<unsigned char>(0xff);
    data.at(7) = (x >> 56) & static_cast<unsigned char>(0xff);
    return true;
}

bool SGEXTN::Containers::Serialisation<unsigned long long>::sendIn(unsigned long long& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 8){return false;}
    x = (static_cast<unsigned long long>(data.at(7)) << 56) | (static_cast<unsigned long long>(data.at(6)) << 48) | (static_cast<unsigned long long>(data.at(5)) << 40) | (static_cast<unsigned long long>(data.at(4)) << 32) | (static_cast<unsigned long long>(data.at(3)) << 24) | (static_cast<unsigned long long>(data.at(2)) << 16) | (static_cast<unsigned long long>(data.at(1)) << 8) | static_cast<unsigned long long>(data.at(0));
    return true;
}

int SGEXTN::Containers::Serialisation<unsigned long long>::sizeOut([[maybe_unused]] unsigned long long x){
    return 8;
}

int SGEXTN::Containers::Serialisation<unsigned long long>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 8){return -1;}
    return 8;
}

bool SGEXTN::Containers::Serialisation<float>::sendOut(float x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 4){return false;}
    const unsigned int sign = static_cast<unsigned int>(std::signbit(x));
    unsigned int exponent = 0;
    unsigned int mantissa = 0;
    if(std::isnan(x) == true){
        exponent = 0xff;
        mantissa = 0x400000;
    }
    else if(std::isinf(x)){exponent = 0xff;}
    else if(x != 0.0f){
        const int prelimExponent = std::ilogb(std::abs(x));
        if(prelimExponent < 1 - 0x7f){mantissa = static_cast<unsigned int>(std::round(std::scalbn(std::abs(x), 23 + 0x7f - 1)));}
        else{
            exponent = static_cast<unsigned int>(prelimExponent + 0x7f);
            const float scaledDownMantissa = std::scalbn(std::abs(x), (-1) * prelimExponent) - 1.0f;
            mantissa = static_cast<unsigned int>(std::round(std::scalbn(scaledDownMantissa, 23)));
        }
        if(mantissa > 0x7fffff){
            mantissa = mantissa & 0x7fffff;
            exponent++;
        }
    }
    const unsigned int packedBinary = (sign << 31) | (exponent << 23) | mantissa;
    return SGEXTN::Containers::Serialisation<unsigned int>::sendOut(packedBinary, data);
}

bool SGEXTN::Containers::Serialisation<float>::sendIn(float& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 4){return false;}
    unsigned int packedBinary = 0;
    const bool isSuccessful = SGEXTN::Containers::Serialisation<unsigned int>::sendIn(packedBinary, data);
    if(isSuccessful == false){return false;}
    const unsigned int sign = static_cast<int>((packedBinary & 0x80000000) >> 31);
    const unsigned int exponent = (packedBinary & 0x7f800000) >> 23;
    const unsigned int mantissa = packedBinary & 0x7fffff;
    float signMultiple = 1.0f;
    if(sign == 1){signMultiple = -1.0f;}
    if(exponent == 0xff){
        if(mantissa != 0){x = std::numeric_limits<float>::quiet_NaN();}
        else{x = signMultiple * std::numeric_limits<float>::infinity();}
    }
    else if(exponent == 0){
        if(mantissa == 0){x = signMultiple * 0.0f;}
        else{x = signMultiple * std::scalbn(static_cast<float>(mantissa), 1 - 23 - 0x7f);}
    }
    else{x = signMultiple * std::scalbn(1.0f + std::scalbn(static_cast<float>(mantissa), -23), static_cast<int>(exponent) - 0x7f);}
    return true;
}

int SGEXTN::Containers::Serialisation<float>::sizeOut([[maybe_unused]] float x){
    return 4;
}

int SGEXTN::Containers::Serialisation<float>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 4){return -1;}
    return 4;
}

bool SGEXTN::Containers::Serialisation<double>::sendOut(double x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 8){return false;}
    const unsigned long long sign = static_cast<unsigned long long>(std::signbit(x));
    unsigned long long exponent = 0;
    unsigned long long mantissa = 0;
    if(std::isnan(x) == true){
        exponent = 0x7ff;
        mantissa = 0x8000000000000ull;
    }
    else if(std::isinf(x)){exponent = 0x7ff;}
    else if(x != 0.0){
        const long long prelimExponent = std::ilogb(std::abs(x));
        if(prelimExponent < 1 - 0x3ff){mantissa = static_cast<unsigned long long>(std::round(std::scalbn(std::abs(x), 52 + 0x3ff - 1)));}
        else{
            exponent = static_cast<unsigned long long>(prelimExponent + 0x3ff);
            const double scaledDownMantissa = std::scalbn(std::abs(x), (-1) * static_cast<int>(prelimExponent)) - 1.0;
            mantissa = static_cast<unsigned long long>(std::round(std::scalbn(scaledDownMantissa, 52)));
        }
        if(mantissa > 0xfffffffffffffull){
            mantissa = mantissa & 0xfffffffffffffull;
            exponent++;
        }
    }
    const unsigned long long packedBinary = (sign << 63) | (exponent << 52) | mantissa;
    return SGEXTN::Containers::Serialisation<unsigned long long>::sendOut(packedBinary, data);
}

bool SGEXTN::Containers::Serialisation<double>::sendIn(double& x, SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() != 8){return false;}
    unsigned long long packedBinary = 0;
    const bool isSuccessful = SGEXTN::Containers::Serialisation<unsigned long long>::sendIn(packedBinary, data);
    if(isSuccessful == false){return false;}
    const unsigned long long sign = static_cast<int>((packedBinary & 0x8000000000000000ull) >> 63);
    const unsigned long long exponent = (packedBinary & 0x7ff0000000000000ull) >> 52;
    const unsigned long long mantissa = packedBinary & 0xfffffffffffffull;
    double signMultiple = 1.0;
    if(sign == 1){signMultiple = -1.0;}
    if(exponent == 0x7ff){
        if(mantissa != 0){x = std::numeric_limits<double>::quiet_NaN();}
        else{x = signMultiple * std::numeric_limits<double>::infinity();}
    }
    else if(exponent == 0){
        if(mantissa == 0){x = signMultiple * 0.0;}
        else{x = signMultiple * std::scalbn(static_cast<double>(mantissa), 1 - 52 - 0x3ff);}
    }
    else{x = signMultiple * std::scalbn(1.0 + std::scalbn(static_cast<double>(mantissa), -52), static_cast<int>(exponent) - 0x3ff);}
    return true;
}

int SGEXTN::Containers::Serialisation<double>::sizeOut([[maybe_unused]] double x){
    return 8;
}

int SGEXTN::Containers::Serialisation<double>::sizeIn(SGEXTN::Containers::Span<unsigned char> data){
    if(data.length() < 8){return -1;}
    return 8;
}
