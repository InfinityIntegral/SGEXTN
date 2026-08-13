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

#include <SGEXTN/SeerattraNum/DirectRandomInstanceLocator.h>
#include <SGEXTN/SeerattraNum/DirectRandom.h>
#include <SGEXTN/Containers/Array.h>
#include <SGEXTN/Containers/Serialise.h>

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(bool useGlobal) : private_ownsRng(useGlobal == false), private_rng(SGEXTN::SeerattraNum::DirectRandom::private_createRng(useGlobal)){}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(const SGEXTN::SeerattraNum::DirectRandom& rng) : private_ownsRng(true), private_rng(new SGEXTN::SeerattraNum::DirectRandom(rng)){}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(const DirectRandomInstanceLocator& x) : private_ownsRng(x.private_ownsRng), private_rng(x.private_rng){
    if(private_ownsRng == true){private_rng = new SGEXTN::SeerattraNum::DirectRandom(*x.private_rng);}
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator=(const DirectRandomInstanceLocator& x){
    if(this == &x){return (*this);}
    if(private_ownsRng == true){delete private_rng;}
    private_ownsRng = x.private_ownsRng;
    if(private_ownsRng == false){private_rng = x.private_rng;}
    else{private_rng = new SGEXTN::SeerattraNum::DirectRandom(*x.private_rng);}
    return (*this);
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::DirectRandomInstanceLocator(DirectRandomInstanceLocator&& x) noexcept : private_ownsRng(x.private_ownsRng), private_rng(x.private_rng){
    x.private_ownsRng = false;
    x.private_rng = nullptr;
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator=(DirectRandomInstanceLocator&& x) noexcept {
    if(private_ownsRng == true){delete private_rng;}
    private_ownsRng = x.private_ownsRng;
    private_rng = x.private_rng;
    x.private_ownsRng = false;
    x.private_rng = nullptr;
    return (*this);
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator::~DirectRandomInstanceLocator(){
    if(private_ownsRng == true){delete private_rng;}
}

SGEXTN::SeerattraNum::DirectRandom& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator*(){
    SGEXTN::SeerattraNum::DirectRandom* temp = private_rng;
    private_rng = temp;
    return (*private_rng);
}

const SGEXTN::SeerattraNum::DirectRandom& SGEXTN::SeerattraNum::DirectRandomInstanceLocator::operator*() const {
    return (*private_rng);
}

SGEXTN::Containers::Array<unsigned char> SGEXTN::SeerattraNum::DirectRandomInstanceLocator::serialise(const SGEXTN::SeerattraNum::DirectRandomInstanceLocator& x){
    if(x.private_ownsRng == false){
        SGEXTN::Containers::Array<unsigned char> outputArray(37, static_cast<unsigned char>(0));
        outputArray.at(32) = static_cast<unsigned char>(0xff);
        return outputArray;
    }
    return SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom>::serialise(*x.private_rng);
}

SGEXTN::SeerattraNum::DirectRandomInstanceLocator SGEXTN::SeerattraNum::DirectRandomInstanceLocator::unserialise(const SGEXTN::Containers::Array<unsigned char>& data, bool& success){
    if(data.length() != 37){
        success = false;
        return SGEXTN::SeerattraNum::DirectRandomInstanceLocator(true);
    }
    if(data.at(32) == static_cast<unsigned char>(0xff)){
        for(int i=0; i<37; i++){
            if(i != 32 && data.at(i) != static_cast<unsigned char>(0)){
                success = false;
                return SGEXTN::SeerattraNum::DirectRandomInstanceLocator(true);
            }
        }
        success = true;
        return SGEXTN::SeerattraNum::DirectRandomInstanceLocator(true);
    }
    const SGEXTN::SeerattraNum::DirectRandom internalRng = SGEXTN::Containers::Serialise<SGEXTN::SeerattraNum::DirectRandom>::unserialise(data, &success);
    if(success == false){return SGEXTN::SeerattraNum::DirectRandomInstanceLocator(true);}
    return SGEXTN::SeerattraNum::DirectRandomInstanceLocator(internalRng);
}

int SGEXTN::SeerattraNum::DirectRandomInstanceLocator::lengthof([[maybe_unused]] const SGEXTN::SeerattraNum::DirectRandomInstanceLocator& x){
    return 37;
}
