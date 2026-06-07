#include <SGEXTN_CoreText_UnicodeQuery.h>
#include <SGEXTN_Math_FloatLimits.h>
#include <SGEXTN_CoreText_String.h>
#include <SGEXTN_CoreText_Character.h>

namespace {
// NOLINTBEGIN(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays, cppcoreguidelines-pro-bounds-constant-array-index)
int getLowercaseOffset(int i){
    if(i >= 0x41 && i < 0x5b){return 32;}
    if(i < 0x80){return 0;}
    if(i >= 0x4e00 && i <= 0x9fff){return 0;}
    if(i >= 0xb80 && i <= 0xbff){return 0;}
    if(i >= 0x2190 && i <= 0x23ff){return 0;}
    if(i >= 0xa0 && i <= 0x24f){
        if(i >= 0xc0 && i < 0xdf && i != 0xd7){return 32;}
        if(i == 0x130){return -199;}
        if(i >= 0x100 && i < 0x138 && i % 2 == 0){return 1;}
        if(i >= 0x138 && i < 0x149 && i % 2 == 1){return 1;}
        if(i >= 0x149 && i < 0x178 && i % 2 == 0){return 1;}
        if(i == 0x178){return -121;}
        if(i >= 0x179 && i < 0x17e && i % 2 == 1){return 1;}
        if(i == 0x181){return 210;}
        if(i == 0x182 || i == 0x184){return 1;}
        if(i == 0x186){return 206;}
        if(i == 0x187){return 1;}
        if(i >= 0x189 && i < 0x18b){return 205;}
        if(i == 0x18b){return 1;}
        if(i == 0x18e){return 79;}
        if(i == 0x18f){return 202;}
        if(i == 0x190){return 203;}
        if(i == 0x191){return 1;}
        if(i == 0x193){return 205;}
        if(i == 0x194){return 207;}
        if(i == 0x196){return 211;}
        if(i == 0x197){return 209;}
        if(i == 0x198){return 1;}
        if(i == 0x19c){return 211;}
        if(i == 0x19d){return 213;}
        if(i == 0x19f){return 214;}
        if(i >= 0x1a0 && i < 0x1a5 && i % 2 == 0){return 1;}
        if(i == 0x1a6){return 218;}
        if(i == 0x1a7){return 1;}
        if(i == 0x1a9){return 218;}
        if(i == 0x1ac){return 1;}
        if(i == 0x1ae){return 218;}
        if(i == 0x1af){return 1;}
        if(i >= 0x1b1 && i < 0x1b3){return 217;}
        if(i == 0x1b3 || i == 0x1b5){return 1;}
        if(i == 0x1b7){return 219;}
        if(i == 0x1b8 || i == 0x1bc){return 1;}
        if(i == 0x1c4 || i == 0x1c7 || i == 0x1ca){return 2;}
        if(i == 0x1c5 || i == 0x1c8){return 1;}
        if(i >= 0x1cb && i < 0x1dd && i % 2 == 1){return 1;}
        if(i >= 0x1dd && i < 0x1f0 && i % 2 == 0){return 1;}
        if(i == 0x1f1){return 2;}
        if(i == 0x1f2 || i == 0x1f4){return 1;}
        if(i == 0x1f6){return -97;}
        if(i == 0x1f7){return -56;}
        if(i == 0x220){return -130;}
        if(i >= 0x1f8 && i < 0x234 && i % 2 == 0){return 1;}
        if(i == 0x23a){return 10795;}
        if(i == 0x23b){return 1;}
        if(i == 0x23d){return -163;}
        if(i == 0x23e){return 10792;}
        if(i == 0x241){return 1;}
        if(i == 0x243){return -195;}
        if(i == 0x244){return 69;}
        if(i == 0x245){return 71;}
        if(i >= 0x246 && i < 0x24f && i % 2 == 0){return 1;}
        return 0;
    }
    if(i >= 0x370 && i <= 0x58f){
        if(i >= 0x370 && i < 0x377 && i % 2 == 0 && i != 0x374){return 1;}
        if(i == 0x37f){return 116;}
        if(i == 0x386){return 38;}
        if(i >= 0x388 && i < 0x38b){return 37;}
        if(i == 0x38c){return 64;}
        if(i >= 0x38e && i < 0x390){return 63;}
        if(i >= 0x391 && i < 0x3ac && i != 0x3a2){return 32;}
        if(i == 0x3cf){return 8;}
        if(i >= 0x3d8 && i < 0x3ef && i % 2 == 0){return 1;}
        if(i == 0x3f4){return -60;}
        if(i == 0x3f7 || i == 0x3fa){return 1;}
        if(i == 0x3f9){return -7;}
        if(i >= 0x3fd && i < 0x400){return -130;}
        if(i >= 0x400 && i < 0x410){return 80;}
        if(i >= 0x410 && i < 0x430){return 32;}
        if(i >= 0x460 && i < 0x482 && i % 2 == 0){return 1;}
        if(i >= 0x489 && i < 0x4c0 && i % 2 == 0){return 1;}
        if(i == 0x4c0){return 15;}
        if(i >= 0x4c0 && i < 0x4cf && i % 2 == 1){return 1;}
        if(i >= 0x4cf && i < 0x530 && i % 2 == 0){return 1;}
        if(i >= 0x531 && i < 0x557){return 48;}
        return 0;
    }
    if(i >= 0x10a0 && i <= 0x10ff){
        if(i >= 0x10a0 && i < 0x10c6){return 7264;}
        if(i == 0x10c7){return 7264;}
        if(i == 0x10cd){return 7264;}
        return 0;
    }
    if(i >= 0x13a0 && i <= 0x13ff){
        if(i >= 0x13a0 && i < 0x13f0){return 38864;}
        if(i >= 0x13f0 && i < 0x13f6){return 8;}
        return 0;
    }
    if(i >= 0x1c80 && i <= 0x1cbf){
        if(i == 0x1c89){return 1;}
        if(i >= 0x1c90 && i < 0x1cbb){return -3008;}
        if(i >= 0x1cbd && i < 0x1cc0){return -3008;}
        return 0;
    }
    if(i >= 0x1e00 && i <= 0x1fff){
        if(i >= 0x1e00 && i < 0x1e96 && i % 2 == 0){return 1;}
        if(i == 0x1e9e){return -7615;}
        if(i >= 0x1e9d && i < 0x1eff && i % 2 == 0){return 1;}
        if(i >= 0x1f08 && i < 0x1f10){return -8;}
        if(i >= 0x1f18 && i < 0x1f1e){return -8;}
        if(i >= 0x1f28 && i < 0x1f30){return -8;}
        if(i >= 0x1f38 && i < 0x1f40){return -8;}
        if(i >= 0x1f48 && i < 0x1f4e){return -8;}
        if(i >= 0x1f59 && i < 0x1f60 && i % 2 == 1){return -8;}
        if(i >= 0x1f68 && i < 0x1f70){return -8;}
        if(i >= 0x1f88 && i < 0x1f90){return -8;}
        if(i >= 0x1f98 && i < 0x1fa0){return -8;}
        if(i >= 0x1fa8 && i < 0x1fb0){return -8;}
        if(i >= 0x1fb8 && i < 0x1fba){return -8;}
        if(i >= 0x1fba && i < 0x1fbc){return -74;}
        if(i == 0x1fbc){return -9;}
        if(i >= 0x1fc8 && i < 0x1fcc){return -86;}
        if(i == 0x1fcc){return -9;}
        if(i >= 0x1fd8 && i < 0x1fda){return -8;}
        if(i >= 0x1fda && i < 0x1fdc){return -100;}
        if(i >= 0x1fe8 && i < 0x1fea){return -8;}
        if(i >= 0x1fea && i < 0x1fec){return -112;}
        if(i == 0x1fec){return -7;}
        if(i >= 0x1ff8 && i < 0x1ffa){return -128;}
        if(i >= 0x1ffa && i < 0x1ffc){return -126;}
        if(i == 0x1ffc){return -9;}
        return 0;
    }
    if(i >= 0x2100 && i <= 0x218f){
        if(i == 0x2126){return -7517;}
        if(i == 0x212a){return -8383;}
        if(i == 0x212b){return -8262;}
        if(i == 0x2132){return 28;}
        if(i >= 0x2160 && i < 0x2170){return 16;}
        if(i == 0x2183){return 1;}
        return 0;
    }
    if(i >= 0x24b6 && i < 0x24d0){return 26;}
    if(i >= 0x2c00 && i < 0x2c30){return 48;}
    if(i >= 0x2c60 && i <= 0x2cff){
        if(i == 0x2c60){return 1;}
        if(i == 0x2c62){return -10743;}
        if(i == 0x2c63){return -3814;}
        if(i == 0x2c64){return -10727;}
        if(i >= 0x2c67 && i < 0x2c6c && i % 2 == 1){return 1;}
        if(i == 0x2c6d){return -10780;}
        if(i == 0x2c6e){return -10749;}
        if(i == 0x2c6f){return -10783;}
        if(i == 0x2c70){return -10782;}
        if(i == 0x2c72 || i == 0x2c75){return 1;}
        if(i >= 0x2c7e && i < 0x2c80){return -10815;}
        if(i >= 0x2c80 && i < 0x2ce4 && i % 2 == 0){return 1;}
        if(i == 0x2ceb){return 1;}
        if(i == 0x2ced){return 1;}
        if(i == 0x2cf2){return 1;}
        return 0;
    }
    if(i >= 0xa640 && i <= 0xa69f){
        if(i >= 0xa640 && i < 0xa66e && i % 2 == 0){return 1;}
        if(i >= 0xa680 && i < 0xa69b && i % 2 == 0){return 1;}
        return 0;
    }
    if(i >= 0xa720 && i <= 0xa7ff){
        if(i >= 0xa722 && i < 0xa76f && i % 2 == 0 && i != 0xa730){return 1;}
        if(i == 0xa779 || i == 0xa77b){return 1;}
        if(i == 0xa77d){return -35332;}
        if(i >= 0xa77e && i < 0xa787 && i % 2 == 0){return 1;}
        if(i == 0xa78b){return 1;}
        if(i == 0xa78d){return -42280;}
        if(i == 0xa790 || i == 0xa792){return 1;}
        if(i >= 0xa796 && i < 0xa7a9 && i % 2 == 0){return 1;}
        if(i == 0xa7aa){return -42308;}
        if(i == 0xa7ab){return -42319;}
        if(i == 0xa7ac){return -42315;}
        if(i == 0xa7ad){return -42305;}
        if(i == 0xa7ae){return -42308;}
        if(i == 0xa7b0){return -42258;}
        if(i == 0xa7b1){return -42282;}
        if(i == 0xa7b2){return -42261;}
        if(i == 0xa7b3){return 928;}
        if(i >= 0xa7b4 && i < 0xa7c3 && i % 2 == 0){return 1;}
        if(i == 0xa7c4){return -48;}
        if(i == 0xa7c5){return -42307;}
        if(i == 0xa7c6){return -35384;}
        if(i == 0xa7c7 || i == 0xa7c9){return 1;}
        if(i == 0xa7cb){return -42343;}
        if(i >= 0xa7cc && i < 0xa7db && i % 2 == 0){return 1;}
        if(i == 0xa7dc){return -42561;}
        if(i == 0xa7f5){return 1;}
        return 0;
    }
    if(i >= 0xff21 && i < 0xff3b){return 32;}
    if(i >= 0x10400 && i < 0x10428){return 40;}
    if(i >= 0x104b0 && i < 0x104d4){return 40;}
    if(i >= 0x10570 && i < 0x10596 && i != 0x1057b && i != 0x1058b && i != 0x10593){return 39;}
    if(i >= 0x10c80 && i < 0x10cb3){return 64;}
    if(i >= 0x10d50 && i < 0x10d66){return 32;}
    if(i >= 0x118a0 && i < 0x118c0){return 32;}
    if(i >= 0x16e40 && i < 0x16e60){return 32;}
    if(i >= 0x16ea0 && i < 0x16eb9){return 27;}
    if(i >= 0x1e900 && i < 0x1e922){return 34;}
    return 0;
}

int getUppercaseOffset(int i){
    if(i >= 0x61 && i < 0x7b){return -32;}
    if(i < 0x80){return 0;}
    if(i >= 0x4e00 && i <= 0x9fff){return 0;}
    if(i >= 0xb80 && i <= 0xbff){return 0;}
    if(i >= 0x2190 && i <= 0x23ff){return 0;}
    if(i >= 0xa0 && i <= 0x2af){
        if(i == 0xb5){return 743;}
        if(i >= 0xe0 && i < 0xf7){return -32;}
        if(i >= 0xf8 && i < 0xff){return -32;}
        if(i == 0xff){return 121;}
        if(i == 0x131){return -232;}
        if(i >= 0x101 && i < 0x138 && i % 2 == 1){return -1;}
        if(i >= 0x13a && i < 0x149 && i % 2 == 0){return -1;}
        if(i >= 0x14b && i < 0x178 && i % 2 == 1){return -1;}
        if(i >= 0x17a && i < 0x17f && i % 2 == 0){return -1;}
        if(i == 0x17f){return -300;}
        if(i == 0x180){return 195;}
        if(i == 0x183 || i == 0x185){return -1;}
        if(i == 0x188 || i == 0x18c || i == 0x192){return -1;}
        if(i == 0x195){return 97;}
        if(i == 0x199){return -1;}
        if(i == 0x19a){return 163;}
        if(i == 0x19b){return 42561;}
        if(i == 0x19e){return 130;}
        if(i >= 0x1a1 && i < 0x1a6 && i % 2 == 1){return -1;}
        if(i == 0x1a8 || i == 0x1ad || i == 0x1b0){return -1;}
        if(i == 0x1b4 || i == 0x1b6){return -1;}
        if(i == 0x1b9 || i == 0x1bd){return -1;}
        if(i == 0x1bf){return 56;}
        if(i == 0x1c5){return -1;}
        if(i == 0x1c6){return -2;}
        if(i == 0x1c8 || i == 0x1cb){return -1;}
        if(i == 0x1c9 || i == 0x1cc){return -2;}
        if(i >= 0x1ce && i < 0x1dd && i % 2 == 0){return -1;}
        if(i == 0x1dd){return -79;}
        if(i >= 0x1df && i <= 0x1f0 && i % 2 == 1){return -1;}
        if(i == 0x1f2 || i == 0x1f5){return -1;}
        if(i == 0x1f3){return -2;}
        if(i >= 0x1f9 && i < 0x234 && i % 2 == 1 && i != 0x221){return -1;}
        if(i == 0x23c || i == 0x242){return -1;}
        if(i >= 0x23f && i < 0x241){return 10815;}
        if(i >= 0x247 && i < 0x250 && i % 2 == 1){return -1;}
        if(i == 0x250){return 10783;}
        if(i == 0x251){return 10780;}
        if(i == 0x252){return 10782;}
        if(i == 0x253){return -210;}
        if(i == 0x254){return -206;}
        if(i >= 0x256 && i < 0x258){return -205;}
        if(i == 0x259){return -202;}
        if(i == 0x25b){return -203;}
        if(i == 0x25c){return 42319;}
        if(i == 0x260){return -205;}
        if(i == 0x261){return 42315;}
        if(i == 0x263){return -207;}
        if(i == 0x264){return 42343;}
        if(i == 0x265){return 42280;}
        if(i == 0x266){return 42308;}
        if(i == 0x268){return -209;}
        if(i == 0x269){return -211;}
        if(i == 0x26a){return 42308;}
        if(i == 0x26b){return 10743;}
        if(i == 0x26c){return 42305;}
        if(i == 0x26f){return -211;}
        if(i == 0x271){return 10749;}
        if(i == 0x272){return -213;}
        if(i == 0x275){return -214;}
        if(i == 0x27d){return 10727;}
        if(i == 0x280){return -218;}
        if(i == 0x282){return 42307;}
        if(i == 0x283){return -218;}
        if(i == 0x287){return 42282;}
        if(i == 0x288){return -218;}
        if(i == 0x289){return -69;}
        if(i >= 0x28a && i < 0x28c){return -217;}
        if(i == 0x28c){return -71;}
        if(i == 0x292){return -219;}
        if(i == 0x29d){return 42261;}
        if(i == 0x29e){return 42258;}
        return 0;
    }
    if(i == 0x345){return 84;}
    if(i >= 0x370 && i <= 0x58f){
        if(i == 0x371 || i == 0x373 || i == 0x377){return -1;}
        if(i >= 0x37b && i < 0x37e){return 130;}
        if(i == 0x3ac){return -38;}
        if(i >= 0x3ad && i < 0x3b0){return -37;}
        if(i >= 0x3b1 && i < 0x3c2){return -32;}
        if(i == 0x3c2){return -31;}
        if(i >= 0x3c3 && i < 0x3cc){return -32;}
        if(i == 0x3cc){return -64;}
        if(i >= 0x3cd && i < 0x3cf){return -63;}
        if(i == 0x3d0){return -62;}
        if(i == 0x3d1){return -57;}
        if(i == 0x3d5){return -47;}
        if(i == 0x3d6){return -54;}
        if(i == 0x3d7){return -8;}
        if(i >= 0x3d9 && i < 0x3f0 && i % 2 == 1){return -1;}
        if(i == 0x3f0){return -86;}
        if(i == 0x3f1){return -80;}
        if(i == 0x3f2){return 7;}
        if(i == 0x3f3){return -116;}
        if(i == 0x3f5){return -96;}
        if(i == 0x3f8 || i == 0x3fb){return -1;}
        if(i >= 0x430 && i < 0x450){return -32;}
        if(i >= 0x450 && i < 0x460){return -80;}
        if(i >= 0x461 && i < 0x482 && i % 2 == 1){return -1;}
        if(i >= 0x48b && i < 0x4c0 && i % 2 == 1){return -1;}
        if(i >= 0x4c2 && i < 0x4cf && i % 2 == 0){return -1;}
        if(i == 0x4cf){return -15;}
        if(i >= 0x4d1 && i < 0x530 && i % 2 == 1){return -1;}
        if(i >= 0x561 && i < 0x587){return -48;}
        return 0;
    }
    if(i >= 0x10a0 && i <= 0x10ff){
        if(i >= 0x10d0 && i < 0x10fb){return 3008;}
        if(i >= 0x10fd && i < 0x1100){return 3008;}
        return 0;
    }
    if(i >= 0x13f8 && i < 0x13fe){return -8;}
    if(i >= 0x1c80 && i <= 0x1cbf){
        if(i == 0x1c80){return -6254;}
        if(i == 0x1c81){return -6253;}
        if(i == 0x1c82){return -6244;}
        if(i >= 0x1c83 && i < 0x1c85){return -6242;}
        if(i == 0x1c85){return -6243;}
        if(i == 0x1c86){return -6236;}
        if(i == 0x1c87){return -6181;}
        if(i == 0x1c88){return 35266;}
        if(i == 0x1c8a){return -1;}
        return 0;
    }
    if(i == 0x1d79){return 35332;}
    if(i == 0x1d7d){return 3814;}
    if(i == 0x1d8e){return 35384;}
    if(i >= 0x1e00 && i <= 0x1fff){
        if(i >= 0x1e01 && i < 0x1e96 && i % 2 == 1){return -1;}
        if(i == 0x1e9b){return -59;}
        if(i >= 0x1ea1 && i < 0x1f00 && i % 2 == 1){return -1;}
        if(i >= 0x1f00 && i < 0x1f08){return 8;}
        if(i >= 0x1f10 && i < 0x1f16){return 8;}
        if(i >= 0x1f20 && i < 0x1f28){return 8;}
        if(i >= 0x1f30 && i < 0x1f38){return 8;}
        if(i >= 0x1f40 && i < 0x1f46){return 8;}
        if(i >= 0x1f51 && i < 0x1f58 && i % 2 == 1){return 8;}
        if(i >= 0x1f60 && i < 0x1f68){return 8;}
        if(i >= 0x1f70 && i < 0x1f72){return 74;}
        if(i >= 0x1f72 && i < 0x1f76){return 86;}
        if(i >= 0x1f76 && i < 0x1f78){return 100;}
        if(i >= 0x1f78 && i < 0x1f7a){return 128;}
        if(i >= 0x1f7a && i < 0x1f7c){return 112;}
        if(i >= 0x1f7c && i < 0x1f7e){return 126;}
        if(i >= 0x1f80 && i < 0x1f88){return 8;}
        if(i >= 0x1f90 && i < 0x1f98){return 8;}
        if(i >= 0x1fa0 && i < 0x1fa8){return 8;}
        if(i >= 0x1fb0 && i < 0x1fb2){return 8;}
        if(i == 0x1fb3 || i == 0x1fc3){return 9;}
        if(i == 0x1fbe){return -7205;}
        if(i >= 0x1fd0 && i < 0x1fd2){return 8;}
        if(i >= 0x1fe0 && i < 0x1fe2){return 8;}
        if(i == 0x1fe5){return 7;}
        if(i == 0x1ff3){return 9;}
        return 0;
    }
    if(i >= 0x2100 && i <= 0x218f){
        if(i == 0x214e){return -28;}
        if(i >= 0x2170 && i < 0x2180){return -16;}
        if(i == 0x2184){return -1;}
        return 0;
    }
    if(i >= 0x24d0 && i < 0x24ea){return -26;}
    if(i >= 0x2c30 && i < 0x2c60){return -48;}
    if(i >= 0x2c60 && i <= 0x2cff){
        if(i == 0x2c61){return -1;}
        if(i == 0x2c65){return -10795;}
        if(i == 0x2c66){return -10792;}
        if(i >= 0x2c68 && i < 0x2c6d && i % 2 == 0){return -1;}
        if(i == 0x2c73 || i == 0x2c76){return -1;}
        if(i >= 0x2c81 && i < 0x2ce4 && i % 2 == 1){return -1;}
        if(i == 0x2cec || i == 0x2cee || i == 0x2cf3){return -1;}
        return 0;
    }
    if(i >= 0x2d00 && i < 0x2d26){return -7264;}
    if(i == 0x2d27 || i == 0x2d2d){return -7264;}
    if(i >= 0xa640 && i <= 0xa69f){
        if(i >= 0xa641 && i < 0xa66e && i % 2 == 1){return -1;}
        if(i >= 0xa681 && i < 0xa69c && i % 2 == 1){return -1;}
        return 0;
    }
    if(i >= 0xa720 && i <= 0xa7ff){
        if(i >= 0xa723 && i < 0xa770 && i % 2 == 1 && i != 0xa731){return -1;}
        if(i == 0xa77a || i == 0xa77c){return -1;}
        if(i >= 0xa77f && i < 0xa788 && i % 2 == 1){return -1;}
        if(i == 0xa78c || i == 0xa791 || i == 0xa793){return -1;}
        if(i == 0xa794){return 48;}
        if(i >= 0xa797 && i < 0xa7aa && i % 2 == 1){return -1;}
        if(i >= 0xa7b5 && i < 0xa7c4 && i % 2 == 1){return -1;}
        if(i == 0xa7c8 || i == 0xa7ca){return -1;}
        if(i >= 0xa7cd && i < 0xa7dc && i % 2 == 1){return -1;}
        if(i == 0xa7f6){return -1;}
        return 0;
    }
    if(i == 0xab53){return -928;}
    if(i >= 0xab70 && i < 0xabc0){return -38864;}
    if(i >= 0xff41 && i < 0xff5b){return -32;}
    if(i >= 0x10428 && i < 0x10450){return -40;}
    if(i >= 0x104d8 && i < 0x104fc){return -40;}
    if(i >= 0x10597 && i < 0x105bd && i != 0x105a2 && i != 0x105b2 && i != 0x105ba){return -39;}
    if(i >= 0x10cc0 && i < 0x10cf3){return -64;}
    if(i >= 0x10d70 && i < 0x10d86){return -32;}
    if(i >= 0x118c0 && i < 0x118e0){return -32;}
    if(i >= 0x16e60 && i < 0x16e80){return -32;}
    if(i >= 0x16ebb && i < 0x16ed4){return -27;}
    if(i >= 0x1e922 && i < 0x1e944){return -34;}
    return 0;
}

int getTitlecaseOffset(int i){
    if(i >= 0x61 && i < 0x7b){return -32;}
    if(i < 0x80){return 0;}
    if(i >= 0x4e00 && i <= 0x9fff){return 0;}
    if(i >= 0xb80 && i <= 0xbff){return 0;}
    if(i >= 0x2190 && i <= 0x23ff){return 0;}
    if(i >= 0xa0 && i <= 0x2af){
        if(i == 0xb5){return 743;}
        if(i >= 0xe0 && i < 0xf7){return -32;}
        if(i >= 0xf8 && i < 0xff){return -32;}
        if(i == 0xff){return 121;}
        if(i == 0x131){return -232;}
        if(i >= 0x101 && i < 0x138 && i % 2 == 1){return -1;}
        if(i >= 0x13a && i < 0x149 && i % 2 == 0){return -1;}
        if(i >= 0x14b && i < 0x178 && i % 2 == 1){return -1;}
        if(i >= 0x17a && i < 0x17f && i % 2 == 0){return -1;}
        if(i == 0x17f){return -300;}
        if(i == 0x180){return 195;}
        if(i == 0x183 || i == 0x185){return -1;}
        if(i == 0x188 || i == 0x18c || i == 0x192){return -1;}
        if(i == 0x195){return 97;}
        if(i == 0x199){return -1;}
        if(i == 0x19a){return 163;}
        if(i == 0x19b){return 42561;}
        if(i == 0x19e){return 130;}
        if(i >= 0x1a1 && i < 0x1a6 && i % 2 == 1){return -1;}
        if(i == 0x1a8 || i == 0x1ad || i == 0x1b0){return -1;}
        if(i == 0x1b4 || i == 0x1b6){return -1;}
        if(i == 0x1b9 || i == 0x1bd){return -1;}
        if(i == 0x1bf){return 56;}
        if(i == 0x1c4){return 1;}
        if(i == 0x1c6){return -1;}
        if(i == 0x1c7){return 1;}
        if(i == 0x1c9 || i == 0x1cc){return -1;}
        if(i == 0x1ca){return 1;}
        if(i >= 0x1ce && i < 0x1dd && i % 2 == 0){return -1;}
        if(i == 0x1dd){return -79;}
        if(i >= 0x1df && i <= 0x1f0 && i % 2 == 1){return -1;}
        if(i == 0x1f1){return 1;}
        if(i == 0x1f5){return -1;}
        if(i == 0x1f3){return -1;}
        if(i >= 0x1f9 && i < 0x234 && i % 2 == 1 && i != 0x221){return -1;}
        if(i == 0x23c || i == 0x242){return -1;}
        if(i >= 0x23f && i < 0x241){return 10815;}
        if(i >= 0x247 && i < 0x250 && i % 2 == 1){return -1;}
        if(i == 0x250){return 10783;}
        if(i == 0x251){return 10780;}
        if(i == 0x252){return 10782;}
        if(i == 0x253){return -210;}
        if(i == 0x254){return -206;}
        if(i >= 0x256 && i < 0x258){return -205;}
        if(i == 0x259){return -202;}
        if(i == 0x25b){return -203;}
        if(i == 0x25c){return 42319;}
        if(i == 0x260){return -205;}
        if(i == 0x261){return 42315;}
        if(i == 0x263){return -207;}
        if(i == 0x264){return 42343;}
        if(i == 0x265){return 42280;}
        if(i == 0x266){return 42308;}
        if(i == 0x268){return -209;}
        if(i == 0x269){return -211;}
        if(i == 0x26a){return 42308;}
        if(i == 0x26b){return 10743;}
        if(i == 0x26c){return 42305;}
        if(i == 0x26f){return -211;}
        if(i == 0x271){return 10749;}
        if(i == 0x272){return -213;}
        if(i == 0x275){return -214;}
        if(i == 0x27d){return 10727;}
        if(i == 0x280){return -218;}
        if(i == 0x282){return 42307;}
        if(i == 0x283){return -218;}
        if(i == 0x287){return 42282;}
        if(i == 0x288){return -218;}
        if(i == 0x289){return -69;}
        if(i >= 0x28a && i < 0x28c){return -217;}
        if(i == 0x28c){return -71;}
        if(i == 0x292){return -219;}
        if(i == 0x29d){return 42261;}
        if(i == 0x29e){return 42258;}
        return 0;
    }
    if(i == 0x345){return 84;}
    if(i >= 0x370 && i <= 0x58f){
        if(i == 0x371 || i == 0x373 || i == 0x377){return -1;}
        if(i >= 0x37b && i < 0x37e){return 130;}
        if(i == 0x3ac){return -38;}
        if(i >= 0x3ad && i < 0x3b0){return -37;}
        if(i >= 0x3b1 && i < 0x3c2){return -32;}
        if(i == 0x3c2){return -31;}
        if(i >= 0x3c3 && i < 0x3cc){return -32;}
        if(i == 0x3cc){return -64;}
        if(i >= 0x3cd && i < 0x3cf){return -63;}
        if(i == 0x3d0){return -62;}
        if(i == 0x3d1){return -57;}
        if(i == 0x3d5){return -47;}
        if(i == 0x3d6){return -54;}
        if(i == 0x3d7){return -8;}
        if(i >= 0x3d9 && i < 0x3f0 && i % 2 == 1){return -1;}
        if(i == 0x3f0){return -86;}
        if(i == 0x3f1){return -80;}
        if(i == 0x3f2){return 7;}
        if(i == 0x3f3){return -116;}
        if(i == 0x3f5){return -96;}
        if(i == 0x3f8 || i == 0x3fb){return -1;}
        if(i >= 0x430 && i < 0x450){return -32;}
        if(i >= 0x450 && i < 0x460){return -80;}
        if(i >= 0x461 && i < 0x482 && i % 2 == 1){return -1;}
        if(i >= 0x48b && i < 0x4c0 && i % 2 == 1){return -1;}
        if(i >= 0x4c2 && i < 0x4cf && i % 2 == 0){return -1;}
        if(i == 0x4cf){return -15;}
        if(i >= 0x4d1 && i < 0x530 && i % 2 == 1){return -1;}
        if(i >= 0x561 && i < 0x587){return -48;}
        return 0;
    }
    if(i >= 0x13f8 && i < 0x13fe){return -8;}
    if(i >= 0x1c80 && i <= 0x1cbf){
        if(i == 0x1c80){return -6254;}
        if(i == 0x1c81){return -6253;}
        if(i == 0x1c82){return -6244;}
        if(i >= 0x1c83 && i < 0x1c85){return -6242;}
        if(i == 0x1c85){return -6243;}
        if(i == 0x1c86){return -6236;}
        if(i == 0x1c87){return -6181;}
        if(i == 0x1c88){return 35266;}
        if(i == 0x1c8a){return -1;}
        return 0;
    }
    if(i == 0x1d79){return 35332;}
    if(i == 0x1d7d){return 3814;}
    if(i == 0x1d8e){return 35384;}
    if(i >= 0x1e00 && i <= 0x1fff){
        if(i >= 0x1e01 && i < 0x1e96 && i % 2 == 1){return -1;}
        if(i == 0x1e9b){return -59;}
        if(i >= 0x1ea1 && i < 0x1f00 && i % 2 == 1){return -1;}
        if(i >= 0x1f00 && i < 0x1f08){return 8;}
        if(i >= 0x1f10 && i < 0x1f16){return 8;}
        if(i >= 0x1f20 && i < 0x1f28){return 8;}
        if(i >= 0x1f30 && i < 0x1f38){return 8;}
        if(i >= 0x1f40 && i < 0x1f46){return 8;}
        if(i >= 0x1f51 && i < 0x1f58 && i % 2 == 1){return 8;}
        if(i >= 0x1f60 && i < 0x1f68){return 8;}
        if(i >= 0x1f70 && i < 0x1f72){return 74;}
        if(i >= 0x1f72 && i < 0x1f76){return 86;}
        if(i >= 0x1f76 && i < 0x1f78){return 100;}
        if(i >= 0x1f78 && i < 0x1f7a){return 128;}
        if(i >= 0x1f7a && i < 0x1f7c){return 112;}
        if(i >= 0x1f7c && i < 0x1f7e){return 126;}
        if(i >= 0x1f80 && i < 0x1f88){return 8;}
        if(i >= 0x1f90 && i < 0x1f98){return 8;}
        if(i >= 0x1fa0 && i < 0x1fa8){return 8;}
        if(i >= 0x1fb0 && i < 0x1fb2){return 8;}
        if(i == 0x1fb3 || i == 0x1fc3){return 9;}
        if(i == 0x1fbe){return -7205;}
        if(i >= 0x1fd0 && i < 0x1fd2){return 8;}
        if(i >= 0x1fe0 && i < 0x1fe2){return 8;}
        if(i == 0x1fe5){return 7;}
        if(i == 0x1ff3){return 9;}
        return 0;
    }
    if(i >= 0x2100 && i <= 0x218f){
        if(i == 0x214e){return -28;}
        if(i >= 0x2170 && i < 0x2180){return -16;}
        if(i == 0x2184){return -1;}
        return 0;
    }
    if(i >= 0x24d0 && i < 0x24ea){return -26;}
    if(i >= 0x2c30 && i < 0x2c60){return -48;}
    if(i >= 0x2c60 && i <= 0x2cff){
        if(i == 0x2c61){return -1;}
        if(i == 0x2c65){return -10795;}
        if(i == 0x2c66){return -10792;}
        if(i >= 0x2c68 && i < 0x2c6d && i % 2 == 0){return -1;}
        if(i == 0x2c73 || i == 0x2c76){return -1;}
        if(i >= 0x2c81 && i < 0x2ce4 && i % 2 == 1){return -1;}
        if(i == 0x2cec || i == 0x2cee || i == 0x2cf3){return -1;}
        return 0;
    }
    if(i >= 0x2d00 && i < 0x2d26){return -7264;}
    if(i == 0x2d27 || i == 0x2d2d){return -7264;}
    if(i >= 0xa640 && i <= 0xa69f){
        if(i >= 0xa641 && i < 0xa66e && i % 2 == 1){return -1;}
        if(i >= 0xa681 && i < 0xa69c && i % 2 == 1){return -1;}
        return 0;
    }
    if(i >= 0xa720 && i <= 0xa7ff){
        if(i >= 0xa723 && i < 0xa770 && i % 2 == 1 && i != 0xa731){return -1;}
        if(i == 0xa77a || i == 0xa77c){return -1;}
        if(i >= 0xa77f && i < 0xa788 && i % 2 == 1){return -1;}
        if(i == 0xa78c || i == 0xa791 || i == 0xa793){return -1;}
        if(i == 0xa794){return 48;}
        if(i >= 0xa797 && i < 0xa7aa && i % 2 == 1){return -1;}
        if(i >= 0xa7b5 && i < 0xa7c4 && i % 2 == 1){return -1;}
        if(i == 0xa7c8 || i == 0xa7ca){return -1;}
        if(i >= 0xa7cd && i < 0xa7dc && i % 2 == 1){return -1;}
        if(i == 0xa7f6){return -1;}
        return 0;
    }
    if(i == 0xab53){return -928;}
    if(i >= 0xab70 && i < 0xabc0){return -38864;}
    if(i >= 0xff41 && i < 0xff5b){return -32;}
    if(i >= 0x10428 && i < 0x10450){return -40;}
    if(i >= 0x104d8 && i < 0x104fc){return -40;}
    if(i >= 0x10597 && i < 0x105bd && i != 0x105a2 && i != 0x105b2 && i != 0x105ba){return -39;}
    if(i >= 0x10cc0 && i < 0x10cf3){return -64;}
    if(i >= 0x10d70 && i < 0x10d86){return -32;}
    if(i >= 0x118c0 && i < 0x118e0){return -32;}
    if(i >= 0x16e60 && i < 0x16e80){return -32;}
    if(i >= 0x16ebb && i < 0x16ed4){return -27;}
    if(i >= 0x1e922 && i < 0x1e944){return -34;}
    return 0;
}

bool getWhitespaceProperty(int i){
    if(i < 0x80){
        if(i >= 0x9 && i <= 0xd){return true;}
        if(i == 0x20){return true;}
        return false;
    }
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i <= 0xff){
        if(i == 0x85){return true;}
        if(i == 0xa0){return true;}
    }
    if(i == 0x1680){return true;}
    if(i >= 0x2000 && i <= 0x205f){
        if(i >= 0x2000 && i <= 0x200a){return true;}
        if(i >= 0x2028 && i <= 0x2029){return true;}
        if(i == 0x202f){return true;}
        if(i == 0x205f){return true;}
    }
    if(i == 0x3000){return true;}
    return false;
}

SGEXTN::CoreText::FullCharacterType getUnicodeGeneralCategory(int i){
    if(i < 0x20){return SGEXTN::CoreText::FullCharacterType::ControlCharacter;}
    if(i >= 0x30 && i < 0x3a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
    if(i >= 0x20 && i < 0x41){
        if(i == 0x20){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(i >= 0x21 && i < 0x24){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x24){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0x25 && i < 0x28){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x28){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x29){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0x2a || i == 0x2c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2b){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x2d){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x2e && i < 0x30){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x3a && i < 0x3c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x3c && i < 0x3f){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x3f && i < 0x41){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
    }
    if(i >= 0x41 && i < 0x5b){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
    if(i >= 0x5b && i < 0x61){
        if(i == 0x5b){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x5c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x5d){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0x5e || i == 0x60){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0x5f){return SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation;}
    }
    if(i >= 0x61 && i < 0x7b){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
    if(i >= 0x7b && i < 0x7f){
        if(i == 0x7b){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x7c){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x7d){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0x7e){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
    }
    if(i >= 0x7f && i < 0xa0){return SGEXTN::CoreText::FullCharacterType::ControlCharacter;}
    if(i >= 0x4e00 && i <= 0x9fff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0xb80 && i <= 0xbff){
        if(i == 0xb82){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xb83 && i < 0xb8b && i != 0xb84){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb8e && i < 0xb96 && i != 0xb91){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb99 && i < 0xba0 && i != 0xb9b && i != 0xb9d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xba3 && i < 0xba5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xba8 && i < 0xbab){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xbae && i < 0xbba){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xbbe && i < 0xbc0){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xbc0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xbc1 && i < 0xbc3){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xbc6 && i < 0xbc9){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xbca && i < 0xbcd){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xbcd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xbd0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xbd7){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xbe6 && i < 0xbf0){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xbf0 && i < 0xbf3){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0xbf3 && i < 0xbf9){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xbf9){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0xbfa){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2200 && i <= 0x22ff){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}

    if(i >= 0xa0 && i <= 0xff){
        if(i == 0xa0){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(i == 0xa1){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa2 && i < 0xa6){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0xa6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xa7){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xa8){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0xa9){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xaa){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xab){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i == 0xac){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0xad){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i == 0xae){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xaf){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0xb0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xb1){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0xb2 && i < 0xb4){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0xb4){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0xb5){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xb6 && i < 0xb8){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xb8){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0xb9){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0xba){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xbb){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(i >= 0xbc && i < 0xbf){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0xbf){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xc0 && i < 0xdf && i != 0xd7){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xdf && i < 0x100 && i != 0xf7){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xd7 || i == 0xf7){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x100 && i <= 0x17f){
        if(i >= 0x100 && i < 0x138 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x100 && i < 0x138){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x138 && i < 0x149 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x138 && i < 0x149){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x149 && i < 0x179 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x149 && i < 0x179){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x179 && i < 0x17f && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x179 && i < 0x17f){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x17f){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x180 && i <= 0x24f){
        if(i == 0x180){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x181){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x182 && i < 0x187 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x182 && i < 0x187){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x187){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x188){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x189 && i < 0x18c){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x18c && i < 0x18e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x18e && i < 0x192){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x192){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x193 && i < 0x195){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x195){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x196 && i < 0x199){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x199 && i < 0x19c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x19c && i < 0x19e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x19e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x19f && i < 0x1a1){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1a1 && i < 0x1a7 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1a1 && i < 0x1a7){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1a7 && i < 0x1ab && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1a7 && i < 0x1ab){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1ab && i < 0x1af && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1ab && i < 0x1af){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1af){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1b0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1b1 && i < 0x1b4){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1b4 || i == 0x1b6){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1b5){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1b7 && i < 0x1b9){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1b9 && i < 0x1bb){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1bb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1bc){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1bd && i < 0x1c0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1c0 && i < 0x1c4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1c4 || i == 0x1c7 || i == 0x1ca){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1c5 || i == 0x1c8 || i == 0x1cb){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i == 0x1c6 || i == 0x1c9){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1cc && i < 0x1dd && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1cc && i < 0x1dd){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1dd && i < 0x1f0 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1dd && i < 0x1f0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1f0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1f1){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1f2){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i == 0x1f3 || i == 0x1f5){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1f4){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f6 && i < 0x1f9){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f9 && i < 0x234 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f9 && i < 0x234){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x234 && i < 0x23a){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x23a && i < 0x23c){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x23c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x23d && i < 0x23f){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x23f && i < 0x241){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x241){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x242){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x243 && i < 0x247){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x247 && i < 0x250 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x247 && i < 0x250){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x250 && i <= 0x2af){
        if(i >= 0x250 && i < 0x294){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 294 && i < 0x296){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x296 && i < 0x2b0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2b0 && i <= 0x2ff){
        if(i >= 0x2b0 && i < 0x2c2){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x2c2 && i < 0x2c6){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x2c6 && i < 0x2d2){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x2d2 && i < 0x2e0){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x2e0 && i < 0x2e5){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x2e5 && i < 0x2ec){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0x2ec || i == 0x2ee){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x2ed){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x2ef && i < 0x300){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x300 && i <= 0x36f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
    if(i >= 0x370 && i <= 0x3ff){
        if(i == 0x370 || i == 0x372){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x371 || i == 0x373){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x374){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x375){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0x376){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x377){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x37a){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x37b && i < 0x37e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x37e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x37f){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x384 && i < 0x386){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0x386){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x387){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x388 && i < 0x38b){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x38c){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x38e && i < 0x390){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x390){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x391 && i < 0x3a2){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3a3 && i < 0x3ac){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3ac && i < 0x3cf){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x3cf){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3d0 && i < 0x3d2){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3d2 && i < 0x3d5){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3d5 && i < 0x3d8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3d8 && i < 0x3f0 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3d8 && i < 0x3f0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3f0 && i < 0x3f4){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x3f4 || i == 0x3f7){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x3f5 || i == 0x3f8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x3f6){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x3f9 && i < 0x3fb){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x3fb && i < 0x3fd){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x3fd && i < 0x400){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x400 && i <= 0x4ff){
        if(i >= 0x400 && i < 0x430){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x430 && i < 0x460){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x460 && i < 0x482 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x460 && i < 0x482){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x482){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x483 && i < 0x488){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x488 && i < 0x48a){return SGEXTN::CoreText::FullCharacterType::EnclosingMark;}
        if(i >= 0x48a && i < 0x4c1 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x48a && i < 0x4c1){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x4c1 && i < 0x4cf && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x4c1 && i < 0x4cf){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x4cf && i < 0x500 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x4cf && i < 0x500){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x500 && i <= 0x52f){
        if(i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;
    }
    if(i >= 0x530 && i <= 0x58f){
        if(i >= 0x531 && i < 0x557){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x559){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x55a && i < 0x560){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x560 && i < 0x589){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x589){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x58a){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x58d && i < 0x58f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x58f){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x590 && i <= 0x5ff){
        if(i >= 0x591 && i < 0x5be){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x5be){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i == 0x5bf){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x5c0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x5c1 && i < 0x5c3){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x5c3){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x5c4 && i < 0x5c6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x5c6){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x5c7){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x5d0 && i < 0x5eb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x5ef && i < 0x5f3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x5f3 && i < 0x5f5){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x600 && i <= 0x6ff){
        if(i >= 0x600 && i < 0x606){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x606 && i < 0x609){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x609 && i < 0x60b){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x60b){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0x60c && i < 0x60e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x60e && i < 0x610){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x610 && i < 0x61b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x61b){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x61c){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x61d && i < 0x620){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x620 && i < 0x640){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x640){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x641 && i < 0x64b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x64b && i < 0x660){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x660 && i < 0x66a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x66a && i < 0x66e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x66e && i < 0x670){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x670){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x671 && i < 0x6d4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x6d4){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x6d5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x6d6 && i < 0x6dd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x6dd){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i == 0x6de){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x6df && i < 0x6e5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x6e5 && i < 0x6e7){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x6e7 && i < 0x6e9){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x6e9){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x6ea && i < 0x6ee){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x6ee && i < 0x6f0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x6f0 && i < 0x6fa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x6fa && i < 0x6fd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x6fd && i < 0x6ff){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x6ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x700 && i <= 0x74f){
        if(i >= 0x700 && i < 0x70e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x70f){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i == 0x710){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x711){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x712 && i < 0x730){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x730 && i < 0x74b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x74d && i < 0x750){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x750 && i <= 0x77f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x780 && i <= 0x7bf){
        if(i >= 0x780 && i < 0x7a6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x7a6 && i < 0x7b1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x7b1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x7c0 && i <= 0x7ff){
        if(i >= 0x7c0 && i < 0x7ca){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x7ca && i < 0x7eb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x7eb && i < 0x7f4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x7f4 && i < 0x7f6){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x7f6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x7f7 && i < 0x7fa){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x7fa){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x7fd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x7fe && i < 0x800){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x800 && i <= 0x83f){
        if(i >= 0x800 && i < 0x816){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x816 && i < 0x81a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x81a){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x81b && i < 0x824){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x824){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x825 && i < 0x828){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x828){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x829 && i < 0x82e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x830 && i < 0x83f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x840 && i <= 0x85f){
        if(i >= 0x840 && i < 0x859){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x859 && i < 0x85c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x85e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x860 && i <= 0x86f){
        if(i >= 0x860 && i < 0x86b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x870 && i <= 0x89f){
        if(i >= 0x870 && i < 0x888){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x888){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x889 && i < 0x890){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x890 && i < 0x892){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x897 && i < 0x8a0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x8a0 && i <= 0x8ff){
        if(i >= 0x8a0 && i < 0x8c9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x8c9){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x8ca && i < 0x8e2){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x8e2){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x8e3 && i < 0x900){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x900 && i <= 0x97f){
        if(i >= 0x900 && i < 0x903){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x903){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x904 && i < 0x93a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x93a || i == 0x93c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x93b){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x93d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x93e && i < 0x941){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x941 && i < 0x949){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x949 && i < 0x94d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x94d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x94e && i < 0x950){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x950){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x951 && i < 0x958){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x958 && i < 0x962){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x962 && i < 0x964){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x964 && i < 0x966){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x966 && i < 0x970){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x970){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x971){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x972 && i < 0x980){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x980 && i <= 0x9ff){
        if(i == 0x980){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x981){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x982 && i < 0x984){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x985 && i < 0x98d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x98f && i < 0x991){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x993 && i < 0x9a9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x9aa && i < 0x9b1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x9b2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x9b6 && i < 0x9ba){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x9bc){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x9bd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x9be && i < 0x9c1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x9c1 && i < 0x9c5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x9c7 && i < 0x9c9){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x9cb && i < 0x9cd){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x9cd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x9ce){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x9d7){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x9dc && i < 0x9de){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x9df && i < 0x9e2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x9e2 && i < 0x9e4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x9e6 && i < 0x9f0){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x9f0 && i < 0x9f2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x9f2 && i < 0x9f4){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0x9f4 && i < 0x9fa){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x9fa){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x9fb){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0x9fc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x9fd){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x9fe){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa00 && i <= 0xa7f){
        if(i >= 0xa01 && i < 0xa03){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa03){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa05 && i < 0xa0b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa0f && i < 0xa11){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa13 && i < 0xa29){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa2a && i < 0xa31){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa32 && i < 0xa34){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa35 && i < 0xa37){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa38 && i < 0xa3a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa3c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa3e && i < 0xa41){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa41 && i < 0xa43){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa47 && i < 0xa49){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa4b && i < 0xa4e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa51){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa59 && i < 0xa5d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa5e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa66 && i < 0xa70){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xa70 && i < 0xa72){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa72 && i < 0xa75){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa75){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa76){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa80 && i <= 0xaff){
        if(i >= 0xa81 && i < 0xa83){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa83){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa85 && i < 0xa8e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa8f && i < 0xa92){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa93 && i<0xaa9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xaaa && i < 0xab1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xab2 && i < 0xab4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xab5 && i < 0xaba){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xabc){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xabd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xabe && i < 0xac1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xac1 && i < 0xac6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xac7 && i < 0xac9){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xac9 && i < 0xaca){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xacb && i < 0xacd){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xacd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xad0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xae0 && i < 0xae2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xae2 && i < 0xae4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xae6 && i < 0xaf0){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0xaf0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xaf1){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0xaf9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xafa && i < 0xb00){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xb00 && i <= 0xb7f){
        if(i == 0xb01){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xb02 && i < 0xb04){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xb05 && i < 0xb0d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb0f && i < 0xb11){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb13 && i < 0xb29){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb2a && i < 0xb31){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb32 && i < 0xb34){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb35 && i < 0xb3a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xb3c || i == 0xb3f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xb3d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xb3e || i == 0xb40){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xb41 && i < 0xb45){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xb47 && i < 0xb49){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xb4b && i < 0xb4d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xb4d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xb55 && i < 0xb57){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xb57){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xb5c && i < 0xb5e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb5f && i < 0xb62){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb62 && i < 0xb64){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xb66 && i < 0xb70){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0xb70){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xb71){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xb72 && i < 0xb78){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xc00 && i <= 0xc7f){
        if(i == 0xc00){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc01 && i < 0xc04){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xc04){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc05 && i < 0xc0d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc0e && i < 0xc11){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc12 && i < 0xc29){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc2a && i < 0xc3a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xc3c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xc3d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc3e && i < 0xc41){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc41 && i < 0xc45){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xc46 && i < 0xc49){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc4a && i < 0xc4e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc55 && i < 0xc57){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc58 && i < 0xc5b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc5c && i < 0xc5e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc60 && i < 0xc62){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc62 && i < 0xc64){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc66 && i < 0xc70){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0xc77){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xc78 && i < 0xc7f){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0xc7f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xc80 && i <= 0xcff){
        if(i == 0xc80){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xc81){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xc82 && i < 0xc84){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xc84){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xc85 && i < 0xc8d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc8e && i < 0xc91){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xc92 && i < 0xca9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xcaa && i < 0xcb4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xcb5 && i < 0xcba){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xcbc){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xcbd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xcbe){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xcbf){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xcc0 && i < 0xcc5){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xcc6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xcc7 && i < 0xcc9){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xcca && i < 0xccc){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xccc && i < 0xcce){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xcd5 && i < 0xcd7){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xcdc && i < 0xcdf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xce0 && i < 0xce2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xce2 && i < 0xce4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xce6 && i < 0xcf0){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xcf1 && i < 0xcf3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xcf3){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xd00 && i <= 0xd7f){
        if(i >= 0xd00 && i < 0xd02){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xd02 && i < 0xd04){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xd04 && i < 0xd0d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xd0e && i < 0xd11){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xd12 && i < 0xd3b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xd3b && i < 0xd3d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xd3d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xd3e && i < 0xd41){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xd41 && i < 0xd45){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xd46 && i < 0xd49){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xd4a && i < 0xd4d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xd4d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xd4e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xd4f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xd54 && i < 0xd57){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xd57){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xd58 && i < 0xd5f){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0xd5f && i < 0xd62){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xd62 && i < 0xd64){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xd66 && i < 0xd70){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xd70 && i < 0xd79){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0xd79){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xd7a && i < 0xd80){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xd80 && i <= 0xdff){
        if(i == 0xd81){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xd82 && i < 0xd84){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xd85 && i < 0xd97){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xd9a && i < 0xdb2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xdb3 && i < 0xdbc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xdbd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xdc0 && i < 0xdc7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xdca){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xdcf && i < 0xdd2){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xdd2 && i < 0xdd5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xdd6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xdd8 && i < 0xde0){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xde6 && i < 0xdf0){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xdf2 && i < 0xdf4){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xdf4){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe00 && i <= 0xe7f){
        if(i >= 0xe01 && i < 0xe31){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xe31){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xe32 && i < 0xe34){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xe34 && i < 0xe3b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xe3f){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0xe40 && i < 0xe46){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xe46){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xe47 && i < 0xe4f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xe4f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xe50 && i < 0xe5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xe5a && i < 0xe5c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe80 && i <= 0xeff){
        if(i >= 0xe81 && i < 0xe83){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xe84){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xe86 && i < 0xe8b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xe8c && i < 0xea4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xea5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xea7 && i < 0xeb1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xeb1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xeb2 && i < 0xeb4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xeb4 && i < 0xebd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xebd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xec0 && i < 0xec5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xec6){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xec8 && i < 0xecf){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xed0 && i < 0xeda){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xedc && i < 0xee0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xf00 && i <= 0xfff){
        if(i == 0xf00){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xf01 && i < 0xf04){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xf04 && i < 0xf13){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xf13){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xf14){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xf15 && i < 0xf18){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xf18 && i < 0xf1a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xf1a && i < 0xf20){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xf20 && i < 0xf2a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xf2a && i < 0xf34){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0xf34 || i == 0xf36 || i == 0xf38){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xf35 || i == 0xf37 || i == 0xf39){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xf3a || i == 0xf3c){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xf3b || i == 0xf3d){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xf3e && i < 0xf40){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xf40 && i < 0xf48){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xf49 && i < 0xf6d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xf71 && i < 0xf7f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xf7f){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xf80 && i < 0xf85){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xf85){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xf86 && i < 0xf88){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xf88 && i < 0xf8d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xf8d && i < 0xf98){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xf99 && i < 0xfbd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xfbe && i < 0xfc6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xfc6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xfc7 && i < 0xfcd){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xfce && i < 0xfd0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd0 && i < 0xfd5){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfd5 && i < 0xfd9){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd9 && i < 0xfdb){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1000 && i <= 0x109f){
        if(i >= 0x1000 && i < 0x102b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x102b && i < 0x102d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x102d && i < 0x1031){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1031){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1032 && i < 0x1038){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1038){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1039 && i < 0x103b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x103b && i < 0x103d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x103d && i < 0x103f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x103f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1040 && i < 0x104a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x104a && i < 0x1050){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1050 && i < 0x1056){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1056 && i < 0x1058){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1058 && i < 0x105a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x105a && i < 0x105e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x105e && i < 0x1061){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1061){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1062 && i < 0x1065){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1065 && i < 0x1067){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1067 && i < 0x106e){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x106e && i < 0x1071){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1071 && i < 0x1075){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1075 && i < 0x1082){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1082){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1083 && i < 0x1085){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1085 && i < 0x1087){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1087 && i < 0x108d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x108d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x108e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x108f){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1090 && i < 0x109a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x109a && i < 0x109d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x109d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x109e && i < 0x10a0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10a0 && i <= 0x10ff){
        if(i >= 0x10a0 && i < 0x10c6){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x10c7 || i == 0x10cd){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10d0 && i < 0x10fb){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x10fb){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x10fc){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x10fd && i < 0x1100){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1100 && i <= 0x11ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x1200 && i <= 0x137f){
        if(i >= 0x1200 && i < 0x1249){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x124a && i < 0x124e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1250 && i < 0x1257){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1258){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x125a && i < 0x125e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1260 && i < 0x1289){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x128a && i < 0x128e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1290 && i < 0x12b1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x12b2 && i < 0x12b6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x12b8 && i < 0x12bf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x12c0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x12c2 && i < 0x12c6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x12c8 && i < 0x12d7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x12d8 && i < 0x1311){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1312 && i < 0x1316){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1318 && i < 0x135b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x135d && i < 0x1360){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1360 && i < 0x1369){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1369 && i < 0x137d){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1380 && i <= 0x139f){
        if(i >= 0x1380 && i < 0x1390){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1390 && i < 0x139a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x13a0 && i <= 0x13ff){
        if(i >= 0x13a0 && i < 0x13f6){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x13f8 && i < 0x13fe){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1400 && i <= 0x167f){
        if(i == 0x1400){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x1401 && i < 0x166d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x166d){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x166e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x166f && i < 0x1680){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1680 && i <= 0x169f){
        if(i == 0x1680){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(i >= 0x1681 && i < 0x169b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x169b){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x169c){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16a0 && i <= 0x16ff){
        if(i >= 0x16a0 && i < 0x16eb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16eb && i < 0x16ee){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x16ee && i < 0x16f1){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i >= 0x16f1 && i < 0x16f9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1700 && i <= 0x171f){
        if(i >= 0x1700 && i < 0x1712){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1712 && i < 0x1715){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1715){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x171f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1720 && i <= 0x173f){
        if(i >= 0x1720 && i < 0x1732){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1732 && i < 0x1734){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1734){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1735 && i < 0x1737){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1740 && i <= 0x175f){
        if(i >= 0x1740 && i < 0x1752){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1752 && i < 0x1754){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1760 && i <= 0x177f){
        if(i >= 0x1760 && i < 0x176d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x176e && i < 0x1771){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1772 && i < 0x1774){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1780 && i <= 0x17ff){
        if(i >= 0x1780 && i < 0x17b4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x17b4 && i < 0x17b6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x17b6){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x17b7 && i < 0x17be){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x17be && i < 0x17c6){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x17c6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x17c7 && i < 0x17c9){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x17c9 && i < 0x17d4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x17d4 && i < 0x17d7){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x17d7){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x17d8 && i < 0x17db){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x17db){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0x17dc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x17dd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x17e0 && i < 0x17ea){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x17f0 && i < 0x17fa){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1800 && i <= 0x18af){
        if(i >= 0x1800 && i < 0x1806){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x1806){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x1807 && i < 0x180b){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x180b && i < 0x180e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x180e){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i == 0x180f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1810 && i < 0x181a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1820 && i < 0x1843){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1843){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1844 && i < 0x1879){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1880 && i < 0x1885){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1885 && i < 0x1887){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1887 && i < 0x18a9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x18a9){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x18aa){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x18b0 && i <= 0x18ff){
        if(i >= 0x18b0 && i < 0x18f6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1900 && i <= 0x194f){
        if(i >= 0x1900 && i < 0x191f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1920 && i < 0x1923){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1923 && i < 0x1927){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1927 && i < 0x1929){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1929 && i < 0x192c){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1930 && i < 0x1932){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1932){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1933 && i < 0x1939){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1939 && i < 0x193c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1940){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1944 && i < 0x1946){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1946 && i < 0x1950){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1950 && i <= 0x197f){
        if(i >= 0x1950 && i < 0x196e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1970 && i < 0x1975){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1980 && i <= 0x19df){
        if(i >= 0x1980 && i < 0x19ac){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x19b0 && i < 0x19ca){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x19d0 && i < 0x19da){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x19da){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x19de && i < 0x19e0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x19e0 && i <= 0x19ff){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x1a00 && i <= 0x1a1f){
        if(i >= 0x1a00 && i < 0x1a17){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1a17 && i < 0x1a19){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1a19 && i < 0x1a1b){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1a1b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1a1e && i < 0x1a20){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1a20 && i <= 0x1aaf){
        if(i >= 0x1a20 && i < 0x1a55){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1a55 || i == 0x1a57){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1a56){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1a58 && i < 0x1a5f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1a60 || i == 0x1a62){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1a61){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1a63 && i < 0x1a65){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1a65 && i < 0x1a6d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1a6d && i < 0x1a73){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1a73 && i < 0x1a7d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1a7f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1a80 && i < 0x1a8a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1a90 && i < 0x1a9a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1aa0 && i < 0x1aa7){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x1aa7){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1aa8 && i < 0x1aae){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ab0 && i <= 0x1aff){
        if(i >= 0x1ab0 && i < 0x1abe){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1abe){return SGEXTN::CoreText::FullCharacterType::EnclosingMark;}
        if(i >= 0x1abf && i < 0x1ade){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1ae0 && i < 0x1aec){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b00 && i <= 0x1b7f){
        if(i >= 0x1b00 && i < 0x1b04){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1b04){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1b05 && i < 0x1b34){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1b34){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1b35){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1b36 && i < 0x1b3b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1b3b){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1b3c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1b3d && i < 0x1b42){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1b42){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1b43 && i < 0x1b45){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1b45 && i < 0x1b4d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1b4e && i < 0x1b50){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1b50 && i < 0x1b5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1b5a && i < 0x1b61){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1b61 && i < 0x1b6b){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1b6b && i < 0x1b74){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1b74 && i < 0x1b7d){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1b7d && i < 0x1b80){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b80 && i <= 0x1bbf){
        if(i >= 0x1b80 && i < 0x1b82){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1b82){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1b83 && i < 0x1ba1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1ba1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1ba2 && i < 0x1ba6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1ba6 && i < 0x1ba8){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1ba8 && i < 0x1baa){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1baa){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1bab && i < 0x1bae){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1bae && i < 0x1bb0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1bb0 && i < 0x1bba){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1bba && i < 0x1bc0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1bc0 && i <= 0x1bff){
        if(i >= 0x1bc0 && i < 0x1be6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1be6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1be7){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1be8 && i < 0x1bea){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1bea && i < 0x1bed){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1bed){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1bee){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1bef && i < 0x1bf2){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1bf2 && i < 0x1bf4){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1bfc && i < 0x1c00){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c00 && i <= 0x1c4f){
        if(i >= 0x1c00 && i < 0x1c24){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1c24 && i < 0x1c2c){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1c2c && i < 0x1c34){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1c34 && i < 0x1c36){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1c36 && i < 0x1c38){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1c3b && i < 0x1c40){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1c40 && i < 0x1c4a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1c4d && i < 0x1c50){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c50 && i <= 0x1c7f){
        if(i >= 0x1c50 && i < 0x1c5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1c5a && i < 0x1c78){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1c78 && i < 0x1c7e){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1c7e && i < 0x1c80){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c80 && i <= 0x1c8f){
        if(i >= 0x1c80 && i < 0x1c89){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1c89){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1c8a){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1c90 && i <= 0x1cbf){
        if(i >= 0x1c90 && i < 0x1cbb){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1cbd && i < 0x1cc0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cc0 && i <= 0x1ccf){
        if(i >= 0x1cc0 && i < 0x1cc8){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cd0 && i <= 0x1cff){
        if(i >= 0x1cd0 && i < 0x1cd3){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1cd3){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1cd4 && i < 0x1ce1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1ce1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1ce2 && i < 0x1ce9){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1ce9 && i < 0x1ced){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1ced){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1cee && i < 0x1cf4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1cf4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1cf5 && i < 0x1cf7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1cf7){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1cf8 && i < 0x1cfa){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1cfa){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d00 && i <= 0x1d7f){
        if(i >= 0x1d00 && i < 0x1d2c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d2c && i < 0x1d6b){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1d6b && i < 0x1d78){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d78){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1d79 && i < 0x1d80){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d80 && i <= 0x1dbf){
        if(i >= 0x1d80 && i < 0x1d9b){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d9b && i < 0x1dc0){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
    }
    if(i >= 0x1dc0 && i <= 0x1dff){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
    if(i >= 0x1e00 && i <= 0x1eff){
        if(i >= 0x1e00 && i < 0x1e95 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1e00 && i < 0x1e95){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1e95 && i < 0x1e9e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1e9e && i < 0x1f00 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1e9e && i < 0x1f00){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f00 && i <= 0x1fff){
        if(i >= 0x1f00 && i < 0x1f08){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f08 && i < 0x1f10){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f10 && i < 0x1f16){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f18 && i < 0x1f1e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f20 && i < 0x1f28){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f28 && i < 0x1f30){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f30 && i < 0x1f38){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f38 && i < 0x1f40){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f40 && i < 0x1f46){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f48 && i < 0x1f4e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f50 && i < 0x1f58){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f59 && i < 0x1f60 && i % 2 == 1){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f60 && i < 0x1f68){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f68 && i < 0x1f70){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1f70 && i < 0x1f7e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f80 && i < 0x1f88){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f88 && i < 0x1f90){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1f90 && i < 0x1f98){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1f98 && i < 0x1fa0){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1fa0 && i < 0x1fa8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fa8 && i < 0x1fb0){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1fb0 && i < 0x1fb5){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fb6 && i < 0x1fb8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fb8 && i < 0x1fbc){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1fbc){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i == 0x1fbd){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0x1fbe){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fbf && i < 0x1fc2){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1fc2 && i < 0x1fc5){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fc6 && i < 0x1fc8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fc8 && i < 0x1fcc){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1fcc){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1fcd && i < 0x1fd0){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1fd0 && i < 0x1fd4){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fd6 && i < 0x1fd8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fd8 && i < 0x1fdc){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1fdd && i < 0x1fe0){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1fe0 && i < 0x1fe8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1fe8 && i < 0x1fed){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1fed && i < 0x1ff0){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1ff2 && i < 0x1ff5){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1ff6 && i < 0x1ff8){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1ff8 && i < 0x1ffc){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1ffc){return SGEXTN::CoreText::FullCharacterType::TitlecaseLetter;}
        if(i >= 0x1ffd && i < 0x1fff){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2000 && i <= 0x206f){
        if(i >= 0x2000 && i < 0x200b){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(i >= 0x200b && i < 0x2010){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x2010 && i < 0x2016){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x2016 && i < 0x2018){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2018){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i == 0x2019 || i == 0x201d){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(i == 0x201a || i == 0x201e){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x201b && i < 0x201d){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i >= 0x201f && i < 0x2020){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i >= 0x2020 && i < 0x2028){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2028){return SGEXTN::CoreText::FullCharacterType::LineBreak;}
        if(i == 0x2029){return SGEXTN::CoreText::FullCharacterType::ParagraphBreak;}
        if(i >= 0x202a && i < 0x202f){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i == 0x202f){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(i >= 0x2030 && i < 0x2039){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2039){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i == 0x203a){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(i >= 0x203b && i < 0x203f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x203f && i < 0x2041){return SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0x2041 && i < 0x2044){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2044){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x2045){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x2046){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2047 && i < 0x2052){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2052){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x2053){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2054){return SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0x2055 && i < 0x205f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x205f){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(i >= 0x2060 && i < 0x2065){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x2066 && i < 0x2070){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2070 && i <= 0x209f){
        if(i == 0x2070){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x2071){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x2074 && i < 0x207a){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x207a && i < 0x207d){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x207d){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x207e){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0x207f){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x2080 && i < 0x208a){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x208a && i < 0x208d){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x208d){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x208e){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2090 && i < 0x209d){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x20a0 && i <= 0x20cf){
        if(i >= 0x20a0 && i < 0x20c2){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x20d0 && i <= 0x20ff){
        if(i >= 0x20d0 && i < 0x20dd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x20dd && i < 0x20e1){return SGEXTN::CoreText::FullCharacterType::EnclosingMark;}
        if(i == 0x20e1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x20e2 && i < 0x20e5){return SGEXTN::CoreText::FullCharacterType::EnclosingMark;}
        if(i >= 0x20e5 && i < 0x20f1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2100 && i <= 0x214f){
        if(i >= 0x2100 && i < 0x2102){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x2102 || i == 0x2107){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2103 && i < 0x2107){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2108 && i < 0x210a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x210a){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x210b && i < 0x210e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x210e && i < 0x2110){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2110 && i < 0x2113){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2113){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x2114){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x2115){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2116 && i < 0x2118){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x2118){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x2119 && i < 0x211e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x211e && i < 0x2124){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2124 && i < 0x212a && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2124 && i < 0x212a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x212a && i < 0x212e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x212e){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x212f){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2130 && i < 0x2134){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2134){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2135 && i < 0x2139){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x2139){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x213a && i < 0x213c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x213c && i < 0x213e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x213e && i < 0x2140){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2140 && i < 0x2145){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x2145){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2146 && i < 0x214a){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x214a || i == 0x214f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x214b){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x214c && i < 0x214e){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x214e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2150 && i <= 0x218f){
        if(i >= 0x2150 && i < 0x2160){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x2160 && i < 0x2183){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i == 0x2183){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2184){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2185 && i < 0x2189){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i == 0x2189){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x218a && i < 0x218c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2190 && i <= 0x21ff){
        if(i >= 0x2190 && i < 0x2195){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x2195 && i < 0x219a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x219a && i < 0x219c){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x219c && i < 0x21a0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x21a0){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x21a1 && i < 0x21a3){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x21a3){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x21a4 && i < 0x21a6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x21a6){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x21a7 && i < 0x21ae){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x21ae){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x21af && i < 0x21ce){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x21ce && i < 0x21d0){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x21d0 && i < 0x21d2){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x21d2 || i == 0x21d4){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x21d3){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x21d5 && i < 0x21f4){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x21f4 && i < 0x2200){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2300 && i <= 0x23ff){
        if(i >= 0x2300 && i < 0x2308){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x2308 || i == 0x230a){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x2309 || i == 0x230b){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x230c && i < 0x2320){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2320 && i < 0x2322){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x2322 && i < 0x2329){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x2329){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x232a){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x232b && i < 0x237c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x237c){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x237d && i < 0x239b){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x239b && i < 0x23b4){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x23b4 && i < 0x23dc){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x23dc && i < 0x23e2){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x23e2 && i < 0x2400){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2400 && i <= 0x243f){
        if(i >= 0x2400 && i < 0x242a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2440 && i <= 0x245f){
        if(i >= 0x2440 && i < 0x244b){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2460 && i <= 0x24ff){
        if(i >= 0x2460 && i < 0x249c){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x249c && i < 0x24ea){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x24ea && i < 0x2500){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2500 && i <= 0x257f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x2580 && i <= 0x259f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x25a0 && i <= 0x25ff){
        if(i >= 0x25a0 && i < 0x25b7){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x25b7){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x25b8 && i < 0x25c1){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x25c1){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x25c2 && i < 0x25f8){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x25f8 && i < 0x2600){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2600 && i <= 0x26ff){
        if(i >= 0x2600 && i < 0x266f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x266f){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x2670 && i < 0x2700){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2700 && i <= 0x27bf){
        if(i >= 0x2700 && i < 0x2768){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2768 && i < 0x2776 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2768 && i < 0x2776){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2776 && i < 0x2794){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x2794 && i < 0x27c0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x27c0 && i <= 0x27ef){
        if(i >= 0x27c0 && i < 0x27c5){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x27c5){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x27c6){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x27c7 && i < 0x27e6){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x27e6 && i < 0x27f0 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x27e6 && i < 0x27f0){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x27f0 && i <= 0x27ff){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
    if(i >= 0x2800 && i <= 0x28ff){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x2900 && i <= 0x297f){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
    if(i >= 0x2980 && i <= 0x29ff){
        if(i >= 0x2980 && i < 0x2983){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x2983 && i < 0x2999 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2983 && i < 0x2999){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2999 && i < 0x29d8){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x29d8 || i == 0x29da){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x29d9 || i == 0x29db){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x29dc && i < 0x29fc){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0x29fc){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x29fd){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x29fe && i < 0x2a00){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2a00 && i <= 0x2aff){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
    if(i >= 0x2b00 && i <= 0x2bff){
        if(i >= 0x2b00 && i < 0x2b30){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2b30 && i < 0x2b45){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x2b45 && i < 0x2b47){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2b47 && i < 0x2b4d){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x2b4d && i < 0x2b74){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2b76 && i < 0x2c00){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2c00 && i <= 0x2c5f){
        if(i >= 0x2c00 && i < 0x2c30){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c30 && i < 0x2c60){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2c60 && i <= 0x2c7f){
        if(i == 0x2c60){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2c61){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2c62 && i < 0x2c65){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c65 && i < 0x2c67){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x2c67 || i == 0x2c69 || i == 0x2c6b){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2c68 || i == 0x2c6a || i == 0x2c6c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2c6d && i < 0x2c71){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2c71){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x2c72){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c73 && i < 0x2c75){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x2c75){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c76 && i < 0x2c7c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2c7c && i < 0x2c7e){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x2c7e && i < 0x2c80){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2c80 && i <= 0x2cff){
        if(i >= 0x2c80 && i < 0x2ce3 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2c80 && i < 0x2ce3){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2ce3 && i < 0x2ce5){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2ce5 && i < 0x2ceb){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x2ceb){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2cec || i == 0x2cee){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x2ced){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x2cef && i < 0x2cf2){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x2cf2){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x2cf3){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x2cf9 && i < 0x2cfd){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2cfd){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x2cfe && i < 0x2d00){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2d00 && i <= 0x2d2f){
        if(i >= 0x2d00 && i < 0x2d26){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x2d27 || i == 0x2d2d){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2d30 && i <= 0x2d7f){
        if(i >= 0x2d30 && i < 0x2d68){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x2d6f){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x2d70){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2d7f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2d80 && i <= 0x2ddf){
        if(i >= 0x2d80 && i < 0x2d97){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2da0 && i < 0x2da7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2da8 && i < 0x2daf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2db0 && i < 0x2db7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2db8 && i < 0x2dbf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2dc0 && i < 0x2dc7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2dc8 && i < 0x2dcf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2dd0 && i < 0x2dd7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2dd8 && i < 0x2ddf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2de0 && i <= 0x2dff){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
    if(i >= 0x2e00 && i <= 0x2e7f){
        if(i >= 0x2e00 && i < 0x2e02){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e02 || i == 0x2e04){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i == 0x2e03 || i == 0x2e05){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(i >= 0x2e06 && i < 0x2e09){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e09 || i == 0x2e0c){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i == 0x2e0a || i == 0x2e0d){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(i == 0x2e0b){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e0e && i < 0x2e17){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e17){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x2e18 && i < 0x2e1a){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e1a){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i == 0x2e1b){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e1c){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i == 0x2e1d){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(i >= 0x2e1e && i < 0x2e20){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e20){return SGEXTN::CoreText::FullCharacterType::OpeningQuote;}
        if(i == 0x2e21){return SGEXTN::CoreText::FullCharacterType::ClosingQuote;}
        if(i >= 0x2e22 && i < 0x2e2a && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2e22 && i < 0x2e2a){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2e2a && i < 0x2e2f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e2f){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x2e30 && i < 0x2e3a){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e3a && i < 0x2e3c){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x2e3c && i < 0x2e40){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e40){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i == 0x2e41){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x2e42){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x2e43 && i < 0x2e50){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e50 && i < 0x2e52){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2e52 && i < 0x2e55){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x2e55 && i < 0x2e5d && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x2e55 && i < 0x2e5d){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0x2e5d){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2e80 && i <= 0x2eff){
        if(i >= 0x2e80 && i < 0x2e9a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x2e9b && i < 0x2ef4){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2f00 && i <= 0x2fdf){
        if(i >= 0x2f00 && i < 0x2fd6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x2ff0 && i <= 0x2fff){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x3000 && i <= 0x303f){
        if(i == 0x3000){return SGEXTN::CoreText::FullCharacterType::SpaceBreak;}
        if(i >= 0x3001 && i < 0x3004){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x3004){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x3005){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x3006){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x3007){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i >= 0x3008 && i < 0x3012 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x3008 && i < 0x3012){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0x3012 && i < 0x3014){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3014 && i < 0x301c && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x3014 && i < 0x301c){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0x301c){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i == 0x301d){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0x301e && i < 0x3020){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0x3020){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3021 && i < 0x302a){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i >= 0x302a && i < 0x302e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x302e && i < 0x3030){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x3030){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x3031 && i < 0x3036){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x3036 && i < 0x3038){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3038 && i < 0x303b){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i == 0x303b){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x303c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x303d){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x303e && i < 0x3040){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3040 && i <= 0x309f){
        if(i >= 0x3041 && i < 0x3097){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x3099 && i < 0x309b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x309b && i < 0x309d){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x309d && i < 0x309f){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x309f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x30a0 && i <= 0x30ff){
        if(i == 0x30a0){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x30a1 && i < 0x30fb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x30fb){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x30fc && i < 0x30ff){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x30ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3100 && i <= 0x312f){
        if(i >= 0x3105 && i < 0x3130){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3130 && i <= 0x318f){
        if(i >= 0x3131 && i < 0x318f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3190 && i <= 0x319f){
        if(i >= 0x3190 && i < 0x3192){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3192 && i < 0x3196){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x3196 && i < 0x31a0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x31a0 && i <= 0x31bf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x31c0 && i <= 0x31ef){
        if(i >= 0x31c0 && i < 0x31e6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x31ef){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x31f0 && i <= 0x31ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x3200 && i <= 0x32ff){
        if(i >= 0x3200 && i < 0x321f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3220 && i < 0x322a){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x322a && i < 0x3248){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3248 && i < 0x3250){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x3250){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3251 && i < 0x3260){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x3260 && i < 0x3280){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x3280 && i < 0x328a){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x328a && i < 0x32b1){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x32b1 && i < 0x32c0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x32c0 && i < 0x3300){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x3300 && i <= 0x33ff){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x3400 && i <= 0x4dbf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x4dc0 && i <= 0x4dff){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0xa000 && i <= 0xa48f){
        if(i >= 0xa000 && i < 0xa015){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa015){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa016 && i < 0xa48d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa490 && i <= 0xa4cf){
        if(i >= 0xa490 && i < 0xa4c7){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa4d0 && i <= 0xa4ff){
        if(i >= 0xa4d0 && i < 0xa4f8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa4f8 && i < 0xa4fe){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa4fe && i < 0xa500){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa500 && i <= 0xa63f){
        if(i >= 0xa500 && i < 0xa60c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa60c){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa60d && i < 0xa610){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa610 && i < 0xa620){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa620 && i < 0xa62a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xa62a && i < 0xa62c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa640 && i <= 0xa69f){
        if(i >= 0xa640 && i < 0xa66e && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa640 && i < 0xa66e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xa66e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa66f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa670 && i < 0xa673){return SGEXTN::CoreText::FullCharacterType::EnclosingMark;}
        if(i == 0xa673){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa674 && i < 0xa67e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa67e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xa67f){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa680 && i < 0xa69c && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa680 && i < 0xa69c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa69c && i < 0xa69e){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa69e && i < 0xa6a0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa6a0 && i <= 0xa6ff){
        if(i >= 0xa6a0 && i < 0xa6e6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa6e6 && i < 0xa6f0){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i >= 0xa6f0 && i < 0xa6f2){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa6f2 && i < 0xa6f8){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa700 && i <= 0xa71f){
        if(i >= 0xa700 && i < 0xa717){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0xa717 && i < 0xa720){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa720 && i <= 0xa7ff){
        if(i >= 0xa720 && i < 0xa722){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0xa722 && i < 0xa72f && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa722 && i < 0xa72f){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa72f && i < 0xa732){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa732 && i < 0xa770 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa732 && i < 0xa770){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xa770){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa771 && i < 0xa779){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa779 && i < 0xa77e && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa779 && i < 0xa77e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa77e && i < 0xa788 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa77e && i < 0xa788){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xa788){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa789 && i < 0xa78b){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0xa78b || i == 0xa78d){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0xa78c || i == 0xa78e){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xa78f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa790 || i == 0xa792){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0xa791){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa793 && i < 0xa796){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xa796){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa797 && i < 0xa7aa && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa797 && i < 0xa7aa){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7aa && i < 0xa7af){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0xa7af){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7b0 && i < 0xa7b5){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7b5 && i < 0xa7c4 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7b5 && i < 0xa7c4){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7c4 && i < 0xa7c8){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0xa7c8 || i == 0xa7ca){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xa7c9){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7cb && i < 0xa7cd){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7cd && i < 0xa7dd && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0xa7cd && i < 0xa7dd){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7f1 && i < 0xa7f5){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0xa7f5){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0xa7f6){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xa7f7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa7f8 && i < 0xa7fa){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0xa7fa){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xa7fb && i < 0xa800){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa800 && i <= 0xa82f){
        if(i >= 0xa800 && i < 0xa802){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa802){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa803 && i < 0xa806){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa806){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa807 && i < 0xa80b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa80b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa80c && i < 0xa823){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa823 && i < 0xa825){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa825 && i < 0xa827){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa827){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa828 && i < 0xa82c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xa82c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa830 && i <= 0xa83f){
        if(i >= 0xa830 && i < 0xa836){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0xa836 && i < 0xa838){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xa838){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0xa839){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa840 && i <= 0xa87f){
        if(i >= 0xa840 && i < 0xa874){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa874 && i < 0xa878){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa880 && i <= 0xa8df){
        if(i >= 0xa880 && i < 0xa882){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa882 && i < 0xa8b4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa8b4 && i < 0xa8c4){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa8c4 && i < 0xa8c6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa8ce && i < 0xa8d0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa8d0 && i < 0xa8da){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa8e0 && i <= 0xa8ff){
        if(i >= 0xa8e0 && i < 0xa8f2){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa8f2 && i < 0xa8f8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa8f8 && i < 0xa8fb){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xa8fb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa8fc){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xa8fd && i < 0xa8ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa8ff){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa900 && i <= 0xa92f){
        if(i >= 0xa900 && i < 0xa90a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xa90a && i < 0xa926){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa926 && i < 0xa92e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa92e && i < 0xa930){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa930 && i <= 0xa95f){
        if(i >= 0xa930 && i < 0xa947){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa947 && i < 0xa952){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa952 && i < 0xa954){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xa95f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa960 && i <= 0xa97f){
        if(i >= 0xa960 && i < 0xa97d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa980 && i <= 0xa9df){
        if(i >= 0xa980 && i < 0xa983){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa983){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa984 && i < 0xa9b3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa9b3){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa9b4 && i < 0xa9b6){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa9b6 && i < 0xa9ba){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa9ba && i < 0xa9bc){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa9bc && i < 0xa9be){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xa9be && i < 0xa9c1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xa9c1 && i < 0xa9ce){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xa9cf){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa9d0 && i < 0xa9da){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xa9de && i < 0xa9e0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xa9e0 && i <= 0xa9ff){
        if(i >= 0xa9e0 && i < 0xa9e5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xa9e5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xa9e6){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xa9e7 && i < 0xa9f0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xa9f0 && i < 0xa9fa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xa9fa && i < 0xa9ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaa00 && i <= 0xaa5f){
        if(i >= 0xaa00 && i < 0xaa29){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xaa29 && i < 0xaa2f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaa2f && i < 0xaa31){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xaa31 && i < 0xaa33){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaa33 && i < 0xaa35){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xaa35 && i < 0xaa37){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaa40 && i < 0xaa43){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaa43){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaa44 && i < 0xaa4c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaa4c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xaa4d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xaa50 && i < 0xaa5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xaa5c && i < 0xaa60){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaa60 && i <= 0xaa7f){
        if(i >= 0xaa60 && i < 0xaa70){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaa70){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xaa71 && i < 0xaa77){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xaa77 && i < 0xaa7a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0xaa7a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaa7b || i == 0xaa7d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xaa7c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaa7e && i < 0xaa80){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaa80 && i <= 0xaadf){
        if(i >= 0xaa80 && i < 0xaab0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaab0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xaab1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xaab2 && i < 0xaab5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaab5 && i < 0xaab7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xaab7 && i < 0xaab9){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaab9 && i < 0xaabe){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xaabe && i < 0xaac0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0xaac0 || i == 0xaac2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaac1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaadb && i < 0xaadd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaadd){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xaade && i < 0xaae0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xaae0 && i <= 0xaaff){
        if(i >= 0xaae0 && i < 0xaaeb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xaaeb){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xaaec && i < 0xaaee){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xaaee && i < 0xaaf0){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0xaaf0 && i < 0xaaf2){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xaaf2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xaaf3 && i < 0xaaf5){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0xaaf5){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xaaf6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xab00 && i <= 0xab2f){
        if(i >= 0xab01 && i < 0xab07){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xab09 && i < 0xab0f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xab11 && i < 0xab17){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xab20 && i < 0xab27){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xab28 && i < 0xab2f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xab30 && i <= 0xab6f){
        if(i >= 0xab30 && i < 0xab5b){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xab5b){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0xab5c && i < 0xab60){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xab60 && i < 0xab69){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xab69){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xab6a && i < 0xab6c){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xab70 && i <= 0xabbf){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
    if(i >= 0xabc0 && i <= 0xabff){
        if(i >= 0xabc0 && i < 0xabe3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xabe3 && i < 0xabe5){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xabe5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xabe6 && i < 0xabe8){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xabe8){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xabe9 && i < 0xabeb){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xabeb){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xabec){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0xabed){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xabf0 && i < 0xabfa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xac00 && i <= 0xd7a3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0xd7b0 && i <= 0xd7ff){
        if(i >= 0xd7b0 && i < 0xd7c7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xd7cb && i < 0xd7fc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xd800 && i <= 0xdfff){return SGEXTN::CoreText::FullCharacterType::SurrogateCharacter;}
    if(i >= 0xe000 && i <= 0xf8ff){return SGEXTN::CoreText::FullCharacterType::PrivateUseCharacter;}
    if(i >= 0xf900 && i <= 0xfaff){
        if(i >= 0xf900 && i < 0xfa6e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfa70 && i < 0xfada){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfb00 && i <= 0xfb4f){
        if(i >= 0xfb00 && i < 0xfb07){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0xfb13 && i < 0xfb18){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xfb1d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xfb1e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0xfb1f && i < 0xfb29){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xfb29){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0xfb2a && i < 0xfb37){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfb38 && i < 0xfb3d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xfb3e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfb40 && i < 0xfb42){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfb43 && i < 0xfb45){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfb46 && i < 0xfb50){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if((i >= 0xfb50 && i <= 0xfdcf) || (i >= 0xfdf0 && i <= 0xfdff)){
        if(i >= 0xfb50 && i < 0xfbb2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfbb2 && i < 0xfbc3){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0xfbc3 && i < 0xfbd3){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xfbd3 && i < 0xfd3e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xfd3e){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0xfd3f){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0xfd40 && i < 0xfd50){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd50 && i < 0xfd90){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfd90 && i < 0xfd92){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xfd92 && i < 0xfdc8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfdc8 && i < 0xfdd0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xfdf0 && i < 0xfdfc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xfdfc){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0xfdfd && i < 0xfe00){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe00 && i <= 0xfe0f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
    if(i >= 0xfe10 && i <= 0xfe1f){
        if(i >= 0xfe10 && i < 0xfe17){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe17){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xfe18){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0xfe19){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe20 && i <= 0xfe2f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
    if(i >= 0xfe30 && i <= 0xfe4f){
        if(i == 0xfe30){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfe31 && i < 0xfe33){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0xfe33 && i < 0xfe35){return SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0xfe35 && i < 0xfe45 && i % 2 == 0){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xfe35 && i < 0xfe45){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i >= 0xfe45 && i < 0xfe47){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe47){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xfe48){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xfe49 && i < 0xfe4d){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfe4d && i < 0xfe50){return SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe50 && i <= 0xfe6f){
        if(i >= 0xfe50 && i < 0xfe53){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xfe54 && i < 0xfe58){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe58){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i == 0xfe59 || i == 0xfe5b || i == 0xfe5d){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xfe5a || i == 0xfe5c || i == 0xfe5e){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i >= 0xfe5f && i < 0xfe62){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe62){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0xfe63){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0xfe64 && i < 0xfe67){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0xfe68){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xfe69){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0xfe6a && i < 0xfe6c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfe70 && i <= 0xfeff){
        if(i >= 0xfe70 && i < 0xfe75){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xfe76 && i < 0xfefd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xfeff){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xff00 && i <= 0xffef){
        if(i >= 0xff01 && i < 0xff04){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xff04){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0xff05 && i < 0xff08){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xff08){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff09){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff0a || i == 0xff0c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xff0b){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0xff0d){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0xff0e && i < 0xff10){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff10 && i < 0xff1a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0xff1a && i < 0xff1c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff1c && i < 0xff1f){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0xff1f && i < 0xff21){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff21 && i < 0xff3b){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0xff3b){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff3c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0xff3d){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff3e || i == 0xff40){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0xff3f){return SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation;}
        if(i >= 0xff41 && i < 0xff5b){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0xff5b){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff5c || i == 0xff5e){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0xff5d){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff5f || i == 0xff62){return SGEXTN::CoreText::FullCharacterType::OpeningPunctuation;}
        if(i == 0xff60 || i == 0xff63){return SGEXTN::CoreText::FullCharacterType::ClosingPunctuation;}
        if(i == 0xff61){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff64 && i < 0xff66){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0xff66 && i < 0xff70){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0xff70){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xff71 && i < 0xff9e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xff9e && i < 0xffa0){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0xffa0 && i < 0xffbf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xffc2 && i < 0xffc8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xffca && i < 0xffd0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xffd2 && i < 0xffd8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xffda && i < 0xffdd){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0xffe0 && i < 0xffe2){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0xffe2){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i == 0xffe3){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i == 0xffe4){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xffe5 && i < 0xffe7){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i == 0xffe8){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0xffe9 && i < 0xffed){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0xffed && i < 0xffef){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xfff0 && i <= 0xffff){
        if(i >= 0xfff9 && i < 0xfffc){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0xfffc && i < 0xfffe){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10000 && i <= 0x1007f){
        if(i >= 0x10000 && i < 0x1000c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1000d && i < 0x10027){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10028 && i < 0x1003b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1003c && i < 0x1003e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1003f && i < 0x1004e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10050 && i < 0x1005e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10080 && i <= 0x100ff){
        if(i >= 0x10080 && i < 0x100fb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10100 && i <= 0x1013f){
        if(i >= 0x10100 && i < 0x10103){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10107 && i < 0x10134){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x10137 && i < 0x10140){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10140 && i <= 0x1018f){
        if(i >= 0x10140 && i < 0x10175){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i >= 0x10175 && i < 0x10179){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x10179 && i < 0x1018a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1018a && i < 0x1018c){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x1018c && i < 0x1018f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10190 && i <= 0x101cf){
        if(i >= 0x10190 && i < 0x1019d){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x101a0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x101d0 && i <= 0x101ff){
        if(i >= 0x101d0 && i < 0x101fd){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x101fd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10280 && i <= 0x1029f){
        if(i >= 0x10280 && i < 0x1029d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x102a0 && i <= 0x102df){
        if(i >= 0x102a0 && i < 0x102d1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x102e0 && i <= 0x102ff){
        if(i == 0x102e0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x102e1 && i < 0x102fc){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10300 && i <= 0x1032f){
        if(i >= 0x10300 && i < 0x10320){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10320 && i < 0x10324){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x1032d && i < 0x10330){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10330 && i <= 0x1034f){
        if(i >= 0x10330 && i < 0x10341){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x10341){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i >= 0x10342 && i < 0x1034a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1034a){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10350 && i <= 0x1037f){
        if(i >= 0x10350 && i < 0x10376){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10376 && i < 0x1037b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10380 && i <= 0x1039f){
        if(i >= 0x10380 && i < 0x1039e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1039f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x103a0 && i <= 0x103df){
        if(i >= 0x103a0 && i < 0x103c4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x103c8 && i < 0x103d0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x103d0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x103d1 && i < 0x103d6){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10400 && i <= 0x1044f){
        if(i >= 0x10400 && i < 0x10428){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10428 && i < 0x10450){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10450 && i <= 0x1047f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x10480 && i <= 0x104af){
        if(i >= 0x10480 && i < 0x1049e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x104a0 && i < 0x104aa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x104b0 && i <= 0x104ff){
        if(i >= 0x104b0 && i < 0x104d4){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x104d8 && i < 0x104fc){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10500 && i <= 0x1052f){
        if(i >= 0x10500 && i < 0x10528){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10530 && i <= 0x1056f){
        if(i >= 0x10530 && i < 0x10564){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1056f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10570 && i <= 0x105bf){
        if(i >= 0x10570 && i < 0x1057b){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1057c && i < 0x1058b){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1058c && i < 0x10593){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10594 && i < 0x10596){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10597 && i < 0x105a2){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x105a3 && i < 0x105b2){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x105b3 && i < 0x105ba){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x105bb && i < 0x105bd){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x105c0 && i <= 0x105ff){
        if(i >= 0x105c0 && i < 0x105f4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10600 && i <= 0x1077f){
        if(i >= 0x10600 && i < 0x10737){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10740 && i < 0x10756){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10760 && i < 0x10768){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10780 && i <= 0x107bf){
        if(i >= 0x10780 && i < 0x10786){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x10787 && i < 0x107b1){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x107b2 && i < 0x107bb){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10800 && i <= 0x1083f){
        if(i >= 0x10800 && i < 0x10806){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x10808){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1080a && i < 0x10836){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10837 && i < 0x10839){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1083c || i == 0x1083f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10840 && i <= 0x1085f){
        if(i >= 0x10840 && i < 0x10856){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x10857){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10858 && i < 0x10860){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10860 && i <= 0x1087f){
        if(i >= 0x10860 && i < 0x10877){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10877 && i < 0x10879){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x10879 && i < 0x10880){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10880 && i <= 0x108af){
        if(i >= 0x10880 && i < 0x1089f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x108a7 && i < 0x108b0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x108e0 && i <= 0x108ff){
        if(i >= 0x108e0 && i < 0x108f3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x108f4 && i < 0x108f6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x108fb && i < 0x10900){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10900 && i <= 0x1091f){
        if(i >= 0x10900 && i < 0x10916){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10916 && i < 0x1091c){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x1091f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10920 && i <= 0x1093f){
        if(i >= 0x10920 && i < 0x1093a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1093f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10940 && i <= 0x1095f){
        if(i >= 0x10940 && i < 0x1095a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10980 && i <= 0x1099f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x109a0 && i <= 0x109ff){
        if(i >= 0x109a0 && i < 0x109b8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x109bc && i < 0x109be){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x109be && i < 0x109c0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x109c0 && i < 0x109d0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x109d2 && i < 0x10a00){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10a00 && i <= 0x10a5f){
        if(i == 0x10a00){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10a01 && i < 0x10a04){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10a05 && i < 0x10a07){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10a0c && i < 0x10a10){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10a10 && i < 0x10a14){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10a15 && i < 0x10a18){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10a19 && i < 0x10a36){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10a38 && i < 0x10a3b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x10a3f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10a40 && i < 0x10a49){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x10a50 && i < 0x10a59){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10a60 && i <= 0x10a7f){
        if(i >= 0x10a60 && i < 0x10a7d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10a7d && i < 0x10a7f){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x10a7f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
    }
    if(i >= 0x10a80 && i <= 0x10a9f){
        if(i >= 0x10a80 && i < 0x10a9d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10a9d && i < 0x10aa0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10ac0 && i <= 0x10aff){
        if(i >= 0x10ac0 && i < 0x10ac8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x10ac8){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x10ac9 && i < 0x10ae5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10ae5 && i < 0x10ae7){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10aeb && i < 0x10af0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x10af0 && i < 0x10af7){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b00 && i <= 0x10b3f){
        if(i >= 0x10b00 && i < 0x10b36){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10b39 && i < 0x10b40){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b40 && i <= 0x10b5f){
        if(i >= 0x10b40 && i < 0x10b56){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10b58 && i < 0x10b60){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b60 && i <= 0x10b7f){
        if(i >= 0x10b60 && i < 0x10b73){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10b78 && i < 0x10b80){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10b80 && i <= 0x10baf){
        if(i >= 0x10b80 && i < 0x10b92){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10b99 && i < 0x10b9d){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10ba9 && i < 0x10bb0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10c00 && i <= 0x10c4f){
        if(i >= 0x10c00 && i < 0x10c49){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10c80 && i <= 0x10cff){
        if(i >= 0x10c80 && i < 0x10cb3){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10cc0 && i < 0x10cf3){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x10cfa && i < 0x10d00){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10d00 && i <= 0x10d3f){
        if(i >= 0x10d00 && i < 0x10d24){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10d24 && i < 0x10d28){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10d30 && i < 0x10d3a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10d40 && i <= 0x10d8f){
        if(i >= 0x10d40 && i < 0x10d4a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x10d4a && i < 0x10d4e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x10d4e){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x10d4f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10d50 && i < 0x10d66){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x10d69 && i < 0x10d6e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x10d6e){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i == 0x10d6f){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x10d70 && i < 0x10d86){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x10d8e && i < 0x10d90){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10e60 && i <= 0x10e7f){
        if(i >= 0x10e60 && i < 0x10e7f){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10e80 && i <= 0x10ebf){
        if(i >= 0x10e80 && i < 0x10eaa){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10eab && i < 0x10ead){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x10ead){return SGEXTN::CoreText::FullCharacterType::DashPunctuation;}
        if(i >= 0x10eb0 && i < 0x10eb2){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10ec0 && i <= 0x10eff){
        if(i >= 0x10ec2 && i < 0x10ec5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x10ec5){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x10ec6 && i < 0x10ec8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x10ed0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x10ed1 && i < 0x10ed9){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x10efa && i < 0x10f00){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10f00 && i <= 0x10f2f){
        if(i >= 0x10f00 && i < 0x10f1d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10f1d && i < 0x10f27){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x10f27){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10f30 && i <= 0x10f6f){
        if(i >= 0x10f30 && i < 0x10f46){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10f46 && i < 0x10f51){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10f51 && i < 0x10f55){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x10f55 && i < 0x10f5a){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10f70 && i <= 0x10faf){
        if(i >= 0x10f70 && i < 0x10f82){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10f82 && i < 0x10f86){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x10f86 && i < 0x10f8a){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10fb0 && i <= 0x10fdf){
        if(i >= 0x10fb0 && i < 0x10fc5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x10fc5 && i < 0x10fcc){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x10fe0 && i <= 0x10fff){
        if(i >= 0x10fe0 && i < 0x10ff7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11000 && i <= 0x1107f){
        if(i == 0x11000 || i == 0x11002){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11001){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11003 && i < 0x11038){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11038 && i < 0x11047){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11047 && i < 0x1104e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11052 && i < 0x11066){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x11066 && i < 0x11070){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x11070){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11071 && i < 0x11073){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11073 && i < 0x11075){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11075){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1107f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11080 && i <= 0x110cf){
        if(i >= 0x11080 && i < 0x11082){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11082){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11083 && i < 0x110b0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x110b0 && i < 0x110b3){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x110b3 && i < 0x110b7){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x110b7 && i < 0x110b9){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x110b9 && i < 0x110bb){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x110bb && i < 0x110bd){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x110bd){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x110be && i < 0x110c2){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x110c2){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x110cd){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x110d0 && i <= 0x110ff){
        if(i >= 0x110d0 && i < 0x110e9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x110f0 && i < 0x110fa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11100 && i <= 0x1114f){
        if(i >= 0x11100 && i < 0x11103){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11103 && i < 0x11127){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11127 && i < 0x1112c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1112c){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1112d && i < 0x11135){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11136 && i < 0x11140){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x11140 && i < 0x11144){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x11144 || i == 0x11147){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11145 && i < 0x11147){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11150 && i <= 0x1117f){
        if(i >= 0x11150 && i < 0x11173){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11173){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11174 && i < 0x11176){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x11176){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11180 && i <= 0x111df){
        if(i >= 0x11180 && i < 0x11182){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11182){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11183 && i < 0x111b3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x111b3 && i < 0x111b6){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x111b6 && i < 0x111bf){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x111bf && i < 0x111c1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x111c1 && i < 0x111c5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x111c5 && i < 0x111c9){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x111c9 && i < 0x111cd){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x111cd){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x111ce){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x111cf){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x111d0 && i < 0x111da){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x111da || i == 0x111dc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x111db){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x111dd && i < 0x111e0){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x111e0 && i <= 0x111ff){
        if(i >= 0x111e1 && i < 0x111f5){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11200 && i <= 0x1124f){
        if(i >= 0x11200 && i < 0x11212){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11213 && i < 0x1122c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1122c && i < 0x1122f){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1122f && i < 0x11232){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11232 && i < 0x11234){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11234){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11235){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11236 && i < 0x11238){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11238 && i < 0x1123e){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x1123e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1123f && i < 0x11241){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11241){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11280 && i <= 0x112af){
        if(i >= 0x11280 && i < 0x11287){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11288){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1128a && i < 0x1128e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1128f && i < 0x1129e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1129f && i < 0x112a9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x112a9){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x112b0 && i <= 0x112ff){
        if(i >= 0x112b0 && i < 0x112df){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x112df){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x112e0 && i < 0x112e3){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x112e3 && i < 0x112eb){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x112f0 && i < 0x112fa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11300 && i <= 0x1137f){
        if(i >= 0x11300 && i < 0x11302){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11302 && i < 0x11304){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11305 && i < 0x1130d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1130f && i < 0x11311){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11313 && i < 0x11329){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1132a && i < 0x11331){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11332 && i < 0x11334){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11335 && i < 0x1133a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1133b && i < 0x1133d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1133d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1133e && i < 0x11340){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11340){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11341 && i < 0x11345){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11347 && i < 0x11349){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1134b && i < 0x1134e){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11350){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11357){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1135d && i < 0x11362){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11362 && i < 0x11364){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11366 && i < 0x1136d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11370 && i < 0x11375){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11380 && i <= 0x113ff){
        if(i >= 0x11380 && i < 0x1138a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1138b || i == 0x1138e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11390 && i < 0x113b6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x113b7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x113b8 && i < 0x113bb){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x113bb && i < 0x113c1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x113c2 || i == 0x113c5){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x113c7 && i < 0x113cb){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x113cc && i < 0x113ce){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x113ce || i == 0x113d0 || i == 0x113d2){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x113cf){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x113d1 || i == 0x113d3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x113d4 && i < 0x113d6){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x113d7 && i < 0x113d9){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x113e1 && i < 0x113e3){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11400 && i <= 0x1147f){
        if(i >= 0x11400 && i < 0x11435){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11435 && i < 0x11438){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11438 && i < 0x11440){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11440 && i < 0x11442){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11442 && i < 0x11445){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11445){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11446){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11447 && i < 0x1144b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1144b && i < 0x11450){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11450 && i < 0x1145a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1145a && i < 0x1145c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x1145d){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x1145e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1145f && i < 0x11462){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11480 && i <= 0x114df){
        if(i >= 0x11480 && i < 0x114b0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x114b0 && i < 0x114b3){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x114b3 && i < 0x114b9){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x114b9){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x114ba){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x114bb && i < 0x114bf){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x114bf && i < 0x114c1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x114c1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x114c2 && i < 0x114c4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x114c4 && i < 0x114c6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x114c6){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x114c7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x114d0 && i < 0x114da){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11580 && i <= 0x115ff){
        if(i >= 0x11580 && i < 0x115af){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x115af && i < 0x115b2){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x115b2 && i < 0x115b6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x115b8 && i < 0x115bc){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x115bc && i < 0x115be){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x115be){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x115bf && i < 0x115c1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x115c1 && i < 0x115d8){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x115d8 && i < 0x115dc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x115dc && i < 0x115de){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11600 && i <= 0x1165f){
        if(i >= 0x11600 && i < 0x11630){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11630 && i < 0x11633){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11633 && i < 0x1163b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1163b && i < 0x1163d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1163d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1163e){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1163f && i < 0x11641){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11641 && i < 0x11644){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x11644){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11650 && i < 0x1165a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11660 && i <= 0x1167f){
        if(i >= 0x11660 && i < 0x1166d){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11680 && i <= 0x116cf){
        if(i >= 0x11680 && i < 0x116ab){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x116ab || i == 0x116ad){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x116ac){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x116ae && i < 0x116b0){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x116b0 && i < 0x116b6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x116b6){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x116b7){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x116b8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x116b9){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x116c0 && i < 0x116ca){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x116d0 && i <= 0x116ff){
        if(i >= 0x116d0 && i < 0x116e4){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11700 && i <= 0x1174f){
        if(i >= 0x11700 && i < 0x1171b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1171d || i == 0x1171f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1171e){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11720 && i < 0x11722){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11722 && i < 0x11726){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11726){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11727 && i < 0x1172c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11730 && i < 0x1173a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1173a && i < 0x1173c){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x1173c && i < 0x1173f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x1173f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x11740 && i < 0x11747){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11800 && i <= 0x1184f){
        if(i >= 0x11800 && i < 0x1182c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1182c && i < 0x1182f){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1182f && i < 0x11838){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11838){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11839 && i < 0x1183b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1183b){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x118a0 && i <= 0x118ff){
        if(i >= 0x118a0 && i < 0x118c0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x118c0 && i < 0x118e0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x118e0 && i < 0x118ea){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x118ea && i < 0x118f3){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x118ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11900 && i <= 0x1195f){
        if(i >= 0x11900 && i < 0x11907){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11909){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1190c && i < 0x11914){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11915 && i < 0x11917){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11918 && i < 0x11930){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11930 && i < 0x11936){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11937 && i < 0x11939){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1193b && i < 0x1193d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1193d || i == 0x11940 || i == 0x11942){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x1193e || i == 0x11943){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1193f || i == 0x11941){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11944 && i < 0x11947){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11950 && i < 0x1195a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x119a0 && i <= 0x119ff){
        if(i >= 0x119a0 && i < 0x119a8){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x119aa && i < 0x119d1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x119d1 && i < 0x119d4){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x119d4 && i < 0x119d8){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x119da && i < 0x119dc){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x119dc && i < 0x119e0){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x119e0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x119e1 || i == 0x119e3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x119e2){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x119e4){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11a00 && i <= 0x11a4f){
        if(i == 0x11a00){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11a01 && i < 0x11a0b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11a0b && i < 0x11a33){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11a33 && i < 0x11a39){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11a39){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11a3a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11a3b && i < 0x11a3f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11a3f && i < 0x11a47){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x11a47){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11a50 && i <= 0x11aaf){
        if(i == 0x11a50){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11a51 && i < 0x11a57){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11a57 && i < 0x11a59){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11a59 && i < 0x11a5c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11a5c && i < 0x11a8a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11a8a && i < 0x11a97){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11a97){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11a98 && i < 0x11a9a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11a9a && i < 0x11a9d){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x11a9d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11a9e && i < 0x11aa3){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11ab0 && i <= 0x11abf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x11ac0 && i <= 0x11aff){
        if(i >= 0x11ac0 && i < 0x11af9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11b00 && i <= 0x11b5f){
        if(i >= 0x11b00 && i < 0x11b0a){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11b60 && i <= 0x11b7f){
        if(i == 0x11b60){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11b61){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11b62 && i < 0x11b65){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11b65 || i == 0x11b67){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11b66){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11bc0 && i <= 0x11bff){
        if(i >= 0x11bc0 && i < 0x11be1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11be1){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11bf0 && i < 0x11bfa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11c00 && i <= 0x11c6f){
        if(i >= 0x11c00 && i < 0x11c09){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11c0a && i < 0x11c2f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11c2f){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11c30 && i < 0x11c37){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11c38 && i < 0x11c3e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11c3e){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11c3f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11c40){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11c41 && i < 0x11c46){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11c50 && i < 0x11c5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x11c5a && i < 0x11c6d){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11c70 && i <= 0x11cbf){
        if(i >= 0x11c70 && i < 0x11c72){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11c72 && i < 0x11c90){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11c92 && i < 0x11ca8){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11ca9){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11caa && i < 0x11cb1){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11cb1){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11cb2 && i < 0x11cb4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11cb4){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11cb5 && i < 0x11cb7){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11d00 && i <= 0x11d5f){
        if(i >= 0x11d00 && i < 0x11d07){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11d08 && i < 0x11d0a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11d0b && i < 0x11d31){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11d31 && i < 0x11d37){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11d3a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11d3c && i < 0x11d3e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11d3f && i < 0x11d46){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11d46){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11d47){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11d50 && i < 0x11d5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11d60 && i <= 0x11daf){
        if(i >= 0x11d60 && i < 0x11d66){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11d67 && i < 0x11d69){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11d6a && i < 0x11d8a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11d8a && i < 0x11d8f){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11d90 && i < 0x11d92){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11d93 && i < 0x11d95){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11d95 || i == 0x11d97){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11d96){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11d98){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11da0 && i < 0x11daa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11db0 && i <= 0x11def){
        if(i >= 0x11db0 && i < 0x11dd9){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11dd9){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x11dda && i < 0x11ddc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11de0 && i < 0x11dea){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        {return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x11ee0 && i <= 0x11eff){
        if(i >= 0x11ee0 && i < 0x11ef3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11ef3 && i < 0x11ef5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11ef5 && i < 0x11ef7){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11ef7 && i < 0x11ef9){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11f00 && i <= 0x11f5f){
        if(i >= 0x11f00 && i < 0x11f02){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11f02){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x11f03){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11f04 && i < 0x11f11){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11f12 && i < 0x11f34){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x11f34 && i < 0x11f36){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11f36 && i < 0x11f3b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x11f3e && i < 0x11f40){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i == 0x11f40 || i == 0x11f42){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x11f41){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x11f43 && i < 0x11f50){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x11f50 && i < 0x11f5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x11f5a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11fb0 && i <= 0x11fbf){
        if(i == 0x11fb0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x11fc0 && i <= 0x11fff){
        if(i >= 0x11fc0 && i < 0x11fd5){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x11fd5 && i < 0x11fdd){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x11fdd && i < 0x11fe1){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0x11fe1 && i < 0x11ff2){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x11fff){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x12000 && i <= 0x123ff){
        if(i >= 0x12000 && i < 0x1239a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        {return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x12400 && i <= 0x1247f){
        if(i >= 0x12400 && i < 0x1246f){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        if(i >= 0x12470 && i < 0x12475){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x12480 && i <= 0x1254f){
        if(i >= 0x12480 && i < 0x12544){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x12f90 && i <= 0x12fff){
        if(i >= 0x12f90 && i < 0x12ff1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x12ff1 && i < 0x12ff3){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x13000 && i <= 0x1342f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x13430 && i <= 0x1345f){
        if(i >= 0x13430 && i < 0x13440){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i == 0x13440){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x13441 && i < 0x13447){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x13447 && i < 0x13456){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x13460 && i <= 0x143ff){
        if(i >= 0x13460 && i < 0x143fb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x14400 && i <= 0x1467f){
        if(i >= 0x14400 && i < 0x14647){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16100 && i <= 0x1613f){
        if(i >= 0x16100 && i < 0x1611e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1611e && i < 0x1612a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1612a && i < 0x1612d){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1612d && i < 0x16130){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x16130 && i < 0x1613a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16800 && i <= 0x16a3f){
        if(i >= 0x16800 && i < 0x16a39){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        {return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x16a40 && i <= 0x16a6f){
        if(i >= 0x16a40 && i < 0x16a5f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16a60 && i < 0x16a6a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x16a6e && i < 0x16b00){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16a70 && i <= 0x16acf){
        if(i >= 0x16a70 && i < 0x16abf){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16ac0 && i < 0x16aca){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16ad0 && i <= 0x16aff){
        if(i >= 0x16ad0 && i < 0x16aee){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16af0 && i < 0x16af5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x16af5){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16b00 && i <= 0x16b8f){
        if(i >= 0x16b00 && i < 0x16b30){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16b30 && i < 0x16b37){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x16b37 && i < 0x16b3c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x16b3c && i < 0x16b40){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x16b40 && i < 0x16b44){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x16b44){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x16b45){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x16b50 && i < 0x16b5a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x16b5b && i < 0x16b62){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x16b63 && i < 0x16b78){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16b7d && i < 0x16b90){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16d40 && i <= 0x16d7f){
        if(i >= 0x16d40 && i < 0x16d43){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x16d43 && i < 0x16d6b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16b6b && i < 0x16d6d){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x16b6d && i < 0x16d70){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x16d70 && i < 0x16d7a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16e40 && i <= 0x16e9f){
        if(i >= 0x16e40 && i < 0x16e60){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x16e40 && i < 0x16e80){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x16e80 && i < 0x16e97){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x16e97 && i < 0x16e9b){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16ea0 && i <= 0x16edf){
        if(i >= 0x16ea0 && i < 0x16eb9){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x16ebb && i < 0x16ed4){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        {return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x16f00 && i <= 0x16f9f){
        if(i >= 0x16f00 && i < 0x16f4b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x16f4f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x16f50){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x16f51 && i < 0x16f88){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x16f8f && i < 0x16f93){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x16f93 && i < 0x16fa0){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x16fe0 && i <= 0x16fff){
        if(i >= 0x16fe0 && i < 0x16fe2){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x16fe2){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i == 0x16fe3){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x16fe4){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x16ff0 && i < 0x16ff2){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x16ff2 && i < 0x16ff4){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x16ff4 && i < 0x16ff7){return SGEXTN::CoreText::FullCharacterType::LetterNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x17000 && i <= 0x187ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x18800 && i <= 0x18aff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x18b00 && i <= 0x18cff){
        if(i >= 0x18b00 && i < 0x18cd6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x18cff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x18d00 && i <= 0x18d7f){
        if(i >= 0x18d00 && i < 0x18d1f){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x18d80 && i <= 0x18dff){
        if(i >= 0x18d80 && i < 0x18df3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1aff0 && i <= 0x1afff){
        if(i >= 0x1aff0 && i < 0x1aff4){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1aff5 && i < 0x1affc){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1affd && i < 0x1afff){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b000 && i <= 0x1b0ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
    if(i >= 0x1b100 && i <= 0x1b12f){
        if(i >= 0x1b100 && i < 0x1b123){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b130 && i <= 0x1b16f){
        if(i == 0x1b132){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1b150 && i < 0x1b153){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1b155){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1b164 && i < 0x1b168){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1b170 && i <= 0x1b2ff){
        if(i >= 0x1b170 && i < 0x1b2fc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1bc00 && i <= 0x1bc9f){
        if(i >= 0x1bc00 && i < 0x1bc6b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1bc70 && i < 0x1bc7d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1bc80 && i < 0x1bc89){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1bc90 && i < 0x1bc9a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1bc9c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1bc9d && i < 0x1bc9f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1bc9f){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1bca0 && i <= 0x1bcaf){
        if(i >= 0x1bca0 && i < 0x1bca4){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cc00 && i <= 0x1cebf){
        if(i >= 0x1cc00 && i < 0x1ccf0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ccf0 && i < 0x1ccfa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1ccfa && i < 0x1ccfd){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1cd00 && i < 0x1ceb4){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ceba && i < 0x1cec0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cec0 && i <= 0x1ceff){
        if(i >= 0x1cec0 && i < 0x1ced1){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1cee0 && i < 0x1cef0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x1cef0){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1cf00 && i <= 0x1cfcf){
        if(i >= 0x1cf00 && i < 0x1cf2e){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1cf30 && i < 0x1cf47){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1cf50 && i < 0x1cfc4){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d000 && i <= 0x1d0ff){
        if(i >= 0x1d000 && i < 0x1d0f6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d100 && i <= 0x1d1ff){
        if(i >= 0x1d100 && i < 0x1d127){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d129 && i < 0x1d165){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d165 && i < 0x1d167){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1d167 && i < 0x1d16a){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1d16a && i < 0x1d16d){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d16d && i < 0x1d173){return SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark;}
        if(i >= 0x1d173 && i < 0x1d17b){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0x1d17b && i < 0x1d183){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1d183 && i < 0x1d185){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d185 && i < 0x1d18c){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1d18c && i < 0x1d1aa){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d1aa && i < 0x1d1ae){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1d1ae && i < 0x1d1eb){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d200 && i <= 0x1d24f){
        if(i >= 0x1d200 && i < 0x1d242){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1d242 && i < 0x1d245){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1d245){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d2c0 && i <= 0x1d2df){
        if(i >= 0x1d2c0 && i < 0x1d2d4){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d2e0 && i <= 0x1d2ff){
        if(i >= 0x1d2e0 && i < 0x1d2f4){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d300 && i <= 0x1d35f){
        if(i >= 0x1d300 && i < 0x1d357){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d360 && i <= 0x1d37f){
        if(i >= 0x1d360 && i < 0x1d379){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d400 && i <= 0x1d7ff){
        if(i >= 0x1d400 && i < 0x1d41a){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d41a && i < 0x1d434){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d434 && i < 0x1d44e){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d44e && i < 0x1d455){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d456 && i < 0x1d468){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d468 && i < 0x1d482){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d482 && i < 0x1d49c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d49c){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d49e && i < 0x1d4a0){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d4a2){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4a5 && i < 0x1d4a7){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4a9 && i < 0x1d4ad){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4ae && i < 0x1d4b6){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4b6 && i < 0x1d4ba){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d4bb){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d4bd && i < 0x1d4c4){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d4c5 && i < 0x1d4d0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d4d0 && i < 0x1d4ea){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d4ea && i < 0x1d504){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d504 && i < 0x1d506){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d507 && i < 0x1d50b){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d50d && i < 0x1d515){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d516 && i < 0x1d51d){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d51e && i < 0x1d538){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d538 && i < 0x1d53a){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d53b && i < 0x1d53f){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d540 && i < 0x1d545){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d546){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d54a && i < 0x1d551){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d552 && i < 0x1d56c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d56c && i < 0x1d586){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d586 && i < 0x1d5a0){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d5a0 && i < 0x1d5ba){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d5ba && i < 0x1d5d4){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d5d4 && i < 0x1d5ee){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d5ee && i < 0x1d608){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d608 && i < 0x1d622){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d622 && i < 0x1d63c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d63c && i < 0x1d656){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d656 && i < 0x1d670){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d670 && i < 0x1d68a){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1d68a && i < 0x1d6a6){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d6a8 && i < 0x1d6c1){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d6c1){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d6c2 && i < 0x1d6db){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d6db){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d6dc && i < 0x1d6e2){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d6e2 && i < 0x1d6fb){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d6fb){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d6fc && i < 0x1d715){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d715){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d716 && i < 0x1d71c){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d71c && i < 0x1d735){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d735){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d736 && i < 0x1d74f){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d74f){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d750 && i < 0x1d756){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d756 && i < 0x1d76f){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d76f){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d770 && i < 0x1d789){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d789){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d78a && i < 0x1d790){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d790 && i < 0x1d7a9){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d7a9){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d7aa && i < 0x1d7c3){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d7c3){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        if(i >= 0x1d7c4 && i < 0x1d7ca){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1d7ca){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i == 0x1d7cb){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1d7ce && i < 0x1d800){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1d800 && i <= 0x1daaf){
        if(i >= 0x1d800 && i < 0x1da00){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1da00 && i < 0x1da37){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1da37 && i < 0x1da3b){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1da3b && i < 0x1da6d){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1da6d && i < 0x1da75){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x1da75){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1da76 && i < 0x1da84){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x1da84){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1da85 && i < 0x1da87){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1da87 && i < 0x1da8c){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        if(i >= 0x1da9b && i < 0x1daa0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1daa1 && i < 0x1dab0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1df00 && i <= 0x1dfff){
        if(i >= 0x1df00 && i < 0x1df0a){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i == 0x1df0a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1df0b && i < 0x1df1f){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1df25 && i < 0x1df2b){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e000 && i <= 0x1e02f){
        if(i >= 0x1e000 && i < 0x1e007){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e008 && i < 0x1e019){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e01b && i < 0x1e022){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e023 && i < 0x1e025){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e026 && i < 0x1e02b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e030 && i <= 0x1e08f){
        if(i >= 0x1e030 && i < 0x1e06e){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i == 0x1e08f){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e100 && i <= 0x1e14f){
        if(i >= 0x1e100 && i < 0x1e12d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e130 && i < 0x1e137){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e137 && i < 0x1e13e){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1e140 && i < 0x1e14a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x1e14e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1e14f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e290 && i <= 0x1e2bf){
        if(i >= 0x1e290 && i < 0x1e2ae){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1e2ae){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e2c0 && i <= 0x1e2ff){
        if(i >= 0x1e2c0 && i < 0x1e2ec){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e2ec && i < 0x1e2f0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e2f0 && i < 0x1e2fa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x1e2ff){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e4d0 && i <= 0x1e4ff){
        if(i >= 0x1e4d0 && i < 0x1e4eb){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1e4eb){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1e4ec && i < 0x1e4f0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e4f0 && i < 0x1e4fa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e5d0 && i <= 0x1e5ff){
        if(i >= 0x1e5d0 && i < 0x1e5ee){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e5ee && i < 0x1e5f0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1e5f0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e5f1 && i < 0x1e5fb){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x1e5ff){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e6c0 && i <= 0x1e6ff){
        if(i >= 0x1e6c0 && i < 0x1e6df){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e6e0 && i < 0x1e6e3){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1e6e3){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e6e4 && i < 0x1e6e6){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1e6e6){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e6e7 && i < 0x1e6ee){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e6ee && i < 0x1e6f0){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i >= 0x1e6f0 && i < 0x1e6f5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1e6f5){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1e6fe){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1e6ff){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e7e0 && i <= 0x1e7ff){
        if(i >= 0x1e7e0 && i < 0x1e7e7){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e7e8 && i < 0x1e7ec){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e7ed && i < 0x1e7ef){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e7f0 && i < 0x1e7ff){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e800 && i <= 0x1e8df){
        if(i >= 0x1e800 && i < 0x1e8c5){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1e8c7 && i < 0x1e8d0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x1e8d0 && i < 0x1e8d7){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1e900 && i <= 0x1e95f){
        if(i >= 0x1e900 && i < 0x1e922){return SGEXTN::CoreText::FullCharacterType::UppercaseLetter;}
        if(i >= 0x1e922 && i < 0x1e944){return SGEXTN::CoreText::FullCharacterType::LowercaseLetter;}
        if(i >= 0x1e944 && i < 0x1e94b){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
        if(i == 0x1e94b){return SGEXTN::CoreText::FullCharacterType::ModifierLetter;}
        if(i >= 0x1e950 && i < 0x1e95a){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i >= 0x1e95e && i < 0x1e960){return SGEXTN::CoreText::FullCharacterType::OtherPunctuation;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ec70 && i <= 0x1ecbf){
        if(i >= 0x1ec71 && i < 0x1ecac){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x1ecac){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ecad && i < 0x1ecb0){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x1ecb0){return SGEXTN::CoreText::FullCharacterType::CurrencySymbol;}
        if(i >= 0x1ecb1 && i < 0x1ecb5){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ed00 && i <= 0x1ed4f){
        if(i >= 0x1ed01 && i < 0x1ed2e){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i == 0x1ed2e){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1ed2f && i < 0x1ed3e){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1ee00 && i <= 0x1eeff){
        if(i >= 0x1ee00 && i < 0x1ee04){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee05 && i < 0x1ee20){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee21 && i < 0x1ee23){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1ee24 || i == 0x1ee27){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee29 && i < 0x1ee33){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee34 && i < 0x1ee38){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1ee39 || i == 0x1ee3b || i == 0x1ee42 || i == 0x1ee47 || i == 0x1ee49 || i == 0x1ee4b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee4d && i < 0x1ee50){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee51 && i < 0x1ee53){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1ee54){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee57 && i < 0x1ee60 && i % 2 == 1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee61 && i < 0x1ee63){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1ee64){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee67 && i < 0x1ee6b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee6c && i < 0x1ee73){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee74 && i < 0x1ee78){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee79 && i < 0x1ee7d){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i == 0x1ee7e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee80 && i < 0x1ee8a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1ee8b && i < 0x1ee9c){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1eea1 && i < 0x1eea4){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1eea5 && i < 0x1eeaa){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1eeab && i < 0x1eebc){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x1eef0 && i < 0x1eef2){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f000 && i <= 0x1f02f){
        if(i >= 0x1f000 && i < 0x1f02c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f030 && i <= 0x1f09f){
        if(i >= 0x1f030 && i < 0x1f094){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f0a0 && i <= 0x1f0ff){
        if(i >= 0x1f0a0 && i < 0x1f0af){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f0b1 && i < 0x1f0c0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f0c1 && i < 0x1f0d0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f0d1 && i < 0x1f0f6){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f100 && i <= 0x1f1ff){
        if(i >= 0x1f100 && i < 0x1f10d){return SGEXTN::CoreText::FullCharacterType::OtherNumber;}
        if(i >= 0x1f10d && i < 0x1f1ae){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f1e6 && i < 0x1f200){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f200 && i <= 0x1f2ff){
        if(i >= 0x1f200 && i < 0x1f203){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f210 && i < 0x1f23c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f240 && i < 0x1f249){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f250 && i < 0x1f252){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f260 && i < 0x1f266){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f300 && i <= 0x1f5ff){
        if(i >= 0x1f300 && i < 0x1f3fb){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f3fb && i < 0x1f400){return SGEXTN::CoreText::FullCharacterType::ModifierSymbol;}
        if(i >= 0x1f400 && i < 0x1f600){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        {return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;}
    }
    if(i >= 0x1f600 && i <= 0x1f64f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x1f650 && i <= 0x1f67f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x1f680 && i <= 0x1f6ff){
        if(i >= 0x1f680 && i < 0x1f6d9){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f6dc && i < 0x1f6ed){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f6f0 && i < 0x1f6fd){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f700 && i <= 0x1f77f){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x1f780 && i <= 0x1f7ff){
        if(i >= 0x1f780 && i < 0x1f7da){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f7e0 && i < 0x1f7ec){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x1f7f0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f800 && i <= 0x1f8ff){
        if(i >= 0x1f800 && i < 0x1f80c){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f810 && i < 0x1f848){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f850 && i < 0x1f85a){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f860 && i < 0x1f888){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f890 && i < 0x1f8ae){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f8b0 && i < 0x1f8bc){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f8c0 && i < 0x1f8c2){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1f8d0 && i < 0x1f8d9){return SGEXTN::CoreText::FullCharacterType::MathSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1f900 && i <= 0x1f9ff){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
    if(i >= 0x1fa00 && i <= 0x1fa6f){
        if(i >= 0x1fa00 && i < 0x1fa58){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fa60 && i < 0x1fa6e){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1fa70 && i <= 0x1faff){
        if(i >= 0x1fa70 && i < 0x1fa7d){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fa80 && i < 0x1fa8b){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fa8e && i < 0x1fac7){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i == 0x1fac8){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1facd && i < 0x1fadd){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fadf && i < 0x1faeb){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1faef && i < 0x1faf9){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x1fb00 && i <= 0x1fbff){
        if(i >= 0x1fb00 && i < 0x1fb93){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fb94 && i < 0x1fbf0){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        if(i >= 0x1fbf0 && i < 0x1fbfa){return SGEXTN::CoreText::FullCharacterType::DecimalDigit;}
        if(i == 0x1fbfa){return SGEXTN::CoreText::FullCharacterType::OtherSymbol;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0x20000 && i <= 0x3ffff){
        if(i >= 0x20000 && i < 0x2a6e0){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2a700 && i < 0x2b81e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2b820 && i < 0x2ceae){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2ceb0 && i < 0x2ebe1){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2ebf0 && i < 0x2ee5e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x2f800 && i < 0x2fa1e){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x30000 && i < 0x3134b){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        if(i >= 0x31350 && i < 0x3347a){return SGEXTN::CoreText::FullCharacterType::OtherLetter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe0000 && i <= 0xe007f){
        if(i == 0xe0001){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        if(i >= 0xe0020 && i < 0xe0080){return SGEXTN::CoreText::FullCharacterType::FormatCharacter;}
        return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
    }
    if(i >= 0xe0100 && i <= 0xe01ef){return SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark;}
    if(i >= 0xf0000 && i <= 0xffffd){return SGEXTN::CoreText::FullCharacterType::PrivateUseCharacter;}
    if(i >= 0x100000 && i <= 0x10fffd){return SGEXTN::CoreText::FullCharacterType::PrivateUseCharacter;}
    return SGEXTN::CoreText::FullCharacterType::UnassignedCharacter;
}

SGEXTN::CoreText::SimplifiedCharacterType getUnicodeSimplifiedCategory(int i){
    const SGEXTN::CoreText::FullCharacterType generalCategory = getUnicodeGeneralCategory(i);
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::UppercaseLetter){return SGEXTN::CoreText::SimplifiedCharacterType::Letter;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::LowercaseLetter){return SGEXTN::CoreText::SimplifiedCharacterType::Letter;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::TitlecaseLetter){return SGEXTN::CoreText::SimplifiedCharacterType::Letter;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::ModifierLetter){return SGEXTN::CoreText::SimplifiedCharacterType::Letter;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::OtherLetter){return SGEXTN::CoreText::SimplifiedCharacterType::Letter;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::ConnectorPunctuation){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::DashPunctuation){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::OpeningPunctuation){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::ClosingPunctuation){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::OpeningQuote){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::ClosingQuote){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::OtherPunctuation){return SGEXTN::CoreText::SimplifiedCharacterType::Punctuation;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::MathSymbol){return SGEXTN::CoreText::SimplifiedCharacterType::Symbol;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::CurrencySymbol){return SGEXTN::CoreText::SimplifiedCharacterType::Symbol;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::ModifierSymbol){return SGEXTN::CoreText::SimplifiedCharacterType::Symbol;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::OtherSymbol){return SGEXTN::CoreText::SimplifiedCharacterType::Symbol;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark){return SGEXTN::CoreText::SimplifiedCharacterType::Mark;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark){return SGEXTN::CoreText::SimplifiedCharacterType::Mark;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::EnclosingMark){return SGEXTN::CoreText::SimplifiedCharacterType::Mark;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::DecimalDigit){return SGEXTN::CoreText::SimplifiedCharacterType::Number;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::LetterNumber){return SGEXTN::CoreText::SimplifiedCharacterType::Number;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::OtherNumber){return SGEXTN::CoreText::SimplifiedCharacterType::Number;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::SpaceBreak){return SGEXTN::CoreText::SimplifiedCharacterType::Whitespace;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::LineBreak){return SGEXTN::CoreText::SimplifiedCharacterType::Whitespace;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::ParagraphBreak){return SGEXTN::CoreText::SimplifiedCharacterType::Whitespace;}
    return SGEXTN::CoreText::SimplifiedCharacterType::Other;
}

int getUnicodeDecimalDigit(int i){
    if(i >= 0x30 && i < 0x3a){return (i - 0x30);}
    if(i < 0x80){return -1;}
    if(i >= 0x4e00 && i <= 0x9fff){return -1;}
    if(i >= 0xbe6 && i < 0xbf0){return (i - 0xbe6);}
    if(i >= 0xb80 && i <= 0xbff){return -1;}
    if(i >= 0x2190 && i <= 0x23ff){return -1;}
    if(i >= 0x600 && i <= 0x1cff){
        if(i >= 0x660 && i < 0x66a){return (i - 0x660);}
        if(i >= 0x6f0 && i < 0x6fa){return (i - 0x6f0);}
        if(i >= 0x7c0 && i < 0x7ca){return (i - 0x7c0);}
        if(i >= 0x966 && i < 0x970){return (i - 0x966);}
        if(i >= 0x9e6 && i < 0x9f0){return (i - 0x9e6);}
        if(i >= 0xa66 && i < 0xa70){return (i - 0xa66);}
        if(i >= 0xae6 && i < 0xaf0){return (i - 0xae6);}
        if(i >= 0xb66 && i < 0xb70){return (i - 0xb66);}
        if(i >= 0xc66 && i < 0xc70){return (i - 0xc66);}
        if(i >= 0xce6 && i < 0xcf0){return (i - 0xce6);}
        if(i >= 0xd66 && i < 0xd70){return (i - 0xd66);}
        if(i >= 0xde6 && i < 0xdf0){return (i - 0xde6);}
        if(i >= 0xe50 && i < 0xe5a){return (i - 0xe50);}
        if(i >= 0xed0 && i < 0xeda){return (i - 0xed0);}
        if(i >= 0xf20 && i < 0xf2a){return (i - 0xf20);}
        if(i >= 0x1040 && i < 0x104a){return (i - 0x1040);}
        if(i >= 0x1090 && i < 0x109a){return (i - 0x1090);}
        if(i >= 0x17e0 && i < 0x17ea){return (i - 0x17e0);}
        if(i >= 0x1810 && i < 0x181a){return (i - 0x1810);}
        if(i >= 0x1946 && i < 0x1950){return (i - 0x1946);}
        if(i >= 0x19d0 && i < 0x19da){return (i - 0x19d0);}
        if(i >= 0x1a80 && i < 0x1a8a){return (i - 0x1a80);}
        if(i >= 0x1a90 && i < 0x1a9a){return (i - 0x1a90);}
        if(i >= 0x1b50 && i < 0x1b5a){return (i - 0x1b50);}
        if(i >= 0x1bb0 && i < 0x1bba){return (i - 0x1bb0);}
        if(i >= 0x1c40 && i < 0x1c4a){return (i - 0x1c40);}
        if(i >= 0x1c50 && i < 0x1c5a){return (i - 0x1c50);}
    }
    if(i >= 0xa600 && i <= 0xabff){
        if(i >= 0xa620 && i < 0xa62a){return (i - 0xa620);}
        if(i >= 0xa8d0 && i < 0xa8da){return (i - 0xa8d0);}
        if(i >= 0xa900 && i < 0xa90a){return (i - 0xa900);}
        if(i >= 0xa9d0 && i < 0xa9da){return (i - 0xa9d0);}
        if(i >= 0xa9f0 && i < 0xa9fa){return (i - 0xa9f0);}
        if(i >= 0xaa50 && i < 0xaa5a){return (i - 0xaa50);}
        if(i >= 0xabf0 && i < 0xabfa){return (i - 0xabf0);}
    }
    if(i >= 0xff10 && i < 0xff1a){return (i - 0xff10);}
    if(i >= 0x104a0 && i < 0x104aa){return (i - 0x104a0);}
    if(i >= 0x10d00 && i <= 0x11fff){
        if(i >= 0x10d30 && i < 0x10d3a){return (i - 0x10d30);}
        if(i >= 0x10d40 && i < 0x10d4a){return (i - 0x10d40);}
        if(i >= 0x11066 && i < 0x11070){return (i - 0x11066);}
        if(i >= 0x110f0 && i < 0x110fa){return (i - 0x110f0);}
        if(i >= 0x11136 && i < 0x11140){return (i - 0x11136);}
        if(i >= 0x111d0 && i < 0x111da){return (i - 0x111d0);}
        if(i >= 0x112f0 && i < 0x112fa){return (i - 0x112f0);}
        if(i >= 0x11450 && i < 0x1145a){return (i - 0x11450);}
        if(i >= 0x114d0 && i < 0x114da){return (i - 0x114d0);}
        if(i >= 0x11650 && i < 0x1165a){return (i - 0x11650);}
        if(i >= 0x116c0 && i < 0x116ca){return (i - 0x116c0);}
        if(i >= 0x116d0 && i < 0x116da){return (i - 0x116d0);}
        if(i >= 0x116da && i < 0x116e4){return (i - 0x116da);}
        if(i >= 0x11730 && i < 0x1173a){return (i - 0x11730);}
        if(i >= 0x118e0 && i < 0x118ea){return (i - 0x118e0);}
        if(i >= 0x11950 && i < 0x1195a){return (i - 0x11950);}
        if(i >= 0x11bf0 && i < 0x11bfa){return (i - 0x11bf0);}
        if(i >= 0x11c50 && i < 0x11c5a){return (i - 0x11c50);}
        if(i >= 0x11d50 && i < 0x11d5a){return (i - 0x11d50);}
        if(i >= 0x11da0 && i < 0x11daa){return (i - 0x11da0);}
        if(i >= 0x11de0 && i < 0x11dea){return (i - 0x11de0);}
        if(i >= 0x11f50 && i < 0x11f5a){return (i - 0x11f50);}
    }
    if(i >= 0x16100 && i <= 0x16dff){
        if(i >= 0x16130 && i < 0x1613a){return (i - 0x16130);}
        if(i >= 0x16a60 && i < 0x16a6a){return (i - 0x16a60);}
        if(i >= 0x16ac0 && i < 0x16aca){return (i - 0x16ac0);}
        if(i >= 0x16b50 && i < 0x16b5a){return (i - 0x16b50);}
        if(i >= 0x16d70 && i < 0x16d7a){return (i - 0x16d70);}
    }
    if(i >= 0x1cc00 && i <= 0x1ffff){
        if(i >= 0x1ccf0 && i < 0x1ccfa){return (i - 0x1ccf0);}
        if(i >= 0x1d7ce && i < 0x1d800){return ((i - 0x1d7ce) % 10);}
        if(i >= 0x1e140 && i < 0x1e14a){return (i - 0x1e140);}
        if(i >= 0x1e2f0 && i < 0x1e2fa){return (i - 0x1e2f0);}
        if(i >= 0x1e4f0 && i < 0x1e4fa){return (i - 0x1e4f0);}
        if(i >= 0x1e5f1 && i < 0x1e5fb){return (i - 0x1e5f1);}
        if(i >= 0x1e950 && i < 0x1e95a){return (i - 0x1e950);}
        if(i >= 0x1fbf0 && i < 0x1fbfa){return (i - 0x1fbf0);}
    }
    return -1;
}

float getUnicodeNumerical(int i){
    const int decimalDigit = getUnicodeDecimalDigit(i);
    if(decimalDigit != -1){return static_cast<float>(decimalDigit);}
    if(i < 0x80){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    if(i >= 0x4e00 && i <= 0x9fff){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    if(i >= 0xb80 && i <= 0xbff){
        if(i == 0xbf0){return 10.0f;}
        if(i == 0xbf1){return 100.0f;}
        if(i == 0xbf2){return 1000.0f;}
        return SGEXTN::Math::FloatLimits<float>::negativeInfinity();
    }
    if(i >= 0x2190 && i <= 0x23ff){return SGEXTN::Math::FloatLimits<float>::negativeInfinity();}
    if(i >= 0xb2 && i <= 0xbe){
        if(i == 0xb2){return 2.0f;}
        if(i == 0xb3){return 3.0f;}
        if(i == 0xb9){return 1.0f;}
        if(i == 0xbc){return 0.25f;}
        if(i == 0xbd){return 0.5f;}
        if(i == 0xbe){return 0.75f;}
    }
    if(i >= 0x900 && i <= 0xfff){
        if(i >= 0x9f4 && i <= 0x9f9){
            if(i == 0x9f4){return 0.0625f;}
            if(i == 0x9f5){return 0.125f;}
            if(i == 0x9f6){return 0.1875f;}
            if(i == 0x9f7){return 0.25f;}
            if(i == 0x9f8){return 0.75f;}
            if(i == 0x9f9){return 16.0f;}
        }
        if(i >= 0xb72 && i <= 0xb77){
            if(i == 0xb72){return 0.25f;}
            if(i == 0xb73){return 0.5f;}
            if(i == 0xb74){return 0.75f;}
            if(i == 0xb75){return 0.0625f;}
            if(i == 0xb76){return 0.125f;}
            if(i == 0xb77){return 0.1875f;}
        }
        if(i >= 0xc78 && i <= 0xc7e){
            if(i == 0xc78){return 0.0f;}
            if(i == 0xc79 || i == 0xc7c){return 1.0f;}
            if(i == 0xc7a || i == 0xc7d){return 2.0f;}
            if(i == 0xc7b || i == 0xc7e){return 3.0f;}
        }
        if(i >= 0xd58 && i <= 0xd5e){
            if(i == 0xd58){return 0.00625f;}
            if(i == 0xd59){return 0.025f;}
            if(i == 0xd5a){return 0.0375f;}
            if(i == 0xd5b){return 0.05f;}
            if(i == 0xd5c){return 0.1f;}
            if(i == 0xd5d){return 0.15f;}
            if(i == 0xd5e){return 0.2f;}
        }
        if(i >= 0xd70 && i <= 0xd78){
            if(i == 0xd70){return 10.0f;}
            if(i == 0xd71){return 100.0f;}
            if(i == 0xd72){return 1000.0f;}
            if(i == 0xd73){return 0.25f;}
            if(i == 0xd74){return 0.5f;}
            if(i == 0xd75){return 0.75f;}
            if(i == 0xd76){return 0.0625f;}
            if(i == 0xd77){return 0.125f;}
            if(i == 0xd78){return 0.1875f;}
        }
        if(i >= 0xf2a && i <= 0xf32){return (static_cast<float>((i - 0xf2a) % 10) + 0.5f);}
        if(i == 0xf33){return -0.5f;}
    }
    if(i >= 0x1300 && i <= 0x21ff){
        if(i >= 0x1369 && i <= 0x1371){return static_cast<float>(i - 0x1368);}
        if(i >= 0x1372 && i <= 0x137b){return (10.0f * static_cast<float>(i - 0x1371));}
        if(i == 0x137c){return 10000.0f;}
        if(i >= 0x16ee && i <= 0x16f0){return (17.0f + static_cast<float>(i - 0x16ee));}
        if(i >= 0x17f0 && i <= 0x17f9){return static_cast<float>(i - 0x17f0);}
        if(i == 0x19da){return 1.0f;}
        if(i == 0x2070){return 0.0f;}
        if(i >= 0x2074 && i <= 0x2079){return static_cast<float>(i - 0x2070);}
        if(i >= 0x2080 && i <= 0x2089){return static_cast<float>(i - 0x2080);}
        if(i >= 0x2150 && i <= 0x215f){
            if(i == 0x2150){return (1.0f / 7.0f);}
            if(i == 0x2151){return (1.0f / 9.0f);}
            if(i == 0x2152){return 0.1f;}
            if(i == 0x2153){return (1.0f / 3.0f);}
            if(i == 0x2154){return (2.0f / 3.0f);}
            if(i == 0x2155){return 0.2f;}
            if(i == 0x2156){return 0.4f;}
            if(i == 0x2157){return 0.6f;}
            if(i == 0x2158){return 0.8f;}
            if(i == 0x2159){return (1.0f / 6.0f);}
            if(i == 0x215a){return (5.0f / 6.0f);}
            if(i == 0x215b){return 0.125f;}
            if(i == 0x215c){return 0.375f;}
            if(i == 0x215d){return 0.625f;}
            if(i == 0x215e){return 0.875f;}
            if(i == 0x215f){return 1.0f;}
        }
        if(i >= 0x2160 && i <= 0x216b){return static_cast<float>(i - 0x215f);}
        if(i >= 0x216c && i <= 0x216f){
            if(i == 0x216c){return 50.0f;}
            if(i == 0x216d){return 100.0f;}
            if(i == 0x216e){return 500.0f;}
            if(i == 0x216f){return 1000.0f;}
        }
        if(i >= 0x2170 && i <= 0x217b){return static_cast<float>(i - 0x216f);}
        if(i >= 0x217c && i <= 0x2189){
            if(i == 0x217c){return 50.0f;}
            if(i == 0x217d){return 100.0f;}
            if(i == 0x217e){return 500.0f;}
            if(i == 0x217f){return 1000.0f;}
            if(i == 0x2180){return 1000.0f;}
            if(i == 0x2181){return 5000.0f;}
            if(i == 0x2182){return 10000.0f;}
            if(i == 0x2185){return 6.0f;}
            if(i == 0x2186){return 50.0f;}
            if(i == 0x2187){return 50000.0f;}
            if(i == 0x2188){return 100000.0f;}
            if(i == 0x2189){return 0.0f;}
        }
    }
    if(i >= 0x2400 && i <= 0x24ff){
        if(i >= 0x2460 && i <= 0x2473){return static_cast<float>(i - 0x245f);}
        if(i >= 0x2474 && i <= 0x2487){return static_cast<float>(i - 0x2473);}
        if(i >= 0x2488 && i <= 0x249b){return static_cast<float>(i - 0x2487);}
        if(i == 0x24ea){return 0.0;}
        if(i >= 0x24eb && i <= 0x24f4){return (10.0f + static_cast<float>(i - 0x24ea));}
        if(i >= 0x24f5 && i <= 0x24fe){return static_cast<float>(i - 0x24f4);}
        if(i == 0x24ff){return 0.0f;}
    }
    if(i >= 2700 && i <= 0x27ff){
        if(i >= 0x2776 && i <= 0x277f){return static_cast<float>(i - 0x2775);}
        if(i >= 0x2780 && i <= 0x2789){return static_cast<float>(i - 0x277f);}
        if(i >= 0x278a && i <= 0x2793){return static_cast<float>(i - 0x2789);}
    }
    if(i == 0x2cfd){return 0.5f;}
    if(i >= 0x3000 && i <= 0x32ff){
        if(i == 0x3007){return 0.0f;}
        if(i >= 0x3021 && i <= 0x3029){return static_cast<float>(i - 0x3020);}
        if(i >= 0x3038 && i <= 0x303a){return (10.0f * static_cast<float>(i - 0x3037));}
        if(i >= 0x3192 && i <= 0x3195){return static_cast<float>(i - 0x3191);}
        if(i >= 0x3220 && i <= 0x3229){return static_cast<float>(i - 0x321f);}
        if(i >= 0x3248 && i <= 0x324f){return (10.0f * static_cast<float>(i - 0x3247));}
        if(i >= 0x3251 && i <= 0x325f){return (20.0f + static_cast<float>(i - 0x3250));}
        if(i >= 0x3280 && i <= 0x3289){return static_cast<float>(i - 0x327f);}
        if(i >= 0x32b1 && i <= 0x32bf){return (35.0f + static_cast<float>(i - 0x32b0));}
    }
    if(i >= 0xa600 && i <= 0xa8ff){
        if(i >= 0xa6e6 && i <= 0xa6ee){return static_cast<float>(i - 0xa6e5);}
        if(i == 0xa6ef){return 0.0f;}
        if(i >= 0xa830 && i <= 0xa835){
            if(i == 0xa830){return 0.25f;}
            if(i == 0xa831){return 0.5f;}
            if(i == 0xa832){return 0.75f;}
            if(i == 0xa833){return 0.0625f;}
            if(i == 0xa834){return 0.125f;}
            if(i == 0xa835){return 0.1875f;}
        }
    }
    if(i >= 0xf900 && i <= 0x103ff){
        if(i == 0xf96b){return 3.0f;}
        if(i == 0xf973){return 10.0f;}
        if(i == 0xf978){return 2.0f;}
        if(i == 0xf9b2){return 0.0f;}
        if(i == 0xf9d1 || i == 0xf9d3){return 6.0f;}
        if(i == 0xf9fd){return 10.0f;}
        if(i >= 0x10107 && i <= 0x1010f){return static_cast<float>(i - 0x10106);}
        if(i >= 0x10110 && i <= 0x10118){return (10.0f * static_cast<float>(i - 0x1010f));}
        if(i >= 0x10119 && i <= 0x10121){return (100.0f * static_cast<float>(i - 0x10118));}
        if(i >= 0x10122 && i <= 0x1012a){return (1000.0f * static_cast<float>(i - 0x10121));}
        if(i >= 0x1012b && i <= 0x10133){return (10000.0f * static_cast<float>(i - 0x1012a));}
        if(i >= 0x10140 && i <= 0x1018b){
            if(i == 0x10140 || i == 0x1018b){return 0.25f;}
            if(i == 0x10141 || i == 0x10175 || i == 0x10176){return 0.5f;}
            if(i == 0x10142){return 1.0f;}
            if(i == 0x10143 || i == 0x10148 || i == 0x1014f || i == 0x1015f || i == 0x10173){return 5.0f;}
            if(i == 0x10144 || i == 0x1014a || i == 0x10151 || i == 0x10174){return 50.0f;}
            if(i == 0x10145 || i == 0x1014c || i == 0x10153){return 500.0f;}
            if(i == 0x10146 || i == 0x1014e || i == 0x10172){return 5000.0f;}
            if(i == 0x10147 || i == 0x10156){return 50000.0f;}
            if(i == 0x10149 || i == 0x10150 || i == 0x10157){return 10.0f;}
            if(i == 0x1014b || i == 0x10152 || i == 0x1016a){return 100.0f;}
            if(i == 0x1014d || i == 0x10154 || i == 0x10171){return 1000.0f;}
            if(i == 0x10155){return 10000.0f;}
            if(i >= 0x10158 && i <= 0x1015a){return 1.0f;}
            if(i >= 0x1015b && i <= 0x1015e){return 2.0f;}
            if(i >= 0x10160 && i <= 0x10164){return 10.0f;}
            if(i == 0x10165){return 30.0f;}
            if(i >= 0x10166 && i <= 0x10169){return 50.0f;}
            if(i == 0x1016b){return 300.0f;}
            if(i >= 0x1016c && i <= 0x10170){return 500.0f;}
            if(i == 0x10177){return (2.0f / 3.0f);}
            if(i == 0x10178){return 0.75f;}
            if(i == 0x1018a){return 0.0f;}
        }
        if(i >= 0x102e1 && i <= 0x102e9){return static_cast<float>(i - 0x102e0);}
        if(i >= 0x102ea && i <= 0x102f2){return (10.0f * static_cast<float>(i - 0x102e9));}
        if(i >= 0x102f3 && i <= 0x102fb){return (100.0f * static_cast<float>(i - 0x102f2));}
        if(i >= 0x10320 && i <= 0x10323){
            if(i == 0x10320){return 1.0f;}
            if(i == 0x10321){return 5.0f;}
            if(i == 0x10322){return 10.0f;}
            if(i == 0x10323){return 50.0f;}
        }
        if(i == 0x10341){return 90.0f;}
        if(i == 0x1034a){return 900.0f;}
        if(i >= 0x103d1 && i <= 0x103d5){
            if(i == 0x103d1){return 1.0f;}
            if(i == 0x103d2){return 2.0f;}
            if(i == 0x103d3){return 10.0f;}
            if(i == 0x103d4){return 20.0f;}
            if(i == 0x103d5){return 100.0f;}
        }
    }
    if(i >= 0x10800 && i <= 0x111ff){
        if(i >= 0x10858 && i <= 0x1085f){
            if(i >= 0x10858 && i <= 0x1085a){return static_cast<float>(i - 0x10857);}
            if(i == 0x1085b){return 10.0f;}
            if(i == 0x1085c){return 20.0f;}
            if(i == 0x1085d){return 100.0f;}
            if(i == 0x1085e){return 1000.0f;}
            if(i == 0x1085f){return 10000.0f;}
        }
        if(i >= 0x10879 && i <= 0x1087f){
            if(i >= 0x10879 && i <= 0x1087d){return static_cast<float>(i - 0x10878);}
            if(i == 0x1087e){return 10.0f;}
            if(i == 0x1087f){return 20.0f;}
        }
        if(i >= 0x108a7 && i <= 0x108af){
            if(i >= 0x108a7 && i <= 0x108aa){return static_cast<float>(i - 0x108a6);}
            if(i == 0x108ab){return 4.0f;}
            if(i == 0x108ac){return 5.0f;}
            if(i == 0x108ad){return 10.0f;}
            if(i == 0x108ae){return 20.0f;}
            if(i == 0x108af){return 100.0f;}
        }
        if(i >= 0x108fb && i <= 0x108ff){
            if(i == 0x108fb){return 1.0f;}
            if(i == 0x108fc){return 5.0f;}
            if(i == 0x108fd){return 10.0f;}
            if(i == 0x108fe){return 20.0f;}
            if(i == 0x108ff){return 100.0f;}
        }
        if(i >= 0x10916 && i <= 0x1091b){
            if(i == 0x10916){return 1.0f;}
            if(i == 0x10917){return 10.0f;}
            if(i == 0x10918){return 20.0f;}
            if(i == 0x10919){return 100.0f;}
            if(i == 0x1091a){return 2.0f;}
            if(i == 0x1091b){return 3.0f;}
        }
        if(i == 0x109bc){return (11.0f / 12.0f);}
        if(i == 0x109bd){return 0.5f;}
        if(i >= 0x109c0 && i <= 0x109c8){return static_cast<float>(i - 0x109bf);}
        if(i >= 0x109c9 && i <= 0x109cf){return (10.0f * static_cast<float>(i - 0x109c8));}
        if(i >= 0x109d2 && i <= 0x109da){return (100.0f * static_cast<float>(i - 0x109d1));}
        if(i >= 0x109db && i <= 0x109e3){return (1000.0f * static_cast<float>(i - 0x109da));}
        if(i >= 0x109e4 && i <= 0x109ec){return (10000.0f * static_cast<float>(i - 0x109e3));}
        if(i >= 0x109ed && i <= 0x109f5){return (100000.0f * static_cast<float>(i - 0x109ec));}
        if(i >= 0x109f6 && i <= 0x109ff){return (static_cast<float>(i - 0x109f5) / 12.0f);}
        if(i >= 0x10a40 && i <= 0x10a48){
            if(i >= 0x10a40 && i <= 0x10a43){return static_cast<float>(i - 0x10a3f);}
            if(i == 0x10a44){return 10.0f;}
            if(i == 0x10a45){return 20.0f;}
            if(i == 0x10a46){return 100.0f;}
            if(i == 0x10a47){return 1000.0f;}
            if(i == 0x10a48){return 0.5f;}
        }
        if(i == 0x10a7d){return 1.0f;}
        if(i == 0x10a7e){return 50.0f;}
        if(i >= 0x10a9d && i <= 0x10a9f){
            if(i == 0x10a9d){return 1.0f;}
            if(i == 0x10a9e){return 10.0f;}
            if(i == 0x10a9f){return 20.0f;}
        }
        if(i >= 0x10aeb && i <= 0x10aef){
            if(i == 0x10aeb){return 1.0f;}
            if(i == 0x10aec){return 5.0f;}
            if(i == 0x10aed){return 10.0f;}
            if(i == 0x10aee){return 20.0f;}
            if(i == 0x10aef){return 100.0f;}
        }
        if(i >= 0x10b58 && i <= 0x10b5f){
            if(i >= 0x10b58 && i <= 0x10b5b){return static_cast<float>(i - 0x10b57);}
            if(i == 0x10b5c){return 10.0f;}
            if(i == 0x10b5d){return 20.0f;}
            if(i == 0x10b5e){return 100.0f;}
            if(i == 0x10b5f){return 1000.0f;}
        }
        if(i >= 0x10b78 && i <= 0x10b7f){
            if(i >= 0x10b78 && i <= 0x10b7b){return static_cast<float>(i - 0x10b77);}
            if(i == 0x10b7c){return 10.0f;}
            if(i == 0x10b7d){return 20.0f;}
            if(i == 0x10b7e){return 100.0f;}
            if(i == 0x10b7f){return 1000.0f;}
        }
        if(i >= 0x10ba9 && i <= 0x10baf){
            if(i >= 0x10ba9 && i <= 0x10bac){return static_cast<float>(i - 0x10ba8);}
            if(i == 0x10bad){return 10.0f;}
            if(i == 0x10bae){return 20.0f;}
            if(i == 0x10baf){return 100.0f;}
        }
        if(i >= 0x10cfa && i <= 0x10cff){
            if(i == 0x10cfa){return 1.0f;}
            if(i == 0x10cfb){return 5.0f;}
            if(i == 0x10cfc){return 10.0f;}
            if(i == 0x10cfd){return 50.0f;}
            if(i == 0x10cfe){return 100.0f;}
            if(i == 0x10cff){return 1000.0f;}
        }
        if(i >= 0x10e60 && i <= 0x10e68){return static_cast<float>(i - 0x10e5f);}
        if(i >= 0x10e69 && i <= 0x10e71){return (10.0f * static_cast<float>(i - 0x10e68));}
        if(i >= 0x10e72 && i <= 0x10e7a){return (100.0f * static_cast<float>(i - 0x10e71));}
        if(i >= 0x10e7b && i <= 0x10e7e){
            if(i == 0x10e7b){return 0.5f;}
            if(i == 0x10e7c){return 0.25f;}
            if(i == 0x10e7d){return (1.0f / 3.0f);}
            if(i == 0x10e7e){return (2.0f / 3.0f);}
        }
        if(i >= 0x10f1d && i <= 0x10f21){return static_cast<float>(i - 0x10f1c);}
        if(i >= 0x10f22 && i <= 0x10f24){return (10.0f * static_cast<float>(i - 0x10f21));}
        if(i == 0x10f25){return 100.0f;}
        if(i == 0x10f26){return 0.5f;}
        if(i >= 0x10f51 && i <= 0x10f54){
            if(i == 0x10f51){return 1.0f;}
            if(i == 0x10f52){return 10.0f;}
            if(i == 0x10f53){return 20.0f;}
            if(i == 0x10f54){return 100.0f;}
        }
        if(i >= 0x10fc5 && i <= 0x10fc8){return static_cast<float>(i - 0x10fc4);}
        if(i >= 0x10fc9 && i <= 0x10fcb){
            if(i == 0x10fc9){return 10.0f;}
            if(i == 0x10fca){return 20.0f;}
            if(i == 0x10fcb){return 100.0f;}
        }
        if(i >= 0x11052 && i <= 0x1105a){return static_cast<float>(i - 0x11051);}
        if(i >= 0x1105b && i <= 0x11064){return (10.0f * static_cast<float>(i - 0x1105a));}
        if(i == 0x11065){return 1000.0f;}
        if(i >= 0x111e1 && i <= 0x111e9){return static_cast<float>(i - 0x111e0);}
        if(i >= 0x111ea && i <= 0x111f3){return (10.0f * static_cast<float>(i - 0x111e9));}
        if(i == 0x111f4){return 1000.0f;}
    }
    if(i >= 0x11700 && i <= 0x124ff){
        if(i == 0x1173a){return 10.0f;}
        if(i == 0x1173b){return 20.0f;}
        if(i >= 0x118ea && i <= 0x118f2){return (10.0f * static_cast<float>(i - 0x118e9));}
        if(i >= 0x11c5a && i <= 0x11c62){return static_cast<float>(i - 0x11c59);}
        if(i >= 0x11c63 && i <= 0x11c6c){return (10.0f * static_cast<float>(i - 0x11c62));}
        if(i >= 0x11fc0 && i <= 0x11fd4){
            if(i == 0x11fc0){return 0.003125f;}
            if(i == 0x11fc1){return 0.00625f;}
            if(i == 0x11fc2){return 0.0125f;}
            if(i == 0x11fc3){return 0.015625f;}
            if(i == 0x11fc4){return 0.025f;}
            if(i == 0x11fc5){return 0.03125f;}
            if(i == 0x11fc6){return 0.0375f;}
            if(i == 0x11fc7){return 0.046875f;}
            if(i == 0x11fc8){return 0.05f;}
            if(i == 0x11fc9 || i== 0x11fca){return 0.0625f;}
            if(i == 0x11fcb){return 0.1f;}
            if(i == 0x11fcc){return 0.125f;}
            if(i == 0x11fcd){return 0.15f;}
            if(i == 0x11fce){return 0.1875f;}
            if(i == 0x11fcf){return 0.2f;}
            if(i == 0x11fd0){return 0.25f;}
            if(i == 0x11fd1 || i == 0x11fd2){return 0.5f;}
            if(i == 0x11fd3){return 0.75f;}
            if(i == 0x11fd4){return 0.003125f;}
        }
        if(i == 0x12038 || i == 0x12039){return 1.0f;}
        if(i == 0x12079){return 1.0f;}
        if(i == 0x12226){return 0.5f;}
        if(i == 0x1222b){return 2.0f;}
        if(i == 0x1230b){return 1.0f;}
        if(i == 0x1230d){return 3.0f;}
        if(i == 0x12399){return 2.0f;}
        if(i >= 0x12400 && i <= 0x1246e){
            if(i >= 0x12400 && i <= 0x12407){return static_cast<float>(i - 0x123fe);}
            if(i >= 0x12408 && i <= 0x1240e){return static_cast<float>(i - 0x12405);}
            if(i >= 0x1240f && i <= 0x12414){return static_cast<float>(i - 0x1240b);}
            if(i >= 0x12415 && i <= 0x1241d){return static_cast<float>(i - 0x12414);}
            if(i >= 0x1241e && i <= 0x12422){return static_cast<float>(i - 0x1241d);}
            if(i == 0x12423){return 2.0f;}
            if(i >= 0x12424 && i <= 0x12425){return 3.0f;}
            if(i >= 0x12426 && i <= 0x1242b){return static_cast<float>(i - 0x12422);}
            if(i >= 0x1242c && i <= 0x1242e){return static_cast<float>(i - 0x1242b);}
            if(i >= 0x1242f && i <= 0x12431){return static_cast<float>(i - 0x1242c);}
            if(i == 0x12432){return 216000.0f;}
            if(i == 0x12433){return 432000.0f;}
            if(i >= 0x12434 && i <= 0x12436){return static_cast<float>(i - 0x12433);}
            if(i >= 0x12437 && i <= 0x12439){return static_cast<float>(i - 0x12434);}
            if(i >= 0x1243a && i <= 0x1243b){return 3.0f;}
            if(i >= 0x1243c && i <= 0x1243f){return 4.0f;}
            if(i == 0x12440){return 6.0f;}
            if(i >= 0x12441 && i <= 0x12443){return 7.0f;}
            if(i >= 0x12444 && i <= 0x12445){return 8.0f;}
            if(i >= 0x12446 && i <= 0x12449){return 9.0f;}
            if(i >= 0x1244a && i <= 0x1244e){return static_cast<float>(i - 0x12448);}
            if(i >= 0x1244f && i <= 0x12452){return static_cast<float>(i - 0x1244e);}
            if(i == 0x12453){return 4.0f;}
            if(i >= 0x12454 && i <= 0x12455){return 5.0f;}
            if(i == 0x12456 || i == 0x12459){return 2.0f;}
            if(i == 0x12457){return 3.0f;}
            if(i == 0x12458){return 1.0f;}
            if(i == 0x1245a || i == 0x1245d || i == 0x12465){return (1.0f / 3.0f);}
            if(i == 0x1245b || i == 0x1245e || i == 0x12466){return (2.0f / 3.0f);}
            if(i == 0x1245c){return (5.0f / 6.0f);}
            if(i == 0x1245f){return 0.125f;}
            if(i == 0x12460 || i == 0x12462 || i == 0x12463){return 0.25f;}
            if(i == 0x12461){return (1.0f / 6.0f);}
            if(i == 0x12464){return 0.5f;}
            if(i == 0x12467){return 40.0f;}
            if(i == 0x12468){return 50.0f;}
            if(i >= 0x12469 && i <= 0x1246e){return static_cast<float>(i - 0x12465);}
        }
    }
    if(i >= 0x16b00 && i <= 0x16fff){
        if(i >= 0x16b5b && i <= 0x16b61){
            if(i == 0x16b5b){return 10.0f;}
            if(i == 0x16b5c){return 100.0f;}
            if(i == 0x16b5d){return 10000.0f;}
            if(i == 0x16b5e){return 1000000.0f;}
            if(i == 0x16b5f){return 100000000.0f;}
            if(i == 0x16b60){return 10000000000.0f;}
            if(i == 0x16b61){return 1000000000000.0f;}
        }
        if(i >= 0x16e80 && i <= 0x16e93){return static_cast<float>(i - 0x16e80);}
        if(i >= 0x16e94 && i <= 0x16e96){return static_cast<float>(i - 0x16e93);}
        if(i >= 0x16ff4 && i <= 0x16ff6){return (1.0f + 0.5f * static_cast<float>(i - 0x16ff4));}
    }
    if(i >= 0x1d200 && i <= 0x1d3ff){
        if(i >= 0x1d2c0 && i <= 0x1d2d3){return static_cast<float>(i - 0x1d2c0);}
        if(i >= 0x1d2e0 && i <= 0x1d2f3){return static_cast<float>(i - 0x1d2e0);}
        if(i >= 0x1d360 && i <= 0x1d368){return static_cast<float>(i - 0x1d35f);}
        if(i >= 0x1d369 && i <= 0x1d371){return (10.0f * static_cast<float>(i - 0x1d368));}
        if(i >= 0x1d372 && i <= 0x1d376){return static_cast<float>(i - 0x1d371);}
        if(i == 0x1d377){return 1.0f;}
        if(i == 0x1d378){return 5.0f;}
    }
    if(i >= 0x1e8c7 && i <= 0x1e8cf){return static_cast<float>(i - 0x1e8c6);}
    if(i >= 0x1ec00 && i <= 0x1ed7f){
        if(i >= 0x1ec71 && i <= 0x1ec79){return static_cast<float>(i - 0x1ec70);}
        if(i >= 0x1ec7a && i <= 0x1ec82){return (10.0f * static_cast<float>(i - 0x1ec79));}
        if(i >= 0x1ec83 && i <= 0x1ec8b){return (100.0f * static_cast<float>(i - 0x1ec82));}
        if(i >= 0x1ec8c && i <= 0x1ec94){return (1000.0f * static_cast<float>(i - 0x1ec8b));}
        if(i >= 0x1ec95 && i <= 0x1ec9e){return (10000.0f * static_cast<float>(i - 0x1ec94));}
        if(i == 0x1ec9f){return 200000.0f;}
        if(i == 0x1eca0){return 100000.0f;}
        if(i == 0x1eca1){return 10000000.0f;}
        if(i == 0x1eca2){return 20000000.0f;}
        if(i >= 0x1eca3 && i <= 0x1ecab){return static_cast<float>(i - 0x1eca2);}
        if(i >= 0x1ecad && i <= 0x1ecaf){return (0.25f * static_cast<float>(i - 0x1ecac));}
        if(i == 0x1ecb1){return 1.0f;}
        if(i == 0x1ecb2){return 2.0f;}
        if(i == 0x1ecb3){return 10000.0f;}
        if(i == 0x1ecb4){return 100000.0f;}
        if(i >= 0x1ed01 && i <= 0x1ed09){return static_cast<float>(i - 0x1ed00);}
        if(i >= 0x1ed0a && i <= 0x1ed12){return (10.0f * static_cast<float>(i - 0x1ed09));}
        if(i >= 0x1ed13 && i <= 0x1ed1b){return (100.0f * static_cast<float>(i - 0x1ed12));}
        if(i >= 0x1ed1c && i <= 0x1ed24){return (1000.0f * static_cast<float>(i - 0x1ed1b));}
        if(i >= 0x1ed25 && i <= 0x1ed2d){return (10000.0f * static_cast<float>(i - 0x1ed24));}
        if(i >= 0x1ed2f && i <= 0x1ed37){return static_cast<float>(i - 0x1ed2d);}
        if(i == 0x1ed38){return 400.0f;}
        if(i == 0x1ed39){return 600.0f;}
        if(i == 0x1ed3a){return 2000.0f;}
        if(i == 0x1ed3b){return 10000.0f;}
        if(i == 0x1ed3c){return 0.5f;}
        if(i == 0x1ed3d){return (1.0f / 6.0f);}
    }
    if(i >= 0x1f100 && i <= 0x1f10f){
        if(i == 0x1f100 || i == 0x1f10b || i == 0x1f10c){return 0.0f;}
        if(i >= 0x1f101 && i <= 0x1f10a){return static_cast<float>(i - 0x1f101);}
    }
    if(i == 0x2f890){return 9.0f;}
    return SGEXTN::Math::FloatLimits<float>::negativeInfinity();
}

bool getUnicodeOtherGraphemeExtendProperty(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i == 0xbbe || i == 0xbd7){return true;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i == 0x9be || i == 0x9d7){return true;}
    if(i == 0xb3e || i == 0xb57){return true;}
    if(i >= 0xcc0 && i <= 0xcdf){
        if(i == 0xcc0){return true;}
        if(i == 0xcc2){return true;}
        if(i >= 0xcc7 && i <= 0xcc8){return true;}
        if(i >= 0xcca && i <= 0xccb){return true;}
        if(i >= 0xcd5 && i <= 0xcd6){return true;}
    }
    if(i == 0xd3e || i == 0xd57){return true;}
    if(i == 0xdcf || i == 0xddf){return true;}
    if(i == 0x1715 || i == 0x1734){return true;}
    if(i >= 0x1b00 && i <= 0x1bff){
        if(i == 0x1b35){return true;}
        if(i == 0x1b3b){return true;}
        if(i == 0x1b3d){return true;}
        if(i >= 0x1b43 && i <= 0x1b44){return true;}
        if(i == 0x1baa){return true;}
        if(i >= 0x1bf2 && i <= 0x1bf3){return true;}
    }
    if(i == 0x200c){return true;}
    if(i >= 0x302e && i <= 0x302f){return true;}
    if(i == 0xa953){return true;}
    if(i == 0xa9c0){return true;}
    if(i >= 0xff9e && i <= 0xff9f){return true;}
    if(i == 0x111c0){return true;}
    if(i == 0x11235){return true;}
    if(i >= 0x11300 && i <= 0x113ff){
        if(i == 0x1133e){return true;}
        if(i == 0x1134d){return true;}
        if(i == 0x11357){return true;}
        if(i == 0x113b8){return true;}
        if(i == 0x113c2){return true;}
        if(i == 0x113c5){return true;}
        if(i >= 0x113c7 && i <= 0x113c9){return true;}
        if(i == 0x113cf){return true;}
    }
    if(i == 0x114b0 || i == 0x114bd){return true;}
    if(i == 0x115af){return true;}
    if(i == 0x116b6){return true;}
    if(i == 0x11930 || i == 0x1193d){return true;}
    if(i == 0x11f41){return true;}
    if(i >= 0x16ff0 && i <= 0x16ff1){return true;}
    if(i >= 0x1d165 && i <= 0x1d166){return true;}
    if(i >= 0x1d16d && i <= 0x1d172){return true;}
    if(i >= 0xe0020 && i <= 0xe007f){return true;}
    return false;
}

bool getUnicodeDefaultInvisibleUnassigned(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i == 0x2065){return true;}
    if(i >= 0xfff0 && i <= 0xfff8){return true;}
    if(i == 0xe0000){return true;}
    if(i >= 0xe0002 && i <= 0xe001f){return true;}
    if(i >= 0xe0080 && i <= 0xe00ff){return true;}
    if(i >= 0xe01f0 && i <= 0xe0fff){return true;}
    return false;
}

bool getUnicodePrependConcatenationMark(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i >= 0x600 && i <= 0x605){return true;}
    if(i == 0x6dd){return true;}
    if(i == 0x70f){return true;}
    if(i >= 0x890 && i <= 0x891){return true;}
    if(i == 0x8e2){return true;}
    if(i == 0x110bd){return true;}
    if(i == 0x110cd){return true;}
    return false;
}

bool getUnicodeIndicSyllabicPrepend(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i == 0xd4e){return true;}
    if(i == 0x113d1){return true;}
    if(i == 0x11941){return true;}
    if(i == 0x11a86){return true;}
    if(i == 0x11d46){return true;}
    if(i == 0x11f02){return true;}
    if(i >= 0x111c2 && i <= 0x111c3){return true;}
    if(i == 0x1193f){return true;}
    if(i >= 0x11a84 && i <= 0x11a85){return true;}
    if(i >= 0x11a87 && i <= 0x11a89){return true;}
    return false;
}

bool getUnicodeSpacingCombiningMarkGraphemeClusterExtendProperty(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i == 0xbbe || i == 0xbd7){return true;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i == 0x9be){return true;}
    if(i == 0x9d7){return true;}
    if(i == 0xb3e){return true;}
    if(i == 0xb57){return true;}
    if(i >= 0xcc0 && i <= 0xdff){
        if(i == 0xcc0){return true;}
        if(i == 0xcc2){return true;}
        if(i >= 0xcc7 && i <= 0xcc8){return true;}
        if(i >= 0xcca && i <= 0xccb){return true;}
        if(i >= 0xcd5 && i <= 0xcd6){return true;}
        if(i == 0xd3e){return true;}
        if(i == 0xd57){return true;}
        if(i == 0xdcf){return true;}
        if(i == 0xddf){return true;}
    }
    if(i == 0x1715){return true;}
    if(i == 0x1734){return true;}
    if(i >= 0x1b00 && i <= 0x1bff){
        if(i == 0x1b35){return true;}
        if(i == 0x1b3b){return true;}
        if(i == 0x1b3d){return true;}
        if(i >= 0x1b43 && i <= 0x1b44){return true;}
        if(i == 0x1baa){return true;}
        if(i >= 0x1bf2 && i <= 0x1bf3){return true;}
    }
    if(i >= 0x302e && i <= 0x302f){return true;}
    if(i == 0xa953){return true;}
    if(i == 0xa9c0){return true;}
    if(i == 0x111c0){return true;}
    if(i == 0x11235){return true;}
    if(i >= 0x11300 && i <= 0x113ff){
        if(i == 0x1133e){return true;}
        if(i == 0x1134d){return true;}
        if(i == 0x11357){return true;}
        if(i == 0x113b8){return true;}
        if(i == 0x113c2){return true;}
        if(i == 0x113c5){return true;}
        if(i >= 0x113c7 && i <= 0x113c9){return true;}
        if(i == 0x113cf){return true;}
    }
    if(i == 0x114b0){return true;}
    if(i == 0x114bd){return true;}
    if(i == 0x115af){return true;}
    if(i == 0x116b6){return true;}
    if(i == 0x11930){return true;}
    if(i == 0x1193d){return true;}
    if(i == 0x11f41){return true;}
    if(i >= 0x16ff0 && i <= 0x16ff1){return true;}
    if(i >= 0x1d165 && i <= 0x1d166){return true;}
    if(i >= 0x1d16d && i <= 0x1d172){return true;}
    return false;
}

bool getUnicodeGraphemeSegmentationSpacingCombiningMarkException(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i >= 0x1000 && i <= 0x109f){
        if(i == 0x102b){return true;}
        if(i == 0x102c){return true;}
        if(i == 0x1038){return true;}
        if(i >= 0x1062 && i <= 0x1064){return true;}
        if(i >= 0x1067 && i <= 0x106d){return true;}
        if(i == 0x1083){return true;}
        if(i >= 0x1087 && i <= 0x108c){return true;}
        if(i == 0x108f){return true;}
        if(i >= 0x109a && i <= 0x109c){return true;}
    }
    if(i == 0x1a61 || i == 0x1a63 || i == 0x1a64){return true;}
    if(i == 0xaa7b || i == 0xaa7d){return true;}
    if(i == 0x11720 || i == 0x11721){return true;}
    return false;
}

bool isUnicodeEmoji(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2200 && i <= 0x22ff){return false;}
    if(i == 0xa9 || i == 0xae){return true;}
    if(i == 0x203c || i == 0x2049){return true;}
    if(i >= 0x2100 && i <= 0x21ff){
        if(i == 0x2122){return true;}
        if(i == 0x2139){return true;}
        if(i >= 0x2194 && i <= 0x2199){return true;}
        if(i >= 0x21a9 && i <= 0x21aa){return true;}
    }
    if(i >= 0x2300 && i <= 0x23ff){
        if(i >= 0x231a && i <= 0x231b){return true;}
        if(i == 0x2328){return true;}
        if(i == 0x23cf){return true;}
        if(i >= 0x23e9 && i <= 0x23f3){return true;}
        if(i >= 0x23f8 && i <= 0x23fa){return true;}
    }
    if(i == 0x24c2){return true;}
    if(i >= 0x25a0 && i <= 0x25ff){
        if(i >= 0x25aa && i <= 0x25ab){return true;}
        if(i == 0x25b6){return true;}
        if(i == 0x25c0){return true;}
        if(i >= 0x25fb && i <= 0x25fe){return true;}
    }
    if(i >= 0x2600 && i <= 0x26ff){
        if(i >= 0x2600 && i <= 0x2604){return true;}
        if(i == 0x260e){return true;}
        if(i == 0x2611){return true;}
        if(i >= 0x2614 && i <= 0x2615){return true;}
        if(i == 0x2618){return true;}
        if(i == 0x261d){return true;}
        if(i == 0x2620){return true;}
        if(i >= 0x2622 && i <= 0x2623){return true;}
        if(i == 0x2626){return true;}
        if(i == 0x262a){return true;}
        if(i >= 0x262e && i <= 0x262f){return true;}
        if(i >= 0x2638 && i <= 0x263a){return true;}
        if(i == 0x2640){return true;}
        if(i == 0x2642){return true;}
        if(i >= 0x2648 && i <= 0x2653){return true;}
        if(i >= 0x265f && i <= 0x2660){return true;}
        if(i == 0x2663){return true;}
        if(i >= 0x2665 && i <= 0x2666){return true;}
        if(i == 0x2668){return true;}
        if(i == 0x267b){return true;}
        if(i >= 0x267e && i <= 0x267f){return true;}
        if(i >= 0x2692 && i <= 0x2697){return true;}
        if(i == 0x2699){return true;}
        if(i >= 0x269b && i <= 0x269c){return true;}
        if(i >= 0x26a0 && i <= 0x26a1){return true;}
        if(i == 0x26a7){return true;}
        if(i >= 0x26aa && i <= 0x26ab){return true;}
        if(i >= 0x26b0 && i <= 0x26b1){return true;}
        if(i >= 0x26bd && i <= 0x26be){return true;}
        if(i >= 0x26c4 && i <= 0x26c5){return true;}
        if(i == 0x26c8){return true;}
        if(i >= 0x26ce && i <= 0x26cf){return true;}
        if(i == 0x26d1){return true;}
        if(i >= 0x26d3 && i <= 0x26d4){return true;}
        if(i >= 0x26e9 && i <= 0x26ea){return true;}
        if(i >= 0x26f0 && i <= 0x26f5){return true;}
        if(i >= 0x26f7 && i <= 0x26fa){return true;}
        if(i == 0x26fd){return true;}
    }
    if(i >= 0x2700 && i <= 0x27ff){
        if(i == 0x2702){return true;}
        if(i == 0x2705){return true;}
        if(i >= 0x2708 && i <= 0x270d){return true;}
        if(i == 0x270f){return true;}
        if(i == 0x2712){return true;}
        if(i == 0x2714){return true;}
        if(i == 0x2716){return true;}
        if(i == 0x271d){return true;}
        if(i == 0x2721){return true;}
        if(i == 0x2728){return true;}
        if(i >= 0x2733 && i <= 0x2734){return true;}
        if(i == 0x2744){return true;}
        if(i == 0x2747){return true;}
        if(i == 0x274c){return true;}
        if(i == 0x274e){return true;}
        if(i >= 0x2753 && i <= 0x2755){return true;}
        if(i == 0x2757){return true;}
        if(i >= 0x2763 && i <= 0x2764){return true;}
        if(i >= 0x2795 && i <= 0x2797){return true;}
        if(i == 0x27a1){return true;}
        if(i == 0x27b0){return true;}
        if(i == 0x27bf){return true;}
    }
    if(i >= 0x2934 && i <= 0x2935){return true;}
    if(i >= 0x2b00 && i <= 0x2b7f){
        if(i >= 0x2b05 && i <= 0x2b07){return true;}
        if(i >= 0x2b1b && i <= 0x2b1c){return true;}
        if(i == 0x2b50){return true;}
        if(i == 0x2b55){return true;}
    }
    if(i == 0x3030 || i == 0x303d){return true;}
    if(i == 0x3297 || i == 0x3299){return true;}
    if(i >= 0x1f000 && i <= 0x1ffff){
        if(i == 0x1f004){return true;}
        if(i >= 0x1f02c && i <= 0x1f02f){return true;}
        if(i >= 0x1f094 && i <= 0x1f09f){return true;}
        if(i >= 0x1f0af && i <= 0x1f0b0){return true;}
        if(i == 0x1f0c0){return true;}
        if(i >= 0x1f0cf && i <= 0x1f0d0){return true;}
        if(i >= 0x1f0f6 && i <= 0x1f0ff){return true;}
        if(i >= 0x1f170 && i <= 0x1f171){return true;}
        if(i >= 0x1f17e && i <= 0x1f17f){return true;}
        if(i == 0x1f18e){return true;}
        if(i >= 0x1f191 && i <= 0x1f19a){return true;}
        if(i >= 0x1f1ae && i <= 0x1f1e5){return true;}
        if(i >= 0x1f201 && i <= 0x1f20f){return true;}
        if(i == 0x1f21a){return true;}
        if(i == 0x1f22f){return true;}
        if(i >= 0x1f232 && i <= 0x1f23a){return true;}
        if(i >= 0x1f23c && i <= 0x1f23f){return true;}
        if(i >= 0x1f249 && i <= 0x1f25f){return true;}
        if(i >= 0x1f266 && i <= 0x1f321){return true;}
        if(i >= 0x1f324 && i <= 0x1f393){return true;}
        if(i >= 0x1f396 && i <= 0x1f397){return true;}
        if(i >= 0x1f399 && i <= 0x1f39b){return true;}
        if(i >= 0x1f39e && i <= 0x1f3f0){return true;}
        if(i >= 0x1f3f3 && i <= 0x1f3f5){return true;}
        if(i >= 0x1f3f7 && i <= 0x1f3fa){return true;}
        if(i >= 0x1f400 && i <= 0x1f4fd){return true;}
        if(i >= 0x1f4ff && i <= 0x1f53d){return true;}
        if(i >= 0x1f549 && i <= 0x1f54e){return true;}
        if(i >= 0x1f550 && i <= 0x1f567){return true;}
        if(i >= 0x1f56f && i <= 0x1f570){return true;}
        if(i >= 0x1f573 && i <= 0x1f57a){return true;}
        if(i == 0x1f587){return true;}
        if(i >= 0x1f58a && i <= 0x1f58d){return true;}
        if(i == 0x1f590){return true;}
        if(i >= 0x1f595 && i <= 0x1f596){return true;}
        if(i >= 0x1f5a4 && i <= 0x1f5a5){return true;}
        if(i == 0x1f5a8){return true;}
        if(i >= 0x1f5b1 && i <= 0x1f5b2){return true;}
        if(i == 0x1f5bc){return true;}
        if(i >= 0x1f5c2 && i <= 0x1f5c4){return true;}
        if(i >= 0x1f5d1 && i <= 0x1f5d3){return true;}
        if(i >= 0x1f5dc && i <= 0x1f5de){return true;}
        if(i == 0x1f5e1){return true;}
        if(i == 0x1f5e3){return true;}
        if(i == 0x1f5e8){return true;}
        if(i == 0x1f5ef){return true;}
        if(i == 0x1f5f3){return true;}
        if(i >= 0x1f5fa && i <= 0x1f64f){return true;}
        if(i >= 0x1f680 && i <= 0x1f6c5){return true;}
        if(i >= 0x1f6cb && i <= 0x1f6d2){return true;}
        if(i >= 0x1f6d5 && i <= 0x1f6e5){return true;}
        if(i == 0x1f6e9){return true;}
        if(i >= 0x1f6eb && i <= 0x1f6f0){return true;}
        if(i >= 0x1f6f3 && i <= 0x1f6ff){return true;}
        if(i >= 0x1f7da && i <= 0x1f7ff){return true;}
        if(i >= 0x1f80c && i <= 0x1f80f){return true;}
        if(i >= 0x1f848 && i <= 0x1f84f){return true;}
        if(i >= 0x1f85a && i <= 0x1f85f){return true;}
        if(i >= 0x1f888 && i <= 0x1f88f){return true;}
        if(i >= 0x1f8ae && i <= 0x1f8af){return true;}
        if(i >= 0x1f8bc && i <= 0x1f8bf){return true;}
        if(i >= 0x1f8c2 && i <= 0x1f8cf){return true;}
        if(i >= 0x1f8d9 && i <= 0x1f8ff){return true;}
        if(i >= 0x1f90c && i <= 0x1f93a){return true;}
        if(i >= 0x1f93c && i <= 0x1f945){return true;}
        if(i >= 0x1f947 && i <= 0x1f9ff){return true;}
        if(i >= 0x1fa58 && i <= 0x1fa5f){return true;}
        if(i >= 0x1fa6e && i <= 0x1faff){return true;}
        if(i >= 0x1fc00 && i <= 0x1fffd){return true;}
    }
    return false;
}

bool isUnicodeIndicGraphemeConsonant(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i >= 0x900 && i <= 0x9ff){
        if(i >= 0x915 && i <= 0x939){return true;}
        if(i >= 0x958 && i <= 0x95f){return true;}
        if(i >= 0x978 && i <= 0x97f){return true;}
        if(i >= 0x995 && i <= 0x9a8){return true;}
        if(i >= 0x9aa && i <= 0x9b0){return true;}
        if(i == 0x9b2){return true;}
        if(i >= 0x9b6 && i <= 0x9b9){return true;}
        if(i >= 0x9dc && i <= 0x9dd){return true;}
        if(i == 0x9df){return true;}
        if(i >= 0x9f0 && i <= 0x9f1){return true;}
    }
    if(i >= 0xa90 && i <= 0xaff){
        if(i >= 0xa95 && i <= 0xaa8){return true;}
        if(i >= 0xaaa && i <= 0xab0){return true;}
        if(i >= 0xab2 && i <= 0xab3){return true;}
        if(i >= 0xab5 && i <= 0xab9){return true;}
        if(i == 0xaf9){return true;}
    }
    if(i >= 0xb00 && i <= 0xb80){
        if(i >= 0xb15 && i <= 0xb28){return true;}
        if(i >= 0xb2a && i <= 0xb30){return true;}
        if(i >= 0xb32 && i <= 0xb33){return true;}
        if(i >= 0xb35 && i <= 0xb39){return true;}
        if(i >= 0xb5c && i <= 0xb5d){return true;}
        if(i == 0xb5f){return true;}
        if(i == 0xb71){return true;}
    }
    if(i >= 0xc00 && i <= 0xc8f){
        if(i >= 0xc15 && i <= 0xc28){return true;}
        if(i >= 0xc2a && i <= 0xc39){return true;}
        if(i >= 0xc58 && i <= 0xc5a){return true;}
    }
    if(i >= 0xd15 && i <= 0xd3a){return true;}
    if(i >= 0x1000 && i <= 0x108f){
        if(i >= 0x1000 && i <= 0x102a){return true;}
        if(i == 0x103f){return true;}
        if(i >= 0x1050 && i <= 0x1055){return true;}
        if(i >= 0x105a && i <= 0x105d){return true;}
        if(i == 0x1061){return true;}
        if(i >= 0x1065 && i <= 0x1066){return true;}
        if(i >= 0x106e && i <= 0x1070){return true;}
        if(i >= 0x1075 && i <= 0x1081){return true;}
        if(i == 0x108e){return true;}
    }
    if(i >= 0x1780 && i <= 0x17b3){return true;}
    if(i >= 0x1a20 && i <= 0x1a54){return true;}
    if(i >= 0x1b00 && i <= 0x1bff){
        if(i >= 0x1b0b && i <= 0x1b0c){return true;}
        if(i >= 0x1b13 && i <= 0x1b33){return true;}
        if(i >= 0x1b45 && i <= 0x1b4c){return true;}
        if(i >= 0x1b83 && i <= 0x1ba0){return true;}
        if(i >= 0x1bae && i <= 0x1baf){return true;}
        if(i >= 0x1bbb && i <= 0x1bbd){return true;}
    }
    if(i >= 0xa980 && i <= 0xa9ff){
        if(i >= 0xa989 && i <= 0xa98b){return true;}
        if(i >= 0xa98f && i <= 0xa9b2){return true;}
        if(i >= 0xa9e0 && i <= 0xa9e4){return true;}
        if(i >= 0xa9e7 && i <= 0xa9ef){return true;}
        if(i >= 0xa9fa && i <= 0xa9fe){return true;}
    }
    if(i >= 0xaa60 && i <= 0xaaff){
        if(i >= 0xaa60 && i <= 0xaa6f){return true;}
        if(i >= 0xaa71 && i <= 0xaa73){return true;}
        if(i == 0xaa7a){return true;}
        if(i >= 0xaa7e && i <= 0xaa7f){return true;}
        if(i >= 0xaae0 && i <= 0xaaea){return true;}
    }
    if(i >= 0xabc0 && i <= 0xabda){return true;}
    if(i >= 0x10a00 && i <= 0x10a3f){
        if(i == 0x10a00){return true;}
        if(i >= 0x10a10 && i <= 0x10a13){return true;}
        if(i >= 0x10a15 && i <= 0x10a17){return true;}
        if(i >= 0x10a19 && i <= 0x10a35){return true;}
    }
    if(i >= 0x11100 && i <= 0x1114f){
        if(i >= 0x11103 && i <= 0x11126){return true;}
        if(i == 0x11144){return true;}
        if(i == 0x11147){return true;}
    }
    if(i >= 0x11380 && i <= 0x113bf){
        if(i >= 0x11380 && i <= 0x11389){return true;}
        if(i == 0x1138b){return true;}
        if(i == 0x1138e){return true;}
        if(i >= 0x11390 && i <= 0x113b5){return true;}
    }
    if(i >= 0x11900 && i <= 0x1192f){
        if(i >= 0x11900 && i <= 0x11906){return true;}
        if(i == 0x11909){return true;}
        if(i >= 0x1190c && i <= 0x11913){return true;}
        if(i >= 0x11915 && i <= 0x11916){return true;}
        if(i >= 0x11918 && i <= 0x1192f){return true;}
    }
    if(i >= 0x11a00 && i <= 0x11aff){
        if(i == 0x11a00){return true;}
        if(i >= 0x11a0b && i <= 0x11a32){return true;}
        if(i == 0x11a50){return true;}
        if(i >= 0x11a5c && i <= 0x11a83){return true;}
    }
    if(i >= 0x11f00 && i <= 0x11f3f){
        if(i >= 0x11f04 && i <= 0x11f10){return true;}
        if(i >= 0x11f12 && i <= 0x11f33){return true;}
    }
    return false;
}

bool isUnicodeIndicGraphemeLinker(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){return false;}
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i == 0x94d || i == 0x9cd){return true;}
    if(i == 0xacd){return true;}
    if(i == 0xb4d){return true;}
    if(i == 0xc4d){return true;}
    if(i == 0xd4d){return true;}
    if(i == 0x1039){return true;}
    if(i == 0x17d2){return true;}
    if(i == 0x1a60){return true;}
    if(i == 0x1b44 || i == 0x1bab){return true;}
    if(i == 0xa9c0){return true;}
    if(i == 0xaaf6){return true;}
    if(i == 0x10a3f){return true;}
    if(i == 0x11133 || i == 0x113d0){return true;}
    if(i == 0x1193e){return true;}
    if(i == 0x11a47 || i == 0x11a99){return true;}
    if(i == 0x11f42){return true;}
    return false;
}

bool isUnicodeIndicGraphemeExtend(int i){
    if(i < 0x80){return false;}
    if(i >= 0x4e00 && i <= 0x9fff){return false;}
    if(i >= 0xb80 && i <= 0xbff){
        if(i == 0xb82 || i == 0xbbe || i == 0xbc0 || i == 0xbcd || i == 0xbd7){return true;}
        return false;
    }
    if(i >= 0x2190 && i <= 0x23ff){return false;}
    if(i >= 0x300 && i <= 0x36f){return true;}
    if(i >= 0x483 && i <= 0x489){return true;}
    if(i >= 0x590 && i <= 0x5cf){
        if(i >= 0x591 && i <= 0x5bd){return true;}
        if(i == 0x5bf){return true;}
        if(i >= 0x5c1 && i <= 0x5c2){return true;}
        if(i >= 0x5c4 && i <= 0x5c5){return true;}
        if(i == 0x5c7){return true;}
    }
    if(i >= 0x600 && i <= 0x6ff){
        if(i >= 0x610 && i <= 0x61a){return true;}
        if(i >= 0x64b && i <= 0x65f){return true;}
        if(i == 0x670){return true;}
        if(i >= 0x6d6 && i <= 0x6dc){return true;}
        if(i >= 0x6df && i <= 0x6e4){return true;}
        if(i >= 0x6e7 && i <= 0x6e8){return true;}
        if(i >= 0x6ea && i <= 0x6ed){return true;}
    }
    if(i >= 0x700 && i <= 0x7ff){
        if(i == 0x711){return true;}
        if(i >= 0x730 && i <= 0x74a){return true;}
        if(i >= 0x7a6 && i <= 0x7b0){return true;}
        if(i >= 0x7eb && i <= 0x7f3){return true;}
        if(i == 0x7fd){return true;}
    }
    if(i >= 0x800 && i <= 0x8ff){
        if(i >= 0x816 && i <= 0x819){return true;}
        if(i >= 0x81b && i <= 0x823){return true;}
        if(i >= 0x825 && i <= 0x827){return true;}
        if(i >= 0x829 && i <= 0x82d){return true;}
        if(i >= 0x859 && i <= 0x85b){return true;}
        if(i >= 0x897 && i <= 0x89f){return true;}
        if(i >= 0x8ca && i <= 0x8e1){return true;}
        if(i >= 0x8e3 && i <= 0x8ff){return true;}
    }
    if(i >= 0x900 && i <= 0x97f){
        if(i >= 0x900 && i <= 0x902){return true;}
        if(i == 0x93a){return true;}
        if(i == 0x93c){return true;}
        if(i >= 0x941 && i <= 0x948){return true;}
        if(i >= 0x951 && i <= 0x957){return true;}
        if(i >= 0x962 && i <= 0x963){return true;}
    }
    if(i >= 0x980 && i <= 0x9ff){
        if(i == 0x981){return true;}
        if(i == 0x9bc){return true;}
        if(i == 0x9be){return true;}
        if(i >= 0x9c1 && i <= 0x9c4){return true;}
        if(i == 0x9d7){return true;}
        if(i >= 0x9e2 && i <= 0x9e3){return true;}
        if(i == 0x9fe){return true;}
    }
    if(i >= 0xa00 && i <= 0xa7f){
        if(i >= 0xa01 && i <= 0xa02){return true;}
        if(i == 0xa3c){return true;}
        if(i >= 0xa41 && i <= 0xa42){return true;}
        if(i >= 0xa47 && i <= 0xa48){return true;}
        if(i >= 0xa4b && i <= 0xa4d){return true;}
        if(i == 0xa51){return true;}
        if(i >= 0xa70 && i <= 0xa71){return true;}
        if(i == 0xa75){return true;}
    }
    if(i >= 0xa80 && i <= 0xaff){
        if(i >= 0xa81 && i <= 0xa82){return true;}
        if(i == 0xabc){return true;}
        if(i >= 0xac1 && i <= 0xac5){return true;}
        if(i >= 0xac7 && i <= 0xac8){return true;}
        if(i >= 0xae2 && i <= 0xae3){return true;}
        if(i >= 0xafa && i <= 0xaff){return true;}
    }
    if(i >= 0xb00 && i <= 0xb7f){
        if(i == 0xb01){return true;}
        if(i == 0xb3c){return true;}
        if(i >= 0xb3e && i <= 0xb3f){return true;}
        if(i >= 0xb41 && i <= 0xb44){return true;}
        if(i >= 0xb55 && i <= 0xb57){return true;}
        if(i >= 0xb62 && i <= 0xb63){return true;}
    }
    if(i >= 0xc00 && i <= 0xc7f){
        if(i == 0xc00){return true;}
        if(i == 0xc04){return true;}
        if(i == 0xc3c){return true;}
        if(i >= 0xc3e && i <= 0xc40){return true;}
        if(i >= 0xc46 && i <= 0xc48){return true;}
        if(i >= 0xc4a && i <= 0xc4c){return true;}
        if(i >= 0xc55 && i <= 0xc56){return true;}
        if(i >= 0xc62 && i <= 0xc63){return true;}
    }
    if(i >= 0xc80 && i <= 0xcff){
        if(i == 0xc81){return true;}
        if(i == 0xcbc){return true;}
        if(i >= 0xcbf && i <= 0xcc0){return true;}
        if(i == 0xcc2){return true;}
        if(i >= 0xcc6 && i <= 0xcc8){return true;}
        if(i >= 0xcca && i <= 0xccd){return true;}
        if(i >= 0xcd5 && i <= 0xcd6){return true;}
        if(i >= 0xce2 && i <= 0xce3){return true;}
    }
    if(i >= 0xd00 && i <= 0xd7f){
        if(i >= 0xd00 && i <= 0xd01){return true;}
        if(i >= 0xd3b && i <= 0xd3c){return true;}
        if(i == 0xd3e){return true;}
        if(i >= 0xd41 && i <= 0xd44){return true;}
        if(i == 0xd57){return true;}
        if(i >= 0xd62 && i <= 0xd63){return true;}
    }
    if(i >= 0xd80 && i <= 0xdff){
        if(i == 0xd81){return true;}
        if(i == 0xdca){return true;}
        if(i == 0xdcf){return true;}
        if(i >= 0xdd2 && i <= 0xdd4){return true;}
        if(i == 0xdd6){return true;}
        if(i == 0xddf){return true;}
    }
    if(i >= 0xe00 && i <= 0xe7f){
        if(i == 0xe31){return true;}
        if(i >= 0xe34 && i <= 0xe3a){return true;}
        if(i >= 0xe47 && i <= 0xe4e){return true;}
    }
    if(i >= 0xe80 && i <= 0xeff){
        if(i == 0xeb1){return true;}
        if(i >= 0xeb4 && i <= 0xebc){return true;}
        if(i >= 0xec8 && i <= 0xece){return true;}
    }
    if(i >= 0xf00 && i <= 0xfff){
        if(i >= 0xf18 && i <= 0xf19){return true;}
        if(i == 0xf35){return true;}
        if(i == 0xf37){return true;}
        if(i == 0xf39){return true;}
        if(i >= 0xf71 && i <= 0xf7e){return true;}
        if(i >= 0xf80 && i <= 0xf84){return true;}
        if(i >= 0xf86 && i <= 0xf87){return true;}
        if(i >= 0xf8d && i <= 0xf97){return true;}
        if(i >= 0xf99 && i <= 0xfbc){return true;}
        if(i == 0xfc6){return true;}
    }
    if(i >= 0x1000 && i <= 0x109f){
        if(i >= 0x102d && i <= 0x1030){return true;}
        if(i >= 0x1032 && i <= 0x1037){return true;}
        if(i == 0x103a){return true;}
        if(i >= 0x103d && i <= 0x103e){return true;}
        if(i >= 0x1058 && i <= 0x1059){return true;}
        if(i >= 0x105e && i <= 0x1060){return true;}
        if(i >= 0x1071 && i <= 0x1074){return true;}
        if(i == 0x1082){return true;}
        if(i >= 0x1085 && i <= 0x1086){return true;}
        if(i == 0x108d){return true;}
        if(i == 0x109d){return true;}
    }
    if(i >= 0x135d && i <= 0x135f){return true;}
    if(i >= 0x1700 && i <= 0x17ff){
        if(i >= 0x1712 && i <= 0x1715){return true;}
        if(i >= 0x1732 && i <= 0x1734){return true;}
        if(i >= 0x1752 && i <= 0x1753){return true;}
        if(i >= 0x1772 && i <= 0x1773){return true;}
        if(i >= 0x17b4 && i <= 0x17b5){return true;}
        if(i >= 0x17b7 && i <= 0x17bd){return true;}
        if(i == 0x17c6){return true;}
        if(i >= 0x17c9 && i <= 0x17d1){return true;}
        if(i == 0x17d3){return true;}
        if(i == 0x17dd){return true;}
    }
    if(i >= 0x1800 && i <= 0x18af){
        if(i >= 0x180b && i <= 0x180d){return true;}
        if(i == 0x180f){return true;}
        if(i >= 0x1885 && i <= 0x1886){return true;}
        if(i == 0x18a9){return true;}
    }
    if(i >= 0x1920 && i <= 0x193f){
        if(i >= 0x1920 && i <= 0x1922){return true;}
        if(i >= 0x1927 && i <= 0x1928){return true;}
        if(i == 0x1932){return true;}
        if(i >= 0x1939 && i <= 0x193b){return true;}
    }
    if(i >= 0x1a00 && i <= 0x1aff){
        if(i >= 0x1a17 && i <= 0x1a18){return true;}
        if(i == 0x1a1b){return true;}
        if(i == 0x1a56){return true;}
        if(i >= 0x1a58 && i <= 0x1a5e){return true;}
        if(i == 0x1a62){return true;}
        if(i >= 0x1a65 && i <= 0x1a6c){return true;}
        if(i >= 0x1a73 && i <= 0x1a7c){return true;}
        if(i == 0x1a7f){return true;}
        if(i >= 0x1ab0 && i <= 0x1add){return true;}
        if(i >= 0x1ae0 && i <= 0x1aeb){return true;}
    }
    if(i >= 0x1b00 && i <= 0x1bff){
        if(i >= 0x1b00 && i <= 0x1b03){return true;}
        if(i >= 0x1b34 && i <= 0x1b3d){return true;}
        if(i >= 0x1b42 && i <= 0x1b43){return true;}
        if(i >= 0x1b6b && i <= 0x1b73){return true;}
        if(i >= 0x1b80 && i <= 0x1b81){return true;}
        if(i >= 0x1ba2 && i <= 0x1ba5){return true;}
        if(i >= 0x1ba8 && i <= 0x1baa){return true;}
        if(i >= 0x1bac && i <= 0x1bad){return true;}
        if(i == 0x1be6){return true;}
        if(i >= 0x1be8 && i <= 0x1be9){return true;}
        if(i == 0x1bed){return true;}
        if(i >= 0x1bef && i <= 0x1bf3){return true;}
    }
    if(i >= 0x1c00 && i <= 0x1cff){
        if(i >= 0x1c2c && i <= 0x1c33){return true;}
        if(i >= 0x1c36 && i <= 0x1c37){return true;}
        if(i >= 0x1cd0 && i <= 0x1cd2){return true;}
        if(i >= 0x1cd4 && i <= 0x1ce0){return true;}
        if(i >= 0x1ce2 && i <= 0x1ce8){return true;}
        if(i == 0x1ced){return true;}
        if(i == 0x1cf4){return true;}
        if(i >= 0x1cf8 && i <= 0x1cf9){return true;}
    }
    if(i >= 0x1dc0 && i <= 0x1dff){return true;}
    if(i == 0x200d){return true;}
    if(i >= 0x20d0 && i <= 0x20f0){return true;}
    if(i >= 0x2cef && i <= 0x2cf1){return true;}
    if(i == 0x2d7f){return true;}
    if(i >= 0x2de0 && i <= 0x2dff){return true;}
    if(i >= 0x302a && i <= 0x302f){return true;}
    if(i >= 0x3099 && i <= 0x309a){return true;}
    if(i >= 0xa660 && i <= 0xa6ff){
        if(i >= 0xa66f && i <= 0xa672){return true;}
        if(i >= 0xa674 && i <= 0xa67d){return true;}
        if(i >= 0xa69e && i <= 0xa69f){return true;}
        if(i >= 0xa6f0 && i <= 0xa6f1){return true;}
    }
    if(i >= 0xa800 && i <= 0xa8ff){
        if(i == 0xa802){return true;}
        if(i == 0xa806){return true;}
        if(i == 0xa80b){return true;}
        if(i >= 0xa825 && i <= 0xa826){return true;}
        if(i == 0xa82c){return true;}
        if(i >= 0xa8c4 && i <= 0xa8c5){return true;}
        if(i >= 0xa8e0 && i <= 0xa8f1){return true;}
        if(i == 0xa8ff){return true;}
    }
    if(i >= 0xa900 && i <= 0xa9ff){
        if(i >= 0xa926 && i <= 0xa92d){return true;}
        if(i >= 0xa947 && i <= 0xa951){return true;}
        if(i == 0xa953){return true;}
        if(i >= 0xa980 && i <= 0xa982){return true;}
        if(i == 0xa9b3){return true;}
        if(i >= 0xa9b6 && i <= 0xa9b9){return true;}
        if(i >= 0xa9bc && i <= 0xa9bd){return true;}
        if(i == 0xa9e5){return true;}
    }
    if(i >= 0xaa00 && i <= 0xaaff){
        if(i >= 0xaa29 && i <= 0xaa2e){return true;}
        if(i >= 0xaa31 && i <= 0xaa32){return true;}
        if(i >= 0xaa35 && i <= 0xaa36){return true;}
        if(i == 0xaa43){return true;}
        if(i == 0xaa4c){return true;}
        if(i == 0xaa7c){return true;}
        if(i == 0xaab0){return true;}
        if(i >= 0xaab2 && i <= 0xaab4){return true;}
        if(i >= 0xaab7 && i <= 0xaab8){return true;}
        if(i >= 0xaabe && i <= 0xaabf){return true;}
        if(i == 0xaac1){return true;}
        if(i >= 0xaaec && i <= 0xaaed){return true;}
    }
    if(i >= 0xabe0 && i <= 0xabef){
        if(i == 0xabe5){return true;}
        if(i == 0xabe8){return true;}
        if(i == 0xabed){return true;}
    }
    if(i == 0xfb1e){return true;}
    if(i >= 0xfe00 && i <= 0xfe0f){return true;}
    if(i >= 0xfe20 && i <= 0xfe2f){return true;}
    if(i >= 0xff9e && i <= 0xff9f){return true;}
    if(i >= 0x10000 && i <= 0x10fff){
        if(i == 0x101fd){return true;}
        if(i == 0x102e0){return true;}
        if(i >= 0x10376 && i <= 0x1037a){return true;}
        if(i >= 0x10a01 && i <= 0x10a03){return true;}
        if(i >= 0x10a05 && i <= 0x10a06){return true;}
        if(i >= 0x10a0c && i <= 0x10a0f){return true;}
        if(i >= 0x10a38 && i <= 0x10a3a){return true;}
        if(i >= 0x10ae5 && i <= 0x10ae6){return true;}
        if(i >= 0x10d24 && i <= 0x10d27){return true;}
        if(i >= 0x10d69 && i <= 0x10d6d){return true;}
        if(i >= 0x10eab && i <= 0x10eac){return true;}
        if(i >= 0x10efa && i <= 0x10eff){return true;}
        if(i >= 0x10f46 && i <= 0x10f50){return true;}
        if(i >= 0x10f82 && i <= 0x10f85){return true;}
    }
    if(i >= 0x11000 && i <= 0x11fff){
        if(i >= 0x11000 && i <= 0x110ff){
            if(i == 0x11001){return true;}
            if(i >= 0x11038 && i <= 0x11046){return true;}
            if(i == 0x11070){return true;}
            if(i >= 0x11073 && i <= 0x11074){return true;}
            if(i >= 0x1107f && i <= 0x11081){return true;}
            if(i >= 0x110b3 && i <= 0x110b6){return true;}
            if(i >= 0x110b9 && i <= 0x110ba){return true;}
            if(i == 0x110c2){return true;}
        }
        if(i >= 0x11100 && i <= 0x111ff){
            if(i >= 0x11100 && i <= 0x11102){return true;}
            if(i >= 0x11127 && i <= 0x1112b){return true;}
            if(i >= 0x1112d && i <= 0x11132){return true;}
            if(i == 0x11134){return true;}
            if(i == 0x11173){return true;}
            if(i >= 0x11180 && i <= 0x11181){return true;}
            if(i >= 0x111b6 && i <= 0x111be){return true;}
            if(i == 0x111c0){return true;}
            if(i >= 0x111c9 && i <= 0x111cc){return true;}
            if(i == 0x111cf){return true;}
        }
        if(i >= 0x11200 && i <= 0x112ff){
            if(i >= 0x1122f && i <= 0x11231){return true;}
            if(i >= 0x11234 && i <= 0x11237){return true;}
            if(i == 0x1123e){return true;}
            if(i == 0x11241){return true;}
            if(i == 0x112df){return true;}
            if(i >= 0x112e3 && i <= 0x112ea){return true;}
        }
        if(i >= 0x11300 && i <= 0x113ff){
            if(i >= 0x11300 && i <= 0x11301){return true;}
            if(i >= 0x1133b && i <= 0x1133c){return true;}
            if(i == 0x1133e){return true;}
            if(i == 0x11340){return true;}
            if(i == 0x1134d){return true;}
            if(i == 0x11357){return true;}
            if(i >= 0x11366 && i <= 0x1136c){return true;}
            if(i >= 0x11370 && i <= 0x11374){return true;}
            if(i == 0x113b8){return true;}
            if(i >= 0x113bb && i <= 0x113c0){return true;}
            if(i == 0x113c2){return true;}
            if(i == 0x113c5){return true;}
            if(i >= 0x113c7 && i <= 0x113c9){return true;}
            if(i >= 0x113ce && i <= 0x113cf){return true;}
            if(i == 0x113d2){return true;}
            if(i >= 0x113e1 && i <= 0x113e2){return true;}
        }
        if(i >= 0x11400 && i <= 0x114ff){
            if(i >= 0x11438 && i <= 0x1143f){return true;}
            if(i >= 0x11442 && i <= 0x11444){return true;}
            if(i == 0x11446){return true;}
            if(i == 0x1145e){return true;}
            if(i == 0x114b0){return true;}
            if(i >= 0x114b3 && i <= 0x114b8){return true;}
            if(i == 0x114ba){return true;}
            if(i == 0x114bd){return true;}
            if(i >= 0x114bf && i <= 0x114c0){return true;}
            if(i >= 0x114c2 && i <= 0x114c3){return true;}
        }
        if(i >= 0x115a0 && i <= 0x115ff){
            if(i == 0x115af){return true;}
            if(i >= 0x115b2 && i <= 0x115b5){return true;}
            if(i >= 0x115bc && i <= 0x115bd){return true;}
            if(i >= 0x115bf && i <= 0x115c0){return true;}
            if(i >= 0x115dc && i <= 0x115dd){return true;}
        }
        if(i >= 0x11600 && i <= 0x116ff){
            if(i >= 0x11633 && i <= 0x1163a){return true;}
            if(i == 0x1163d){return true;}
            if(i >= 0x1163f && i <= 0x11640){return true;}
            if(i == 0x116ab){return true;}
            if(i == 0x116ad){return true;}
            if(i >= 0x116b0 && i <= 0x116b7){return true;}
        }
        if(i >= 0x11710 && i <= 0x1172f){
            if(i == 0x1171d){return true;}
            if(i == 0x1171f){return true;}
            if(i >= 0x11722 && i <= 0x11725){return true;}
            if(i >= 0x11727 && i <= 0x1172b){return true;}
        }
        if(i >= 0x11820 && i <= 0x1183f){
            if(i >= 0x1182f && i <= 0x11837){return true;}
            if(i >= 0x11839 && i <= 0x1183a){return true;}
        }
        if(i >= 0x11900 && i <= 0x119ff){
            if(i == 0x11930){return true;}
            if(i >= 0x1193b && i <= 0x1193d){return true;}
            if(i == 0x11943){return true;}
            if(i >= 0x119d4 && i <= 0x119d7){return true;}
            if(i >= 0x119da && i <= 0x119db){return true;}
            if(i == 0x119e0){return true;}
        }
        if(i >= 0x11a00 && i <= 0x11aff){
            if(i >= 0x11a01 && i <= 0x11a0a){return true;}
            if(i >= 0x11a33 && i <= 0x11a38){return true;}
            if(i >= 0x11a3b && i <= 0x11a3e){return true;}
            if(i >= 0x11a51 && i <= 0x11a56){return true;}
            if(i >= 0x11a59 && i <= 0x11a5b){return true;}
            if(i >= 0x11a8a && i <= 0x11a96){return true;}
            if(i == 0x11a98){return true;}
        }
        if(i >= 0x11b60 && i <= 0x11b6f){
            if(i == 0x11b60){return true;}
            if(i >= 0x11b62 && i <= 0x11b64){return true;}
            if(i == 0x11b66){return true;}
        }
        if(i >= 0x11c00 && i <= 0x11cff){
            if(i >= 0x11c30 && i <= 0x11c36){return true;}
            if(i >= 0x11c38 && i <= 0x11c3d){return true;}
            if(i == 0x11c3f){return true;}
            if(i >= 0x11c92 && i <= 0x11ca7){return true;}
            if(i >= 0x11caa && i <= 0x11cb0){return true;}
            if(i >= 0x11cb2 && i <= 0x11cb3){return true;}
            if(i >= 0x11cb5 && i <= 0x11cb6){return true;}
        }
        if(i >= 0x11d00 && i <= 0x11dff){
            if(i >= 0x11d31 && i <= 0x11d36){return true;}
            if(i == 0x11d3a){return true;}
            if(i >= 0x11d3c && i <= 0x11d3d){return true;}
            if(i >= 0x11d3f && i <= 0x11d45){return true;}
            if(i == 0x11d47){return true;}
            if(i >= 0x11d90 && i <= 0x11d91){return true;}
            if(i == 0x11d95){return true;}
            if(i == 0x11d97){return true;}
        }
        if(i >= 0x11ef3 && i <= 0x11ef4){return true;}
        if(i >= 0x11f00 && i <= 0x11fff){
            if(i >= 0x11f00 && i <= 0x11f01){return true;}
            if(i >= 0x11f36 && i <= 0x11f3a){return true;}
            if(i >= 0x11f40 && i <= 0x11f41){return true;}
            if(i == 0x11f5a){return true;}
        }
    }
    if(i >= 0x13400 && i <= 0x134ff){
        if(i == 0x13440){return true;}
        if(i >= 0x13447 && i <= 0x13455){return true;}
    }
    if(i >= 0x16000 && i <= 0x16fff){
        if(i >= 0x1611e && i <= 0x16129){return true;}
        if(i >= 0x1612d && i <= 0x1612f){return true;}
        if(i >= 0x16af0 && i <= 0x16af4){return true;}
        if(i >= 0x16b30 && i <= 0x16b36){return true;}
        if(i == 0x16f4f){return true;}
        if(i >= 0x16f8f && i <= 0x16f92){return true;}
        if(i == 0x16fe4){return true;}
        if(i >= 0x16ff0 && i <= 0x16ff1){return true;}
    }
    if(i >= 0x1bc9d && i <= 0x1bc9e){return true;}
    if(i >= 0x1cf00 && i <= 0x1cf2d){return true;}
    if(i >= 0x1cf30 && i <= 0x1cf46){return true;}
    if(i >= 0x1d000 && i <= 0x1dfff){
        if(i >= 0x1d165 && i <= 0x1d169){return true;}
        if(i >= 0x1d16d && i <= 0x1d172){return true;}
        if(i >= 0x1d17b && i <= 0x1d182){return true;}
        if(i >= 0x1d185 && i <= 0x1d18b){return true;}
        if(i >= 0x1d1aa && i <= 0x1d1ad){return true;}
        if(i >= 0x1d242 && i <= 0x1d244){return true;}
        if(i >= 0x1da00 && i <= 0x1da36){return true;}
        if(i >= 0x1da3b && i <= 0x1da6c){return true;}
        if(i == 0x1da75){return true;}
        if(i == 0x1da84){return true;}
        if(i >= 0x1da9b && i <= 0x1da9f){return true;}
        if(i >= 0x1daa1 && i <= 0x1daaf){return true;}
    }
    if(i >= 0x1e000 && i <= 0x1efff){
        if(i >= 0x1e000 && i <= 0x1e006){return true;}
        if(i >= 0x1e008 && i <= 0x1e018){return true;}
        if(i >= 0x1e01b && i <= 0x1e021){return true;}
        if(i >= 0x1e023 && i <= 0x1e024){return true;}
        if(i >= 0x1e026 && i <= 0x1e02a){return true;}
        if(i == 0x1e08f){return true;}
        if(i >= 0x1e130 && i <= 0x1e136){return true;}
        if(i == 0x1e2ae){return true;}
        if(i >= 0x1e2ec && i <= 0x1e2ef){return true;}
        if(i >= 0x1e4ec && i <= 0x1e4ef){return true;}
        if(i >= 0x1e5ee && i <= 0x1e5ef){return true;}
        if(i == 0x1e6e3){return true;}
        if(i == 0x1e6e6){return true;}
        if(i >= 0x1e6ee && i <= 0x1e6ef){return true;}
        if(i == 0x1e6f5){return true;}
        if(i >= 0x1e8d0 && i <= 0x1e8d6){return true;}
        if(i >= 0x1e944 && i <= 0x1e94a){return true;}
    }
    if(i >= 0x1f3fb && i <= 0x1f3ff){return true;}
    if(i >= 0xe0020 && i <= 0xe007f){return true;}
    if(i >= 0xe0100 && i <= 0xe01ef){return true;}
    return false;
}

#define U8(str) reinterpret_cast<const char*>(u8##str)
const char* lookupEquiv_0x00c0_to_0x00ff_Table[] = { U8("\u0041\u0300"), U8("\u0041\u0301"), U8("\u0041\u0302"), U8("\u0041\u0303"), U8("\u0041\u0308"), U8("\u0041\u030a"), U8(""), U8("\u0043\u0327"), U8("\u0045\u0300"), U8("\u0045\u0301"), U8("\u0045\u0302"), U8("\u0045\u0308"), U8("\u0049\u0300"), U8("\u0049\u0301"), U8("\u0049\u0302"), U8("\u0049\u0308"), U8(""), U8("\u004e\u0303"), U8("\u004f\u0300"), U8("\u004f\u0301"), U8("\u004f\u0302"), U8("\u004f\u0303"), U8("\u004f\u0308"), U8(""), U8(""), U8("\u0055\u0300"), U8("\u0055\u0301"), U8("\u0055\u0302"), U8("\u0055\u0308"), U8("\u0059\u0301"), U8(""), U8(""), U8("\u0061\u0300"), U8("\u0061\u0301"), U8("\u0061\u0302"), U8("\u0061\u0303"), U8("\u0061\u0308"), U8("\u0061\u030a"), U8(""), U8("\u0063\u0327"), U8("\u0065\u0300"), U8("\u0065\u0301"), U8("\u0065\u0302"), U8("\u0065\u0308"), U8("\u0069\u0300"), U8("\u0069\u0301"), U8("\u0069\u0302"), U8("\u0069\u0308"), U8(""), U8("\u006e\u0303"), U8("\u006f\u0300"), U8("\u006f\u0301"), U8("\u006f\u0302"), U8("\u006f\u0303"), U8("\u006f\u0308"), U8(""), U8(""), U8("\u0075\u0300"), U8("\u0075\u0301"), U8("\u0075\u0302"), U8("\u0075\u0308"), U8("\u0079\u0301"), U8(""), U8("\u0079\u0308") };

const char* lookupEquiv_0x0100_to_0x017e_Table[] = { U8("\u0041\u0304"), U8("\u0061\u0304"), U8("\u0041\u0306"), U8("\u0061\u0306"), U8("\u0041\u0328"), U8("\u0061\u0328"), U8("\u0043\u0301"), U8("\u0063\u0301"), U8("\u0043\u0302"), U8("\u0063\u0302"), U8("\u0043\u0307"), U8("\u0063\u0307"), U8("\u0043\u030c"), U8("\u0063\u030c"), U8("\u0044\u030c"), U8("\u0064\u030c"), U8(""), U8(""), U8("\u0045\u0304"), U8("\u0065\u0304"), U8("\u0045\u0306"), U8("\u0065\u0306"), U8("\u0045\u0307"), U8("\u0065\u0307"), U8("\u0045\u0328"), U8("\u0065\u0328"), U8("\u0045\u030c"), U8("\u0065\u030c"), U8("\u0047\u0302"), U8("\u0067\u0302"), U8("\u0047\u0306"), U8("\u0067\u0306"), U8("\u0047\u0307"), U8("\u0067\u0307"), U8("\u0047\u0327"), U8("\u0067\u0327"), U8("\u0048\u0302"), U8("\u0068\u0302"), U8(""), U8(""), U8("\u0049\u0303"), U8("\u0069\u0303"), U8("\u0049\u0304"), U8("\u0069\u0304"), U8("\u0049\u0306"), U8("\u0069\u0306"), U8("\u0049\u0328"), U8("\u0069\u0328"), U8("\u0049\u0307"), U8(""), U8(""), U8(""), U8("\u004a\u0302"), U8("\u006a\u0302"), U8("\u004b\u0327"), U8("\u006b\u0327"), U8(""), U8("\u004c\u0301"), U8("\u006c\u0301"), U8("\u004c\u0327"), U8("\u006c\u0327"), U8("\u004c\u030c"), U8("\u006c\u030c"), U8(""), U8(""), U8(""), U8(""), U8("\u004e\u0301"), U8("\u006e\u0301"), U8("\u004e\u0327"), U8("\u006e\u0327"), U8("\u004e\u030c"), U8("\u006e\u030c"), U8(""), U8(""), U8(""), U8("\u004f\u0304"), U8("\u006f\u0304"), U8("\u004f\u0306"), U8("\u006f\u0306"), U8("\u004f\u030b"), U8("\u006f\u030b"), U8(""), U8(""), U8("\u0052\u0301"), U8("\u0072\u0301"), U8("\u0052\u0327"), U8("\u0072\u0327"), U8("\u0052\u030c"), U8("\u0072\u030c"), U8("\u0053\u0301"), U8("\u0073\u0301"), U8("\u0053\u0302"), U8("\u0073\u0302"), U8("\u0053\u0327"), U8("\u0073\u0327"), U8("\u0053\u030c"), U8("\u0073\u030c"), U8("\u0054\u0327"), U8("\u0074\u0327"), U8("\u0054\u030c"), U8("\u0074\u030c"), U8(""), U8(""), U8("\u0055\u0303"), U8("\u0075\u0303"), U8("\u0055\u0304"), U8("\u0075\u0304"), U8("\u0055\u0306"), U8("\u0075\u0306"), U8("\u0055\u030a"), U8("\u0075\u030a"), U8("\u0055\u030b"), U8("\u0075\u030b"), U8("\u0055\u0328"), U8("\u0075\u0328"), U8("\u0057\u0302"), U8("\u0077\u0302"), U8("\u0059\u0302"), U8("\u0079\u0302"), U8("\u0059\u0308"), U8("\u005a\u0301"), U8("\u007a\u0301"), U8("\u005a\u0307"), U8("\u007a\u0307"), U8("\u005a\u030c"), U8("\u007a\u030c") };

const char* lookupEquiv_0x01cd_to_0x01ff_Table[] = { U8("\u0041\u030c"), U8("\u0061\u030c"), U8("\u0049\u030c"), U8("\u0069\u030c"), U8("\u004f\u030c"), U8("\u006f\u030c"), U8("\u0055\u030c"), U8("\u0075\u030c"), U8("\u00dc\u0304"), U8("\u00fc\u0304"), U8("\u00dc\u0301"), U8("\u00fc\u0301"), U8("\u00dc\u030c"), U8("\u00fc\u030c"), U8("\u00dc\u0300"), U8("\u00fc\u0300"), U8(""), U8("\u00c4\u0304"), U8("\u00e4\u0304"), U8("\u0226\u0304"), U8("\u0227\u0304"), U8("\u00c6\u0304"), U8("\u00e6\u0304"), U8(""), U8(""), U8("\u0047\u030c"), U8("\u0067\u030c"), U8("\u004b\u030c"), U8("\u006b\u030c"), U8("\u004f\u0328"), U8("\u006f\u0328"), U8("\u01ea\u0304"), U8("\u01eb\u0304"), U8("\u01b7\u030c"), U8("\u0292\u030c"), U8("\u006a\u030c"), U8(""), U8(""), U8(""), U8("\u0047\u0301"), U8("\u0067\u0301"), U8(""), U8(""), U8("\u004e\u0300"), U8("\u006e\u0300"), U8("\u00c5\u0301"), U8("\u00e5\u0301"), U8("\u00c6\u0301"), U8("\u00e6\u0301"), U8("\u00d8\u0301"), U8("\u00f8\u0301") };

const char* lookupEquiv_0x0200_to_0x021b_Table[] = { U8("\u0041\u030f"), U8("\u0061\u030f"), U8("\u0041\u0311"), U8("\u0061\u0311"), U8("\u0045\u030f"), U8("\u0065\u030f"), U8("\u0045\u0311"), U8("\u0065\u0311"), U8("\u0049\u030f"), U8("\u0069\u030f"), U8("\u0049\u0311"), U8("\u0069\u0311"), U8("\u004f\u030f"), U8("\u006f\u030f"), U8("\u004f\u0311"), U8("\u006f\u0311"), U8("\u0052\u030f"), U8("\u0072\u030f"), U8("\u0052\u0311"), U8("\u0072\u0311"), U8("\u0055\u030f"), U8("\u0075\u030f"), U8("\u0055\u0311"), U8("\u0075\u0311"), U8("\u0053\u0326"), U8("\u0073\u0326"), U8("\u0054\u0326"), U8("\u0074\u0326") };

const char* lookupEquiv_0x0226_to_0x0233_Table[] = { U8("\u0041\u0307"), U8("\u0061\u0307"), U8("\u0045\u0327"), U8("\u0065\u0327"), U8("\u00d6\u0304"), U8("\u00f6\u0304"), U8("\u00d5\u0304"), U8("\u00f5\u0304"), U8("\u004f\u0307"), U8("\u006f\u0307"), U8("\u022e\u0304"), U8("\u022f\u0304"), U8("\u0059\u0304"), U8("\u0079\u0304") };

const char* lookupEquiv_0x0385_to_0x0390_Table[] = { U8("\u00a8\u0301"), U8("\u0391\u0301"), U8("\u00b7"), U8("\u0395\u0301"), U8("\u0397\u0301"), U8("\u0399\u0301"), U8(""), U8("\u039f\u0301"), U8(""), U8("\u03a5\u0301"), U8("\u03a9\u0301"), U8("\u03ca\u0301") };

const char* lookupEquiv_0x03aa_to_0x03b0_Table[] = { U8("\u0399\u0308"), U8("\u03a5\u0308"), U8("\u03b1\u0301"), U8("\u03b5\u0301"), U8("\u03b7\u0301"), U8("\u03b9\u0301"), U8("\u03cb\u0301") };

const char* lookupEquiv_0x03ca_to_0x03ce_Table[] = { U8("\u03b9\u0308"), U8("\u03c5\u0308"), U8("\u03bf\u0301"), U8("\u03c5\u0301"), U8("\u03c9\u0301") };

const char* lookupEquiv_0x04d0_to_0x04f9_Table[] = { U8("\u0410\u0306"), U8("\u0430\u0306"), U8("\u0410\u0308"), U8("\u0430\u0308"), U8(""), U8(""), U8("\u0415\u0306"), U8("\u0435\u0306"), U8(""), U8(""), U8("\u04d8\u0308"), U8("\u04d9\u0308"), U8("\u0416\u0308"), U8("\u0436\u0308"), U8("\u0417\u0308"), U8("\u0437\u0308"), U8(""), U8(""), U8("\u0418\u0304"), U8("\u0438\u0304"), U8("\u0418\u0308"), U8("\u0438\u0308"), U8("\u041e\u0308"), U8("\u043e\u0308"), U8(""), U8(""), U8("\u04e8\u0308"), U8("\u04e9\u0308"), U8("\u042d\u0308"), U8("\u044d\u0308"), U8("\u0423\u0304"), U8("\u0443\u0304"), U8("\u0423\u0308"), U8("\u0443\u0308"), U8("\u0423\u030b"), U8("\u0443\u030b"), U8("\u0427\u0308"), U8("\u0447\u0308"), U8(""), U8(""), U8("\u042b\u0308"), U8("\u044b\u0308") };

const char* lookupEquiv_0x0958_to_0x095f_Table[] = { U8("\u0915\u093c"), U8("\u0916\u093c"), U8("\u0917\u093c"), U8("\u091c\u093c"), U8("\u0921\u093c"), U8("\u0922\u093c"), U8("\u092b\u093c"), U8("\u092f\u093c") };

const char* lookupEquiv_0x1e00_to_0x1eff_Table[] = { U8("\u0041\u0325"), U8("\u0061\u0325"), U8("\u0042\u0307"), U8("\u0062\u0307"), U8("\u0042\u0323"), U8("\u0062\u0323"), U8("\u0042\u0331"), U8("\u0062\u0331"), U8("\u00c7\u0301"), U8("\u00e7\u0301"), U8("\u0044\u0307"), U8("\u0064\u0307"), U8("\u0044\u0323"), U8("\u0064\u0323"), U8("\u0044\u0331"), U8("\u0064\u0331"), U8("\u0044\u0327"), U8("\u0064\u0327"), U8("\u0044\u032d"), U8("\u0064\u032d"), U8("\u0112\u0300"), U8("\u0113\u0300"), U8("\u0112\u0301"), U8("\u0113\u0301"), U8("\u0045\u032d"), U8("\u0065\u032d"), U8("\u0045\u0330"), U8("\u0065\u0330"), U8("\u0228\u0306"), U8("\u0229\u0306"), U8("\u0046\u0307"), U8("\u0066\u0307"), U8("\u0047\u0304"), U8("\u0067\u0304"), U8("\u0048\u0307"), U8("\u0068\u0307"), U8("\u0048\u0323"), U8("\u0068\u0323"), U8("\u0048\u0308"), U8("\u0068\u0308"), U8("\u0048\u0327"), U8("\u0068\u0327"), U8("\u0048\u032e"), U8("\u0068\u032e"), U8("\u0049\u0330"), U8("\u0069\u0330"), U8("\u00cf\u0301"), U8("\u00ef\u0301"), U8("\u004b\u0301"), U8("\u006b\u0301"), U8("\u004b\u0323"), U8("\u006b\u0323"), U8("\u004b\u0331"), U8("\u006b\u0331"), U8("\u004c\u0323"), U8("\u006c\u0323"), U8("\u1e36\u0304"), U8("\u1e37\u0304"), U8("\u004c\u0331"), U8("\u006c\u0331"), U8("\u004c\u032d"), U8("\u006c\u032d"), U8("\u004d\u0301"), U8("\u006d\u0301"), U8("\u004d\u0307"), U8("\u006d\u0307"), U8("\u004d\u0323"), U8("\u006d\u0323"), U8("\u004e\u0307"), U8("\u006e\u0307"), U8("\u004e\u0323"), U8("\u006e\u0323"), U8("\u004e\u0331"), U8("\u006e\u0331"), U8("\u004e\u032d"), U8("\u006e\u032d"), U8("\u00d5\u0301"), U8("\u00f5\u0301"), U8("\u00d5\u0308"), U8("\u00f5\u0308"), U8("\u014c\u0300"), U8("\u014d\u0300"), U8("\u014c\u0301"), U8("\u014d\u0301"), U8("\u0050\u0301"), U8("\u0070\u0301"), U8("\u0050\u0307"), U8("\u0070\u0307"), U8("\u0052\u0307"), U8("\u0072\u0307"), U8("\u0052\u0323"), U8("\u0072\u0323"), U8("\u1e5a\u0304"), U8("\u1e5b\u0304"), U8("\u0052\u0331"), U8("\u0072\u0331"), U8("\u0053\u0307"), U8("\u0073\u0307"), U8("\u0053\u0323"), U8("\u0073\u0323"), U8("\u015a\u0307"), U8("\u015b\u0307"), U8("\u0160\u0307"), U8("\u0161\u0307"), U8("\u1e62\u0307"), U8("\u1e63\u0307"), U8("\u0054\u0307"), U8("\u0074\u0307"), U8("\u0054\u0323"), U8("\u0074\u0323"), U8("\u0054\u0331"), U8("\u0074\u0331"), U8("\u0054\u032d"), U8("\u0074\u032d"), U8("\u0055\u0324"), U8("\u0075\u0324"), U8("\u0055\u0330"), U8("\u0075\u0330"), U8("\u0055\u032d"), U8("\u0075\u032d"), U8("\u0168\u0301"), U8("\u0169\u0301"), U8("\u016a\u0308"), U8("\u016b\u0308"), U8("\u0056\u0303"), U8("\u0076\u0303"), U8("\u0056\u0323"), U8("\u0076\u0323"), U8("\u0057\u0300"), U8("\u0077\u0300"), U8("\u0057\u0301"), U8("\u0077\u0301"), U8("\u0057\u0308"), U8("\u0077\u0308"), U8("\u0057\u0307"), U8("\u0077\u0307"), U8("\u0057\u0323"), U8("\u0077\u0323"), U8("\u0058\u0307"), U8("\u0078\u0307"), U8("\u0058\u0308"), U8("\u0078\u0308"), U8("\u0059\u0307"), U8("\u0079\u0307"), U8("\u005a\u0302"), U8("\u007a\u0302"), U8("\u005a\u0323"), U8("\u007a\u0323"), U8("\u005a\u0331"), U8("\u007a\u0331"), U8("\u0068\u0331"), U8("\u0074\u0308"), U8("\u0077\u030a"), U8("\u0079\u030a"), U8(""), U8("\u017f\u0307"), U8(""), U8(""), U8(""), U8(""), U8("\u0041\u0323"), U8("\u0061\u0323"), U8("\u0041\u0309"), U8("\u0061\u0309"), U8("\u00c2\u0301"), U8("\u00e2\u0301"), U8("\u00c2\u0300"), U8("\u00e2\u0300"), U8("\u00c2\u0309"), U8("\u00e2\u0309"), U8("\u00c2\u0303"), U8("\u00e2\u0303"), U8("\u1ea0\u0302"), U8("\u1ea1\u0302"), U8("\u0102\u0301"), U8("\u0103\u0301"), U8("\u0102\u0300"), U8("\u0103\u0300"), U8("\u0102\u0309"), U8("\u0103\u0309"), U8("\u0102\u0303"), U8("\u0103\u0303"), U8("\u1ea0\u0306"), U8("\u1ea1\u0306"), U8("\u0045\u0323"), U8("\u0065\u0323"), U8("\u0045\u0309"), U8("\u0065\u0309"), U8("\u0045\u0303"), U8("\u0065\u0303"), U8("\u00ca\u0301"), U8("\u00ea\u0301"), U8("\u00ca\u0300"), U8("\u00ea\u0300"), U8("\u00ca\u0309"), U8("\u00ea\u0309"), U8("\u00ca\u0303"), U8("\u00ea\u0303"), U8("\u1eb8\u0302"), U8("\u1eb9\u0302"), U8("\u0049\u0309"), U8("\u0069\u0309"), U8("\u0049\u0323"), U8("\u0069\u0323"), U8("\u004f\u0323"), U8("\u006f\u0323"), U8("\u004f\u0309"), U8("\u006f\u0309"), U8("\u00d4\u0301"), U8("\u00f4\u0301"), U8("\u00d4\u0300"), U8("\u00f4\u0300"), U8("\u00d4\u0309"), U8("\u00f4\u0309"), U8("\u00d4\u0303"), U8("\u00f4\u0303"), U8("\u1ecc\u0302"), U8("\u1ecd\u0302"), U8("\u01a0\u0301"), U8("\u01a1\u0301"), U8("\u01a0\u0300"), U8("\u01a1\u0300"), U8("\u01a0\u0309"), U8("\u01a1\u0309"), U8("\u01a0\u0303"), U8("\u01a1\u0303"), U8("\u01a0\u0323"), U8("\u01a1\u0323"), U8("\u0055\u0323"), U8("\u0075\u0323"), U8("\u0055\u0309"), U8("\u0075\u0309"), U8("\u01af\u0301"), U8("\u01b0\u0301"), U8("\u01af\u0300"), U8("\u01b0\u0300"), U8("\u01af\u0309"), U8("\u01b0\u0309"), U8("\u01af\u0303"), U8("\u01b0\u0303"), U8("\u01af\u0323"), U8("\u01b0\u0323"), U8("\u0059\u0300"), U8("\u0079\u0300"), U8("\u0059\u0323"), U8("\u0079\u0323"), U8("\u0059\u0309"), U8("\u0079\u0309"), U8("\u0059\u0303"), U8("\u0079\u0303"), U8(""), U8(""), U8(""), U8(""), U8(""), U8("") };

const char* lookupEquiv_0x1f00_to_0x1fff_Table[] = { U8("\u03b1\u0313"), U8("\u03b1\u0314"), U8("\u1f00\u0300"), U8("\u1f01\u0300"), U8("\u1f00\u0301"), U8("\u1f01\u0301"), U8("\u1f00\u0342"), U8("\u1f01\u0342"), U8("\u0391\u0313"), U8("\u0391\u0314"), U8("\u1f08\u0300"), U8("\u1f09\u0300"), U8("\u1f08\u0301"), U8("\u1f09\u0301"), U8("\u1f08\u0342"), U8("\u1f09\u0342"), U8("\u03b5\u0313"), U8("\u03b5\u0314"), U8("\u1f10\u0300"), U8("\u1f11\u0300"), U8("\u1f10\u0301"), U8("\u1f11\u0301"), U8(""), U8(""), U8("\u0395\u0313"), U8("\u0395\u0314"), U8("\u1f18\u0300"), U8("\u1f19\u0300"), U8("\u1f18\u0301"), U8("\u1f19\u0301"), U8(""), U8(""), U8("\u03b7\u0313"), U8("\u03b7\u0314"), U8("\u1f20\u0300"), U8("\u1f21\u0300"), U8("\u1f20\u0301"), U8("\u1f21\u0301"), U8("\u1f20\u0342"), U8("\u1f21\u0342"), U8("\u0397\u0313"), U8("\u0397\u0314"), U8("\u1f28\u0300"), U8("\u1f29\u0300"), U8("\u1f28\u0301"), U8("\u1f29\u0301"), U8("\u1f28\u0342"), U8("\u1f29\u0342"), U8("\u03b9\u0313"), U8("\u03b9\u0314"), U8("\u1f30\u0300"), U8("\u1f31\u0300"), U8("\u1f30\u0301"), U8("\u1f31\u0301"), U8("\u1f30\u0342"), U8("\u1f31\u0342"), U8("\u0399\u0313"), U8("\u0399\u0314"), U8("\u1f38\u0300"), U8("\u1f39\u0300"), U8("\u1f38\u0301"), U8("\u1f39\u0301"), U8("\u1f38\u0342"), U8("\u1f39\u0342"), U8("\u03bf\u0313"), U8("\u03bf\u0314"), U8("\u1f40\u0300"), U8("\u1f41\u0300"), U8("\u1f40\u0301"), U8("\u1f41\u0301"), U8(""), U8(""), U8("\u039f\u0313"), U8("\u039f\u0314"), U8("\u1f48\u0300"), U8("\u1f49\u0300"), U8("\u1f48\u0301"), U8("\u1f49\u0301"), U8(""), U8(""), U8("\u03c5\u0313"), U8("\u03c5\u0314"), U8("\u1f50\u0300"), U8("\u1f51\u0300"), U8("\u1f50\u0301"), U8("\u1f51\u0301"), U8("\u1f50\u0342"), U8("\u1f51\u0342"), U8(""), U8("\u03a5\u0314"), U8(""), U8("\u1f59\u0300"), U8(""), U8("\u1f59\u0301"), U8(""), U8("\u1f59\u0342"), U8("\u03c9\u0313"), U8("\u03c9\u0314"), U8("\u1f60\u0300"), U8("\u1f61\u0300"), U8("\u1f60\u0301"), U8("\u1f61\u0301"), U8("\u1f60\u0342"), U8("\u1f61\u0342"), U8("\u03a9\u0313"), U8("\u03a9\u0314"), U8("\u1f68\u0300"), U8("\u1f69\u0300"), U8("\u1f68\u0301"), U8("\u1f69\u0301"), U8("\u1f68\u0342"), U8("\u1f69\u0342"), U8("\u03b1\u0300"), U8("\u03ac"), U8("\u03b5\u0300"), U8("\u03ad"), U8("\u03b7\u0300"), U8("\u03ae"), U8("\u03b9\u0300"), U8("\u03af"), U8("\u03bf\u0300"), U8("\u03cc"), U8("\u03c5\u0300"), U8("\u03cd"), U8("\u03c9\u0300"), U8("\u03ce"), U8(""), U8(""), U8("\u1f00\u0345"), U8("\u1f01\u0345"), U8("\u1f02\u0345"), U8("\u1f03\u0345"), U8("\u1f04\u0345"), U8("\u1f05\u0345"), U8("\u1f06\u0345"), U8("\u1f07\u0345"), U8("\u1f08\u0345"), U8("\u1f09\u0345"), U8("\u1f0a\u0345"), U8("\u1f0b\u0345"), U8("\u1f0c\u0345"), U8("\u1f0d\u0345"), U8("\u1f0e\u0345"), U8("\u1f0f\u0345"), U8("\u1f20\u0345"), U8("\u1f21\u0345"), U8("\u1f22\u0345"), U8("\u1f23\u0345"), U8("\u1f24\u0345"), U8("\u1f25\u0345"), U8("\u1f26\u0345"), U8("\u1f27\u0345"), U8("\u1f28\u0345"), U8("\u1f29\u0345"), U8("\u1f2a\u0345"), U8("\u1f2b\u0345"), U8("\u1f2c\u0345"), U8("\u1f2d\u0345"), U8("\u1f2e\u0345"), U8("\u1f2f\u0345"), U8("\u1f60\u0345"), U8("\u1f61\u0345"), U8("\u1f62\u0345"), U8("\u1f63\u0345"), U8("\u1f64\u0345"), U8("\u1f65\u0345"), U8("\u1f66\u0345"), U8("\u1f67\u0345"), U8("\u1f68\u0345"), U8("\u1f69\u0345"), U8("\u1f6a\u0345"), U8("\u1f6b\u0345"), U8("\u1f6c\u0345"), U8("\u1f6d\u0345"), U8("\u1f6e\u0345"), U8("\u1f6f\u0345"), U8("\u03b1\u0306"), U8("\u03b1\u0304"), U8("\u1f70\u0345"), U8("\u03b1\u0345"), U8("\u03ac\u0345"), U8(""), U8("\u03b1\u0342"), U8("\u1fb6\u0345"), U8("\u0391\u0306"), U8("\u0391\u0304"), U8("\u0391\u0300"), U8("\u0386"), U8("\u0391\u0345"), U8(""), U8("\u03b9"), U8(""), U8(""), U8("\u00a8\u0342"), U8("\u1f74\u0345"), U8("\u03b7\u0345"), U8("\u03ae\u0345"), U8(""), U8("\u03b7\u0342"), U8("\u1fc6\u0345"), U8("\u0395\u0300"), U8("\u0388"), U8("\u0397\u0300"), U8("\u0389"), U8("\u0397\u0345"), U8("\u1fbf\u0300"), U8("\u1fbf\u0301"), U8("\u1fbf\u0342"), U8("\u03b9\u0306"), U8("\u03b9\u0304"), U8("\u03ca\u0300"), U8("\u0390"), U8(""), U8(""), U8("\u03b9\u0342"), U8("\u03ca\u0342"), U8("\u0399\u0306"), U8("\u0399\u0304"), U8("\u0399\u0300"), U8("\u038a"), U8(""), U8("\u1ffe\u0300"), U8("\u1ffe\u0301"), U8("\u1ffe\u0342"), U8("\u03c5\u0306"), U8("\u03c5\u0304"), U8("\u03cb\u0300"), U8("\u03b0"), U8("\u03c1\u0313"), U8("\u03c1\u0314"), U8("\u03c5\u0342"), U8("\u03cb\u0342"), U8("\u03a5\u0306"), U8("\u03a5\u0304"), U8("\u03a5\u0300"), U8("\u038e"), U8("\u03a1\u0314"), U8("\u00a8\u0300"), U8("\u0385"), U8("\u0060"), U8(""), U8(""), U8("\u1f7c\u0345"), U8("\u03c9\u0345"), U8("\u03ce\u0345"), U8(""), U8("\u03c9\u0342"), U8("\u1ff6\u0345"), U8("\u039f\u0300"), U8("\u038c"), U8("\u03a9\u0300"), U8("\u038f"), U8("\u03a9\u0345"), U8("\u00b4"), U8(""), U8("") };

const char* lookupEquiv_0xf900_to_0xfad9_Table[] = { U8("\u8c48"), U8("\u66f4"), U8("\u8eca"), U8("\u8cc8"), U8("\u6ed1"), U8("\u4e32"), U8("\u53e5"), U8("\u9f9c"), U8("\u9f9c"), U8("\u5951"), U8("\u91d1"), U8("\u5587"), U8("\u5948"), U8("\u61f6"), U8("\u7669"), U8("\u7f85"), U8("\u863f"), U8("\u87ba"), U8("\u88f8"), U8("\u908f"), U8("\u6a02"), U8("\u6d1b"), U8("\u70d9"), U8("\u73de"), U8("\u843d"), U8("\u916a"), U8("\u99f1"), U8("\u4e82"), U8("\u5375"), U8("\u6b04"), U8("\u721b"), U8("\u862d"), U8("\u9e1e"), U8("\u5d50"), U8("\u6feb"), U8("\u85cd"), U8("\u8964"), U8("\u62c9"), U8("\u81d8"), U8("\u881f"), U8("\u5eca"), U8("\u6717"), U8("\u6d6a"), U8("\u72fc"), U8("\u90ce"), U8("\u4f86"), U8("\u51b7"), U8("\u52de"), U8("\u64c4"), U8("\u6ad3"), U8("\u7210"), U8("\u76e7"), U8("\u8001"), U8("\u8606"), U8("\u865c"), U8("\u8def"), U8("\u9732"), U8("\u9b6f"), U8("\u9dfa"), U8("\u788c"), U8("\u797f"), U8("\u7da0"), U8("\u83c9"), U8("\u9304"), U8("\u9e7f"), U8("\u8ad6"), U8("\u58df"), U8("\u5f04"), U8("\u7c60"), U8("\u807e"), U8("\u7262"), U8("\u78ca"), U8("\u8cc2"), U8("\u96f7"), U8("\u58d8"), U8("\u5c62"), U8("\u6a13"), U8("\u6dda"), U8("\u6f0f"), U8("\u7d2f"), U8("\u7e37"), U8("\u964b"), U8("\u52d2"), U8("\u808b"), U8("\u51dc"), U8("\u51cc"), U8("\u7a1c"), U8("\u7dbe"), U8("\u83f1"), U8("\u9675"), U8("\u8b80"), U8("\u62cf"), U8("\u6a02"), U8("\u8afe"), U8("\u4e39"), U8("\u5be7"), U8("\u6012"), U8("\u7387"), U8("\u7570"), U8("\u5317"), U8("\u78fb"), U8("\u4fbf"), U8("\u5fa9"), U8("\u4e0d"), U8("\u6ccc"), U8("\u6578"), U8("\u7d22"), U8("\u53c3"), U8("\u585e"), U8("\u7701"), U8("\u8449"), U8("\u8aaa"), U8("\u6bba"), U8("\u8fb0"), U8("\u6c88"), U8("\u62fe"), U8("\u82e5"), U8("\u63a0"), U8("\u7565"), U8("\u4eae"), U8("\u5169"), U8("\u51c9"), U8("\u6881"), U8("\u7ce7"), U8("\u826f"), U8("\u8ad2"), U8("\u91cf"), U8("\u52f5"), U8("\u5442"), U8("\u5973"), U8("\u5eec"), U8("\u65c5"), U8("\u6ffe"), U8("\u792a"), U8("\u95ad"), U8("\u9a6a"), U8("\u9e97"), U8("\u9ece"), U8("\u529b"), U8("\u66c6"), U8("\u6b77"), U8("\u8f62"), U8("\u5e74"), U8("\u6190"), U8("\u6200"), U8("\u649a"), U8("\u6f23"), U8("\u7149"), U8("\u7489"), U8("\u79ca"), U8("\u7df4"), U8("\u806f"), U8("\u8f26"), U8("\u84ee"), U8("\u9023"), U8("\u934a"), U8("\u5217"), U8("\u52a3"), U8("\u54bd"), U8("\u70c8"), U8("\u88c2"), U8("\u8aaa"), U8("\u5ec9"), U8("\u5ff5"), U8("\u637b"), U8("\u6bae"), U8("\u7c3e"), U8("\u7375"), U8("\u4ee4"), U8("\u56f9"), U8("\u5be7"), U8("\u5dba"), U8("\u601c"), U8("\u73b2"), U8("\u7469"), U8("\u7f9a"), U8("\u8046"), U8("\u9234"), U8("\u96f6"), U8("\u9748"), U8("\u9818"), U8("\u4f8b"), U8("\u79ae"), U8("\u91b4"), U8("\u96b8"), U8("\u60e1"), U8("\u4e86"), U8("\u50da"), U8("\u5bee"), U8("\u5c3f"), U8("\u6599"), U8("\u6a02"), U8("\u71ce"), U8("\u7642"), U8("\u84fc"), U8("\u907c"), U8("\u9f8d"), U8("\u6688"), U8("\u962e"), U8("\u5289"), U8("\u677b"), U8("\u67f3"), U8("\u6d41"), U8("\u6e9c"), U8("\u7409"), U8("\u7559"), U8("\u786b"), U8("\u7d10"), U8("\u985e"), U8("\u516d"), U8("\u622e"), U8("\u9678"), U8("\u502b"), U8("\u5d19"), U8("\u6dea"), U8("\u8f2a"), U8("\u5f8b"), U8("\u6144"), U8("\u6817"), U8("\u7387"), U8("\u9686"), U8("\u5229"), U8("\u540f"), U8("\u5c65"), U8("\u6613"), U8("\u674e"), U8("\u68a8"), U8("\u6ce5"), U8("\u7406"), U8("\u75e2"), U8("\u7f79"), U8("\u88cf"), U8("\u88e1"), U8("\u91cc"), U8("\u96e2"), U8("\u533f"), U8("\u6eba"), U8("\u541d"), U8("\u71d0"), U8("\u7498"), U8("\u85fa"), U8("\u96a3"), U8("\u9c57"), U8("\u9e9f"), U8("\u6797"), U8("\u6dcb"), U8("\u81e8"), U8("\u7acb"), U8("\u7b20"), U8("\u7c92"), U8("\u72c0"), U8("\u7099"), U8("\u8b58"), U8("\u4ec0"), U8("\u8336"), U8("\u523a"), U8("\u5207"), U8("\u5ea6"), U8("\u62d3"), U8("\u7cd6"), U8("\u5b85"), U8("\u6d1e"), U8("\u66b4"), U8("\u8f3b"), U8("\u884c"), U8("\u964d"), U8("\u898b"), U8("\u5ed3"), U8("\u5140"), U8("\u55c0"), U8(""), U8(""), U8("\u585a"), U8(""), U8("\u6674"), U8(""), U8(""), U8("\u51de"), U8("\u732a"), U8("\u76ca"), U8("\u793c"), U8("\u795e"), U8("\u7965"), U8("\u798f"), U8("\u9756"), U8("\u7cbe"), U8("\u7fbd"), U8(""), U8("\u8612"), U8(""), U8("\u8af8"), U8(""), U8(""), U8("\u9038"), U8("\u90fd"), U8(""), U8(""), U8(""), U8("\u98ef"), U8("\u98fc"), U8("\u9928"), U8("\u9db4"), U8("\u90de"), U8("\u96b7"), U8("\u4fae"), U8("\u50e7"), U8("\u514d"), U8("\u52c9"), U8("\u52e4"), U8("\u5351"), U8("\u559d"), U8("\u5606"), U8("\u5668"), U8("\u5840"), U8("\u58a8"), U8("\u5c64"), U8("\u5c6e"), U8("\u6094"), U8("\u6168"), U8("\u618e"), U8("\u61f2"), U8("\u654f"), U8("\u65e2"), U8("\u6691"), U8("\u6885"), U8("\u6d77"), U8("\u6e1a"), U8("\u6f22"), U8("\u716e"), U8("\u722b"), U8("\u7422"), U8("\u7891"), U8("\u793e"), U8("\u7949"), U8("\u7948"), U8("\u7950"), U8("\u7956"), U8("\u795d"), U8("\u798d"), U8("\u798e"), U8("\u7a40"), U8("\u7a81"), U8("\u7bc0"), U8("\u7df4"), U8("\u7e09"), U8("\u7e41"), U8("\u7f72"), U8("\u8005"), U8("\u81ed"), U8("\u8279"), U8("\u8279"), U8("\u8457"), U8("\u8910"), U8("\u8996"), U8("\u8b01"), U8("\u8b39"), U8("\u8cd3"), U8("\u8d08"), U8("\u8fb6"), U8("\u9038"), U8("\u96e3"), U8("\u97ff"), U8("\u983b"), U8("\u6075"), U8("\U000242ee"), U8("\u8218"), U8(""), U8(""), U8("\u4e26"), U8("\u51b5"), U8("\u5168"), U8("\u4f80"), U8("\u5145"), U8("\u5180"), U8("\u52c7"), U8("\u52fa"), U8("\u559d"), U8("\u5555"), U8("\u5599"), U8("\u55e2"), U8("\u585a"), U8("\u58b3"), U8("\u5944"), U8("\u5954"), U8("\u5a62"), U8("\u5b28"), U8("\u5ed2"), U8("\u5ed9"), U8("\u5f69"), U8("\u5fad"), U8("\u60d8"), U8("\u614e"), U8("\u6108"), U8("\u618e"), U8("\u6160"), U8("\u61f2"), U8("\u6234"), U8("\u63c4"), U8("\u641c"), U8("\u6452"), U8("\u6556"), U8("\u6674"), U8("\u6717"), U8("\u671b"), U8("\u6756"), U8("\u6b79"), U8("\u6bba"), U8("\u6d41"), U8("\u6edb"), U8("\u6ecb"), U8("\u6f22"), U8("\u701e"), U8("\u716e"), U8("\u77a7"), U8("\u7235"), U8("\u72af"), U8("\u732a"), U8("\u7471"), U8("\u7506"), U8("\u753b"), U8("\u761d"), U8("\u761f"), U8("\u76ca"), U8("\u76db"), U8("\u76f4"), U8("\u774a"), U8("\u7740"), U8("\u78cc"), U8("\u7ab1"), U8("\u7bc0"), U8("\u7c7b"), U8("\u7d5b"), U8("\u7df4"), U8("\u7f3e"), U8("\u8005"), U8("\u8352"), U8("\u83ef"), U8("\u8779"), U8("\u8941"), U8("\u8986"), U8("\u8996"), U8("\u8abf"), U8("\u8af8"), U8("\u8acb"), U8("\u8b01"), U8("\u8afe"), U8("\u8aed"), U8("\u8b39"), U8("\u8b8a"), U8("\u8d08"), U8("\u8f38"), U8("\u9072"), U8("\u9199"), U8("\u9276"), U8("\u967c"), U8("\u96e3"), U8("\u9756"), U8("\u97db"), U8("\u97ff"), U8("\u980b"), U8("\u983b"), U8("\u9b12"), U8("\u9f9c"), U8("\U0002284a"), U8("\U00022844"), U8("\U000233d5"), U8("\u3b9d"), U8("\u4018"), U8("\u4039"), U8("\U00025249"), U8("\U00025cd0"), U8("\U00027ed3"), U8("\u9f43"), U8("\u9f8e") };

const char* lookupEquiv_0xfb2a_to_0xfb4e_Table[] = { U8("\u05e9\u05c1"), U8("\u05e9\u05c2"), U8("\ufb49\u05c1"), U8("\ufb49\u05c2"), U8("\u05d0\u05b7"), U8("\u05d0\u05b8"), U8("\u05d0\u05bc"), U8("\u05d1\u05bc"), U8("\u05d2\u05bc"), U8("\u05d3\u05bc"), U8("\u05d4\u05bc"), U8("\u05d5\u05bc"), U8("\u05d6\u05bc"), U8(""), U8("\u05d8\u05bc"), U8("\u05d9\u05bc"), U8("\u05da\u05bc"), U8("\u05db\u05bc"), U8("\u05dc\u05bc"), U8(""), U8("\u05de\u05bc"), U8(""), U8("\u05e0\u05bc"), U8("\u05e1\u05bc"), U8(""), U8("\u05e3\u05bc"), U8("\u05e4\u05bc"), U8(""), U8("\u05e6\u05bc"), U8("\u05e7\u05bc"), U8("\u05e8\u05bc"), U8("\u05e9\u05bc"), U8("\u05ea\u05bc"), U8("\u05d5\u05b9"), U8("\u05d1\u05bf"), U8("\u05db\u05bf"), U8("\u05e4\u05bf") };

const char* lookupEquiv_0x16121_to_0x16128_Table[] = { U8("\U0001611e\U0001611e"), U8("\U0001611e\U00016129"), U8("\U0001611e\U0001611f"), U8("\U00016129\U0001611f"), U8("\U0001611e\U00016120"), U8("\U00016121\U0001611f"), U8("\U00016122\U0001611f"), U8("\U00016121\U00016120") };

const char* lookupEquiv_0x1d15e_to_0x1d164_Table[] = { U8("\U0001d157\U0001d165"), U8("\U0001d158\U0001d165"), U8("\U0001d15f\U0001d16e"), U8("\U0001d15f\U0001d16f"), U8("\U0001d15f\U0001d170"), U8("\U0001d15f\U0001d171"), U8("\U0001d15f\U0001d172") };

const char* lookupEquiv_0x1d1bb_to_0x1d1c0_Table[] = { U8("\U0001d1b9\U0001d165"), U8("\U0001d1ba\U0001d165"), U8("\U0001d1bb\U0001d16e"), U8("\U0001d1bc\U0001d16e"), U8("\U0001d1bb\U0001d16f"), U8("\U0001d1bc\U0001d16f") };

const char* lookupEquiv_0x2f800_to_0x2fa1d_Table[] = { U8("\u4e3d"), U8("\u4e38"), U8("\u4e41"), U8("\U00020122"), U8("\u4f60"), U8("\u4fae"), U8("\u4fbb"), U8("\u5002"), U8("\u507a"), U8("\u5099"), U8("\u50e7"), U8("\u50cf"), U8("\u349e"), U8("\U0002063a"), U8("\u514d"), U8("\u5154"), U8("\u5164"), U8("\u5177"), U8("\U0002051c"), U8("\u34b9"), U8("\u5167"), U8("\u518d"), U8("\U0002054b"), U8("\u5197"), U8("\u51a4"), U8("\u4ecc"), U8("\u51ac"), U8("\u51b5"), U8("\U000291df"), U8("\u51f5"), U8("\u5203"), U8("\u34df"), U8("\u523b"), U8("\u5246"), U8("\u5272"), U8("\u5277"), U8("\u3515"), U8("\u52c7"), U8("\u52c9"), U8("\u52e4"), U8("\u52fa"), U8("\u5305"), U8("\u5306"), U8("\u5317"), U8("\u5349"), U8("\u5351"), U8("\u535a"), U8("\u5373"), U8("\u537d"), U8("\u537f"), U8("\u537f"), U8("\u537f"), U8("\U00020a2c"), U8("\u7070"), U8("\u53ca"), U8("\u53df"), U8("\U00020b63"), U8("\u53eb"), U8("\u53f1"), U8("\u5406"), U8("\u549e"), U8("\u5438"), U8("\u5448"), U8("\u5468"), U8("\u54a2"), U8("\u54f6"), U8("\u5510"), U8("\u5553"), U8("\u5563"), U8("\u5584"), U8("\u5584"), U8("\u5599"), U8("\u55ab"), U8("\u55b3"), U8("\u55c2"), U8("\u5716"), U8("\u5606"), U8("\u5717"), U8("\u5651"), U8("\u5674"), U8("\u5207"), U8("\u58ee"), U8("\u57ce"), U8("\u57f4"), U8("\u580d"), U8("\u578b"), U8("\u5832"), U8("\u5831"), U8("\u58ac"), U8("\U000214e4"), U8("\u58f2"), U8("\u58f7"), U8("\u5906"), U8("\u591a"), U8("\u5922"), U8("\u5962"), U8("\U000216a8"), U8("\U000216ea"), U8("\u59ec"), U8("\u5a1b"), U8("\u5a27"), U8("\u59d8"), U8("\u5a66"), U8("\u36ee"), U8("\u36fc"), U8("\u5b08"), U8("\u5b3e"), U8("\u5b3e"), U8("\U000219c8"), U8("\u5bc3"), U8("\u5bd8"), U8("\u5be7"), U8("\u5bf3"), U8("\U00021b18"), U8("\u5bff"), U8("\u5c06"), U8("\u5f53"), U8("\u5c22"), U8("\u3781"), U8("\u5c60"), U8("\u5c6e"), U8("\u5cc0"), U8("\u5c8d"), U8("\U00021de4"), U8("\u5d43"), U8("\U00021de6"), U8("\u5d6e"), U8("\u5d6b"), U8("\u5d7c"), U8("\u5de1"), U8("\u5de2"), U8("\u382f"), U8("\u5dfd"), U8("\u5e28"), U8("\u5e3d"), U8("\u5e69"), U8("\u3862"), U8("\U00022183"), U8("\u387c"), U8("\u5eb0"), U8("\u5eb3"), U8("\u5eb6"), U8("\u5eca"), U8("\U0002a392"), U8("\u5efe"), U8("\U00022331"), U8("\U00022331"), U8("\u8201"), U8("\u5f22"), U8("\u5f22"), U8("\u38c7"), U8("\U000232b8"), U8("\U000261da"), U8("\u5f62"), U8("\u5f6b"), U8("\u38e3"), U8("\u5f9a"), U8("\u5fcd"), U8("\u5fd7"), U8("\u5ff9"), U8("\u6081"), U8("\u393a"), U8("\u391c"), U8("\u6094"), U8("\U000226d4"), U8("\u60c7"), U8("\u6148"), U8("\u614c"), U8("\u614e"), U8("\u614c"), U8("\u617a"), U8("\u618e"), U8("\u61b2"), U8("\u61a4"), U8("\u61af"), U8("\u61de"), U8("\u61f2"), U8("\u61f6"), U8("\u6210"), U8("\u621b"), U8("\u625d"), U8("\u62b1"), U8("\u62d4"), U8("\u6350"), U8("\U00022b0c"), U8("\u633d"), U8("\u62fc"), U8("\u6368"), U8("\u6383"), U8("\u63e4"), U8("\U00022bf1"), U8("\u6422"), U8("\u63c5"), U8("\u63a9"), U8("\u3a2e"), U8("\u6469"), U8("\u647e"), U8("\u649d"), U8("\u6477"), U8("\u3a6c"), U8("\u654f"), U8("\u656c"), U8("\U0002300a"), U8("\u65e3"), U8("\u66f8"), U8("\u6649"), U8("\u3b19"), U8("\u6691"), U8("\u3b08"), U8("\u3ae4"), U8("\u5192"), U8("\u5195"), U8("\u6700"), U8("\u669c"), U8("\u80ad"), U8("\u43d9"), U8("\u6717"), U8("\u671b"), U8("\u6721"), U8("\u675e"), U8("\u6753"), U8("\U000233c3"), U8("\u3b49"), U8("\u67fa"), U8("\u6785"), U8("\u6852"), U8("\u6885"), U8("\U0002346d"), U8("\u688e"), U8("\u681f"), U8("\u6914"), U8("\u3b9d"), U8("\u6942"), U8("\u69a3"), U8("\u69ea"), U8("\u6aa8"), U8("\U000236a3"), U8("\u6adb"), U8("\u3c18"), U8("\u6b21"), U8("\U000238a7"), U8("\u6b54"), U8("\u3c4e"), U8("\u6b72"), U8("\u6b9f"), U8("\u6bba"), U8("\u6bbb"), U8("\U00023a8d"), U8("\U00021d0b"), U8("\U00023afa"), U8("\u6c4e"), U8("\U00023cbc"), U8("\u6cbf"), U8("\u6ccd"), U8("\u6c67"), U8("\u6d16"), U8("\u6d3e"), U8("\u6d77"), U8("\u6d41"), U8("\u6d69"), U8("\u6d78"), U8("\u6d85"), U8("\U00023d1e"), U8("\u6d34"), U8("\u6e2f"), U8("\u6e6e"), U8("\u3d33"), U8("\u6ecb"), U8("\u6ec7"), U8("\U00023ed1"), U8("\u6df9"), U8("\u6f6e"), U8("\U00023f5e"), U8("\U00023f8e"), U8("\u6fc6"), U8("\u7039"), U8("\u701e"), U8("\u701b"), U8("\u3d96"), U8("\u704a"), U8("\u707d"), U8("\u7077"), U8("\u70ad"), U8("\U00020525"), U8("\u7145"), U8("\U00024263"), U8("\u719c"), U8("\U000243ab"), U8("\u7228"), U8("\u7235"), U8("\u7250"), U8("\U00024608"), U8("\u7280"), U8("\u7295"), U8("\U00024735"), U8("\U00024814"), U8("\u737a"), U8("\u738b"), U8("\u3eac"), U8("\u73a5"), U8("\u3eb8"), U8("\u3eb8"), U8("\u7447"), U8("\u745c"), U8("\u7471"), U8("\u7485"), U8("\u74ca"), U8("\u3f1b"), U8("\u7524"), U8("\U00024c36"), U8("\u753e"), U8("\U00024c92"), U8("\u7570"), U8("\U0002219f"), U8("\u7610"), U8("\U00024fa1"), U8("\U00024fb8"), U8("\U00025044"), U8("\u3ffc"), U8("\u4008"), U8("\u76f4"), U8("\U000250f3"), U8("\U000250f2"), U8("\U00025119"), U8("\U00025133"), U8("\u771e"), U8("\u771f"), U8("\u771f"), U8("\u774a"), U8("\u4039"), U8("\u778b"), U8("\u4046"), U8("\u4096"), U8("\U0002541d"), U8("\u784e"), U8("\u788c"), U8("\u78cc"), U8("\u40e3"), U8("\U00025626"), U8("\u7956"), U8("\U0002569a"), U8("\U000256c5"), U8("\u798f"), U8("\u79eb"), U8("\u412f"), U8("\u7a40"), U8("\u7a4a"), U8("\u7a4f"), U8("\U0002597c"), U8("\U00025aa7"), U8("\U00025aa7"), U8("\u7aee"), U8("\u4202"), U8("\U00025bab"), U8("\u7bc6"), U8("\u7bc9"), U8("\u4227"), U8("\U00025c80"), U8("\u7cd2"), U8("\u42a0"), U8("\u7ce8"), U8("\u7ce3"), U8("\u7d00"), U8("\U00025f86"), U8("\u7d63"), U8("\u4301"), U8("\u7dc7"), U8("\u7e02"), U8("\u7e45"), U8("\u4334"), U8("\U00026228"), U8("\U00026247"), U8("\u4359"), U8("\U000262d9"), U8("\u7f7a"), U8("\U0002633e"), U8("\u7f95"), U8("\u7ffa"), U8("\u8005"), U8("\U000264da"), U8("\U00026523"), U8("\u8060"), U8("\U000265a8"), U8("\u8070"), U8("\U0002335f"), U8("\u43d5"), U8("\u80b2"), U8("\u8103"), U8("\u440b"), U8("\u813e"), U8("\u5ab5"), U8("\U000267a7"), U8("\U000267b5"), U8("\U00023393"), U8("\U0002339c"), U8("\u8201"), U8("\u8204"), U8("\u8f9e"), U8("\u446b"), U8("\u8291"), U8("\u828b"), U8("\u829d"), U8("\u52b3"), U8("\u82b1"), U8("\u82b3"), U8("\u82bd"), U8("\u82e6"), U8("\U00026b3c"), U8("\u82e5"), U8("\u831d"), U8("\u8363"), U8("\u83ad"), U8("\u8323"), U8("\u83bd"), U8("\u83e7"), U8("\u8457"), U8("\u8353"), U8("\u83ca"), U8("\u83cc"), U8("\u83dc"), U8("\U00026c36"), U8("\U00026d6b"), U8("\U00026cd5"), U8("\u452b"), U8("\u84f1"), U8("\u84f3"), U8("\u8516"), U8("\U000273ca"), U8("\u8564"), U8("\U00026f2c"), U8("\u455d"), U8("\u4561"), U8("\U00026fb1"), U8("\U000270d2"), U8("\u456b"), U8("\u8650"), U8("\u865c"), U8("\u8667"), U8("\u8669"), U8("\u86a9"), U8("\u8688"), U8("\u870e"), U8("\u86e2"), U8("\u8779"), U8("\u8728"), U8("\u876b"), U8("\u8786"), U8("\u45d7"), U8("\u87e1"), U8("\u8801"), U8("\u45f9"), U8("\u8860"), U8("\u8863"), U8("\U00027667"), U8("\u88d7"), U8("\u88de"), U8("\u4635"), U8("\u88fa"), U8("\u34bb"), U8("\U000278ae"), U8("\U00027966"), U8("\u46be"), U8("\u46c7"), U8("\u8aa0"), U8("\u8aed"), U8("\u8b8a"), U8("\u8c55"), U8("\U00027ca8"), U8("\u8cab"), U8("\u8cc1"), U8("\u8d1b"), U8("\u8d77"), U8("\U00027f2f"), U8("\U00020804"), U8("\u8dcb"), U8("\u8dbc"), U8("\u8df0"), U8("\U000208de"), U8("\u8ed4"), U8("\u8f38"), U8("\U000285d2"), U8("\U000285ed"), U8("\u9094"), U8("\u90f1"), U8("\u9111"), U8("\U0002872e"), U8("\u911b"), U8("\u9238"), U8("\u92d7"), U8("\u92d8"), U8("\u927c"), U8("\u93f9"), U8("\u9415"), U8("\U00028bfa"), U8("\u958b"), U8("\u4995"), U8("\u95b7"), U8("\U00028d77"), U8("\u49e6"), U8("\u96c3"), U8("\u5db2"), U8("\u9723"), U8("\U00029145"), U8("\U0002921a"), U8("\u4a6e"), U8("\u4a76"), U8("\u97e0"), U8("\U0002940a"), U8("\u4ab2"), U8("\U00029496"), U8("\u980b"), U8("\u980b"), U8("\u9829"), U8("\U000295b6"), U8("\u98e2"), U8("\u4b33"), U8("\u9929"), U8("\u99a7"), U8("\u99c2"), U8("\u99fe"), U8("\u4bce"), U8("\U00029b30"), U8("\u9b12"), U8("\u9c40"), U8("\u9cfd"), U8("\u4cce"), U8("\u4ced"), U8("\u9d67"), U8("\U0002a0ce"), U8("\u4cf8"), U8("\U0002a105"), U8("\U0002a20e"), U8("\U0002a291"), U8("\u9ebb"), U8("\u4d56"), U8("\u9ef9"), U8("\u9efe"), U8("\u9f05"), U8("\u9f0f"), U8("\u9f16"), U8("\u9f3b"), U8("\U0002a600") };

SGEXTN::CoreText::String getEquivDecomp(int i){
    if(i < 0x80){return "";}
    if(i >= 0x4e00 && i <= 0x9fff){return "";}
    if(i >= 0xb80 && i <= 0xbff){
        if(i == 0xb94){return U8("\u0b92\u0bd7");}
        if(i == 0xbca){return U8("\u0bc6\u0bbe");}
        if(i == 0xbcb){return U8("\u0bc7\u0bbe");}
        if(i == 0xbcc){return U8("\u0bc6\u0bd7");}
        return "";
    }
    if(i >= 0x2200 && i <= 0x22ff){
        if(i == 0x2204){return U8("\u2203\u0338");}
        if(i == 0x2209){return U8("\u2208\u0338");}
        if(i == 0x220c){return U8("\u220b\u0338");}
        if(i == 0x2224){return U8("\u2223\u0338");}
        if(i == 0x2226){return U8("\u2225\u0338");}
        if(i == 0x2241){return U8("\u223c\u0338");}
        if(i == 0x2244){return U8("\u2243\u0338");}
        if(i == 0x2247){return U8("\u2245\u0338");}
        if(i == 0x2249){return U8("\u2248\u0338");}
        if(i == 0x2260){return U8("\u003d\u0338");}
        if(i == 0x2262){return U8("\u2261\u0338");}
        if(i == 0x226d){return U8("\u224d\u0338");}
        if(i == 0x226e){return U8("\u003c\u0338");}
        if(i == 0x226f){return U8("\u003e\u0338");}
        if(i == 0x2270){return U8("\u2264\u0338");}
        if(i == 0x2271){return U8("\u2265\u0338");}
        if(i == 0x2274){return U8("\u2272\u0338");}
        if(i == 0x2275){return U8("\u2273\u0338");}
        if(i == 0x2278){return U8("\u2276\u0338");}
        if(i == 0x2279){return U8("\u2277\u0338");}
        if(i == 0x2280){return U8("\u227a\u0338");}
        if(i == 0x2281){return U8("\u227b\u0338");}
        if(i == 0x2284){return U8("\u2282\u0338");}
        if(i == 0x2285){return U8("\u2283\u0338");}
        if(i == 0x2288){return U8("\u2286\u0338");}
        if(i == 0x2289){return U8("\u2287\u0338");}
        if(i == 0x22ac){return U8("\u22a2\u0338");}
        if(i == 0x22ad){return U8("\u22a8\u0338");}
        if(i == 0x22ae){return U8("\u22a9\u0338");}
        if(i == 0x22af){return U8("\u22ab\u0338");}
        if(i == 0x22e0){return U8("\u227c\u0338");}
        if(i == 0x22e1){return U8("\u227d\u0338");}
        if(i == 0x22e2){return U8("\u2291\u0338");}
        if(i == 0x22e3){return U8("\u2292\u0338");}
        if(i == 0x22ea){return U8("\u22b2\u0338");}
        if(i == 0x22eb){return U8("\u22b3\u0338");}
        if(i == 0x22ec){return U8("\u22b4\u0338");}
        if(i == 0x22ed){return U8("\u22b5\u0338");}
        return "";
    }
    if(i >= 0xac00 && i <= 0xd7a3){
        SGEXTN::CoreText::String thisEquivDecomp;
        const int index = i - 0xac00;
        if(index % 28 == 0){
            thisEquivDecomp += SGEXTN::CoreText::Character(0x1100 + (index / 588));
            thisEquivDecomp += SGEXTN::CoreText::Character(0x1161 + ((index % 588) / 28));
        }
        else{
            thisEquivDecomp += SGEXTN::CoreText::Character(0xac00 + 28 * (index / 28));
            thisEquivDecomp += SGEXTN::CoreText::Character(0x11a7 + (index % 28));
        }
        return thisEquivDecomp;
    }
    if(i >= 0x00c0 && i <= 0x0fff){
        if(i >= 0x00c0 && i <= 0x00ff){return lookupEquiv_0x00c0_to_0x00ff_Table[i - 0x00c0];}
        if(i >= 0x0100 && i <= 0x1fff){
            if(i >= 0x0100 && i <= 0x017e){return lookupEquiv_0x0100_to_0x017e_Table[i - 0x0100];}
            if(i == 0x01a0){return U8("\u004f\u031b");}
            if(i == 0x01a1){return U8("\u006f\u031b");}
            if(i == 0x01af){return U8("\u0055\u031b");}
            if(i == 0x01b0){return U8("\u0075\u031b");}
            if(i >= 0x01cd && i <= 0x01ff){return lookupEquiv_0x01cd_to_0x01ff_Table[i - 0x01cd];}
        }
        if(i >= 0x0200 && i <= 0x02ff){
            if(i >= 0x0200 && i <= 0x021b){return lookupEquiv_0x0200_to_0x021b_Table[i - 0x0200];}
            if(i == 0x021e){return U8("\u0048\u030c");}
            if(i == 0x021f){return U8("\u0068\u030c");}
            if(i >= 0x0226 && i <= 0x0233){return lookupEquiv_0x0226_to_0x0233_Table[i - 0x0226];}
        }
        if(i >= 0x0300 && i <= 0x03ff){
            if(i == 0x0340){return U8("\u0300");}
            if(i == 0x0341){return U8("\u0301");}
            if(i == 0x0343){return U8("\u0313");}
            if(i == 0x0344){return U8("\u0308\u0301");}
            if(i == 0x0374){return U8("\u02b9");}
            if(i == 0x037e){return U8("\u003b");}
            if(i >= 0x0385 && i <= 0x0390){return lookupEquiv_0x0385_to_0x0390_Table[i - 0x0385];}
            if(i >= 0x03aa && i <= 0x03b0){return lookupEquiv_0x03aa_to_0x03b0_Table[i - 0x03aa];}
            if(i >= 0x03ca && i <= 0x03ce){return lookupEquiv_0x03ca_to_0x03ce_Table[i - 0x03ca];}
            if(i == 0x03d3){return U8("\u03d2\u0301");}
            if(i == 0x03d4){return U8("\u03d2\u0308");}
        }
        if(i >= 0x0400 && i <= 0x04ff){
            if(i == 0x0400){return U8("\u0415\u0300");}
            if(i == 0x0401){return U8("\u0415\u0308");}
            if(i == 0x0403){return U8("\u0413\u0301");}
            if(i == 0x0407){return U8("\u0406\u0308");}
            if(i == 0x040c){return U8("\u041a\u0301");}
            if(i == 0x040d){return U8("\u0418\u0300");}
            if(i == 0x040e){return U8("\u0423\u0306");}
            if(i == 0x0419){return U8("\u0418\u0306");}
            if(i == 0x0439){return U8("\u0438\u0306");}
            if(i == 0x0450){return U8("\u0435\u0300");}
            if(i == 0x0451){return U8("\u0435\u0308");}
            if(i == 0x0453){return U8("\u0433\u0301");}
            if(i == 0x0457){return U8("\u0456\u0308");}
            if(i == 0x045c){return U8("\u043a\u0301");}
            if(i == 0x045d){return U8("\u0438\u0300");}
            if(i == 0x045e){return U8("\u0443\u0306");}
            if(i == 0x0476){return U8("\u0474\u030f");}
            if(i == 0x0477){return U8("\u0475\u030f");}
            if(i == 0x04c1){return U8("\u0416\u0306");}
            if(i == 0x04c2){return U8("\u0436\u0306");}
            if(i >= 0x04d0 && i <= 0x04f9){return lookupEquiv_0x04d0_to_0x04f9_Table[i - 0x04d0];}
        }
        if(i >= 0x0600 && i <= 0x06ff){
            if(i == 0x0622){return U8("\u0627\u0653");}
            if(i == 0x0623){return U8("\u0627\u0654");}
            if(i == 0x0624){return U8("\u0648\u0654");}
            if(i == 0x0625){return U8("\u0627\u0655");}
            if(i == 0x0626){return U8("\u064a\u0654");}
            if(i == 0x06c0){return U8("\u06d5\u0654");}
            if(i == 0x06c2){return U8("\u06c1\u0654");}
            if(i == 0x06d3){return U8("\u06d2\u0654");}
        }
        if(i >= 0x0900 && i <= 0x09ff){
            if(i == 0x0929){return U8("\u0928\u093c");}
            if(i == 0x0931){return U8("\u0930\u093c");}
            if(i == 0x0934){return U8("\u0933\u093c");}
            if(i >= 0x0958 && i <= 0x095f){return lookupEquiv_0x0958_to_0x095f_Table[i - 0x0958];}
            if(i == 0x09cb){return U8("\u09c7\u09be");}
            if(i == 0x09cc){return U8("\u09c7\u09d7");}
            if(i == 0x09dc){return U8("\u09a1\u09bc");}
            if(i == 0x09dd){return U8("\u09a2\u09bc");}
            if(i == 0x09df){return U8("\u09af\u09bc");}
        }
        if(i >= 0x0a00 && i <= 0x0aff){
            if(i == 0x0a33){return U8("\u0a32\u0a3c");}
            if(i == 0x0a36){return U8("\u0a38\u0a3c");}
            if(i == 0x0a59){return U8("\u0a16\u0a3c");}
            if(i == 0x0a5a){return U8("\u0a17\u0a3c");}
            if(i == 0x0a5b){return U8("\u0a1c\u0a3c");}
            if(i == 0x0a5e){return U8("\u0a2b\u0a3c");}
        }
        if(i >= 0x0b00 && i <= 0x0b7f){
            if(i == 0x0b48){return U8("\u0b47\u0b56");}
            if(i == 0x0b4b){return U8("\u0b47\u0b3e");}
            if(i == 0x0b4c){return U8("\u0b47\u0b57");}
            if(i == 0x0b5c){return U8("\u0b21\u0b3c");}
            if(i == 0x0b5d){return U8("\u0b22\u0b3c");}
        }
        if(i >= 0x0c00 && i <= 0x0cff){
            if(i == 0x0c48){return U8("\u0c46\u0c56");}
            if(i == 0x0cc0){return U8("\u0cbf\u0cd5");}
            if(i == 0x0cc7){return U8("\u0cc6\u0cd5");}
            if(i == 0x0cc8){return U8("\u0cc6\u0cd6");}
            if(i == 0x0cca){return U8("\u0cc6\u0cc2");}
            if(i == 0x0ccb){return U8("\u0cca\u0cd5");}
        }
        if(i >= 0x0d00 && i <= 0x0dff){
            if(i == 0x0d4a){return U8("\u0d46\u0d3e");}
            if(i == 0x0d4b){return U8("\u0d47\u0d3e");}
            if(i == 0x0d4c){return U8("\u0d46\u0d57");}
            if(i == 0x0dda){return U8("\u0dd9\u0dca");}
            if(i == 0x0ddc){return U8("\u0dd9\u0dcf");}
            if(i == 0x0ddd){return U8("\u0ddc\u0dca");}
            if(i == 0x0dde){return U8("\u0dd9\u0ddf");}
        }
        if(i >= 0x0f00 && i <= 0x0fff){
            if(i == 0x0f43){return U8("\u0f42\u0fb7");}
            if(i == 0x0f4d){return U8("\u0f4c\u0fb7");}
            if(i == 0x0f52){return U8("\u0f51\u0fb7");}
            if(i == 0x0f57){return U8("\u0f56\u0fb7");}
            if(i == 0x0f5c){return U8("\u0f5b\u0fb7");}
            if(i == 0x0f69){return U8("\u0f40\u0fb5");}
            if(i == 0x0f73){return U8("\u0f71\u0f72");}
            if(i == 0x0f75){return U8("\u0f71\u0f74");}
            if(i == 0x0f76){return U8("\u0fb2\u0f80");}
            if(i == 0x0f78){return U8("\u0fb3\u0f80");}
            if(i == 0x0f81){return U8("\u0f71\u0f80");}
            if(i == 0x0f93){return U8("\u0f92\u0fb7");}
            if(i == 0x0f9d){return U8("\u0f9c\u0fb7");}
            if(i == 0x0fa2){return U8("\u0fa1\u0fb7");}
            if(i == 0x0fa7){return U8("\u0fa6\u0fb7");}
            if(i == 0x0fac){return U8("\u0fab\u0fb7");}
            if(i == 0x0fb9){return U8("\u0f90\u0fb5");}
        }
    }
    if(i >= 0x1000 && i <= 0x1fff){
        if(i == 0x1026){return U8("\u1025\u102e");}
        if(i >= 0x1b00 && i <= 0x1b4f){
            if(i == 0x1b06){return U8("\u1b05\u1b35");}
            if(i == 0x1b08){return U8("\u1b07\u1b35");}
            if(i == 0x1b0a){return U8("\u1b09\u1b35");}
            if(i == 0x1b0c){return U8("\u1b0b\u1b35");}
            if(i == 0x1b0e){return U8("\u1b0d\u1b35");}
            if(i == 0x1b12){return U8("\u1b11\u1b35");}
            if(i == 0x1b3b){return U8("\u1b3a\u1b35");}
            if(i == 0x1b3d){return U8("\u1b3c\u1b35");}
            if(i == 0x1b40){return U8("\u1b3e\u1b35");}
            if(i == 0x1b41){return U8("\u1b3f\u1b35");}
            if(i == 0x1b43){return U8("\u1b42\u1b35");}
        }
        if(i >= 0x1e00 && i <= 0x1eff){return lookupEquiv_0x1e00_to_0x1eff_Table[i - 0x1e00];}
        if(i >= 0x1f00 && i <= 0x1fff){return lookupEquiv_0x1f00_to_0x1fff_Table[i - 0x1f00];}
    }
    if(i >= 0x2000 && i <= 0x2fff){
        if(i == 0x2000){return U8("\u2002");}
        if(i == 0x2001){return U8("\u2003");}
        if(i == 0x2126){return U8("\u03a9");}
        if(i == 0x212a){return U8("\u004b");}
        if(i == 0x212b){return U8("\u00c5");}
        if(i == 0x219a){return U8("\u2190\u0338");}
        if(i == 0x219b){return U8("\u2192\u0338");}
        if(i == 0x21ae){return U8("\u2194\u0338");}
        if(i == 0x21cd){return U8("\u21d0\u0338");}
        if(i == 0x21ce){return U8("\u21d4\u0338");}
        if(i == 0x21cf){return U8("\u21d2\u0338");}
        if(i == 0x2329){return U8("\u3008");}
        if(i == 0x232a){return U8("\u3009");}
        if(i == 0x2adc){return U8("\u2add\u0338");}
    }
    if(i >= 0x3000 && i <= 0x309f){
        if(i == 0x304c){return U8("\u304b\u3099");}
        if(i == 0x304e){return U8("\u304d\u3099");}
        if(i == 0x3050){return U8("\u304f\u3099");}
        if(i == 0x3052){return U8("\u3051\u3099");}
        if(i == 0x3054){return U8("\u3053\u3099");}
        if(i == 0x3056){return U8("\u3055\u3099");}
        if(i == 0x3058){return U8("\u3057\u3099");}
        if(i == 0x305a){return U8("\u3059\u3099");}
        if(i == 0x305c){return U8("\u305b\u3099");}
        if(i == 0x305e){return U8("\u305d\u3099");}
        if(i == 0x3060){return U8("\u305f\u3099");}
        if(i == 0x3062){return U8("\u3061\u3099");}
        if(i == 0x3065){return U8("\u3064\u3099");}
        if(i == 0x3067){return U8("\u3066\u3099");}
        if(i == 0x3069){return U8("\u3068\u3099");}
        if(i == 0x3070){return U8("\u306f\u3099");}
        if(i == 0x3071){return U8("\u306f\u309a");}
        if(i == 0x3073){return U8("\u3072\u3099");}
        if(i == 0x3074){return U8("\u3072\u309a");}
        if(i == 0x3076){return U8("\u3075\u3099");}
        if(i == 0x3077){return U8("\u3075\u309a");}
        if(i == 0x3079){return U8("\u3078\u3099");}
        if(i == 0x307a){return U8("\u3078\u309a");}
        if(i == 0x307c){return U8("\u307b\u3099");}
        if(i == 0x307d){return U8("\u307b\u309a");}
        if(i == 0x3094){return U8("\u3046\u3099");}
        if(i == 0x309e){return U8("\u309d\u3099");}
    }
    if(i >= 0x30a0 && i <= 0x30ff){
        if(i == 0x30ac){return U8("\u30ab\u3099");}
        if(i == 0x30ae){return U8("\u30ad\u3099");}
        if(i == 0x30b0){return U8("\u30af\u3099");}
        if(i == 0x30b2){return U8("\u30b1\u3099");}
        if(i == 0x30b4){return U8("\u30b3\u3099");}
        if(i == 0x30b6){return U8("\u30b5\u3099");}
        if(i == 0x30b8){return U8("\u30b7\u3099");}
        if(i == 0x30ba){return U8("\u30b9\u3099");}
        if(i == 0x30bc){return U8("\u30bb\u3099");}
        if(i == 0x30be){return U8("\u30bd\u3099");}
        if(i == 0x30c0){return U8("\u30bf\u3099");}
        if(i == 0x30c2){return U8("\u30c1\u3099");}
        if(i == 0x30c5){return U8("\u30c4\u3099");}
        if(i == 0x30c7){return U8("\u30c6\u3099");}
        if(i == 0x30c9){return U8("\u30c8\u3099");}
        if(i == 0x30d0){return U8("\u30cf\u3099");}
        if(i == 0x30d1){return U8("\u30cf\u309a");}
        if(i == 0x30d3){return U8("\u30d2\u3099");}
        if(i == 0x30d4){return U8("\u30d2\u309a");}
        if(i == 0x30d6){return U8("\u30d5\u3099");}
        if(i == 0x30d7){return U8("\u30d5\u309a");}
        if(i == 0x30d9){return U8("\u30d8\u3099");}
        if(i == 0x30da){return U8("\u30d8\u309a");}
        if(i == 0x30dc){return U8("\u30db\u3099");}
        if(i == 0x30dd){return U8("\u30db\u309a");}
        if(i == 0x30f4){return U8("\u30a6\u3099");}
        if(i == 0x30f7){return U8("\u30ef\u3099");}
        if(i == 0x30f8){return U8("\u30f0\u3099");}
        if(i == 0x30f9){return U8("\u30f1\u3099");}
        if(i == 0x30fa){return U8("\u30f2\u3099");}
        if(i == 0x30fe){return U8("\u30fd\u3099");}
    }
    if(i >= 0xf900 && i <= 0xffff){
        if(i >= 0xf900 && i <= 0xfad9){return lookupEquiv_0xf900_to_0xfad9_Table[i - 0xf900];}
        if(i == 0xfb1d){return U8("\u05d9\u05b4");}
        if(i == 0xfb1f){return U8("\u05f2\u05b7");}
        if(i >= 0xfb2a && i <= 0xfb4e){return lookupEquiv_0xfb2a_to_0xfb4e_Table[i - 0xfb2a];}
    }
    if(i >= 0x10000 && i <= 0x11fff){
        if(i == 0x105c9){return U8("\U000105d2\u0307");}
        if(i == 0x105e4){return U8("\U000105da\u0307");}
        if(i == 0x1109a){return U8("\U00011099\U000110ba");}
        if(i == 0x1109c){return U8("\U0001109b\U000110ba");}
        if(i == 0x110ab){return U8("\U000110a5\U000110ba");}
        if(i == 0x1112e){return U8("\U00011131\U00011127");}
        if(i == 0x1112f){return U8("\U00011132\U00011127");}
        if(i == 0x1134b){return U8("\U00011347\U0001133e");}
        if(i == 0x1134c){return U8("\U00011347\U00011357");}
        if(i == 0x11383){return U8("\U00011382\U000113c9");}
        if(i == 0x11385){return U8("\U00011384\U000113bb");}
        if(i == 0x1138e){return U8("\U0001138b\U000113c2");}
        if(i == 0x11391){return U8("\U00011390\U000113c9");}
        if(i == 0x113c5){return U8("\U000113c2\U000113c2");}
        if(i == 0x113c7){return U8("\U000113c2\U000113b8");}
        if(i == 0x113c8){return U8("\U000113c2\U000113c9");}
        if(i == 0x114bb){return U8("\U000114b9\U000114ba");}
        if(i == 0x114bc){return U8("\U000114b9\U000114b0");}
        if(i == 0x114be){return U8("\U000114b9\U000114bd");}
        if(i == 0x115ba){return U8("\U000115b8\U000115af");}
        if(i == 0x115bb){return U8("\U000115b9\U000115af");}
        if(i == 0x11938){return U8("\U00011935\U00011930");}
    }
    if(i >= 0x16121 && i <= 0x16128){return lookupEquiv_0x16121_to_0x16128_Table[i - 0x16121];}
    if(i >= 0x16d68 && i <= 0x16d70){
        if(i == 0x16d68){return U8("\U00016d67\U00016d67");}
        if(i == 0x16d69){return U8("\U00016d63\U00016d67");}
        if(i == 0x16d6a){return U8("\U00016d69\U00016d67");}
    }
    if(i >= 0x1d15e && i <= 0x1d164){return lookupEquiv_0x1d15e_to_0x1d164_Table[i - 0x1d15e];}
    if(i >= 0x1d1bb && i <= 0x1d1c0){return lookupEquiv_0x1d1bb_to_0x1d1c0_Table[i - 0x1d1bb];}
    if(i >= 0x2f800 && i <= 0x2fa1d){return lookupEquiv_0x2f800_to_0x2fa1d_Table[i - 0x2f800];}
    return "";
}

const char* lookupCompat_0x00b2_to_0x00be_Table[] = { U8("\u0032"), U8("\u0033"), U8("\u0020\u0301"), U8("\u03bc"), U8(""), U8(""), U8("\u0020\u0327"), U8("\u0031"), U8("\u006f"), U8(""), U8("\u0031\u2044\u0034"), U8("\u0031\u2044\u0032"), U8("\u0033\u2044\u0034") };

const char* lookupCompat_0x01c4_to_0x01cc_Table[] = { U8("\u0044\u017d"), U8("\u0044\u017e"), U8("\u0064\u017e"), U8("\u004c\u004a"), U8("\u004c\u006a"), U8("\u006c\u006a"), U8("\u004e\u004a"), U8("\u004e\u006a"), U8("\u006e\u006a") };

const char* lookupCompat_0x02b0_to_0x02b8_Table[] = { U8("\u0068"), U8("\u0266"), U8("\u006a"), U8("\u0072"), U8("\u0279"), U8("\u027b"), U8("\u0281"), U8("\u0077"), U8("\u0079") };

const char* lookupCompat_0x02d8_to_0x02dd_Table[] = { U8("\u0020\u0306"), U8("\u0020\u0307"), U8("\u0020\u030a"), U8("\u0020\u0328"), U8("\u0020\u0303"), U8("\u0020\u030b") };

const char* lookupCompat_0x02e0_to_0x02e4_Table[] = { U8("\u0263"), U8("\u006c"), U8("\u0073"), U8("\u0078"), U8("\u0295") };

const char* lookupCompat_0x1d2c_to_0x1d6a_Table[] = { U8("\u0041"), U8("\u00c6"), U8("\u0042"), U8(""), U8("\u0044"), U8("\u0045"), U8("\u018e"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8(""), U8("\u004f"), U8("\u0222"), U8("\u0050"), U8("\u0052"), U8("\u0054"), U8("\u0055"), U8("\u0057"), U8("\u0061"), U8("\u0250"), U8("\u0251"), U8("\u1d02"), U8("\u0062"), U8("\u0064"), U8("\u0065"), U8("\u0259"), U8("\u025b"), U8("\u025c"), U8("\u0067"), U8(""), U8("\u006b"), U8("\u006d"), U8("\u014b"), U8("\u006f"), U8("\u0254"), U8("\u1d16"), U8("\u1d17"), U8("\u0070"), U8("\u0074"), U8("\u0075"), U8("\u1d1d"), U8("\u026f"), U8("\u0076"), U8("\u1d25"), U8("\u03b2"), U8("\u03b3"), U8("\u03b4"), U8("\u03c6"), U8("\u03c7"), U8("\u0069"), U8("\u0072"), U8("\u0075"), U8("\u0076"), U8("\u03b2"), U8("\u03b3"), U8("\u03c1"), U8("\u03c6"), U8("\u03c7") };

const char* lookupCompat_0x1d9b_to_0x1dbf_Table[] = { U8("\u0252"), U8("\u0063"), U8("\u0255"), U8("\u00f0"), U8("\u025c"), U8("\u0066"), U8("\u025f"), U8("\u0261"), U8("\u0265"), U8("\u0268"), U8("\u0269"), U8("\u026a"), U8("\u1d7b"), U8("\u029d"), U8("\u026d"), U8("\u1d85"), U8("\u029f"), U8("\u0271"), U8("\u0270"), U8("\u0272"), U8("\u0273"), U8("\u0274"), U8("\u0275"), U8("\u0278"), U8("\u0282"), U8("\u0283"), U8("\u01ab"), U8("\u0289"), U8("\u028a"), U8("\u1d1c"), U8("\u028b"), U8("\u028c"), U8("\u007a"), U8("\u0290"), U8("\u0291"), U8("\u0292"), U8("\u03b8") };

const char* lookupCompat_0x2070_to_0x209c_Table[] = { U8("\u0030"), U8("\u0069"), U8(""), U8(""), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u002b"), U8("\u2212"), U8("\u003d"), U8("\u0028"), U8("\u0029"), U8("\u006e"), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u002b"), U8("\u2212"), U8("\u003d"), U8("\u0028"), U8("\u0029"), U8(""), U8("\u0061"), U8("\u0065"), U8("\u006f"), U8("\u0078"), U8("\u0259"), U8("\u0068"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u0070"), U8("\u0073"), U8("\u0074") };

const char* lookupCompat_0x2100_to_0x217f_Table[] = { U8("\u0061\u002f\u0063"), U8("\u0061\u002f\u0073"), U8("\u0043"), U8("\u00b0\u0043"), U8(""), U8("\u0063\u002f\u006f"), U8("\u0063\u002f\u0075"), U8("\u0190"), U8(""), U8("\u00b0\u0046"), U8("\u0067"), U8("\u0048"), U8("\u0048"), U8("\u0048"), U8("\u0068"), U8("\u0127"), U8("\u0049"), U8("\u0049"), U8("\u004c"), U8("\u006c"), U8(""), U8("\u004e"), U8("\u004e\u006f"), U8(""), U8(""), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0052"), U8("\u0052"), U8(""), U8(""), U8("\u0053\u004d"), U8("\u0054\u0045\u004c"), U8("\u0054\u004d"), U8(""), U8("\u005a"), U8(""), U8(""), U8(""), U8("\u005a"), U8(""), U8(""), U8(""), U8("\u0042"), U8("\u0043"), U8(""), U8("\u0065"), U8("\u0045"), U8("\u0046"), U8(""), U8("\u004d"), U8("\u006f"), U8("\u05d0"), U8("\u05d1"), U8("\u05d2"), U8("\u05d3"), U8("\u0069"), U8(""), U8("\u0046\u0041\u0058"), U8("\u03c0"), U8("\u03b3"), U8("\u0393"), U8("\u03a0"), U8("\u2211"), U8(""), U8(""), U8(""), U8(""), U8("\u0044"), U8("\u0064"), U8("\u0065"), U8("\u0069"), U8("\u006a"), U8(""), U8(""), U8(""), U8(""), U8(""), U8(""), U8("\u0031\u2044\u0037"), U8("\u0031\u2044\u0039"), U8("\u0031\u2044\u0031\u0030"), U8("\u0031\u2044\u0033"), U8("\u0032\u2044\u0033"), U8("\u0031\u2044\u0035"), U8("\u0032\u2044\u0035"), U8("\u0033\u2044\u0035"), U8("\u0034\u2044\u0035"), U8("\u0031\u2044\u0036"), U8("\u0035\u2044\u0036"), U8("\u0031\u2044\u0038"), U8("\u0033\u2044\u0038"), U8("\u0035\u2044\u0038"), U8("\u0037\u2044\u0038"), U8("\u0031\u2044"), U8("\u0049"), U8("\u0049\u0049"), U8("\u0049\u0049\u0049"), U8("\u0049\u0056"), U8("\u0056"), U8("\u0056\u0049"), U8("\u0056\u0049\u0049"), U8("\u0056\u0049\u0049\u0049"), U8("\u0049\u0058"), U8("\u0058"), U8("\u0058\u0049"), U8("\u0058\u0049\u0049"), U8("\u004c"), U8("\u0043"), U8("\u0044"), U8("\u004d"), U8("\u0069"), U8("\u0069\u0069"), U8("\u0069\u0069\u0069"), U8("\u0069\u0076"), U8("\u0076"), U8("\u0076\u0069"), U8("\u0076\u0069\u0069"), U8("\u0076\u0069\u0069\u0069"), U8("\u0069\u0078"), U8("\u0078"), U8("\u0078\u0069"), U8("\u0078\u0069\u0069"), U8("\u006c"), U8("\u0063"), U8("\u0064"), U8("\u006d") };

const char* lookupCompat_0x2460_to_0x24ea_Table[] = { U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u0031\u0030"), U8("\u0031\u0031"), U8("\u0031\u0032"), U8("\u0031\u0033"), U8("\u0031\u0034"), U8("\u0031\u0035"), U8("\u0031\u0036"), U8("\u0031\u0037"), U8("\u0031\u0038"), U8("\u0031\u0039"), U8("\u0032\u0030"), U8("\u0028\u0031\u0029"), U8("\u0028\u0032\u0029"), U8("\u0028\u0033\u0029"), U8("\u0028\u0034\u0029"), U8("\u0028\u0035\u0029"), U8("\u0028\u0036\u0029"), U8("\u0028\u0037\u0029"), U8("\u0028\u0038\u0029"), U8("\u0028\u0039\u0029"), U8("\u0028\u0031\u0030\u0029"), U8("\u0028\u0031\u0031\u0029"), U8("\u0028\u0031\u0032\u0029"), U8("\u0028\u0031\u0033\u0029"), U8("\u0028\u0031\u0034\u0029"), U8("\u0028\u0031\u0035\u0029"), U8("\u0028\u0031\u0036\u0029"), U8("\u0028\u0031\u0037\u0029"), U8("\u0028\u0031\u0038\u0029"), U8("\u0028\u0031\u0039\u0029"), U8("\u0028\u0032\u0030\u0029"), U8("\u0031\u002e"), U8("\u0032\u002e"), U8("\u0033\u002e"), U8("\u0034\u002e"), U8("\u0035\u002e"), U8("\u0036\u002e"), U8("\u0037\u002e"), U8("\u0038\u002e"), U8("\u0039\u002e"), U8("\u0031\u0030\u002e"), U8("\u0031\u0031\u002e"), U8("\u0031\u0032\u002e"), U8("\u0031\u0033\u002e"), U8("\u0031\u0034\u002e"), U8("\u0031\u0035\u002e"), U8("\u0031\u0036\u002e"), U8("\u0031\u0037\u002e"), U8("\u0031\u0038\u002e"), U8("\u0031\u0039\u002e"), U8("\u0032\u0030\u002e"), U8("\u0028\u0061\u0029"), U8("\u0028\u0062\u0029"), U8("\u0028\u0063\u0029"), U8("\u0028\u0064\u0029"), U8("\u0028\u0065\u0029"), U8("\u0028\u0066\u0029"), U8("\u0028\u0067\u0029"), U8("\u0028\u0068\u0029"), U8("\u0028\u0069\u0029"), U8("\u0028\u006a\u0029"), U8("\u0028\u006b\u0029"), U8("\u0028\u006c\u0029"), U8("\u0028\u006d\u0029"), U8("\u0028\u006e\u0029"), U8("\u0028\u006f\u0029"), U8("\u0028\u0070\u0029"), U8("\u0028\u0071\u0029"), U8("\u0028\u0072\u0029"), U8("\u0028\u0073\u0029"), U8("\u0028\u0074\u0029"), U8("\u0028\u0075\u0029"), U8("\u0028\u0076\u0029"), U8("\u0028\u0077\u0029"), U8("\u0028\u0078\u0029"), U8("\u0028\u0079\u0029"), U8("\u0028\u007a\u0029"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0030") };

const char* lookupCompat_0x2f00_to_0x2fd5_Table[] = { U8("\u4e00"), U8("\u4e28"), U8("\u4e36"), U8("\u4e3f"), U8("\u4e59"), U8("\u4e85"), U8("\u4e8c"), U8("\u4ea0"), U8("\u4eba"), U8("\u513f"), U8("\u5165"), U8("\u516b"), U8("\u5182"), U8("\u5196"), U8("\u51ab"), U8("\u51e0"), U8("\u51f5"), U8("\u5200"), U8("\u529b"), U8("\u52f9"), U8("\u5315"), U8("\u531a"), U8("\u5338"), U8("\u5341"), U8("\u535c"), U8("\u5369"), U8("\u5382"), U8("\u53b6"), U8("\u53c8"), U8("\u53e3"), U8("\u56d7"), U8("\u571f"), U8("\u58eb"), U8("\u5902"), U8("\u590a"), U8("\u5915"), U8("\u5927"), U8("\u5973"), U8("\u5b50"), U8("\u5b80"), U8("\u5bf8"), U8("\u5c0f"), U8("\u5c22"), U8("\u5c38"), U8("\u5c6e"), U8("\u5c71"), U8("\u5ddb"), U8("\u5de5"), U8("\u5df1"), U8("\u5dfe"), U8("\u5e72"), U8("\u5e7a"), U8("\u5e7f"), U8("\u5ef4"), U8("\u5efe"), U8("\u5f0b"), U8("\u5f13"), U8("\u5f50"), U8("\u5f61"), U8("\u5f73"), U8("\u5fc3"), U8("\u6208"), U8("\u6236"), U8("\u624b"), U8("\u652f"), U8("\u6534"), U8("\u6587"), U8("\u6597"), U8("\u65a4"), U8("\u65b9"), U8("\u65e0"), U8("\u65e5"), U8("\u66f0"), U8("\u6708"), U8("\u6728"), U8("\u6b20"), U8("\u6b62"), U8("\u6b79"), U8("\u6bb3"), U8("\u6bcb"), U8("\u6bd4"), U8("\u6bdb"), U8("\u6c0f"), U8("\u6c14"), U8("\u6c34"), U8("\u706b"), U8("\u722a"), U8("\u7236"), U8("\u723b"), U8("\u723f"), U8("\u7247"), U8("\u7259"), U8("\u725b"), U8("\u72ac"), U8("\u7384"), U8("\u7389"), U8("\u74dc"), U8("\u74e6"), U8("\u7518"), U8("\u751f"), U8("\u7528"), U8("\u7530"), U8("\u758b"), U8("\u7592"), U8("\u7676"), U8("\u767d"), U8("\u76ae"), U8("\u76bf"), U8("\u76ee"), U8("\u77db"), U8("\u77e2"), U8("\u77f3"), U8("\u793a"), U8("\u79b8"), U8("\u79be"), U8("\u7a74"), U8("\u7acb"), U8("\u7af9"), U8("\u7c73"), U8("\u7cf8"), U8("\u7f36"), U8("\u7f51"), U8("\u7f8a"), U8("\u7fbd"), U8("\u8001"), U8("\u800c"), U8("\u8012"), U8("\u8033"), U8("\u807f"), U8("\u8089"), U8("\u81e3"), U8("\u81ea"), U8("\u81f3"), U8("\u81fc"), U8("\u820c"), U8("\u821b"), U8("\u821f"), U8("\u826e"), U8("\u8272"), U8("\u8278"), U8("\u864d"), U8("\u866b"), U8("\u8840"), U8("\u884c"), U8("\u8863"), U8("\u897e"), U8("\u898b"), U8("\u89d2"), U8("\u8a00"), U8("\u8c37"), U8("\u8c46"), U8("\u8c55"), U8("\u8c78"), U8("\u8c9d"), U8("\u8d64"), U8("\u8d70"), U8("\u8db3"), U8("\u8eab"), U8("\u8eca"), U8("\u8f9b"), U8("\u8fb0"), U8("\u8fb5"), U8("\u9091"), U8("\u9149"), U8("\u91c6"), U8("\u91cc"), U8("\u91d1"), U8("\u9577"), U8("\u9580"), U8("\u961c"), U8("\u96b6"), U8("\u96b9"), U8("\u96e8"), U8("\u9751"), U8("\u975e"), U8("\u9762"), U8("\u9769"), U8("\u97cb"), U8("\u97ed"), U8("\u97f3"), U8("\u9801"), U8("\u98a8"), U8("\u98db"), U8("\u98df"), U8("\u9996"), U8("\u9999"), U8("\u99ac"), U8("\u9aa8"), U8("\u9ad8"), U8("\u9adf"), U8("\u9b25"), U8("\u9b2f"), U8("\u9b32"), U8("\u9b3c"), U8("\u9b5a"), U8("\u9ce5"), U8("\u9e75"), U8("\u9e7f"), U8("\u9ea5"), U8("\u9ebb"), U8("\u9ec3"), U8("\u9ecd"), U8("\u9ed1"), U8("\u9ef9"), U8("\u9efd"), U8("\u9f0e"), U8("\u9f13"), U8("\u9f20"), U8("\u9f3b"), U8("\u9f4a"), U8("\u9f52"), U8("\u9f8d"), U8("\u9f9c"), U8("\u9fa0") };

const char* lookupCompat_0x3131_to_0x319f_Table[] = { U8("\u1100"), U8("\u1101"), U8("\u11aa"), U8("\u1102"), U8("\u11ac"), U8("\u11ad"), U8("\u1103"), U8("\u1104"), U8("\u1105"), U8("\u11b0"), U8("\u11b1"), U8("\u11b2"), U8("\u11b3"), U8("\u11b4"), U8("\u11b5"), U8("\u111a"), U8("\u1106"), U8("\u1107"), U8("\u1108"), U8("\u1121"), U8("\u1109"), U8("\u110a"), U8("\u110b"), U8("\u110c"), U8("\u110d"), U8("\u110e"), U8("\u110f"), U8("\u1110"), U8("\u1111"), U8("\u1112"), U8("\u1161"), U8("\u1162"), U8("\u1163"), U8("\u1164"), U8("\u1165"), U8("\u1166"), U8("\u1167"), U8("\u1168"), U8("\u1169"), U8("\u116a"), U8("\u116b"), U8("\u116c"), U8("\u116d"), U8("\u116e"), U8("\u116f"), U8("\u1170"), U8("\u1171"), U8("\u1172"), U8("\u1173"), U8("\u1174"), U8("\u1175"), U8("\u1160"), U8("\u1114"), U8("\u1115"), U8("\u11c7"), U8("\u11c8"), U8("\u11cc"), U8("\u11ce"), U8("\u11d3"), U8("\u11d7"), U8("\u11d9"), U8("\u111c"), U8("\u11dd"), U8("\u11df"), U8("\u111d"), U8("\u111e"), U8("\u1120"), U8("\u1122"), U8("\u1123"), U8("\u1127"), U8("\u1129"), U8("\u112b"), U8("\u112c"), U8("\u112d"), U8("\u112e"), U8("\u112f"), U8("\u1132"), U8("\u1136"), U8("\u1140"), U8("\u1147"), U8("\u114c"), U8("\u11f1"), U8("\u11f2"), U8("\u1157"), U8("\u1158"), U8("\u1159"), U8("\u1184"), U8("\u1185"), U8("\u1188"), U8("\u1191"), U8("\u1192"), U8("\u1194"), U8("\u119e"), U8("\u11a1"), U8(""), U8(""), U8(""), U8("\u4e00"), U8("\u4e8c"), U8("\u4e09"), U8("\u56db"), U8("\u4e0a"), U8("\u4e2d"), U8("\u4e0b"), U8("\u7532"), U8("\u4e59"), U8("\u4e19"), U8("\u4e01"), U8("\u5929"), U8("\u5730"), U8("\u4eba") };

const char* lookupCompat_0x3200_to_0x3247_Table[] = { U8("\u0028\u1100\u0029"), U8("\u0028\u1102\u0029"), U8("\u0028\u1103\u0029"), U8("\u0028\u1105\u0029"), U8("\u0028\u1106\u0029"), U8("\u0028\u1107\u0029"), U8("\u0028\u1109\u0029"), U8("\u0028\u110b\u0029"), U8("\u0028\u110c\u0029"), U8("\u0028\u110e\u0029"), U8("\u0028\u110f\u0029"), U8("\u0028\u1110\u0029"), U8("\u0028\u1111\u0029"), U8("\u0028\u1112\u0029"), U8("\u0028\u1100\u1161\u0029"), U8("\u0028\u1102\u1161\u0029"), U8("\u0028\u1103\u1161\u0029"), U8("\u0028\u1105\u1161\u0029"), U8("\u0028\u1106\u1161\u0029"), U8("\u0028\u1107\u1161\u0029"), U8("\u0028\u1109\u1161\u0029"), U8("\u0028\u110b\u1161\u0029"), U8("\u0028\u110c\u1161\u0029"), U8("\u0028\u110e\u1161\u0029"), U8("\u0028\u110f\u1161\u0029"), U8("\u0028\u1110\u1161\u0029"), U8("\u0028\u1111\u1161\u0029"), U8("\u0028\u1112\u1161\u0029"), U8("\u0028\u110c\u116e\u0029"), U8("\u0028\u110b\u1169\u110c\u1165\u11ab\u0029"), U8("\u0028\u110b\u1169\u1112\u116e\u0029"), U8(""), U8("\u0028\u4e00\u0029"), U8("\u0028\u4e8c\u0029"), U8("\u0028\u4e09\u0029"), U8("\u0028\u56db\u0029"), U8("\u0028\u4e94\u0029"), U8("\u0028\u516d\u0029"), U8("\u0028\u4e03\u0029"), U8("\u0028\u516b\u0029"), U8("\u0028\u4e5d\u0029"), U8("\u0028\u5341\u0029"), U8("\u0028\u6708\u0029"), U8("\u0028\u706b\u0029"), U8("\u0028\u6c34\u0029"), U8("\u0028\u6728\u0029"), U8("\u0028\u91d1\u0029"), U8("\u0028\u571f\u0029"), U8("\u0028\u65e5\u0029"), U8("\u0028\u682a\u0029"), U8("\u0028\u6709\u0029"), U8("\u0028\u793e\u0029"), U8("\u0028\u540d\u0029"), U8("\u0028\u7279\u0029"), U8("\u0028\u8ca1\u0029"), U8("\u0028\u795d\u0029"), U8("\u0028\u52b4\u0029"), U8("\u0028\u4ee3\u0029"), U8("\u0028\u547c\u0029"), U8("\u0028\u5b66\u0029"), U8("\u0028\u76e3\u0029"), U8("\u0028\u4f01\u0029"), U8("\u0028\u8cc7\u0029"), U8("\u0028\u5354\u0029"), U8("\u0028\u796d\u0029"), U8("\u0028\u4f11\u0029"), U8("\u0028\u81ea\u0029"), U8("\u0028\u81f3\u0029"), U8("\u554f"), U8("\u5e7c"), U8("\u6587"), U8("\u7b8f") };

const char* lookupCompat_0x3250_to_0x33ff_Table[] = { U8("\u0050\u0054\u0045"), U8("\u0032\u0031"), U8("\u0032\u0032"), U8("\u0032\u0033"), U8("\u0032\u0034"), U8("\u0032\u0035"), U8("\u0032\u0036"), U8("\u0032\u0037"), U8("\u0032\u0038"), U8("\u0032\u0039"), U8("\u0033\u0030"), U8("\u0033\u0031"), U8("\u0033\u0032"), U8("\u0033\u0033"), U8("\u0033\u0034"), U8("\u0033\u0035"), U8("\u1100"), U8("\u1102"), U8("\u1103"), U8("\u1105"), U8("\u1106"), U8("\u1107"), U8("\u1109"), U8("\u110b"), U8("\u110c"), U8("\u110e"), U8("\u110f"), U8("\u1110"), U8("\u1111"), U8("\u1112"), U8("\u1100\u1161"), U8("\u1102\u1161"), U8("\u1103\u1161"), U8("\u1105\u1161"), U8("\u1106\u1161"), U8("\u1107\u1161"), U8("\u1109\u1161"), U8("\u110b\u1161"), U8("\u110c\u1161"), U8("\u110e\u1161"), U8("\u110f\u1161"), U8("\u1110\u1161"), U8("\u1111\u1161"), U8("\u1112\u1161"), U8("\u110e\u1161\u11b7\u1100\u1169"), U8("\u110c\u116e\u110b\u1174"), U8("\u110b\u116e"), U8(""), U8("\u4e00"), U8("\u4e8c"), U8("\u4e09"), U8("\u56db"), U8("\u4e94"), U8("\u516d"), U8("\u4e03"), U8("\u516b"), U8("\u4e5d"), U8("\u5341"), U8("\u6708"), U8("\u706b"), U8("\u6c34"), U8("\u6728"), U8("\u91d1"), U8("\u571f"), U8("\u65e5"), U8("\u682a"), U8("\u6709"), U8("\u793e"), U8("\u540d"), U8("\u7279"), U8("\u8ca1"), U8("\u795d"), U8("\u52b4"), U8("\u79d8"), U8("\u7537"), U8("\u5973"), U8("\u9069"), U8("\u512a"), U8("\u5370"), U8("\u6ce8"), U8("\u9805"), U8("\u4f11"), U8("\u5199"), U8("\u6b63"), U8("\u4e0a"), U8("\u4e2d"), U8("\u4e0b"), U8("\u5de6"), U8("\u53f3"), U8("\u533b"), U8("\u5b97"), U8("\u5b66"), U8("\u76e3"), U8("\u4f01"), U8("\u8cc7"), U8("\u5354"), U8("\u591c"), U8("\u0033\u0036"), U8("\u0033\u0037"), U8("\u0033\u0038"), U8("\u0033\u0039"), U8("\u0034\u0030"), U8("\u0034\u0031"), U8("\u0034\u0032"), U8("\u0034\u0033"), U8("\u0034\u0034"), U8("\u0034\u0035"), U8("\u0034\u0036"), U8("\u0034\u0037"), U8("\u0034\u0038"), U8("\u0034\u0039"), U8("\u0035\u0030"), U8("\u0031\u6708"), U8("\u0032\u6708"), U8("\u0033\u6708"), U8("\u0034\u6708"), U8("\u0035\u6708"), U8("\u0036\u6708"), U8("\u0037\u6708"), U8("\u0038\u6708"), U8("\u0039\u6708"), U8("\u0031\u0030\u6708"), U8("\u0031\u0031\u6708"), U8("\u0031\u0032\u6708"), U8("\u0048\u0067"), U8("\u0065\u0072\u0067"), U8("\u0065\u0056"), U8("\u004c\u0054\u0044"), U8("\u30a2"), U8("\u30a4"), U8("\u30a6"), U8("\u30a8"), U8("\u30aa"), U8("\u30ab"), U8("\u30ad"), U8("\u30af"), U8("\u30b1"), U8("\u30b3"), U8("\u30b5"), U8("\u30b7"), U8("\u30b9"), U8("\u30bb"), U8("\u30bd"), U8("\u30bf"), U8("\u30c1"), U8("\u30c4"), U8("\u30c6"), U8("\u30c8"), U8("\u30ca"), U8("\u30cb"), U8("\u30cc"), U8("\u30cd"), U8("\u30ce"), U8("\u30cf"), U8("\u30d2"), U8("\u30d5"), U8("\u30d8"), U8("\u30db"), U8("\u30de"), U8("\u30df"), U8("\u30e0"), U8("\u30e1"), U8("\u30e2"), U8("\u30e4"), U8("\u30e6"), U8("\u30e8"), U8("\u30e9"), U8("\u30ea"), U8("\u30eb"), U8("\u30ec"), U8("\u30ed"), U8("\u30ef"), U8("\u30f0"), U8("\u30f1"), U8("\u30f2"), U8("\u4ee4\u548c"), U8("\u30a2\u30d1\u30fc\u30c8"), U8("\u30a2\u30eb\u30d5\u30a1"), U8("\u30a2\u30f3\u30da\u30a2"), U8("\u30a2\u30fc\u30eb"), U8("\u30a4\u30cb\u30f3\u30b0"), U8("\u30a4\u30f3\u30c1"), U8("\u30a6\u30a9\u30f3"), U8("\u30a8\u30b9\u30af\u30fc\u30c9"), U8("\u30a8\u30fc\u30ab\u30fc"), U8("\u30aa\u30f3\u30b9"), U8("\u30aa\u30fc\u30e0"), U8("\u30ab\u30a4\u30ea"), U8("\u30ab\u30e9\u30c3\u30c8"), U8("\u30ab\u30ed\u30ea\u30fc"), U8("\u30ac\u30ed\u30f3"), U8("\u30ac\u30f3\u30de"), U8("\u30ae\u30ac"), U8("\u30ae\u30cb\u30fc"), U8("\u30ad\u30e5\u30ea\u30fc"), U8("\u30ae\u30eb\u30c0\u30fc"), U8("\u30ad\u30ed"), U8("\u30ad\u30ed\u30b0\u30e9\u30e0"), U8("\u30ad\u30ed\u30e1\u30fc\u30c8\u30eb"), U8("\u30ad\u30ed\u30ef\u30c3\u30c8"), U8("\u30b0\u30e9\u30e0"), U8("\u30b0\u30e9\u30e0\u30c8\u30f3"), U8("\u30af\u30eb\u30bc\u30a4\u30ed"), U8("\u30af\u30ed\u30fc\u30cd"), U8("\u30b1\u30fc\u30b9"), U8("\u30b3\u30eb\u30ca"), U8("\u30b3\u30fc\u30dd"), U8("\u30b5\u30a4\u30af\u30eb"), U8("\u30b5\u30f3\u30c1\u30fc\u30e0"), U8("\u30b7\u30ea\u30f3\u30b0"), U8("\u30bb\u30f3\u30c1"), U8("\u30bb\u30f3\u30c8"), U8("\u30c0\u30fc\u30b9"), U8("\u30c7\u30b7"), U8("\u30c9\u30eb"), U8("\u30c8\u30f3"), U8("\u30ca\u30ce"), U8("\u30ce\u30c3\u30c8"), U8("\u30cf\u30a4\u30c4"), U8("\u30d1\u30fc\u30bb\u30f3\u30c8"), U8("\u30d1\u30fc\u30c4"), U8("\u30d0\u30fc\u30ec\u30eb"), U8("\u30d4\u30a2\u30b9\u30c8\u30eb"), U8("\u30d4\u30af\u30eb"), U8("\u30d4\u30b3"), U8("\u30d3\u30eb"), U8("\u30d5\u30a1\u30e9\u30c3\u30c9"), U8("\u30d5\u30a3\u30fc\u30c8"), U8("\u30d6\u30c3\u30b7\u30a7\u30eb"), U8("\u30d5\u30e9\u30f3"), U8("\u30d8\u30af\u30bf\u30fc\u30eb"), U8("\u30da\u30bd"), U8("\u30da\u30cb\u30d2"), U8("\u30d8\u30eb\u30c4"), U8("\u30da\u30f3\u30b9"), U8("\u30da\u30fc\u30b8"), U8("\u30d9\u30fc\u30bf"), U8("\u30dd\u30a4\u30f3\u30c8"), U8("\u30dc\u30eb\u30c8"), U8("\u30db\u30f3"), U8("\u30dd\u30f3\u30c9"), U8("\u30db\u30fc\u30eb"), U8("\u30db\u30fc\u30f3"), U8("\u30de\u30a4\u30af\u30ed"), U8("\u30de\u30a4\u30eb"), U8("\u30de\u30c3\u30cf"), U8("\u30de\u30eb\u30af"), U8("\u30de\u30f3\u30b7\u30e7\u30f3"), U8("\u30df\u30af\u30ed\u30f3"), U8("\u30df\u30ea"), U8("\u30df\u30ea\u30d0\u30fc\u30eb"), U8("\u30e1\u30ac"), U8("\u30e1\u30ac\u30c8\u30f3"), U8("\u30e1\u30fc\u30c8\u30eb"), U8("\u30e4\u30fc\u30c9"), U8("\u30e4\u30fc\u30eb"), U8("\u30e6\u30a2\u30f3"), U8("\u30ea\u30c3\u30c8\u30eb"), U8("\u30ea\u30e9"), U8("\u30eb\u30d4\u30fc"), U8("\u30eb\u30fc\u30d6\u30eb"), U8("\u30ec\u30e0"), U8("\u30ec\u30f3\u30c8\u30b2\u30f3"), U8("\u30ef\u30c3\u30c8"), U8("\u0030\u70b9"), U8("\u0031\u70b9"), U8("\u0032\u70b9"), U8("\u0033\u70b9"), U8("\u0034\u70b9"), U8("\u0035\u70b9"), U8("\u0036\u70b9"), U8("\u0037\u70b9"), U8("\u0038\u70b9"), U8("\u0039\u70b9"), U8("\u0031\u0030\u70b9"), U8("\u0031\u0031\u70b9"), U8("\u0031\u0032\u70b9"), U8("\u0031\u0033\u70b9"), U8("\u0031\u0034\u70b9"), U8("\u0031\u0035\u70b9"), U8("\u0031\u0036\u70b9"), U8("\u0031\u0037\u70b9"), U8("\u0031\u0038\u70b9"), U8("\u0031\u0039\u70b9"), U8("\u0032\u0030\u70b9"), U8("\u0032\u0031\u70b9"), U8("\u0032\u0032\u70b9"), U8("\u0032\u0033\u70b9"), U8("\u0032\u0034\u70b9"), U8("\u0068\u0050\u0061"), U8("\u0064\u0061"), U8("\u0041\u0055"), U8("\u0062\u0061\u0072"), U8("\u006f\u0056"), U8("\u0070\u0063"), U8("\u0064\u006d"), U8("\u0064\u006d\u00b2"), U8("\u0064\u006d\u00b3"), U8("\u0049\u0055"), U8("\u5e73\u6210"), U8("\u662d\u548c"), U8("\u5927\u6b63"), U8("\u660e\u6cbb"), U8("\u682a\u5f0f\u4f1a\u793e"), U8("\u0070\u0041"), U8("\u006e\u0041"), U8("\u03bc\u0041"), U8("\u006d\u0041"), U8("\u006b\u0041"), U8("\u004b\u0042"), U8("\u004d\u0042"), U8("\u0047\u0042"), U8("\u0063\u0061\u006c"), U8("\u006b\u0063\u0061\u006c"), U8("\u0070\u0046"), U8("\u006e\u0046"), U8("\u03bc\u0046"), U8("\u03bc\u0067"), U8("\u006d\u0067"), U8("\u006b\u0067"), U8("\u0048\u007a"), U8("\u006b\u0048\u007a"), U8("\u004d\u0048\u007a"), U8("\u0047\u0048\u007a"), U8("\u0054\u0048\u007a"), U8("\u03bc\u2113"), U8("\u006d\u2113"), U8("\u0064\u2113"), U8("\u006b\u2113"), U8("\u0066\u006d"), U8("\u006e\u006d"), U8("\u03bc\u006d"), U8("\u006d\u006d"), U8("\u0063\u006d"), U8("\u006b\u006d"), U8("\u006d\u006d\u00b2"), U8("\u0063\u006d\u00b2"), U8("\u006d\u00b2"), U8("\u006b\u006d\u00b2"), U8("\u006d\u006d\u00b3"), U8("\u0063\u006d\u00b3"), U8("\u006d\u00b3"), U8("\u006b\u006d\u00b3"), U8("\u006d\u2215\u0073"), U8("\u006d\u2215\u0073\u00b2"), U8("\u0050\u0061"), U8("\u006b\u0050\u0061"), U8("\u004d\u0050\u0061"), U8("\u0047\u0050\u0061"), U8("\u0072\u0061\u0064"), U8("\u0072\u0061\u0064\u2215\u0073"), U8("\u0072\u0061\u0064\u2215\u0073\u00b2"), U8("\u0070\u0073"), U8("\u006e\u0073"), U8("\u03bc\u0073"), U8("\u006d\u0073"), U8("\u0070\u0056"), U8("\u006e\u0056"), U8("\u03bc\u0056"), U8("\u006d\u0056"), U8("\u006b\u0056"), U8("\u004d\u0056"), U8("\u0070\u0057"), U8("\u006e\u0057"), U8("\u03bc\u0057"), U8("\u006d\u0057"), U8("\u006b\u0057"), U8("\u004d\u0057"), U8("\u006b\u03a9"), U8("\u004d\u03a9"), U8("\u0061\u002e\u006d\u002e"), U8("\u0042\u0071"), U8("\u0063\u0063"), U8("\u0063\u0064"), U8("\u0043\u2215\u006b\u0067"), U8("\u0043\u006f\u002e"), U8("\u0064\u0042"), U8("\u0047\u0079"), U8("\u0068\u0061"), U8("\u0048\u0050"), U8("\u0069\u006e"), U8("\u004b\u004b"), U8("\u004b\u004d"), U8("\u006b\u0074"), U8("\u006c\u006d"), U8("\u006c\u006e"), U8("\u006c\u006f\u0067"), U8("\u006c\u0078"), U8("\u006d\u0062"), U8("\u006d\u0069\u006c"), U8("\u006d\u006f\u006c"), U8("\u0050\u0048"), U8("\u0070\u002e\u006d\u002e"), U8("\u0050\u0050\u004d"), U8("\u0050\u0052"), U8("\u0073\u0072"), U8("\u0053\u0076"), U8("\u0057\u0062"), U8("\u0056\u2215\u006d"), U8("\u0041\u2215\u006d"), U8("\u0031\u65e5"), U8("\u0032\u65e5"), U8("\u0033\u65e5"), U8("\u0034\u65e5"), U8("\u0035\u65e5"), U8("\u0036\u65e5"), U8("\u0037\u65e5"), U8("\u0038\u65e5"), U8("\u0039\u65e5"), U8("\u0031\u0030\u65e5"), U8("\u0031\u0031\u65e5"), U8("\u0031\u0032\u65e5"), U8("\u0031\u0033\u65e5"), U8("\u0031\u0034\u65e5"), U8("\u0031\u0035\u65e5"), U8("\u0031\u0036\u65e5"), U8("\u0031\u0037\u65e5"), U8("\u0031\u0038\u65e5"), U8("\u0031\u0039\u65e5"), U8("\u0032\u0030\u65e5"), U8("\u0032\u0031\u65e5"), U8("\u0032\u0032\u65e5"), U8("\u0032\u0033\u65e5"), U8("\u0032\u0034\u65e5"), U8("\u0032\u0035\u65e5"), U8("\u0032\u0036\u65e5"), U8("\u0032\u0037\u65e5"), U8("\u0032\u0038\u65e5"), U8("\u0032\u0039\u65e5"), U8("\u0033\u0030\u65e5"), U8("\u0033\u0031\u65e5"), U8("\u0067\u0061\u006c") };

const char* lookupCompat_0xfb00_to_0xfb06_Table[] = { U8("\u0066\u0066"), U8("\u0066\u0069"), U8("\u0066\u006c"), U8("\u0066\u0066\u0069"), U8("\u0066\u0066\u006c"), U8("\u017f\u0074"), U8("\u0073\u0074") };

const char* lookupCompat_0xfb13_to_0xfb17_Table[] = { U8("\u0574\u0576"), U8("\u0574\u0565"), U8("\u0574\u056b"), U8("\u057e\u0576"), U8("\u0574\u056d") };

const char* lookupCompat_0xfb20_to_0xfb29_Table[] = { U8("\u05e2"), U8("\u05d0"), U8("\u05d3"), U8("\u05d4"), U8("\u05db"), U8("\u05dc"), U8("\u05dd"), U8("\u05e8"), U8("\u05ea"), U8("\u002b") };

const char* lookupCompat_0xfb4f_to_0xfbb1_Table[] = { U8("\u05d0\u05dc"), U8("\u0671"), U8("\u0671"), U8("\u067b"), U8("\u067b"), U8("\u067b"), U8("\u067b"), U8("\u067e"), U8("\u067e"), U8("\u067e"), U8("\u067e"), U8("\u0680"), U8("\u0680"), U8("\u0680"), U8("\u0680"), U8("\u067a"), U8("\u067a"), U8("\u067a"), U8("\u067a"), U8("\u067f"), U8("\u067f"), U8("\u067f"), U8("\u067f"), U8("\u0679"), U8("\u0679"), U8("\u0679"), U8("\u0679"), U8("\u06a4"), U8("\u06a4"), U8("\u06a4"), U8("\u06a4"), U8("\u06a6"), U8("\u06a6"), U8("\u06a6"), U8("\u06a6"), U8("\u0684"), U8("\u0684"), U8("\u0684"), U8("\u0684"), U8("\u0683"), U8("\u0683"), U8("\u0683"), U8("\u0683"), U8("\u0686"), U8("\u0686"), U8("\u0686"), U8("\u0686"), U8("\u0687"), U8("\u0687"), U8("\u0687"), U8("\u0687"), U8("\u068d"), U8("\u068d"), U8("\u068c"), U8("\u068c"), U8("\u068e"), U8("\u068e"), U8("\u0688"), U8("\u0688"), U8("\u0698"), U8("\u0698"), U8("\u0691"), U8("\u0691"), U8("\u06a9"), U8("\u06a9"), U8("\u06a9"), U8("\u06a9"), U8("\u06af"), U8("\u06af"), U8("\u06af"), U8("\u06af"), U8("\u06b3"), U8("\u06b3"), U8("\u06b3"), U8("\u06b3"), U8("\u06b1"), U8("\u06b1"), U8("\u06b1"), U8("\u06b1"), U8("\u06ba"), U8("\u06ba"), U8("\u06bb"), U8("\u06bb"), U8("\u06bb"), U8("\u06bb"), U8("\u06c0"), U8("\u06c0"), U8("\u06c1"), U8("\u06c1"), U8("\u06c1"), U8("\u06c1"), U8("\u06be"), U8("\u06be"), U8("\u06be"), U8("\u06be"), U8("\u06d2"), U8("\u06d2"), U8("\u06d3"), U8("\u06d3") };

const char* lookupCompat_0xfbd3_to_0xfd3d_Table[] = { U8("\u06ad"), U8("\u06ad"), U8("\u06ad"), U8("\u06ad"), U8("\u06c7"), U8("\u06c7"), U8("\u06c6"), U8("\u06c6"), U8("\u06c8"), U8("\u06c8"), U8("\u0677"), U8("\u06cb"), U8("\u06cb"), U8("\u06c5"), U8("\u06c5"), U8("\u06c9"), U8("\u06c9"), U8("\u06d0"), U8("\u06d0"), U8("\u06d0"), U8("\u06d0"), U8("\u0649"), U8("\u0649"), U8("\u0626\u0627"), U8("\u0626\u0627"), U8("\u0626\u06d5"), U8("\u0626\u06d5"), U8("\u0626\u0648"), U8("\u0626\u0648"), U8("\u0626\u06c7"), U8("\u0626\u06c7"), U8("\u0626\u06c6"), U8("\u0626\u06c6"), U8("\u0626\u06c8"), U8("\u0626\u06c8"), U8("\u0626\u06d0"), U8("\u0626\u06d0"), U8("\u0626\u06d0"), U8("\u0626\u0649"), U8("\u0626\u0649"), U8("\u0626\u0649"), U8("\u06cc"), U8("\u06cc"), U8("\u06cc"), U8("\u06cc"), U8("\u0626\u062c"), U8("\u0626\u062d"), U8("\u0626\u0645"), U8("\u0626\u0649"), U8("\u0626\u064a"), U8("\u0628\u062c"), U8("\u0628\u062d"), U8("\u0628\u062e"), U8("\u0628\u0645"), U8("\u0628\u0649"), U8("\u0628\u064a"), U8("\u062a\u062c"), U8("\u062a\u062d"), U8("\u062a\u062e"), U8("\u062a\u0645"), U8("\u062a\u0649"), U8("\u062a\u064a"), U8("\u062b\u062c"), U8("\u062b\u0645"), U8("\u062b\u0649"), U8("\u062b\u064a"), U8("\u062c\u062d"), U8("\u062c\u0645"), U8("\u062d\u062c"), U8("\u062d\u0645"), U8("\u062e\u062c"), U8("\u062e\u062d"), U8("\u062e\u0645"), U8("\u0633\u062c"), U8("\u0633\u062d"), U8("\u0633\u062e"), U8("\u0633\u0645"), U8("\u0635\u062d"), U8("\u0635\u0645"), U8("\u0636\u062c"), U8("\u0636\u062d"), U8("\u0636\u062e"), U8("\u0636\u0645"), U8("\u0637\u062d"), U8("\u0637\u0645"), U8("\u0638\u0645"), U8("\u0639\u062c"), U8("\u0639\u0645"), U8("\u063a\u062c"), U8("\u063a\u0645"), U8("\u0641\u062c"), U8("\u0641\u062d"), U8("\u0641\u062e"), U8("\u0641\u0645"), U8("\u0641\u0649"), U8("\u0641\u064a"), U8("\u0642\u062d"), U8("\u0642\u0645"), U8("\u0642\u0649"), U8("\u0642\u064a"), U8("\u0643\u0627"), U8("\u0643\u062c"), U8("\u0643\u062d"), U8("\u0643\u062e"), U8("\u0643\u0644"), U8("\u0643\u0645"), U8("\u0643\u0649"), U8("\u0643\u064a"), U8("\u0644\u062c"), U8("\u0644\u062d"), U8("\u0644\u062e"), U8("\u0644\u0645"), U8("\u0644\u0649"), U8("\u0644\u064a"), U8("\u0645\u062c"), U8("\u0645\u062d"), U8("\u0645\u062e"), U8("\u0645\u0645"), U8("\u0645\u0649"), U8("\u0645\u064a"), U8("\u0646\u062c"), U8("\u0646\u062d"), U8("\u0646\u062e"), U8("\u0646\u0645"), U8("\u0646\u0649"), U8("\u0646\u064a"), U8("\u0647\u062c"), U8("\u0647\u0645"), U8("\u0647\u0649"), U8("\u0647\u064a"), U8("\u064a\u062c"), U8("\u064a\u062d"), U8("\u064a\u062e"), U8("\u064a\u0645"), U8("\u064a\u0649"), U8("\u064a\u064a"), U8("\u0630\u0670"), U8("\u0631\u0670"), U8("\u0649\u0670"), U8("\u0020\u064c\u0651"), U8("\u0020\u064d\u0651"), U8("\u0020\u064e\u0651"), U8("\u0020\u064f\u0651"), U8("\u0020\u0650\u0651"), U8("\u0020\u0651\u0670"), U8("\u0626\u0631"), U8("\u0626\u0632"), U8("\u0626\u0645"), U8("\u0626\u0646"), U8("\u0626\u0649"), U8("\u0626\u064a"), U8("\u0628\u0631"), U8("\u0628\u0632"), U8("\u0628\u0645"), U8("\u0628\u0646"), U8("\u0628\u0649"), U8("\u0628\u064a"), U8("\u062a\u0631"), U8("\u062a\u0632"), U8("\u062a\u0645"), U8("\u062a\u0646"), U8("\u062a\u0649"), U8("\u062a\u064a"), U8("\u062b\u0631"), U8("\u062b\u0632"), U8("\u062b\u0645"), U8("\u062b\u0646"), U8("\u062b\u0649"), U8("\u062b\u064a"), U8("\u0641\u0649"), U8("\u0641\u064a"), U8("\u0642\u0649"), U8("\u0642\u064a"), U8("\u0643\u0627"), U8("\u0643\u0644"), U8("\u0643\u0645"), U8("\u0643\u0649"), U8("\u0643\u064a"), U8("\u0644\u0645"), U8("\u0644\u0649"), U8("\u0644\u064a"), U8("\u0645\u0627"), U8("\u0645\u0645"), U8("\u0646\u0631"), U8("\u0646\u0632"), U8("\u0646\u0645"), U8("\u0646\u0646"), U8("\u0646\u0649"), U8("\u0646\u064a"), U8("\u0649\u0670"), U8("\u064a\u0631"), U8("\u064a\u0632"), U8("\u064a\u0645"), U8("\u064a\u0646"), U8("\u064a\u0649"), U8("\u064a\u064a"), U8("\u0626\u062c"), U8("\u0626\u062d"), U8("\u0626\u062e"), U8("\u0626\u0645"), U8("\u0626\u0647"), U8("\u0628\u062c"), U8("\u0628\u062d"), U8("\u0628\u062e"), U8("\u0628\u0645"), U8("\u0628\u0647"), U8("\u062a\u062c"), U8("\u062a\u062d"), U8("\u062a\u062e"), U8("\u062a\u0645"), U8("\u062a\u0647"), U8("\u062b\u0645"), U8("\u062c\u062d"), U8("\u062c\u0645"), U8("\u062d\u062c"), U8("\u062d\u0645"), U8("\u062e\u062c"), U8("\u062e\u0645"), U8("\u0633\u062c"), U8("\u0633\u062d"), U8("\u0633\u062e"), U8("\u0633\u0645"), U8("\u0635\u062d"), U8("\u0635\u062e"), U8("\u0635\u0645"), U8("\u0636\u062c"), U8("\u0636\u062d"), U8("\u0636\u062e"), U8("\u0636\u0645"), U8("\u0637\u062d"), U8("\u0638\u0645"), U8("\u0639\u062c"), U8("\u0639\u0645"), U8("\u063a\u062c"), U8("\u063a\u0645"), U8("\u0641\u062c"), U8("\u0641\u062d"), U8("\u0641\u062e"), U8("\u0641\u0645"), U8("\u0642\u062d"), U8("\u0642\u0645"), U8("\u0643\u062c"), U8("\u0643\u062d"), U8("\u0643\u062e"), U8("\u0643\u0644"), U8("\u0643\u0645"), U8("\u0644\u062c"), U8("\u0644\u062d"), U8("\u0644\u062e"), U8("\u0644\u0645"), U8("\u0644\u0647"), U8("\u0645\u062c"), U8("\u0645\u062d"), U8("\u0645\u062e"), U8("\u0645\u0645"), U8("\u0646\u062c"), U8("\u0646\u062d"), U8("\u0646\u062e"), U8("\u0646\u0645"), U8("\u0646\u0647"), U8("\u0647\u062c"), U8("\u0647\u0645"), U8("\u0647\u0670"), U8("\u064a\u062c"), U8("\u064a\u062d"), U8("\u064a\u062e"), U8("\u064a\u0645"), U8("\u064a\u0647"), U8("\u0626\u0645"), U8("\u0626\u0647"), U8("\u0628\u0645"), U8("\u0628\u0647"), U8("\u062a\u0645"), U8("\u062a\u0647"), U8("\u062b\u0645"), U8("\u062b\u0647"), U8("\u0633\u0645"), U8("\u0633\u0647"), U8("\u0634\u0645"), U8("\u0634\u0647"), U8("\u0643\u0644"), U8("\u0643\u0645"), U8("\u0644\u0645"), U8("\u0646\u0645"), U8("\u0646\u0647"), U8("\u064a\u0645"), U8("\u064a\u0647"), U8("\u0640\u064e\u0651"), U8("\u0640\u064f\u0651"), U8("\u0640\u0650\u0651"), U8("\u0637\u0649"), U8("\u0637\u064a"), U8("\u0639\u0649"), U8("\u0639\u064a"), U8("\u063a\u0649"), U8("\u063a\u064a"), U8("\u0633\u0649"), U8("\u0633\u064a"), U8("\u0634\u0649"), U8("\u0634\u064a"), U8("\u062d\u0649"), U8("\u062d\u064a"), U8("\u062c\u0649"), U8("\u062c\u064a"), U8("\u062e\u0649"), U8("\u062e\u064a"), U8("\u0635\u0649"), U8("\u0635\u064a"), U8("\u0636\u0649"), U8("\u0636\u064a"), U8("\u0634\u062c"), U8("\u0634\u062d"), U8("\u0634\u062e"), U8("\u0634\u0645"), U8("\u0634\u0631"), U8("\u0633\u0631"), U8("\u0635\u0631"), U8("\u0636\u0631"), U8("\u0637\u0649"), U8("\u0637\u064a"), U8("\u0639\u0649"), U8("\u0639\u064a"), U8("\u063a\u0649"), U8("\u063a\u064a"), U8("\u0633\u0649"), U8("\u0633\u064a"), U8("\u0634\u0649"), U8("\u0634\u064a"), U8("\u062d\u0649"), U8("\u062d\u064a"), U8("\u062c\u0649"), U8("\u062c\u064a"), U8("\u062e\u0649"), U8("\u062e\u064a"), U8("\u0635\u0649"), U8("\u0635\u064a"), U8("\u0636\u0649"), U8("\u0636\u064a"), U8("\u0634\u062c"), U8("\u0634\u062d"), U8("\u0634\u062e"), U8("\u0634\u0645"), U8("\u0634\u0631"), U8("\u0633\u0631"), U8("\u0635\u0631"), U8("\u0636\u0631"), U8("\u0634\u062c"), U8("\u0634\u062d"), U8("\u0634\u062e"), U8("\u0634\u0645"), U8("\u0633\u0647"), U8("\u0634\u0647"), U8("\u0637\u0645"), U8("\u0633\u062c"), U8("\u0633\u062d"), U8("\u0633\u062e"), U8("\u0634\u062c"), U8("\u0634\u062d"), U8("\u0634\u062e"), U8("\u0637\u0645"), U8("\u0638\u0645"), U8("\u0627\u064b"), U8("\u0627\u064b") };

const char* lookupCompat_0xfd50_to_0xfdc7_Table[] = { U8("\u062a\u062c\u0645"), U8("\u062a\u062d\u062c"), U8("\u062a\u062d\u062c"), U8("\u062a\u062d\u0645"), U8("\u062a\u062e\u0645"), U8("\u062a\u0645\u062c"), U8("\u062a\u0645\u062d"), U8("\u062a\u0645\u062e"), U8("\u062c\u0645\u062d"), U8("\u062c\u0645\u062d"), U8("\u062d\u0645\u064a"), U8("\u062d\u0645\u0649"), U8("\u0633\u062d\u062c"), U8("\u0633\u062c\u062d"), U8("\u0633\u062c\u0649"), U8("\u0633\u0645\u062d"), U8("\u0633\u0645\u062d"), U8("\u0633\u0645\u062c"), U8("\u0633\u0645\u0645"), U8("\u0633\u0645\u0645"), U8("\u0635\u062d\u062d"), U8("\u0635\u062d\u062d"), U8("\u0635\u0645\u0645"), U8("\u0634\u062d\u0645"), U8("\u0634\u062d\u0645"), U8("\u0634\u062c\u064a"), U8("\u0634\u0645\u062e"), U8("\u0634\u0645\u062e"), U8("\u0634\u0645\u0645"), U8("\u0634\u0645\u0645"), U8("\u0636\u062d\u0649"), U8("\u0636\u062e\u0645"), U8("\u0636\u062e\u0645"), U8("\u0637\u0645\u062d"), U8("\u0637\u0645\u062d"), U8("\u0637\u0645\u0645"), U8("\u0637\u0645\u064a"), U8("\u0639\u062c\u0645"), U8("\u0639\u0645\u0645"), U8("\u0639\u0645\u0645"), U8("\u0639\u0645\u0649"), U8("\u063a\u0645\u0645"), U8("\u063a\u0645\u064a"), U8("\u063a\u0645\u0649"), U8("\u0641\u062e\u0645"), U8("\u0641\u062e\u0645"), U8("\u0642\u0645\u062d"), U8("\u0642\u0645\u0645"), U8("\u0644\u062d\u0645"), U8("\u0644\u062d\u064a"), U8("\u0644\u062d\u0649"), U8("\u0644\u062c\u062c"), U8("\u0644\u062c\u062c"), U8("\u0644\u062e\u0645"), U8("\u0644\u062e\u0645"), U8("\u0644\u0645\u062d"), U8("\u0644\u0645\u062d"), U8("\u0645\u062d\u062c"), U8("\u0645\u062d\u0645"), U8("\u0645\u062d\u064a"), U8("\u0645\u062c\u062d"), U8("\u0645\u062c\u0645"), U8("\u0645\u062e\u062c"), U8("\u0645\u062e\u0645"), U8(""), U8(""), U8("\u0645\u062c\u062e"), U8("\u0647\u0645\u062c"), U8("\u0647\u0645\u0645"), U8("\u0646\u062d\u0645"), U8("\u0646\u062d\u0649"), U8("\u0646\u062c\u0645"), U8("\u0646\u062c\u0645"), U8("\u0646\u062c\u0649"), U8("\u0646\u0645\u064a"), U8("\u0646\u0645\u0649"), U8("\u064a\u0645\u0645"), U8("\u064a\u0645\u0645"), U8("\u0628\u062e\u064a"), U8("\u062a\u062c\u064a"), U8("\u062a\u062c\u0649"), U8("\u062a\u062e\u064a"), U8("\u062a\u062e\u0649"), U8("\u062a\u0645\u064a"), U8("\u062a\u0645\u0649"), U8("\u062c\u0645\u064a"), U8("\u062c\u062d\u0649"), U8("\u062c\u0645\u0649"), U8("\u0633\u062e\u0649"), U8("\u0635\u062d\u064a"), U8("\u0634\u062d\u064a"), U8("\u0636\u062d\u064a"), U8("\u0644\u062c\u064a"), U8("\u0644\u0645\u064a"), U8("\u064a\u062d\u064a"), U8("\u064a\u062c\u064a"), U8("\u064a\u0645\u064a"), U8("\u0645\u0645\u064a"), U8("\u0642\u0645\u064a"), U8("\u0646\u062d\u064a"), U8("\u0642\u0645\u062d"), U8("\u0644\u062d\u0645"), U8("\u0639\u0645\u064a"), U8("\u0643\u0645\u064a"), U8("\u0646\u062c\u062d"), U8("\u0645\u062e\u064a"), U8("\u0644\u062c\u0645"), U8("\u0643\u0645\u0645"), U8("\u0644\u062c\u0645"), U8("\u0646\u062c\u062d"), U8("\u062c\u062d\u064a"), U8("\u062d\u062c\u064a"), U8("\u0645\u062c\u064a"), U8("\u0641\u0645\u064a"), U8("\u0628\u062d\u064a"), U8("\u0643\u0645\u0645"), U8("\u0639\u062c\u0645"), U8("\u0635\u0645\u0645"), U8("\u0633\u062e\u064a"), U8("\u0646\u062c\u064a") };

const char* lookupCompat_0xfdf0_to_0xfdfc_Table[] = { U8("\u0635\u0644\u06d2"), U8("\u0642\u0644\u06d2"), U8("\u0627\u0644\u0644\u0647"), U8("\u0627\u0643\u0628\u0631"), U8("\u0645\u062d\u0645\u062f"), U8("\u0635\u0644\u0639\u0645"), U8("\u0631\u0633\u0648\u0644"), U8("\u0639\u0644\u064a\u0647"), U8("\u0648\u0633\u0644\u0645"), U8("\u0635\u0644\u0649"), U8("\u0635\u0644\u0649\u0020\u0627\u0644\u0644\u0647\u0020\u0639\u0644\u064a\u0647\u0020\u0648\u0633\u0644\u0645"), U8("\u062c\u0644\u0020\u062c\u0644\u0627\u0644\u0647"), U8("\u0631\u06cc\u0627\u0644") };

const char* lookupCompat_0xfe10_to_0xfe19_Table[] = { U8("\u002c"), U8("\u3001"), U8("\u3002"), U8("\u003a"), U8("\u003b"), U8("\u0021"), U8("\u003f"), U8("\u3016"), U8("\u3017"), U8("\u2026") };

const char* lookupCompat_0xfe30_to_0xfe6b_Table[] = { U8("\u2025"), U8("\u2014"), U8("\u2013"), U8("\u005f"), U8("\u005f"), U8("\u0028"), U8("\u0029"), U8("\u007b"), U8("\u007d"), U8("\u3014"), U8("\u3015"), U8("\u3010"), U8("\u3011"), U8("\u300a"), U8("\u300b"), U8("\u3008"), U8("\u3009"), U8("\u300c"), U8("\u300d"), U8("\u300e"), U8("\u300f"), U8(""), U8(""), U8("\u005b"), U8("\u005d"), U8("\u203e"), U8("\u203e"), U8("\u203e"), U8("\u203e"), U8("\u005f"), U8("\u005f"), U8("\u005f"), U8("\u002c"), U8("\u3001"), U8("\u002e"), U8(""), U8("\u003b"), U8("\u003a"), U8("\u003f"), U8("\u0021"), U8("\u2014"), U8("\u0028"), U8("\u0029"), U8("\u007b"), U8("\u007d"), U8("\u3014"), U8("\u3015"), U8("\u0023"), U8("\u0026"), U8("\u002a"), U8("\u002b"), U8("\u002d"), U8("\u003c"), U8("\u003e"), U8("\u003d"), U8(""), U8("\u005c"), U8("\u0024"), U8("\u0025"), U8("\u0040") };

const char* lookupCompat_0xfe70_to_0xfefc_Table[] = { U8("\u0020\u064b"), U8("\u0640\u064b"), U8("\u0020\u064c"), U8(""), U8("\u0020\u064d"), U8(""), U8("\u0020\u064e"), U8("\u0640\u064e"), U8("\u0020\u064f"), U8("\u0640\u064f"), U8("\u0020\u0650"), U8("\u0640\u0650"), U8("\u0020\u0651"), U8("\u0640\u0651"), U8("\u0020\u0652"), U8("\u0640\u0652"), U8("\u0621"), U8("\u0622"), U8("\u0622"), U8("\u0623"), U8("\u0623"), U8("\u0624"), U8("\u0624"), U8("\u0625"), U8("\u0625"), U8("\u0626"), U8("\u0626"), U8("\u0626"), U8("\u0626"), U8("\u0627"), U8("\u0627"), U8("\u0628"), U8("\u0628"), U8("\u0628"), U8("\u0628"), U8("\u0629"), U8("\u0629"), U8("\u062a"), U8("\u062a"), U8("\u062a"), U8("\u062a"), U8("\u062b"), U8("\u062b"), U8("\u062b"), U8("\u062b"), U8("\u062c"), U8("\u062c"), U8("\u062c"), U8("\u062c"), U8("\u062d"), U8("\u062d"), U8("\u062d"), U8("\u062d"), U8("\u062e"), U8("\u062e"), U8("\u062e"), U8("\u062e"), U8("\u062f"), U8("\u062f"), U8("\u0630"), U8("\u0630"), U8("\u0631"), U8("\u0631"), U8("\u0632"), U8("\u0632"), U8("\u0633"), U8("\u0633"), U8("\u0633"), U8("\u0633"), U8("\u0634"), U8("\u0634"), U8("\u0634"), U8("\u0634"), U8("\u0635"), U8("\u0635"), U8("\u0635"), U8("\u0635"), U8("\u0636"), U8("\u0636"), U8("\u0636"), U8("\u0636"), U8("\u0637"), U8("\u0637"), U8("\u0637"), U8("\u0637"), U8("\u0638"), U8("\u0638"), U8("\u0638"), U8("\u0638"), U8("\u0639"), U8("\u0639"), U8("\u0639"), U8("\u0639"), U8("\u063a"), U8("\u063a"), U8("\u063a"), U8("\u063a"), U8("\u0641"), U8("\u0641"), U8("\u0641"), U8("\u0641"), U8("\u0642"), U8("\u0642"), U8("\u0642"), U8("\u0642"), U8("\u0643"), U8("\u0643"), U8("\u0643"), U8("\u0643"), U8("\u0644"), U8("\u0644"), U8("\u0644"), U8("\u0644"), U8("\u0645"), U8("\u0645"), U8("\u0645"), U8("\u0645"), U8("\u0646"), U8("\u0646"), U8("\u0646"), U8("\u0646"), U8("\u0647"), U8("\u0647"), U8("\u0647"), U8("\u0647"), U8("\u0648"), U8("\u0648"), U8("\u0649"), U8("\u0649"), U8("\u064a"), U8("\u064a"), U8("\u064a"), U8("\u064a"), U8("\u0644\u0622"), U8("\u0644\u0622"), U8("\u0644\u0623"), U8("\u0644\u0623"), U8("\u0644\u0625"), U8("\u0644\u0625"), U8("\u0644\u0627"), U8("\u0644\u0627") };

const char* lookupCompat_0xff01_to_0xffee_Table[] = { U8("\u0021"), U8("\u0022"), U8("\u0023"), U8("\u0024"), U8("\u0025"), U8("\u0026"), U8("\u0027"), U8("\u0028"), U8("\u0029"), U8("\u002a"), U8("\u002b"), U8("\u002c"), U8("\u002d"), U8("\u002e"), U8("\u002f"), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u003a"), U8("\u003b"), U8("\u003c"), U8("\u003d"), U8("\u003e"), U8("\u003f"), U8("\u0040"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u005b"), U8("\u005c"), U8("\u005d"), U8("\u005e"), U8("\u005f"), U8("\u0060"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u007b"), U8("\u007c"), U8("\u007d"), U8("\u007e"), U8("\u2985"), U8("\u2986"), U8("\u3002"), U8("\u300c"), U8("\u300d"), U8("\u3001"), U8("\u30fb"), U8("\u30f2"), U8("\u30a1"), U8("\u30a3"), U8("\u30a5"), U8("\u30a7"), U8("\u30a9"), U8("\u30e3"), U8("\u30e5"), U8("\u30e7"), U8("\u30c3"), U8("\u30fc"), U8("\u30a2"), U8("\u30a4"), U8("\u30a6"), U8("\u30a8"), U8("\u30aa"), U8("\u30ab"), U8("\u30ad"), U8("\u30af"), U8("\u30b1"), U8("\u30b3"), U8("\u30b5"), U8("\u30b7"), U8("\u30b9"), U8("\u30bb"), U8("\u30bd"), U8("\u30bf"), U8("\u30c1"), U8("\u30c4"), U8("\u30c6"), U8("\u30c8"), U8("\u30ca"), U8("\u30cb"), U8("\u30cc"), U8("\u30cd"), U8("\u30ce"), U8("\u30cf"), U8("\u30d2"), U8("\u30d5"), U8("\u30d8"), U8("\u30db"), U8("\u30de"), U8("\u30df"), U8("\u30e0"), U8("\u30e1"), U8("\u30e2"), U8("\u30e4"), U8("\u30e6"), U8("\u30e8"), U8("\u30e9"), U8("\u30ea"), U8("\u30eb"), U8("\u30ec"), U8("\u30ed"), U8("\u30ef"), U8("\u30f3"), U8("\u3099"), U8("\u309a"), U8("\u3164"), U8("\u3131"), U8("\u3132"), U8("\u3133"), U8("\u3134"), U8("\u3135"), U8("\u3136"), U8("\u3137"), U8("\u3138"), U8("\u3139"), U8("\u313a"), U8("\u313b"), U8("\u313c"), U8("\u313d"), U8("\u313e"), U8("\u313f"), U8("\u3140"), U8("\u3141"), U8("\u3142"), U8("\u3143"), U8("\u3144"), U8("\u3145"), U8("\u3146"), U8("\u3147"), U8("\u3148"), U8("\u3149"), U8("\u314a"), U8("\u314b"), U8("\u314c"), U8("\u314d"), U8("\u314e"), U8(""), U8(""), U8(""), U8("\u314f"), U8("\u3150"), U8("\u3151"), U8("\u3152"), U8("\u3153"), U8("\u3154"), U8(""), U8(""), U8("\u3155"), U8("\u3156"), U8("\u3157"), U8("\u3158"), U8("\u3159"), U8("\u315a"), U8(""), U8(""), U8("\u315b"), U8("\u315c"), U8("\u315d"), U8("\u315e"), U8("\u315f"), U8("\u3160"), U8(""), U8(""), U8("\u3161"), U8("\u3162"), U8("\u3163"), U8(""), U8(""), U8(""), U8("\u00a2"), U8("\u00a3"), U8("\u00ac"), U8("\u00af"), U8("\u00a6"), U8("\u00a5"), U8("\u20a9"), U8(""), U8("\u2502"), U8("\u2190"), U8("\u2191"), U8("\u2192"), U8("\u2193"), U8("\u25a0"), U8("\u25cb") };

const char* lookupCompat_0x10781_to_0x107ba_Table[] = { U8("\u02d0"), U8("\u02d1"), U8("\u00e6"), U8("\u0299"), U8("\u0253"), U8(""), U8("\u02a3"), U8("\uab66"), U8("\u02a5"), U8("\u02a4"), U8("\u0256"), U8("\u0257"), U8("\u1d91"), U8("\u0258"), U8("\u025e"), U8("\u02a9"), U8("\u0264"), U8("\u0262"), U8("\u0260"), U8("\u029b"), U8("\u0127"), U8("\u029c"), U8("\u0267"), U8("\u0284"), U8("\u02aa"), U8("\u02ab"), U8("\u026c"), U8("\U0001df04"), U8("\ua78e"), U8("\u026e"), U8("\U0001df05"), U8("\u028e"), U8("\U0001df06"), U8("\u00f8"), U8("\u0276"), U8("\u0277"), U8("\u0071"), U8("\u027a"), U8("\U0001df08"), U8("\u027d"), U8("\u027e"), U8("\u0280"), U8("\u02a8"), U8("\u02a6"), U8("\uab67"), U8("\u02a7"), U8("\u0288"), U8("\u2c71"), U8(""), U8("\u028f"), U8("\u02a1"), U8("\u02a2"), U8("\u0298"), U8("\u01c0"), U8("\u01c1"), U8("\u01c2"), U8("\U0001df0a"), U8("\U0001df1e") };

const char* lookupCompat_0x1ccd6_to_0x1ccf9_Table[] = { U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039") };

const char* lookupCompat_0x1d400_to_0x1d7ff_Table[] = { U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8(""), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8(""), U8("\u0043"), U8("\u0044"), U8(""), U8(""), U8("\u0047"), U8(""), U8(""), U8("\u004a"), U8("\u004b"), U8(""), U8(""), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8(""), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8(""), U8("\u0066"), U8(""), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8(""), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8(""), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8(""), U8(""), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8(""), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8(""), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8(""), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8(""), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8(""), U8("\u004f"), U8(""), U8(""), U8(""), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8(""), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0061"), U8("\u0062"), U8("\u0063"), U8("\u0064"), U8("\u0065"), U8("\u0066"), U8("\u0067"), U8("\u0068"), U8("\u0069"), U8("\u006a"), U8("\u006b"), U8("\u006c"), U8("\u006d"), U8("\u006e"), U8("\u006f"), U8("\u0070"), U8("\u0071"), U8("\u0072"), U8("\u0073"), U8("\u0074"), U8("\u0075"), U8("\u0076"), U8("\u0077"), U8("\u0078"), U8("\u0079"), U8("\u007a"), U8("\u0131"), U8("\u0237"), U8(""), U8(""), U8("\u0391"), U8("\u0392"), U8("\u0393"), U8("\u0394"), U8("\u0395"), U8("\u0396"), U8("\u0397"), U8("\u0398"), U8("\u0399"), U8("\u039a"), U8("\u039b"), U8("\u039c"), U8("\u039d"), U8("\u039e"), U8("\u039f"), U8("\u03a0"), U8("\u03a1"), U8("\u03f4"), U8("\u03a3"), U8("\u03a4"), U8("\u03a5"), U8("\u03a6"), U8("\u03a7"), U8("\u03a8"), U8("\u03a9"), U8("\u2207"), U8("\u03b1"), U8("\u03b2"), U8("\u03b3"), U8("\u03b4"), U8("\u03b5"), U8("\u03b6"), U8("\u03b7"), U8("\u03b8"), U8("\u03b9"), U8("\u03ba"), U8("\u03bb"), U8("\u03bc"), U8("\u03bd"), U8("\u03be"), U8("\u03bf"), U8("\u03c0"), U8("\u03c1"), U8("\u03c2"), U8("\u03c3"), U8("\u03c4"), U8("\u03c5"), U8("\u03c6"), U8("\u03c7"), U8("\u03c8"), U8("\u03c9"), U8("\u2202"), U8("\u03f5"), U8("\u03d1"), U8("\u03f0"), U8("\u03d5"), U8("\u03f1"), U8("\u03d6"), U8("\u0391"), U8("\u0392"), U8("\u0393"), U8("\u0394"), U8("\u0395"), U8("\u0396"), U8("\u0397"), U8("\u0398"), U8("\u0399"), U8("\u039a"), U8("\u039b"), U8("\u039c"), U8("\u039d"), U8("\u039e"), U8("\u039f"), U8("\u03a0"), U8("\u03a1"), U8("\u03f4"), U8("\u03a3"), U8("\u03a4"), U8("\u03a5"), U8("\u03a6"), U8("\u03a7"), U8("\u03a8"), U8("\u03a9"), U8("\u2207"), U8("\u03b1"), U8("\u03b2"), U8("\u03b3"), U8("\u03b4"), U8("\u03b5"), U8("\u03b6"), U8("\u03b7"), U8("\u03b8"), U8("\u03b9"), U8("\u03ba"), U8("\u03bb"), U8("\u03bc"), U8("\u03bd"), U8("\u03be"), U8("\u03bf"), U8("\u03c0"), U8("\u03c1"), U8("\u03c2"), U8("\u03c3"), U8("\u03c4"), U8("\u03c5"), U8("\u03c6"), U8("\u03c7"), U8("\u03c8"), U8("\u03c9"), U8("\u2202"), U8("\u03f5"), U8("\u03d1"), U8("\u03f0"), U8("\u03d5"), U8("\u03f1"), U8("\u03d6"), U8("\u0391"), U8("\u0392"), U8("\u0393"), U8("\u0394"), U8("\u0395"), U8("\u0396"), U8("\u0397"), U8("\u0398"), U8("\u0399"), U8("\u039a"), U8("\u039b"), U8("\u039c"), U8("\u039d"), U8("\u039e"), U8("\u039f"), U8("\u03a0"), U8("\u03a1"), U8("\u03f4"), U8("\u03a3"), U8("\u03a4"), U8("\u03a5"), U8("\u03a6"), U8("\u03a7"), U8("\u03a8"), U8("\u03a9"), U8("\u2207"), U8("\u03b1"), U8("\u03b2"), U8("\u03b3"), U8("\u03b4"), U8("\u03b5"), U8("\u03b6"), U8("\u03b7"), U8("\u03b8"), U8("\u03b9"), U8("\u03ba"), U8("\u03bb"), U8("\u03bc"), U8("\u03bd"), U8("\u03be"), U8("\u03bf"), U8("\u03c0"), U8("\u03c1"), U8("\u03c2"), U8("\u03c3"), U8("\u03c4"), U8("\u03c5"), U8("\u03c6"), U8("\u03c7"), U8("\u03c8"), U8("\u03c9"), U8("\u2202"), U8("\u03f5"), U8("\u03d1"), U8("\u03f0"), U8("\u03d5"), U8("\u03f1"), U8("\u03d6"), U8("\u0391"), U8("\u0392"), U8("\u0393"), U8("\u0394"), U8("\u0395"), U8("\u0396"), U8("\u0397"), U8("\u0398"), U8("\u0399"), U8("\u039a"), U8("\u039b"), U8("\u039c"), U8("\u039d"), U8("\u039e"), U8("\u039f"), U8("\u03a0"), U8("\u03a1"), U8("\u03f4"), U8("\u03a3"), U8("\u03a4"), U8("\u03a5"), U8("\u03a6"), U8("\u03a7"), U8("\u03a8"), U8("\u03a9"), U8("\u2207"), U8("\u03b1"), U8("\u03b2"), U8("\u03b3"), U8("\u03b4"), U8("\u03b5"), U8("\u03b6"), U8("\u03b7"), U8("\u03b8"), U8("\u03b9"), U8("\u03ba"), U8("\u03bb"), U8("\u03bc"), U8("\u03bd"), U8("\u03be"), U8("\u03bf"), U8("\u03c0"), U8("\u03c1"), U8("\u03c2"), U8("\u03c3"), U8("\u03c4"), U8("\u03c5"), U8("\u03c6"), U8("\u03c7"), U8("\u03c8"), U8("\u03c9"), U8("\u2202"), U8("\u03f5"), U8("\u03d1"), U8("\u03f0"), U8("\u03d5"), U8("\u03f1"), U8("\u03d6"), U8("\u0391"), U8("\u0392"), U8("\u0393"), U8("\u0394"), U8("\u0395"), U8("\u0396"), U8("\u0397"), U8("\u0398"), U8("\u0399"), U8("\u039a"), U8("\u039b"), U8("\u039c"), U8("\u039d"), U8("\u039e"), U8("\u039f"), U8("\u03a0"), U8("\u03a1"), U8("\u03f4"), U8("\u03a3"), U8("\u03a4"), U8("\u03a5"), U8("\u03a6"), U8("\u03a7"), U8("\u03a8"), U8("\u03a9"), U8("\u2207"), U8("\u03b1"), U8("\u03b2"), U8("\u03b3"), U8("\u03b4"), U8("\u03b5"), U8("\u03b6"), U8("\u03b7"), U8("\u03b8"), U8("\u03b9"), U8("\u03ba"), U8("\u03bb"), U8("\u03bc"), U8("\u03bd"), U8("\u03be"), U8("\u03bf"), U8("\u03c0"), U8("\u03c1"), U8("\u03c2"), U8("\u03c3"), U8("\u03c4"), U8("\u03c5"), U8("\u03c6"), U8("\u03c7"), U8("\u03c8"), U8("\u03c9"), U8("\u2202"), U8("\u03f5"), U8("\u03d1"), U8("\u03f0"), U8("\u03d5"), U8("\u03f1"), U8("\u03d6"), U8("\u03dc"), U8("\u03dd"), U8(""), U8(""), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039"), U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039") };

const char* lookupCompat_0x1e030_to_0x1e06d_Table[] = { U8("\u0430"), U8("\u0431"), U8("\u0432"), U8("\u0433"), U8("\u0434"), U8("\u0435"), U8("\u0436"), U8("\u0437"), U8("\u0438"), U8("\u043a"), U8("\u043b"), U8("\u043c"), U8("\u043e"), U8("\u043f"), U8("\u0440"), U8("\u0441"), U8("\u0442"), U8("\u0443"), U8("\u0444"), U8("\u0445"), U8("\u0446"), U8("\u0447"), U8("\u0448"), U8("\u044b"), U8("\u044d"), U8("\u044e"), U8("\ua689"), U8("\u04d9"), U8("\u0456"), U8("\u0458"), U8("\u04e9"), U8("\u04af"), U8("\u04cf"), U8("\u0430"), U8("\u0431"), U8("\u0432"), U8("\u0433"), U8("\u0434"), U8("\u0435"), U8("\u0436"), U8("\u0437"), U8("\u0438"), U8("\u043a"), U8("\u043b"), U8("\u043e"), U8("\u043f"), U8("\u0441"), U8("\u0443"), U8("\u0444"), U8("\u0445"), U8("\u0446"), U8("\u0447"), U8("\u0448"), U8("\u044a"), U8("\u044b"), U8("\u0491"), U8("\u0456"), U8("\u0455"), U8("\u045f"), U8("\u04ab"), U8("\ua651"), U8("\u04b1") };

const char* lookupCompat_0x1ee00_to_0x1eebb_Table[] = { U8("\u0627"), U8("\u0628"), U8("\u062c"), U8("\u062f"), U8(""), U8("\u0648"), U8("\u0632"), U8("\u062d"), U8("\u0637"), U8("\u064a"), U8("\u0643"), U8("\u0644"), U8("\u0645"), U8("\u0646"), U8("\u0633"), U8("\u0639"), U8("\u0641"), U8("\u0635"), U8("\u0642"), U8("\u0631"), U8("\u0634"), U8("\u062a"), U8("\u062b"), U8("\u062e"), U8("\u0630"), U8("\u0636"), U8("\u0638"), U8("\u063a"), U8("\u066e"), U8("\u06ba"), U8("\u06a1"), U8("\u066f"), U8(""), U8("\u0628"), U8("\u062c"), U8(""), U8("\u0647"), U8(""), U8(""), U8("\u062d"), U8(""), U8("\u064a"), U8("\u0643"), U8("\u0644"), U8("\u0645"), U8("\u0646"), U8("\u0633"), U8("\u0639"), U8("\u0641"), U8("\u0635"), U8("\u0642"), U8(""), U8("\u0634"), U8("\u062a"), U8("\u062b"), U8("\u062e"), U8(""), U8("\u0636"), U8(""), U8("\u063a"), U8(""), U8(""), U8(""), U8(""), U8(""), U8(""), U8("\u062c"), U8(""), U8(""), U8(""), U8(""), U8("\u062d"), U8(""), U8("\u064a"), U8(""), U8("\u0644"), U8(""), U8("\u0646"), U8("\u0633"), U8("\u0639"), U8(""), U8("\u0635"), U8("\u0642"), U8(""), U8("\u0634"), U8(""), U8(""), U8("\u062e"), U8(""), U8("\u0636"), U8(""), U8("\u063a"), U8(""), U8("\u06ba"), U8(""), U8("\u066f"), U8(""), U8("\u0628"), U8("\u062c"), U8(""), U8("\u0647"), U8(""), U8(""), U8("\u062d"), U8("\u0637"), U8("\u064a"), U8("\u0643"), U8(""), U8("\u0645"), U8("\u0646"), U8("\u0633"), U8("\u0639"), U8("\u0641"), U8("\u0635"), U8("\u0642"), U8(""), U8("\u0634"), U8("\u062a"), U8("\u062b"), U8("\u062e"), U8(""), U8("\u0636"), U8("\u0638"), U8("\u063a"), U8("\u066e"), U8(""), U8("\u06a1"), U8(""), U8("\u0627"), U8("\u0628"), U8("\u062c"), U8("\u062f"), U8("\u0647"), U8("\u0648"), U8("\u0632"), U8("\u062d"), U8("\u0637"), U8("\u064a"), U8(""), U8("\u0644"), U8("\u0645"), U8("\u0646"), U8("\u0633"), U8("\u0639"), U8("\u0641"), U8("\u0635"), U8("\u0642"), U8("\u0631"), U8("\u0634"), U8("\u062a"), U8("\u062b"), U8("\u062e"), U8("\u0630"), U8("\u0636"), U8("\u0638"), U8("\u063a"), U8(""), U8(""), U8(""), U8(""), U8(""), U8("\u0628"), U8("\u062c"), U8("\u062f"), U8(""), U8("\u0648"), U8("\u0632"), U8("\u062d"), U8("\u0637"), U8("\u064a"), U8(""), U8("\u0644"), U8("\u0645"), U8("\u0646"), U8("\u0633"), U8("\u0639"), U8("\u0641"), U8("\u0635"), U8("\u0642"), U8("\u0631"), U8("\u0634"), U8("\u062a"), U8("\u062b"), U8("\u062e"), U8("\u0630"), U8("\u0636"), U8("\u0638"), U8("\u063a") };

const char* lookupCompat_0x1f100_to_0x1f14f_Table[] = { U8("\u0030\u002e"), U8("\u0030\u002c"), U8("\u0031\u002c"), U8("\u0032\u002c"), U8("\u0033\u002c"), U8("\u0034\u002c"), U8("\u0035\u002c"), U8("\u0036\u002c"), U8("\u0037\u002c"), U8("\u0038\u002c"), U8("\u0039\u002c"), U8(""), U8(""), U8(""), U8(""), U8(""), U8("\u0028\u0041\u0029"), U8("\u0028\u0042\u0029"), U8("\u0028\u0043\u0029"), U8("\u0028\u0044\u0029"), U8("\u0028\u0045\u0029"), U8("\u0028\u0046\u0029"), U8("\u0028\u0047\u0029"), U8("\u0028\u0048\u0029"), U8("\u0028\u0049\u0029"), U8("\u0028\u004a\u0029"), U8("\u0028\u004b\u0029"), U8("\u0028\u004c\u0029"), U8("\u0028\u004d\u0029"), U8("\u0028\u004e\u0029"), U8("\u0028\u004f\u0029"), U8("\u0028\u0050\u0029"), U8("\u0028\u0051\u0029"), U8("\u0028\u0052\u0029"), U8("\u0028\u0053\u0029"), U8("\u0028\u0054\u0029"), U8("\u0028\u0055\u0029"), U8("\u0028\u0056\u0029"), U8("\u0028\u0057\u0029"), U8("\u0028\u0058\u0029"), U8("\u0028\u0059\u0029"), U8("\u0028\u005a\u0029"), U8("\u3014\u0053\u3015"), U8("\u0043"), U8("\u0052"), U8("\u0043\u0044"), U8("\u0057\u005a"), U8(""), U8("\u0041"), U8("\u0042"), U8("\u0043"), U8("\u0044"), U8("\u0045"), U8("\u0046"), U8("\u0047"), U8("\u0048"), U8("\u0049"), U8("\u004a"), U8("\u004b"), U8("\u004c"), U8("\u004d"), U8("\u004e"), U8("\u004f"), U8("\u0050"), U8("\u0051"), U8("\u0052"), U8("\u0053"), U8("\u0054"), U8("\u0055"), U8("\u0056"), U8("\u0057"), U8("\u0058"), U8("\u0059"), U8("\u005a"), U8("\u0048\u0056"), U8("\u004d\u0056"), U8("\u0053\u0044"), U8("\u0053\u0053"), U8("\u0050\u0050\u0056"), U8("\u0057\u0043") };

const char* lookupCompat_0x1f210_to_0x1f23b_Table[] = { U8("\u624b"), U8("\u5b57"), U8("\u53cc"), U8("\u30c7"), U8("\u4e8c"), U8("\u591a"), U8("\u89e3"), U8("\u5929"), U8("\u4ea4"), U8("\u6620"), U8("\u7121"), U8("\u6599"), U8("\u524d"), U8("\u5f8c"), U8("\u518d"), U8("\u65b0"), U8("\u521d"), U8("\u7d42"), U8("\u751f"), U8("\u8ca9"), U8("\u58f0"), U8("\u5439"), U8("\u6f14"), U8("\u6295"), U8("\u6355"), U8("\u4e00"), U8("\u4e09"), U8("\u904a"), U8("\u5de6"), U8("\u4e2d"), U8("\u53f3"), U8("\u6307"), U8("\u8d70"), U8("\u6253"), U8("\u7981"), U8("\u7a7a"), U8("\u5408"), U8("\u6e80"), U8("\u6709"), U8("\u6708"), U8("\u7533"), U8("\u5272"), U8("\u55b6"), U8("\u914d") };

const char* lookupCompat_0x1f240_to_0x1f248_Table[] = { U8("\u3014\u672c\u3015"), U8("\u3014\u4e09\u3015"), U8("\u3014\u4e8c\u3015"), U8("\u3014\u5b89\u3015"), U8("\u3014\u70b9\u3015"), U8("\u3014\u6253\u3015"), U8("\u3014\u76d7\u3015"), U8("\u3014\u52dd\u3015"), U8("\u3014\u6557\u3015") };

const char* lookupCompat_0x1fbf0_to_0x1fbf9_Table[] = { U8("\u0030"), U8("\u0031"), U8("\u0032"), U8("\u0033"), U8("\u0034"), U8("\u0035"), U8("\u0036"), U8("\u0037"), U8("\u0038"), U8("\u0039") };

SGEXTN::CoreText::String getCompatDecomp(int i){
    if(i < 0x80){return "";}
    if(i >= 0x4e00 && i <= 0x9fff){return "";}
    if(i >= 0xb80 && i <= 0xbff){return "";}
    if(i >= 0x2200 && i <= 0x22ff){
        if(i == 0x222c){return U8("\u222b\u222b");}
        if(i == 0x222d){return U8("\u222b\u222b\u222b");}
        if(i == 0x222f){return U8("\u222e\u222e");}
        if(i == 0x2230){return U8("\u222e\u222e\u222e");}
    }
    if(i >= 0x2190 && i <= 0x23ff){return "";}
    if(i >= 0x00a0 && i <= 0x0fff){
        if(i >= 0x00a0 && i <= 0x00ff){
            if(i == 0x00a0){return U8("\u0020");}
            if(i == 0x00a8){return U8("\u0020\u0308");}
            if(i == 0x00aa){return U8("\u0061");}
            if(i == 0x00af){return U8("\u0020\u0304");}
            if(i >= 0x00b2 && i <= 0x00be){return lookupCompat_0x00b2_to_0x00be_Table[i - 0x00b2];}
        }
        if(i >= 0x0100 && i <= 0x01ff){
            if(i == 0x0132){return U8("\u0049\u004a");}
            if(i == 0x0133){return U8("\u0069\u006a");}
            if(i == 0x013f){return U8("\u004c\u00b7");}
            if(i == 0x0140){return U8("\u006c\u00b7");}
            if(i == 0x0149){return U8("\u02bc\u006e");}
            if(i == 0x017f){return U8("\u0073");}
            if(i >= 0x01c4 && i <= 0x01cc){return lookupCompat_0x01c4_to_0x01cc_Table[i - 0x01c4];}
            if(i == 0x01f1){return U8("\u0044\u005a");}
            if(i == 0x01f2){return U8("\u0044\u007a");}
            if(i == 0x01f3){return U8("\u0064\u007a");}
        }
        if(i >= 0x0200 && i <= 0x02ff){
            if(i >= 0x02b0 && i <= 0x02b8){return lookupCompat_0x02b0_to_0x02b8_Table[i - 0x02b0];}
            if(i >= 0x02d8 && i <= 0x02dd){return lookupCompat_0x02d8_to_0x02dd_Table[i - 0x02d8];}
            if(i >= 0x02e0 && i <= 0x02e4){return lookupCompat_0x02e0_to_0x02e4_Table[i - 0x02e0];}
        }
        if(i >= 0x0300 && i <= 0x03ff){
            if(i == 0x037a){return U8("\u0020\u0345");}
            if(i == 0x0384){return U8("\u0020\u0301");}
            if(i == 0x03d0){return U8("\u03b2");}
            if(i == 0x03d1){return U8("\u03b8");}
            if(i == 0x03d2){return U8("\u03a5");}
            if(i == 0x03d5){return U8("\u03c6");}
            if(i == 0x03d6){return U8("\u03c0");}
            if(i == 0x03f0){return U8("\u03ba");}
            if(i == 0x03f1){return U8("\u03c1");}
            if(i == 0x03f2){return U8("\u03c2");}
            if(i == 0x03f4){return U8("\u0398");}
            if(i == 0x03f5){return U8("\u03b5");}
            if(i == 0x03f9){return U8("\u03a3");}
        }
        if(i == 0x0587){return U8("\u0565\u0582");}
        if(i >= 0x0600 && i <= 0x06ff){
            if(i == 0x0675){return U8("\u0627\u0674");}
            if(i == 0x0676){return U8("\u0648\u0674");}
            if(i == 0x0677){return U8("\u06c7\u0674");}
            if(i == 0x0678){return U8("\u064a\u0674");}
        }
        if(i >= 0x0e00 && i <= 0x0eff){
            if(i == 0x0e33){return U8("\u0e4d\u0e32");}
            if(i == 0x0eb3){return U8("\u0ecd\u0eb2");}
            if(i == 0x0edc){return U8("\u0eab\u0e99");}
            if(i == 0x0edd){return U8("\u0eab\u0ea1");}
        }
        if(i >= 0x0f00 && i <= 0x0fff){
            if(i == 0x0f0c){return U8("\u0f0b");}
            if(i == 0x0f77){return U8("\u0fb2\u0f81");}
            if(i == 0x0f79){return U8("\u0fb3\u0f81");}
        }
    }
    if(i >= 0x1000 && i <= 0x1fff){
        if(i == 0x10fc){return U8("\u10dc");}
        if(i >= 0x1d00 && i <= 0x1dff){
            if(i >= 0x1d2c && i <= 0x1d6a){return lookupCompat_0x1d2c_to_0x1d6a_Table[i - 0x1d2c];}
            if(i == 0x1d78){return U8("\u043d");}
            if(i >= 0x1d9b && i <= 0x1dbf){return lookupCompat_0x1d9b_to_0x1dbf_Table[i - 0x1d9b];}
        }
        if(i == 0x1e9a){return U8("\u0061\u02be");}
        if(i >= 0x1f00 && i <= 0x1fff){
            if(i == 0x1fbd){return U8("\u0020\u0313");}
            if(i == 0x1fbf){return U8("\u0020\u0313");}
            if(i == 0x1fc0){return U8("\u0020\u0342");}
            if(i == 0x1ffe){return U8("\u0020\u0314");}
        }
    }
    if(i >= 0x2000 && i <= 0x2fff){
        if(i >= 0x2000 && i <= 0x20ff){
            if(i >= 0x2002 && i <= 0x200a){return U8("\u0020");}
            if(i == 0x2011){return U8("\u2010");}
            if(i == 0x2017){return U8("\u0020\u0333");}
            if(i == 0x2024){return U8("\u002e");}
            if(i == 0x2025){return U8("\u002e\u002e");}
            if(i == 0x2026){return U8("\u002e\u002e\u002e");}
            if(i == 0x202f){return U8("\u0020");}
            if(i == 0x2033){return U8("\u2032\u2032");}
            if(i == 0x2034){return U8("\u2032\u2032\u2032");}
            if(i == 0x2036){return U8("\u2035\u2035");}
            if(i == 0x2037){return U8("\u2035\u2035\u2035");}
            if(i == 0x203c){return U8("\u0021\u0021");}
            if(i == 0x203e){return U8("\u0020\u0305");}
            if(i == 0x203e){return U8("\u0020\u0305");}
            if(i == 0x2047){return U8("\u003f\u003f");}
            if(i == 0x2048){return U8("\u003f\u0021");}
            if(i == 0x2049){return U8("\u0021\u003f");}
            if(i == 0x2057){return U8("\u2032\u2032\u2032\u2032");}
            if(i == 0x205f){return U8("\u0020");}
            if(i >= 0x02070 && i <= 0x209c){return lookupCompat_0x2070_to_0x209c_Table[i - 0x2070];}
            if(i == 0x20a8){return U8("\u0052\u0073");}
        }
        if(i >= 0x2100 && i <= 0x217f){return lookupCompat_0x2100_to_0x217f_Table[i - 0x2100];}
        if(i == 0x2189){return U8("\u0030\u2044\u0033");}
        if(i >= 0x2460 && i <= 0x24ea){return lookupCompat_0x2460_to_0x24ea_Table[i - 0x2460];}
        if(i >= 0x2a00 && i <= 0x2aff){
            if(i == 0x2a0c){return U8("\u222b\u222b\u222b\u222b");}
            if(i == 0x2a74){return U8("\u003a\u003a\u003d");}
            if(i == 0x2a75){return U8("\u003d\u003d");}
            if(i == 0x2a76){return U8("\u003d\u003d\u003d");}
        }
        if(i >= 0x2c00 && i <= 0x2cff){
            if(i == 0x2c7c){return U8("\u006a");}
            if(i == 0x2c7d){return U8("\u0056");}
        }
        if(i == 0x2d6f){return U8("\u2d61");}
        if(i >= 0x2e00 && i <= 0x2eff){
            if(i == 0x2e9f){return U8("\u6bcd");}
            if(i == 0x2ef3){return U8("\u9f9f");}
        }
        if(i >= 0x2f00 && i <= 0x2fd5){return lookupCompat_0x2f00_to_0x2fd5_Table[i - 0x2f00];}
    }
    if(i >= 0x3000 && i <= 0x3fff){
        if(i >= 0x3000 && i <= 0x30ff){
            if(i == 0x3000){return U8("\u0020");}
            if(i == 0x3036){return U8("\u3012");}
            if(i == 0x3038){return U8("\u5341");}
            if(i == 0x3039){return U8("\u5344");}
            if(i == 0x303a){return U8("\u5345");}
            if(i == 0x309b){return U8("\u0020\u3099");}
            if(i == 0x309c){return U8("\u0020\u309a");}
            if(i == 0x309f){return U8("\u3088\u308a");}
            if(i == 0x30ff){return U8("\u30b3\u30c8");}
        }
        if(i >= 0x3131 && i <= 0x319f){return lookupCompat_0x3131_to_0x319f_Table[i - 0x3131];}
        if(i >= 0x3200 && i <= 0x3247){return lookupCompat_0x3200_to_0x3247_Table[i - 0x3200];}
        if(i >= 0x3250 && i <= 0x33ff){return lookupCompat_0x3250_to_0x33ff_Table[i - 0x3250];}
    }
    if(i >= 0xa000 && i <= 0xafff){
        if(i >= 0xa600 && i <= 0xa7ff){
            if(i == 0xa69c){return U8("\u044a");}
            if(i == 0xa69d){return U8("\u044c");}
            if(i == 0xa770){return U8("\ua76f");}
            if(i == 0xa7f1){return U8("\u0053");}
            if(i == 0xa7f2){return U8("\u0043");}
            if(i == 0xa7f3){return U8("\u0046");}
            if(i == 0xa7f4){return U8("\u0051");}
            if(i == 0xa7f8){return U8("\u0126");}
            if(i == 0xa7f9){return U8("\u0153");}
        }
        if(i >= 0xab00 && i <= 0xabff){
            if(i == 0xab5c){return U8("\ua727");}
            if(i == 0xab5d){return U8("\uab37");}
            if(i == 0xab5e){return U8("\u026b");}
            if(i == 0xab5f){return U8("\uab52");}
            if(i == 0xab69){return U8("\u028d");}
        }
    }
    if(i >= 0xf000 && i <= 0xffff){
        if(i >= 0xfb00 && i <= 0xfb06){return lookupCompat_0xfb00_to_0xfb06_Table[i - 0xfb00];}
        if(i >= 0xfb13 && i <= 0xfb17){return lookupCompat_0xfb13_to_0xfb17_Table[i - 0xfb13];}
        if(i >= 0xfb20 && i <= 0xfb29){return lookupCompat_0xfb20_to_0xfb29_Table[i - 0xfb20];}
        if(i >= 0xfb4f && i <= 0xfbb1){return lookupCompat_0xfb4f_to_0xfbb1_Table[i - 0xfb4f];}
        if(i >= 0xfbd3 && i <= 0xfd3d){return lookupCompat_0xfbd3_to_0xfd3d_Table[i - 0xfbd3];}
        if(i >= 0xfd50 && i <= 0xfdc7){return lookupCompat_0xfd50_to_0xfdc7_Table[i - 0xfd50];}
        if(i >= 0xfdf0 && i <= 0xfdfc){return lookupCompat_0xfdf0_to_0xfdfc_Table[i - 0xfdf0];}
        if(i >= 0xfe10 && i <= 0xfe19){return lookupCompat_0xfe10_to_0xfe19_Table[i - 0xfe10];}
        if(i >= 0xfe30 && i <= 0xfe6b){return lookupCompat_0xfe30_to_0xfe6b_Table[i - 0xfe30];}
        if(i >= 0xfe70 && i <= 0xfefc){return lookupCompat_0xfe70_to_0xfefc_Table[i - 0xfe70];}
        if(i >= 0xff01 && i <= 0xffee){return lookupCompat_0xff01_to_0xffee_Table[i - 0xff01];}
    }
    if(i >= 0x10000 && i <= 0x1ffff){
        if(i >= 0x10781 && i <= 0x107ba){return lookupCompat_0x10781_to_0x107ba_Table[i - 0x10781];}
        if(i >= 0x1ccd6 && i <= 0x1ccf9){return lookupCompat_0x1ccd6_to_0x1ccf9_Table[i - 0x1ccd6];}
        if(i >= 0x1d400 && i <= 0x1d7ff){return lookupCompat_0x1d400_to_0x1d7ff_Table[i - 0x1d400];}
        if(i >= 0x1e030 && i <= 0x1e06d){return lookupCompat_0x1e030_to_0x1e06d_Table[i - 0x1e030];}
        if(i >= 0x1ee00 && i <= 0x1eebb){return lookupCompat_0x1ee00_to_0x1eebb_Table[i - 0x1ee00];}
        if(i >= 0x1f100 && i <= 0x1f14f){return lookupCompat_0x1f100_to_0x1f14f_Table[i - 0x1f100];}
        if(i >= 0x1f160 && i <= 0x1f20f){
            if(i == 0x1f16a){return U8("\u004d\u0043");}
            if(i == 0x1f16b){return U8("\u004d\u0044");}
            if(i == 0x1f16c){return U8("\u004d\u0052");}
            if(i == 0x1f190){return U8("\u0044\u004a");}
            if(i == 0x1f200){return U8("\u307b\u304b");}
            if(i == 0x1f201){return U8("\u30b3\u30b3");}
            if(i == 0x1f202){return U8("\u30b5");}
        }
        if(i >= 0x1f210 && i <= 0x1f23b){return lookupCompat_0x1f210_to_0x1f23b_Table[i - 0x1f210];}
        if(i >= 0x1f240 && i <= 0x1f248){return lookupCompat_0x1f240_to_0x1f248_Table[i - 0x1f240];}
        if(i == 0x1f250){return U8("\u5f97");}
        if(i == 0x1f251){return U8("\u53ef");}
        if(i >= 0x1fbf0 && i <= 0x1fbf9){return lookupCompat_0x1fbf0_to_0x1fbf9_Table[i - 0x1fbf0];}
    }
    return "";
}
#undef U8

int getUnicodeCombiningMarkOrder(int i){
    if(i < 0x80){return 0;}
    if(i >= 0x4e00 && i <= 0x9fff){return 0;}
    if(i == 0xbcd){return 9;}
    if(i >= 0xb80 && i <= 0xbff){return 0;}
    if(i >= 0x2190 && i <= 0x23ff){return 0;}
    if(i >= 0x300 && i < 0x370){
        if(i >= 0x300 && i < 0x315){return 230;}
        if(i == 0x315){return 232;}
        if(i >= 0x316 && i < 0x31a){return 220;}
        if(i == 0x31a){return 232;}
        if(i == 0x31b){return 216;}
        if(i >= 0x31c && i < 0x321){return 220;}
        if(i >= 0x321 && i < 0x323){return 202;}
        if(i >= 0x323 && i < 0x327){return 220;}
        if(i >= 0x327 && i < 0x329){return 202;}
        if(i >= 0x329 && i < 0x334){return 220;}
        if(i >= 0x334 && i < 0x339){return 1;}
        if(i >= 0x339 && i < 0x33d){return 220;}
        if(i >= 0x33d && i < 0x345){return 230;}
        if(i == 0x345){return 240;}
        if(i == 0x346){return 230;}
        if(i >= 0x347 && i < 0x34a){return 220;}
        if(i >= 0x34a && i < 0x34d){return 230;}
        if(i >= 0x34d && i < 0x34f){return 220;}
        if(i >= 0x350 && i < 0x353){return 230;}
        if(i >= 0x353 && i < 0x357){return 220;}
        if(i == 0x357){return 230;}
        if(i == 0x358){return 232;}
        if(i >= 0x359 && i < 0x35b){return 220;}
        if(i == 0x35b){return 230;}
        if(i == 0x35c || i == 0x35f || i == 0x362){return 233;}
        if(i >= 0x35d && i < 0x35f){return 234;}
        if(i >= 0x360 && i < 0x362){return 234;}
        if(i >= 0x363 && i < 0x370){return 230;}
        return 0;
    }
    if(i >= 0x483 && i < 0x488){return 230;}
    if(i >= 0x591 && i < 0x5c8){
        if(i == 0x591){return 220;}
        if(i >= 0x592 && i < 0x596){return 230;}
        if(i == 0x596){return 220;}
        if(i >= 0x597 && i < 0x59a){return 230;}
        if(i == 0x59a){return 222;}
        if(i == 0x59b){return 220;}
        if(i >= 0x59c && i < 0x5a2){return 230;}
        if(i >= 0x5a2 && i < 0x5a8){return 220;}
        if(i >= 0x5a8 && i < 0x5aa){return 230;}
        if(i == 0x5aa){return 220;}
        if(i >= 0x5ab && i < 0x5ad){return 230;}
        if(i == 0x5ad){return 222;}
        if(i == 0x5ae){return 228;}
        if(i == 0x5af){return 230;}
        if(i >= 0x5b0 && i < 0x5ba){return (10 + i - 0x5b0);}
        if(i >= 0x5ba && i < 0x5be){return (19 + i - 0x5ba);}
        if(i == 0x5bf){return 23;}
        if(i >= 0x5c1 && i < 0x5c3){return (24 + i - 0x5c1);}
        if(i == 0x5c4){return 230;}
        if(i == 0x5c5){return 220;}
        if(i == 0x5c7){return 18;}
        return 0;
    }
    if(i >= 0x600 && i < 0x700){
        if(i >= 0x610 && i < 0x618){return 230;}
        if(i >= 0x618 && i < 0x61b){return (30 + i - 0x618);}
        if(i >= 0x64b && i < 0x653){return (27 + i - 0x64b);}
        if(i >= 0x653 && i < 0x655){return 230;}
        if(i >= 0x655 && i < 0x657){return 220;}
        if(i >= 0x657 && i < 0x65c){return 230;}
        if(i == 0x65c || i == 0x65f){return 220;}
        if(i >= 0x65d && i < 0x65f){return 230;}
        if(i == 0x670){return 35;}
        if(i >= 0x6d6 && i < 0x6dd){return 230;}
        if(i >= 0x6df && i < 0x6e3){return 230;}
        if(i == 0x6e3){return 220;}
        if(i == 0x6e4){return 230;}
        if(i >= 0x6e7 && i < 0x6e9){return 230;}
        if(i == 0x6ea || i == 0x6ed){return 220;}
        if(i >= 0x6eb && i < 0x6ed){return 230;}
        return 0;
    }
    if(i >= 0x700 && i < 0x800){
        if(i == 0x711){return 36;}
        if(i == 0x730){return 230;}
        if(i == 0x731){return 220;}
        if(i >= 0x732 && i < 0x734){return 230;}
        if(i == 0x734){return 220;}
        if(i >= 0x735 && i < 0x737){return 230;}
        if(i >= 0x737 && i < 0x73a){return 220;}
        if(i == 0x73a){return 230;}
        if(i >= 0x73b && i < 0x73d){return 220;}
        if(i == 0x73d){return 230;}
        if(i == 0x73e){return 220;}
        if(i >= 0x73f && i < 0x742){return 230;}
        if(i >= 0x742 && i < 0x749 && i % 2 == 0){return 220;}
        if(i >= 0x742 && i < 0x749){return 230;}
        if(i >= 0x749 && i < 0x74b){return 230;}
        if(i >= 0x7eb && i < 0x7f2){return 230;}
        if(i == 0x7f2){return 220;}
        if(i == 0x7f3){return 230;}
        if(i == 0x7fd){return 220;}
        return 0;
    }
    if(i >= 0x800 && i < 0x900){
        if(i >= 0x816 && i < 0x81a){return 230;}
        if(i >= 0x81b && i < 0x824){return 230;}
        if(i >= 0x825 && i < 0x828){return 230;}
        if(i >= 0x829 && i < 0x82e){return 230;}
        if(i >= 0x859 && i < 0x85c){return 220;}
        if(i >= 0x897 && i < 0x899){return 230;}
        if(i >= 0x899 && i < 0x89c){return 220;}
        if(i >= 0x89c && i < 0x8a0){return 230;}
        if(i >= 0x8ca && i < 0x8cf){return 230;}
        if(i >= 0x8cf && i < 0x8d4){return 220;}
        if(i >= 0x8d4 && i < 0x8e2){return 230;}
        if(i == 0x8e3){return 220;}
        if(i >= 0x8e4 && i < 0x8e6){return 230;}
        if(i == 0x8e6){return 220;}
        if(i >= 0x8e7 && i < 0x8e9){return 230;}
        if(i == 0x8e9){return 220;}
        if(i >= 0x8ea && i < 0x8ed){return 230;}
        if(i >= 0x8ed && i < 0x8f0){return 220;}
        if(i >= 0x8f0 && i < 0x8f3){return (27 + i - 0x8f0);}
        if(i >= 0x8f3 && i < 0x8f6){return 230;}
        if(i == 0x8f6){return 220;}
        if(i >= 0x8f7 && i < 0x8f9){return 230;}
        if(i >= 0x8f9 && i < 0x8fb){return 220;}
        if(i >= 0x8fb && i < 0x900){return 230;}
        return 0;
    }
    if(i >= 0x900 && i < 0xa00){
        if(i == 0x93c){return 7;}
        if(i == 0x94d){return 9;}
        if(i == 0x951){return 230;}
        if(i == 0x952){return 220;}
        if(i >= 0x953 && i < 0x955){return 230;}
        if(i == 0x9bc){return 7;}
        if(i == 0x9cd){return 9;}
        if(i == 0x9fe){return 230;}
        return 0;
    }
    if(i >= 0xa00 && i < 0xb80){
        if(i == 0xa3c){return 7;}
        if(i == 0xa4d){return 9;}
        if(i == 0xabc){return 7;}
        if(i == 0xacd){return 9;}
        if(i == 0xb3c){return 7;}
        if(i == 0xb4d){return 9;}
        return 0;
    }
    if(i >= 0xc00 && i < 0xe00){
        if(i == 0xc3c){return 7;}
        if(i == 0xc4d){return 9;}
        if(i == 0xc55){return 84;}
        if(i == 0xc56){return 91;}
        if(i == 0xcbc){return 7;}
        if(i == 0xccd){return 9;}
        if(i >= 0xd3b && i < 0xd3d){return 9;}
        if(i == 0xd4d){return 9;}
        if(i == 0xdca){return 9;}
        return 0;
    }
    if(i >= 0xe00 && i < 0xf00){
        if(i >= 0xe38 && i < 0xe3a){return 103;}
        if(i == 0xe3a){return 9;}
        if(i >= 0xe48 && i < 0xe4c){return 107;}
        if(i >= 0xeb8 && i < 0xeba){return 118;}
        if(i == 0xeba){return 9;}
        if(i >= 0xec8 && i < 0xecc){return 122;}
        return 0;
    }
    if(i >= 0xf00 && i < 0x1000){
        if(i >= 0xf18 && i < 0xf1a){return 220;}
        if(i == 0xf35){return 220;}
        if(i == 0xf37){return 220;}
        if(i == 0xf39){return 216;}
        if(i == 0xf71){return 129;}
        if(i == 0xf72){return 130;}
        if(i == 0xf74){return 132;}
        if(i >= 0xf7a && i < 0xf7e){return 130;}
        if(i == 0xf80){return 130;}
        if(i >= 0xf82 && i < 0xf84){return 230;}
        if(i == 0xf84){return 9;}
        if(i >= 0xf86 && i < 0xf88){return 230;}
        if(i == 0xfc6){return 220;}
        return 0;
    }
    if(i >= 0x1000 && i < 0x1100){
        if(i == 0x1037){return 7;}
        if(i >= 0x1039 && i < 0x103b){return 9;}
        if(i == 0x108d){return 220;}
        return 0;
    }
    if(i >= 0x135d && i < 0x1360){return 230;}
    if(i >= 0x1700 && i < 0x1800){
        if(i >= 0x1714 && i < 0x1716){return 9;}
        if(i == 0x1734){return 9;}
        if(i == 0x17d2){return 9;}
        if(i == 0x17dd){return 230;}
        return 0;
    }
    if(i == 0x18a9){return 228;}
    if(i >= 0x1939 && i < 0x193c){
        if(i == 0x1939){return 222;}
        if(i == 0x193a){return 230;}
        if(i == 0x193b){return 220;}
    }
    if(i >= 0x1a00 && i < 0x1b00){
        if(i == 0x1a17){return 230;}
        if(i == 0x1a18){return 220;}
        if(i == 0x1a60){return 9;}
        if(i >= 0x1a75 && i < 0x1a7d){return 230;}
        if(i == 0x1a7f){return 220;}
        if(i >= 0x1ab0 && i < 0x1ab5){return 230;}
        if(i >= 0x1ab5 && i < 0x1abb){return 220;}
        if(i >= 0x1abb && i < 0x1abd){return 230;}
        if(i == 0x1abd){return 220;}
        if(i >= 0x1abf && i < 0x1ac1){return 220;}
        if(i >= 0x1ac1 && i < 0x1ac3){return 230;}
        if(i >= 0x1ac3 && i < 0x1ac5){return 220;}
        if(i >= 0x1ac5 && i < 0x1aca){return 230;}
        if(i == 0x1aca){return 220;}
        if(i >= 0x1acb && i < 0x1add){return 230;}
        if(i == 0x1add){return 220;}
        if(i >= 0x1ae0 && i < 0x1ae6){return 230;}
        if(i == 0x1ae6){return 220;}
        if(i >= 0x1ae7 && i < 0x1aeb){return 230;}
        if(i == 0x1aeb){return 234;}
        return 0;
    }
    if(i >= 0x1b00 && i < 0x1c00){
        if(i == 0x1b34){return 7;}
        if(i == 0x1b44){return 9;}
        if(i == 0x1b6b){return 230;}
        if(i == 0x1b6c){return 220;}
        if(i >= 0x1b6d && i < 0x1b74){return 230;}
        if(i >= 0x1baa && i < 0x1bac){return 9;}
        if(i == 0x1be6){return 7;}
        if(i >= 0x1bf2 && i < 0x1bf4){return 9;}
        return 0;
    }
    if(i >= 0x1c00 && i < 0x1d00){
        if(i == 0x1c37){return 7;}
        if(i >= 0x1cd0 && i < 0x1cd3){return 230;}
        if(i == 0x1cd4){return 1;}
        if(i >= 0x1cd5 && i < 0x1cda){return 220;}
        if(i >= 0x1cda && i < 0x1cdc){return 230;}
        if(i >= 0x1cdc && i < 0x1ce0){return 220;}
        if(i == 0x1ce0){return 230;}
        if(i >= 0x1ce2 && i < 0x1ce9){return 1;}
        if(i == 0x1ced){return 220;}
        if(i == 0x1cf4){return 230;}
        if(i >= 0x1cf8 && i < 0x1cfa){return 230;}
        return 0;
    }
    if(i >= 0x1d00 && i < 0x1e00){
        if(i >= 0x1dc0 && i < 0x1dc2){return 230;}
        if(i == 0x1dc2){return 220;}
        if(i >= 0x1dc3 && i < 0x1dca){return 230;}
        if(i == 0x1dca){return 220;}
        if(i >= 0x1dcb && i < 0x1dcd){return 230;}
        if(i == 0x1dcd){return 234;}
        if(i == 0x1dce){return 214;}
        if(i == 0x1dcf){return 220;}
        if(i == 0x1dd0){return 202;}
        if(i >= 0x1dd1 && i < 0x1df6){return 230;}
        if(i == 0x1df6){return 232;}
        if(i >= 0x1df7 && i < 0x1df9){return 228;}
        if(i == 0x1df9){return 220;}
        if(i == 0x1dfa){return 218;}
        if(i == 0x1dfb){return 230;}
        if(i == 0x1dfc){return 233;}
        if(i == 0x1dfd){return 220;}
        if(i == 0x1dfe){return 230;}
        if(i == 0x1dff){return 220;}
        return 0;
    }
    if(i >= 0x20d0 && i < 0x2100){
        if(i >= 0x20d0 && i < 0x20d2){return 230;}
        if(i >= 0x20d2 && i < 0x20d4){return 1;}
        if(i >= 0x20d4 && i < 0x20d8){return 230;}
        if(i >= 0x20d8 && i < 0x20db){return 1;}
        if(i >= 0x20db && i < 0x20dd){return 230;}
        if(i == 0x20e1){return 230;}
        if(i >= 0x20e5 && i < 0x20e7){return 1;}
        if(i == 0x20e7){return 230;}
        if(i == 0x20e8){return 220;}
        if(i == 0x20e9){return 230;}
        if(i >= 0x20ea && i < 0x20ec){return 1;}
        if(i >= 0x20ec && i < 0x20f0){return 220;}
        if(i == 0x20f0){return 230;}
        return 0;
    }
    if(i >= 0x2cef && i < 0x2cf2){return 230;}
    if(i == 0x2d7f){return 9;}
    if(i >= 0x2de0 && i < 0x2e00){return 230;}
    if(i >= 0x3000 && i < 0x3100){
        if(i == 0x302a){return 218;}
        if(i == 0x302b){return 228;}
        if(i == 0x302c){return 232;}
        if(i == 0x302d){return 222;}
        if(i >= 0x302e && i < 0x3030){return 224;}
        if(i >= 0x3099 && i < 0x309b){return 8;}
        return 0;
    }
    if(i >= 0xa600 && i < 0xac00){
        if(i == 0xa66f){return 230;}
        if(i >= 0xa674 && i < 0xa67e){return 230;}
        if(i >= 0xa69e && i < 0xa6a0){return 230;}
        if(i >= 0xa6f0 && i < 0xa6f2){return 230;}
        if(i == 0xa806){return 9;}
        if(i == 0xa82c){return 9;}
        if(i == 0xa8c4){return 9;}
        if(i >= 0xa8e0 && i < 0xa8f2){return 230;}
        if(i >= 0xa92b && i < 0xa92e){return 220;}
        if(i == 0xa953){return 9;}
        if(i == 0xa9b3){return 7;}
        if(i == 0xa9c0){return 9;}
        if(i == 0xaab0){return 230;}
        if(i >= 0xaab2 && i < 0xaab4){return 230;}
        if(i == 0xaab4){return 220;}
        if(i >= 0xaab7 && i < 0xaab9){return 230;}
        if(i >= 0xaabe && i < 0xaac0){return 230;}
        if(i == 0xaac1){return 230;}
        if(i == 0xaaf6){return 9;}
        if(i == 0xabed){return 9;}
        return 0;
    }
    if(i >= 0xfb00 && i < 0xff00){
        if(i == 0xfb1e){return 26;}
        if(i >= 0xfe20 && i < 0xfe27){return 230;}
        if(i >= 0xfe27 && i < 0xfe2e){return 220;}
        if(i >= 0xfe2e && i < 0xfe30){return 230;}
        return 0;
    }
    if(i >= 0x10000 && i < 0x11000){
        if(i == 0x101fd){return 220;}
        if(i == 0x102e0){return 220;}
        if(i >= 0x10376 && i < 0x1037b){return 230;}
        if(i == 0x10a0d){return 220;}
        if(i == 0x10a0f){return 230;}
        if(i == 0x10a38){return 230;}
        if(i == 0x10a39){return 1;}
        if(i == 0x10a3a){return 220;}
        if(i == 0x10a3f){return 9;}
        if(i == 0x10ae5){return 230;}
        if(i == 0x10ae6){return 220;}
        if(i >= 0x10d24 && i < 0x10d28){return 230;}
        if(i >= 0x10d69 && i < 0x10d6e){return 230;}
        if(i >= 0x10eab && i < 0x10ead){return 230;}
        if(i >= 0x10efa && i < 0x10efc){return 220;}
        if(i >= 0x10efd && i < 0x10f00){return 220;}
        if(i >= 0x10f46 && i < 0x10f48){return 220;}
        if(i >= 0x10f48 && i < 0x10f4b){return 230;}
        if(i == 0x10f4b){return 220;}
        if(i == 0x10f4c){return 230;}
        if(i >= 0x10f4d && i < 0x10f51){return 220;}
        if(i == 0x10f82){return 230;}
        if(i == 0x10f83){return 220;}
        if(i == 0x10f84){return 230;}
        if(i == 0x10f85){return 220;}
        return 0;
    }
    if(i >= 0x11000 && i < 0x12000){
        if(i == 0x11046){return 9;}
        if(i == 0x11070){return 9;}
        if(i == 0x1107f){return 9;}
        if(i == 0x110b9){return 9;}
        if(i == 0x110ba){return 7;}
        if(i >= 0x11100 && i < 0x11103){return 230;}
        if(i >= 0x11133 && i < 0x11135){return 9;}
        if(i == 0x11173){return 7;}
        if(i == 0x111c0){return 9;}
        if(i == 0x111ca){return 7;}
        if(i == 0x11235){return 9;}
        if(i == 0x11236){return 7;}
        if(i == 0x112e9){return 7;}
        if(i == 0x112ea){return 9;}
        if(i >= 0x1133b && i < 0x1133d){return 7;}
        if(i == 0x1134d){return 9;}
        if(i >= 0x11366 && i < 0x1136d){return 230;}
        if(i >= 0x11370 && i < 0x11375){return 230;}
        if(i >= 0x113ce && i < 0x113d1){return 9;}
        if(i == 0x11442){return 9;}
        if(i == 0x11446){return 7;}
        if(i == 0x1145e){return 230;}
        if(i == 0x114c2){return 9;}
        if(i == 0x114c3){return 7;}
        if(i == 0x115bf){return 9;}
        if(i == 0x115c0){return 7;}
        if(i == 0x1163f){return 9;}
        if(i == 0x116b6){return 9;}
        if(i == 0x116b7){return 7;}
        if(i == 0x1172b){return 9;}
        if(i == 0x11839){return 9;}
        if(i == 0x1183a){return 7;}
        if(i >= 0x1193d && i < 0x1193f){return 9;}
        if(i == 0x11943){return 7;}
        if(i == 0x119e0){return 9;}
        if(i == 0x11a34){return 9;}
        if(i == 0x11a47){return 9;}
        if(i == 0x11a99){return 9;}
        if(i == 0x11c3f){return 9;}
        if(i == 0x11d42){return 7;}
        if(i >= 0x11d44 && i < 0x11d46){return 9;}
        if(i == 0x11d97){return 9;}
        if(i >= 0x11f41 && i < 0x11f43){return 9;}
        return 0;
    }
    if(i >= 0x16000 && i < 0x17000){
        if(i == 0x1612f){return 9;}
        if(i >= 0x16af0 && i < 0x16af5){return 1;}
        if(i >= 0x16b30 && i < 0x16b37){return 230;}
        if(i >= 0x16ff0 && i < 0x16ff2){return 6;}
        return 0;
    }
    if(i == 0x1bc9e){return 1;}
    if(i >= 0x1d000 && i < 0x1e000){
        if(i >= 0x1d165 && i < 0x1d167){return 216;}
        if(i >= 0x1d167 && i < 0x1d16a){return 1;}
        if(i == 0x1d16d){return 226;}
        if(i >= 0x1d16e && i < 0x1d173){return 216;}
        if(i >= 0x1d17b && i < 0x1d183){return 220;}
        if(i >= 0x1d185 && i < 0x1d18a){return 230;}
        if(i >= 0x1d18a && i < 0x1d18c){return 220;}
        if(i >= 0x1d1aa && i < 0x1d1ae){return 230;}
        if(i >= 0x1d242 && i < 0x1d245){return 230;}
        return 0;
    }
    if(i >= 0x1e000 && i < 0x1f000){
        if(i >= 0x1e000 && i < 0x1e007){return 230;}
        if(i >= 0x1e008 && i < 0x1e019){return 230;}
        if(i >= 0x1e01b && i < 0x1e022){return 230;}
        if(i >= 0x1e023 && i < 0x1e025){return 230;}
        if(i >= 0x1e026 && i < 0x1e02b){return 230;}
        if(i == 0x1e08f){return 230;}
        if(i >= 0x1e130 && i < 0x1e137){return 230;}
        if(i == 0x1e2ae){return 230;}
        if(i >= 0x1e2ec && i < 0x1e2f0){return 230;}
        if(i >= 0x1e4ec && i < 0x1e4ee){return 232;}
        if(i == 0x1e4ee){return 220;}
        if(i == 0x1e4ef){return 230;}
        if(i == 0x1e5ee){return 230;}
        if(i == 0x1e5ef){return 220;}
        if(i == 0x1e6e3){return 230;}
        if(i == 0x1e6e6){return 230;}
        if(i >= 0x1e6ee && i < 0x1e6f0){return 230;}
        if(i == 0x1e6f5){return 230;}
        if(i >= 0x1e8d0 && i < 0x1e8d7){return 220;}
        if(i >= 0x1e944 && i < 0x1e94a){return 230;}
        if(i == 0x1e94a){return 7;}
        return 0;
    }
    return 0;
}

int getUnicodeRecompositionMapping(int first, int second){
    if(first >= 0xb80 && first <= 0xbff){
        if(first == 0xb92 && second == 0xbd7){return 0xb94;}
        if(first == 0xbc6 && second == 0xbbe){return 0xbca;}
        if(first == 0xbc6 && second == 0xbd7){return 0xbcc;}
        if(first == 0xbc7 && second == 0xbbe){return 0xbcb;}
        return -1;
    }
    if(first >= 0x2200 && first <= 0x22ff && second == 0x338){
        if(first == 0x2203){return 0x2204;}
        if(first == 0x2208){return 0x2209;}
        if(first == 0x220b){return 0x220c;}
        if(first == 0x2223){return 0x2224;}
        if(first == 0x2225){return 0x2226;}
        if(first == 0x223c){return 0x2241;}
        if(first == 0x2243){return 0x2244;}
        if(first == 0x2245){return 0x2247;}
        if(first == 0x2248){return 0x2249;}
        if(first == 0x224d){return 0x226d;}
        if(first == 0x2261){return 0x2262;}
        if(first == 0x2264){return 0x2270;}
        if(first == 0x2265){return 0x2271;}
        if(first == 0x2272){return 0x2274;}
        if(first == 0x2273){return 0x2275;}
        if(first == 0x2276){return 0x2278;}
        if(first == 0x2277){return 0x2279;}
        if(first == 0x227a){return 0x2280;}
        if(first == 0x227b){return 0x2281;}
        if(first == 0x227c){return 0x22e0;}
        if(first == 0x227d){return 0x22e1;}
        if(first == 0x2282){return 0x2284;}
        if(first == 0x2283){return 0x2285;}
        if(first == 0x2286){return 0x2288;}
        if(first == 0x2287){return 0x2289;}
        if(first == 0x2291){return 0x22e2;}
        if(first == 0x2292){return 0x22e3;}
        if(first == 0x22a2){return 0x22ac;}
        if(first == 0x22a8){return 0x22ad;}
        if(first == 0x22a9){return 0x22ae;}
        if(first == 0x22ab){return 0x22af;}
        if(first == 0x22b2){return 0x22ea;}
        if(first == 0x22b3){return 0x22eb;}
        if(first == 0x22b4){return 0x22ec;}
        if(first == 0x22b5){return 0x22ed;}
        return -1;
    }
    if(first >= 0x1100 && first < 0x1113 && second >= 0x1161 && second < 0x1176){return (0xac00 + 28 * (21 * (first - 0x1100) + (second - 0x1161)));}
    if(first >= 0xac00 && first < 0xd7a4 && (first - 0xac00) % 28 == 0 && second >= 0x11a8 && second < 0x11c3){return (first + (second - 0x11a7));}
    if(first >= 0x0000 && first <= 0x00ff){
        if(first >= 0x3c && first < 0x80){
            if(first >= 0x003c && first <= 0x003e && second == 0x0338){
                if(first == 0x003c){return 0x226e;}
                if(first == 0x003d){return 0x2260;}
                if(first == 0x003e){return 0x226f;}
            }
            if(first >= 0x0041 && first <= 0x005a){
                if(first >= 0x0041 && first <= 0x0047){
                    if(first == 0x0041){
                        if(second == 0x0300){return 0x00c0;}
                        if(second == 0x0301){return 0x00c1;}
                        if(second == 0x0302){return 0x00c2;}
                        if(second == 0x0303){return 0x00c3;}
                        if(second == 0x0304){return 0x0100;}
                        if(second == 0x0306){return 0x0102;}
                        if(second == 0x0307){return 0x0226;}
                        if(second == 0x0308){return 0x00c4;}
                        if(second == 0x0309){return 0x1ea2;}
                        if(second == 0x030a){return 0x00c5;}
                        if(second == 0x030c){return 0x01cd;}
                        if(second == 0x030f){return 0x0200;}
                        if(second == 0x0311){return 0x0202;}
                        if(second == 0x0323){return 0x1ea0;}
                        if(second == 0x0325){return 0x1e00;}
                        if(second == 0x0328){return 0x0104;}
                    }
                    if(first == 0x0042){
                        if(second == 0x0307){return 0x1e02;}
                        if(second == 0x0323){return 0x1e04;}
                        if(second == 0x0331){return 0x1e06;}
                    }
                    if(first == 0x0043){
                        if(second == 0x0301){return 0x0106;}
                        if(second == 0x0302){return 0x0108;}
                        if(second == 0x0307){return 0x010a;}
                        if(second == 0x030c){return 0x010c;}
                        if(second == 0x0327){return 0x00c7;}
                    }
                    if(first == 0x0044){
                        if(second == 0x0307){return 0x1e0a;}
                        if(second == 0x030c){return 0x010e;}
                        if(second == 0x0323){return 0x1e0c;}
                        if(second == 0x0327){return 0x1e10;}
                        if(second == 0x032d){return 0x1e12;}
                        if(second == 0x0331){return 0x1e0e;}
                    }
                    if(first == 0x0045){
                        if(second == 0x0300){return 0x00c8;}
                        if(second == 0x0301){return 0x00c9;}
                        if(second == 0x0302){return 0x00ca;}
                        if(second == 0x0303){return 0x1ebc;}
                        if(second == 0x0304){return 0x0112;}
                        if(second == 0x0306){return 0x0114;}
                        if(second == 0x0307){return 0x0116;}
                        if(second == 0x0308){return 0x00cb;}
                        if(second == 0x0309){return 0x1eba;}
                        if(second == 0x030c){return 0x011a;}
                        if(second == 0x030f){return 0x0204;}
                        if(second == 0x0311){return 0x0206;}
                        if(second == 0x0323){return 0x1eb8;}
                        if(second == 0x0327){return 0x0228;}
                        if(second == 0x0328){return 0x0118;}
                        if(second == 0x032d){return 0x1e18;}
                        if(second == 0x0330){return 0x1e1a;}
                    }
                    if(first == 0x0046 && second == 0x0307){return 0x1e1e;}
                    if(first == 0x0047){
                        if(second == 0x0301){return 0x01f4;}
                        if(second == 0x0302){return 0x011c;}
                        if(second == 0x0304){return 0x1e20;}
                        if(second == 0x0306){return 0x011e;}
                        if(second == 0x0307){return 0x0120;}
                        if(second == 0x030c){return 0x01e6;}
                        if(second == 0x0327){return 0x0122;}
                    }
                }
                if(first >= 0x0048 && first <= 0x004e){
                    if(first == 0x0048){
                        if(second == 0x0302){return 0x0124;}
                        if(second == 0x0307){return 0x1e22;}
                        if(second == 0x0308){return 0x1e26;}
                        if(second == 0x030c){return 0x021e;}
                        if(second == 0x0323){return 0x1e24;}
                        if(second == 0x0327){return 0x1e28;}
                        if(second == 0x032e){return 0x1e2a;}
                    }
                    if(first == 0x0049){
                        if(second == 0x0300){return 0x00cc;}
                        if(second == 0x0301){return 0x00cd;}
                        if(second == 0x0302){return 0x00ce;}
                        if(second == 0x0303){return 0x0128;}
                        if(second == 0x0304){return 0x012a;}
                        if(second == 0x0306){return 0x012c;}
                        if(second == 0x0307){return 0x0130;}
                        if(second == 0x0308){return 0x00cf;}
                        if(second == 0x0309){return 0x1ec8;}
                        if(second == 0x030c){return 0x01cf;}
                        if(second == 0x030f){return 0x0208;}
                        if(second == 0x0311){return 0x020a;}
                        if(second == 0x0323){return 0x1eca;}
                        if(second == 0x0328){return 0x012e;}
                        if(second == 0x0330){return 0x1e2c;}
                    }
                    if(first == 0x004a && second == 0x0302){return 0x0134;}
                    if(first == 0x004b){
                        if(second == 0x0301){return 0x1e30;}
                        if(second == 0x030c){return 0x01e8;}
                        if(second == 0x0323){return 0x1e32;}
                        if(second == 0x0327){return 0x0136;}
                        if(second == 0x0331){return 0x1e34;}
                    }
                    if(first == 0x004c){
                        if(second == 0x0301){return 0x0139;}
                        if(second == 0x030c){return 0x013d;}
                        if(second == 0x0323){return 0x1e36;}
                        if(second == 0x0327){return 0x013b;}
                        if(second == 0x032d){return 0x1e3c;}
                        if(second == 0x0331){return 0x1e3a;}
                    }
                    if(first == 0x004d){
                        if(second == 0x0301){return 0x1e3e;}
                        if(second == 0x0307){return 0x1e40;}
                        if(second == 0x0323){return 0x1e42;}
                    }
                    if(first == 0x004e){
                        if(second == 0x0300){return 0x01f8;}
                        if(second == 0x0301){return 0x0143;}
                        if(second == 0x0303){return 0x00d1;}
                        if(second == 0x0307){return 0x1e44;}
                        if(second == 0x030c){return 0x0147;}
                        if(second == 0x0323){return 0x1e46;}
                        if(second == 0x0327){return 0x0145;}
                        if(second == 0x032d){return 0x1e4a;}
                        if(second == 0x0331){return 0x1e48;}
                    }
                }
                if(first >= 0x004f && first <= 0x0054){
                    if(first == 0x004f){
                        if(second == 0x0300){return 0x00d2;}
                        if(second == 0x0301){return 0x00d3;}
                        if(second == 0x0302){return 0x00d4;}
                        if(second == 0x0303){return 0x00d5;}
                        if(second == 0x0304){return 0x014c;}
                        if(second == 0x0306){return 0x014e;}
                        if(second == 0x0307){return 0x022e;}
                        if(second == 0x0308){return 0x00d6;}
                        if(second == 0x0309){return 0x1ece;}
                        if(second == 0x030b){return 0x0150;}
                        if(second == 0x030c){return 0x01d1;}
                        if(second == 0x030f){return 0x020c;}
                        if(second == 0x0311){return 0x020e;}
                        if(second == 0x031b){return 0x01a0;}
                        if(second == 0x0323){return 0x1ecc;}
                        if(second == 0x0328){return 0x01ea;}
                    }
                    if(first == 0x0050){
                        if(second == 0x0301){return 0x1e54;}
                        if(second == 0x0307){return 0x1e56;}
                    }
                    if(first == 0x0052){
                        if(second == 0x0301){return 0x0154;}
                        if(second == 0x0307){return 0x1e58;}
                        if(second == 0x030c){return 0x0158;}
                        if(second == 0x030f){return 0x0210;}
                        if(second == 0x0311){return 0x0212;}
                        if(second == 0x0323){return 0x1e5a;}
                        if(second == 0x0327){return 0x0156;}
                        if(second == 0x0331){return 0x1e5e;}
                    }
                    if(first == 0x0053){
                        if(second == 0x0301){return 0x015a;}
                        if(second == 0x0302){return 0x015c;}
                        if(second == 0x0307){return 0x1e60;}
                        if(second == 0x030c){return 0x0160;}
                        if(second == 0x0323){return 0x1e62;}
                        if(second == 0x0326){return 0x0218;}
                        if(second == 0x0327){return 0x015e;}
                    }
                    if(first == 0x0054){
                        if(second == 0x0307){return 0x1e6a;}
                        if(second == 0x030c){return 0x0164;}
                        if(second == 0x0323){return 0x1e6c;}
                        if(second == 0x0326){return 0x021a;}
                        if(second == 0x0327){return 0x0162;}
                        if(second == 0x032d){return 0x1e70;}
                        if(second == 0x0331){return 0x1e6e;}
                    }
                }
                if(first >= 0x0055 && first <= 0x005a){
                    if(first == 0x0055){
                        if(second == 0x0300){return 0x00d9;}
                        if(second == 0x0301){return 0x00da;}
                        if(second == 0x0302){return 0x00db;}
                        if(second == 0x0303){return 0x0168;}
                        if(second == 0x0304){return 0x016a;}
                        if(second == 0x0306){return 0x016c;}
                        if(second == 0x0308){return 0x00dc;}
                        if(second == 0x0309){return 0x1ee6;}
                        if(second == 0x030a){return 0x016e;}
                        if(second == 0x030b){return 0x0170;}
                        if(second == 0x030c){return 0x01d3;}
                        if(second == 0x030f){return 0x0214;}
                        if(second == 0x0311){return 0x0216;}
                        if(second == 0x031b){return 0x01af;}
                        if(second == 0x0323){return 0x1ee4;}
                        if(second == 0x0324){return 0x1e72;}
                        if(second == 0x0328){return 0x0172;}
                        if(second == 0x032d){return 0x1e76;}
                        if(second == 0x0330){return 0x1e74;}
                    }
                    if(first == 0x0056){
                        if(second == 0x0303){return 0x1e7c;}
                        if(second == 0x0323){return 0x1e7e;}
                    }
                    if(first == 0x0057){
                        if(second == 0x0300){return 0x1e80;}
                        if(second == 0x0301){return 0x1e82;}
                        if(second == 0x0302){return 0x0174;}
                        if(second == 0x0307){return 0x1e86;}
                        if(second == 0x0308){return 0x1e84;}
                        if(second == 0x0323){return 0x1e88;}
                    }
                    if(first == 0x0058){
                        if(second == 0x0307){return 0x1e8a;}
                        if(second == 0x0308){return 0x1e8c;}
                    }
                    if(first == 0x0059){
                        if(second == 0x0300){return 0x1ef2;}
                        if(second == 0x0301){return 0x00dd;}
                        if(second == 0x0302){return 0x0176;}
                        if(second == 0x0303){return 0x1ef8;}
                        if(second == 0x0304){return 0x0232;}
                        if(second == 0x0307){return 0x1e8e;}
                        if(second == 0x0308){return 0x0178;}
                        if(second == 0x0309){return 0x1ef6;}
                        if(second == 0x0323){return 0x1ef4;}
                    }
                    if(first == 0x005a){
                        if(second == 0x0301){return 0x0179;}
                        if(second == 0x0302){return 0x1e90;}
                        if(second == 0x0307){return 0x017b;}
                        if(second == 0x030c){return 0x017d;}
                        if(second == 0x0323){return 0x1e92;}
                        if(second == 0x0331){return 0x1e94;}
                    }
                }
            }
            if(first >= 0x0061 && first <= 0x007a){
                if(first >= 0x0061 && first <= 0x0067){
                    if(first == 0x0061){
                        if(second == 0x0300){return 0x00e0;}
                        if(second == 0x0301){return 0x00e1;}
                        if(second == 0x0302){return 0x00e2;}
                        if(second == 0x0303){return 0x00e3;}
                        if(second == 0x0304){return 0x0101;}
                        if(second == 0x0306){return 0x0103;}
                        if(second == 0x0307){return 0x0227;}
                        if(second == 0x0308){return 0x00e4;}
                        if(second == 0x0309){return 0x1ea3;}
                        if(second == 0x030a){return 0x00e5;}
                        if(second == 0x030c){return 0x01ce;}
                        if(second == 0x030f){return 0x0201;}
                        if(second == 0x0311){return 0x0203;}
                        if(second == 0x0323){return 0x1ea1;}
                        if(second == 0x0325){return 0x1e01;}
                        if(second == 0x0328){return 0x0105;}
                    }
                    if(first == 0x0062){
                        if(second == 0x0307){return 0x1e03;}
                        if(second == 0x0323){return 0x1e05;}
                        if(second == 0x0331){return 0x1e07;}
                    }
                    if(first == 0x0063){
                        if(second == 0x0301){return 0x0107;}
                        if(second == 0x0302){return 0x0109;}
                        if(second == 0x0307){return 0x010b;}
                        if(second == 0x030c){return 0x010d;}
                        if(second == 0x0327){return 0x00e7;}
                    }
                    if(first == 0x0064){
                        if(second == 0x0307){return 0x1e0b;}
                        if(second == 0x030c){return 0x010f;}
                        if(second == 0x0323){return 0x1e0d;}
                        if(second == 0x0327){return 0x1e11;}
                        if(second == 0x032d){return 0x1e13;}
                        if(second == 0x0331){return 0x1e0f;}
                    }
                    if(first == 0x0065){
                        if(second == 0x0300){return 0x00e8;}
                        if(second == 0x0301){return 0x00e9;}
                        if(second == 0x0302){return 0x00ea;}
                        if(second == 0x0303){return 0x1ebd;}
                        if(second == 0x0304){return 0x0113;}
                        if(second == 0x0306){return 0x0115;}
                        if(second == 0x0307){return 0x0117;}
                        if(second == 0x0308){return 0x00eb;}
                        if(second == 0x0309){return 0x1ebb;}
                        if(second == 0x030c){return 0x011b;}
                        if(second == 0x030f){return 0x0205;}
                        if(second == 0x0311){return 0x0207;}
                        if(second == 0x0323){return 0x1eb9;}
                        if(second == 0x0327){return 0x0229;}
                        if(second == 0x0328){return 0x0119;}
                        if(second == 0x032d){return 0x1e19;}
                        if(second == 0x0330){return 0x1e1b;}
                    }
                    if(first == 0x0066 && second == 0x0307){return 0x1e1f;}
                    if(first == 0x0067){
                        if(second == 0x0301){return 0x01f5;}
                        if(second == 0x0302){return 0x011d;}
                        if(second == 0x0304){return 0x1e21;}
                        if(second == 0x0306){return 0x011f;}
                        if(second == 0x0307){return 0x0121;}
                        if(second == 0x030c){return 0x01e7;}
                        if(second == 0x0327){return 0x0123;}
                    }
                }
                if(first >= 0x0068 && first <= 0x006e){
                    if(first == 0x0068){
                        if(second == 0x0302){return 0x0125;}
                        if(second == 0x0307){return 0x1e23;}
                        if(second == 0x0308){return 0x1e27;}
                        if(second == 0x030c){return 0x021f;}
                        if(second == 0x0323){return 0x1e25;}
                        if(second == 0x0327){return 0x1e29;}
                        if(second == 0x032e){return 0x1e2b;}
                        if(second == 0x0331){return 0x1e96;}
                    }
                    if(first == 0x0069){
                        if(second == 0x0300){return 0x00ec;}
                        if(second == 0x0301){return 0x00ed;}
                        if(second == 0x0302){return 0x00ee;}
                        if(second == 0x0303){return 0x0129;}
                        if(second == 0x0304){return 0x012b;}
                        if(second == 0x0306){return 0x012d;}
                        if(second == 0x0308){return 0x00ef;}
                        if(second == 0x0309){return 0x1ec9;}
                        if(second == 0x030c){return 0x01d0;}
                        if(second == 0x030f){return 0x0209;}
                        if(second == 0x0311){return 0x020b;}
                        if(second == 0x0323){return 0x1ecb;}
                        if(second == 0x0328){return 0x012f;}
                        if(second == 0x0330){return 0x1e2d;}
                    }
                    if(first == 0x006a){
                        if(second == 0x0302){return 0x0135;}
                        if(second == 0x030c){return 0x01f0;}
                    }
                    if(first == 0x006b){
                        if(second == 0x0301){return 0x1e31;}
                        if(second == 0x030c){return 0x01e9;}
                        if(second == 0x0323){return 0x1e33;}
                        if(second == 0x0327){return 0x0137;}
                        if(second == 0x0331){return 0x1e35;}
                    }
                    if(first == 0x006c){
                        if(second == 0x0301){return 0x013a;}
                        if(second == 0x030c){return 0x013e;}
                        if(second == 0x0323){return 0x1e37;}
                        if(second == 0x0327){return 0x013c;}
                        if(second == 0x032d){return 0x1e3d;}
                        if(second == 0x0331){return 0x1e3b;}
                    }
                    if(first == 0x006d){
                        if(second == 0x0301){return 0x1e3f;}
                        if(second == 0x0307){return 0x1e41;}
                        if(second == 0x0323){return 0x1e43;}
                    }
                    if(first == 0x006e){
                        if(second == 0x0300){return 0x01f9;}
                        if(second == 0x0301){return 0x0144;}
                        if(second == 0x0303){return 0x00f1;}
                        if(second == 0x0307){return 0x1e45;}
                        if(second == 0x030c){return 0x0148;}
                        if(second == 0x0323){return 0x1e47;}
                        if(second == 0x0327){return 0x0146;}
                        if(second == 0x032d){return 0x1e4b;}
                        if(second == 0x0331){return 0x1e49;}
                    }
                }
                if(first >= 0x006f && first <= 0x0074){
                    if(first == 0x006f){
                        if(second == 0x0300){return 0x00f2;}
                        if(second == 0x0301){return 0x00f3;}
                        if(second == 0x0302){return 0x00f4;}
                        if(second == 0x0303){return 0x00f5;}
                        if(second == 0x0304){return 0x014d;}
                        if(second == 0x0306){return 0x014f;}
                        if(second == 0x0307){return 0x022f;}
                        if(second == 0x0308){return 0x00f6;}
                        if(second == 0x0309){return 0x1ecf;}
                        if(second == 0x030b){return 0x0151;}
                        if(second == 0x030c){return 0x01d2;}
                        if(second == 0x030f){return 0x020d;}
                        if(second == 0x0311){return 0x020f;}
                        if(second == 0x031b){return 0x01a1;}
                        if(second == 0x0323){return 0x1ecd;}
                        if(second == 0x0328){return 0x01eb;}
                    }
                    if(first == 0x0070){
                        if(second == 0x0301){return 0x1e55;}
                        if(second == 0x0307){return 0x1e57;}
                    }
                    if(first == 0x0072){
                        if(second == 0x0301){return 0x0155;}
                        if(second == 0x0307){return 0x1e59;}
                        if(second == 0x030c){return 0x0159;}
                        if(second == 0x030f){return 0x0211;}
                        if(second == 0x0311){return 0x0213;}
                        if(second == 0x0323){return 0x1e5b;}
                        if(second == 0x0327){return 0x0157;}
                        if(second == 0x0331){return 0x1e5f;}
                    }
                    if(first == 0x0073){
                        if(second == 0x0301){return 0x015b;}
                        if(second == 0x0302){return 0x015d;}
                        if(second == 0x0307){return 0x1e61;}
                        if(second == 0x030c){return 0x0161;}
                        if(second == 0x0323){return 0x1e63;}
                        if(second == 0x0326){return 0x0219;}
                        if(second == 0x0327){return 0x015f;}
                    }
                    if(first == 0x0074){
                        if(second == 0x0307){return 0x1e6b;}
                        if(second == 0x0308){return 0x1e97;}
                        if(second == 0x030c){return 0x0165;}
                        if(second == 0x0323){return 0x1e6d;}
                        if(second == 0x0326){return 0x021b;}
                        if(second == 0x0327){return 0x0163;}
                        if(second == 0x032d){return 0x1e71;}
                        if(second == 0x0331){return 0x1e6f;}
                    }
                }
                if(first >= 0x0075 && first <= 0x007a){
                    if(first == 0x0075){
                        if(second == 0x0300){return 0x00f9;}
                        if(second == 0x0301){return 0x00fa;}
                        if(second == 0x0302){return 0x00fb;}
                        if(second == 0x0303){return 0x0169;}
                        if(second == 0x0304){return 0x016b;}
                        if(second == 0x0306){return 0x016d;}
                        if(second == 0x0308){return 0x00fc;}
                        if(second == 0x0309){return 0x1ee7;}
                        if(second == 0x030a){return 0x016f;}
                        if(second == 0x030b){return 0x0171;}
                        if(second == 0x030c){return 0x01d4;}
                        if(second == 0x030f){return 0x0215;}
                        if(second == 0x0311){return 0x0217;}
                        if(second == 0x031b){return 0x01b0;}
                        if(second == 0x0323){return 0x1ee5;}
                        if(second == 0x0324){return 0x1e73;}
                        if(second == 0x0328){return 0x0173;}
                        if(second == 0x032d){return 0x1e77;}
                        if(second == 0x0330){return 0x1e75;}
                    }
                }
                if(first == 0x0076){
                    if(second == 0x0303){return 0x1e7d;}
                    if(second == 0x0323){return 0x1e7f;}
                }
                if(first == 0x0077){
                    if(second == 0x0300){return 0x1e81;}
                    if(second == 0x0301){return 0x1e83;}
                    if(second == 0x0302){return 0x0175;}
                    if(second == 0x0307){return 0x1e87;}
                    if(second == 0x0308){return 0x1e85;}
                    if(second == 0x030a){return 0x1e98;}
                    if(second == 0x0323){return 0x1e89;}
                }
                if(first == 0x0078){
                    if(second == 0x0307){return 0x1e8b;}
                    if(second == 0x0308){return 0x1e8d;}
                }
                if(first == 0x0079){
                    if(second == 0x0300){return 0x1ef3;}
                    if(second == 0x0301){return 0x00fd;}
                    if(second == 0x0302){return 0x0177;}
                    if(second == 0x0303){return 0x1ef9;}
                    if(second == 0x0304){return 0x0233;}
                    if(second == 0x0307){return 0x1e8f;}
                    if(second == 0x0308){return 0x00ff;}
                    if(second == 0x0309){return 0x1ef7;}
                    if(second == 0x030a){return 0x1e99;}
                    if(second == 0x0323){return 0x1ef5;}
                }
                if(first == 0x007a){
                    if(second == 0x0301){return 0x017a;}
                    if(second == 0x0302){return 0x1e91;}
                    if(second == 0x0307){return 0x017c;}
                    if(second == 0x030c){return 0x017e;}
                    if(second == 0x0323){return 0x1e93;}
                    if(second == 0x0331){return 0x1e95;}
                }
            }
            return -1;
        }
        if(first == 0x00a8){
            if(second == 0x0300){return 0x1fed;}
            if(second == 0x0301){return 0x0385;}
            if(second == 0x0342){return 0x1fc1;}
        }
        if(first >= 0x00c0 && first <= 0x00ff){
            if(first >= 0x00c0 && first <= 0x00cf){
                if(first == 0x00c2){
                    if(second == 0x0300){return 0x1ea6;}
                    if(second == 0x0301){return 0x1ea4;}
                    if(second == 0x0303){return 0x1eaa;}
                    if(second == 0x0309){return 0x1ea8;}
                }
                if(first == 0x00c4 && second == 0x0304){return 0x01de;}
                if(first == 0x00c5 && second == 0x0301){return 0x01fa;}
                if(first == 0x00c6){
                    if(second == 0x0301){return 0x01fc;}
                    if(second == 0x0304){return 0x01e2;}
                }
                if(first == 0x00c7 && second == 0x0301){return 0x1e08;}
                if(first == 0x00ca){
                    if(second == 0x0300){return 0x1ec0;}
                    if(second == 0x0301){return 0x1ebe;}
                    if(second == 0x0303){return 0x1ec4;}
                    if(second == 0x0309){return 0x1ec2;}
                }
                if(first == 0x00cf && second == 0x0301){return 0x1e2e;}
            }
            if(first >= 0x00d0 && first <= 0x00df){
                if(first == 0x00d4){
                    if(second == 0x0300){return 0x1ed2;}
                    if(second == 0x0301){return 0x1ed0;}
                    if(second == 0x0303){return 0x1ed6;}
                    if(second == 0x0309){return 0x1ed4;}
                }
                if(first == 0x00d5){
                    if(second == 0x0301){return 0x1e4c;}
                    if(second == 0x0304){return 0x022c;}
                    if(second == 0x0308){return 0x1e4e;}
                }
                if(first == 0x00d6 && second == 0x0304){return 0x022a;}
                if(first == 0x00d8 && second == 0x0301){return 0x01fe;}
                if(first == 0x00dc){
                    if(second == 0x0300){return 0x01db;}
                    if(second == 0x0301){return 0x01d7;}
                    if(second == 0x0304){return 0x01d5;}
                    if(second == 0x030c){return 0x01d9;}
                }
            }
            if(first >= 0x00e0 && first <= 0x00ef){
                if(first == 0x00e2){
                    if(second == 0x0300){return 0x1ea7;}
                    if(second == 0x0301){return 0x1ea5;}
                    if(second == 0x0303){return 0x1eab;}
                    if(second == 0x0309){return 0x1ea9;}
                }
                if(first == 0x00e4 && second == 0x0304){return 0x01df;}
                if(first == 0x00e5 && second == 0x0301){return 0x01fb;}
                if(first == 0x00e6){
                    if(second == 0x0301){return 0x01fd;}
                    if(second == 0x0304){return 0x01e3;}
                }
                if(first == 0x00e7 && second == 0x0301){return 0x1e09;}
                if(first == 0x00ea){
                    if(second == 0x0300){return 0x1ec1;}
                    if(second == 0x0301){return 0x1ebf;}
                    if(second == 0x0303){return 0x1ec5;}
                    if(second == 0x0309){return 0x1ec3;}
                }
                if(first == 0x00ef && second == 0x0301){return 0x1e2f;}
            }
            if(first >= 0x00f0 && first <= 0x00ff){
                if(first == 0x00f4){
                    if(second == 0x0300){return 0x1ed3;}
                    if(second == 0x0301){return 0x1ed1;}
                    if(second == 0x0303){return 0x1ed7;}
                    if(second == 0x0309){return 0x1ed5;}
                }
                if(first == 0x00f5){
                    if(second == 0x0301){return 0x1e4d;}
                    if(second == 0x0304){return 0x022d;}
                    if(second == 0x0308){return 0x1e4f;}
                }
                if(first == 0x00f6 && second == 0x0304){return 0x022b;}
                if(first == 0x00f8 && second == 0x0301){return 0x01ff;}
                if(first == 0x00fc){
                    if(second == 0x0300){return 0x01dc;}
                    if(second == 0x0301){return 0x01d8;}
                    if(second == 0x0304){return 0x01d6;}
                    if(second == 0x030c){return 0x01da;}
                }
            }
        }
    }
    if(first >= 0x0100 && first <= 0x0fff){
        if(first >= 0x0100 && first <= 0x01ff){
            if(first == 0x0102){
                if(second == 0x0300){return 0x1eb0;}
                if(second == 0x0301){return 0x1eae;}
                if(second == 0x0303){return 0x1eb4;}
                if(second == 0x0309){return 0x1eb2;}
            }
            if(first == 0x0103){
                if(second == 0x0300){return 0x1eb1;}
                if(second == 0x0301){return 0x1eaf;}
                if(second == 0x0303){return 0x1eb5;}
                if(second == 0x0309){return 0x1eb3;}
            }
            if(first == 0x0112){
                if(second == 0x0300){return 0x1e14;}
                if(second == 0x0301){return 0x1e16;}
            }
            if(first == 0x0113){
                if(second == 0x0300){return 0x1e15;}
                if(second == 0x0301){return 0x1e17;}
            }
            if(first == 0x014c){
                if(second == 0x0300){return 0x1e50;}
                if(second == 0x0301){return 0x1e52;}
            }
            if(first == 0x014d){
                if(second == 0x0300){return 0x1e51;}
                if(second == 0x0301){return 0x1e53;}
            }
            if(first == 0x015a && second == 0x0307){return 0x1e64;}
            if(first == 0x015b && second == 0x0307){return 0x1e65;}
            if(first == 0x0160 && second == 0x0307){return 0x1e66;}
            if(first == 0x0161 && second == 0x0307){return 0x1e67;}
            if(first == 0x0168 && second == 0x0301){return 0x1e78;}
            if(first == 0x0169 && second == 0x0301){return 0x1e79;}
            if(first == 0x016a && second == 0x0308){return 0x1e7a;}
            if(first == 0x016b && second == 0x0308){return 0x1e7b;}
            if(first == 0x017f && second == 0x0307){return 0x1e9b;}
            if(first == 0x01a0){
                if(second == 0x0300){return 0x1edc;}
                if(second == 0x0301){return 0x1eda;}
                if(second == 0x0303){return 0x1ee0;}
                if(second == 0x0309){return 0x1ede;}
                if(second == 0x0323){return 0x1ee2;}
            }
            if(first == 0x01a1){
                if(second == 0x0300){return 0x1edd;}
                if(second == 0x0301){return 0x1edb;}
                if(second == 0x0303){return 0x1ee1;}
                if(second == 0x0309){return 0x1edf;}
                if(second == 0x0323){return 0x1ee3;}
            }
            if(first == 0x01af){
                if(second == 0x0300){return 0x1eea;}
                if(second == 0x0301){return 0x1ee8;}
                if(second == 0x0303){return 0x1eee;}
                if(second == 0x0309){return 0x1eec;}
                if(second == 0x0323){return 0x1ef0;}
            }
            if(first == 0x01b0){
                if(second == 0x0300){return 0x1eeb;}
                if(second == 0x0301){return 0x1ee9;}
                if(second == 0x0303){return 0x1eef;}
                if(second == 0x0309){return 0x1eed;}
                if(second == 0x0323){return 0x1ef1;}
            }
            if(first == 0x01b7 && second == 0x030c){return 0x01ee;}
            if(first == 0x01ea && second == 0x0304){return 0x01ec;}
            if(first == 0x01eb && second == 0x0304){return 0x01ed;}
        }
        if(first >= 0x0200 && first <= 0x02ff){
            if(first == 0x0226 && second == 0x0304){return 0x01e0;}
            if(first == 0x0227 && second == 0x0304){return 0x01e1;}
            if(first == 0x0228 && second == 0x0306){return 0x1e1c;}
            if(first == 0x0229 && second == 0x0306){return 0x1e1d;}
            if(first == 0x022e && second == 0x0304){return 0x0230;}
            if(first == 0x022f && second == 0x0304){return 0x0231;}
            if(first == 0x0292 && second == 0x030c){return 0x01ef;}
        }
        if(first >= 0x0300 && first <= 0x03ff){
            if(first == 0x0391){
                if(second == 0x0300){return 0x1fba;}
                if(second == 0x0301){return 0x0386;}
                if(second == 0x0304){return 0x1fb9;}
                if(second == 0x0306){return 0x1fb8;}
                if(second == 0x0313){return 0x1f08;}
                if(second == 0x0314){return 0x1f09;}
                if(second == 0x0345){return 0x1fbc;}
            }
            if(first == 0x0395){
                if(second == 0x0300){return 0x1fc8;}
                if(second == 0x0301){return 0x0388;}
                if(second == 0x0313){return 0x1f18;}
                if(second == 0x0314){return 0x1f19;}
            }
            if(first == 0x0397){
                if(second == 0x0300){return 0x1fca;}
                if(second == 0x0301){return 0x0389;}
                if(second == 0x0313){return 0x1f28;}
                if(second == 0x0314){return 0x1f29;}
                if(second == 0x0345){return 0x1fcc;}
            }
            if(first == 0x0399){
                if(second == 0x0300){return 0x1fda;}
                if(second == 0x0301){return 0x038a;}
                if(second == 0x0304){return 0x1fd9;}
                if(second == 0x0306){return 0x1fd8;}
                if(second == 0x0308){return 0x03aa;}
                if(second == 0x0313){return 0x1f38;}
                if(second == 0x0314){return 0x1f39;}
            }
            if(first == 0x039f){
                if(second == 0x0300){return 0x1ff8;}
                if(second == 0x0301){return 0x038c;}
                if(second == 0x0313){return 0x1f48;}
                if(second == 0x0314){return 0x1f49;}
            }
            if(first == 0x03a1 && second == 0x0314){return 0x1fec;}
            if(first == 0x03a5){
                if(second == 0x0300){return 0x1fea;}
                if(second == 0x0301){return 0x038e;}
                if(second == 0x0304){return 0x1fe9;}
                if(second == 0x0306){return 0x1fe8;}
                if(second == 0x0308){return 0x03ab;}
                if(second == 0x0314){return 0x1f59;}
            }
            if(first == 0x03a9){
                if(second == 0x0300){return 0x1ffa;}
                if(second == 0x0301){return 0x038f;}
                if(second == 0x0313){return 0x1f68;}
                if(second == 0x0314){return 0x1f69;}
                if(second == 0x0345){return 0x1ffc;}
            }
            if(first == 0x03ac && second == 0x0345){return 0x1fb4;}
            if(first == 0x03ae && second == 0x0345){return 0x1fc4;}
            if(first == 0x03b1){
                if(second == 0x0300){return 0x1f70;}
                if(second == 0x0301){return 0x03ac;}
                if(second == 0x0304){return 0x1fb1;}
                if(second == 0x0306){return 0x1fb0;}
                if(second == 0x0313){return 0x1f00;}
                if(second == 0x0314){return 0x1f01;}
                if(second == 0x0342){return 0x1fb6;}
                if(second == 0x0345){return 0x1fb3;}
            }
            if(first == 0x03b5){
                if(second == 0x0300){return 0x1f72;}
                if(second == 0x0301){return 0x03ad;}
                if(second == 0x0313){return 0x1f10;}
                if(second == 0x0314){return 0x1f11;}
            }
            if(first == 0x03b7){
                if(second == 0x0300){return 0x1f74;}
                if(second == 0x0301){return 0x03ae;}
                if(second == 0x0313){return 0x1f20;}
                if(second == 0x0314){return 0x1f21;}
                if(second == 0x0342){return 0x1fc6;}
                if(second == 0x0345){return 0x1fc3;}
            }
            if(first == 0x03b9){
                if(second == 0x0300){return 0x1f76;}
                if(second == 0x0301){return 0x03af;}
                if(second == 0x0304){return 0x1fd1;}
                if(second == 0x0306){return 0x1fd0;}
                if(second == 0x0308){return 0x03ca;}
                if(second == 0x0313){return 0x1f30;}
                if(second == 0x0314){return 0x1f31;}
                if(second == 0x0342){return 0x1fd6;}
            }
            if(first == 0x03bf){
                if(second == 0x0300){return 0x1f78;}
                if(second == 0x0301){return 0x03cc;}
                if(second == 0x0313){return 0x1f40;}
                if(second == 0x0314){return 0x1f41;}
            }
            if(first == 0x03c1){
                if(second == 0x0313){return 0x1fe4;}
                if(second == 0x0314){return 0x1fe5;}
            }
            if(first == 0x03c5){
                if(second == 0x0300){return 0x1f7a;}
                if(second == 0x0301){return 0x03cd;}
                if(second == 0x0304){return 0x1fe1;}
                if(second == 0x0306){return 0x1fe0;}
                if(second == 0x0308){return 0x03cb;}
                if(second == 0x0313){return 0x1f50;}
                if(second == 0x0314){return 0x1f51;}
                if(second == 0x0342){return 0x1fe6;}
            }
            if(first == 0x03c9){
                if(second == 0x0300){return 0x1f7c;}
                if(second == 0x0301){return 0x03ce;}
                if(second == 0x0313){return 0x1f60;}
                if(second == 0x0314){return 0x1f61;}
                if(second == 0x0342){return 0x1ff6;}
                if(second == 0x0345){return 0x1ff3;}
            }
            if(first == 0x03ca){
                if(second == 0x0300){return 0x1fd2;}
                if(second == 0x0301){return 0x0390;}
                if(second == 0x0342){return 0x1fd7;}
            }
            if(first == 0x03cb){
                if(second == 0x0300){return 0x1fe2;}
                if(second == 0x0301){return 0x03b0;}
                if(second == 0x0342){return 0x1fe7;}
            }
            if(first == 0x03ce && second == 0x0345){return 0x1ff4;}
            if(first == 0x03d2){
                if(second == 0x0301){return 0x03d3;}
                if(second == 0x0308){return 0x03d4;}
            }
        }
        if(first >= 0x0400 && first <= 0x04ff){
            if(first == 0x0406 && second == 0x0308){return 0x0407;}
            if(first == 0x0410){
                if(second == 0x0306){return 0x04d0;}
                if(second == 0x0308){return 0x04d2;}
            }
            if(first == 0x0413 && second == 0x0301){return 0x0403;}
            if(first == 0x0415){
                if(second == 0x0300){return 0x0400;}
                if(second == 0x0306){return 0x04d6;}
                if(second == 0x0308){return 0x0401;}
            }
            if(first == 0x0416){
                if(second == 0x0306){return 0x04c1;}
                if(second == 0x0308){return 0x04dc;}
            }
            if(first == 0x0417 && second == 0x0308){return 0x04de;}
            if(first == 0x0418){
                if(second == 0x0300){return 0x040d;}
                if(second == 0x0304){return 0x04e2;}
                if(second == 0x0306){return 0x0419;}
                if(second == 0x0308){return 0x04e4;}
            }
            if(first == 0x041a && second == 0x0301){return 0x040c;}
            if(first == 0x041e && second == 0x0308){return 0x04e6;}
            if(first == 0x0423){
                if(second == 0x0304){return 0x04ee;}
                if(second == 0x0306){return 0x040e;}
                if(second == 0x0308){return 0x04f0;}
                if(second == 0x030b){return 0x04f2;}
            }
            if(first == 0x0427 && second == 0x0308){return 0x04f4;}
            if(first == 0x042b && second == 0x0308){return 0x04f8;}
            if(first == 0x042d && second == 0x0308){return 0x04ec;}
            if(first == 0x0430){
                if(second == 0x0306){return 0x04d1;}
                if(second == 0x0308){return 0x04d3;}
            }
            if(first == 0x0433 && second == 0x0301){return 0x0453;}
            if(first == 0x0435){
                if(second == 0x0300){return 0x0450;}
                if(second == 0x0306){return 0x04d7;}
                if(second == 0x0308){return 0x0451;}
            }
            if(first == 0x0436){
                if(second == 0x0306){return 0x04c2;}
                if(second == 0x0308){return 0x04dd;}
            }
            if(first == 0x0437 && second == 0x0308){return 0x04df;}
            if(first == 0x0438){
                if(second == 0x0300){return 0x045d;}
                if(second == 0x0304){return 0x04e3;}
                if(second == 0x0306){return 0x0439;}
                if(second == 0x0308){return 0x04e5;}
            }
            if(first == 0x043a && second == 0x0301){return 0x045c;}
            if(first == 0x043e && second == 0x0308){return 0x04e7;}
            if(first == 0x0443){
                if(second == 0x0304){return 0x04ef;}
                if(second == 0x0306){return 0x045e;}
                if(second == 0x0308){return 0x04f1;}
                if(second == 0x030b){return 0x04f3;}
            }
            if(first == 0x0447 && second == 0x0308){return 0x04f5;}
            if(first == 0x044b && second == 0x0308){return 0x04f9;}
            if(first == 0x044d && second == 0x0308){return 0x04ed;}
            if(first == 0x0456 && second == 0x0308){return 0x0457;}
            if(first == 0x0474 && second == 0x030f){return 0x0476;}
            if(first == 0x0475 && second == 0x030f){return 0x0477;}
            if(first == 0x04d8 && second == 0x0308){return 0x04da;}
            if(first == 0x04d9 && second == 0x0308){return 0x04db;}
            if(first == 0x04e8 && second == 0x0308){return 0x04ea;}
            if(first == 0x04e9 && second == 0x0308){return 0x04eb;}
        }
        if(first >= 0x0600 && first <= 0x06ff){
            if(first == 0x0627){
                if(second == 0x0653){return 0x0622;}
                if(second == 0x0654){return 0x0623;}
                if(second == 0x0655){return 0x0625;}
            }
            if(first == 0x0648 && second == 0x0654){return 0x0624;}
            if(first == 0x064a && second == 0x0654){return 0x0626;}
            if(first == 0x06c1 && second == 0x0654){return 0x06c2;}
            if(first == 0x06d2 && second == 0x0654){return 0x06d3;}
            if(first == 0x06d5 && second == 0x0654){return 0x06c0;}
        }
        if(first >= 0x0900 && first <= 0x09ff){
            if(first == 0x0928 && second == 0x093c){return 0x0929;}
            if(first == 0x0930 && second == 0x093c){return 0x0931;}
            if(first == 0x0933 && second == 0x093c){return 0x0934;}
            if(first == 0x09c7){
                if(second == 0x09be){return 0x09cb;}
                if(second == 0x09d7){return 0x09cc;}
            }
        }
        if(first >= 0x0b00 && first <= 0x0b7f){
            if(first == 0x0b47){
                if(second == 0x0b3e){return 0x0b4b;}
                if(second == 0x0b56){return 0x0b48;}
                if(second == 0x0b57){return 0x0b4c;}
            }
        }
        if(first >= 0x0c00 && first <= 0x0cff){
            if(first == 0x0c46 && second == 0x0c56){return 0x0c48;}
            if(first == 0x0cbf && second == 0x0cd5){return 0x0cc0;}
            if(first == 0x0cc6){
                if(second == 0x0cc2){return 0x0cca;}
                if(second == 0x0cd5){return 0x0cc7;}
                if(second == 0x0cd6){return 0x0cc8;}
            }
            if(first == 0x0cca && second == 0x0cd5){return 0x0ccb;}
        }
        if(first >= 0x0d00 && first <= 0x0dff){
            if(first == 0x0d46){
                if(second == 0x0d3e){return 0x0d4a;}
                if(second == 0x0d57){return 0x0d4c;}
            }
            if(first == 0x0d47 && second == 0x0d3e){return 0x0d4b;}
            if(first == 0x0dd9){
                if(second == 0x0dca){return 0x0dda;}
                if(second == 0x0dcf){return 0x0ddc;}
                if(second == 0x0ddf){return 0x0dde;}
            }
            if(first == 0x0ddc && second == 0x0dca){return 0x0ddd;}
        }
    }
    if(first >= 0x1000 && first <= 0x1fff){
        if(first == 0x1025 && second == 0x102e){return 0x1026;}
        if(first >= 0x1b00 && first <= 0x1bff){
            if(first == 0x1b05 && second == 0x1b35){return 0x1b06;}
            if(first == 0x1b07 && second == 0x1b35){return 0x1b08;}
            if(first == 0x1b09 && second == 0x1b35){return 0x1b0a;}
            if(first == 0x1b0b && second == 0x1b35){return 0x1b0c;}
            if(first == 0x1b0d && second == 0x1b35){return 0x1b0e;}
            if(first == 0x1b11 && second == 0x1b35){return 0x1b12;}
            if(first == 0x1b3a && second == 0x1b35){return 0x1b3b;}
            if(first == 0x1b3c && second == 0x1b35){return 0x1b3d;}
            if(first == 0x1b3e && second == 0x1b35){return 0x1b40;}
            if(first == 0x1b3f && second == 0x1b35){return 0x1b41;}
            if(first == 0x1b42 && second == 0x1b35){return 0x1b43;}
        }
        if(first >= 0x1e00 && first <= 0x1eff){
            if(first == 0x1e36 && second == 0x0304){return 0x1e38;}
            if(first == 0x1e37 && second == 0x0304){return 0x1e39;}
            if(first == 0x1e5a && second == 0x0304){return 0x1e5c;}
            if(first == 0x1e5b && second == 0x0304){return 0x1e5d;}
            if(first == 0x1e62 && second == 0x0307){return 0x1e68;}
            if(first == 0x1e63 && second == 0x0307){return 0x1e69;}
            if(first == 0x1ea0){
                if(second == 0x0302){return 0x1eac;}
                if(second == 0x0306){return 0x1eb6;}
            }
            if(first == 0x1ea1){
                if(second == 0x0302){return 0x1ead;}
                if(second == 0x0306){return 0x1eb7;}
            }
            if(first == 0x1eb8 && second == 0x0302){return 0x1ec6;}
            if(first == 0x1eb9 && second == 0x0302){return 0x1ec7;}
            if(first == 0x1ecc && second == 0x0302){return 0x1ed8;}
            if(first == 0x1ecd && second == 0x0302){return 0x1ed9;}
        }
        if(first >= 0x1f00 && first <= 0x1fff){
            if(first == 0x1f00){
                if(second == 0x0300){return 0x1f02;}
                if(second == 0x0301){return 0x1f04;}
                if(second == 0x0342){return 0x1f06;}
                if(second == 0x0345){return 0x1f80;}
            }
            if(first == 0x1f01){
                if(second == 0x0300){return 0x1f03;}
                if(second == 0x0301){return 0x1f05;}
                if(second == 0x0342){return 0x1f07;}
                if(second == 0x0345){return 0x1f81;}
            }
            if(first == 0x1f02 && second == 0x0345){return 0x1f82;}
            if(first == 0x1f03 && second == 0x0345){return 0x1f83;}
            if(first == 0x1f04 && second == 0x0345){return 0x1f84;}
            if(first == 0x1f05 && second == 0x0345){return 0x1f85;}
            if(first == 0x1f06 && second == 0x0345){return 0x1f86;}
            if(first == 0x1f07 && second == 0x0345){return 0x1f87;}
            if(first == 0x1f08){
                if(second == 0x0300){return 0x1f0a;}
                if(second == 0x0301){return 0x1f0c;}
                if(second == 0x0342){return 0x1f0e;}
                if(second == 0x0345){return 0x1f88;}
            }
            if(first == 0x1f09){
                if(second == 0x0300){return 0x1f0b;}
                if(second == 0x0301){return 0x1f0d;}
                if(second == 0x0342){return 0x1f0f;}
                if(second == 0x0345){return 0x1f89;}
            }
            if(first == 0x1f0a && second == 0x0345){return 0x1f8a;}
            if(first == 0x1f0b && second == 0x0345){return 0x1f8b;}
            if(first == 0x1f0c && second == 0x0345){return 0x1f8c;}
            if(first == 0x1f0d && second == 0x0345){return 0x1f8d;}
            if(first == 0x1f0e && second == 0x0345){return 0x1f8e;}
            if(first == 0x1f0f && second == 0x0345){return 0x1f8f;}
            if(first == 0x1f10){
                if(second == 0x0300){return 0x1f12;}
                if(second == 0x0301){return 0x1f14;}
            }
            if(first == 0x1f11){
                if(second == 0x0300){return 0x1f13;}
                if(second == 0x0301){return 0x1f15;}
            }
            if(first == 0x1f18){
                if(second == 0x0300){return 0x1f1a;}
                if(second == 0x0301){return 0x1f1c;}
            }
            if(first == 0x1f19){
                if(second == 0x0300){return 0x1f1b;}
                if(second == 0x0301){return 0x1f1d;}
            }
            if(first == 0x1f20){
                if(second == 0x0300){return 0x1f22;}
                if(second == 0x0301){return 0x1f24;}
                if(second == 0x0342){return 0x1f26;}
                if(second == 0x0345){return 0x1f90;}
            }
            if(first == 0x1f21){
                if(second == 0x0300){return 0x1f23;}
                if(second == 0x0301){return 0x1f25;}
                if(second == 0x0342){return 0x1f27;}
                if(second == 0x0345){return 0x1f91;}
            }
            if(first == 0x1f22 && second == 0x0345){return 0x1f92;}
            if(first == 0x1f23 && second == 0x0345){return 0x1f93;}
            if(first == 0x1f24 && second == 0x0345){return 0x1f94;}
            if(first == 0x1f25 && second == 0x0345){return 0x1f95;}
            if(first == 0x1f26 && second == 0x0345){return 0x1f96;}
            if(first == 0x1f27 && second == 0x0345){return 0x1f97;}
            if(first == 0x1f28){
                if(second == 0x0300){return 0x1f2a;}
                if(second == 0x0301){return 0x1f2c;}
                if(second == 0x0342){return 0x1f2e;}
                if(second == 0x0345){return 0x1f98;}
            }
            if(first == 0x1f29){
                if(second == 0x0300){return 0x1f2b;}
                if(second == 0x0301){return 0x1f2d;}
                if(second == 0x0342){return 0x1f2f;}
                if(second == 0x0345){return 0x1f99;}
            }
            if(first == 0x1f2a && second == 0x0345){return 0x1f9a;}
            if(first == 0x1f2b && second == 0x0345){return 0x1f9b;}
            if(first == 0x1f2c && second == 0x0345){return 0x1f9c;}
            if(first == 0x1f2d && second == 0x0345){return 0x1f9d;}
            if(first == 0x1f2e && second == 0x0345){return 0x1f9e;}
            if(first == 0x1f2f && second == 0x0345){return 0x1f9f;}
            if(first == 0x1f30){
                if(second == 0x0300){return 0x1f32;}
                if(second == 0x0301){return 0x1f34;}
                if(second == 0x0342){return 0x1f36;}
            }
            if(first == 0x1f31){
                if(second == 0x0300){return 0x1f33;}
                if(second == 0x0301){return 0x1f35;}
                if(second == 0x0342){return 0x1f37;}
            }
            if(first == 0x1f38){
                if(second == 0x0300){return 0x1f3a;}
                if(second == 0x0301){return 0x1f3c;}
                if(second == 0x0342){return 0x1f3e;}
            }
            if(first == 0x1f39){
                if(second == 0x0300){return 0x1f3b;}
                if(second == 0x0301){return 0x1f3d;}
                if(second == 0x0342){return 0x1f3f;}
            }
            if(first == 0x1f40){
                if(second == 0x0300){return 0x1f42;}
                if(second == 0x0301){return 0x1f44;}
            }
            if(first == 0x1f41){
                if(second == 0x0300){return 0x1f43;}
                if(second == 0x0301){return 0x1f45;}
            }
            if(first == 0x1f48){
                if(second == 0x0300){return 0x1f4a;}
                if(second == 0x0301){return 0x1f4c;}
            }
            if(first == 0x1f49){
                if(second == 0x0300){return 0x1f4b;}
                if(second == 0x0301){return 0x1f4d;}
            }
            if(first == 0x1f50){
                if(second == 0x0300){return 0x1f52;}
                if(second == 0x0301){return 0x1f54;}
                if(second == 0x0342){return 0x1f56;}
            }
            if(first == 0x1f51){
                if(second == 0x0300){return 0x1f53;}
                if(second == 0x0301){return 0x1f55;}
                if(second == 0x0342){return 0x1f57;}
            }
            if(first == 0x1f59){
                if(second == 0x0300){return 0x1f5b;}
                if(second == 0x0301){return 0x1f5d;}
                if(second == 0x0342){return 0x1f5f;}
            }
            if(first == 0x1f60){
                if(second == 0x0300){return 0x1f62;}
                if(second == 0x0301){return 0x1f64;}
                if(second == 0x0342){return 0x1f66;}
                if(second == 0x0345){return 0x1fa0;}
            }
            if(first == 0x1f61){
                if(second == 0x0300){return 0x1f63;}
                if(second == 0x0301){return 0x1f65;}
                if(second == 0x0342){return 0x1f67;}
                if(second == 0x0345){return 0x1fa1;}
            }
            if(first == 0x1f62 && second == 0x0345){return 0x1fa2;}
            if(first == 0x1f63 && second == 0x0345){return 0x1fa3;}
            if(first == 0x1f64 && second == 0x0345){return 0x1fa4;}
            if(first == 0x1f65 && second == 0x0345){return 0x1fa5;}
            if(first == 0x1f66 && second == 0x0345){return 0x1fa6;}
            if(first == 0x1f67 && second == 0x0345){return 0x1fa7;}
            if(first == 0x1f68){
                if(second == 0x0300){return 0x1f6a;}
                if(second == 0x0301){return 0x1f6c;}
                if(second == 0x0342){return 0x1f6e;}
                if(second == 0x0345){return 0x1fa8;}
            }
            if(first == 0x1f69){
                if(second == 0x0300){return 0x1f6b;}
                if(second == 0x0301){return 0x1f6d;}
                if(second == 0x0342){return 0x1f6f;}
                if(second == 0x0345){return 0x1fa9;}
            }
            if(first == 0x1f6a && second == 0x0345){return 0x1faa;}
            if(first == 0x1f6b && second == 0x0345){return 0x1fab;}
            if(first == 0x1f6c && second == 0x0345){return 0x1fac;}
            if(first == 0x1f6d && second == 0x0345){return 0x1fad;}
            if(first == 0x1f6e && second == 0x0345){return 0x1fae;}
            if(first == 0x1f6f && second == 0x0345){return 0x1faf;}
            if(first == 0x1f70 && second == 0x0345){return 0x1fb2;}
            if(first == 0x1f74 && second == 0x0345){return 0x1fc2;}
            if(first == 0x1f7c && second == 0x0345){return 0x1ff2;}
            if(first == 0x1fb6 && second == 0x0345){return 0x1fb7;}
            if(first == 0x1fbf){
                if(second == 0x0300){return 0x1fcd;}
                if(second == 0x0301){return 0x1fce;}
                if(second == 0x0342){return 0x1fcf;}
            }
            if(first == 0x1fc6 && second == 0x0345){return 0x1fc7;}
            if(first == 0x1ff6 && second == 0x0345){return 0x1ff7;}
            if(first == 0x1ffe){
                if(second == 0x0300){return 0x1fdd;}
                if(second == 0x0301){return 0x1fde;}
                if(second == 0x0342){return 0x1fdf;}
            }
        }
    }
    if(first >= 0x2000 && first <= 0xffff){
        if(first >= 0x2190 && first <= 0x21ff){
            if(first == 0x2190 && second == 0x0338){return 0x219a;}
            if(first == 0x2192 && second == 0x0338){return 0x219b;}
            if(first == 0x2194 && second == 0x0338){return 0x21ae;}
            if(first == 0x21d0 && second == 0x0338){return 0x21cd;}
            if(first == 0x21d2 && second == 0x0338){return 0x21cf;}
            if(first == 0x21d4 && second == 0x0338){return 0x21ce;}
        }
        if(first >= 0x3000 && first <= 0x30ff){
            if(first == 0x3046 && second == 0x3099){return 0x3094;}
            if(first == 0x304b && second == 0x3099){return 0x304c;}
            if(first == 0x304d && second == 0x3099){return 0x304e;}
            if(first == 0x304f && second == 0x3099){return 0x3050;}
            if(first == 0x3051 && second == 0x3099){return 0x3052;}
            if(first == 0x3053 && second == 0x3099){return 0x3054;}
            if(first == 0x3055 && second == 0x3099){return 0x3056;}
            if(first == 0x3057 && second == 0x3099){return 0x3058;}
            if(first == 0x3059 && second == 0x3099){return 0x305a;}
            if(first == 0x305b && second == 0x3099){return 0x305c;}
            if(first == 0x305d && second == 0x3099){return 0x305e;}
            if(first == 0x305f && second == 0x3099){return 0x3060;}
            if(first == 0x3061 && second == 0x3099){return 0x3062;}
            if(first == 0x3064 && second == 0x3099){return 0x3065;}
            if(first == 0x3066 && second == 0x3099){return 0x3067;}
            if(first == 0x3068 && second == 0x3099){return 0x3069;}
            if(first == 0x306f){
                if(second == 0x3099){return 0x3070;}
                if(second == 0x309a){return 0x3071;}
            }
            if(first == 0x3072){
                if(second == 0x3099){return 0x3073;}
                if(second == 0x309a){return 0x3074;}
            }
            if(first == 0x3075){
                if(second == 0x3099){return 0x3076;}
                if(second == 0x309a){return 0x3077;}
            }
            if(first == 0x3078){
                if(second == 0x3099){return 0x3079;}
                if(second == 0x309a){return 0x307a;}
            }
            if(first == 0x307b){
                if(second == 0x3099){return 0x307c;}
                if(second == 0x309a){return 0x307d;}
            }
            if(first == 0x309d && second == 0x3099){return 0x309e;}
            if(first == 0x30a6 && second == 0x3099){return 0x30f4;}
            if(first == 0x30ab && second == 0x3099){return 0x30ac;}
            if(first == 0x30ad && second == 0x3099){return 0x30ae;}
            if(first == 0x30af && second == 0x3099){return 0x30b0;}
            if(first == 0x30b1 && second == 0x3099){return 0x30b2;}
            if(first == 0x30b3 && second == 0x3099){return 0x30b4;}
            if(first == 0x30b5 && second == 0x3099){return 0x30b6;}
            if(first == 0x30b7 && second == 0x3099){return 0x30b8;}
            if(first == 0x30b9 && second == 0x3099){return 0x30ba;}
            if(first == 0x30bb && second == 0x3099){return 0x30bc;}
            if(first == 0x30bd && second == 0x3099){return 0x30be;}
            if(first == 0x30bf && second == 0x3099){return 0x30c0;}
            if(first == 0x30c1 && second == 0x3099){return 0x30c2;}
            if(first == 0x30c4 && second == 0x3099){return 0x30c5;}
            if(first == 0x30c6 && second == 0x3099){return 0x30c7;}
            if(first == 0x30c8 && second == 0x3099){return 0x30c9;}
            if(first == 0x30cf){
                if(second == 0x3099){return 0x30d0;}
                if(second == 0x309a){return 0x30d1;}
            }
            if(first == 0x30d2){
                if(second == 0x3099){return 0x30d3;}
                if(second == 0x309a){return 0x30d4;}
            }
            if(first == 0x30d5){
                if(second == 0x3099){return 0x30d6;}
                if(second == 0x309a){return 0x30d7;}
            }
            if(first == 0x30d8){
                if(second == 0x3099){return 0x30d9;}
                if(second == 0x309a){return 0x30da;}
            }
            if(first == 0x30db){
                if(second == 0x3099){return 0x30dc;}
                if(second == 0x309a){return 0x30dd;}
            }
            if(first == 0x30ef && second == 0x3099){return 0x30f7;}
            if(first == 0x30f0 && second == 0x3099){return 0x30f8;}
            if(first == 0x30f1 && second == 0x3099){return 0x30f9;}
            if(first == 0x30f2 && second == 0x3099){return 0x30fa;}
            if(first == 0x30fd && second == 0x3099){return 0x30fe;}
        }
    }
    if(first >= 0x10000 && first <= 0x1ffff){
        if(first >= 0x10000 && first <= 0x10fff){
            if(first == 0x105d2 && second == 0x0307){return 0x105c9;}
            if(first == 0x105da && second == 0x0307){return 0x105e4;}
        }
        if(first >= 0x11000 && first <= 0x11fff){
            if(first == 0x11099 && second == 0x110ba){return 0x1109a;}
            if(first == 0x1109b && second == 0x110ba){return 0x1109c;}
            if(first == 0x110a5 && second == 0x110ba){return 0x110ab;}
            if(first == 0x11131 && second == 0x11127){return 0x1112e;}
            if(first == 0x11132 && second == 0x11127){return 0x1112f;}
            if(first == 0x11347){
                if(second == 0x1133e){return 0x1134b;}
                if(second == 0x11357){return 0x1134c;}
            }
            if(first == 0x11382 && second == 0x113c9){return 0x11383;}
            if(first == 0x11384 && second == 0x113bb){return 0x11385;}
            if(first == 0x1138b && second == 0x113c2){return 0x1138e;}
            if(first == 0x11390 && second == 0x113c9){return 0x11391;}
            if(first == 0x113c2){
                if(second == 0x113b8){return 0x113c7;}
                if(second == 0x113c2){return 0x113c5;}
                if(second == 0x113c9){return 0x113c8;}
            }
            if(first == 0x114b9){
                if(second == 0x114b0){return 0x114bc;}
                if(second == 0x114ba){return 0x114bb;}
                if(second == 0x114bd){return 0x114be;}
            }
            if(first == 0x115b8 && second == 0x115af){return 0x115ba;}
            if(first == 0x115b9 && second == 0x115af){return 0x115bb;}
            if(first == 0x11935 && second == 0x11930){return 0x11938;}
        }
        if(first >= 0x16000 && first <= 0x16fff){
            if(first == 0x1611e){
                if(second == 0x1611e){return 0x16121;}
                if(second == 0x1611f){return 0x16123;}
                if(second == 0x16120){return 0x16125;}
                if(second == 0x16129){return 0x16122;}
            }
            if(first == 0x16121){
                if(second == 0x1611f){return 0x16126;}
                if(second == 0x16120){return 0x16128;}
            }
            if(first == 0x16122 && second == 0x1611f){return 0x16127;}
            if(first == 0x16129 && second == 0x1611f){return 0x16124;}
            if(first == 0x16d63 && second == 0x16d67){return 0x16d69;}
            if(first == 0x16d67 && second == 0x16d67){return 0x16d68;}
            if(first == 0x16d69 && second == 0x16d67){return 0x16d6a;}
        }
    }
    return -1;
}
// NOLINTEND(modernize-avoid-c-arrays, cppcoreguidelines-avoid-c-arrays, cppcoreguidelines-pro-bounds-constant-array-index)
}

int SGEXTN::CoreText::UnicodeQuery::getUppercase(int c){
    return (c + getUppercaseOffset(c));
}

int SGEXTN::CoreText::UnicodeQuery::getLowercase(int c){
    return (c + getLowercaseOffset(c));
}

int SGEXTN::CoreText::UnicodeQuery::getTitlecase(int c){
    return (c + getTitlecaseOffset(c));
}

bool SGEXTN::CoreText::UnicodeQuery::isWhitespace(int c){
    return getWhitespaceProperty(c);
}

SGEXTN::CoreText::FullCharacterType SGEXTN::CoreText::UnicodeQuery::getFullType(int c){
    return getUnicodeGeneralCategory(c);
}

SGEXTN::CoreText::SimplifiedCharacterType SGEXTN::CoreText::UnicodeQuery::getSimplifiedType(int c){
    return getUnicodeSimplifiedCategory(c);
}

int SGEXTN::CoreText::UnicodeQuery::getDecimalDigitValue(int c){
    return getUnicodeDecimalDigit(c);
}

float SGEXTN::CoreText::UnicodeQuery::getNumericalValue(int c){
    return getUnicodeNumerical(c);
}

SGEXTN::CoreText::GraphemeSegmentationType SGEXTN::CoreText::UnicodeQuery::getGraphemeSegmentationType(int c){
    if(c == 0xd){return SGEXTN::CoreText::GraphemeSegmentationType::Return;}
    if(c == 0xa){return SGEXTN::CoreText::GraphemeSegmentationType::NewLine;}
    if(c == 0x200d){return SGEXTN::CoreText::GraphemeSegmentationType::ZeroWidthJoiner;}
    if(c >= 0x1f1e6 && c <= 0x1f1ff){return SGEXTN::CoreText::GraphemeSegmentationType::RegionalIndicator;}
    if((c >= 0x1100 && c <= 0x115f) || (c >= 0xa960 && c <= 0xa97c)){return SGEXTN::CoreText::GraphemeSegmentationType::HangulLeading;}
    if((c >= 0x1160 && c <= 0x11a7) || (c >= 0xd7b0 && c <= 0xd7c6) || c == 0x16d63 || (c >= 0x16d67 && c <= 0x16d6a)){return SGEXTN::CoreText::GraphemeSegmentationType::HangulVowel;}
    if((c >= 0x11a8 && c <= 0x11ff) || (c >= 0xd7cb && c <= 0xd7fb)){return SGEXTN::CoreText::GraphemeSegmentationType::HangulTrailing;}
    if(c >= 0xac00 && c <= 0xd7a3){
        if((c - 0xac00) % 0x1c == 0){return SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowel;}
        return SGEXTN::CoreText::GraphemeSegmentationType::HangulLeadingAndVowelAndTrailing;
    }
    if(c >= 0x1f3fb && c <= 0x1f3ff){return SGEXTN::CoreText::GraphemeSegmentationType::Extend;}
    const SGEXTN::CoreText::FullCharacterType generalCategory = getUnicodeGeneralCategory(c);
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::EnclosingMark || generalCategory == SGEXTN::CoreText::FullCharacterType::NonspacingCombiningMark){return SGEXTN::CoreText::GraphemeSegmentationType::Extend;}
    if(getUnicodeOtherGraphemeExtendProperty(c) == true){return SGEXTN::CoreText::GraphemeSegmentationType::Extend;}
    if(getUnicodePrependConcatenationMark(c) == true){return SGEXTN::CoreText::GraphemeSegmentationType::Prepend;}
    if(getUnicodeIndicSyllabicPrepend(c) == true){return SGEXTN::CoreText::GraphemeSegmentationType::Prepend;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::LineBreak || generalCategory == SGEXTN::CoreText::FullCharacterType::ParagraphBreak || generalCategory == SGEXTN::CoreText::FullCharacterType::ControlCharacter || generalCategory == SGEXTN::CoreText::FullCharacterType::FormatCharacter){return SGEXTN::CoreText::GraphemeSegmentationType::ControlCharacter;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::UnassignedCharacter && getUnicodeDefaultInvisibleUnassigned(c) == true){return SGEXTN::CoreText::GraphemeSegmentationType::ControlCharacter;}
    if(c == 0xe33 || c == 0xeb3){return SGEXTN::CoreText::GraphemeSegmentationType::SpacingCombiningMark;}
    if(generalCategory == SGEXTN::CoreText::FullCharacterType::SpacingCombiningMark && getUnicodeSpacingCombiningMarkGraphemeClusterExtendProperty(c) == false && getUnicodeGraphemeSegmentationSpacingCombiningMarkException(c) == false){return SGEXTN::CoreText::GraphemeSegmentationType::SpacingCombiningMark;}
    return SGEXTN::CoreText::GraphemeSegmentationType::Other;
}

SGEXTN::CoreText::GraphemeRuleRelatedType SGEXTN::CoreText::UnicodeQuery::getGraphemeRuleRelatedType(int c){
    if(isUnicodeEmoji(c) == true){return SGEXTN::CoreText::GraphemeRuleRelatedType::Rule11Emoji;}
    if(isUnicodeIndicGraphemeConsonant(c) == true){return SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cConsonant;}
    if(isUnicodeIndicGraphemeLinker(c) == true){return SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cLinker;}
    if(isUnicodeIndicGraphemeExtend(c) == true){return SGEXTN::CoreText::GraphemeRuleRelatedType::Rule9cExtend;}
    return SGEXTN::CoreText::GraphemeRuleRelatedType::None;
}

SGEXTN::CoreText::String SGEXTN::CoreText::UnicodeQuery::getEquivDecomposition(int c){
    return getEquivDecomp(c);
}

SGEXTN::CoreText::String SGEXTN::CoreText::UnicodeQuery::getCompatDecomposition(int c){
    if(getEquivDecomp(c) != ""){return getEquivDecomp(c);}
    return getCompatDecomp(c);
}

int SGEXTN::CoreText::UnicodeQuery::getCombiningMarkOrder(int c){
    return getUnicodeCombiningMarkOrder(c);
}

int SGEXTN::CoreText::UnicodeQuery::getBinaryRecomposition(int first, int second){
    return getUnicodeRecompositionMapping(first, second);
}