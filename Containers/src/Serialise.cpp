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

#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Array.h>
#include <cmath>
#include <limits>

void SGEXTN::Containers::MemoryCopySerialise::copySection(SGEXTN::Containers::Array<unsigned char>& mainArray, int& offset, const SGEXTN::Containers::Array<unsigned char>& section){
    for(int i=0; i<section.length(); i++){
        mainArray.at(offset + i) = section.at(i);
    }
    offset += section.length();
}

void SGEXTN::Containers::MemoryCopySerialise::copyOutSection(const SGEXTN::Containers::Array<unsigned char>& mainArray, int& offset, SGEXTN::Containers::Array<unsigned char>& destination){
    for(int i=0; i<destination.length(); i++){
        destination.at(i) = mainArray.at(offset + i);
    }
    offset += destination.length();
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<bool>::serialise(bool x){
    if(x == false){return SGEXTN::Containers::Array<unsigned char>(1, static_cast<unsigned char>(0));}
    return SGEXTN::Containers::Array<unsigned char>(1, static_cast<unsigned char>(1));
}

bool SGEXTN::Containers::Serialise<bool>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 1 || static_cast<unsigned int>(data.at(0)) > 1){
        if(success != nullptr){(*success) = false;}
        return false;
    }
    if(success != nullptr){(*success) = true;}
    bool output = false;
    if(data.at(0) == static_cast<unsigned char>(1)){output = true;}
    return output;
}

int SGEXTN::Containers::Serialise<bool>::lengthof([[maybe_unused]] bool x){
    return 1;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<unsigned char>::serialise(unsigned char x){
    return SGEXTN::Containers::Array<unsigned char>(1, x);
}

unsigned char SGEXTN::Containers::Serialise<unsigned char>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 1){
        if(success != nullptr){(*success) = false;}
        return static_cast<unsigned char>(0);
    }
    if(success != nullptr){(*success) = true;}
    return data.at(0);
}

int SGEXTN::Containers::Serialise<unsigned char>::lengthof([[maybe_unused]] unsigned char x){
    return 1;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<short>::serialise(short x){
    SGEXTN::Containers::Array<unsigned char> outputArray(2);
    const unsigned short convertedUnsigned = static_cast<unsigned short>(x);
    outputArray.at(0) = convertedUnsigned & static_cast<unsigned char>(0xff);
    outputArray.at(1) = (convertedUnsigned >> 8) & static_cast<unsigned char>(0xff);
    return outputArray;
}

short SGEXTN::Containers::Serialise<short>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 2){
        if(success != nullptr){(*success) = false;}
        return 0;
    }
    if(success != nullptr){(*success) = true;}
    const unsigned short outputUnsigned = (static_cast<unsigned short>(data.at(1)) << 8) | static_cast<unsigned short>(data.at(0));
    return static_cast<short>(outputUnsigned);
}

int SGEXTN::Containers::Serialise<short>::lengthof([[maybe_unused]] short x){
    return 2;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<unsigned short>::serialise(unsigned short x){
    SGEXTN::Containers::Array<unsigned char> outputArray(2);
    outputArray.at(0) = x & static_cast<unsigned char>(0xff);
    outputArray.at(1) = (x >> 8) & static_cast<unsigned char>(0xff);
    return outputArray;
}

unsigned short SGEXTN::Containers::Serialise<unsigned short>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 2){
        if(success != nullptr){(*success) = false;}
        return 0;
    }
    if(success != nullptr){(*success) = true;}
    return ((static_cast<unsigned short>(data.at(1)) << 8) | (static_cast<unsigned short>(data.at(0))));
}

int SGEXTN::Containers::Serialise<unsigned short>::lengthof([[maybe_unused]] unsigned short x){
    return 2;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<int>::serialise(int x){
    SGEXTN::Containers::Array<unsigned char> outputArray(4);
    const unsigned int convertedUnsigned = static_cast<unsigned int>(x);
    outputArray.at(0) = convertedUnsigned & 0xff;
    outputArray.at(1) = (convertedUnsigned >> 8) & 0xff;
    outputArray.at(2) = (convertedUnsigned >> 16) & 0xff;
    outputArray.at(3) = (convertedUnsigned >> 24) & 0xff;
    return outputArray;
}

int SGEXTN::Containers::Serialise<int>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 4){
        if(success != nullptr){(*success) = false;}
        return 0;
    }
    if(success != nullptr){(*success) = true;}
    const unsigned int outputUnsigned = (static_cast<unsigned int>(data.at(3)) << 24) | (static_cast<unsigned int>(data.at(2)) << 16) | (static_cast<unsigned int>(data.at(1)) << 8) | static_cast<unsigned int>(data.at(0));
    return static_cast<int>(outputUnsigned);
}

int SGEXTN::Containers::Serialise<int>::lengthof([[maybe_unused]] int x){
    return 4;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<unsigned int>::serialise(unsigned int x){
    SGEXTN::Containers::Array<unsigned char> outputArray(4);
    outputArray.at(0) = x & 0xff;
    outputArray.at(1) = (x >> 8) & 0xff;
    outputArray.at(2) = (x >> 16) & 0xff;
    outputArray.at(3) = (x >> 24) & 0xff;
    return outputArray;
}

unsigned int SGEXTN::Containers::Serialise<unsigned int>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 4){
        if(success != nullptr){(*success) = false;}
        return 0;
    }
    if(success != nullptr){(*success) = true;}
    return ((static_cast<unsigned int>(data.at(3)) << 24) | (static_cast<unsigned int>(data.at(2)) << 16) | (static_cast<unsigned int>(data.at(1)) << 8) | static_cast<unsigned int>(data.at(0)));
}

int SGEXTN::Containers::Serialise<unsigned int>::lengthof([[maybe_unused]] unsigned int x){
    return 4;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<long long>::serialise(long long x){
    SGEXTN::Containers::Array<unsigned char> outputArray(8);
    const unsigned long long convertedUnsigned = static_cast<unsigned long long>(x);
    outputArray.at(0) = convertedUnsigned & 0xff;
    outputArray.at(1) = (convertedUnsigned >> 8) & 0xff;
    outputArray.at(2) = (convertedUnsigned >> 16) & 0xff;
    outputArray.at(3) = (convertedUnsigned >> 24) & 0xff;
    outputArray.at(4) = (convertedUnsigned >> 32) & 0xff;
    outputArray.at(5) = (convertedUnsigned >> 40) & 0xff;
    outputArray.at(6) = (convertedUnsigned >> 48) & 0xff;
    outputArray.at(7) = (convertedUnsigned >> 56) & 0xff;
    return outputArray;
}

long long SGEXTN::Containers::Serialise<long long>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 8){
        if(success != nullptr){(*success) = false;}
        return 0;
    }
    if(success != nullptr){(*success) = true;}
    const unsigned long long outputUnsigned = (static_cast<unsigned long long>(data.at(7)) << 56) | (static_cast<unsigned long long>(data.at(6)) << 48) | (static_cast<unsigned long long>(data.at(5)) << 40) | (static_cast<unsigned long long>(data.at(4)) << 32) | (static_cast<unsigned long long>(data.at(3)) << 24) | (static_cast<unsigned long long>(data.at(2)) << 16) | (static_cast<unsigned long long>(data.at(1)) << 8) | static_cast<unsigned long long>(data.at(0));
    return static_cast<long long>(outputUnsigned);
}

int SGEXTN::Containers::Serialise<long long>::lengthof([[maybe_unused]] long long x){
    return 8;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<unsigned long long>::serialise(unsigned long long x){
    SGEXTN::Containers::Array<unsigned char> outputArray(8);
    outputArray.at(0) = x & 0xff;
    outputArray.at(1) = (x >> 8) & 0xff;
    outputArray.at(2) = (x >> 16) & 0xff;
    outputArray.at(3) = (x >> 24) & 0xff;
    outputArray.at(4) = (x >> 32) & 0xff;
    outputArray.at(5) = (x >> 40) & 0xff;
    outputArray.at(6) = (x >> 48) & 0xff;
    outputArray.at(7) = (x >> 56) & 0xff;
    return outputArray;
}

unsigned long long SGEXTN::Containers::Serialise<unsigned long long>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    if(data.length() != 8){
        if(success != nullptr){(*success) = false;}
        return 0;
    }
    if(success != nullptr){(*success) = true;}
    return ((static_cast<unsigned long long>(data.at(7)) << 56) | (static_cast<unsigned long long>(data.at(6)) << 48) | (static_cast<unsigned long long>(data.at(5)) << 40) | (static_cast<unsigned long long>(data.at(4)) << 32) | (static_cast<unsigned long long>(data.at(3)) << 24) | (static_cast<unsigned long long>(data.at(2)) << 16) | (static_cast<unsigned long long>(data.at(1)) << 8) | static_cast<unsigned long long>(data.at(0)));
}

int SGEXTN::Containers::Serialise<unsigned long long>::lengthof([[maybe_unused]] unsigned long long x){
    return 8;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<float>::serialise(float x){
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
    return SGEXTN::Containers::Serialise<unsigned int>::serialise(packedBinary);
}

float SGEXTN::Containers::Serialise<float>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    bool isSuccessful = false;
    const unsigned int packedBinary = SGEXTN::Containers::Serialise<unsigned int>::unserialise(data, &isSuccessful);
    if(isSuccessful == false){
        if(success != nullptr){(*success) = false;}
        return 0.0f;
    }
    if(success != nullptr){(*success) = true;}
    const unsigned int sign = static_cast<int>((packedBinary & 0x80000000) >> 31);
    const unsigned int exponent = (packedBinary & 0x7f800000) >> 23;
    const unsigned int mantissa = packedBinary & 0x7fffff;
    if(exponent == 0xff){
        if(mantissa != 0){return std::numeric_limits<float>::quiet_NaN();}
        if(sign == 1){return (-1.0f * std::numeric_limits<float>::infinity());}
        return std::numeric_limits<float>::infinity();
    }
    if(exponent == 0){
        if(mantissa == 0){
            if(sign == 1){return -0.0f;}
            return 0.0f;
        }
        if(sign == 1){return (-1.0f * std::scalbn(static_cast<float>(mantissa), 1 - 23 - 0x7f));}
        return std::scalbn(static_cast<float>(mantissa), 1 - 23 - 0x7f);
    }
    if(sign == 1){return (-1.0f * std::scalbn(1.0f + std::scalbn(static_cast<float>(mantissa), -23), static_cast<int>(exponent) - 0x7f));}
    return std::scalbn(1.0f + std::scalbn(static_cast<float>(mantissa), -23), static_cast<int>(exponent) - 0x7f);
}

int SGEXTN::Containers::Serialise<float>::lengthof([[maybe_unused]] float x){
    return 4;
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::Containers::Serialise<double>::serialise(double x){
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
    return SGEXTN::Containers::Serialise<unsigned long long>::serialise(packedBinary);
}

double SGEXTN::Containers::Serialise<double>::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool* success){
    bool isSuccessful = false;
    const unsigned long long packedBinary = SGEXTN::Containers::Serialise<unsigned long long>::unserialise(data, &isSuccessful);
    if(isSuccessful == false){
        if(success != nullptr){(*success) = false;}
        return 0.0;
    }
    if(success != nullptr){(*success) = true;}
    const unsigned long long sign = static_cast<int>((packedBinary & 0x8000000000000000ull) >> 63);
    const unsigned long long exponent = (packedBinary & 0x7ff0000000000000ull) >> 52;
    const unsigned long long mantissa = packedBinary & 0xfffffffffffffull;
    if(exponent == 0x7ff){
        if(mantissa != 0){return std::numeric_limits<double>::quiet_NaN();}
        if(sign == 1){return (-1.0 * std::numeric_limits<double>::infinity());}
        return std::numeric_limits<double>::infinity();
    }
    if(exponent == 0){
        if(mantissa == 0){
            if(sign == 1){return -0.0;}
            return 0.0;
        }
        if(sign == 1){return (-1.0 * std::scalbn(static_cast<double>(mantissa), 1 - 52 - 0x3ff));}
        return std::scalbn(static_cast<double>(mantissa), 1 - 52 - 0x3ff);
    }
    if(sign == 1){return (-1.0 * std::scalbn(1.0 + std::scalbn(static_cast<double>(mantissa), -52), static_cast<int>(exponent) - 0x3ff));}
    return std::scalbn(1.0 + std::scalbn(static_cast<double>(mantissa), -52), static_cast<int>(exponent) - 0x3ff);
}

int SGEXTN::Containers::Serialise<double>::lengthof([[maybe_unused]] double x){
    return 8;
}
