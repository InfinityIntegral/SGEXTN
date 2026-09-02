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

#include <SGEXTN/Utilities/Identifier.h>
#include <SGEXTN/SingText/String.h>
#include <SGEXTN/Containers/Serialise.h>
#include <SGEXTN/Containers/Span.h>

SGEXTN::Utilities::Identifier::Identifier() : data_(0) {}

SGEXTN::Utilities::Identifier SGEXTN::Utilities::Identifier::nullIdentifier(){
    SGEXTN::Utilities::Identifier x;
    x.data_ = 0u;
    return x;
}

bool SGEXTN::Utilities::Identifier::operator==(SGEXTN::Utilities::Identifier x) const {
    return (data_ == x.data_);
}

bool SGEXTN::Utilities::Identifier::operator!=(SGEXTN::Utilities::Identifier x) const {
    return (data_ != x.data_);
}

SGEXTN::SingText::String SGEXTN::Utilities::Identifier::getStringForPrinting() const {
    return SGEXTN::SingText::String::stringFromUnsignedInt(data_, 16).fillLeftToByteLength(8, '0');
}

SGEXTN::SingText::String SGEXTN::Utilities::Identifier::debugPrint() const {
    return getStringForPrinting();
}

bool SGEXTN::Utilities::Identifier::sendOut(SGEXTN::Utilities::Identifier x, SGEXTN::Containers::Span<unsigned char> data){
    return SGEXTN::Containers::Serialise<unsigned int>::sendOut(x.data_, data);
}

bool SGEXTN::Utilities::Identifier::sendIn(SGEXTN::Utilities::Identifier& x, SGEXTN::Containers::Span<unsigned char> data){
    unsigned int internalData = 0;
    const bool isValid = SGEXTN::Containers::Serialise<unsigned int>::sendIn(internalData, data);
    if(isValid == false){return false;}
    x.data_ = internalData;
    return true;
}

int SGEXTN::Utilities::Identifier::size(){
    return 4;
}
