#include <SGXIdentifier.h>
#include <SGXRandomNumberGenerator.h>
#include <SGXString.h>
#include <SGLHashAlgorithm.h>
#include <SGLArray.h>
#include <SGLSpan.h>
#include <SGLHash.h>
#include <SGLUnorderedSet.h>
#include <SGLEqualsTo.h>

SGLUnorderedSet<SGXIdentifier, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>* SGXIdentifier::identifiersList = new SGLUnorderedSet<SGXIdentifier, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>();
const SGXIdentifier SGXIdentifier::nullIdentifier = SGXIdentifier(0);

SGXIdentifier::SGXIdentifier(bool ifValid){ // NOLINT(misc-no-recursion)
    if(ifValid == false){
        (*this).a = SGXRandomNumberGenerator::rngInt32();
        (*this).b = SGXRandomNumberGenerator::rngInt32();
        (*this).c = SGXRandomNumberGenerator::rngInt32();
        (*this).d = SGXRandomNumberGenerator::rngInt32();
    }
    else{
        SGXIdentifier t = SGXIdentifier(false);
        while(t.exists()){
            t = SGXIdentifier(false);
        }
        (*this) = t;
    }
}

SGXIdentifier::SGXIdentifier(int /*placeholder*/){
    (*this).a = 0u;
    (*this).b = 0u;
    (*this).c = 0u;
    (*this).d = 0u;
}

SGXIdentifier::SGXIdentifier(unsigned int a, unsigned int b, unsigned int c, unsigned int d, bool ifValid, int *errCode){
    (*this).a = a;
    (*this).b = b;
    (*this).c = c;
    (*this).d = d;
    if(errCode != nullptr){
        if((*this) == SGXIdentifier::nullIdentifier){(*errCode) = 2;}
        else if(ifValid == true && (*this).exists() == true){(*errCode) = 1;}
        else{(*errCode) = 0;}
    }
}

SGXIdentifier::SGXIdentifier(const SGXString &s, bool ifValid, int *errCode){
    unsigned int a = 0u;
    unsigned int b = 0u;
    unsigned int c = 0u;
    unsigned int d = 0u;
    if(s.length() == 32){
        bool x = true;
        bool x0 = true;
        a = s.substring(0, 8).parseToUnsignedIntBase16(&x);
        if(x == false){x0 = false;}
        b = s.substring(8, 8).parseToUnsignedIntBase16(&x);
        if(x == false){x0 = false;}
        c = s.substring(16, 8).parseToUnsignedIntBase16(&x);
        if(x == false){x0 = false;}
        d = s.substring(24, 8).parseToUnsignedIntBase16(&x);
        if(x == false){x0 = false;}
        if(x0 == false){
            a = 0u;
            b = 0u;
            c = 0u;
            d = 0u;
        }
    }
    (*this).a = a;
    (*this).b = b;
    (*this).c = c;
    (*this).d = d;
    if(errCode != nullptr){
        if((*this) == SGXIdentifier::nullIdentifier){(*errCode) = 2;}
        else if(ifValid == true && (*this).exists() == true){(*errCode) = 1;}
        else{(*errCode) = 0;}
    }
}

bool SGXIdentifier::registerIdentifier(SGXIdentifier x){
    if(SGXIdentifier::identifiersList != nullptr && (*SGXIdentifier::identifiersList).contains(x)){return false;}
    if(SGXIdentifier::identifiersList == nullptr){SGXIdentifier::identifiersList = new SGLUnorderedSet<SGXIdentifier, SGLEqualsTo<SGXIdentifier>, SGLHash<SGXIdentifier>>();}
    (*SGXIdentifier::identifiersList).insert(x);
    return true;
}

bool SGXIdentifier::unregisterIdentifier(SGXIdentifier x){
    if(SGXIdentifier::identifiersList == nullptr || (*SGXIdentifier::identifiersList).contains(x) == false){return false;}
    (*SGXIdentifier::identifiersList).erase(x);
    return true;
}

bool SGXIdentifier::exists() const {
    if(SGXIdentifier::identifiersList == nullptr){return false;}
    return (*SGXIdentifier::identifiersList).contains((*this));
}

bool SGXIdentifier::operator==(SGXIdentifier x) const {
    return ((a == x.a) && (b == x.b) && (c == x.c) && (d == x.d));
}

bool SGXIdentifier::operator<(SGXIdentifier x) const {
    if(a != x.a){return (a < x.a);}
    if(b != x.b){return (b < x.b);}
    if(c != x.c){return (c < x.c);}
    return (d < x.d);
}

bool SGXIdentifier::operator>(SGXIdentifier x) const {
    if(a != x.a){return (a > x.a);}
    if(b != x.b){return (b > x.b);}
    if(c != x.c){return (c > x.c);}
    return (d > x.d);
}

int SGXIdentifier::hash() const {
    SGLArray<int> hashArray(4);
    hashArray.at(0) = SGLHash<unsigned int>()(a);
    hashArray.at(1) = SGLHash<unsigned int>()(b);
    hashArray.at(2) = SGLHash<unsigned int>()(c);
    hashArray.at(3) = SGLHash<unsigned int>()(d);
    return SGLHashAlgorithm::wyHash32(SGLSpan<const unsigned char>(reinterpret_cast<const unsigned char*>(hashArray.pointerToData(0)), 4 * sizeof(int)));
}

bool SGXIdentifier::operator!=(SGXIdentifier x) const {
    return ((a != x.a) || (b != x.b) || (c != x.c) || (d != x.d));
}

SGXString SGXIdentifier::getStringForPrinting() const {
    return (SGXString::unsignedIntToStringBase16(a).fillLeftToLength(8, '0')  + SGXString::unsignedIntToStringBase16(b).fillLeftToLength(8, '0') + SGXString::unsignedIntToStringBase16(c).fillLeftToLength(8, '0') + SGXString::unsignedIntToStringBase16(d).fillLeftToLength(8, '0'));
}
