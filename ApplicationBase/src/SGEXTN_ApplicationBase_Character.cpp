#include <SGEXTN_ApplicationBase_Character.h>
#include <private_api/SGEXTN_ApplicationBase_TextBuffer.h>
#include <private_api/SGEXTN_Containers_Crash.h>
#include <SGEXTN_Containers_Hash.h>
#include <SGEXTN_Containers_Array.h>
#include <SGEXTN_ApplicationBase_String.h>

namespace {
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

void appendUnicode(int unicode, SGEXTN::ApplicationBase::Character& c){
    if(unicode < 0x80){c.private_data.pushBack(static_cast<char>(unicode));}
    else if(unicode < 0x800){
        c.private_data.pushBack(static_cast<char>(0xc0 + (unicode >> 6)));
        c.private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x10000){
        c.private_data.pushBack(static_cast<char>(0xe0 + (unicode >> 12)));
        c.private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 6) & 0x3f)));
        c.private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
    else if(unicode < 0x110000){
        c.private_data.pushBack(static_cast<char>(0xf0 + (unicode >> 18)));
        c.private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 12) & 0x3f)));
        c.private_data.pushBack(static_cast<char>(0x80 + ((unicode >> 6) & 0x3f)));
        c.private_data.pushBack(static_cast<char>(0x80 + (unicode & 0x3f)));
    }
}
}

SGEXTN::ApplicationBase::Character::Character(){
    private_data.pushBack(0xE2);
    private_data.pushBack(0x99);
    private_data.pushBack(0xA5);
}

SGEXTN::ApplicationBase::Character::Character(char c){
    private_data.pushBack(c);
}

SGEXTN::ApplicationBase::Character::Character(int unicode){
    if(unicode < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor crashed because unicode is negative");}
    else if(unicode > 0x10ffff){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character constructor crashed because unicode exceeds the largest possible code point");}
    appendUnicode(unicode, (*this));
}

bool SGEXTN::ApplicationBase::Character::operator==(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data == x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator!=(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data != x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator<(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data < x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator>(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data > x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator<=(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data <= x.private_data);
}

bool SGEXTN::ApplicationBase::Character::operator>=(const SGEXTN::ApplicationBase::Character& x) const {
    return (private_data >= x.private_data);
}

int SGEXTN::ApplicationBase::Character::hash() const {
    return SGEXTN::Containers::Hash<SGEXTN::ApplicationBase::TextBuffer>()(private_data);
}

int SGEXTN::ApplicationBase::Character::byteLength() const {
    return private_data.length();
}

unsigned char& SGEXTN::ApplicationBase::Character::byteAt(int i){
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index points beyond the end of the character");}
    return private_data.byteAt(i);
}

const unsigned char& SGEXTN::ApplicationBase::Character::byteAt(int i) const {
    if(i < 0){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index is negative");}
    else if(i >= byteLength()){SGEXTN::Containers::Crash::crash("SGEXTN::ApplicationBase::Character::byteAt crashed because the index points beyond the end of the character");}
    return private_data.byteAt(i);
}

char SGEXTN::ApplicationBase::Character::baseToChar() const {
    return static_cast<char>(private_data.byteAt(0));
}

bool SGEXTN::ApplicationBase::Character::isDigit() const {
    if(byteLength() != 1){return false;}
    if((*this) >= '0' && (*this) <= '9'){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isEnglishLowercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'a' && (*this) <= 'z'){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isEnglishUppercase() const {
    if(byteLength() != 1){return false;}
    if((*this) >= 'A' && (*this) <= 'Z'){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isEnglishLetter() const {
    return (isEnglishUppercase() || isEnglishLowercase());
}

bool SGEXTN::ApplicationBase::Character::isEnglishAlphanumeric() const {
    return (isEnglishLetter() || isDigit());
}

bool SGEXTN::ApplicationBase::Character::isASCII() const {
    if(byteLength() != 1){return false;}
    if(byteAt(0) < 128){return true;}
    return false;
}

bool SGEXTN::ApplicationBase::Character::isWhitespace() const {
    return (getBaseSimplifiedType() == SGEXTN::ApplicationBase::SimplifiedCharacterType::Whitespace);
}

SGEXTN::Containers::Array<int> SGEXTN::ApplicationBase::Character::getUnicode() const {
    SGEXTN::Containers::Vector<int> output;
    int i = 0;
    while(i < byteLength()){
        if((byteAt(i) & 0x80) == 0){
            output.pushBack(static_cast<int>(byteAt(i)));
            i++;
        }
        else if((byteAt(i) & 0xE0) == 0xC0){
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x1f) << 6);
            unicode += static_cast<int>(byteAt(i + 1) & 0x3f);
            output.pushBack(unicode);
            i += 2;
        }
        else if((byteAt(i) & 0xF0) == 0xE0){
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x0f) << 12);
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 6);
            unicode += static_cast<int>(byteAt(i + 2) & 0x3f);
            output.pushBack(unicode);
            i += 3;
        }
        else{
            int unicode = 0;
            unicode += (static_cast<int>(byteAt(i) & 0x07) << 18);
            unicode += (static_cast<int>(byteAt(i + 1) & 0x3f) << 12);
            unicode += (static_cast<int>(byteAt(i + 2) & 0x3f) << 6);
            unicode += static_cast<int>(byteAt(i + 3) & 0x3f);
            output.pushBack(unicode);
            i += 4;
        }
    }
    SGEXTN::Containers::Array<int> outputArray(output.length());
    for(int j=0; j<output.length(); j++){
        outputArray.at(j) = output.at(j);
    }
    return outputArray;
}

bool SGEXTN::ApplicationBase::Character::isUppercase() const {
    return (getBaseFullType() == SGEXTN::ApplicationBase::FullCharacterType::UppercaseLetter);
}

bool SGEXTN::ApplicationBase::Character::isLowercase() const {
    return (getBaseFullType() == SGEXTN::ApplicationBase::FullCharacterType::LowercaseLetter);
}

bool SGEXTN::ApplicationBase::Character::isTitlecase() const {
    return (getBaseFullType() == SGEXTN::ApplicationBase::FullCharacterType::TitlecaseLetter);
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::Character::getUppercase() const {
    if(byteLength() == 1){return SGEXTN::ApplicationBase::Character(static_cast<int>(byteAt(0)) + getUppercaseOffset(byteAt(0)));}
    SGEXTN::ApplicationBase::Character output;
    output.private_data = SGEXTN::ApplicationBase::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(unicode.at(i) + getUppercaseOffset(unicode.at(i)), output);
    }
    return output;
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::Character::getLowercase() const {
    if(byteLength() == 1){return SGEXTN::ApplicationBase::Character(static_cast<int>(byteAt(0)) + getLowercaseOffset(byteAt(0)));}
    SGEXTN::ApplicationBase::Character output;
    output.private_data = SGEXTN::ApplicationBase::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(unicode.at(i) + getLowercaseOffset(unicode.at(i)), output);
    }
    return output;
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::Character::getTitlecase() const {
    if(byteLength() == 1){return SGEXTN::ApplicationBase::Character(static_cast<int>(byteAt(0)) + getTitlecaseOffset(byteAt(0)));}
    SGEXTN::ApplicationBase::Character output;
    output.private_data = SGEXTN::ApplicationBase::TextBuffer();
    SGEXTN::Containers::Array<int> unicode = getUnicode();
    for(int i=0; i<unicode.length(); i++){
        appendUnicode(unicode.at(i) + getTitlecaseOffset(unicode.at(i)), output);
    }
    return output;
}

bool SGEXTN::ApplicationBase::Character::isNormalised() const {
    // run fast check path
    //return ((*this) == getNormalised());
}

SGEXTN::ApplicationBase::Character SGEXTN::ApplicationBase::Character::getNormalised() const {

}

SGEXTN::ApplicationBase::FullCharacterType SGEXTN::ApplicationBase::Character::getBaseFullType() const {

}

SGEXTN::ApplicationBase::SimplifiedCharacterType SGEXTN::ApplicationBase::Character::getBaseSimplifiedType() const {

}

SGEXTN::ApplicationBase::WritingDirection SGEXTN::ApplicationBase::Character::getBaseWritingDirection() const {

}

SGEXTN::ApplicationBase::String SGEXTN::ApplicationBase::Character::getSimplestEquivalent() const {

}