#pragma once
#include <QDebug>
#include <SGEXTN_ApplicationBase_String.h>
#include <SGEXTN_Containers_Set.h>
#include <SGEXTN_Containers_LessThan.h>
#include <SGEXTN_ApplicationBase_UnicodeQuery.h>
#include <SGEXTN_Containers_Array.h>
#include <QFile>
#include <SGEXTN_ApplicationBase_Character.h>
#include <SGEXTN_Containers_Map.h>
#include <SGEXTN_Containers_Pair.h>

SGEXTN::Containers::Set<int, SGEXTN::Containers::LessThan<int>> exclusions;
SGEXTN::Containers::Map<SGEXTN::Containers::Pair<int, int>, int, SGEXTN::Containers::LessThan<SGEXTN::Containers::Pair<int, int>>> compositionMappings;

void logNewString(const SGEXTN::ApplicationBase::String& s){
    qDebug().noquote().nospace() << QString::fromUtf8(reinterpret_cast<const char*>(&s.private_data.byteAt(0)), s.byteLength());
}

void parseExclusions(){
    QString dataString = "";
    QFile file("../ApplicationBase/misc/unicodecompositionexclusion.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        dataString = file.readAll();
        file.close();
    }
    QVector<QString> lines = dataString.split('\n');
    for(int i=0; i<lines.length(); i++){
        int start = 0;
        int end = 0;
        QString codePoint = lines.at(i).left(lines.at(i).indexOf(';')).trimmed();
        if(codePoint.contains("..") == false){
            start = codePoint.toInt(nullptr, 16);
            end = start;
        }
        else{
            start = codePoint.left(codePoint.indexOf("..")).toInt(nullptr, 16);
            end = codePoint.right(codePoint.length() - 2 - codePoint.indexOf("..")).toInt(nullptr, 16);
        }
        for(int j=start; j<=end; j++){
            exclusions.insert(j);
        }
    }
}

void createMappings(){
    for(int i=0; i<=0x10ffff; i++){
        if(i >= 0xac00 && i <= 0xd7a3){continue;}
        SGEXTN::ApplicationBase::String decomp = SGEXTN::ApplicationBase::UnicodeQuery::getEquivDecomposition(i);
        if(decomp.getUnicode().length() > 1 && exclusions.contains(i) == false){
            int first = decomp.getUnicode().at(0);
            int second = decomp.getUnicode().at(1);
            compositionMappings.insert(SGEXTN::Containers::Pair<int, int>(first, second), i);
        }
    }
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
    {
        int leadingHangulIndex = first - 0x1100;
        int vowelHangulIndex = second - 0x1161;
        if(leadingHangulIndex >= 0 && leadingHangulIndex < 19 && vowelHangulIndex >= 0 && vowelHangulIndex < 21){return (0xac00 + (leadingHangulIndex * 21 + vowelHangulIndex) * 28);}
    }
    {
        int leadingAndVowelHangulIndex = first - 0xac00;
        int trailingHangulIndex = second - 0x11a7;
        if(leadingAndVowelHangulIndex >= 0 && leadingAndVowelHangulIndex < 11172 && leadingAndVowelHangulIndex % 28 == 0 && trailingHangulIndex > 0 && trailingHangulIndex < 28){return (first + trailingHangulIndex);}
    }
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
            if(first == 0x0308 && second == 0x0301){return 0x0344;}
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
        if(first >= 0x0500 && first <= 0x05ff){
            if(first == 0x05d0){
                if(second == 0x05b7){return 0xfb2e;}
                if(second == 0x05b8){return 0xfb2f;}
                if(second == 0x05bc){return 0xfb30;}
            }
            if(first == 0x05d1){
                if(second == 0x05bc){return 0xfb31;}
                if(second == 0x05bf){return 0xfb4c;}
            }
            if(first == 0x05d2 && second == 0x05bc){return 0xfb32;}
            if(first == 0x05d3 && second == 0x05bc){return 0xfb33;}
            if(first == 0x05d4 && second == 0x05bc){return 0xfb34;}
            if(first == 0x05d5){
                if(second == 0x05b9){return 0xfb4b;}
                if(second == 0x05bc){return 0xfb35;}
            }
            if(first == 0x05d6 && second == 0x05bc){return 0xfb36;}
            if(first == 0x05d8 && second == 0x05bc){return 0xfb38;}
            if(first == 0x05d9){
                if(second == 0x05b4){return 0xfb1d;}
                if(second == 0x05bc){return 0xfb39;}
            }
            if(first == 0x05da && second == 0x05bc){return 0xfb3a;}
            if(first == 0x05db){
                if(second == 0x05bc){return 0xfb3b;}
                if(second == 0x05bf){return 0xfb4d;}
            }
            if(first == 0x05dc && second == 0x05bc){return 0xfb3c;}
            if(first == 0x05de && second == 0x05bc){return 0xfb3e;}
            if(first == 0x05e0 && second == 0x05bc){return 0xfb40;}
            if(first == 0x05e1 && second == 0x05bc){return 0xfb41;}
            if(first == 0x05e3 && second == 0x05bc){return 0xfb43;}
            if(first == 0x05e4){
                if(second == 0x05bc){return 0xfb44;}
                if(second == 0x05bf){return 0xfb4e;}
            }
            if(first == 0x05e6 && second == 0x05bc){return 0xfb46;}
            if(first == 0x05e7 && second == 0x05bc){return 0xfb47;}
            if(first == 0x05e8 && second == 0x05bc){return 0xfb48;}
            if(first == 0x05e9){
                if(second == 0x05bc){return 0xfb49;}
                if(second == 0x05c1){return 0xfb2a;}
                if(second == 0x05c2){return 0xfb2b;}
            }
            if(first == 0x05ea && second == 0x05bc){return 0xfb4a;}
            if(first == 0x05f2 && second == 0x05b7){return 0xfb1f;}
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
            if(first == 0x0915 && second == 0x093c){return 0x0958;}
            if(first == 0x0916 && second == 0x093c){return 0x0959;}
            if(first == 0x0917 && second == 0x093c){return 0x095a;}
            if(first == 0x091c && second == 0x093c){return 0x095b;}
            if(first == 0x0921 && second == 0x093c){return 0x095c;}
            if(first == 0x0922 && second == 0x093c){return 0x095d;}
            if(first == 0x0928 && second == 0x093c){return 0x0929;}
            if(first == 0x092b && second == 0x093c){return 0x095e;}
            if(first == 0x092f && second == 0x093c){return 0x095f;}
            if(first == 0x0930 && second == 0x093c){return 0x0931;}
            if(first == 0x0933 && second == 0x093c){return 0x0934;}
            if(first == 0x09a1 && second == 0x09bc){return 0x09dc;}
            if(first == 0x09a2 && second == 0x09bc){return 0x09dd;}
            if(first == 0x09af && second == 0x09bc){return 0x09df;}
            if(first == 0x09c7){
                if(second == 0x09be){return 0x09cb;}
                if(second == 0x09d7){return 0x09cc;}
            }
        }
        if(first >= 0x0a00 && first <= 0x0aff){
            if(first == 0x0a16 && second == 0x0a3c){return 0x0a59;}
            if(first == 0x0a17 && second == 0x0a3c){return 0x0a5a;}
            if(first == 0x0a1c && second == 0x0a3c){return 0x0a5b;}
            if(first == 0x0a2b && second == 0x0a3c){return 0x0a5e;}
            if(first == 0x0a32 && second == 0x0a3c){return 0x0a33;}
            if(first == 0x0a38 && second == 0x0a3c){return 0x0a36;}
        }
        if(first >= 0x0b00 && first <= 0x0b7f){
            if(first == 0x0b21 && second == 0x0b3c){return 0x0b5c;}
            if(first == 0x0b22 && second == 0x0b3c){return 0x0b5d;}
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
        if(first >= 0x0f00 && first <= 0x0fff){
            if(first == 0x0f40 && second == 0x0fb5){return 0x0f69;}
            if(first == 0x0f42 && second == 0x0fb7){return 0x0f43;}
            if(first == 0x0f4c && second == 0x0fb7){return 0x0f4d;}
            if(first == 0x0f51 && second == 0x0fb7){return 0x0f52;}
            if(first == 0x0f56 && second == 0x0fb7){return 0x0f57;}
            if(first == 0x0f5b && second == 0x0fb7){return 0x0f5c;}
            if(first == 0x0f71){
                if(second == 0x0f72){return 0x0f73;}
                if(second == 0x0f74){return 0x0f75;}
                if(second == 0x0f80){return 0x0f81;}
            }
            if(first == 0x0f90 && second == 0x0fb5){return 0x0fb9;}
            if(first == 0x0f92 && second == 0x0fb7){return 0x0f93;}
            if(first == 0x0f9c && second == 0x0fb7){return 0x0f9d;}
            if(first == 0x0fa1 && second == 0x0fb7){return 0x0fa2;}
            if(first == 0x0fa6 && second == 0x0fb7){return 0x0fa7;}
            if(first == 0x0fab && second == 0x0fb7){return 0x0fac;}
            if(first == 0x0fb2 && second == 0x0f80){return 0x0f76;}
            if(first == 0x0fb3 && second == 0x0f80){return 0x0f78;}
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
        if(first == 0x2add && second == 0x0338){return 0x2adc;}
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
        if(first == 0xfb49){
            if(second == 0x05c1){return 0xfb2c;}
            if(second == 0x05c2){return 0xfb2d;}
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
        if(first >= 0x1d100 && first <= 0x1d1ff){
            if(first == 0x1d157 && second == 0x1d165){return 0x1d15e;}
            if(first == 0x1d158 && second == 0x1d165){return 0x1d15f;}
            if(first == 0x1d15f){
                if(second == 0x1d16e){return 0x1d160;}
                if(second == 0x1d16f){return 0x1d161;}
                if(second == 0x1d170){return 0x1d162;}
                if(second == 0x1d171){return 0x1d163;}
                if(second == 0x1d172){return 0x1d164;}
            }
            if(first == 0x1d1b9 && second == 0x1d165){return 0x1d1bb;}
            if(first == 0x1d1ba && second == 0x1d165){return 0x1d1bc;}
            if(first == 0x1d1bb){
                if(second == 0x1d16e){return 0x1d1bd;}
                if(second == 0x1d16f){return 0x1d1bf;}
            }
            if(first == 0x1d1bc){
                if(second == 0x1d16e){return 0x1d1be;}
                if(second == 0x1d16f){return 0x1d1c0;}
            }
        }
    }
    return -1;
}

void logMappings(){
    int count = 0;
    for(SGEXTN::Containers::MapConstIterator<SGEXTN::Containers::Pair<int, int>, int, SGEXTN::Containers::LessThan<SGEXTN::Containers::Pair<int, int>>> i = compositionMappings.constBegin(); i != compositionMappings.constEnd(); i++){
        if(getUnicodeRecompositionMapping(i.key().first, i.key().second) == i.value()){continue;}
        SGEXTN::ApplicationBase::String log;
        log += SGEXTN::ApplicationBase::String::stringFromInt(i.key().first, 16).fillLeftToCharacterLength(4, '0');
        log += " ";
        log += SGEXTN::ApplicationBase::String::stringFromInt(i.key().second, 16).fillLeftToCharacterLength(4, '0');
        log += " --> ";
        log += SGEXTN::ApplicationBase::String::stringFromInt(i.value(), 16).fillLeftToCharacterLength(4, '0');
        log += " | ";
        log += SGEXTN::ApplicationBase::Character(i.value());
        logNewString(log);
        count++;
    }
    qDebug() << count;
}